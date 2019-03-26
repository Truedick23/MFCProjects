
// cgDzxFillPolyView.cpp : CcgDzxFillPolyView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cgDzxFillPoly.h"
#include <stack>

#endif

#include "cgDzxFillPolyDoc.h"
#include "cgDzxFillPolyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcgDzxFillPolyView

IMPLEMENT_DYNCREATE(CcgDzxFillPolyView, CView)

BEGIN_MESSAGE_MAP(CcgDzxFillPolyView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CcgDzxFillPolyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CcgDzxFillPolyView 构造/析构
int m_patternData1[20][20] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							 {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							 {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
							 {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
							 {0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
						     {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
						     {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
							 {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
							 {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
						     {0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
					         {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
							 {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
							 {0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
						     {0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
						     {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
							 {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
							 {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
						     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
						     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int m_patternData2[20][20] = {	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
								{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
								{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
								{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int m_patternData3[20][20] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
								{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
								{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
								{0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0},
								{0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
								{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};	

CcgDzxFillPolyView::CcgDzxFillPolyView()
{
	// TODO: 在此处添加构造代码
	m_pNumbers = 0;
	pattern = 0;
}

CcgDzxFillPolyView::~CcgDzxFillPolyView()
{
}

BOOL CcgDzxFillPolyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CcgDzxFillPolyView 绘制

void CcgDzxFillPolyView::OnDraw(CDC* /*pDC*/)
{
	CcgDzxFillPolyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CDC* pDC = GetDC();               // 获取绘图设备描述表指针

    // 绘制2D坐标系
	pDC->MoveTo(0, pDoc->wm_height/2);
	pDC->LineTo(pDoc->wm_width, pDoc->wm_height/2);
	pDC->MoveTo(pDoc->wm_width/2, 0);
	pDC->LineTo(pDoc->wm_width/2, pDoc->wm_height);

}


// CcgDzxFillPolyView 打印


void CcgDzxFillPolyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CcgDzxFillPolyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CcgDzxFillPolyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CcgDzxFillPolyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CcgDzxFillPolyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
	GetCursorPos(&seed);
}

void CcgDzxFillPolyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CcgDzxFillPolyView 诊断

#ifdef _DEBUG
void CcgDzxFillPolyView::AssertValid() const
{
	CView::AssertValid();
}

void CcgDzxFillPolyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgDzxFillPolyDoc* CcgDzxFillPolyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgDzxFillPolyDoc)));
	return (CcgDzxFillPolyDoc*)m_pDocument;
}
#endif //_DEBUG


// CcgDzxFillPolyView 消息处理程序


void CcgDzxFillPolyView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CcgDzxFillPolyDoc *pDoc = GetDocument();
	pDoc->wm_width = cx;
	pDoc->wm_height = cy;
}


void CcgDzxFillPolyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_pNumbers < N) {
		m_pAccord[m_pNumbers] = point;
		m_pNumbers++;

		m_mousePoint = point;
	}
	CView::OnLButtonDown(nFlags, point);
}

int CcgDzxFillPolyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pDC = new CClientDC(this);

	return 0;
}

void CcgDzxFillPolyView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CcgDzxFillPolyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC* m_pDC = GetDC();
	m_pDC->MoveTo(m_pAccord[m_pNumbers-1]);
	m_pDC->LineTo(m_pAccord[0]);

	m_pAccord[m_pNumbers] = m_pAccord[0];
	m_pNumbers++;

	if(pDoc->m_drawMode == 1) {
		Fillpolygon(m_pNumbers, m_pAccord, m_pDC);
		pattern++;
		m_pNumbers = 0;
	}
	
	if(pDoc->m_drawMode == 2) {
		BoxRect_t polyRect;
		polyRect = GetPolygonRect(m_pNumbers, m_pAccord);

		m_pDC->MoveTo(polyRect.minX, polyRect.minY);
		m_pDC->LineTo(polyRect.minX, polyRect.maxY);
		m_pDC->LineTo(polyRect.maxX, polyRect.maxY);
		m_pDC->LineTo(polyRect.maxX, polyRect.minY);
		m_pDC->LineTo(polyRect.minX, polyRect.minY);

		CPoint testPoint;
		for(testPoint.x = polyRect.minX; testPoint.x < polyRect.maxX; testPoint.x++)
			for(testPoint.y = polyRect.minY; testPoint.y < polyRect.maxY; testPoint.y++)
				if(PointInPolygon(m_pNumbers, m_pAccord, testPoint))
					m_pDC->SetPixel(testPoint.x, testPoint.y, RGB(255,255,0));
		m_pNumbers = 0;
	}

	if(pDoc->m_drawMode == 3) {
		BoxRect_t polyRect;
		polyRect = GetPolygonRect(m_pNumbers, m_pAccord);
		SeedFill(seed, RGB(238,180,34), RGB(0,0,0), m_pDC, polyRect);
	}
	

	CView::OnLButtonDblClk(nFlags, point);
}


void CcgDzxFillPolyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CcgDzxFillPolyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC* m_pDC = GetDC();
	if(m_pNumbers) {
		m_pDC->SetROP2(2);
		m_pDC->MoveTo(m_pAccord[m_pNumbers-1]);
		m_pDC->LineTo(m_mousePoint);

		m_mousePoint = point;
		m_pDC->MoveTo(m_pAccord[m_pNumbers-1]);
		m_pDC->LineTo(m_mousePoint);
	}
	CView::OnMouseMove(nFlags, point);
}

void CcgDzxFillPolyView::Fillpolygon(int pNumbers, CPoint *points, CDC *pDC)
{

	m_edgeNumbers = 0;
	pLoadPolygon(pNumbers, points);   // Polygon Loading, calculates every edge's m_yMax[],m_yMin[],m_Xa[],m_Dx[]

	m_Begin = m_End = 0;              // Initializing intersect edge set
	m_Scan = (int)m_yMax[0];          // Initial scan-line
	Include();                        // Checking whether exist enter intersecting.
	UpdateXvalue();                   // Calculating intersect point
	while (m_Begin != m_End) {
		pFillScan(pDC);
		m_Scan--;
		Include();
		UpdateXvalue();
	}

}

void CcgDzxFillPolyView::pLoadPolygon(int pNumbers, CPoint *points)
{
	float x1,y1,x2,y2;

	x1 = points[0].x;    y1 = points[0].y+0.5;
	for (int i = 1; i < pNumbers; i++) {
		x2 = points[i].x;    y2 = points[i].y+0.5;
		/* fill the right condition below */ 
		if (y1 - y2)
			pInsertLine(x1, y1, x2, y2);
		x1 = x2;      y1 = y2;
	}
}

void CcgDzxFillPolyView::pInsertLine(float x1, float y1,
	float x2, float y2)
{
	int i;
	float Ymax,Ymin;

	Ymax = (y2 > y1) ? y2 : y1;
	Ymin = (y2 < y1) ? y2 : y1;
	i = m_edgeNumbers;
	/* fill the right condition code below */ 
	while (i > 0 && Ymax >m_yMax[i-1]) {
		m_yMax[i] = m_yMax[i-1];
		m_yMin[i] = m_yMin[i-1];
		m_Xa[i] = m_Xa[i-1];
		m_Dx[i] = m_Dx[i-1];
		i--;
	}
	m_yMax[i] = Ymax;
	m_yMin[i] = Ymin;
	if (y2 > y1) m_Xa[i] = x2;
	else         m_Xa[i] = x1;

	/* fill the right calculation code below */
	m_Dx[i] = (x1 - x2) / (y2 - y1);
	m_edgeNumbers++;
}

void CcgDzxFillPolyView::Include()
{
	/* fill the right condition code below */ 
	while (m_End < m_edgeNumbers && m_yMax[m_End] > m_Scan) {
		m_Xa[m_End] = m_Xa[m_End] - 0.5*m_Dx[m_End];
		//m_Dx[m_End] = -m_Dx[m_End];
		m_End++;
	}
}

void CcgDzxFillPolyView::UpdateXvalue()
{
	int i,start = m_Begin;

	for (i = start; i < m_End; i++) {
		if (m_Scan > m_yMin[i]) {
			/* fill the right calculation code below */
			m_Xa[i] += m_Dx[i];       /* Calculating intersect point x value */ ;
			pXsort(m_Begin, i);
		} else {
			for (int j = i; j > m_Begin; j--) {
				m_yMin[i] = m_yMin[i-1];
				m_Xa[i] = m_Xa[i-1];
				m_Dx[i] = m_Dx[i-1];
			}
			m_Begin++;
		}
	}
}

void CcgDzxFillPolyView::pXsort(int Begin, int i)
{
	float temp;

	while (i > Begin && m_Xa[i] < m_Xa[i-1]) {
		temp = m_Xa[i];   m_Xa[i]   = m_Xa[i-1];   m_Xa[i-1] = temp;
		temp = m_Dx[i];   m_Dx[i]   = m_Dx[i-1];   m_Dx[i-1] = temp;
		temp = m_yMin[i]; m_yMin[i] = m_yMin[i-1]; m_yMin[i-1] = temp;
		i--;
	}
}

void CcgDzxFillPolyView::pFillScan(CDC* pDC)
{
	int x,y;
	CcgDzxFillPolyDoc* pDoc = GetDocument();
	pDC->SetROP2(10);
	for (int i = m_Begin; i < m_End; i += 2) {
		if (pDoc->m_drawMode == 0) {
			pDC->MoveTo(m_Xa[i],   m_Scan);
			pDC->LineTo(m_Xa[i+1], m_Scan);

		} else {
		  y = m_Scan;
		  for (int x = m_Xa[i]; x < m_Xa[i+1]; x++) 
			if (pattern % 3 == 0 && m_patternData1[y%20][x%20]
			  ||pattern % 3 == 1 && m_patternData2[y%20][x%20]
			  ||pattern % 3 == 2 && m_patternData3[y%20][x%20])
				pDC->SetPixel(x, y, RGB(0,0,0));
			}
	}
}

void CcgDzxFillPolyView::PointFillpoly(int pNumbers, CPoint *points, CDC *m_pDC)
{
 	BoxRect_t polyRect;
 
 	polyRect = GetPolygonRect(pNumbers, points);
 
 	m_pDC->MoveTo(polyRect.minX, polyRect.minY);
 	m_pDC->LineTo(polyRect.minX, polyRect.maxY);
 	m_pDC->LineTo(polyRect.maxX, polyRect.maxY);
 	m_pDC->LineTo(polyRect.maxX, polyRect.minY);
 	m_pDC->LineTo(polyRect.minX, polyRect.minY);
 
 	CPoint testPoint;
 
 	for (testPoint.x = polyRect.minX; testPoint.x < polyRect.maxX; testPoint.x++) 
 		for (testPoint.y = polyRect.minY; testPoint.y < polyRect.maxY; testPoint.y++) {
 
 			if (PointInPolygon(m_pNumbers, m_pAccord, testPoint))
 				m_pDC->SetPixel(testPoint.x, testPoint.y, RGB(255,255,0));
      }
}

BoxRect_t CcgDzxFillPolyView::GetPolygonRect(int pointNumOfPolygon, CPoint tarPolygon[])
{
	BoxRect_t boxRect;

	boxRect.minX = 50000;
	boxRect.minY = 50000;
	boxRect.maxX = -50000;
	boxRect.maxY = -50000;

	for (int i = 0; i < pointNumOfPolygon; i++) {
		if (tarPolygon[i].x < boxRect.minX) boxRect.minX = tarPolygon[i].x;
		if (tarPolygon[i].y < boxRect.minY) boxRect.minY = tarPolygon[i].y;
		if (tarPolygon[i].x > boxRect.maxX) boxRect.maxX = tarPolygon[i].x;
		if (tarPolygon[i].y > boxRect.maxY) boxRect.maxY = tarPolygon[i].y;
	}
	return boxRect;
}

BOOL CcgDzxFillPolyView::PointInPolygon(int pointNumOfPolygon, CPoint tarPolygon[], 
	                               CPoint testPoint)
{
	if (pointNumOfPolygon < 3) return false;

	bool  inSide = FALSE;
	float lineSlope,interSectX;
	int   i = 0, j = pointNumOfPolygon-1;

	for (i = 0; i < pointNumOfPolygon; i++) {
		if ((tarPolygon[i].y < testPoint.y && tarPolygon[j].y >= testPoint.y  ||
			tarPolygon[j].y < testPoint.y && tarPolygon[i].y >= testPoint.y) && 
			(tarPolygon[i].x <= testPoint.x || tarPolygon[j].x <= testPoint.x)) {

				if (tarPolygon[j].x != tarPolygon[i].x) {
					lineSlope = (float)(tarPolygon[j].y-tarPolygon[i].y)/(tarPolygon[j].x-tarPolygon[i].x);
					interSectX = (int)(tarPolygon[i].x + (testPoint.y-tarPolygon[i].y) / lineSlope);
				} else interSectX = tarPolygon[i].x;
				if (interSectX < testPoint.x)	inSide = !inSide;
		}
		j = i; 
	}

	return inSide;
}

void CcgDzxFillPolyView::SeedFill(CPoint seed,COLORREF fill,COLORREF edge,CDC* pDC,BoxRect_t polyRect1)
{
	int steps[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	std::stack<CPoint> stackPoint;
	stackPoint.push(seed);
	int x,y;
	CPoint test;
	while(!stackPoint.empty())
	{
		test = stackPoint.top();
		stackPoint.pop();
		x = test.x;
		y = test.y;
		if (x < polyRect1.minX )continue;
		else if (x > polyRect1.maxX)continue;
		else if (y < polyRect1.minY)continue;
		else if (y > polyRect1.maxY)continue;

		COLORREF thispointcolor = GetPixel(pDC->m_hDC,x,y);

		if (GetPixel(pDC->m_hDC,x,y)) continue ;

		else if (thispointcolor != fill)
		{
			pDC->SetPixel(x, y, fill);
			for (int i = 0 ;i < 4 ;i ++)
			{
				test.x = x + steps[i][0];
				test.y = y + steps[i][1];
				stackPoint.push(test);
			}
		}
	}
}