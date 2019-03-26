
// cg2018Dzx3DTransView.h : Ccg2018Dzx3DTransView ��Ľӿ�
//

#pragma once

class CDrawScene;
class CCameraView;

class Ccg2018Dzx3DTransView : public CView
{
protected: // �������л�����
	Ccg2018Dzx3DTransView();
	DECLARE_DYNCREATE(Ccg2018Dzx3DTransView)

// ����
public:
	Ccg2018Dzx3DTransDoc* GetDocument() const;

	CClientDC  *m_pDC; 
	BOOL       m_autoPlay;
	CRect      m_viewRect;

 	CDrawScene *m_drawScene;
	CCameraView *m_cameraView;

// // ����
public:
	void DrawScene();
	BOOL bSetupPixelFormat();

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
	virtual ~Ccg2018Dzx3DTransView();
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAutoplay();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnOnlight();
	afx_msg void OnOnshade();
};

#ifndef _DEBUG  // cg2018Dzx3DTransView.cpp �еĵ��԰汾
inline Ccg2018Dzx3DTransDoc* Ccg2018Dzx3DTransView::GetDocument() const
   { return reinterpret_cast<Ccg2018Dzx3DTransDoc*>(m_pDocument); }
#endif

