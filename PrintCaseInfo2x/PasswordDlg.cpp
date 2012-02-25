// PasswordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PrintCaseInfo2x.h"
#include "PasswordDlg.h"


// CPasswordDlg �Ի���

IMPLEMENT_DYNAMIC(CPasswordDlg, CDialog)

CPasswordDlg::CPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPasswordDlg::IDD, pParent)
	, m_password(_T(""))
	,dlgFlag ( DKF_VLD)
{

}

CPasswordDlg::~CPasswordDlg()
{
}

void CPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
}


BEGIN_MESSAGE_MAP(CPasswordDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPasswordDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPasswordDlg ��Ϣ�������


BOOL CPasswordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	switch (dlgFlag)
	{
		case DKF_SET:
			SetWindowText( _T("�ļ�����") );
			GetDlgItem( IDOK )->SetWindowText( _T("�ļ�����(&P)") );
			GetDlgItem( IDC_STATIC_MESSAGE )->SetWindowText( _T("�ļ��������������������") );
			break;
		case DKF_VLD:	
			SetWindowText( _T("�ļ�����") );
			GetDlgItem( IDOK )->SetWindowText( _T("�ļ�����(&D)") );
			GetDlgItem( IDC_STATIC_MESSAGE )->SetWindowText( _T("�ļ��Ѽ������������������") );
			break;
		default:
			TRACE(_T("error:dlgFlag is not Set!\n"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPasswordDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	switch (dlgFlag)
	{
	case DKF_SET:
		if (m_password.IsEmpty())
		{

			GetDlgItem( IDC_STATIC_MESSAGE )->SetWindowText( _T("���벻��Ϊ�գ�") );
			GetDlgItem( IDC_EDIT_PASSWORD )->SetFocus();
			

		}
		else
		{
			OnOK();	
		}
		break;
	case DKF_VLD:
		if (m_password != m_docPassword)
		{
			GetDlgItem( IDC_STATIC_MESSAGE )->SetWindowText( _T("�����������������") );
			GetDlgItem( IDC_EDIT_PASSWORD )->SetFocus();
		}
		else
		{
			OnOK();
		}
		break;
	}
}
