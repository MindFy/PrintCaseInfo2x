// ConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PrintCaseInfo2x.h"
#include "ConfigDlg.h"


// CConfigDlg �Ի���

IMPLEMENT_DYNAMIC(CConfigDlg, CDialog)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
	, m_strStyle(_T(""))
	, m_VS(0)
{

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STYTLE, ctrlComboStytleFile);
	DDX_CBString(pDX, IDC_COMBO_STYTLE, m_strStyle);
	DDX_CBIndex(pDX, IDC_COMBO_VIEW, m_VS);
	DDX_Control(pDX, IDC_COMBO_VIEW, ctrlComboView);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConfigDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_STYTLE, &CConfigDlg::OnCbnSelchangeComboStyle)
	ON_CBN_SELCHANGE(IDC_COMBO_VIEW, &CConfigDlg::OnCbnSelchangeComboView)
END_MESSAGE_MAP()


// CConfigDlg ��Ϣ�������

void CConfigDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

BOOL CConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString   fileName;   
	CFileFind   m_find;   
	ctrlComboStytleFile.AddString( _T("�޷��"));   
	if(m_find.FindFile( theApp.GetStylesPath()+_T("*.cjstyles") , 0 ) )   
	{   
		while(m_find.FindNextFile())   
		{   

			fileName   =   m_find.GetFileName();   
			ctrlComboStytleFile.AddString(fileName);   

		}   
		fileName   =   m_find.GetFileName();   
		ctrlComboStytleFile.AddString(fileName);   
	}   
	m_find.Close();//�����ļ����   

	CString style;
	style = theApp.GetProfileString(  _T("Settings"), _T("theme") , _T("�޷��") );
	int sel = ctrlComboStytleFile.SelectString( -1 ,style);

	if ( sel>0 )
	{
		ctrlComboStytleFile.SetCurSel( sel );
	}
	int vs ;
	vs = theApp.GetProfileInt(  _T("Settings"), _T("Vscombo") , 0 );
	ctrlComboView.SetCurSel( vs );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CConfigDlg::OnCbnSelchangeComboStyle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData( );
	TRACE(m_strStyle+_T("\n"));
	theApp.WriteProfileString( _T("Settings") , _T("theme") , m_strStyle );
	XTPSkinManager()->LoadSkin( theApp.GetStylesPath()+m_strStyle );	
	//XTPSkinManager()->
}

void CConfigDlg::OnCbnSelchangeComboView()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData( );
	theApp.WriteProfileInt( _T("Settings") , _T("Vscombo") , m_VS );
	AfxMessageBox(_T("���Ľ����´�����ʱ��Ч��"));
}
