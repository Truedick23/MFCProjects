// CgSelectControl.cpp : 实现文件
//

#include "stdafx.h"
#include "cgDzxDrawLine.h"
#include "cgDzxDrawLineDoc.h"
#include "cgDzxDrawLineView.h"
#include "CgSelectControl.h"
#include "resource.h" 


// CCgSelectControl

IMPLEMENT_DYNCREATE(CCgSelectControl, CFormView)

CCgSelectControl::CCgSelectControl()
	: CFormView(CCgSelectControl::IDD)
{
	m_stringinfo = _T("Welcome!");
}

CCgSelectControl::~CCgSelectControl()
{
}

//void CCgSelectControl::DoDataExchange(CDataExchange* pDX)
//{
//	CFormView::DoDataExchange(pDX);
//	//  DDX_Control(pDX, IDC_TEXT, m_editcontrol);
//	DDX_Control(pDX, IDC_INFO1, m_stringinfo);
//}

BEGIN_MESSAGE_MAP(CCgSelectControl, CFormView)
	ON_BN_CLICKED(IDC_BLINE, &CCgSelectControl::OnClickedBline)
	ON_BN_CLICKED(IDC_DDALINE, &CCgSelectControl::OnClickedDdaline)
	ON_BN_CLICKED(IDC_MIDPOINT, &CCgSelectControl::OnClickedMidpoint)
	ON_BN_CLICKED(IDC_BARC, &CCgSelectControl::OnClickedBarc)
	ON_BN_CLICKED(IDC_COMPARE, &CCgSelectControl::OnClickedCompare)
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


void CCgSelectControl::OnClickedBline()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgDzxDrawLineDoc* pDoc = (CcgDzxDrawLineDoc*)GetDocument();
	pDoc->m_displayMode = 1;
	pDoc->UpdateAllViews(this);
	CString m_stringinfo = _T("");
	if(pDoc->BLineDrawed) {
		CString errorEbuf, timeEbuf, smoothEbuf;
		errorEbuf.Format(_T("%0.3f "), pDoc->BLineAverageError);
		timeEbuf.Format(_T("%dms "), pDoc->BLineTime);
		smoothEbuf.Format(_T("%0.3f "), pDoc->BLineSmooth);
		m_stringinfo = _T("Bline: \n Error = " + errorEbuf + 
			"\n Smooth = " + smoothEbuf + 
			"\n Time = " + timeEbuf);
	}
	else 
		m_stringinfo = _T("Bline was drawn, click again to see data.");
	CWnd* pWnd = GetDlgItem(IDC_INFO1);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CCgSelectControl::OnClickedDdaline()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgDzxDrawLineDoc* pDoc = (CcgDzxDrawLineDoc*)GetDocument();
	pDoc->m_displayMode = 0;
	pDoc->UpdateAllViews(this);
	CString m_stringinfo = _T("");
	if(pDoc->DDAdrawed) {
		CString errorEbuf, timeEbuf, smoothEbuf;;
		errorEbuf.Format(_T("%0.3f "), pDoc->DDALineAverageError);
		timeEbuf.Format(_T("%dms "), pDoc->DDALineTime);
		smoothEbuf.Format(_T("%0.3f "), pDoc->DDALineSmooth);
		m_stringinfo = _T("DDA: \n Error = " + errorEbuf + 
			"\n Smooth = " + smoothEbuf + 
			"\n Time = " + timeEbuf);
	}
	else
		m_stringinfo = _T("DDA was drawn, click again to see data.");
	CWnd* pWnd = GetDlgItem(IDC_INFO1);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CCgSelectControl::OnClickedMidpoint()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgDzxDrawLineDoc* pDoc = (CcgDzxDrawLineDoc*)GetDocument();
	pDoc->m_displayMode = 2;
	pDoc->UpdateAllViews(this);
	CString m_stringinfo = _T("");
	if(pDoc->MidPointDrawed) {
		CString smoothEbuf, timeEbuf;
		smoothEbuf.Format(_T("%0.3f "), pDoc->MidpointLineSmooth);
		timeEbuf.Format(_T("%dms "), pDoc->MidPointTime);
		m_stringinfo = _T("MidPoint:\n Smooth = " + smoothEbuf + 
			"\n Time = " + timeEbuf);
	}
	else
		m_stringinfo = _T("MidPoint was drawn, click again to see data.");
	CWnd* pWnd = GetDlgItem(IDC_INFO1);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}

void CCgSelectControl::OnClickedBarc()
{
	// TODO: 在此添加控件通知处理程序代码
	CcgDzxDrawLineDoc* pDoc = (CcgDzxDrawLineDoc*)GetDocument();
	pDoc->m_displayMode = 3;
	pDoc->UpdateAllViews(this);
	CString m_stringinfo = _T("Arc has drawed");
	CWnd* pWnd = GetDlgItem(IDC_INFO1);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}


void CCgSelectControl::OnEnChangeText()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	CcgDzxDrawLineDoc* pDoc = (CcgDzxDrawLineDoc*)GetDocument();
}


void CCgSelectControl::OnChangeInfo()
{
	
}


void CCgSelectControl::OnEnableStaticText()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CCgSelectControl::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CcgDzxDrawLineDoc* pDoc = (CcgDzxDrawLineDoc*)GetDocument();
	UpdateData(TRUE);
}


void CCgSelectControl::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类	
	CcgDzxDrawLineDoc* pDoc = (CcgDzxDrawLineDoc*)GetDocument();
	UpdateData(TRUE);
	pDoc->UpdateAllViews(this);
	CWnd* pWnd = GetDlgItem(IDC_INFO1);
    if (pWnd)
        pWnd->SetWindowText( TEXT("") );
}



void CCgSelectControl::OnClickedCompare()
{
	CcgDzxDrawLineDoc* pDoc = (CcgDzxDrawLineDoc*)GetDocument();
	pDoc->UpdateAllViews(this);
	// TODO: 在此添加控件通知处理程序代码
	CString m_stringinfo = _T("");
	if(pDoc->BLineDrawed && pDoc->DDAdrawed && pDoc->MidPointDrawed) {
		CString errorEbufDDA, timeEbufDDA, smoothEbufDDA, 
			errorEbufBline, timeEbufBline, smoothEbufBline, 
			smoothEbufMidLine, timeEbufMidLine;
		errorEbufDDA.Format(_T("%0.3f "), pDoc->DDALineAverageError);
		timeEbufDDA.Format(_T("%dms "), pDoc->DDALineTime);
		smoothEbufDDA.Format(_T("%0.3f "), pDoc->DDALineSmooth);
		errorEbufBline.Format(_T("%0.3f "), pDoc->BLineAverageError);
		timeEbufBline.Format(_T("%dms "), pDoc->BLineTime);
		smoothEbufBline.Format(_T("%0.3f "), pDoc->BLineSmooth);
		smoothEbufMidLine.Format(_T("%0.3f "), pDoc->MidpointLineSmooth);
		timeEbufMidLine.Format(_T("%dms "), pDoc->MidPointTime);
		m_stringinfo = 
			_T("Comparison:\n Error:\n   DDA = " + errorEbufDDA + 
			"\n   Bline = " + errorEbufBline + 
			"\n Smooth\n   DDA = " + smoothEbufDDA + "\n   Bline = " + smoothEbufBline + 
			"\n   MidPoint = " + smoothEbufMidLine + "\n Time:\n   DDA = " + timeEbufDDA + 
			"\n   Bline = " + timeEbufBline + "\n   MidPoint = " + timeEbufMidLine);
	}
	else 
		m_stringinfo = _T("Please click those three button above first, in order to acquire data.");
	CWnd* pWnd = GetDlgItem(IDC_INFO1);
	if (pWnd)
		pWnd->SetWindowText(m_stringinfo);
	UpdateData(FALSE);
}