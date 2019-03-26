
// cgDzxDrawLineDoc.h : CcgDzxDrawLineDoc 类的接口
//


#pragma once


class CcgDzxDrawLineDoc : public CDocument
{
protected: // 仅从序列化创建
	CcgDzxDrawLineDoc();
	DECLARE_DYNCREATE(CcgDzxDrawLineDoc)

// 特性
public:
	int wm_width;   //窗口宽度
	int wm_height;	//窗口高度
	int m_displayMode;	//画图的选项
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
	virtual ~CcgDzxDrawLineDoc();
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
public:
	float DDALineAverageError;
	float BLineAverageError;		//误差
	float DDALineSmooth;
	float BLineSmooth;
	float MidpointLineSmooth;		//光滑度
	int DDALineTime;
	int BLineTime;
	int MidPointTime;				//运行时间
	bool DDAdrawed;
	bool BLineDrawed;
	bool MidPointDrawed;			//是否已经画过
};
