
// cg2018QBFillPolyDoc.h : Ccg2018QBFillPolyDoc ��Ľӿ�
//


#pragma once


class Ccg2018QBFillPolyDoc : public CDocument
{
protected: // �������л�����
	Ccg2018QBFillPolyDoc();
	DECLARE_DYNCREATE(Ccg2018QBFillPolyDoc)

// ����
public:
	int wm_width, wm_height;
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
	virtual ~Ccg2018QBFillPolyDoc();
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
