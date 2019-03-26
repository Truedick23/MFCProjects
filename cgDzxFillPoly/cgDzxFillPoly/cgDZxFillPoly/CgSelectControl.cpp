// CgSelectControl.cpp : 实现文件
//

#include "stdafx.h"
#include "cgDZxFillPoly.h"
#include "CgSelectControl.h"
#include "cgDZxFillPolyDoc.h"
#include <stack>


// CCgSelectControl

IMPLEMENT_DYNCREATE(CCgSelectControl, CFormView)

CCgSelectControl::CCgSelectControl()
	: CFormView(CCgSelectControl::IDD)
{

}

CCgSelectControl::~CCgSelectControl()
{
}

void CCgSelectControl::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCgSelectControl, CFormView)
	ON_BN_CLICKED(IDC_FILLPOINT, &CCgSelectControl::OnClickedFillpoint)
	ON_BN_CLICKED(IDC_SCANLINE, &CCgSelectControl::OnClickedScanline)
	ON_BN_CLICKED(IDC_SEEDFILL, &CCgSelectControl::OnClickedSeedfill)
	ON_BN_CLICKED(IDC_TRIPOLY, &CCgSelectControl::OnBnClickedTripoly)
	ON_BN_CLICKED(IDC_COMPARISON, &CCgSelectControl::OnBnClickedComparison)
END_MESSAGE_MAP()


// CCgSelectControl 诊断

#ifdef _DEBUG
void CCgSelectControl::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCgSelectControl::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCgSelectControl 消息处理程序

void CCgSelectControl::OnClickedFillpoint()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgDZxFillPolyDoc *pDoc = (CcgDZxFillPolyDoc*)GetDocument();
	pDoc->m_drawMode = 1;
	//pDoc->UpdateAllViews(this);
	CString m_stringinfo = _T("");
	if(pDoc->FillPointDrawed) {
		CString timeEbuf;
		timeEbuf.Format(_T("%dms "), pDoc->FillPointTime);
		m_stringinfo = _T("Fill Point: \n time = " + timeEbuf);
	}
	else 
		m_stringinfo = _T("Mode: Fill Point\nclick again to see data.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CCgSelectControl::OnClickedScanline()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgDZxFillPolyDoc *pDoc = (CcgDZxFillPolyDoc*)GetDocument();
	pDoc->m_drawMode = 2;
	//pDoc->UpdateAllViews(this);
	CString m_stringinfo = _T("");
	if(pDoc->ScanLineDrawed) {
		CString timeEbuf;
		timeEbuf.Format(_T("%dms "), pDoc->ScanLineTime);
		m_stringinfo = _T("Scan Line: \n time = " + timeEbuf);
	}
	else 
		m_stringinfo = _T("Mode: Scan Line\nclick again to see data.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CCgSelectControl::OnClickedSeedfill()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgDZxFillPolyDoc *pDoc = (CcgDZxFillPolyDoc*)GetDocument();
	pDoc->m_drawMode = 3;
	//pDoc->UpdateAllViews(this);
	CString m_stringinfo = _T("");
	if(pDoc->SeedFillDrawed) {
		CString timeEbuf;
		timeEbuf.Format(_T("%dms "), pDoc->SeedFillTime);
		m_stringinfo = _T("Seed Fill: \n time = " + timeEbuf);
	}
	else {
		m_stringinfo = _T("Mode: Seed Fill\nclick again to see data.");
		
	}
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CCgSelectControl::OnBnClickedTripoly()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	CcgDZxFillPolyDoc *pDoc = (CcgDZxFillPolyDoc*)GetDocument();
	pDoc->m_drawMode = 4;
	//pDoc->UpdateAllViews(this);
	CString m_stringinfo;
	m_stringinfo = _T("Mode: TriPoly.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CCgSelectControl::OnBnClickedComparison()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	CcgDZxFillPolyDoc *pDoc = (CcgDZxFillPolyDoc*)GetDocument();
	pDoc->m_drawMode = 5;
	//pDoc->UpdateAllViews(this);
	CString m_stringinfo = _T("");
	if(pDoc->SeedFillDrawed && pDoc->FillPointDrawed && pDoc->ScanLineDrawed) {
		CString time1Ebuf, time2Ebuf, time3Ebuf;
		time1Ebuf.Format(_T("%dms "), pDoc->FillPointTime);
		time2Ebuf.Format(_T("%dms "), pDoc->ScanLineTime);
		time3Ebuf.Format(_T("%dms "), pDoc->SeedFillTime);
		m_stringinfo = _T("Compare:\n Fill Point: time = " + time1Ebuf + 
								  "\n Scan Line: time = " + time2Ebuf + 
								  "\n Seed Fill: time = " + time3Ebuf);
	}
	else {
		m_stringinfo = _T("You haven't use all of these algorithms yet, click them on the left.");
	}
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}
