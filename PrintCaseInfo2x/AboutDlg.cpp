// AboutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PrintCaseInfo2x.h"
#include "AboutDlg.h"


// CAboutDlg �Ի���

IMPLEMENT_DYNAMIC(CAboutDlg, CDialog)

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{

}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_QQ, m_QQLink);
	DDX_Control(pDX, IDC_STATIC_GMAIL, m_GmailLink);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CAboutDlg ��Ϣ�������

BOOL CAboutDlg::OnInitDialog()
{
//	extern const int appMarjorVersion ;
//extern const int appMinjorVersion ;
	CDialog::OnInitDialog();
	CString version ;
	version.Format(_T("[%d.%d ��]"),appMarjorVersion,appMinjorVersion);
		//= CString( "V"+appMarjorVersion);
	//version.Append(CString("."+appMinjorVersion));
	TRACE(version);
	GetDlgItem(IDC_STATIC_VERSION)->SetWindowText( version );
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_GmailLink.SetURL( _T("mailto:Gyk001@Gmail.com?subject=����ֳҽѧ������ӡ����ʹ�÷���"));
	m_QQLink.SetURL( _T("tencent://message/?uin=644655955"));


	_Init(&bp, AfxGetInstanceHandle(), GetDlgItem(IDC_STATIC_MESSAGE)->m_hWnd, IDB_BITMAP_ABOUT); 
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CDialog::OnMouseMove(nFlags, point);
}
