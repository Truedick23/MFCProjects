#pragma once

#include "TypeDefine.h"
#include "cg2018Dzx3DTransDoc.h"

class Ccg2018Dzx3DTransView;

class CCameraView
{
public:
	CCameraView(void);
	~CCameraView(void);
	CCameraView(Ccg2018Dzx3DTransView* pView);

	void DrawScene();

private:
	Ccg2018Dzx3DTransView* m_pView;
	float glObjColor[SPACEOBJECTS][3];

	Object_p m_whoObj_p;     // Object pointer
	int      m_objNumber;    // Object Number

	float viewOx,viewOy,viewOz;                      // View Original Point
	float viewEyex,viewEyey,viewEyez;
	float xAxisX,xAxisY,xAxisZ;                      // View X Axis 
	float yAxisX,yAxisY,yAxisZ;                      // View Y Axis
	float zAxisX,zAxisY,zAxisZ;                      // View Z Axis
	float m_viewTransMatrix[4][3];            // Object view transforms matrix
	float m_reverseTransMatrix[4][3];         // Object view-reverse transforms matrix

	void DrawBackground();

	void ViewTransObject();
	void InitViewTransMatrix();

	void CalculateViewTransMatrix();
	void rotateX3Dmatrix(float S, float C, float transMatrix[4][3]);
	void rotateY3Dmatrix(float S, float C, float transMatrix[4][3]);
	void rotateZ3Dmatrix(float S, float C, float transMatrix[4][3]);
	void translate3dMatrix(float dx, float dy, float dz, float transMatrix[4][3]);
};

