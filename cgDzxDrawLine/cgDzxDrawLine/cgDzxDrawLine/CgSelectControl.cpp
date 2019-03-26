// CgSelectControl.cpp : ʵ���ļ�
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


// CCgSelectControl ���

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


// CCgSelectControl ��Ϣ�������


void CCgSelectControl::OnClickedBline()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CcgDzxDrawLineDoc* pDoc = (CcgDzxDrawLineDoc*)GetDocument();
}


void CCgSelectControl::OnChangeInfo()
{
	
}


void CCgSelectControl::OnEnableStaticText()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CCgSelectControl::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CcgDzxDrawLineDoc* pDoc = (CcgDzxDrawLineDoc*)GetDocument();
	UpdateData(TRUE);
}


void CCgSelectControl::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���	
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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