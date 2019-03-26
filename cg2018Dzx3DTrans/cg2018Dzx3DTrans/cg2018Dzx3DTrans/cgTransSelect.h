#pragma once
#include "cg2018Dzx3DTransDoc.h"

#define  NN 64
#define PRJPLANERETWIDTH  300
#define PRJPLANERETHEIGHT 300



// cgTransSelect 窗体视图

class cgTransSelect : public CFormView
{
	DECLARE_DYNCREATE(cgTransSelect)

protected:
	cgTransSelect();           // 动态创建所使用的受保护的构造函数
	virtual ~cgTransSelect();

public:
	enum { IDD = IDD_SELECTCONTROL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	int m_transObj;
	afx_msg void OnBnClickedZback();
	afx_msg void OnBnClickedTransmode();
	afx_msg void OnBnClickedYup();
	afx_msg void OnBnClickedXleft();
	afx_msg void OnBnClickedZfront();
	afx_msg void OnBnClickedYdown();
	afx_msg void OnBnClickedXright();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeTransobj();
	afx_msg void OnBnClickedAuto();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

private:
	int      m_objNumber;
	Object_p m_whoObject;           // Object pointer
	COLORREF vcObjColor[SPACEOBJECTS];

	int polyCount;
	float ymax[NN],ymin[NN];
	int ibegin,iend,scan,pdges;
	float Dx[NN],Xa[NN],Sc[NN],Dc[NN];

	float prjPlaneRetZ[PRJPLANERETWIDTH][PRJPLANERETHEIGHT];  // Z-Buffer 2D Array

	void pTransToZbuffer(CRect dcRect);
	void pDrawLineObject(CDC *pDC, CRect dcRect);
	void pDrawLightObject(CDC *pDC, CRect dcRect, float maxShade, float minShade);
	void pDrawShadeLightObject(CDC *pDC, CRect dcRect, float maxShade, float minShade);

	void FillPolygon(CDC *pDC, int n,int *x,int *y,int *color,CRect dcRect);
	void Loadpolygon(int n,int *x,int *y, int *color);
	void PolyInsert(float x1,float y1,float x2,float y2, int c1, int c2);
	void UpdateXvalue();
	void XSort(int begin,int i);
	void Fillscan(CDC *pDC,CRect dcRect);
	void Include();

	float CalculateZValue(int x,int y,CRect dcRect,int i);
public:
	afx_msg void OnBnClickedOnshade();
	afx_msg void OnBnClickedOnlight();
};


