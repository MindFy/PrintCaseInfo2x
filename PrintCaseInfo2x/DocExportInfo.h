#pragma once
#include "PrintCaseInfo2xDoc.h"
#include "../DocExport/WordTools.h"
// CDocExportInfo ����Ŀ��

class CDocExportInfo : public CObject
{
public:
	//�߳̿��ƶԻ���
	CDialog * pDlg;	
	//�Ƿ����ִ��
	BOOL bExit;
	//�ĵ�ָ��
	CPrintCaseInfo2xDoc * pDoc;
	//Word����
	CWordTools wdt;

	

public:
	CDocExportInfo(CDialog* pDlg , 	CPrintCaseInfo2xDoc * pDoc );
	virtual ~CDocExportInfo();
public:
	BOOL SBT(CString bkName, CString bkText);
public:
	BOOL DocInit(void);
public:
	void ShowWordApp(void);
};


