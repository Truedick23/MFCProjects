
// cg2018QBFillPoly.h : cg2018QBFillPoly Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// Ccg2018QBFillPolyApp:
// �йش����ʵ�֣������ cg2018QBFillPoly.cpp
//

class Ccg2018QBFillPolyApp : public CWinAppEx
{
public:
	Ccg2018QBFillPolyApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Ccg2018QBFillPolyApp theApp;
