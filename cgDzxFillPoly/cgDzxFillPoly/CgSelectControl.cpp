// CgSelectControl.cpp : 实现文件
//

#include "stdafx.h"
#include "cgDzxFillPoly.h"
#include "CgSelectControl.h"
#include "cgDzxFillPolyDoc.h"
#include "cgDzxFillPolyView.h"
#include "resource.h" 


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

//	ON_BN_CLICKED(IDC_FILLPOINT, &CCgSelectControl::OnBnClickedFillpoint)
	ON_BN_CLICKED(IDC_FILLPOINT, &CCgSelectControl::OnClickedFillPoint)
	ON_BN_CLICKED(IDC_SEEDFILL, &CCgSelectControl::OnClickedSeedFill)
	ON_BN_CLICKED(IDC_SCANLINE, &CCgSelectControl::OnClickedScanLine)
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




//void CCgSelectControl::OnBnClickedFillpoint()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void CCgSelectControl::OnClickedFillPoint()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgDzxFillPolyDoc *pDoc = (CcgDzxFillPolyDoc*)GetDocument();
	pDoc->m_drawMode = 1;
	pDoc->UpdateAllViews(this);
	CString m_stringinfo = _T("");
	if(pDoc->FillPointTime) {
		CString timeEbuf;
		timeEbuf.Format(_T("%dms "), pDoc->FillPointTime);
		m_stringinfo = _T("Fill Point: \n time = " + timeEbuf);
	}
	else 
		m_stringinfo = _T("Fill Point has completed, click again to see data.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CCgSelectControl::OnClickedScanLine()
{
	// TODO: 在此添加控件通知处理程序代码
		CcgDzxFillPolyDoc *pDoc = (CcgDzxFillPolyDoc*)GetDocument();
	pDoc->m_drawMode = 2;
	pDoc->UpdateAllViews(this);
	CString m_stringinfo = _T("");
	if(pDoc->ScanLineDrawed) {
		CString timeEbuf;
		timeEbuf.Format(_T("%dms "), pDoc->ScanLineTime);
		m_stringinfo = _T("Scan Line: \n time = " + timeEbuf);
	}
	else 
		m_stringinfo = _T("Scan Line has completed, click again to see data.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CCgSelectControl::OnClickedSeedFill()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgDzxFillPolyDoc *pDoc = (CcgDzxFillPolyDoc*)GetDocument();
	pDoc->m_drawMode = 3;
	pDoc->UpdateAllViews(this);
	CString m_stringinfo = _T("");
	if(pDoc->SeedFillDrawed) {
		CString timeEbuf;
		timeEbuf.Format(_T("%dms "), pDoc->SeedFillTime);
		m_stringinfo = _T("Seed Fill: \n time = " + timeEbuf);
	}
	else 
		m_stringinfo = _T("Seed Fill has completed, click again to see data.");
	CWnd* pWnd = GetDlgItem(IDC_INFO);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}

