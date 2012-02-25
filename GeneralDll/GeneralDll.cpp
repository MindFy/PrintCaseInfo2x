// GeneralDll.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include <afxdllx.h>
#ifdef _MANAGED
#error ���Ķ� GeneralDll.cpp �е�˵����ʹ�� /clr ���б���
// ���Ҫ��������Ŀ����� /clr������ִ�����в���:
//	1. �Ƴ������� afxdllx.h �İ���
//	2. ��û��ʹ�� /clr ���ѽ���Ԥ����ͷ��
//	   ��Ŀ���һ�� .cpp �ļ������к��������ı�:
//			#include <afxwin.h>
//			#include <afxdllx.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static AFX_EXTENSION_MODULE GeneralDllDLL = { NULL, NULL };

#ifdef _MANAGED
#pragma managed(push, off)
#endif

#include "MyComboBox.h"
#include "MyPreviewView.h"
#include "CascadeInt.h"
#include "CascadeString.h"
#include "SplashWnd.h"

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// ���ʹ�� lpReserved���뽫���Ƴ�
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("GeneralDll.DLL ���ڳ�ʼ��!\n");
		
		// ��չ DLL һ���Գ�ʼ��
		if (!AfxInitExtensionModule(GeneralDllDLL, hInstance))
			return 0;

		// ���� DLL ���뵽��Դ����
		// ע��: �������չ DLL ��
		//  MFC ���� DLL (�� ActiveX �ؼ�)��ʽ���ӵ���
		//  �������� MFC Ӧ�ó������ӵ�������Ҫ
		//  �����д� DllMain ���Ƴ������������һ��
		//  �Ӵ���չ DLL �����ĵ����ĺ����С�ʹ�ô���չ DLL ��
		//  ���� DLL Ȼ��Ӧ��ʽ
		//  ���øú����Գ�ʼ������չ DLL������
		//  CDynLinkLibrary ���󲻻ḽ�ӵ�
		//  ���� DLL ����Դ���������������ص�
		//  ���⡣

		new CDynLinkLibrary(GeneralDllDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("GeneralDll.DLL ������ֹ!\n");

		// �ڵ�����������֮ǰ��ֹ�ÿ�
		AfxTermExtensionModule(GeneralDllDLL);
	}
	return 1;   // ȷ��
}

extern "C" AFX_EXT_API CWnd* ShowSplashWnd()
{
	CSplashWnd *m_pSplashWnd;				//�����������洰�ڱ���
	m_pSplashWnd = new CSplashWnd();		//����һ������ʵ��
	m_pSplashWnd ->ShowWindow(SW_SHOW);	//��ʾ����
	m_pSplashWnd ->UpdateWindow();
	return m_pSplashWnd;
}

extern "C" AFX_EXT_API BOOL QuitSplashWnd(CWnd *pSplashWnd)
{
	if ( pSplashWnd)
	{
		((CSplashWnd *)pSplashWnd)->QuitSplashWnd();
		return TRUE;
	}
	return FALSE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

