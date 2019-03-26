
// cgLfrFillPolyView.cpp : CcgLfrFillPolyView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "cgLfrFillPoly.h"
#endif

#include "cgLfrFillPolyDoc.h"
#include "cgLfrFillPolyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define N 64

// CcgLfrFillPolyView

IMPLEMENT_DYNCREATE(CcgLfrFillPolyView, CView)

BEGIN_MESSAGE_MAP(CcgLfrFillPolyView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CcgLfrFillPolyView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CcgLfrFillPolyView ����/����

int m_patternData[20][20] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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

CcgLfrFillPolyView::CcgLfrFillPolyView()
{
	// TODO: �ڴ˴���ӹ������
	m_pNumbers = 0;
}

CcgLfrFillPolyView::~CcgLfrFillPolyView()
{
}

BOOL CcgLfrFillPolyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CcgLfrFillPolyView ����

void CcgLfrFillPolyView::OnDraw(CDC* /*pDC*/)
{
	CcgLfrFillPolyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CcgLfrFillPolyView ��ӡ


void CcgLfrFillPolyView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CcgLfrFillPolyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CcgLfrFillPolyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CcgLfrFillPolyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CcgLfrFillPolyView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CcgLfrFillPolyView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CcgLfrFillPolyView ���

#ifdef _DEBUG
void CcgLfrFillPolyView::AssertValid() const
{
	CView::AssertValid();
}

void CcgLfrFillPolyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgLfrFillPolyDoc* CcgLfrFillPolyView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgLfrFillPolyDoc)));
	return (CcgLfrFillPolyDoc*)m_pDocument;
}
#endif //_DEBUG


// CcgLfrFillPolyView ��Ϣ�������

void CcgLfrFillPolyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_pNumbers < N) {
		m_pAccord[m_pNumbers] = point;
		m_pNumbers++;

		m_mousePoint = point;
	}	

	CView::OnLButtonDown(nFlags, point);
}


void CcgLfrFillPolyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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


void CcgLfrFillPolyView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_pDC->MoveTo(m_pAccord[m_pNumbers-1]);
	m_pDC->LineTo(m_pAccord[0]);

	m_pAccord[m_pNumbers] = m_pAccord[0];
	m_pNumbers++;

	Fillpolygon(m_pNumbers, m_pAccord, m_pDC);

	m_pNumbers = 0;

	CView::OnLButtonDblClk(nFlags, point);
}


int CcgLfrFillPolyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_pDC = new CClientDC(this);

	return 0;
}

void CcgLfrFillPolyView::Fillpolygon(int pNumbers, CPoint *points, CDC *pDC)
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

void CcgLfrFillPolyView::pLoadPolygon(int pNumbers, CPoint *points)
{
	float x1,y1,x2,y2;

	x1 = points[0].x;    y1 = points[0].y+0.5;
	for (int i = 1; i < pNumbers; i++) {
		x2 = points[i].x;    y2 = points[i].y+0.5;
		/* fill the right condition below */ 
		if (y1 - y2) pInsertLine(x1, y1, x2, y2);
		x1 = x2;      y1 = y2;
	}
}

void CcgLfrFillPolyView::pInsertLine(float x1, float y1,
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

void CcgLfrFillPolyView::Include()
{
	/* fill the right condition code below */ 
	while (m_End < m_edgeNumbers && m_yMax[m_End] > m_Scan) {
		m_Xa[m_End] = m_Xa[m_End] - 0.5*m_Dx[m_End];
		//m_Dx[m_End] = -m_Dx[m_End];
		m_End++;
	}
}

void CcgLfrFillPolyView::UpdateXvalue()
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

void CcgLfrFillPolyView::pXsort(int Begin, int i)
{
	float temp;

	while (i > Begin && m_Xa[i] < m_Xa[i-1]) {
		temp = m_Xa[i];   m_Xa[i]   = m_Xa[i-1];   m_Xa[i-1] = temp;
		temp = m_Dx[i];   m_Dx[i]   = m_Dx[i-1];   m_Dx[i-1] = temp;
		temp = m_yMin[i]; m_yMin[i] = m_yMin[i-1]; m_yMin[i-1] = temp;
		i--;
	}
}

void CcgLfrFillPolyView::pFillScan(CDC* pDC)
{
	int x,y;
    CcgLfrFillPolyDoc* pDoc = GetDocument();

	pDC->SetROP2(10);
	for (int i = m_Begin; i < m_End; i += 2) {
		if (pDoc->m_drawMode == 0) {
			pDC->MoveTo(m_Xa[i],   m_Scan);
			pDC->LineTo(m_Xa[i+1], m_Scan);

		} else {
		  y = m_Scan;
		  for (int x = m_Xa[i]; x < m_Xa[i+1]; x++) 
			if (m_patternData[y%20][x%20])
				pDC->SetPixel(x, y, RGB(255,0,0));

		}

	}
}

void CcgLfrFillPolyView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CcgLfrFillPolyDoc *pDoc = GetDocument();
	pDoc->wm_width = cx;
	pDoc->wm_height = cy;
}