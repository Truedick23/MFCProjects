
// cgDzxDrawLineDoc.cpp : CcgDzxDrawLineDoc ���ʵ��
//

#include "stdafx.h"
#include<iostream>
using namespace std;
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "cgDzxDrawLine.h"
#endif

#include "cgDzxDrawLineDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CcgDzxDrawLineDoc

IMPLEMENT_DYNCREATE(CcgDzxDrawLineDoc, CDocument)

BEGIN_MESSAGE_MAP(CcgDzxDrawLineDoc, CDocument)
END_MESSAGE_MAP()


// CcgDzxDrawLineDoc ����/����

CcgDzxDrawLineDoc::CcgDzxDrawLineDoc()
{
	// TODO: �ڴ����һ���Թ������
	wm_width = 0;
	wm_height = 0;
	m_displayMode = 5;
	DDALineAverageError = 0.0f;
	BLineAverageError = 0.0f;
	DDALineSmooth = 0;
	BLineSmooth = 0;
	MidpointLineSmooth = 0;
	DDALineTime = 0.0f;
	BLineTime = 0.0f;
	MidPointTime = 0.0f;
	DDAdrawed = false;
	BLineDrawed = false;
	MidPointDrawed = false;
}

CcgDzxDrawLineDoc::~CcgDzxDrawLineDoc()
{
}

BOOL CcgDzxDrawLineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CcgDzxDrawLineDoc ���л�

void CcgDzxDrawLineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CcgDzxDrawLineDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CcgDzxDrawLineDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CcgDzxDrawLineDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CcgDzxDrawLineDoc ���

#ifdef _DEBUG
void CcgDzxDrawLineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CcgDzxDrawLineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CcgDzxDrawLineDoc ����
