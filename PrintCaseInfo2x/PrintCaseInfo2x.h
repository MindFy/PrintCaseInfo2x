// PrintCaseInfo2x.h : PrintCaseInfo2x Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CPrintCaseInfo2xApp:
// �йش����ʵ�֣������ PrintCaseInfo2x.cpp
//

class CPrintCaseInfo2xApp : public CWinApp
{
public:
	CPrintCaseInfo2xApp();
private:
		CString m_strStylesPath;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnFileNew();
public:
	CString GetStylesPath(void);
};

extern CPrintCaseInfo2xApp theApp;
extern const int appMarjorVersion ;
extern const int appMinjorVersion ;
extern const int minSupportMarjorVersion ;
extern const int minSupportMinjorVersion ;

extern const CString fileTypeString;
extern UINT DocExportThreadProc(const LPVOID lpParam);