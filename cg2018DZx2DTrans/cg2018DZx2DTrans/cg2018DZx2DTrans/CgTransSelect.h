#include "stdafx.h"

#pragma once
#include "afxwin.h"



// CgTransSelect ������ͼ

class CgTransSelect : public CFormView
{
	DECLARE_DYNCREATE(CgTransSelect)

protected:
	CgTransSelect();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CgTransSelect();

	void ViewTransLine(CDC* pDC, CRect dcRect);
	void ViewTransPolygon(CDC* pDC, CRect dcRect);

public:
	enum { IDD = IDD_SELECTCONTROL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_transSelect;

	afx_msg void OnBnClickedYup();
	afx_msg void OnBnClickedXleft();
	afx_msg void OnBnClickedTransmode();
	afx_msg void OnBnClickedXright();
	afx_msg void OnBnClickedYdown();

	afx_msg void OnBnClickedRdtransline();
	afx_msg void OnBnClickedTranspoly();

	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

	afx_msg void OnBnClickedRdliangb();
	afx_msg void OnBnClickedRdweilera();
};


