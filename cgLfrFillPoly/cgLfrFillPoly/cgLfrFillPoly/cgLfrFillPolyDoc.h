
// cgLfrFillPolyDoc.h : CcgLfrFillPolyDoc ��Ľӿ�
//


#pragma once


class CcgLfrFillPolyDoc : public CDocument
{
protected: // �������л�����
	CcgLfrFillPolyDoc();
	DECLARE_DYNCREATE(CcgLfrFillPolyDoc)

// ����
public:
	int wm_width, wm_height;
	int m_drawMode;
// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CcgLfrFillPolyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
