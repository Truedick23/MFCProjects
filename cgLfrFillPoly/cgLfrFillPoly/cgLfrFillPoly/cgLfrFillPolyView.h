
// cgLfrFillPolyView.h : CcgLfrFillPolyView ��Ľӿ�
//

#pragma once
#define N 64


class CcgLfrFillPolyView : public CView
{
protected: // �������л�����
	CcgLfrFillPolyView();
	DECLARE_DYNCREATE(CcgLfrFillPolyView)

// ����
public:
	CcgLfrFillPolyDoc* GetDocument() const;

	CClientDC *m_pDC;
	int m_pNumbers;                               // polygon input buffer
	CPoint m_pAccord[N],m_mousePoint;

	int m_wndWidth,m_wndHeight;

	int m_Begin,m_End,m_edgeNumbers,m_Scan;       // polygon fill data structure
	float m_yMax[N],m_yMin[N],m_Xa[N],m_Dx[N];

	void Fillpolygon(int pNumbers, CPoint *points, CDC *pDC); // polygon fill algorithm

	void pLoadPolygon(int pNumbers, CPoint *points);
	void pInsertLine(float x1, float y1, float x2, float y2);
	void Include();
	void UpdateXvalue();
	void pXsort(int Begin, int i);
	void pFillScan(CDC* pDC);

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
	virtual ~CcgLfrFillPolyView();
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void PointFillpoly(int pNumbers, CPoint *points, CDC *pDC);
};

#ifndef _DEBUG  // cgLfrFillPolyView.cpp �еĵ��԰汾
inline CcgLfrFillPolyDoc* CcgLfrFillPolyView::GetDocument() const
   { return reinterpret_cast<CcgLfrFillPolyDoc*>(m_pDocument); }
#endif

