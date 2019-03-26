#pragma once

#include "TypeDefine.h"
#include "cg2018Dzx3DTransDoc.h"
#include "cg2018Dzx3DTransView.h"
#include <glut.h>

class CDrawScene
{
public:
	CDrawScene(void);
	~CDrawScene(void);
	CDrawScene(Ccg2018Dzx3DTransView* pView);

	void DrawScene();

private:
	int      m_objNumber;
	Object_p m_whoObject;           // Object pointer
	Ccg2018Dzx3DTransView* m_pView;
	float glObjColor[SPACEOBJECTS][3];

	//	float xCenter,yCenter,zCenter;

	void CaculateMatrix();
	void DrawBackground();

	void DrawRect(Gpoint_t p1, Gpoint_t p2, Gpoint_t p3, Gpoint_t p4, GLfloat* color, int width);
	void DrawCube(GLfloat* color, int width);
	void DrawSphere(double R, int n, GLfloat *color, int width);
	void DrawOblong(double Rx, double Ry, double Rz, int n, GLfloat* color, int width);
	void DrawTorus(double R, double R0, int nlong, int nlat, GLfloat* color, int width);

	void DrawSpaceObject();
	void TransSpaceObject();

	void projectSpaceObject();

	void rotateX3Dmatrix(float S, float C);
	void rotateY3Dmatrix(float S, float C);
	void rotateZ3Dmatrix(float S, float C);
	void translate3DMatrix(float dx, float dy, float dz);

 	void pRemoveBackFace();
// 
	void pClipSpaceObject();
	int pVisible(float x, float y, float z, int pane);
	int outPut(float x, float y, float z, int *outCount, Gpoint_p polyClip);
	int pLineCrossPane(float sx, float sy, float sz,
		               float px, float py, float pz, int pane);
	int pLineInterSectPane(float sx, float sy, float sz, 
		                   float px, float py, float pz,
		                   int pane, int *outCount, Gpoint_p polyClip);
// 
	void pObjectCenter();
	void pLightSpaceBall();
	void pLightSpaceObject();
	float xCenter,yCenter,zCenter;

};

