
// cgDzxDrawLineView.h : CcgDzxDrawLineView ��Ľӿ�
//
#include "cgDzxDrawLineDoc.h"

#pragma once


class CcgDzxDrawLineView : public CView
{
protected: // �������л�����
	CcgDzxDrawLineView();
	DECLARE_DYNCREATE(CcgDzxDrawLineView)

// ����
public:
	CcgDzxDrawLineDoc* GetDocument() const;

// ����
public:
	void DDAline(int, int, int, int, double&, double&, CDC*);
	void Bline(int, int, int, int, double&, double&, CDC*);
	void MidPline(int, int, int, int, double&, CDC*);
	double MidPline(int, int, int, int, int, int, float, float, double &, CDC*);
	void BresenhamArc(double, double, double, COLORREF, CDC* pDC);
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
	virtual ~CcgDzxDrawLineView();
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
	afx_msg void OnText(CString str, CDC* pdc);
};

#ifndef _DEBUG  // cgDzxDrawLineView.cpp �еĵ��԰汾
inline CcgDzxDrawLineDoc* CcgDzxDrawLineView::GetDocument() const
   { return reinterpret_cast<CcgDzxDrawLineDoc*>(m_pDocument); }
#endif

