// PrintCaseInfo2x.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "PrintCaseInfo2x.h"
#include "MainFrm.h"
#include "../GeneralDll/GeneralDll.h"
#include "PrintCaseInfo2xDoc.h"
#include "PrintCaseInfoView.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPrintCaseInfo2xApp

BEGIN_MESSAGE_MAP(CPrintCaseInfo2xApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPrintCaseInfo2xApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_NEW, &CPrintCaseInfo2xApp::OnFileNew)
END_MESSAGE_MAP()


// CPrintCaseInfo2xApp ����

CPrintCaseInfo2xApp::CPrintCaseInfo2xApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	TCHAR szStylesPath[_MAX_PATH];
	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		

	m_strStylesPath = szStylesPath;
	int nIndex  = m_strStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		m_strStylesPath = m_strStylesPath.Left(nIndex);
	}
	else {
		m_strStylesPath.Empty();
	}
	m_strStylesPath += _T("\\Styles\\");
}


// Ψһ��һ�� CPrintCaseInfo2xApp ����

CPrintCaseInfo2xApp theApp;
//����汾�� 2.3
const int appMarjorVersion = 2;
const int appMinjorVersion = 3;

//֧�ֵ��ļ��汾�����Ϊ 2.1
const int minSupportMarjorVersion = 2;
const int minSupportMinjorVersion = 1;



const CString fileTypeString = _T("printcaseinfo-yisufuyou");



// CPrintCaseInfo2xApp ��ʼ��

BOOL CPrintCaseInfo2xApp::InitInstance()
{

	SetRegistryKey(_T("PrintCaseInfo"));
	CWnd *pSplashWnd = NULL;
//#ifndef _DEBUG 
	//����ģʽ����ʾ�������棬Ҳ������Ƥ��
	pSplashWnd =	ShowSplashWnd();
	
	CXTPWinDwmWrapper().SetProcessDPIAware();
	XTPSkinManager()->SetApplyOptions(XTPSkinManager()->GetApplyOptions() | xtpSkinApplyMetrics);

	CString style;
	style = GetProfileString(  _T("Settings"), _T("theme") , _T("Office2007.Blue.cjstyles") );
	XTPSkinManager()->LoadSkin(  m_strStylesPath+style );	
	WriteProfileString( _T("Settings") , _T("theme") , style );
//#endif

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	//SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPrintCaseInfo2xDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CPrintCaseInfoView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

		QuitSplashWnd( pSplashWnd);//�˳���������
	// ���á�DDE ִ�С�
	EnableShellOpen();
	//RegisterShellFileTypes(TRUE);

	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;



	//���´��ڱ���
	//TRACE_FUNC();
	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand  ֮����
	// ������/��
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}


// �������жԻ����Ӧ�ó�������
void CPrintCaseInfo2xApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CPrintCaseInfo2xApp ��Ϣ�������




void CPrintCaseInfo2xApp::OnFileNew()
{
	if (m_pMainWnd)
	{	//������Ϣ�����ĵ���Ϣ����ֹ��ͼ���ĵ����ݲ�ͬ��
		m_pMainWnd->SendMessage(WM_UPDATE_DOC_FROM_VIEW );
	}

	CWinApp::OnFileNew();
}

CString CPrintCaseInfo2xApp::GetStylesPath(void)
{
	return m_strStylesPath;
}
