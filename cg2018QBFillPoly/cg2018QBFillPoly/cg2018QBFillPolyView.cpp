
// cg2018QBFillPolyView.cpp : Ccg2018QBFillPolyView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cg2018QBFillPoly.h"
#endif

#include "cg2018QBFillPolyDoc.h"
#include "cg2018QBFillPolyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// Ccg2018QBFillPolyView

IMPLEMENT_DYNCREATE(Ccg2018QBFillPolyView, CView)

BEGIN_MESSAGE_MAP(Ccg2018QBFillPolyView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Ccg2018QBFillPolyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// Ccg2018QBFillPolyView 构造/析构

Ccg2018QBFillPolyView::Ccg2018QBFillPolyView()
{
	// TODO: 在此处添加构造代码
	m_pNumbers = 0;
}

Ccg2018QBFillPolyView::~Ccg2018QBFillPolyView()
{
}

BOOL Ccg2018QBFillPolyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Ccg2018QBFillPolyView 绘制

void Ccg2018QBFillPolyView::OnDraw(CDC* /*pDC*/)
{
	Ccg2018QBFillPolyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// Ccg2018QBFillPolyView 打印


void Ccg2018QBFillPolyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Ccg2018QBFillPolyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Ccg2018QBFillPolyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Ccg2018QBFillPolyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void Ccg2018QBFillPolyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Ccg2018QBFillPolyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Ccg2018QBFillPolyView 诊断

#ifdef _DEBUG
void Ccg2018QBFillPolyView::AssertValid() const
{
	CView::AssertValid();
}

void Ccg2018QBFillPolyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ccg2018QBFillPolyDoc* Ccg2018QBFillPolyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ccg2018QBFillPolyDoc)));
	return (Ccg2018QBFillPolyDoc*)m_pDocument;
}
#endif //_DEBUG


// Ccg2018QBFillPolyView 消息处理程序


void Ccg2018QBFillPolyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_pNumbers < N) {
		m_pAccord[m_pNumbers] = point;
		m_pNumbers++;

		m_mousePoint = point;
	}	

	CView::OnLButtonDown(nFlags, point);
}


void Ccg2018QBFillPolyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_pNumbers) {

		m_pDC->SetROP2(2);
		m_pDC->MoveTo(m_pAccord[m_pNumbers-1]);
		m_pDC->LineTo(m_mousePoint);

		m_mousePoint = point;
		m_pDC->MoveTo(m_pAccord[m_pNumbers-1]);
		m_pDC->LineTo(m_mousePoint);
	}

	CView::OnMouseMove(nFlags, point);
}


void Ccg2018QBFillPolyView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pDC->MoveTo(m_pAccord[m_pNumbers-1]);
	m_pDC->LineTo(m_pAccord[0]);

	m_pAccord[m_pNumbers] = m_pAccord[0];
	m_pNumbers++;

//	Fillpolygon(m_pNumbers, m_pAccord, m_pDC);

	m_pNumbers = 0;

	CView::OnLButtonDblClk(nFlags, point);
}


int Ccg2018QBFillPolyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pDC = new CClientDC(this);

	return 0;
}

void Ccg2018QBFillPolyView::Fillpolygon(int pNumbers, CPoint *points, CDC *pDC)
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

void Ccg2018QBFillPolyView::pLoadPolygon(int pNumbers, CPoint *points)
{
	float x1,y1,x2,y2;

	x1 = points[0].x;    y1 = points[0].y+0.5;
	for (int i = 1; i < pNumbers; i++) {
		x2 = points[i].x;    y2 = points[i].y+0.5;
		/* fill the right condition below */ 
		if (....../* un-horizontal line */ ) pInsertLine(x1, y1, x2, y2);
		x1 = x2;      y1 = y2;
	}
}

void Ccg2018QBFillPolyView::pInsertLine(float x1, float y1,
	float x2, float y2)
{
	int i;
	float Ymax,Ymin;

	Ymax = (y2 > y1) ? y2 : y1;
	Ymin = (y2 < y1) ? y2 : y1;
	i = m_edgeNumbers;
	/* fill the right condition code below */ 
	while ( ...... /* uncomparing to the begin && current line's yMax less than the last */ ) {
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
	m_Dx[i] = ...... /* current line's 1/m */;
	m_edgeNumbers++;
}

void Ccg2018QBFillPolyView::Include()
{
	/* fill the right condition code below */ 
	while ( ....../* Have exist edge &&  m_scan less than m_End line's yMax */ ) {
		m_Xa[m_End] = m_Xa[m_End] - 0.5*m_Dx[m_End];
		m_Dx[m_End] = -m_Dx[m_End];
		m_End++;
	}
}

void Ccg2018QBFillPolyView::UpdateXvalue()
{
	int i,start = m_Begin;

	for (i = start; i < m_End; i++) {
		if (m_Scan > m_yMin[i]) {
			/* fill the right calculation code below */
			......        /* Calculating intersect point x value */ ;
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

void Ccg2018QBFillPolyView::pXsort(int Begin, int i)
{
	float temp;

	while (i > Begin && m_Xa[i] < m_Xa[i-1]) {
		temp = m_Xa[i];   m_Xa[i]   = m_Xa[i-1];   m_Xa[i-1] = temp;
		temp = m_Dx[i];   m_Dx[i]   = m_Dx[i-1];   m_Dx[i-1] = temp;
		temp = m_yMin[i]; m_yMin[i] = m_yMin[i-1]; m_yMin[i-1] = temp;
		i--;
	}
}

void Ccg2018QBFillPolyView::pFillScan(CDC* pDC)
{
	int x,y;
//	Ccg2017QBFillpolyDoc* pDoc = GetDocument();

	//	pDC->SetROP2(10);
	for (int i = m_Begin; i < m_End; i += 2) {
		if (pDoc->m_drawMode == 0) {
			pDC->MoveTo(m_Xa[i],   m_Scan);
			pDC->LineTo(m_Xa[i+1], m_Scan);

		} else {
		  y = m_Scan;
		  for (int x = m_Xa[i]; x < m_Xa[i+1]; x++) 
			if (m_patternData[y%7][x%8])
				pDC->SetPixel(x, y, RGB(255,0,0));

		}

	}
}

void Ccg2017QBFillpolyView::PointFillpoly(int pNumbers, CPoint *points, CDC *pDC)
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
 				pDC->SetPixel(testPoint.x, testPoint.y, RGB(255,0,0));
      }
}


BoxRect_t CCgQBFillView::GetPolygonRect(int pointNumOfPolygon, CPoint tarPolygon[])
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

BOOL CCgQBFillView::PointInPolygon(int pointNumOfPolygon, CPoint tarPolygon[], 
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

	void Ccg2018QBFillPolyView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	Ccg2018QB
}
