
// cg2018DZx2DTransDoc.cpp : Ccg2018DZx2DTransDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "cg2018DZx2DTrans.h"
#endif

#include "cg2018DZx2DTransDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Ccg2018DZx2DTransDoc

IMPLEMENT_DYNCREATE(Ccg2018DZx2DTransDoc, CDocument)

BEGIN_MESSAGE_MAP(Ccg2018DZx2DTransDoc, CDocument)
END_MESSAGE_MAP()


// Ccg2018DZx2DTransDoc ����/����

Ccg2018DZx2DTransDoc::Ccg2018DZx2DTransDoc()
{
	// TODO: �ڴ����һ���Թ������
		// General Line Space Model
	P1.x =   20;   P1.y =   30;
	P2.x = 150;   P2.y = 200;

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 2; j++)
			if (i == j) m_lineMatrix[i][j] = 1.0f;
			else        m_lineMatrix[i][j] = 0.0f;

	// Liang-Barsky Line Space Model
	LB_P1.x =  30;   LB_P1.y =  30;
	LB_P2.x = 230;   LB_P2.y = 230;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			if (i == j) m_LB_LineMatrix[i][j] = 1.0f;
			else        m_LB_LineMatrix[i][j] = 0.0f;

	// General Polygon Space Model
	m_pointNumber = 0;

	/*m_pointNumber = 7;
	m_spPolygon[0].x = 10;    m_spPolygon[0].y = 10;
	m_spPolygon[1].x = 40;    m_spPolygon[1].y = 120;
	m_spPolygon[2].x = 60;    m_spPolygon[2].y = 150;
	m_spPolygon[3].x = 100;    m_spPolygon[3].y = 100;
	m_spPolygon[4].x = 120;    m_spPolygon[4].y = 180;
	m_spPolygon[5].x = 135;    m_spPolygon[5].y = 80;
	m_spPolygon[6].x = 10;    m_spPolygon[7].y = 10;*/


	m_polygonVisible = true;
	m_clipPointNumber = 7;
	m_clipPolygon[0].x = 0;   m_clipPolygon[0].y =   0;
	m_clipPolygon[1].x = 0;  m_clipPolygon[1].y = 0;
	m_clipPolygon[2].x = 0;   m_clipPolygon[2].y = 0;
	m_clipPolygon[3].x = 0;    m_clipPolygon[3].y = 0;
	m_clipPolygon[4].x = 0;  m_clipPolygon[4].y = 0;
	m_clipPolygon[5].x = 0;   m_clipPolygon[5].y = 0;
	m_clipPolygon[6].x = 0;    m_clipPolygon[6].y = 0;

	for (int i = 0; i < 3; i++)
	    for (int j = 0; j < 2; j++)
			if (i == j) m_polygonMatrix[i][j] = 1.0f;
			else        m_polygonMatrix[i][j] = 0.0f;

	// Weiler-Atherton Polygon Space Model
			/*
	m_WA_polygonVisible = true;
	m_WA_pointNumber = 4;
	m_WA_spPolygon[0].x =   0;    m_WA_spPolygon[0].y =   0;
	m_WA_spPolygon[1].x = 25;    m_WA_spPolygon[1].y = 100;
	m_WA_spPolygon[2].x = 80;    m_WA_spPolygon[2].y =  20;
	m_WA_spPolygon[3].x =   0;    m_WA_spPolygon[3].y =   0;

	m_WA_clipPointNumber = 4;
	m_WA_clipPolygon[0].x = 0;   m_WA_clipPolygon[0].y =   0;
	m_WA_clipPolygon[1].x = 0;  m_WA_clipPolygon[1].y = 0;
	m_WA_clipPolygon[2].x = 0;   m_WA_clipPolygon[2].y = 0;
	m_WA_clipPolygon[3].x = 0;    m_WA_clipPolygon[3].y = 0;*/

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			if (i == j) m_WA_polygonMatrix[i][j] = 1.0f;
			else        m_WA_polygonMatrix[i][j] = 0.0f;

	m_transDir  = 0;     // 0:-X      1:+X         2: -Y         3:+Y
	m_transMode = 0;     // 0: Move   1: Rotate    2: Scale
	m_transSelect = 0;   // 0: Line   1: Polygon   2: Window  3:LB_Line  4:WA_Polygon

	m_wndLx = 0;
	m_wndLy = 0;
	m_wndRx = 300;
	m_wndRy = 300;

	m_lineVisible = true;
}

Ccg2018DZx2DTransDoc::~Ccg2018DZx2DTransDoc()
{
}

BOOL Ccg2018DZx2DTransDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// Ccg2018DZx2DTransDoc ���л�

void Ccg2018DZx2DTransDoc::Serialize(CArchive& ar)
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
void Ccg2018DZx2DTransDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void Ccg2018DZx2DTransDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void Ccg2018DZx2DTransDoc::SetSearchContent(const CString& value)
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

// Ccg2018DZx2DTransDoc ���

#ifdef _DEBUG
void Ccg2018DZx2DTransDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Ccg2018DZx2DTransDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Ccg2018DZx2DTransDoc ����
