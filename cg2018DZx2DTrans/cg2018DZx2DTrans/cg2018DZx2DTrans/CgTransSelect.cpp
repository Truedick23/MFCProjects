#include "stdafx.h"
#include "cg2018DZx2DTrans.h"
#include "CgTransSelect.h"
#include "cg2018DZx2DTransDoc.h"

#define WND_DELTAX 5
#define WND_DELTAY 5
// CgTransSelect

IMPLEMENT_DYNCREATE(CgTransSelect, CFormView)

CgTransSelect::CgTransSelect()
	: CFormView(CgTransSelect::IDD)
{
	
}

CgTransSelect::~CgTransSelect()
{
}

void CgTransSelect::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgTransSelect, CFormView)
	ON_BN_CLICKED(IDC_YUP, &CgTransSelect::OnBnClickedYup)
	ON_BN_CLICKED(IDC_XLEFT, &CgTransSelect::OnBnClickedXleft)
	ON_BN_CLICKED(IDC_TRANSMODE, &CgTransSelect::OnBnClickedTransmode)
	ON_BN_CLICKED(IDC_XRIGHT, &CgTransSelect::OnBnClickedXright)
	ON_BN_CLICKED(IDC_YDOWN, &CgTransSelect::OnBnClickedYdown)
	ON_BN_CLICKED(IDC_RDTRANSLINE, &CgTransSelect::OnBnClickedRdtransline)
	ON_BN_CLICKED(IDC_TRANSPOLY, &CgTransSelect::OnBnClickedTranspoly)
	ON_BN_CLICKED(IDC_RDLIANGB, &CgTransSelect::OnBnClickedRdliangb)
	ON_BN_CLICKED(IDC_RDWEILERA, &CgTransSelect::OnBnClickedRdweilera)
END_MESSAGE_MAP()


// CgTransSelect 诊断

#ifdef _DEBUG
void CgTransSelect::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CgTransSelect::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CgTransSelect 消息处理程序


void CgTransSelect::OnBnClickedYup()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018DZx2DTransDoc *pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();
	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLy += WND_DELTAY;
		pDoc->m_wndRy += WND_DELTAY;
	}
	pDoc->m_transDir = 3;
	CString m_stringinfo = _T("You clicked Y-Up.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
	pDoc->UpdateAllViews(this);
}


void CgTransSelect::OnBnClickedXleft()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018DZx2DTransDoc *pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();
	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLx -= WND_DELTAX;
		pDoc->m_wndRx -= WND_DELTAX;
	}
	pDoc->m_transDir = 0;
	CString m_stringinfo = _T("You clicked X-Left.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
	pDoc->UpdateAllViews(this);
}


void CgTransSelect::OnBnClickedTransmode()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018DZx2DTransDoc* pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();
	CButton *pButton = (CButton *)GetDlgItem(IDC_TRANSMODE);

	//	if (pDoc->rayTraceNow) return;

	pDoc->m_transMode++;
	if (pDoc->m_transMode > 2) pDoc->m_transMode = 0;

	if (pDoc->m_transMode == 0)      pButton->SetWindowText(_T("Move"));
	else if (pDoc->m_transMode == 1) pButton->SetWindowText(_T("Rotate"));
	else                             pButton->SetWindowText(_T("Scale"));
}


void CgTransSelect::OnBnClickedXright()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018DZx2DTransDoc *pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();
	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLx += WND_DELTAX;
		pDoc->m_wndRx += WND_DELTAX;
	}
	pDoc->m_transDir = 1;
	CString m_stringinfo = _T("You clicked X-Right.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
	pDoc->UpdateAllViews(this);
}


void CgTransSelect::OnBnClickedYdown()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018DZx2DTransDoc *pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();
	if (pDoc->m_transSelect == 2) {
		pDoc->m_wndLy -= WND_DELTAY;
		pDoc->m_wndRy -= WND_DELTAY;
	}
	pDoc->m_transDir = 2;
	CString m_stringinfo = _T("You clicked Y-Down.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
	pDoc->UpdateAllViews(this);
}

void CgTransSelect::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CStatic *viewPlane =(CStatic *)GetDlgItem(IDC_VIEWPORT);
	Ccg2018DZx2DTransDoc* pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();
	CDC *pDC = viewPlane->GetDC();

	CDC     *prjPlaneCDC;
	CRect    prjPlaneRet;

	prjPlaneCDC = viewPlane->GetDC();
	viewPlane->GetClientRect(&prjPlaneRet); 

	pDoc->m_wndRx = prjPlaneRet.Width();
	pDoc->m_wndRy = prjPlaneRet.Height();

	// Clear BackGround of DC
	CBrush brBlack(RGB(155, 205, 155));
	
	CPen *oldPen;

	CPen newPen;
	newPen.CreatePen(PS_SOLID, 1, RGB(139, 26, 26));
	oldPen = (CPen *)pDC->SelectObject(&newPen);
	prjPlaneCDC->FillRect(prjPlaneRet, &brBlack);	

    ViewTransLine(prjPlaneCDC, prjPlaneRet);
	ViewTransPolygon(prjPlaneCDC, prjPlaneRet);

	if (pDoc->m_lineVisible) {
		ViewTransLine(prjPlaneCDC, prjPlaneRet);		
		pDC->MoveTo(pDoc->CP1.x, prjPlaneRet.Height()-pDoc->CP1.y);
		pDC->LineTo(pDoc->CP2.x, prjPlaneRet.Height()-pDoc->CP2.y);
	}

	if (pDoc->m_LB_lineVisible) {
		ViewTransLine(prjPlaneCDC, prjPlaneRet);
		pDC->MoveTo(pDoc->LB_CP1.x, prjPlaneRet.Height()-pDoc->LB_CP1.y);
		pDC->LineTo(pDoc->LB_CP2.x, prjPlaneRet.Height()-pDoc->LB_CP2.y);
	}

	
	if (pDoc->m_polygonVisible) {
		ViewTransPolygon(prjPlaneCDC, prjPlaneRet);
		pDC->MoveTo(pDoc->m_clipPolygon[0].x, prjPlaneRet.Height()-pDoc->m_clipPolygon[0].y);
		for (int i = 1; i < pDoc->m_clipPointNumber; i++) 
			pDC->LineTo(pDoc->m_clipPolygon[i].x, prjPlaneRet.Height()-pDoc->m_clipPolygon[i].y);
	}
	/*
	if (pDoc->m_WA_polygonVisible) {
		ViewTransPolygon(prjPlaneCDC, prjPlaneRet);
		pDC->MoveTo(pDoc->m_WA_clipPolygon[0].x, prjPlaneRet.Height()-pDoc->m_WA_clipPolygon[0].y);
		for (int i = 1; i < pDoc->m_WA_clipPointNumber; i++) 
			pDC->LineTo(pDoc->m_WA_clipPolygon[i].x, prjPlaneRet.Height()-pDoc->m_WA_clipPolygon[i].y);
	}*/


	// Must remember to release prjPlaneCDC
	ReleaseDC(prjPlaneCDC);
}

void CgTransSelect::ViewTransLine(CDC* pDC, CRect dcRect)
{
	CPen newPen;
	CPen *oldPen;
	Ccg2018DZx2DTransDoc* pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();

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

	pDoc->LB_CP1.x = (pDoc->LB_CP1.x - pDoc->m_wndLx) * Sx;
	pDoc->LB_CP1.y = (pDoc->LB_CP1.y - pDoc->m_wndLy) * Sy;
	pDoc->LB_CP2.x = (pDoc->LB_CP2.x - pDoc->m_wndLx) * Sx;
	pDoc->LB_CP2.y = (pDoc->LB_CP2.y - pDoc->m_wndLy) * Sy;

	// Remember: must delete newPen every time.	
	pDC->SelectObject(oldPen);
	newPen.DeleteObject();
}

void CgTransSelect::ViewTransPolygon(CDC* pDC, CRect dcRect)
{
	CPen newPen;
	CPen *oldPen;
	Ccg2018DZx2DTransDoc* pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();

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
	/*
	for (int i = 0; i < pDoc->m_WA_clipPointNumber; i++) {
		pDoc->m_WA_clipPolygon[i].x = (pDoc->m_WA_clipPolygon[i].x - pDoc->m_wndLx) * Sx;
		pDoc->m_WA_clipPolygon[i].y = (pDoc->m_WA_clipPolygon[i].y - pDoc->m_wndLy) * Sy;
	}*/

	// Remember: must delete newPen every time.	
	pDC->SelectObject(oldPen);
	newPen.DeleteObject();  
}

void CgTransSelect::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	Ccg2018DZx2DTransDoc* pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();

	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(TRUE);

	m_transSelect = pDoc->m_transSelect;

	UpdateData(FALSE);
}


void CgTransSelect::OnBnClickedRdtransline()
{
	Ccg2018DZx2DTransDoc *pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();
	pDoc->m_transSelect = 0;
	CString m_stringinfo = _T("You clicked TransLine.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CgTransSelect::OnBnClickedTranspoly()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018DZx2DTransDoc *pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();
	pDoc->m_transSelect = 1;
	CString m_stringinfo = _T("You clicked TransPolye.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CgTransSelect::OnBnClickedRdliangb()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018DZx2DTransDoc *pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();
	pDoc->m_transSelect = 3;
	CString m_stringinfo = _T("You clicked Liang-Barsky.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CgTransSelect::OnBnClickedRdweilera()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018DZx2DTransDoc *pDoc = (Ccg2018DZx2DTransDoc*)GetDocument();
	pDoc->m_transSelect = 4;
	CString m_stringinfo = _T("You clicked Weiler-Atherton.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}
