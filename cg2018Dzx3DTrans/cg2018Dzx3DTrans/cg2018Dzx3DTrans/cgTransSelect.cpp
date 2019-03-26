// cgTransSelect.cpp : 实现文件
//

#include "stdafx.h"
#include "math.h"
#include "CameraView.h"
#include "cg2018Dzx3DTrans.h"
#include "cgTransSelect.h"
#include "cg2018Dzx3DTransDoc.h"


// cgTransSelect

IMPLEMENT_DYNCREATE(cgTransSelect, CFormView)

cgTransSelect::cgTransSelect()
	: CFormView(cgTransSelect::IDD)
{
	m_transObj = 0;	
	vcObjColor[BALL] = RGB(255,   0, 0);
	vcObjColor[CUBE] = RGB(  0, 255, 0);
	vcObjColor[TRIANGLE] = RGB( 0, 0, 255);
}

cgTransSelect::~cgTransSelect()
{
}

void cgTransSelect::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_TRANSOBJ, m_transObj);
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();
	DDX_Text(pDX,IDC_INFO, pDoc->infomation);
}

BEGIN_MESSAGE_MAP(cgTransSelect, CFormView)
	ON_BN_CLICKED(IDC_ZBACK, &cgTransSelect::OnBnClickedZback)
	ON_BN_CLICKED(IDC_TRANSMODE, &cgTransSelect::OnBnClickedTransmode)
	ON_BN_CLICKED(IDC_YUP, &cgTransSelect::OnBnClickedYup)
	ON_BN_CLICKED(IDC_XLEFT, &cgTransSelect::OnBnClickedXleft)
	ON_BN_CLICKED(IDC_ZFRONT, &cgTransSelect::OnBnClickedZfront)
	ON_BN_CLICKED(IDC_YDOWN, &cgTransSelect::OnBnClickedYdown)
	ON_BN_CLICKED(IDC_XRIGHT, &cgTransSelect::OnBnClickedXright)
	ON_CBN_SELCHANGE(IDC_TRANSOBJ, &cgTransSelect::OnCbnSelchangeTransobj)
	ON_BN_CLICKED(IDC_AUTO, &cgTransSelect::OnBnClickedAuto)
	ON_BN_CLICKED(ID_ONSHADE, &cgTransSelect::OnBnClickedOnshade)
	ON_BN_CLICKED(ID_ONLIGHT, &cgTransSelect::OnBnClickedOnlight)
END_MESSAGE_MAP()


// cgTransSelect 诊断

#ifdef _DEBUG
void cgTransSelect::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void cgTransSelect::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// cgTransSelect 消息处理程序


void cgTransSelect::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}

#define OFFSET      0.5f
#define DELTAANGLE  5.0f

void cgTransSelect::OnBnClickedZback()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	if (pDoc->m_transSelect == SCENE) {           // Scene Trans
		if (pDoc->m_transMode == 0) pDoc->m_translateVector[2] -= OFFSET;
		else                        pDoc->m_zAngle -= DELTAANGLE;
 	} else if (pDoc->m_transSelect == LIGHT0) {     // Light0 Trans
 		pDoc->lightZ[0] -= OFFSET;
 	} else if (pDoc->m_transSelect == LIGHT1) {   // Light1 Trans
 		pDoc->lightZ[1] -= OFFSET;
	} else if (pDoc->m_transSelect == EYE) {      // Eye Trans
 		pDoc->eyeZ -= OFFSET;
		//pDoc->pCreateClipBox();
	} else	pDoc->m_transDir = 5;

	pDoc->UpdateAllViews(this);
}


void cgTransSelect::OnBnClickedTransmode()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton *pButton = (CButton *)GetDlgItem(IDC_TRANSMODE);
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	pDoc->m_transMode++;
	pDoc->m_transMode %= 2;

	if (pDoc->m_transMode == 0) pButton->SetWindowText(_T("Move"));
	else                        pButton->SetWindowText(_T("Rotate"));
}


void cgTransSelect::OnBnClickedYup()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	if (pDoc->m_transSelect == SCENE) {           // Scene Trans
		if (pDoc->m_transMode == 0) pDoc->m_translateVector[1] += OFFSET;
		else                        pDoc->m_yAngle += DELTAANGLE;
 	} else if (pDoc->m_transSelect == LIGHT0) {     // Light0 Trans
 		pDoc->lightY[0] += OFFSET;
 	} else if (pDoc->m_transSelect == LIGHT1) {   // Light1 Trans
 		pDoc->lightY[1] += OFFSET;
	} else if (pDoc->m_transSelect == EYE) {      // Eye Trans
		pDoc->eyeY += OFFSET;
		//pDoc->pCreateClipBox();
	} else	pDoc->m_transDir = 3;

	pDoc->UpdateAllViews(this);
}


void cgTransSelect::OnBnClickedXleft()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	if (pDoc->m_transSelect == SCENE) {           // Scene Trans
		if (pDoc->m_transMode == 0) pDoc->m_translateVector[0] -= OFFSET;
		else                        pDoc->m_xAngle -= DELTAANGLE;
	} else if (pDoc->m_transSelect == LIGHT0) {     // Light0 Trans
 		pDoc->lightX[0] -= OFFSET;
 	} else if (pDoc->m_transSelect == LIGHT1) {   // Light1 Trans
 		pDoc->lightX[1] -= OFFSET;
	} else if (pDoc->m_transSelect == EYE) {      // Eye Trans
 		pDoc->eyeX -= OFFSET;
		pDoc->pCreateClipBox();
	} else pDoc->m_transDir = 0;

	pDoc->UpdateAllViews(this);
}


void cgTransSelect::OnBnClickedZfront()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	if (pDoc->m_transSelect == SCENE) {           // Scene Trans
		if (pDoc->m_transMode == 0) pDoc->m_translateVector[2] += OFFSET;
		else                        pDoc->m_zAngle += DELTAANGLE;
 	} else if (pDoc->m_transSelect == LIGHT0) {     // Light0 Trans
 		pDoc->lightZ[0] += OFFSET;
 	} else if (pDoc->m_transSelect == LIGHT1) {   // Light1 Trans
 		pDoc->lightZ[1] += OFFSET;
	} else if (pDoc->m_transSelect == EYE) {      // Eye Trans
		pDoc->eyeZ += OFFSET;
		//pDoc->pCreateClipBox();
	} else	pDoc->m_transDir = 4;

	pDoc->UpdateAllViews(this);
}


void cgTransSelect::OnBnClickedYdown()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	if (pDoc->m_transSelect == SCENE) {           // Scene Trans
		if (pDoc->m_transMode == 0) pDoc->m_translateVector[1] -= OFFSET;
		else                        pDoc->m_yAngle -= DELTAANGLE;
 	} else if (pDoc->m_transSelect == LIGHT0) {     // Light0 Trans
 		pDoc->lightY[0] -= OFFSET;
 	} else if (pDoc->m_transSelect == LIGHT1) {   // Light1 Trans
 		pDoc->lightY[1] -= OFFSET;
	} else if (pDoc->m_transSelect == EYE) {      // Eye Trans
 		pDoc->eyeY -= OFFSET;
		//pDoc->pCreateClipBox();
	} else	pDoc->m_transDir = 2;

	pDoc->UpdateAllViews(this);
}


void cgTransSelect::OnBnClickedXright()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	if (pDoc->m_transSelect == SCENE) {           // Scene Trans
		if (pDoc->m_transMode == 0) pDoc->m_translateVector[0] += OFFSET;
		else                        pDoc->m_xAngle += DELTAANGLE;
 	} else if (pDoc->m_transSelect == LIGHT0) {     // Light0 Trans
 		pDoc->lightX[0] += OFFSET;
 	} else if (pDoc->m_transSelect == LIGHT1) {   // Light1 Trans
 		pDoc->lightX[1] += OFFSET;
	} else if (pDoc->m_transSelect == EYE) {      // Eye Trans
 		pDoc->eyeX += OFFSET;
		pDoc->pCreateClipBox();
	} else	pDoc->m_transDir = 1;

	pDoc->UpdateAllViews(this);
}


void cgTransSelect::OnCbnSelchangeTransobj()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	UpdateData(TRUE);

	pDoc->m_transSelect = m_transObj;

	UpdateData(FALSE);
}


void cgTransSelect::OnBnClickedAuto()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();
	pDoc->autoplay_control = !pDoc->autoplay_control;
	pDoc->UpdateAllViews(this);
}


void cgTransSelect::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();
	CStatic *prjPlane =(CStatic *)GetDlgItem(IDC_VIEWPORT);

	CDC     *prjPlaneCDC;
	CRect    prjPlaneRet;

	AssertValid();

		DWORD  opStart,opFinish;

	opStart = GetTickCount();       // 记录测试开始时间，单位是毫秒
	//	UpdateData(TRUE);

	prjPlaneCDC = prjPlane->GetDC();
	prjPlane->GetClientRect(&prjPlaneRet); 

	// Clear BackGround of DC
	CBrush brBlack(RGB(0, 0, 0));
	prjPlaneCDC->FillRect(prjPlaneRet, &brBlack);	


	// Initial the Z-Buffer prjPlaneRetZ
	for (int i = 0; i < PRJPLANERETHEIGHT; i++)
		for (int j = 0; j < PRJPLANERETWIDTH; j++)
			prjPlaneRetZ[i][j] = -100.0f;

	m_objNumber = 0;
	for (m_objNumber = pDoc->m_objectNum-1; m_objNumber >= 0 ; m_objNumber--) { 

		m_whoObject = &pDoc->m_spaceObjects[m_objNumber];

 		pTransToZbuffer(prjPlaneRet);
// 		pDrawLineObject(prjPlaneCDC, prjPlaneRet);

		if (pDoc->m_spaceObjects[m_objNumber].objectVisible) { 
			if (pDoc->m_onLight) {
				float maxShade,minShade;

				maxShade = -100.0f;    minShade = 100.0f;
				for (int i = 0; i < m_whoObject->polyCount; i++)
					if (m_whoObject->objectSpace[i].polyVisible) {
						for (int j = 0; j < m_whoObject->objectSpace[i].clipCount; j++) {
							if (m_whoObject->objectSpace[i].polyLight[j] > maxShade)
								maxShade = m_whoObject->objectSpace[i].polyLight[j];
							if (m_whoObject->objectSpace[i].polyLight[j] < minShade)
								minShade = m_whoObject->objectSpace[i].polyLight[j];
						}
					}
					if (!pDoc->m_onShade) pDrawLightObject(prjPlaneCDC, prjPlaneRet, maxShade, minShade);
					else                  pDrawShadeLightObject(prjPlaneCDC, prjPlaneRet, maxShade, minShade);
					//	             pDrawLightObject(prjPlaneCDC, prjPlaneRet, maxShade, minShade);
			} else {
				pDrawLineObject(prjPlaneCDC, prjPlaneRet);
			} 
		} 

	}
	opFinish = GetTickCount();      //记录测试结束时间，单位是毫秒

	CString opTimeStr;
	CStatic* drawSceneTime = (CStatic*)GetDlgItem(IDC_INFO);

	opTimeStr.Format(_T("DrawScene Run-Time: %.6fs"),pDoc->m_DrawSceneRunTime);
	drawSceneTime->SetWindowTextW(opTimeStr);
	// Must remember to release prjPlaneCDC every time after using.
	ReleaseDC(prjPlaneCDC);
}

void cgTransSelect::pTransToZbuffer(CRect dcRect)
{
	int i,j;
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	float vxScale = (float)dcRect.right / (pDoc->winRx - pDoc->winLx);
	float vyScale = (float)dcRect.bottom / (pDoc->winRy - pDoc->winLy);
	for (i = 0; i < m_whoObject->polyCount; i++) {
		if (m_whoObject->objectSpace[i].polyVisible) {
			for (j = 0; j < m_whoObject->objectSpace[i].clipCount; j++) {
				m_whoObject->objectSpace[i].zBufferObject[j].x  = 
					(int)((m_whoObject->objectSpace[i].projectObject[j].x - pDoc->winLx) * 
					       vxScale + 0.5f);
				m_whoObject->objectSpace[i].zBufferObject[j].y = dcRect.bottom -
					(int)((m_whoObject->objectSpace[i].projectObject[j].y - pDoc->winLy) * 
					       vyScale + 0.5f);
			}
		}
	}
}


void cgTransSelect::pDrawLineObject(CDC *pDC, CRect dcRect)
{
	CPen newPen;
	CPen *oldPen;
	int i,j,x1,y1,x2,y2;
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	if (m_objNumber >= 3)
		newPen.CreatePen(PS_SOLID, 1, vcObjColor[BALL]);
	else 
		newPen.CreatePen(PS_SOLID, 1, vcObjColor[m_objNumber]);

	oldPen = (CPen *)pDC->SelectObject(&newPen);

	// Draw Object in DC
	for (i = 0; i < m_whoObject->polyCount; i++) {
		if (m_whoObject->objectSpace[i].polyVisible) {
			x1 = m_whoObject->objectSpace[i].zBufferObject[0].x;
			y1 = m_whoObject->objectSpace[i].zBufferObject[0].y;
			for (j = 1; j < m_whoObject->objectSpace[i].clipCount; j++) {
				x2 = m_whoObject->objectSpace[i].zBufferObject[j].x;
				y2 = m_whoObject->objectSpace[i].zBufferObject[j].y;
				// draw a line
				pDC->MoveTo(x1, y1);
				pDC->LineTo(x2, y2);
				x1 = x2;           
				y1 = y2;
			}
		}
	}

	pDC->SelectObject(oldPen);
	newPen.DeleteObject();
}

void cgTransSelect::pDrawLightObject(CDC *pDC, CRect dcRect, float maxShade, float minShade) 
{
	CRgn rgn;	
	CBrush br;
	int i,j,color;
	float shadeValue;
	tagPOINT Point[10];
	Ccg2018Dzx3DTransDoc *pDoc = (Ccg2018Dzx3DTransDoc *)GetDocument();

	// Draw Object in DC
	float shadeWidth = maxShade - minShade;
	for (i = 0; i < m_whoObject->polyCount; i++) {
		if (m_whoObject->objectSpace[i].polyVisible) {
			for (j = 0; j < m_whoObject->objectSpace[i].clipCount; j++) {
				Point[j].x = m_whoObject->objectSpace[i].zBufferObject[j].x;
				Point[j].y = m_whoObject->objectSpace[i].zBufferObject[j].y;
			}

			float sum = 0;
			for (int k = 0; k < 4; k++) sum += m_whoObject->objectSpace[i].polyLight[k];

			shadeValue = sum / 4.0f;
					color = (int) (200 * (shadeValue - minShade) / (maxShade - minShade)) + 55;
			//color = (int) (255 * (shadeValue - minShade) / shadeWidth);
			if (color > 255) color = 255;

			switch (m_objNumber) {
			case BALL: br.CreateSolidBrush(RGB(color, 0, 0)); break;
			case CUBE: br.CreateSolidBrush(RGB(0, color, 0)); break;
			case TRIANGLE: br.CreateSolidBrush(RGB(0 , 0, color)); break;
			default:br.CreateSolidBrush(RGB(color, 0, 0)); break;
			}

			rgn.CreatePolygonRgn(Point,m_whoObject->objectSpace[i].clipCount, WINDING);
			pDC->FillRgn(&rgn, &br);

			br.DeleteObject();
			rgn.DeleteObject();
		}
	}
}

void cgTransSelect::pDrawShadeLightObject(CDC *pDC, CRect dcRect, float maxShade, float minShade) 
{
    int i,j,color[10];
    float shadeValue;
    int  x[10], y[10];
    Ccg2018Dzx3DTransDoc *pDoc = (Ccg2018Dzx3DTransDoc *)GetDocument();

	float shadeWidth = maxShade - minShade;
	// Draw Object in DC
    for (i = 0; i < m_whoObject->polyCount; i++) {
	  if (m_whoObject->objectSpace[i].polyVisible) {
        for (j = 0; j < m_whoObject->objectSpace[i].clipCount; j++) {
	      x[j] = m_whoObject->objectSpace[i].zBufferObject[j].x;
	      y[j] = m_whoObject->objectSpace[i].zBufferObject[j].y;

		  shadeValue = m_whoObject->objectSpace[i].polyLight[j];
		  color[j] = (int) (200 * (shadeValue - minShade) / shadeWidth) + 55;
//          color[j] = (int) (255 * (shadeValue - minShade) / shadeWidth);
		  if (color[j] > 255) color[j] = 255;
		} 
		polyCount = i;
		if (m_whoObject->objectSpace[i].clipCount >= 2)
          FillPolygon(pDC,
			          m_whoObject->objectSpace[i].clipCount,
					  x,y,color,dcRect);
	  }
	}
}

void cgTransSelect::FillPolygon(CDC *pDC,
								int n,int *x,int *y,int *color,
								CRect dcRect)
{
	pdges = 0;
	ibegin = iend = 0;
    Loadpolygon(n,x,y,color);
    if (pdges <2 ) return;
    scan = (int)ymax[0];
    Include();
    UpdateXvalue();
    while (ibegin != iend) {
      Fillscan(pDC,dcRect);
      scan--;
      Include();
      UpdateXvalue();
    }
}
 
void cgTransSelect::Loadpolygon(int n,int *x,int *y, int *color)
{
    int i,color1,color2;
    float x1,x2,y1,y2;

	color1 = color[0];
    x1 = (float)x[0];     y1 = y[0] + 0.5f;
    for (i = 1; i < n; i++) {
	  color2 = color[i];
      x2 = (float)x[i];   y2 = y[i] + 0.5f;
      if (y2-y1)   PolyInsert(x1, y1, x2, y2, color1, color2);
      x1 = x2;     y1 = y2;  color1 = color2; 
    }
	color2 = color[0];     
	x2 = (float)x[0];             y2 = y[0] + 0.5f; 
    if (y2-y1)   PolyInsert(x1,y1,x2,y2, color1, color2);
}

void cgTransSelect::PolyInsert(float x1,float y1,float x2,float y2,
							   int color1, int color2)
{
    int i;
    float maxY,minY,slope;

    i = pdges;
    maxY = (y1>y2) ? y1:y2;
    minY = (y1<y2) ? y1:y2;
    while (i > 0 && maxY > ymax[i-1]) {
      ymax[i] = ymax[i-1];
      ymin[i] = ymin[i-1];
      Xa[i] = Xa[i-1];
      Dx[i] = Dx[i-1];
	  Sc[i] = Sc[i-1];
	  Dc[i] = Dc[i-1];
      i--;
    }
    ymax[i] = maxY;
    ymin[i] = minY;
    Dx[i] = (x2-x1) / (y2-y1);
    if (y1 > y2) { Xa[i] = x1; Sc[i] = (float)color1; Dc[i] = (float)color2 - color1; }
    else         { Xa[i] = x2; Sc[i] = (float)color2; Dc[i] = (float)color1 - color2; }
    slope = (float)fabs(1 / (y2 - y1));
	Dc[i] = Dc[i] * slope;
    pdges++;
}

void cgTransSelect::Include()
{
    while (iend < pdges && ymax[iend] > scan) {
      Dx[iend] = -Dx[iend];
      iend++;
    }
}

void cgTransSelect::UpdateXvalue()
{
    int i,j,start;

    start = ibegin;
    for (i = start; i < iend; i++) {
      if (ymin[i] < scan) {
		Sc[i] += Dc[i];
	    Xa[i] += Dx[i];
	    XSort(ibegin,i);
      } else {
	    for (j = i;j > ibegin; j--) {
	      ymin[j]=ymin[j-1];              
	      Xa[j]=Xa[j-1];
	      Dx[j]=Dx[j-1];

		  Sc[j]=Sc[j-1];                   
		  Dc[j]=Dc[j-1];
		}
	    ibegin++;
      }
    }
}

void cgTransSelect::XSort(int begin,int i)
{
    float temp;
    while (i > begin && Xa[i] < Xa[i-1]) {
      temp=ymin[i];  ymin[i]=ymin[i-1];  ymin[i-1]=temp;
      temp=Xa[i];    Xa[i]=Xa[i-1];      Xa[i-1]=temp;
      temp=Sc[i];    Sc[i]=Sc[i-1];      Sc[i-1]=temp;
      temp=Dx[i];    Dx[i]=Dx[i-1];      Dx[i-1]=temp;
      temp=Dc[i];    Dc[i]=Dc[i-1];      Dc[i-1]=temp;

      i--;
    }
}

void cgTransSelect::Fillscan(CDC *pDC,CRect dcRect)
  {
//	float zb,zt;
	float z;
    tagPOINT Point;
    COLORREF rgbColor;
	float dColor,color;
    Ccg2018Dzx3DTransDoc *pDoc = (Ccg2018Dzx3DTransDoc *)GetDocument();

	Point.y = (int)scan;
    for (int i = ibegin; i < iend; i+=2) {
	  color  = Sc[i];
	  dColor = (Sc[i+1] - Sc[i]) / (Xa[i+1] - Xa[i]);
	  for (Point.x = (int)Xa[i]; Point.x < (int)Xa[i+1]; Point.x++) {
		  
//////// Segment for Only Ball and Triangle Hidden processing. //////
/*	
	Object_p objBall_p = &pDoc->m_spaceObjects[BALL];
	Object_p objTriangle_p = &pDoc->m_spaceObjects[TRIANGLE];
		if (pDoc->m_spaceObjects[TRIANGLE].objectVisible) {
		  if (inTriangle((float)Point.x, (float)Point.y)) {
		    zt = CalculateZValue(Point.x, Point.y, dcRect, objTriangle_p, 0);
		    zb = CalculateZValue(Point.x, Point.y, dcRect, objBall_p, polyCount);
            if (zb < zt) rgbColor = RGB(color, 0, 0);
		    else         rgbColor = RGB(color, color, 0); 
		  } else  rgbColor = RGB(color, color, 0); 
		} else 
			rgbColor = RGB(color, color, 0);
*/
///////////////////////////////////////////////////////////////////////	

//////////////// Segment for Normal Hidden processing. ////////////////
		
	    z = CalculateZValue(Point.x, Point.y, dcRect, polyCount);
		if (0 <= Point.x && Point.x <= PRJPLANERETWIDTH && 
			0 <= Point.y && Point.y <= PRJPLANERETHEIGHT) {
		  if (z > prjPlaneRetZ[(int)Point.x][(int)Point.y]) {
			switch (m_objNumber) {
			  case BALL: rgbColor = RGB(color, 0, 0); break;
			  case CUBE: rgbColor = RGB(0, color, 0); break;
			  case TRIANGLE: rgbColor = RGB(0 , 0, color); break;
			  default:rgbColor = RGB(color, 0, 0); break;
			} 
			pDC->SetPixel(Point, rgbColor);	
            prjPlaneRetZ[(int)Point.x][(int)Point.y] = z;
		  } 
		}

///////////////////////////////////////////////////////////////////////	
 
//		rgbColor = RGB(color, color, 0);  // Only for Grouand Shade.
	   		  
//		pDC->SetPixel(Point, rgbColor);	
		color += dColor;//颜色渐变
	  }
	}
}  

//*
float cgTransSelect::CalculateZValue(int x,int y,CRect dcRect,int i)
{
	int j;
	float lx,ly,lz;
	float cx,cy,kx,ky;
	float sx[5],sy[5],sz[5];
	float denominator,space_z;
    float project_x,project_y,project_z=0;
	float n1x,n1y,n1z,n2x,n2y,n2z,fx,fy,fz;
    Ccg2018Dzx3DTransDoc *pDoc = (Ccg2018Dzx3DTransDoc *)GetDocument();
	
	project_x = ((float)x / (float)dcRect.right) + pDoc->winLx;
   	project_y = ((float)dcRect.bottom - (float)y) / (float)dcRect.bottom + pDoc->winLy;
	
	for (j = 0; j < 3; j++)	{
        sx[j] = m_whoObject->objectSpace[i].clipObject[j].x;
		sy[j] = m_whoObject->objectSpace[i].clipObject[j].y;
		sz[j] = m_whoObject->objectSpace[i].clipObject[j].z;
	}
    
	n1x = sx[1] - sx[0];  n1y = sy[1] - sy[0]; n1z = sz[1] - sz[0];
	n2x = sx[2] - sx[0];  n2y = sy[2] - sy[0]; n2z = sz[2] - sz[0];
    
	fx = n1y*n2z - n1z*n2y;
	fy = n1z*n2x - n1x*n2z;
	fz = n1x*n2y - n1y*n2x;
	
	lx = pDoc->eyeX - project_x;
	ly = pDoc->eyeY - project_y;
	lz = pDoc->eyeZ - project_z; 
	
    cx = lx/lz;            cy = ly/lz;
	kx = pDoc->eyeX - cx * pDoc->eyeZ;
	ky = pDoc->eyeY - cy * pDoc->eyeZ;
	
	denominator = fz + fy*cy + fx*cx;
	space_z = ((fx*sx[0] + fy*sy[0] + fz*sz[0])-(fy*ky +fx*kx)) / denominator;
	
	return space_z;
}

void cgTransSelect::OnBnClickedOnshade()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	pDoc->m_onLight = !pDoc->m_onLight;

}


void cgTransSelect::OnBnClickedOnlight()
{
	// TODO: 在此添加控件通知处理程序代码
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	pDoc->m_onShade = !pDoc->m_onShade;
}
