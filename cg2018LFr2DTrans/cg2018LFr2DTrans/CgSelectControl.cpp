// CgSelectControl.cpp : 实现文件
//

#include "stdafx.h"
#include "cg2018LFr2DTrans.h"
#include "CgSelectControl.h"
#include "cg2018LFr2DTransDoc.h"

#define WND_DELTAX 5
#define WND_DELTAY 5

// CCgSelectControl

IMPLEMENT_DYNCREATE(CCgSelectControl, CFormView)

CCgSelectControl::CCgSelectControl()
	: CFormView(CCgSelectControl::IDD)
{

}

CCgSelectControl::~CCgSelectControl()
{
}

void CCgSelectControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCgSelectControl, CFormView)
	ON_BN_CLICKED(IDC_YUP, &CCgSelectControl::OnBnClickedYup)
	ON_BN_CLICKED(IDC_XLEFT, &CCgSelectControl::OnBnClickedXleft)
	ON_BN_CLICKED(IDC_TRANSMODE, &CCgSelectControl::OnBnClickedTransmode)
	ON_BN_CLICKED(IDC_TRANSPOLY, &CCgSelectControl::OnBnClickedTranspoly)
	ON_BN_CLICKED(IDC_TRANSLINE, &CCgSelectControl::OnBnClickedTransline)
	ON_BN_CLICKED(IDC_LIANGBSK, &CCgSelectControl::OnBnClickedLiangbsk)
	ON_BN_CLICKED(IDC_WEILERATH, &CCgSelectControl::OnBnClickedWeilerath)
	ON_BN_CLICKED(IDC_XRIGHT, &CCgSelectControl::OnBnClickedXright)
	ON_BN_CLICKED(IDC_YDOWN, &CCgSelectControl::OnBnClickedYdown)
END_MESSAGE_MAP()


// CCgSelectControl 诊断

#ifdef _DEBUG
void CCgSelectControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCgSelectControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCgSelectControl 消息处理程序


void CCgSelectControl::OnBnClickedYup()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018LFr2DTransDoc *pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();
	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLy += WND_DELTAY;
		pDoc->m_wndRy += WND_DELTAY;
	}
	pDoc->m_transDir = 3;
	UpdateData(FALSE);
	pDoc->UpdateAllViews(this);
}


void CCgSelectControl::OnBnClickedXleft()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018LFr2DTransDoc *pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();
	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLx -= WND_DELTAX;
		pDoc->m_wndRx -= WND_DELTAX;
	}
	pDoc->m_transDir = 0;
	UpdateData(FALSE);
	pDoc->UpdateAllViews(this);
}


void CCgSelectControl::OnBnClickedTransmode()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018LFr2DTransDoc* pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();
	CButton *pButton = (CButton *)GetDlgItem(IDC_TRANSMODE);

	//	if (pDoc->rayTraceNow) return;

	pDoc->m_transMode++;
	if (pDoc->m_transMode > 2) pDoc->m_transMode = 0;

	if (pDoc->m_transMode == 0)      pButton->SetWindowText(_T("Move"));
	else if (pDoc->m_transMode == 1) pButton->SetWindowText(_T("Rotate"));
	else                             pButton->SetWindowText(_T("Scale"));
}


void CCgSelectControl::OnBnClickedTranspoly()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018LFr2DTransDoc *pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();
	pDoc->m_transSelect = 1;
	UpdateData(FALSE);
}


void CCgSelectControl::OnBnClickedTransline()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCgSelectControl::OnBnClickedLiangbsk()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018LFr2DTransDoc *pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();
	pDoc->m_transSelect = 3;
	UpdateData(FALSE);
}


void CCgSelectControl::OnBnClickedWeilerath()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018LFr2DTransDoc *pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();
	pDoc->m_transSelect = 4;
	UpdateData(FALSE);
}


void CCgSelectControl::OnBnClickedXright()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018LFr2DTransDoc *pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();
	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLx += WND_DELTAX;
		pDoc->m_wndRx += WND_DELTAX;
	}
	pDoc->m_transDir = 1;
	UpdateData(FALSE);
	pDoc->UpdateAllViews(this);
}


void CCgSelectControl::OnBnClickedYdown()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018LFr2DTransDoc *pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();
	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLy -= WND_DELTAY;
		pDoc->m_wndRy -= WND_DELTAY;
	}
	pDoc->m_transDir = 2;
	UpdateData(FALSE);
	pDoc->UpdateAllViews(this);
}

void CCgSelectControl::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	Ccg2018LFr2DTransDoc* pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();

	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);

	m_transSelect = pDoc->m_transSelect;

	UpdateData(FALSE);
}

void CCgSelectControl::ViewTransLine(CDC* pDC, CRect dcRect)
{
	CPen newPen;
	CPen *oldPen;
	Ccg2018LFr2DTransDoc* pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();

	// Create new red-color pen to Draw Clipping Line
	newPen.CreatePen(PS_SOLID, 1,  RGB(255, 0, 255));
	oldPen = (CPen *)pDC->SelectObject(&newPen);

	int vx1 = 0, vy1 = 0, vx2 = 0, vy2 = 0;

	float wndWidth  = pDoc->m_wndRx - pDoc->m_wndLx;  // Space Window size parameters.
	float wndHeight = pDoc->m_wndRy - pDoc->m_wndLy;

	float Sx = float(dcRect.Width()) / wndWidth;    // View-Space Viewport size parameters.
	float Sy = float(dcRect.Height()) / wndHeight;  

	// Please fill the right codes below lines ...
	pDoc->CP1.x = (pDoc->CP1.x - pDoc->m_wndLx) * Sx;
	pDoc->CP1.y = (pDoc->CP1.y - pDoc->m_wndLy) * Sy;
	pDoc->CP2.x = (pDoc->CP2.x - pDoc->m_wndLx) * Sx;
	pDoc->CP2.y = (pDoc->CP2.y - pDoc->m_wndLy) * Sy;

	// Remember: must delete newPen every time.	
	pDC->SelectObject(oldPen);
	newPen.DeleteObject();
}

void CCgSelectControl::ViewTransPolygon(CDC* pDC, CRect dcRect)
{
	CPen newPen;
	CPen *oldPen;
	Ccg2018LFr2DTransDoc* pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();

	// Create new red-color pen to Draw Clipping Line
	newPen.CreatePen(PS_SOLID, 1,  RGB(255, 130, 71));
	oldPen = (CPen *)pDC->SelectObject(&newPen);

	CPoint m_VPolygon[N];

	float wndWidth  = pDoc->m_wndRx - pDoc->m_wndLx;  // Space Window size parameters.
	float wndHeight = pDoc->m_wndRy - pDoc->m_wndLy;

	float Sx = dcRect.Width() / wndWidth;    // View-Space Viewport size parameters.
	float Sy = dcRect.Height() / wndHeight;

	// Please fill the right codes below lines ...
	
	for (int i = 0; i < pDoc->m_clipPointNumber; i++) {
		pDoc->m_clipPolygon[i].x = (pDoc->m_clipPolygon[i].x - pDoc->m_wndLx) * Sx;
		pDoc->m_clipPolygon[i].y = (pDoc->m_clipPolygon[i].y - pDoc->m_wndLy) * Sy;
	}


	// Remember: must delete newPen every time.	
	pDC->SelectObject(oldPen);
	newPen.DeleteObject();  
}

void CCgSelectControl::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CStatic *viewPlane =(CStatic *)GetDlgItem(IDC_VIEWPORT);
	Ccg2018LFr2DTransDoc* pDoc = (Ccg2018LFr2DTransDoc*)GetDocument();
	CDC *pDC = viewPlane->GetDC();

	CDC     *prjPlaneCDC;
	CRect    prjPlaneRet;

	prjPlaneCDC = viewPlane->GetDC();
	viewPlane->GetClientRect(&prjPlaneRet); 

	// Clear BackGround of DC
	CBrush brBlack(RGB(255, 255, 0));
	prjPlaneCDC->FillRect(prjPlaneRet, &brBlack);	

    ViewTransLine(prjPlaneCDC, prjPlaneRet);
	ViewTransPolygon(prjPlaneCDC, prjPlaneRet);

	if (pDoc->m_lineVisible) {
		ViewTransLine(prjPlaneCDC, prjPlaneRet);		
		pDC->MoveTo(pDoc->CP1.x, prjPlaneRet.Height()-pDoc->CP1.y);
		pDC->LineTo(pDoc->CP2.x, prjPlaneRet.Height()-pDoc->CP2.y);
	}
	if (pDoc->m_polygonVisible) {
		ViewTransPolygon(prjPlaneCDC, prjPlaneRet);
		pDC->MoveTo(pDoc->m_clipPolygon[0].x, prjPlaneRet.Height()-pDoc->m_clipPolygon[0].y);
		for (int i = 1; i < pDoc->m_clipPointNumber; i++) 
			pDC->LineTo(pDoc->m_clipPolygon[i].x, prjPlaneRet.Height()-pDoc->m_clipPolygon[i].y);
	}
	// Must remember to release prjPlaneCDC
	ReleaseDC(prjPlaneCDC);
}