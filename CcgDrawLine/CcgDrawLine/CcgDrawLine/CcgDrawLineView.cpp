
// CcgDrawLineView.cpp : CCcgDrawLineView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CcgDrawLine.h"
#endif

#include "CcgDrawLineDoc.h"
#include "CcgDrawLineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCcgDrawLineView

IMPLEMENT_DYNCREATE(CCcgDrawLineView, CView)

BEGIN_MESSAGE_MAP(CCcgDrawLineView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCcgDrawLineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CCcgDrawLineView 构造/析构

CCcgDrawLineView::CCcgDrawLineView()
{
	// TODO: 在此处添加构造代码

}

CCcgDrawLineView::~CCcgDrawLineView()
{
}

BOOL CCcgDrawLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCcgDrawLineView 绘制

void CCcgDrawLineView::OnDraw(CDC* /*pDC*/)
{
	CCcgDrawLineDoc* pDoc = GetDocument();
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


// CCcgDrawLineView 打印


void CCcgDrawLineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCcgDrawLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCcgDrawLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCcgDrawLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CCcgDrawLineView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCcgDrawLineView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCcgDrawLineView 诊断

#ifdef _DEBUG
void CCcgDrawLineView::AssertValid() const
{
	CView::AssertValid();
}

void CCcgDrawLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCcgDrawLineDoc* CCcgDrawLineView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCcgDrawLineDoc)));
	return (CCcgDrawLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CCcgDrawLineView 消息处理程序


void CCcgDrawLineView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CCcgDrawLineDoc *pDoc = GetDocument();     // 获取Doc类指针

	pDoc->wm_width = cx;                    // 记录窗体视口尺寸
	pDoc->wm_height = cy;

	// TODO: 在此处添加消息处理程序代码
}
