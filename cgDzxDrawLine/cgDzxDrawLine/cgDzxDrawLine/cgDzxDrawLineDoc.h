
// cgDzxDrawLineDoc.h : CcgDzxDrawLineDoc ��Ľӿ�
//


#pragma once


class CcgDzxDrawLineDoc : public CDocument
{
protected: // �������л�����
	CcgDzxDrawLineDoc();
	DECLARE_DYNCREATE(CcgDzxDrawLineDoc)

// ����
public:
	int wm_width;   //���ڿ��
	int wm_height;	//���ڸ߶�
	int m_displayMode;	//��ͼ��ѡ��
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
	virtual ~CcgDzxDrawLineDoc();
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
public:
	float DDALineAverageError;
	float BLineAverageError;		//���
	float DDALineSmooth;
	float BLineSmooth;
	float MidpointLineSmooth;		//�⻬��
	int DDALineTime;
	int BLineTime;
	int MidPointTime;				//����ʱ��
	bool DDAdrawed;
	bool BLineDrawed;
	bool MidPointDrawed;			//�Ƿ��Ѿ�����
};
