
// cg2018LFr2DTrans.h : cg2018LFr2DTrans Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// Ccg2018LFr2DTransApp:
// �йش����ʵ�֣������ cg2018LFr2DTrans.cpp
//

class Ccg2018LFr2DTransApp : public CWinAppEx
{
public:
	Ccg2018LFr2DTransApp();


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

extern Ccg2018LFr2DTransApp theApp;
