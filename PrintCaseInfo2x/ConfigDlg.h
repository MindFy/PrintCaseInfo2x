#pragma once
#include "afxwin.h"


// CConfigDlg �Ի���

class CConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConfigDlg();

// �Ի�������
	enum { IDD = IDD_CONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox ctrlComboStytleFile;
public:
	CString m_strStyle;
public:
	afx_msg void OnBnClickedOk();
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnCbnSelchangeComboStyle();
public:
	afx_msg void OnCbnSelchangeComboView();
public:
	int m_VS;
public:
	CComboBox ctrlComboView;
};
