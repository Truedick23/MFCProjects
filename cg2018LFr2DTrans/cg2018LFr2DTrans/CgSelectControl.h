#pragma once



// CCgSelectControl ������ͼ

class CCgSelectControl : public CFormView
{
	DECLARE_DYNCREATE(CCgSelectControl)

protected:
	CCgSelectControl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCgSelectControl();

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
	afx_msg void OnBnClickedYup();
	afx_msg void OnBnClickedXleft();
	afx_msg void OnBnClickedXright();
	afx_msg void OnBnClickedYdown();
	afx_msg void OnBnClickedTransmode();

	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	int m_transSelect;
	afx_msg void OnBnClickedTranspoly();
	afx_msg void OnBnClickedTransline();
	afx_msg void OnBnClickedLiangbsk();
	afx_msg void OnBnClickedWeilerath();

};


