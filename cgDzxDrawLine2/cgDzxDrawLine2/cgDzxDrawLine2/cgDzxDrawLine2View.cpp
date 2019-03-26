
// cgDzxDrawLine2View.cpp : CcgDzxDrawLine2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "cgDzxDrawLine2.h"
#endif

#include "cgDzxDrawLine2Doc.h"
#include "cgDzxDrawLine2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcgDzxDrawLine2View

IMPLEMENT_DYNCREATE(CcgDzxDrawLine2View, CView)

BEGIN_MESSAGE_MAP(CcgDzxDrawLine2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CcgDzxDrawLine2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CcgDzxDrawLine2View 构造/析构

CcgDzxDrawLine2View::CcgDzxDrawLine2View()
{
	// TODO: 在此处添加构造代码

}

CcgDzxDrawLine2View::~CcgDzxDrawLine2View()
{
}

BOOL CcgDzxDrawLine2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CcgDzxDrawLine2View 绘制

void CcgDzxDrawLine2View::OnDraw(CDC* /*pDC*/)
{
	CcgDzxDrawLine2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CcgDzxDrawLine2View 打印


void CcgDzxDrawLine2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CcgDzxDrawLine2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CcgDzxDrawLine2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CcgDzxDrawLine2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CcgDzxDrawLine2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CcgDzxDrawLine2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CcgDzxDrawLine2View 诊断

#ifdef _DEBUG
void CcgDzxDrawLine2View::AssertValid() const
{
	CView::AssertValid();
}

void CcgDzxDrawLine2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgDzxDrawLine2Doc* CcgDzxDrawLine2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgDzxDrawLine2Doc)));
	return (CcgDzxDrawLine2Doc*)m_pDocument;
}
#endif //_DEBUG


// CcgDzxDrawLine2View 消息处理程序
