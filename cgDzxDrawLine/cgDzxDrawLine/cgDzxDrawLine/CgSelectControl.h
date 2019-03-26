#pragma once
#include "afxwin.h"



// CCgSelectControl 窗体视图

class CCgSelectControl : public CFormView
{
	DECLARE_DYNCREATE(CCgSelectControl)

protected:
	CCgSelectControl();           // 动态创建所使用的受保护的构造函数
	virtual ~CCgSelectControl();

public:
	enum { IDD = IDD_SELECTCONTROL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedBline();
	afx_msg void OnClickedDdaline();
	afx_msg void OnClickedComparison();
	afx_msg void OnClickedMidpoint();
//	CEdit m_editcontrol;
	afx_msg void OnEnChangeText();
//	CString m_info;
	afx_msg void OnChangeInfo();
	afx_msg void OnEnableStaticText();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual void OnInitialUpdate();
//	afx_msg void OnBnClickedMidpoint2();
	afx_msg void OnClickedBarc();
	CString m_stringinfo;
	afx_msg void OnClickedCompare();
//	float m_radius;
	afx_msg void OnChangeRadius();
	afx_msg void OnChangeTheta1();
	afx_msg void OnChangeTheta2();
};


