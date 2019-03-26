
// cgDZxFillPolyDoc.h : CcgDZxFillPolyDoc 类的接口
//


#pragma once


class CcgDZxFillPolyDoc : public CDocument
{
protected: // 仅从序列化创建
	CcgDZxFillPolyDoc();
	DECLARE_DYNCREATE(CcgDZxFillPolyDoc)

// 特性
public:
	int wm_width, wm_height;
	int m_drawMode;
	long FillPointTime;
	long ScanLineTime;		//时间
	long SeedFillTime;
	bool FillPointDrawed;
	bool ScanLineDrawed;	//是否使用过算法
	bool SeedFillDrawed;
// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CcgDZxFillPolyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
