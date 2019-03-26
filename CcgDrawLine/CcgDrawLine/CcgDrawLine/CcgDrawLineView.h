
// CcgDrawLineView.h : CCcgDrawLineView ��Ľӿ�
//

#pragma once


class CCcgDrawLineView : public CView
{
protected: // �������л�����
	CCcgDrawLineView();
	DECLARE_DYNCREATE(CCcgDrawLineView)

// ����
public:
	CCcgDrawLineDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CCcgDrawLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // CcgDrawLineView.cpp �еĵ��԰汾
inline CCcgDrawLineDoc* CCcgDrawLineView::GetDocument() const
   { return reinterpret_cast<CCcgDrawLineDoc*>(m_pDocument); }
#endif

