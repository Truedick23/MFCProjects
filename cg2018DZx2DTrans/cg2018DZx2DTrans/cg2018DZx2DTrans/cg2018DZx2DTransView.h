
// cg2018DZx2DTransView.h : Ccg2018DZx2DTransView 类的接口
//

#pragma once
#include <vector>
using namespace std;


class Ccg2018DZx2DTransView : public CView
{
protected: // 仅从序列化创建
	Ccg2018DZx2DTransView();
	DECLARE_DYNCREATE(Ccg2018DZx2DTransView)

// 特性
public:
	Ccg2018DZx2DTransDoc* GetDocument() const;

	int m_pNumbers;
	int m_wndWidth,m_wndHeight;
	CPoint m_pAccord[N],m_mousePoint, seed;
// 操作
public:
	void CalculateMatrix(float transMatrix[3][2]);

	void ScaleMatrix(float Sx, float Sy, float m[3][2]);
	void RotateMatrix(float S, float C, float m[3][2]);
	void TranslateMatrix(float Tx, float Ty, float m[3][2]);

	void TransLine(CPoint p1, CPoint p2, CPoint *tp1, CPoint *tp2, float transMatrix[3][2]);
	void TransPolygon(int pointNumber, CPoint spPolygon[N], CPoint transPolygon[N], float transMatrix[3][2]);

	void DisplayLine(CDC* pDC,CPoint p1, CPoint p2, COLORREF rgbColor);
	void DisplayPolygon(CDC* pDC, int pointNumber, CPoint transPolygon[N], COLORREF rgbColor);

	void DrawClipLine(CDC* pDC);
	void DrawClipPolygon(CDC* pDC);

	// Cohn-Sutherland Subdivision Line Clip
	int  ClipLine(int *x1, int *y1, int *x2, int *y2);
	int  pCode(int *x, int *y);
	int  LineVisible(int *x1, int *y1, int *x2, int *y2);

	// Sutherland-Hodgman Polygon Clip
	int  ClipPolygon(int n, CPoint *tPoints, int *cn, CPoint *cPoints);
	int  pVisible(int x, int y, int i);
	int  LineCross(int x1, int y1, int x2, int y2, int i);
	void interSect(int Sx, int  Sy, int Px, int Py,	int  i, int *ix, int *iy);
	void outPut(int x, int y, int *cn, CPoint *cPoints);
	
	
	//Liang-Barsky Line Clip
	double Calculate_p(int x1, int y1, int x2, int y2, int type);
	double Calculate_q(int x1, int y1, int x2, int y2, int type);
	bool Liang_test(double p, double q, double &u1, double &u2); 
	bool Liang_ClipLine(int *x1, int *y1, int *x2, int *y2);
	
	void Weiler_PolygonEdgeClip(vector<CPoint> &set, vector<CPoint> &newset, const int mode);
	void Weiler_ParallelClip(CPoint p1, CPoint p2, vector<CPoint> &set, const int mode);
	bool Weiler_PolygonClip(vector<CPoint> &set, vector<CPoint> &set_result);

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
	virtual ~Ccg2018DZx2DTransView();
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
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // cg2018DZx2DTransView.cpp 中的调试版本
inline Ccg2018DZx2DTransDoc* Ccg2018DZx2DTransView::GetDocument() const
   { return reinterpret_cast<Ccg2018DZx2DTransDoc*>(m_pDocument); }
#endif

