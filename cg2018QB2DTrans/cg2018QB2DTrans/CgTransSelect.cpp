// CgTransSelect.cpp : 实现文件
//

#include "stdafx.h"
#include "cg2018QB2DTrans.h"
#include "CgTransSelect.h"

#include "cg2018QB2DTransDoc.h"

// CCgTransSelect

IMPLEMENT_DYNCREATE(CCgTransSelect, CFormView)

CCgTransSelect::CCgTransSelect()
	: CFormView(CCgTransSelect::IDD)
{

	m_transSelect = 0;
}

CCgTransSelect::~CCgTransSelect()
{
}

void CCgTransSelect::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_TRANSSELECT, m_transSelect);

}

BEGIN_MESSAGE_MAP(CCgTransSelect, CFormView)
	ON_BN_CLICKED(IDC_XLEFT, &CCgTransSelect::OnClickedXleft)
	ON_BN_CLICKED(IDC_XRIGHT, &CCgTransSelect::OnClickedXright)
	ON_BN_CLICKED(IDC_YUP, &CCgTransSelect::OnClickedYup)
	ON_BN_CLICKED(IDC_YDOWN, &CCgTransSelect::OnClickedYdown)
    ON_CBN_SELCHANGE(IDC_TRANSSELECT, &CCgTransSelect::OnSelchangeTransselect)
	ON_BN_CLICKED(IDC_TRANSMODE, &CCgTransSelect::OnClickedTransmode)
END_MESSAGE_MAP()


// CCgTransSelect 诊断

#ifdef _DEBUG
void CCgTransSelect::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCgTransSelect::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCgTransSelect 消息处理程序

#define WND_DELTAX 10
#define WND_DELTAY 10

void CCgTransSelect::OnClickedXleft()
{
    Ccg2018QB2DTransDoc* pDoc = (Ccg2018QB2DTransDoc*)GetDocument();

	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLx -= WND_DELTAX;
		pDoc->m_wndRx -= WND_DELTAX;
	}

	pDoc->m_transDir = 0;

	pDoc->UpdateAllViews(this);
}


void CCgTransSelect::OnClickedXright()
{
	Ccg2018QB2DTransDoc* pDoc = (Ccg2018QB2DTransDoc*)GetDocument();

	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLx += WND_DELTAX;
		pDoc->m_wndRx += WND_DELTAX;
	}
	pDoc->m_transDir = 1;

	pDoc->UpdateAllViews(this);
}


void CCgTransSelect::OnClickedYup()
{
	Ccg2018QB2DTransDoc* pDoc = (Ccg2018QB2DTransDoc*)GetDocument();

	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLy += WND_DELTAY;
		pDoc->m_wndRy += WND_DELTAY;
	}

	pDoc->m_transDir = 3;

	pDoc->UpdateAllViews(this);
}


void CCgTransSelect::OnClickedYdown()
{
	Ccg2018QB2DTransDoc* pDoc = (Ccg2018QB2DTransDoc*)GetDocument();

	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLy -= WND_DELTAY;
		pDoc->m_wndRy -= WND_DELTAY;
	}

	pDoc->m_transDir = 2;

	pDoc->UpdateAllViews(this);
}


void CCgTransSelect::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	Ccg2018QB2DTransDoc* pDoc = (Ccg2018QB2DTransDoc*)GetDocument();

	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);

	m_transSelect = pDoc->m_transSelect;

	UpdateData(FALSE);
}


void CCgTransSelect::OnSelchangeTransselect()
{
	Ccg2018QB2DTransDoc* pDoc = (Ccg2018QB2DTransDoc*)GetDocument();

	UpdateData(TRUE);

	pDoc->m_transSelect = m_transSelect;

	UpdateData(FALSE);
}


void CCgTransSelect::OnClickedTransmode()
{
	Ccg2018QB2DTransDoc* pDoc = (Ccg2018QB2DTransDoc*)GetDocument();
	CButton *pButton = (CButton *)GetDlgItem(IDC_TRANSMODE);

	//	if (pDoc->rayTraceNow) return;

	pDoc->m_transMode++;
	if (pDoc->m_transMode > 2) pDoc->m_transMode = 0;

	if (pDoc->m_transMode == 0)      pButton->SetWindowText(_T("Move"));
	else if (pDoc->m_transMode == 1) pButton->SetWindowText(_T("Rotate"));
	else                             pButton->SetWindowText(_T("Scale"));

}


void CCgTransSelect::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CStatic *viewPlane =(CStatic *)GetDlgItem(IDC_VIEWPORT);
	Ccg2018QB2DTransDoc* pDoc = (Ccg2018QB2DTransDoc*)GetDocument();

	CDC     *prjPlaneCDC;
	CRect    prjPlaneRet;

	prjPlaneCDC = viewPlane->GetDC();
	viewPlane->GetClientRect(&prjPlaneRet); 

	// Clear BackGround of DC
	CBrush brBlack(RGB(255, 255, 0));
	prjPlaneCDC->FillRect(prjPlaneRet, &brBlack);	

    ViewTransLine(prjPlaneCDC, prjPlaneRet);
	ViewTransPolygon(prjPlaneCDC, prjPlaneRet);

// 	if (pDoc->m_lineVisible) ViewTransLine(prjPlaneCDC, prjPlaneRet);
// 	if (pDoc->m_polygonVisible) ViewTransPolygon(prjPlaneCDC, prjPlaneRet);

	// Must remember to release prjPlaneCDC
	ReleaseDC(prjPlaneCDC);
}

void CCgTransSelect::ViewTransLine(CDC* pDC, CRect dcRect)
{
	CPen newPen;
	CPen *oldPen;
	Ccg2018QB2DTransDoc* pDoc = (Ccg2018QB2DTransDoc*)GetDocument();

	// Create new red-color pen to Draw Clipping Line
	newPen.CreatePen(PS_SOLID, 1,  RGB(255, 0, 255));
	oldPen = (CPen *)pDC->SelectObject(&newPen);

	int vx1,vy1,vx2,vy2;

	int wndWidth  = pDoc->m_wndRx - pDoc->m_wndLx;  // Space Window size parameters.
	int wndHeight = pDoc->m_wndRy - pDoc->m_wndLy;

	float Sx = (float)(dcRect.right) / wndWidth;    // View-Space Viewport size parameters.
	float Sy = (float)(dcRect.bottom) / wndHeight;  

	// Please fill the right codes below lines ...
	vx1 = ......;
	vy1 = ......;
	vx2 = ......;
	vy2 = ......;	

	pDC->MoveTo(vx1, dcRect.bottom-vy1);
	pDC->LineTo(vx2, dcRect.bottom-vy2);

	// Remember: must delete newPen every time.	
	pDC->SelectObject(oldPen);
	newPen.DeleteObject();
}

void CCgTransSelect::ViewTransPolygon(CDC* pDC, CRect dcRect)
{
	CPen newPen;
	CPen *oldPen;
	Ccg2018QB2DTransDoc* pDoc = (Ccg2018QB2DTransDoc*)GetDocument();

	// Create new red-color pen to Draw Clipping Line
	newPen.CreatePen(PS_SOLID, 1,  RGB(0, 255, 255));
	oldPen = (CPen *)pDC->SelectObject(&newPen);

	CPoint m_VPolygon[N];

	int wndWidth  = pDoc->m_wndRx - pDoc->m_wndLx;  // Space Window size parameters.
	int wndHeight = pDoc->m_wndRy - pDoc->m_wndLy;

	float Sx = (float)(dcRect.right) / wndWidth;    // View-Space Viewport size parameters.
	float Sy = (float)(dcRect.bottom) / wndHeight;

	// Please fill the right codes below lines ...
	for (int i = 0; i < pDoc->m_clipPointNumber; i++) {
		m_VPolygon[i].x = ......;
		m_VPolygon[i].y = ......;
	}

	pDC->MoveTo(m_VPolygon[0]);
	for (int i = 1; i < pDoc->m_clipPointNumber; i++) pDC->LineTo(m_VPolygon[i]);

	// Remember: must delete newPen every time.	
	pDC->SelectObject(oldPen);
	newPen.DeleteObject();  
}
