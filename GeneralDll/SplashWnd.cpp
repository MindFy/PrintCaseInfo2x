#include <stdafx.h>
#include "SplashWnd.h"
#include "Resource.h"
//////////////////////////////////////////////////////////////////////////////
//CSplashWnd��Ϣѭ��
BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////
//CSplashWnd���캯��
CSplashWnd::CSplashWnd()
{
	bitmap.LoadBitmap(IDB_SPLASH);						//����λͼ��Դ
	bitmap.GetBitmap(&mapInfo);						//��ȡλͼ��Ϣ
	
	//
	//ע��WNDCLASS
	//
	CString strWndClass;

	strWndClass = AfxRegisterWndClass(
		NULL,
		AfxGetApp() ->LoadStandardCursor(IDC_ARROW),
		NULL,
		NULL);

#ifdef _DEBUG //����״̬����TOPMOST���ԣ��������
	DWORD exStyle = WS_EX_TOOLWINDOW ;
#else
	DWORD exStyle = WS_EX_TOOLWINDOW  | WS_EX_TOPMOST ;
#endif
	CreateEx( exStyle, strWndClass, NULL, WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT,
		mapInfo.bmWidth, mapInfo.bmHeight,NULL, NULL, NULL );
}

//////////////////////////////////////////////////////////////////////////////
//CSplashWnd��������
CSplashWnd::~CSplashWnd()
{
	
}

//CSplashAlpha���ڽ�����Ϣ����,��ӦWM_CREATE
BOOL CSplashWnd::OnCreate(LPCREATESTRUCT lpcs)
{
	//���н��Դ���
	CenterWindow();
	AnimateWindow(500, AW_BLEND);
	return true;
}

void CSplashWnd::QuitSplashWnd()
{
	//��������
	AnimateWindow(300, AW_BLEND | AW_HIDE);
	PostMessage(WM_CLOSE);
}

//////////////////////////////////////////////////////////////////////////////
//���屳���ػ���Ϣ��������Ӧ��ϢON_ERASEBKGND
BOOL CSplashWnd::OnEraseBkgnd(CDC *pDC)
{
	CDC dcMem;										//�����ڴ��豸
	dcMem.CreateCompatibleDC(pDC);					//ʹ�ڴ��豸��pDC�豸����

	CBitmap *pOldBitmap = dcMem.SelectObject(&bitmap);  //����ԭ���豸���������豸
	//dcMem.TextOut(0,0,_T("ffffffffffffff"));	
	pDC ->BitBlt(0, 0, mapInfo.bmWidth, mapInfo.bmHeight, &dcMem, 0, 0, SRCCOPY);
	//���ڴ��豸����λͼ��pDC�豸
	pDC ->SelectObject(pOldBitmap);					//�ָ�ԭ���豸(ɾ��ԭ���豸)
	return true;
}

void CSplashWnd::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	CWnd::PostNcDestroy();
	//�ͷſռ䣬������Ϊnew
	delete this;
}


