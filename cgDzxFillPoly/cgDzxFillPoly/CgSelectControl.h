#pragma once
#include "resource.h" 



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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnClickedFillPoint();
	afx_msg void OnClickedSeedFill();
	afx_msg void OnClickedScanLine();
};


