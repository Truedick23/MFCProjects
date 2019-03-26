
// cg2018DZx2DTransView.cpp : Ccg2018DZx2DTransView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cg2018DZx2DTrans.h"
#endif

#include <cmath>
#include <vector>
using namespace std;

#include "cg2018DZx2DTransDoc.h"
#include "cg2018DZx2DTransView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

# define N 64
// Ccg2018DZx2DTransView

IMPLEMENT_DYNCREATE(Ccg2018DZx2DTransView, CView)

BEGIN_MESSAGE_MAP(Ccg2018DZx2DTransView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Ccg2018DZx2DTransView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// Ccg2018DZx2DTransView 构造/析构

Ccg2018DZx2DTransView::Ccg2018DZx2DTransView()
{
	// TODO: 在此处添加构造代码
		m_pNumbers = 0;
}

Ccg2018DZx2DTransView::~Ccg2018DZx2DTransView()
{
}

BOOL Ccg2018DZx2DTransView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Ccg2018DZx2DTransView 绘制

void Ccg2018DZx2DTransView::OnDraw(CDC* /*pDC*/)
{
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();
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
 	CalculateMatrix(pDoc->m_polygonMatrix);

	// Trans & Display General Line Space Model
	TransLine(pDoc->P1,pDoc->P2,&pDoc->TP1,&pDoc->TP2,pDoc->m_lineMatrix);
	DisplayLine(pDC, pDoc->TP1,pDoc->TP2, RGB(255,0,0));	

	TransLine(pDoc->LB_P1,pDoc->LB_P2,&pDoc->LB_TP1,&pDoc->LB_TP2,pDoc->m_LB_LineMatrix);
	DisplayLine(pDC, pDoc->LB_TP1,pDoc->LB_TP2, RGB(0,255,0));

	// Cohn-Sutherland Subdivision Line Clip 
	int cx1,cy1,cx2,cy2;                                         
	pDoc->m_lineVisible = FALSE;
	cx1 = pDoc->TP1.x;    cy1 = pDoc->TP1.y;
	cx2 = pDoc->TP2.x;    cy2 = pDoc->TP2.y;

	int lx1, ly1, lx2, ly2;
	pDoc->m_LB_lineVisible = FALSE;
	lx1 = pDoc->LB_TP1.x;  ly1 = pDoc->LB_TP1.y;
	lx2 = pDoc->LB_TP2.x;  ly2 = pDoc->LB_TP2.y;

	if (ClipLine(&cx1, &cy1, &cx2, &cy2)) {           

		pDoc->CP1.x = cx1;    pDoc->CP1.y = cy1;
		pDoc->CP2.x = cx2;    pDoc->CP2.y = cy2;

		DisplayLine(pDC, pDoc->CP1, pDoc->CP2, RGB(0,0, 255));
		pDoc->m_lineVisible = TRUE; 
	} 

	if (Liang_ClipLine(&lx1, &ly1, &lx2, &ly2)) {
		pDoc->LB_CP1.x = lx1;  pDoc->LB_CP1.y = ly1;
		pDoc->LB_CP2.x = lx2;  pDoc->LB_CP2.y = ly2;

		DisplayLine(pDC, pDoc->LB_CP1, pDoc->LB_CP2, RGB(105, 105, 105));
		pDoc->m_LB_lineVisible = TRUE; 
	}

	// Trans & Display General Polygon Space Model
	TransPolygon(pDoc->m_pointNumber, pDoc->m_spPolygon, pDoc->m_transPolygon, pDoc->m_polygonMatrix);
	DisplayPolygon(pDC, pDoc->m_pointNumber, pDoc->m_transPolygon, RGB(255,0,0));
	
	/*TransPolygon(pDoc->m_WA_pointNumber, pDoc->m_WA_spPolygon, pDoc->m_WA_transPolygon, pDoc->m_WA_polygonMatrix);
	DisplayPolygon(pDC, pDoc->m_WA_pointNumber, pDoc->m_WA_transPolygon, RGB(39, 64, 139));*/

	// Sutherland-Hodgman Polygon Clip
	pDoc->m_polygonVisible = FALSE;  

	if (ClipPolygon(pDoc->m_pointNumber, pDoc->m_transPolygon, 
		            &pDoc->m_clipPointNumber, pDoc->m_clipPolygon)) 
	{
		DisplayPolygon(pDC, pDoc->m_clipPointNumber, pDoc->m_clipPolygon, RGB(0,0, 255));
		pDoc->m_polygonVisible = TRUE;
	}

	/*
	pDoc->m_WA_polygonVisible = FALSE;  

	vector<CPoint> set;
	for(int i = 0; i < pDoc->m_WA_pointNumber; i++)
		set.push_back(pDoc->m_WA_transPolygon[i]);

	vector<CPoint> newset;
	if (Weiler_PolygonClip(set, newset)) 
	{
		for(int i = 0; i < pDoc->m_WA_clipPointNumber; i++) {
			pDoc->m_WA_clipPolygon[i] = newset[i];
		}
		DisplayPolygon(pDC, pDoc->m_WA_clipPointNumber, pDoc->m_WA_clipPolygon, RGB(123, 104, 238));
		pDoc->m_WA_polygonVisible = TRUE;
	}
	*/
	pDoc->UpdateAllViews(this);

	// Must remember to release pDC
	ReleaseDC(pDC);
	// TODO: 在此处为本机数据添加绘制代码
	/*
	set.clear();
	newset.clear();*/
}


// Ccg2018DZx2DTransView 打印


void Ccg2018DZx2DTransView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Ccg2018DZx2DTransView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Ccg2018DZx2DTransView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Ccg2018DZx2DTransView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void Ccg2018DZx2DTransView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
	GetCursorPos(&seed);
}

void Ccg2018DZx2DTransView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Ccg2018DZx2DTransView 诊断

#ifdef _DEBUG
void Ccg2018DZx2DTransView::AssertValid() const
{
	CView::AssertValid();
}

void Ccg2018DZx2DTransView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ccg2018DZx2DTransDoc* Ccg2018DZx2DTransView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ccg2018DZx2DTransDoc)));
	return (Ccg2018DZx2DTransDoc*)m_pDocument;
}
#endif //_DEBUG


// Ccg2018DZx2DTransView 消息处理程序


void Ccg2018DZx2DTransView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_wndWidth = cx;
	m_wndHeight = cy;
	// TODO: 在此处添加消息处理程序代码
}

#define DELTAX 10
#define DELTAY 10
#define DELTATHETA 3.1415926/36

void Ccg2018DZx2DTransView::CalculateMatrix(float transMatrix[3][2])
{
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();
	
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

void Ccg2018DZx2DTransView::ScaleMatrix(float Sx, float Sy, float m[3][2])
{
	// Please fill in the right code below lines ...
	for (int i = 0; i < 3; i++) {
		m[i][0] *= Sx;
		m[i][1] *= Sy;
	}
}

void Ccg2018DZx2DTransView::RotateMatrix(float S, float C, float m[3][2])
{
	float temp;
	// Please fill in the right code below lines ...
	for (int i = 0; i < 3; i++) {
		temp = m[i][0];
		m[i][0] = temp * C - m[i][1] * S;
		m[i][1] = temp * S + m[i][1] * C;
	}
}

void Ccg2018DZx2DTransView::TranslateMatrix(float Tx, float Ty, float m[3][2])
{
	// Please fill in the right code below lines ...
	m[2][0] += Tx;
	m[2][1] += Ty;
}

void Ccg2018DZx2DTransView::TransLine(CPoint p1, CPoint p2, CPoint *tp1, CPoint *tp2, float transMatrix[3][2])
{
	// Please fill in the right code below lines ...
	tp1->x = p1.x * transMatrix[0][0] + p1.y * transMatrix[1][0] + transMatrix[2][0];
	tp1->y = p1.x * transMatrix[0][1] + p1.y * transMatrix[1][1] + transMatrix[2][1];
	tp2->x = p2.x * transMatrix[0][0] + p2.y * transMatrix[1][0] + transMatrix[2][0];
	tp2->y = p2.x * transMatrix[0][1] + p2.y * transMatrix[1][1] + transMatrix[2][1];
}

void Ccg2018DZx2DTransView::DisplayLine(CDC* pDC, CPoint p1, CPoint p2, COLORREF rgbColor)
{
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();

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

void Ccg2018DZx2DTransView::TransPolygon(int pointNumber, CPoint spPolygon[N],
	CPoint transPolygon[N], float transMatrix[3][2])
{
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();
	// Please fill in the right code below lines ...	
	for (int i = 0; i < pointNumber; i++) {
		transPolygon[i].x = spPolygon[i].x * transMatrix[0][0] + 
			spPolygon[i].y * transMatrix[1][0] + transMatrix[2][0];
		transPolygon[i].y = spPolygon[i].x * transMatrix[0][1] + 
			spPolygon[i].y * transMatrix[1][1] + transMatrix[2][1];
	}
}

void Ccg2018DZx2DTransView::DisplayPolygon(CDC* pDC, int pointNumber, 
	                                      CPoint transPolygon[N], COLORREF rgbColor)
{
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();
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
	oldPen->DeleteObject();
}

// Cohn-Sutherland Subdivision Line Clip
int Ccg2018DZx2DTransView::ClipLine(int *x1, int *y1, int *x2, int *y2)
{
	
	int visible, m_window[4];
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();
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

int Ccg2018DZx2DTransView::LineVisible(int *x1, int *y1, int *x2, int *y2)
{
	int pcode1,pcode2;

	pcode1 = pCode(x1, y1);
	pcode2 = pCode(x2, y2);

	if (!pcode1 && !pcode2)    return 1;     // Visible
	if ((pcode1 & pcode2) != 0)  return 0;     // Unvisible
	if (pcode1 == 0) {
		float temp;
		temp = *x1;  *x1= *x2;  *x2 = temp;
		temp = *y1;  *y1= *y2;  *y2 = temp;
	}
	return 2;
}

int Ccg2018DZx2DTransView::pCode(int *x, int *y)
{
	int code = 0;
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();

	// Please fill in the right code here ...
	if (*x <= pDoc->m_wndLx)  code = code | 1;
	if (*x >= pDoc->m_wndRx)  code = code | 2;
	if (*y >= pDoc->m_wndRy)  code = code | 4;
	if (*y <= pDoc->m_wndLy)  code = code | 8;
	return code;
}

int Ccg2018DZx2DTransView::LineCross(int x1, int y1, int x2, int y2, int i)
{
	int visible1,visible2;

	visible1 = pVisible(x1, y1, i);
	visible2 = pVisible(x2, y2, i);

	if (visible1 != visible2) return 1;
	else                      return 0;

}

int Ccg2018DZx2DTransView::pVisible(int x, int y, int i)
{
	int visible = 0;
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();

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
int Ccg2018DZx2DTransView::ClipPolygon(int n, CPoint *tPoints, int *cn, CPoint *cPoints)
{
	int Nin,Nout,ix,iy,Sx,Sy;
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();

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

void Ccg2018DZx2DTransView::interSect(int Sx, int  Sy, int Px, int Py,
	                                 int  i, int *ix, int *iy)
{
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();

	// Please fill in the right code below lines ...
	switch (i) {
	case 0: // Left
		*ix = pDoc->m_wndLx;
		*iy =  (int) ((float)((*ix - Px)*(Sy - Py)/(Sx - Px) + Py + 0.5));
		break;
	case 1: // Right
		*ix = pDoc->m_wndRx;
		*iy = (int) ((float)((*ix - Px)*(Sy - Py)/(Sx - Px) + Py + 0.5));
		break;
	case 2: // Top
		*iy = pDoc->m_wndRy;
		*ix = (int) ((float)((*iy - Py)*(Sx - Px)/(Sy - Py) + Px + 0.5));
		break;
	case 3: // Bottom
		*iy = pDoc->m_wndLy;
		*ix = (int) ((float)((*iy - Py)*(Sx - Px)/(Sy - Py) + Px + 0.5));
		break;
	}
}

void Ccg2018DZx2DTransView::outPut(int x, int y, int *cn, CPoint *cPoints)
{
	cPoints[*cn].x = x;
	cPoints[*cn].y = y;
	(*cn)++;
}


double Ccg2018DZx2DTransView::Calculate_p(int x1, int y1, int x2, int y2, int type) 
{
	if(type == 0) 
		return -(x2 - x1);
	if(type == 1) 
		return x2 - x1;
	if(type == 2)
		return  -(y2 - y1);
	if(type == 3)
		return (y2 - y1);
}

double Ccg2018DZx2DTransView::Calculate_q(int x1, int y1, int x2, int y2, int type)
{
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();
	if(type == 0)
		return (x1 - pDoc->m_wndLx);
	if(type == 1)
		return (pDoc->m_wndRx - x1);
	if(type == 2)
		return (y1 - pDoc->m_wndLy);
	if(type == 3)
		return (pDoc->m_wndRy - y1);
}

bool Ccg2018DZx2DTransView::Liang_test(double p, double q, double &u1, double &u2)
{
	double u = q / p;
	if(p < 0) {
		if(u > u2)
			return false;
		else if(u > u1) {
			u1 = u;
			return true;
		}
	}
	else if (p > 0) {
		if(u < u1)
			return false;
		else if(u < u2) {
			u2 = u;
			return true;
		}
	}
	else if(q < 0)
		return false;
}

bool Ccg2018DZx2DTransView::Liang_ClipLine(int *x1, int *y1, int *x2, int *y2)
{
	double u1 = 0, u2 = 1, u = 0;
	int dx = *x2 - *x1;
	int dy = *y2 - *y1;
	vector<double> pk;
	vector<double> qk;
	for(int i = 0; i < 4; i++) {
		double temp;
		temp = Calculate_p(*x1, *y1, *x2, *y2, i);
		pk.push_back(temp);
		temp = Calculate_q(*x1, *y1, *x2, *y2, i);
		qk.push_back(temp);
	}
	if (Liang_test(pk[0], qk[0], u1, u2)) {
		if (Liang_test(pk[1], qk[1], u1, u2)) {
			if (Liang_test(pk[2], qk[2], u1, u2)){
				if (Liang_test(pk[3], qk[3], u1, u2)) {
					if(u2 < 1) {
						*x2 = *x1 + u2 * dx;
						*y2 = *y1 + u2 * dy;
					}
					if(u1 > 0) {
						*x1 = *x1 + u1 * dx;
						*y1 = *y1 + u1 * dy;
					}
					return 1;
				}

			}
		}
	}
	return 0;
}


void Ccg2018DZx2DTransView::Weiler_ParallelClip(CPoint p1, CPoint p2, vector<CPoint> &set, const int mode)
{
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();
	if(p1.x == p2.x) {
		switch(mode) {
		case 0:
			if(p1.x >= pDoc->m_wndLx)
				set.push_back(p2);
			break;
		case 1:
			if(p1.x <= pDoc->m_wndRx)
				set.push_back(p2);
			break;
		case 2:
			if((p1.y >= pDoc->m_wndLy) && (p2.y >= pDoc->m_wndLy))
				set.push_back(p2);
			else if((p1.y >= pDoc->m_wndLy) && (p2.y < pDoc->m_wndLy)) {
				CPoint newP(p1.x, pDoc->m_wndLy);
				set.push_back(newP);
			}
			else if((p1.y < pDoc->m_wndLy) && (p2.y >= pDoc->m_wndLy)) {
				CPoint newP(p1.x, pDoc->m_wndLy);
				set.push_back(newP);
				set.push_back(p2);
			}
			break;
		case 3:
			if((p1.y <= pDoc->m_wndRy) && (p2.y <= pDoc->m_wndRy))
				set.push_back(p2);
			else if((p1.y > pDoc->m_wndRy) && (p2.y <= pDoc->m_wndRy)) {
				CPoint newP(p1.x, pDoc->m_wndRy);
				set.push_back(newP);
				set.push_back(p2);
			}
			else if((p1.y <= pDoc->m_wndRy) && (p2.y > pDoc->m_wndRy)) {
				CPoint newP(p1.x, pDoc->m_wndRy);
				set.push_back(newP);
			}
			break;
		}
	}

	else if(p1.y == p2.y) {
		switch(mode) {
		case 0:
			if((p1.x >= pDoc->m_wndLx) && (p2.x >= pDoc->m_wndLx))
				set.push_back(p2);
			else if((p1.x < pDoc->m_wndLx) && (p2.x >= pDoc->m_wndLx)) {
				CPoint newP(pDoc->m_wndLx, p1.y);
				set.push_back(newP);
				set.push_back(p2);
			}
			else if((p1.x >= pDoc->m_wndLx) && (p2.x <  pDoc->m_wndLx)) {
				CPoint newP(pDoc->m_wndLx, p1.y);
				set.push_back(p1);
				set.push_back(newP);
			}
			break;
		case 1:
			if((p1.x <= pDoc->m_wndRx) && (p2.x <= pDoc->m_wndRx))
				set.push_back(p2);
			else if((p1.x <= pDoc->m_wndRx) && (p2.y > pDoc->m_wndRx)) {
				CPoint newP(pDoc->m_wndRx, p1.y);
				set.push_back(p1);
				set.push_back(newP);
			}
			else if((p1.x > pDoc->m_wndRx) && (p2.x <= pDoc->m_wndRx)) {
				CPoint newP(pDoc->m_wndRx, p1.y);
				set.push_back(newP);
				set.push_back(p2);
			}
			break;
		case 2:
			if(p1.y >= pDoc->m_wndLy)
				set.push_back(p2);
			break;
		case 3:
			if(p1.y <= pDoc->m_wndRx)
				set.push_back(p2);
			break;
		}
	}

	
}
void Ccg2018DZx2DTransView::Weiler_PolygonEdgeClip(vector<CPoint> &set, vector<CPoint> &newset, const int mode) 
{
	newset.clear();
	for(int i = 0; i < set.size(); i++) {
		CPoint pl = set[i];
		if(i == set.size() - 1)
			break;
		CPoint pr = set[i + 1];
		if(pVisible(pl.x, pl.y, mode)) {
			if(pVisible(pr.x, pr.y, mode)) 
				newset.push_back(pr);
			else {
				int ix, iy;
				interSect(pl.x, pl.y, pr.x, pr.y, mode, &ix, &iy);
				CPoint newP(ix, iy);
				newset.push_back(newP);
			}
		}
		else if(!pVisible(pl.x, pl.y ,mode)) {
			if(pVisible(pr.x, pr.y ,mode)) {
				int ix, iy ;
				interSect(pl.x, pl.y, pr.x, pr.y, mode, &ix, &iy);
				CPoint newP(ix, iy);

				newset.push_back(newP);
				newset.push_back(pr);
			}
		}
	}
	if(set[set.size()-1].x == set[0].x || set[set.size()-1].y == set[0].y) 
		Weiler_ParallelClip(set[set.size()-1], set[0], newset, mode);

	else if(pVisible(set[set.size()-1].x, set[set.size()-1].y, mode)) {
		if(pVisible(set[0].x, set[0].y, mode))
			newset.push_back(set[0]);
		else if(!pVisible(set[0].x, set[0].y, mode)) {
			int ix, iy;
			interSect(set[set.size()-1].x, set[set.size()-1].y, set[0].x, set[0].y, mode, &ix, &iy);
			CPoint newP(ix, iy);
			newset.push_back(newP);
		}		
	}
	else if(!pVisible(set[set.size()-1].x, set[set.size()-1].y, mode)) {
		if(pVisible(set[0].x, set[0].y, mode)) {
			int ix, iy;
			interSect(set[set.size()-1].x, set[set.size()-1].y, set[0].x, set[0].y, mode, &ix, &iy);
			CPoint newP(ix, iy);
			newset.push_back(newP);
			newset.push_back(set[0]);
		}
	}
}

bool Ccg2018DZx2DTransView::Weiler_PolygonClip(vector<CPoint> &set, vector<CPoint> &set_result)
{
	vector<CPoint> set_L, set_R, set_B;
	Weiler_PolygonEdgeClip(set, set_L, 0);
	Weiler_PolygonEdgeClip(set_L, set_R, 1);
	Weiler_PolygonEdgeClip(set_R, set_B, 2);
	Weiler_PolygonEdgeClip(set_B, set_result, 3);

	return 1;
}

void Ccg2018DZx2DTransView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_pNumbers < N) {
		m_pAccord[m_pNumbers] = point;
		m_pNumbers++;

		m_mousePoint = point;
	}
	CView::OnLButtonDown(nFlags, point);
	CView::OnLButtonDown(nFlags, point);
}


void Ccg2018DZx2DTransView::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnNcLButtonDblClk(nHitTest, point);
}


void Ccg2018DZx2DTransView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();
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


void Ccg2018DZx2DTransView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Ccg2018DZx2DTransDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC* m_pDC = GetDC();
	m_pDC->MoveTo(m_pAccord[m_pNumbers-1]);
	m_pDC->LineTo(m_pAccord[0]);

	m_pAccord[m_pNumbers-1] = m_pAccord[0];
	m_pNumbers++;

	pDoc->m_pointNumber = m_pNumbers;
	pDoc->m_WA_pointNumber = m_pNumbers;
	pDoc->m_WA_clipPointNumber = m_pNumbers;
	pDoc->m_clipPointNumber = m_pNumbers;

	for(int i = 0; i < m_pNumbers; i++) 
	{
		pDoc->m_spPolygon[i] = m_pAccord[i];
	}
	m_pNumbers = 0;
	CView::OnLButtonDblClk(nFlags, point);
}
