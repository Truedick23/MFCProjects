
// cgDzxDrawLine.h : cgDzxDrawLine Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CcgDzxDrawLineApp:
// �йش����ʵ�֣������ cgDzxDrawLine.cpp
//

class CcgDzxDrawLineApp : public CWinAppEx
{
public:
	CcgDzxDrawLineApp();


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

extern CcgDzxDrawLineApp theApp;
