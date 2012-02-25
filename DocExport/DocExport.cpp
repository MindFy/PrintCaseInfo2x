// DocExport.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include <afxdllx.h>
#include "WordTools.h"
#include "Resource.h"
#ifdef _MANAGED
#error ���Ķ� DocExport.cpp �е�˵����ʹ�� /clr ���б���
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


static AFX_EXTENSION_MODULE DocExportDLL = { NULL, NULL };

#ifdef _MANAGED
#pragma managed(push, off)
#endif

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// ���ʹ�� lpReserved���뽫���Ƴ�
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("DocExport.DLL ���ڳ�ʼ��!\n");
		
		// ��չ DLL һ���Գ�ʼ��
		if (!AfxInitExtensionModule(DocExportDLL, hInstance))
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



	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("DocExport.DLL ������ֹ!\n");

		// �ڵ�����������֮ǰ��ֹ�ÿ�
		AfxTermExtensionModule(DocExportDLL);
	}
	return 1;   // ȷ��
}

extern "C" AFX_API_EXPORT BOOL InitDocExportDLL()
{
	new CDynLinkLibrary(DocExportDLL);
	AfxEnableControlContainer();   
	_AFX_THREAD_STATE* pState = AfxGetThreadState();
	if(!pState->m_bNeedTerm)    
		return AfxOleInit();
	else
		return TRUE;
}



bool ResToFile(int ResID, CString ResKind, CString &fileName)
{
	HRSRC  res=::FindResource(DocExportDLL.hModule,  MAKEINTRESOURCE(ResID),  ResKind);
	HGLOBAL  gl=::LoadResource(DocExportDLL.hModule,res);
	LPVOID  lp=::LockResource(gl);   //  ���ң����أ�������Դ  

	CString strFilePath;
	CString strFileName;
	GetTempPath(MAX_PATH, strFilePath.GetBuffer(MAX_PATH));
	strFilePath.ReleaseBuffer();
	GetTempFileName(strFilePath,_T("Guo"),0,strFileName.GetBuffer(MAX_PATH));
	strFileName.ReleaseBuffer();

	HANDLE fp=::CreateFile(strFileName,
		GENERIC_WRITE,
		FILE_SHARE_READ ,
		NULL,
		CREATE_ALWAYS, 
		0, 
		NULL);  

	DWORD aa;              
	if (!::WriteFile (fp,lp,::SizeofResource(DocExportDLL.hModule,res),&aa,NULL))
	{
		return false;      //sizeofResource �õ���Դ�ļ��Ĵ�С 
	}

	::CloseHandle (fp);       //�رվ��
	::FreeResource (gl);     //�ͷ��ڴ�
	fileName = strFileName;
	return true;
}
/*
extern "C" AFX_API_EXPORT UINT ExportToDoc2_0()
{

	CString strDotName;
	//CHAR szSknName [ MAX_PATH ];
	if( !ResToFile( IDR_PCI_DOT,_T("DOT"), strDotName))
	{
		//AfxMessageBox(_T("d"));
		return FALSE;
	}	
	CWordTools wdt;
	wdt.Create(strDotName);
	wdt.BookmarkText(TOSTRING(FEMALE_NAME),TOSTRING(FEMALE_NAME));
	wdt.SaveDocumentAs(_T("C:/a.doc"));
	return 0;
}
*/


#ifdef _MANAGED
#pragma managed(pop)
#endif

