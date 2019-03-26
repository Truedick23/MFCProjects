
// cgDZxFillPolyView.cpp : CcgDZxFillPolyView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cgDZxFillPoly.h"
#include <stack>

#endif

#include "cgDZxFillPolyDoc.h"
#include "cgDZxFillPolyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcgDZxFillPolyView

IMPLEMENT_DYNCREATE(CcgDZxFillPolyView, CView)

BEGIN_MESSAGE_MAP(CcgDZxFillPolyView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CcgDZxFillPolyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
//	ON_WM_MBUTTONDOWN()
//	ON_WM_MBUTTONDBLCLK()
END_MESSAGE_MAP()

int m_patternData[20][20] = {	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
// CcgDZxFillPolyView 构造/析构

CcgDZxFillPolyView::CcgDZxFillPolyView()
{
	// TODO: 在此处添加构造代码
	m_pNumbers = 0;
	ABS_DOUBLE_0 = 0.0001;
}

CcgDZxFillPolyView::~CcgDZxFillPolyView()
{
}

BOOL CcgDZxFillPolyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CcgDZxFillPolyView 绘制

void CcgDZxFillPolyView::OnDraw(CDC* /*pDC*/)
{
	CcgDZxFillPolyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CcgDZxFillPolyView 打印


void CcgDZxFillPolyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CcgDZxFillPolyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CcgDZxFillPolyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CcgDZxFillPolyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CcgDZxFillPolyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CcgDZxFillPolyView 诊断

#ifdef _DEBUG
void CcgDZxFillPolyView::AssertValid() const
{
	CView::AssertValid();
}

void CcgDZxFillPolyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgDZxFillPolyDoc* CcgDZxFillPolyView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgDZxFillPolyDoc)));
	return (CcgDZxFillPolyDoc*)m_pDocument;
}
#endif //_DEBUG


// CcgDZxFillPolyView 消息处理程序


void CcgDZxFillPolyView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CcgDZxFillPolyDoc *pDoc = GetDocument();     // 获取Doc类指针

	pDoc->wm_width = cx;                    // 记录窗体视口尺寸
	pDoc->wm_height = cy;

}



void CcgDZxFillPolyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_pNumbers < N) {
		m_pAccord[m_pNumbers] = point;
		m_pNumbers++;

		m_mousePoint = point;
	}
	CView::OnLButtonDown(nFlags, point);
}

int CcgDZxFillPolyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pDC = new CClientDC(this);

	return 0;
}

void CcgDZxFillPolyView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CcgDZxFillPolyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
		if (!pDoc)
	return;

	m_pDC->MoveTo(m_pAccord[m_pNumbers-1]);
	m_pDC->LineTo(m_pAccord[0]);

	m_pAccord[m_pNumbers] = m_pAccord[0];
	m_pNumbers++;

	if(pDoc->m_drawMode == 1) {
		long t1 = GetTickCount();
		Fillpolygon(m_pNumbers, m_pAccord, m_pDC);
		long t2 = GetTickCount();
		pDoc->FillPointTime = t2 - t1;
		pDoc->FillPointDrawed = true;
		//UpdateData(FALSE);
	}
	
	else if(pDoc->m_drawMode == 2) {
		long t1 = GetTickCount();
		PointFillpoly(m_pNumbers, m_pAccord, m_pDC);
		long t2 = GetTickCount();
		pDoc->ScanLineTime = t2 - t1;
		pDoc->ScanLineDrawed = true;
		//UpdateData(FALSE);
	}

	else if(pDoc->m_drawMode == 3) {

		//ScanLineFill4(seed.x, seed.y, RGB(255, 255, 255), m_pDC);
		long t1 = GetTickCount();
		ScanLineSeedFill(seed.x, seed.y, RGB(0, 0, 0),RGB(205, 112, 84), m_pDC);
		//SeedFill(seed, RGB(0, 0, 0),RGB(255, 255, 255),  m_pDC);
		long t2 = GetTickCount();
		pDoc->SeedFillTime = t2 - t1;
		pDoc->SeedFillDrawed = true;
		//UpdateData(FALSE);
	}

	else if(pDoc->m_drawMode == 4) {
		TriPoly(m_pNumbers, m_pAccord, m_pDC);
	}
	m_pNumbers = 0;
	CView::OnLButtonDblClk(nFlags, point);
}


void CcgDZxFillPolyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CcgDZxFillPolyDoc* pDoc = GetDocument();
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

void CcgDZxFillPolyView::Fillpolygon(int pNumbers, CPoint *points, CDC *pDC)
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

void CcgDZxFillPolyView::pLoadPolygon(int pNumbers, CPoint *points)
{
	float x1,y1,x2,y2;

	x1 = points[0].x;    y1 = points[0].y+0.5;
	for (int i = 1; i < pNumbers; i++) {
		x2 = points[i].x;    y2 = points[i].y+0.5;
		/* fill the right condition below */ 
		if (y1 != y2)
			pInsertLine(x1, y1, x2, y2);
		x1 = x2;      y1 = y2;
	}
}

void CcgDZxFillPolyView::pInsertLine(float x1, float y1,
	float x2, float y2)
{
	int i;
	float Ymax,Ymin;

	Ymax = (y2 > y1) ? y2 : y1;
	Ymin = (y2 < y1) ? y2 : y1;
	i = m_edgeNumbers;
	/* fill the right condition code below */ 
	while (i > 0 && Ymax > m_yMax[i-1]) {
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

void CcgDZxFillPolyView::Include()
{
	/* fill the right condition code below */ 
	while (m_End < m_edgeNumbers && m_yMax[m_End] > m_Scan) {
		m_Xa[m_End] = m_Xa[m_End] - 0.5*m_Dx[m_End];
		m_End++;
	}
}

void CcgDZxFillPolyView::UpdateXvalue()
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

void CcgDZxFillPolyView::pXsort(int Begin, int i)
{
	float temp;

	while (i > Begin && m_Xa[i] < m_Xa[i-1]) {
		temp = m_Xa[i];   m_Xa[i]   = m_Xa[i-1];   m_Xa[i-1] = temp;
		temp = m_Dx[i];   m_Dx[i]   = m_Dx[i-1];   m_Dx[i-1] = temp;
		temp = m_yMin[i]; m_yMin[i] = m_yMin[i-1]; m_yMin[i-1] = temp;
		i--;
	}
}

void CcgDZxFillPolyView::pFillScan(CDC* pDC)
{
	int x,y;
	CcgDZxFillPolyDoc* pDoc = GetDocument();
	pDC->SetROP2(10);
	for (int i = m_Begin; i < m_End; i += 2) {
		if (pDoc->m_drawMode == 0) {
			pDC->MoveTo(m_Xa[i],   m_Scan);
			pDC->LineTo(m_Xa[i+1], m_Scan);

		} else {
		  y = m_Scan;
		  for (int x = m_Xa[i]; x < m_Xa[i+1]; x++) 
			if (m_patternData[y%20][x%20])
				pDC->SetPixel(x, y, RGB(0,0,0));
			}
	}
}

void CcgDZxFillPolyView::PointFillpoly(int pNumbers, CPoint *points, CDC *m_pDC)
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

BoxRect_t CcgDZxFillPolyView::GetPolygonRect(int pointNumOfPolygon, CPoint tarPolygon[])
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

BOOL CcgDZxFillPolyView::PointInPolygon(int pointNumOfPolygon, CPoint tarPolygon[], 
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


void CcgDZxFillPolyView::SeedFill(CPoint seed,COLORREF fill,COLORREF edge,CDC* pDC)
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
		if (PointInPolygon(m_pNumbers, m_pAccord, test))
			continue;

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


void CcgDZxFillPolyView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ClientToScreen(&point);
	OnContextMenu(this, point);

	GetDesktopWindow()->MapWindowPoints(this, &point, 1);
	seed = point;
}

void CcgDZxFillPolyView::ScanLineSeedFill(int x, int y, COLORREF boundarycolor,COLORREF newcolor ,CDC *pDC) {
	using namespace std;
	int x0, xl, xr, y0, xid;
	bool flag;
	stack<CPoint>s;
	CPoint p;
	s.push(CPoint(x, y));
	while (!s.empty()) {
		p = s.top();
		s.pop();
		x = p.x;
		y = p.y;
		pDC->SetPixel(x, y, newcolor);
		x0 = x + 1;
		while (pDC->GetPixel(x0, y) != boundarycolor && pDC->GetPixel(x0, y) != newcolor) {
			pDC->SetPixel(x0, y, newcolor);
			x0++;
		}
		
		xr = x0 - 1;
		x0 = x - 1;
		while (pDC->GetPixel(x0, y) != boundarycolor && pDC->GetPixel(x0, y) != newcolor) {
			pDC->SetPixel(x0, y, newcolor);
			x0--;
		}
		xl = x0 + 1;
		y0 = y;
		for (int i = 1; i >= -1; i-=2) {
			x0 = xr;
			y = y0 + i;
			while (x0 >= xl) {
				flag = false;
				while (pDC->GetPixel(x0, y) != boundarycolor && pDC->GetPixel(x0, y) != newcolor && x0 >= xl)
				{
					if (!flag) {
						flag = true;
						xid = x0;
					}
					x0--;
				}
				if (flag) {
					s.push(CPoint(xid, y));
					flag = false;
				}
				while (pDC->GetPixel(x0, y) == boundarycolor || pDC->GetPixel(x0, y) == newcolor) 
					x0--;
				}
			}
		}
	}

void CcgDZxFillPolyView::TriPoly(int pNumbers, CPoint points[100], CDC *pDC) {
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen * pOldPen = pDC->SelectObject(&pen);
	if (pNumbers <= 3) return;
	//寻找最左顶点
	int L = 0, min = 10010, LL = 0, LR = 0; //左顶点，右顶点
	for(int i = 0; i < pNumbers; i++) {
		if (points[i].x < min) {
			min = points[i].x;
			L = i;
		}
	}
	LR = (L + 1) % pNumbers;
	LL = L == 0 ? (pNumbers - 1) : L - 1;
	int inNum = 0;
	CPoint inPoints[100] = {CPoint(0,0)};
	int preIndex[100] = { 0 };
	//是否有进入顶点
	for (int i = 0; i < pNumbers; i++) {
		if (i == L || i == LL || i == LR) {
			continue;
		}
		if (isInTriangle(points[L], points[LL], points[LR], points[i])) {
			inPoints[inNum] = points[i];
			preIndex[inNum] = i;
			inNum++;
		}
	}
	CPoint p1[100] = { CPoint(0,0) }, p2[100] = { CPoint(0,0) };
	int index1 = 0, index2 = 0;
	if (inNum == 0) {
		//分割
		pDC->MoveTo(points[LL].x, points[LL].y);
		pDC->LineTo(points[LR].x, points[LR].y);
		pDC->SelectObject(pOldPen);
		//构造新的多边形
		for (int i = 0; i < pNumbers; i++) {
			if (i == L) {
				continue;
			}
			p1[index1++] = points[i];
		}
	}
	else {
		//Tri内有其他顶点，找最左顶点
		index1 = 0;
		index2 = 0;
		int mostLeftIn=0,minLeftIn=10005;
		for (int i = 0; i < inNum; i++) {
			if (inPoints[i].x < minLeftIn) {
				minLeftIn = inPoints[i].x;
				mostLeftIn = preIndex[i];
			}
		}
		pDC->MoveTo(points[L].x, points[L].y);
		pDC->LineTo(points[mostLeftIn].x, points[mostLeftIn].y);
		pDC->SelectObject(pOldPen);
		//分割多边形，两部分，分别递归
		for (int i = L; i != mostLeftIn; i++) {
			if (i >= pNumbers) {
				i -= pNumbers;
			}
			if (i == mostLeftIn) break;
			p1[index1++] = points[i]; 
		}
		p1[index1++] = points[mostLeftIn];
		for (int i = L; i!=mostLeftIn; i--) {
			if (i < 0) {
				i += pNumbers;
			}
			if (i == mostLeftIn) break;
			p2[index2++] = points[i];
		}
		p2[index2++] = points[mostLeftIn];
	}
	TriPoly(index1, p1, pDC);
	TriPoly(index2, p2, pDC);
}

double CcgDZxFillPolyView::getTriangleArea(CPoint p0, CPoint p1, CPoint p2) {
	CPoint ab, bc;
	ab = CPoint(p1.x - p0.x, p1.y - p0.y);
	bc = CPoint(p2.x - p1.x, p2.y - p1.y);
	return fabs((ab.x * bc.y - ab.y * bc.x) / 2.0);
}

bool CcgDZxFillPolyView::isInTriangle(CPoint a, CPoint b, CPoint c, CPoint d) {
	double sabc, sadb, sbdc, sadc;
	sabc = getTriangleArea(a, b, c);
	sadb = getTriangleArea(a, d, b);
	sbdc = getTriangleArea(b, d, c);
	sadc = getTriangleArea(a, d, c);
	double sumSuqar = sadb + sbdc + sadc;
	if (-ABS_DOUBLE_0 < (sabc - sumSuqar) && (sabc - sumSuqar) < ABS_DOUBLE_0) {
		return true;
	}
	else {
		return false;
	}
}
