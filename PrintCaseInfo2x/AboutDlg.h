#pragma once
#include "hyperlink.h"
#include "waveLib.h"

// CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
	DECLARE_DYNAMIC(CAboutDlg)

public:
	CAboutDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAboutDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CHyperLink m_QQLink;
	CHyperLink m_GmailLink;
	_WAVE_OBJECT bp;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
