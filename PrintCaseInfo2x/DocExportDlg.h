#pragma once
#include "DocExportInfo.h"

// CDocExportDlg �Ի���

class CDocExportDlg : public CDialog
{
	DECLARE_DYNAMIC(CDocExportDlg)

public:
	CDocExportDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDocExportDlg();

// �Ի�������
	enum { IDD = IDD_DOC_EXPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CProgressCtrl m_progressCtrl;

	DECLARE_MESSAGE_MAP()
public:	
	CPrintCaseInfo2xDoc *pCidDoc;
	CDocExportInfo *pInfo;
	virtual BOOL OnInitDialog();
private:
	CWinThread *pThread;
public:
	void CloseIt(void);
public:
	afx_msg void OnBnClickedOpenWord();
public:
	afx_msg void OnBnClickedPreviewWord();
public:
	afx_msg void OnBnClickedSaveWord();
public:
	afx_msg void OnBnClickedCancel();
public:
//	bool bFinished;
public:
	void OnExportFinished(void);
public:
	// �ƽ�������
	void OnStepIt(void);
};
