
// CcgDrawLineView.cpp : CCcgDrawLineView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCcgDrawLineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CCcgDrawLineView ����/����

CCcgDrawLineView::CCcgDrawLineView()
{
	// TODO: �ڴ˴���ӹ������

}

CCcgDrawLineView::~CCcgDrawLineView()
{
}

BOOL CCcgDrawLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCcgDrawLineView ����

void CCcgDrawLineView::OnDraw(CDC* /*pDC*/)
{
	CCcgDrawLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CDC* pDC = GetDC();               // ��ȡ��ͼ�豸������ָ��

    // ����2D����ϵ
	pDC->MoveTo(0, pDoc->wm_height/2);
	pDC->LineTo(pDoc->wm_width, pDoc->wm_height/2);
	pDC->MoveTo(pDoc->wm_width/2, 0);
	pDC->LineTo(pDoc->wm_width/2, pDoc->wm_height);

}


// CCcgDrawLineView ��ӡ


void CCcgDrawLineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCcgDrawLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCcgDrawLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCcgDrawLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CCcgDrawLineView ���

#ifdef _DEBUG
void CCcgDrawLineView::AssertValid() const
{
	CView::AssertValid();
}

void CCcgDrawLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCcgDrawLineDoc* CCcgDrawLineView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCcgDrawLineDoc)));
	return (CCcgDrawLineDoc*)m_pDocument;
}
#endif //_DEBUG


// CCcgDrawLineView ��Ϣ�������


void CCcgDrawLineView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CCcgDrawLineDoc *pDoc = GetDocument();     // ��ȡDoc��ָ��

	pDoc->wm_width = cx;                    // ��¼�����ӿڳߴ�
	pDoc->wm_height = cy;

	// TODO: �ڴ˴������Ϣ����������
}
