
// CcgDrawLineDoc.h : CCcgDrawLineDoc ��Ľӿ�
//


#pragma once


class CCcgDrawLineDoc : public CDocument
{
protected: // �������л�����
	CCcgDrawLineDoc();
	DECLARE_DYNCREATE(CCcgDrawLineDoc)

// ����
public:
	int wm_width;
	int wm_height;
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
	virtual ~CCcgDrawLineDoc();
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
