
// cg2018QBFillPolyView.h : Ccg2018QBFillPolyView ��Ľӿ�
//

#pragma once

#define N 64

class Ccg2018QBFillPolyView : public CView
{
protected: // �������л�����
	Ccg2018QBFillPolyView();
	DECLARE_DYNCREATE(Ccg2018QBFillPolyView)

// ����
public:
	Ccg2018QBFillPolyDoc* GetDocument() const;

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
	void SeedFill(CPoint seed,COLORREF fill,COLORREF edge,CDC* pDC,BoxRect_t polyRect1)

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
	virtual ~Ccg2018QBFillPolyView();
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
	afx_msg BoxRect_t GetPolygonRect(int pointNumOfPolygon, CPoint tarPolygon[]);
	afx_msg BOOL PointInPolygon(int pointNumOfPolygon, CPoint tarPolygon[], CPoint testPoint);
};

#ifndef _DEBUG  // cg2018QBFillPolyView.cpp �еĵ��԰汾
inline Ccg2018QBFillPolyDoc* Ccg2018QBFillPolyView::GetDocument() const
   { return reinterpret_cast<Ccg2018QBFillPolyDoc*>(m_pDocument); }
#endif

