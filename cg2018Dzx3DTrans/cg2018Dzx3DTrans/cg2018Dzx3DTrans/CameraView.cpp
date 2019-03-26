#include "StdAfx.h"
#include "CameraView.h"

#include "math.h"
#include "gl\gl.h"
#include "gl\glu.h"
#include "glut.h"
#include "cg2018Dzx3DTransDoc.h"
#include "cg2018Dzx3DTransView.h"

CCameraView::CCameraView(void)
{
	m_pView = NULL;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			if (i == j) m_viewTransMatrix[i][j] = 1.0;
			else        m_viewTransMatrix[i][j] = 0.0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			if (i == j) m_reverseTransMatrix[i][j] = 1.0;
			else        m_reverseTransMatrix[i][j] = 0.0;

	glObjColor[TRIANGLE][0] = 0.0f;
	glObjColor[TRIANGLE][1] = 0.0f;
	glObjColor[TRIANGLE][2] = 1.0f;
	glObjColor[BALL][0] = 1.0f;  glObjColor[BALL][1] = 0.0f;  glObjColor[BALL][2] = 0.0f;
	glObjColor[CUBE][0] = 0.0f;  glObjColor[CUBE][1] = 1.0f;  glObjColor[CUBE][2] = 0.0f;

}

CCameraView::CCameraView(Ccg2018Dzx3DTransView* pView)
{
	m_pView = pView;
}


CCameraView::~CCameraView(void)
{
}

void CCameraView::DrawScene()
{
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*) m_pView->GetDocument();

	DrawBackground();

	for (m_objNumber = 0; m_objNumber < pDoc->m_objectNum; m_objNumber++) { 

		m_whoObj_p = &pDoc->m_spaceObjects[m_objNumber];

		CalculateViewTransMatrix();

		ViewTransObject();
	}

}

#define LOOKDEPTH 5.5f
#define AXISLENGTH 1.5f

void CCameraView::DrawBackground()
{
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*) m_pView->GetDocument();

	viewEyex = 0.0f;
	viewEyey = 0.0f;
	viewEyez = 3.0f;

	viewOx = pDoc->m_refX - pDoc->m_viewX * pDoc->m_viewDistance;
	viewOy = pDoc->m_refY - pDoc->m_viewY * pDoc->m_viewDistance;
	viewOz = pDoc->m_refZ - pDoc->m_viewZ * pDoc->m_viewDistance;

	zAxisX = viewOx+AXISLENGTH*pDoc->m_viewX;
	zAxisY = viewOy+AXISLENGTH*pDoc->m_viewY;
	zAxisZ = viewOz+AXISLENGTH*pDoc->m_viewZ;

	yAxisX = viewOx+AXISLENGTH*pDoc->m_viewUpX;
	yAxisY = viewOy+AXISLENGTH*pDoc->m_viewUpY;
	yAxisZ = viewOz+AXISLENGTH*pDoc->m_viewUpZ;

	xAxisX =   pDoc->m_viewUpY*pDoc->m_viewZ - pDoc->m_viewY*pDoc->m_viewUpZ;
	xAxisY = -(pDoc->m_viewUpX*pDoc->m_viewZ - pDoc->m_viewX*pDoc->m_viewUpZ);
	xAxisZ =   pDoc->m_viewUpX*pDoc->m_viewY - pDoc->m_viewX*pDoc->m_viewUpY;

	float vLength = sqrtf(xAxisX*xAxisX+xAxisY*xAxisY+xAxisZ*xAxisZ);

	xAxisX = -xAxisX / vLength;
	xAxisY = -xAxisY / vLength;
	xAxisZ = -xAxisZ / vLength;
	xAxisX = viewOx+2.0f*xAxisX;
	xAxisY = viewOy+2.0f*xAxisY;
	xAxisZ = viewOz+2.0f*xAxisZ;

	/* Draw View Space Axis */
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);             // Z Axis     
	glVertex3f(viewOx, viewOy, viewOz);
	glVertex3f(xAxisX, xAxisY, xAxisZ);
	glEnd();
	glColor3f(0.0f, 1.0f, 1.f);
	glBegin(GL_LINE_STRIP);             // Y Axis     
	glVertex3f(viewOx, viewOy, viewOz);
	glVertex3f(yAxisX, yAxisY, yAxisZ);
	glEnd();
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_STRIP);             // Z Axis     
	glVertex3f(viewOx, viewOy, viewOz);
	glVertex3f(zAxisX, zAxisY, zAxisZ);
	glEnd();



	// 	float Offset[3] = {6.0f, 0.0f, -0.1f};
	// 	float Scale[3] = {0.4f, 0.4f, 0.4f};
	// 	float Rotate[3] = {0.0f, 0.0f, 0.0f};  // No rotate
	// 	   
	//     glColor3f(1.0f, 0.0f, 0.0f);
	// 	m_pView->m_axisFont.GLDrawText(Offset, Scale, Rotate, "X");
	// 	
	// 	glColor3f(0.0f, 1.0f, 1.f);
	// 	Offset[0] = 0.0f;  Offset[1] = 6.0f;  Offset[2] = -0.1f;
	// 	m_pView->m_axisFont.GLDrawText(Offset, Scale, Rotate, "Y");
	// 	
	// 	glColor3f(0.0f, 1.0f, 1.0f);
	// 	Rotate[1] = 90.0f;                                             // Around Y 90'
	// 	Offset[0] =-0.1f;  Offset[1] = 0.0f;  Offset[2] =  6.5f;
	// 	m_pView->m_axisFont.GLDrawText(Offset, Scale, Rotate, "Z");



}

void CCameraView::InitViewTransMatrix()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			if (i == j) m_viewTransMatrix[i][j] = 1.0;
			else        m_viewTransMatrix[i][j] = 0.0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			if (i == j) m_reverseTransMatrix[i][j] = 1.0;
			else        m_reverseTransMatrix[i][j] = 0.0;
}

void CCameraView::CalculateViewTransMatrix()
{
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*) m_pView->GetDocument();

	// Calculate view trans matrix.
	float upX,upY,upZ;
	float rSin,rCos,vLength;
	float rotateMatrix[4][3];

	InitViewTransMatrix();
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			if (i == j) rotateMatrix[i][j] = 1.0;
			else        rotateMatrix[i][j] = 0.0;

	translate3dMatrix(-viewOx, -viewOy, -viewOz, m_viewTransMatrix);

	vLength = sqrtf(pDoc->m_viewY*pDoc->m_viewY+pDoc->m_viewZ*pDoc->m_viewZ);
	rSin = -pDoc->m_viewY / vLength;
	rCos = -pDoc->m_viewZ / vLength;
	rotateX3Dmatrix(rSin, rCos, rotateMatrix);
	rotateX3Dmatrix(rSin, rCos, m_viewTransMatrix);

	rSin = -pDoc->m_viewX;
	rCos = vLength;
	rotateY3Dmatrix(-rSin, rCos, rotateMatrix);
	rotateY3Dmatrix(-rSin, rCos, m_viewTransMatrix);

	upX = pDoc->m_viewUpX*rotateMatrix[0][0] + pDoc->m_viewUpY*rotateMatrix[1][0] +
		  pDoc->m_viewUpZ*rotateMatrix[2][0] + rotateMatrix[3][0];
	upY = pDoc->m_viewUpX*rotateMatrix[0][1] + pDoc->m_viewUpY*rotateMatrix[1][1] +
		  pDoc->m_viewUpZ*rotateMatrix[2][1] + rotateMatrix[3][1];
	upZ = pDoc->m_viewUpX*rotateMatrix[0][2] + pDoc->m_viewUpY*rotateMatrix[1][2] +
		  pDoc->m_viewUpZ*rotateMatrix[2][2] + rotateMatrix[3][2];

	vLength = sqrtf(upX*upX+upY*upY);
	rSin = upX / vLength;
	rCos = upY / vLength;
	rotateZ3Dmatrix(rSin, rCos, m_viewTransMatrix);


	rotateZ3Dmatrix(-rSin, rCos, m_reverseTransMatrix);

	vLength = sqrtf(pDoc->m_viewY*pDoc->m_viewY+pDoc->m_viewZ*pDoc->m_viewZ);
	rSin = -pDoc->m_viewX;
	rCos = vLength;

	rotateY3Dmatrix(rSin, rCos, m_reverseTransMatrix);

	rSin = -pDoc->m_viewY / vLength;
	rCos = -pDoc->m_viewZ / vLength;

	rotateX3Dmatrix(-rSin, rCos, m_reverseTransMatrix);

	translate3dMatrix(viewOx, viewOy, viewOz, m_reverseTransMatrix);
}

void CCameraView::translate3dMatrix(float Tx, float Ty, float Tz, float transMatrix[4][3])
{

	transMatrix[3][0] += Tx;
	transMatrix[3][1] += Ty;
	transMatrix[3][2] += Tz;
}

void CCameraView::rotateX3Dmatrix(float S, float C, float transMatrix[4][3])
{

	for (int i = 0; i < 4; i++) {
		float temp;
		temp = transMatrix[i][1]*C - transMatrix[i][2]*S;
		transMatrix[i][2] = transMatrix[i][1]*S + transMatrix[i][2]*C;
		transMatrix[i][1] = temp;
	}

}

void CCameraView::rotateY3Dmatrix(float S, float C, float transMatrix[4][3])
{

	for (int i = 0; i < 4; i++) {
		float temp;
		temp = transMatrix[i][0]*C + transMatrix[i][2]*S;
		transMatrix[i][2] = -transMatrix[i][0]*S + transMatrix[i][2]*C;
		transMatrix[i][0] = temp;
	}

}

void CCameraView::rotateZ3Dmatrix(float S, float C, float transMatrix[4][3])
{

	for (int i = 0; i < 4; i++) {
		float temp;
		temp = transMatrix[i][0]*C - transMatrix[i][1]*S;
		transMatrix[i][1] = transMatrix[i][0]*S + transMatrix[i][1]*C;
		transMatrix[i][0] = temp;
	}

}


void CCameraView::ViewTransObject()
{
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*) m_pView->GetDocument();
	// View Trans Object
	for (int i = 0; i < m_whoObj_p->polyCount; i++) {
		for (int j = 0; j < m_whoObj_p->objectSpace[i].polyCount; j++) {

			m_whoObj_p->objectSpace[i].viewTransObject[j].x = 
				m_whoObj_p->objectSpace[i].transObject[j].x * m_viewTransMatrix[0][0]+
				m_whoObj_p->objectSpace[i].transObject[j].y * m_viewTransMatrix[1][0]+
				m_whoObj_p->objectSpace[i].transObject[j].z * m_viewTransMatrix[2][0]+
				m_viewTransMatrix[3][0];
			m_whoObj_p->objectSpace[i].viewTransObject[j].y = 
				m_whoObj_p->objectSpace[i].transObject[j].x * m_viewTransMatrix[0][1]+
				m_whoObj_p->objectSpace[i].transObject[j].y * m_viewTransMatrix[1][1]+
				m_whoObj_p->objectSpace[i].transObject[j].z * m_viewTransMatrix[2][1]+
				m_viewTransMatrix[3][1];
			m_whoObj_p->objectSpace[i].viewTransObject[j].z = 
				m_whoObj_p->objectSpace[i].transObject[j].x * m_viewTransMatrix[0][2]+
				m_whoObj_p->objectSpace[i].transObject[j].y * m_viewTransMatrix[1][2]+
				m_whoObj_p->objectSpace[i].transObject[j].z * m_viewTransMatrix[2][2]+
				m_viewTransMatrix[3][2];
		}
	}

	// Project object to XOY plane in View Space
	for (int i = 0; i < m_whoObj_p->polyCount; i++) {
		for (int j = 0; j < m_whoObj_p->objectSpace[i].polyCount; j++) {
			m_whoObj_p->objectSpace[i].viewProjectObject[j].x = 
				-(m_whoObj_p->objectSpace[i].viewTransObject[j].x - viewEyex) / 
				(m_whoObj_p->objectSpace[i].viewTransObject[j].z - viewEyez) *
				viewEyez + viewEyex;
			m_whoObj_p->objectSpace[i].viewProjectObject[j].y = 
				-(m_whoObj_p->objectSpace[i].viewTransObject[j].y - viewEyey) / 
				(m_whoObj_p->objectSpace[i].viewTransObject[j].z - viewEyez) *
				viewEyez + viewEyey;
			m_whoObj_p->objectSpace[i].viewProjectObject[j].z = 0.0f;

		}
	}

	// Reverse transform View Space Project object back to original space.
	for (int i = 0; i < m_whoObj_p->polyCount; i++) {
		for (int j = 0; j < m_whoObj_p->objectSpace[i].polyCount; j++) {

			// fill the right code (3-Lines) here ...
			m_whoObj_p->objectSpace[i].viewDrawObject[j].x = 
				m_whoObj_p->objectSpace[i].viewProjectObject[j].x * m_reverseTransMatrix[0][0]+
				m_whoObj_p->objectSpace[i].viewProjectObject[j].y * m_reverseTransMatrix[1][0]+
				m_whoObj_p->objectSpace[i].viewProjectObject[j].z * m_reverseTransMatrix[2][0]+
				m_reverseTransMatrix[3][0];
			m_whoObj_p->objectSpace[i].viewDrawObject[j].y = 
				m_whoObj_p->objectSpace[i].viewProjectObject[j].x * m_reverseTransMatrix[0][1]+
				m_whoObj_p->objectSpace[i].viewProjectObject[j].y * m_reverseTransMatrix[1][1]+
				m_whoObj_p->objectSpace[i].viewProjectObject[j].z * m_reverseTransMatrix[2][1]+
				m_reverseTransMatrix[3][1];
			m_whoObj_p->objectSpace[i].viewDrawObject[j].z = 
				m_whoObj_p->objectSpace[i].viewProjectObject[j].x * m_reverseTransMatrix[0][2]+
				m_whoObj_p->objectSpace[i].viewProjectObject[j].y * m_reverseTransMatrix[1][2]+
				m_whoObj_p->objectSpace[i].viewProjectObject[j].z * m_reverseTransMatrix[2][2]+
				m_reverseTransMatrix[3][2];
		}
	}
	// Draw project result on view plane.
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < m_whoObj_p->polyCount; i++) {
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j < m_whoObj_p->objectSpace[i].polyCount; j++)
			glVertex3f(m_whoObj_p->objectSpace[i].viewDrawObject[j].x,
			m_whoObj_p->objectSpace[i].viewDrawObject[j].y,
			m_whoObj_p->objectSpace[i].viewDrawObject[j].z);
		glEnd();
	}	
}