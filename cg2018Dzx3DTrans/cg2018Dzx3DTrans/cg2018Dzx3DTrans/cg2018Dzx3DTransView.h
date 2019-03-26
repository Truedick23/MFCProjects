
// cg2018Dzx3DTransView.h : Ccg2018Dzx3DTransView 类的接口
//

#pragma once

class CDrawScene;
class CCameraView;

class Ccg2018Dzx3DTransView : public CView
{
protected: // 仅从序列化创建
	Ccg2018Dzx3DTransView();
	DECLARE_DYNCREATE(Ccg2018Dzx3DTransView)

// 特性
public:
	Ccg2018Dzx3DTransDoc* GetDocument() const;

	CClientDC  *m_pDC; 
	BOOL       m_autoPlay;
	CRect      m_viewRect;

 	CDrawScene *m_drawScene;
	CCameraView *m_cameraView;

// // 操作
public:
	void DrawScene();
	BOOL bSetupPixelFormat();

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
	virtual ~Ccg2018Dzx3DTransView();
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAutoplay();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnOnlight();
	afx_msg void OnOnshade();
};

#ifndef _DEBUG  // cg2018Dzx3DTransView.cpp 中的调试版本
inline Ccg2018Dzx3DTransDoc* Ccg2018Dzx3DTransView::GetDocument() const
   { return reinterpret_cast<Ccg2018Dzx3DTransDoc*>(m_pDocument); }
#endif

