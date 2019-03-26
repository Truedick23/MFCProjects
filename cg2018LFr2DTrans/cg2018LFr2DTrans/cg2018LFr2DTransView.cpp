
// cg2018LFr2DTransView.cpp : Ccg2018LFr2DTransView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "cg2018LFr2DTrans.h"
#endif

#include<cmath>
#include "cg2018LFr2DTransDoc.h"
#include "cg2018LFr2DTransView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ccg2018LFr2DTransView

IMPLEMENT_DYNCREATE(Ccg2018LFr2DTransView, CView)

BEGIN_MESSAGE_MAP(Ccg2018LFr2DTransView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Ccg2018LFr2DTransView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Ccg2018LFr2DTransView ����/����

Ccg2018LFr2DTransView::Ccg2018LFr2DTransView()
{
	// TODO: �ڴ˴���ӹ������

}

Ccg2018LFr2DTransView::~Ccg2018LFr2DTransView()
{
}

BOOL Ccg2018LFr2DTransView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// Ccg2018LFr2DTransView ����

void Ccg2018LFr2DTransView::OnDraw(CDC* /*pDC*/)
{
	Ccg2018LFr2DTransDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC* pDC = GetDC();

	pDC->MoveTo(0, m_wndHeight/2);
	pDC->LineTo(m_wndWidth, m_wndHeight/2);
	pDC->MoveTo(m_wndWidth/2, 0);
	pDC->LineTo(m_wndWidth/2, m_wndHeight);

	CPen newPen;
	CPen *oldPen;

	newPen.CreatePen(PS_SOLID, 1, RGB(255,0,255));
	oldPen = (CPen *)pDC->SelectObject(&newPen);

	pDC->MoveTo(m_wndWidth/2+pDoc->m_wndLx, m_wndHeight/2-pDoc->m_wndLy);
	pDC->LineTo(m_wndWidth/2+pDoc->m_wndLx, m_wndHeight/2-pDoc->m_wndRy);
	pDC->LineTo(m_wndWidth/2+pDoc->m_wndRx, m_wndHeight/2-pDoc->m_wndRy);
	pDC->LineTo(m_wndWidth/2+pDoc->m_wndRx, m_wndHeight/2-pDoc->m_wndLy);
	pDC->LineTo(m_wndWidth/2+pDoc->m_wndLx, m_wndHeight/2-pDoc->m_wndLy);

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();

    // m_transSelect = 2 control window, has been processed in CCgTransSelect class.
	if (pDoc->m_transSelect == 0) CalculateMatrix(pDoc->m_lineMatrix);
 	else if (pDoc->m_transSelect == 1) CalculateMatrix(pDoc->m_polygonMatrix);
 	else if (pDoc->m_transSelect == 3) CalculateMatrix(pDoc->m_LB_LineMatrix);
 	else if (pDoc->m_transSelect == 4) CalculateMatrix(pDoc->m_WA_polygonMatrix);

	// Trans & Display General Line Space Model
	TransLine(pDoc->P1,pDoc->P2,&pDoc->TP1,&pDoc->TP2,pDoc->m_lineMatrix);
	DisplayLine(pDC, pDoc->TP1,pDoc->TP2, RGB(255,0,0));	

	// Cohn-Sutherland Subdivision Line Clip 
	int cx1,cy1,cx2,cy2;                                         
	pDoc->m_lineVisible = FALSE;
	cx1 = pDoc->TP1.x;    cy1 = pDoc->TP1.y;
	cx2 = pDoc->TP2.x;    cy2 = pDoc->TP2.y;

	if (ClipLine(&cx1, &cy1, &cx2, &cy2)) {           

		pDoc->CP1.x = cx1;    pDoc->CP1.y = cy1;
		pDoc->CP2.x = cx2;    pDoc->CP2.y = cy2;

		DisplayLine(pDC, pDoc->CP1, pDoc->CP2, RGB(0,0, 255));
		pDoc->m_lineVisible = TRUE; 
	} 

	// Trans & Display General Polygon Space Model
	TransPolygon(pDoc->m_pointNumber, pDoc->m_spPolygon, pDoc->m_transPolygon, pDoc->m_polygonMatrix);
	DisplayPolygon(pDC, pDoc->m_pointNumber, pDoc->m_transPolygon, RGB(255,0,0));

	// Sutherland-Hodgman Polygon Clip
	pDoc->m_polygonVisible = FALSE;  

	if (ClipPolygon(pDoc->m_pointNumber, pDoc->m_transPolygon, 
		            &pDoc->m_clipPointNumber, pDoc->m_clipPolygon)) 
	{
		DisplayPolygon(pDC, pDoc->m_clipPointNumber, pDoc->m_clipPolygon, RGB(0,0, 255));
		pDoc->m_polygonVisible = TRUE;
	}

	pDoc->UpdateAllViews(this);

	// Must remember to release pDC
	ReleaseDC(pDC);
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// Ccg2018LFr2DTransView ��ӡ


void Ccg2018LFr2DTransView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Ccg2018LFr2DTransView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void Ccg2018LFr2DTransView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void Ccg2018LFr2DTransView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void Ccg2018LFr2DTransView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Ccg2018LFr2DTransView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Ccg2018LFr2DTransView ���

#ifdef _DEBUG
void Ccg2018LFr2DTransView::AssertValid() const
{
	CView::AssertValid();
}

void Ccg2018LFr2DTransView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ccg2018LFr2DTransDoc* Ccg2018LFr2DTransView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ccg2018LFr2DTransDoc)));
	return (Ccg2018LFr2DTransDoc*)m_pDocument;
}
#endif //_DEBUG

void Ccg2018LFr2DTransView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_wndWidth = cx;
	m_wndHeight = cy;
	// TODO: �ڴ˴������Ϣ����������
}

#define DELTAX 10
#define DELTAY 10
#define DELTATHETA 3.1415926/36

void Ccg2018LFr2DTransView::CalculateMatrix(float transMatrix[3][2])
{
	Ccg2018LFr2DTransDoc* pDoc = GetDocument();
	
	switch (pDoc->m_transDir) {
	case 0: // -X
		switch (pDoc->m_transMode)	{
		case 0: // Move
			TranslateMatrix(-DELTAX, 0, transMatrix);
			break;
		case 1: // rotate
			RotateMatrix(-sin(DELTATHETA), cos(DELTATHETA), transMatrix);
			break;
		case 2: // Scale
			ScaleMatrix(0.8, 0.8, transMatrix);
			break;
		}
		break;
	case 1: // +X
		switch (pDoc->m_transMode)	{
		case 0: // Move
			TranslateMatrix(DELTAX, 0, transMatrix);
			break;
		case 1: // rotate
			RotateMatrix(sin(DELTATHETA), cos(DELTATHETA), transMatrix);
			break;
		case 2: // Scale
			ScaleMatrix(1.2, 1.2, transMatrix);
			break;
		}
		break;
	case 2: // -Y
		switch (pDoc->m_transMode)	{
		case 0: // Move
			TranslateMatrix(0, -DELTAY, transMatrix);
			break;
		case 1: // rotate
			RotateMatrix(-sin(DELTATHETA), cos(DELTATHETA), transMatrix);
			break;
		case 2: // Scale
			ScaleMatrix(0.8, 0.8, transMatrix);
			break;
		}
		break;
	case 3: // +Y
		switch (pDoc->m_transMode)	{
		case 0: // Move
			TranslateMatrix(0, DELTAY, transMatrix);
			break;
		case 1: // rotate
			RotateMatrix(sin(DELTATHETA), cos(DELTATHETA), transMatrix);
			break;
		case 2: // Scale
			ScaleMatrix(1.2, 1.2, transMatrix);
			break;
		}
		break;
	}
	
}

void Ccg2018LFr2DTransView::ScaleMatrix(float Sx, float Sy, float m[3][2])
{
	// Please fill in the right code below lines ...
	
	for (int i = 0; i < 3; i++) {
		m[i][0] *= Sx;
		m[i][1] *= Sy;
	}
}

void Ccg2018LFr2DTransView::RotateMatrix(float S, float C, float m[3][2])
{
	float temp;

	// Please fill in the right code below lines ...
	
	for (int i = 0; i < 3; i++) {
		temp = m[i][0];
		m[i][0] = temp * C - m[i][1] * S;
		m[i][1] = temp * S + m[i][1] * C;
	}
}

void Ccg2018LFr2DTransView::TranslateMatrix(float Tx, float Ty, float m[3][2])
{
	// Please fill in the right code below lines ...
	m[2][0] += Tx;
	m[2][1] += Ty;
}

void Ccg2018LFr2DTransView::TransLine(CPoint p1, CPoint p2, CPoint *tp1, CPoint *tp2, float transMatrix[3][2])
{
	// Please fill in the right code below lines ...
	
	tp1->x = p1.x * transMatrix[0][0] + p1.y * transMatrix[1][0] + transMatrix[2][0];
	tp1->y = p1.x * transMatrix[0][1] + p1.y * transMatrix[1][1] + transMatrix[2][1];
	tp2->x = p2.x * transMatrix[0][0] + p2.y * transMatrix[1][0] + transMatrix[2][0];
	tp2->y = p2.x * transMatrix[0][1] + p2.y * transMatrix[1][1] + transMatrix[2][1];
	
}

void Ccg2018LFr2DTransView::DisplayLine(CDC* pDC, CPoint p1, CPoint p2, COLORREF rgbColor)
{
	Ccg2018LFr2DTransDoc* pDoc = GetDocument();

	CPen newPen;
	CPen *oldPen;
	CPoint VP1,VP2;

	newPen.CreatePen(PS_SOLID, 1, rgbColor);
	oldPen = (CPen *)pDC->SelectObject(&newPen);

	VP1.x = m_wndWidth/2 + p1.x;
	VP1.y = m_wndHeight/2 - p1.y;
	VP2.x = m_wndWidth/2 + p2.x;
	VP2.y = m_wndHeight/2 - p2.y;

	pDC->MoveTo(VP1);
	pDC->LineTo(VP2);

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();
}

void Ccg2018LFr2DTransView::TransPolygon(int pointNumber, CPoint spPolygon[N],
	CPoint transPolygon[N], float transMatrix[3][2])
{
	Ccg2018LFr2DTransDoc* pDoc = GetDocument();

	// Please fill in the right code below lines ...
	
	for (int i = 0; i < pointNumber; i++) {

		transPolygon[i].x = spPolygon[i].x * transMatrix[0][0] + 
			spPolygon[i].y * transMatrix[1][0] + transMatrix[2][0];
		transPolygon[i].y = spPolygon[i].x * transMatrix[0][1] + 
			spPolygon[i].y * transMatrix[1][1] + transMatrix[2][1];

	}

}

void Ccg2018LFr2DTransView::DisplayPolygon(CDC* pDC, int pointNumber, 
	                                      CPoint transPolygon[N], COLORREF rgbColor)
{
	Ccg2018LFr2DTransDoc* pDoc = GetDocument();

	CPen newPen;
	CPen *oldPen;
	CPoint VPolygon[N];

	newPen.CreatePen(PS_SOLID, 1, rgbColor);
	oldPen = (CPen *)pDC->SelectObject(&newPen);

	for (int i = 0; i < pointNumber; i++) {
		VPolygon[i].x = m_wndWidth/2 + transPolygon[i].x;
		VPolygon[i].y = m_wndHeight/2 - transPolygon[i].y;
	}

	pDC->MoveTo(VPolygon[0]);
	for (int i = 1; i < pointNumber; i++) pDC->LineTo(VPolygon[i]);

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();
}

// Cohn-Sutherland Subdivision Line Clip
int  Ccg2018LFr2DTransView::ClipLine(int *x1, int *y1, int *x2, int *y2)
{
	
	int visible, m_window[4];
	Ccg2018LFr2DTransDoc* pDoc = GetDocument();

	m_window[0] = pDoc->m_wndLx;    m_window[1] = pDoc->m_wndRx;
	m_window[2] = pDoc->m_wndRy;    m_window[3] = pDoc->m_wndLy;
	for (int i = 0; i < 4; i++) { // Along the WIN Border
		visible = LineVisible(x1, y1, x2, y2);
		if (visible == 1) return 1;         // Total Visible
		if (visible == 0) return 0;         // Total Unvisible

		if (LineCross(*x1, *y1, *x2, *y2, i)) {

			// Please fill in the right code below lines ...
			if (i < 2 && *x2-*x1) {                       // Left , Right
				float m = (float)(*y2-*y1)/(*x2-*x1);
				float iy = m * (m_window[i] - *x1) + *y1;

			if (pVisible(*x1,*y1,i) == 0) {
				*x1 = m_window[i];
				*y1 = iy;
			} 
			else if (pVisible(*x2,*y2,i) == 0) {
				*x2 = m_window[i];
				*y2 = iy;
			}
			} else if (*y2-*y1) {                         // Top    Bottom
				float m = (float)(*x2-*x1)/(*y2-*y1);
				float ix = m * (m_window[i] - *y1) + *x1;
				
			if (pVisible(*x1,*y1,i) == 0) {
				*x1 = ix;
				*y1 = m_window[i];
			} 
			else if (pVisible(*x2,*y2,i) == 0) {
				*x2 = ix;
				*y2 = m_window[i];
			}
			}
		}
	}
	return 1;
}

int Ccg2018LFr2DTransView::LineVisible(int *x1, int *y1, int *x2, int *y2)
{
	int pcode1,pcode2;

	pcode1 = pCode(x1, y1);
	pcode2 = pCode(x2, y2);

	if (!pcode1 && !pcode2)    return 1;     // Visible
	if ((pcode1&pcode2) != 0)  return 0;     // Unvisible
	if (pcode1 == 0) {
		float temp;
		temp = *x1;  *x1= *x2;  *x2 = temp;
		temp = *y1;  *y1= *y2;  *y2 = temp;
	}
	return 2;
}

int Ccg2018LFr2DTransView::pCode(int *x, int *y)
{
	int code = 0;
	Ccg2018LFr2DTransDoc* pDoc = GetDocument();

	// Please fill in the right code here ...
	if (*x <= pDoc->m_wndLx)  code = code | 1;
	if (*x >= pDoc->m_wndRx)  code = code | 2;
	if (*y >= pDoc->m_wndRy)  code = code | 4;
	if (*y <= pDoc->m_wndLy)  code = code | 8;
	return code;
	
}

int Ccg2018LFr2DTransView::LineCross(int x1, int y1, int x2, int y2, int i)
{
	int visible1,visible2;

	visible1 = pVisible(x1, y1, i);
	visible2 = pVisible(x2, y2, i);

	if (visible1 != visible2) return 1;
	else                      return 0;

}

int Ccg2018LFr2DTransView::pVisible(int x, int y, int i)
{
	int visible = 0;
	Ccg2018LFr2DTransDoc* pDoc = GetDocument();

	switch (i) {
	  case 0: // Left
		if (x >= pDoc->m_wndLx)  visible = 1; break;
	  case 1: // Right
		if (x <= pDoc->m_wndRx)  visible = 1; break;
	  case 2: // Top
		if (y <= pDoc->m_wndRy)  visible = 1; break;
	  case 3: // Bottom
		if (y >= pDoc->m_wndLy)  visible = 1; break;
	}
	return visible;
}

// Sutherland-Hodgman Polygon Clip
int Ccg2018LFr2DTransView::ClipPolygon(int n, CPoint *tPoints, int *cn, CPoint *cPoints)
{
	int Nin,Nout,ix,iy,Sx,Sy;
	Ccg2018LFr2DTransDoc* pDoc = GetDocument();

	Nin = n;
	for (int i = 0; i < 4; i++) {  // Along the window border
		*cn = 0;
		for (int j = 0; j < Nin; j++) {  // Scan polygon every point and line.
			if (j > 0) {
				if (LineCross(Sx, Sy, tPoints[j].x, tPoints[j].y, i)) {
					interSect(Sx, Sy, tPoints[j].x, tPoints[j].y, i, &ix, &iy);
					outPut(ix, iy, cn, cPoints);
				}
			}
			Sx = tPoints[j].x;
			Sy = tPoints[j].y;
			if (pVisible(Sx, Sy, i)) outPut(Sx, Sy, cn, cPoints);
		}

		Nin = *cn;
		if (*cn == 0) return 0;
		for (int j = 0; j < Nin; j++) {	
			tPoints[j].x = cPoints[j].x; 
			tPoints[j].y = cPoints[j].y; 
		}

		if (cPoints[0].x != cPoints[Nin-1].x || 
			cPoints[0].y != cPoints[Nin-1].y) {

				tPoints[Nin].x = cPoints[Nin].x = cPoints[0].x; 
				tPoints[Nin].y = cPoints[Nin].y = cPoints[0].y; 

				Nin++; 
				*cn = Nin;
		}
	}
	return 1;
}

void Ccg2018LFr2DTransView::interSect(int Sx, int  Sy, int Px, int Py,
	                                 int  i, int *ix, int *iy)
{
	Ccg2018LFr2DTransDoc* pDoc = GetDocument();

	// Please fill in the right code below lines ...
	switch (i) {
	case 0: // Left
		*ix = pDoc->m_wndLx;
		*iy = (*ix - Px)*(Sy - Py)/(Sx - Px) + Py + 0.5;
		break;
	case 1: // Right
		*ix = pDoc->m_wndRx;
		*iy = (*ix - Px)*(Sy - Py)/(Sx - Px) + Py;
		break;
	case 2: // Top
		*iy = pDoc->m_wndRy;
		*ix = (*iy - Py)*(Sx - Px)/(Sy - Py) + Px;
		break;
	case 3: // Bottom
		*iy = pDoc->m_wndLy;
		*ix = (*iy - Py)*(Sx - Px)/(Sy - Py) + Px;
		break;
	}
}

void Ccg2018LFr2DTransView::outPut(int x, int y, int *cn, CPoint *cPoints)
{
	cPoints[*cn].x = x;
	cPoints[*cn].y = y;
	(*cn)++;
}
// Ccg2018LFr2DTransView ��Ϣ�������
