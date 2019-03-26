
// cgDzxFillPolyDoc.h : CcgDzxFillPolyDoc ��Ľӿ�
//


#pragma once


class CcgDzxFillPolyDoc : public CDocument
{
protected: // �������л�����
	CcgDzxFillPolyDoc();
	DECLARE_DYNCREATE(CcgDzxFillPolyDoc)

// ����
public:
	int wm_height;
	int wm_width;
	int m_drawMode;
	double FillPointTime;
	double ScanLineTime;
	double SeedFillTime;
	bool FillPointDrawed;
	bool ScanLineDrawed;
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
	virtual ~CcgDzxFillPolyDoc();
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
