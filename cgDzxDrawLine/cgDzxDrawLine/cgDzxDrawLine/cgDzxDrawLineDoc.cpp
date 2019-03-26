
// cgDzxDrawLineDoc.cpp : CcgDzxDrawLineDoc 类的实现
//

#include "stdafx.h"
#include<iostream>
using namespace std;
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// CcgDzxDrawLineDoc 构造/析构

CcgDzxDrawLineDoc::CcgDzxDrawLineDoc()
{
	// TODO: 在此添加一次性构造代码
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

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CcgDzxDrawLineDoc 序列化

void CcgDzxDrawLineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CcgDzxDrawLineDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CcgDzxDrawLineDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CcgDzxDrawLineDoc 诊断

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


// CcgDzxDrawLineDoc 命令
