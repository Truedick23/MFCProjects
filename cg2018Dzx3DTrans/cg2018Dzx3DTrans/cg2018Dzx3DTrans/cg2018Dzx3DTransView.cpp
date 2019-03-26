
// cg2018Dzx3DTransView.cpp : Ccg2018Dzx3DTransView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "cg2018Dzx3DTrans.h"
#endif

#include "gl\gl.h"
#include "gl\glu.h"

#include "cg2018Dzx3DTransDoc.h"
#include "cg2018Dzx3DTransView.h"
#include "DrawScene.h"
#include "CameraView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ccg2018Dzx3DTransView

IMPLEMENT_DYNCREATE(Ccg2018Dzx3DTransView, CView)

BEGIN_MESSAGE_MAP(Ccg2018Dzx3DTransView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Ccg2018Dzx3DTransView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_AUTOPLAY, &Ccg2018Dzx3DTransView::OnAutoplay)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// Ccg2018Dzx3DTransView ����/����

Ccg2018Dzx3DTransView::Ccg2018Dzx3DTransView()
{
	// TODO: �ڴ˴���ӹ������
	m_drawScene = new CDrawScene(this);
	m_cameraView = new CCameraView(this);
}

Ccg2018Dzx3DTransView::~Ccg2018Dzx3DTransView()
{
}

BOOL Ccg2018Dzx3DTransView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// Ccg2018Dzx3DTransView ����

void Ccg2018Dzx3DTransView::OnDraw(CDC* /*pDC*/)
{
	Ccg2018Dzx3DTransDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	DrawScene();

	CString m_stringinfo = _T("");
	CString timeEbuf;
	timeEbuf.Format(_T("%dms "), pDoc->m_DrawSceneRunTime+10);
	m_stringinfo = _T("Draw Scene Time = " + timeEbuf);

	pDoc->infomation = m_stringinfo;
	UpdateData(FALSE);
}


// Ccg2018Dzx3DTransView ��ӡ


void Ccg2018Dzx3DTransView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Ccg2018Dzx3DTransView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void Ccg2018Dzx3DTransView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void Ccg2018Dzx3DTransView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void Ccg2018Dzx3DTransView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Ccg2018Dzx3DTransView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Ccg2018Dzx3DTransView ���

#ifdef _DEBUG
void Ccg2018Dzx3DTransView::AssertValid() const
{
	CView::AssertValid();
}

void Ccg2018Dzx3DTransView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ccg2018Dzx3DTransDoc* Ccg2018Dzx3DTransView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ccg2018Dzx3DTransDoc)));
	return (Ccg2018Dzx3DTransDoc*)m_pDocument;
}
#endif //_DEBUG


// Ccg2018Dzx3DTransView ��Ϣ�������
BOOL Ccg2018Dzx3DTransView::bSetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,               // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int pixelformat;

	if ( (pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0 )	{
		MessageBox(_T("ChoosePixelFormat failed"));
		return FALSE;
	}

	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)	{
		MessageBox(_T("SetPixelFormat failed"));
		return FALSE;
	}

	return TRUE;
}


int Ccg2018Dzx3DTransView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	PIXELFORMATDESCRIPTOR pfd;
	int         n;
	HGLRC       hrc;
	GLfloat      fAspect;

	m_pDC = new CClientDC(this);

	ASSERT(m_pDC != NULL);

	if (!bSetupPixelFormat()) return 0;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

	//	CreateRGBPalette();

	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

	glClearDepth(100.0f);
	glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	GetClientRect(&m_viewRect);

	if (!m_viewRect.bottom)	fAspect = 1.0f;
	else                    fAspect = (GLfloat)m_viewRect.right/m_viewRect.bottom;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, fAspect, 3.0f, 7.0f);
	glMatrixMode(GL_MODELVIEW);

	return 0;
}

void Ccg2018Dzx3DTransView::DrawScene()
{
	static BOOL bBusy = FALSE;
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	if (bBusy)	return;

	bBusy = TRUE;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(pDoc->m_translateVector[0], 
		         pDoc->m_translateVector[1],
		         pDoc->m_translateVector[2]);
	glRotatef(pDoc->m_xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(pDoc->m_yAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(pDoc->m_zAngle, 0.0f, 0.0f, 1.0f);
	glScalef(0.3f, 0.3f, 0.3f);   /* Make Scene Smaller Enough to Look */	

 	if (m_drawScene) m_drawScene->DrawScene();
 	if (m_cameraView) m_cameraView->DrawScene();

	glPopMatrix();

	glFinish();
	SwapBuffers(wglGetCurrentDC());

	bBusy = FALSE;

	// Notify CCgTransControl can process the Project Result to PictureBox 'PROJECTPANE'
	//	if (pDoc->rayTraceSelect != CVIEWRAYTRACE) 
	pDoc->UpdateAllViews(this);
}

void Ccg2018Dzx3DTransView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (cy > 0)
	{
		glViewport(0, 0, cx, cy);

		if((m_viewRect.right > cx) || (m_viewRect.bottom > cy))
			RedrawWindow();

		m_viewRect.right = cx;
		m_viewRect.bottom = cy;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLdouble)cx/cy, 3.0f, 7.0f);
		glMatrixMode(GL_MODELVIEW);
	}				
}

BOOL m_autoPlay = FALSE;

void Ccg2018Dzx3DTransView::OnAutoplay()
{
	m_autoPlay = !m_autoPlay;

	if (m_autoPlay) SetTimer(1, 50, NULL);
	else            KillTimer(1);
}


void Ccg2018Dzx3DTransView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DrawScene();

	CView::OnTimer(nIDEvent);
}


void Ccg2018Dzx3DTransView::OnOnlight()
{
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	pDoc->m_onLight = !pDoc->m_onLight;
}


void Ccg2018Dzx3DTransView::OnOnshade()
{
	Ccg2018Dzx3DTransDoc* pDoc = (Ccg2018Dzx3DTransDoc*)GetDocument();

	pDoc->m_onShade = !pDoc->m_onShade;
}
