#pragma once


// CPasswordDlg �Ի���

class CPasswordDlg : public CDialog
{
	DECLARE_DYNAMIC(CPasswordDlg)
public:	
	enum DlgKindFlag
	{
		DKF_SET,//��������
		DKF_DEL,//ɾ������
		DKF_VLD//��֤����
	};
	DlgKindFlag dlgFlag;
	CPasswordDlg(  CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPasswordDlg();
	CString m_password;
	CString m_docPassword;
// �Ի�������
	enum { IDD = IDD_PASSWORD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
public:
	virtual BOOL OnInitDialog();
};
