
// cgDzxDrawLineView.cpp : CcgDzxDrawLineView 类的实现
//

#include "stdafx.h"
#include <math.h>
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cgDzxDrawLine.h"
#endif

#include "cgDzxDrawLineDoc.h"
#include "cgDzxDrawLineView.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Pi 3.1415926

// CcgDzxDrawLineView

IMPLEMENT_DYNCREATE(CcgDzxDrawLineView, CView)

BEGIN_MESSAGE_MAP(CcgDzxDrawLineView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CcgDzxDrawLineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CcgDzxDrawLineView 构造/析构

CcgDzxDrawLineView::CcgDzxDrawLineView()
{
	// TODO: 在此处添加构造代码

}

CcgDzxDrawLineView::~CcgDzxDrawLineView()
{
}

BOOL CcgDzxDrawLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CcgDzxDrawLineView 绘制

void CcgDzxDrawLineView::OnDraw(CDC* /*pDC*/)
{
	CcgDzxDrawLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CDC* pDC = GetDC();
	pDC->MoveTo(0, pDoc->wm_height/2);
	pDC->LineTo(pDoc->wm_width, pDoc->wm_height/2);
	pDC->MoveTo(pDoc->wm_width/2, 0);
	pDC->LineTo(pDoc->wm_width/2, pDoc->wm_height);

	CRect rect;
	GetClientRect(&rect);
	CPoint point(pDoc->wm_width/2, pDoc->wm_height/2);
	pDC->DPtoLP(&point);
	pDC->SetWindowOrg(-point.x, -point.y);
	
	//pDC->SetWindowOrg(pDoc->wm_width/2, pDoc->wm_height/2);

	if(pDoc->m_displayMode == 0) {
		double smooth = 0, error = 0;
		CcgDzxDrawLineDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
			if (!pDoc)
		return;
		long t1 = GetTickCount();
		for(int i = 0; i < 50; i++) {
			DDAline(0, 0, 250, 70, error, smooth, pDC);
			DDAline(0, 0,  70, 250, error, smooth, pDC);
			DDAline(0, 0, -250,  70, error, smooth, pDC);
			DDAline(0, 0,  -70, 250, error, smooth, pDC);
			DDAline(0, 0, 250,  -70, error, smooth, pDC);
			DDAline(0, 0,  70, -250, error, smooth, pDC);
			DDAline(0, 0, -250, -70, error, smooth, pDC);
			DDAline(0, 0,  -70, -250, error, smooth, pDC);
		}
		long t2 = GetTickCount();
		pDoc->DDALineSmooth = smooth;
		pDoc->DDALineAverageError = error / 50;
		pDoc->DDALineTime = t2 - t1;
		pDoc->DDAdrawed = true;
		UpdateData(FALSE);
		ReleaseDC(pDC);
	}

	else if (pDoc->m_displayMode == 1) {
		double smooth = 0, error = 0;
		CcgDzxDrawLineDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
			if (!pDoc)
		return;
		long t1 = GetTickCount();
		for(int i = 0; i < 50; i++) {
			Bline(0, 0, 250,  70, error, smooth, pDC);
			Bline(0, 0,  70, 250, error, smooth, pDC);
			Bline(0, 0, -250,  70, error, smooth, pDC);
			Bline(0, 0, -70, 250 , error, smooth, pDC);
			Bline(0, 0, 250,  -70, error, smooth, pDC);
			Bline(0, 0,  70, -250 , error, smooth, pDC);
			Bline(0, 0, -250,  -70, error, smooth, pDC);
			Bline(0, 0, -70, -250 , error, smooth, pDC);
		}
		long t2 = GetTickCount();
		pDoc->BLineAverageError = error / 50;
		pDoc->BLineSmooth = smooth;
		pDoc->BLineTime = t2 - t1;
		pDoc->BLineDrawed = true;
		UpdateData(FALSE);
		ReleaseDC(pDC);
	} 
	else if (pDoc->m_displayMode == 2) {
		double smooth = 0;
		CcgDzxDrawLineDoc* pDoc = GetDocument();
		long t1 = GetTickCount();
		for(int i = 0; i < 50; i++) {
			MidPline(0, 0, 250,  70, smooth, pDC);
			MidPline(0, 0,  70, 250, smooth, pDC);
			MidPline(0, 0, -250, 70, smooth, pDC);
			MidPline(0, 0, -70, 250, smooth, pDC);
			MidPline(0, 0, 250,  -70, smooth, pDC);
			MidPline(0, 0,  70, -250 , smooth, pDC);
			MidPline(0, 0, -250,  -70, smooth, pDC);
			MidPline(0, 0, -70, -250 , smooth, pDC);
		}
		long t2 = GetTickCount();

		pDoc->MidpointLineSmooth = smooth;
		pDoc->MidPointTime = t2 - t1;
		pDoc->MidPointDrawed = true;
		UpdateData(FALSE);
		ReleaseDC(pDC);
	}
	else if (pDoc->m_displayMode == 3) {
		CcgDzxDrawLineDoc* pDoc = GetDocument();
		BresenhamArc(30, 330, 100, RGB(205, 104, 57), pDC);
		BresenhamArc(60, 150, 80, RGB(138, 43, 226), pDC);
		BresenhamArc(90, 240, 135, RGB(255, 99, 71), pDC);
		ReleaseDC(pDC);
	}
	else {

	}
	ReleaseDC(pDC);
}


// CcgDzxDrawLineView 打印


void CcgDzxDrawLineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CcgDzxDrawLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CcgDzxDrawLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CcgDzxDrawLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CcgDzxDrawLineView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CcgDzxDrawLineView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CcgDzxDrawLineView 诊断

#ifdef _DEBUG
void CcgDzxDrawLineView::AssertValid() const
{
	CView::AssertValid();
}

void CcgDzxDrawLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgDzxDrawLineDoc* CcgDzxDrawLineView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgDzxDrawLineDoc)));
	return (CcgDzxDrawLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CcgDzxDrawLineView 消息处理程序


void CcgDzxDrawLineView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CcgDzxDrawLineDoc *pDoc = GetDocument();
	pDoc->wm_width = cx;
	pDoc->wm_height = cy;
}

void CcgDzxDrawLineView::DDAline(int x1, int y1, int x2, int y2, double &error, double &smooth, CDC *pdc) {
	CcgDzxDrawLineDoc* pDoc = GetDocument();
	double steps;
	double x, y, Dx, Dy, e, k, b;
	k = (float)(y2 - y1) / (x2 - x1);
	b = y1 - k * x1;
	Dx = x2 - x1;
	Dy = y2 - y1;

	steps = (abs(Dx) > abs(Dy))? abs(Dx): abs(Dy);
	Dx /= steps;
	Dy /= steps;
	x = x1 + 0.5; y = y1 + 0.5;
	for(int i = 0; i < steps + 1; i++) {
		double xp = (y - y1 + x / k + k * x1) / (k + 1 / k);
		double yp = -1 / k * (xp - x) + y;
		smooth += sqrtf((x - xp) * (x - xp) + (y - yp) * (y - yp));
		pdc->SetPixel((int)(x+0.5), (int)(y+0.5), RGB(46, 139, 87));
		x += Dx;
		y += Dy;
	}
	smooth /= steps;
	error += sqrtf((float)(x - x2)*(float)(x - x2) + (float)(y - y2)* (float)(y - y2));
}

void CcgDzxDrawLineView::Bline(int x1, int y1, int x2, int y2, double &error, double &smooth, CDC *pdc) {
	CcgDzxDrawLineDoc* pDoc = GetDocument();
	int  x, y, e;
	double k;
	int dx, dy, xSign, ySign, interchange;
	dx = abs(x2 - x1); dy = abs(y2 - y1);
	k = (y2 - y1) / (x2 - x1);
	xSign = x2 > x1 ? 1: -1;
	ySign = y2 > y1? 1: -1;
	if(dx < dy) {
		int temp = dx;
		dx = dy;
		dy = temp;
		interchange = 1;
	}
	else
		interchange = 0;
	e = 2 * dy - dx;
	x = x1; y = y1;
	
	k = (float)(y2 - y1) / (float)(x2 - x1);
	for(int i = 0; i <= dx; i++) {
		double xp = (y - y1 + x / k + k * x1) / (k + 1 / k);
		double yp = -1 / k * (xp - x) + y;
		smooth += sqrtf((x - xp) * (x - xp) + (y - yp) * (y - yp));
		pdc->SetPixel((int)(x+0.5), (int)(y+0.5), RGB(178, 34, 34));
		if(e >= 0) {
			e = e - 2 * dx;
			if(interchange)
				x += xSign;
			else
				y += ySign;
		}
		e = e + 2 * dy;
		if(interchange)
			y = y + ySign;
		else
			x = x + xSign;
	}
	smooth /= dx;
	error += sqrtf((x - x2)*(x - x2) + (y - y2)*(y - y2));
}

void CcgDzxDrawLineView::MidPline(int x1, int y1, int x2, int y2, double &smooth, CDC *pdc) {
	CcgDzxDrawLineDoc* pDoc = GetDocument();
	double count = 0;
	double k = (float)(y2 - y1) / (float)(x2 - x1);
	double b = y1 - k * x1;
    if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {
		int x = (int)(x1 + x2) / 2;
		int y = (int)(y1 + y2) / 2;
		double xp = (y - y1 + x / k + k * x1) / (k + 1 / k);
		double yp = -1 / k * (xp - x) + y;
		smooth += sqrtf((xp - x) * (xp - x) + (yp - y) * (yp - y));
		count++;
        pdc->SetPixel(x, y, RGB(0, 197, 205));//输出绘制像素
	}
    else{
        smooth += MidPline(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2, x1, y1, k, b, count, pdc);
        smooth += MidPline((x1 + x2) / 2, (y1 + y2) / 2, x2, y2, x1, y1, k, b, count, pdc);
    }
	smooth /= count;
}

double CcgDzxDrawLineView::MidPline(int x1, int y1, int x2, int y2, 
	int startx, int starty, float k, float b, double &count, CDC *pdc) {
	CcgDzxDrawLineDoc* pDoc = GetDocument();
	float smooth = 0;
    if (abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1) {
		int x = (int)(x1 + x2) / 2;
		int y = (int)(y1 + y2) / 2;
		double xp = (y - starty + x / k + k * startx) / (k + 1 / k);
		double yp = -1 / k * (xp - x) + y;
		smooth += sqrtf((x - xp) * (x - xp) + (y - yp) * (y - yp));
		count++;
		pdc->SetPixel(x, y, RGB(0, 197, 205));
	}
    else{
        smooth += MidPline(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2, startx, starty, k, b, count, pdc);
        smooth += MidPline((x1 + x2) / 2, (y1 + y2) / 2, x2, y2, startx, starty, k, b, count, pdc);
    }
	return smooth;
}

void CcgDzxDrawLineView::BresenhamArc(double theta1, double theta2, double R, COLORREF color, CDC* pDC)
{
	theta1 = theta1 / 180 * Pi;
	theta2 = theta2 / 180 * Pi;
	for(double angle = theta1; angle < theta2; angle = angle + 0.01)
	{
		 pDC->SetPixel((int)(cos(angle) * R + 0.5), (int)(-sin(angle) * R + 0.5), color); 
	}
}

void CcgDzxDrawLineView::OnText(CString str, CDC *pdc)
{

}
