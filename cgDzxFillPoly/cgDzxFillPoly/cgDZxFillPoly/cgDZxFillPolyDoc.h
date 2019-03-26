
// cgDZxFillPolyDoc.h : CcgDZxFillPolyDoc ��Ľӿ�
//


#pragma once


class CcgDZxFillPolyDoc : public CDocument
{
protected: // �������л�����
	CcgDZxFillPolyDoc();
	DECLARE_DYNCREATE(CcgDZxFillPolyDoc)

// ����
public:
	int wm_width, wm_height;
	int m_drawMode;
	long FillPointTime;
	long ScanLineTime;		//ʱ��
	long SeedFillTime;
	bool FillPointDrawed;
	bool ScanLineDrawed;	//�Ƿ�ʹ�ù��㷨
	bool SeedFillDrawed;
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
	virtual ~CcgDZxFillPolyDoc();
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
