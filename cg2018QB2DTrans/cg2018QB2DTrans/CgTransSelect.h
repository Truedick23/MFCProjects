#pragma once



// CCgTransSelect 窗体视图

class CCgTransSelect : public CFormView
{
	DECLARE_DYNCREATE(CCgTransSelect)

protected:
	CCgTransSelect();           // 动态创建所使用的受保护的构造函数
	virtual ~CCgTransSelect();

	void ViewTransLine(CDC* pDC, CRect dcRect);
	void ViewTransPolygon(CDC* pDC, CRect dcRect);


public:
	enum { IDD = IDD_TRANSSELECT };
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
	afx_msg void OnClickedXleft();
	afx_msg void OnClickedXright();
	afx_msg void OnClickedYup();
	afx_msg void OnClickedYdown();
	virtual void OnInitialUpdate();

	int m_transSelect;
	afx_msg void OnSelchangeTransselect();
	afx_msg void OnClickedTransmode();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


