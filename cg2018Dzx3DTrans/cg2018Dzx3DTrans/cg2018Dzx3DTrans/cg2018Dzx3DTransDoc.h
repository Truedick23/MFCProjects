
// cg2018Dzx3DTransDoc.h : Ccg2018Dzx3DTransDoc 类的接口
//


#pragma once

#include "TypeDefine.h"

// Trans Object Select No.
#define BALL     0
#define CUBE     1
#define TRIANGLE 2
#define EYE      3
#define LIGHT0   4
#define LIGHT1   5
#define SCENE    6

#define SPACEOBJECTS 16

class Ccg2018Dzx3DTransDoc : public CDocument
{
protected: // 仅从序列化创建
	Ccg2018Dzx3DTransDoc();
	DECLARE_DYNCREATE(Ccg2018Dzx3DTransDoc)

// 特性
public:
	float m_translateVector[3];
	float m_xAngle,m_yAngle,m_zAngle;

	BOOL m_selfRotate;
	int m_transDir,m_transMode,m_transSelect;

	float eyeX,eyeY,eyeZ;
	float BallCx, BallCy, BallCz;
	float winLx,winLy,winRx,winRy;    // window on XOY project plane

	float ballRadius;
	float zBack, zFront;

	float clipCubeBackLB[3], clipCubeBackRB[3];
	float clipCubeBackLT[3], clipCubeBackRT[3];
	float clipCubeFrontLB[3], clipCubeFrontRB[3];
	float clipCubeFrontLT[3], clipCubeFrontRT[3];
	float winLpaneM,winRpaneM,winBpaneM,winTpaneM;

	int      m_objectNum;
	Object_t m_spaceObjects[SPACEOBJECTS];       // Space Object Buffer

	// Camera view model parameters.
	float m_viewDistance;                   // View distance
	float m_refX,m_refY,m_refZ;             // View reference point
	float m_viewX,m_viewY,m_viewZ;          // View direction
	float m_viewUpX,m_viewUpY,m_viewUpZ;    // View Up direction

	BOOL  m_onLight,m_onShade, autoplay_control;;
	int   nrLights,shinePara;
	float lightX[5], lightY[5], lightZ[5];
	float ambientLight, pointLight, reflectPara,refractPara;
	CString infomation;
	float m_DrawSceneRunTime;
// 操作
public:
	void pCreateBall();
	void pCreateBall(int Num, float Dx, float Dy, float Dz);
	void pCreateCube();
	void pCreateClipBox();
	void pCreateTriangle();

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
	virtual ~Ccg2018Dzx3DTransDoc();
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
