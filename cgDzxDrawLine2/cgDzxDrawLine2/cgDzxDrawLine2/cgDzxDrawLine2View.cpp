
// cgDzxDrawLine2View.cpp : CcgDzxDrawLine2View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CcgDzxDrawLine2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CcgDzxDrawLine2View ����/����

CcgDzxDrawLine2View::CcgDzxDrawLine2View()
{
	// TODO: �ڴ˴���ӹ������

}

CcgDzxDrawLine2View::~CcgDzxDrawLine2View()
{
}

BOOL CcgDzxDrawLine2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CcgDzxDrawLine2View ����

void CcgDzxDrawLine2View::OnDraw(CDC* /*pDC*/)
{
	CcgDzxDrawLine2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CcgDzxDrawLine2View ��ӡ


void CcgDzxDrawLine2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CcgDzxDrawLine2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CcgDzxDrawLine2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CcgDzxDrawLine2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CcgDzxDrawLine2View ���

#ifdef _DEBUG
void CcgDzxDrawLine2View::AssertValid() const
{
	CView::AssertValid();
}

void CcgDzxDrawLine2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcgDzxDrawLine2Doc* CcgDzxDrawLine2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcgDzxDrawLine2Doc)));
	return (CcgDzxDrawLine2Doc*)m_pDocument;
}
#endif //_DEBUG


// CcgDzxDrawLine2View ��Ϣ�������
