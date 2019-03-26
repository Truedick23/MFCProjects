
// cgDzxFillPolyView.h : CcgDzxFillPolyView 类的接口
//

#pragma once
# define N 64

struct BoxRect_t 
{
	int minX;
	int minY;
	int maxX;
	int maxY;
};

class CcgDzxFillPolyView : public CView
{
protected: // 仅从序列化创建
	CcgDzxFillPolyView() ;
	DECLARE_DYNCREATE(CcgDzxFillPolyView)

// 特性
public:
	CcgDzxFillPolyDoc* GetDocument() const;

	CClientDC *m_pDC;
	int m_pNumbers;                               // polygon input buffer
	CPoint m_pAccord[N],m_mousePoint, seed;

	int m_wndWidth,m_wndHeight;
	int pattern;

	int m_Begin,m_End,m_edgeNumbers,m_Scan;       // polygon fill data structure
	float m_yMax[N],m_yMin[N],m_Xa[N],m_Dx[N];

	void Fillpolygon(int pNumbers, CPoint *points, CDC *pDC); // polygon fill algorithm

	void pLoadPolygon(int pNumbers, CPoint *points);
	void pInsertLine(float x1, float y1, float x2, float y2);
	void Include();
	void UpdateXvalue();
	void pXsort(int Begin, int i);
	void pFillScan(CDC* pDC);
	void PointFillpoly(int pNumbers, CPoint *points, CDC *m_pDC);
	BoxRect_t GetPolygonRect(int pointNumOfPolygon, CPoint tarPolygon[]);
	BOOL PointInPolygon(int pointNumOfPolygon, CPoint tarPolygon[], 
	                               CPoint testPoint);
	void SeedFill(CPoint seed,COLORREF fill,COLORREF edge,CDC* pDC,BoxRect_t polyRect1);

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CcgDzxFillPolyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // cgDzxFillPolyView.cpp 中的调试版本
inline CcgDzxFillPolyDoc* CcgDzxFillPolyView::GetDocument() const
   { return reinterpret_cast<CcgDzxFillPolyDoc*>(m_pDocument); }
#endif

