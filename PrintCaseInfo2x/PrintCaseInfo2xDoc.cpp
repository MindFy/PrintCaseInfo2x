// PrintCaseInfo2xDoc.cpp : CPrintCaseInfo2xDoc ���ʵ��
//

#include "stdafx.h"
#include "PrintCaseInfo2x.h"
#include "MainFrm.h"
#include "PrintCaseInfo2xDoc.h"
#include "PrintCaseInfoView.h"
#include "PasswordDlg.h"
#include "DocExportDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPrintCaseInfo2xDoc

IMPLEMENT_DYNCREATE(CPrintCaseInfo2xDoc, CDocument)

BEGIN_MESSAGE_MAP(CPrintCaseInfo2xDoc, CDocument)
	ON_COMMAND(ID_EXPORT_TO_WORD, &CPrintCaseInfo2xDoc::OnExportToWord)
	ON_COMMAND(ID_MENU_FILE_LOCK, &CPrintCaseInfo2xDoc::OnMenuFileLock)
	ON_COMMAND(ID_MENU_DEL_FILE_LOCK, &CPrintCaseInfo2xDoc::OnMenuDelFileLock)
	ON_UPDATE_COMMAND_UI(ID_MENU_FILE_LOCK, &CPrintCaseInfo2xDoc::OnUpdateMenuFileLock)
	ON_UPDATE_COMMAND_UI(ID_MENU_DEL_FILE_LOCK, &CPrintCaseInfo2xDoc::OnUpdateMenuDelFileLock)
END_MESSAGE_MAP()


// CPrintCaseInfo2xDoc ����/����

CPrintCaseInfo2xDoc::CPrintCaseInfo2xDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CPrintCaseInfo2xDoc::~CPrintCaseInfo2xDoc()
{
}


// CPrintCaseInfo2xDoc ���л�

BOOL CPrintCaseInfo2xDoc::ValidatePassword(CString password)
{
	password = unSer( password );
	//AfxMessageBox( password  );

	CPasswordDlg dlg;
	dlg.dlgFlag = CPasswordDlg::DKF_VLD;
	dlg.m_docPassword = password;
	if(dlg.DoModal() == IDCANCEL)
	{
		THROW( new   CUserException( TRUE , IDS_EXCEPTION_CANCEL_OPEN )) ;
		//	return FALSE;
	}

	return TRUE;
}

void CPrintCaseInfo2xDoc::ReadFile(CArchive& ar)
{
	if (ar.IsStoring())
	{
		return;
	}
	CString fileType;
	ar>>fileType;
	if ( fileType != fileTypeString )
	{
		THROW( new   CUserException( TRUE , IDS_EXCEPTION_FILE_TYPE_ERROR )) ;
		return ;
	}

	//��ȡ���屾��
	ar >> majorVersion;
	if( majorVersion < 2 ){ //1.x�汾���ĵ��޴ΰ汾�ţ�ȡ��֧��
		THROW( new   CUserException( TRUE , IDS_EXCEPTION_VERSION_LOW )) ;
		return ;
	}
	//��ȡ�ΰ汾��
	ar>>minorVersion;



	if ( majorVersion > appMarjorVersion ) //�ļ����汾�Ź���
	{
		THROW( new   CUserException( TRUE , IDS_EXCEPTION_VERSION_LOW )) ;
		return ;
	}
	else
	{
		if(minorVersion > appMinjorVersion) //�ļ��ΰ汾�Ź���
		{
			THROW( new   CUserException( TRUE , IDS_EXCEPTION_VERSION_LOW )) ;
			return ;
		}else
		{
			if(  majorVersion < minSupportMarjorVersion ) // �ļ����屾�Ź���
			{
				//ȡ���Ͱ汾�ļ�֧��
				THROW( new   CUserException( TRUE , IDS_EXCEPTION_LOW_VERSION_FILE )) ;
				return ;
			}
			else
			{
				if ( minorVersion < minSupportMinjorVersion) //�ļ��ΰ汾�Ź���
				{
					//ȡ���Ͱ汾�ļ�֧��
					THROW( new   CUserException( TRUE , IDS_EXCEPTION_LOW_VERSION_FILE )) ;
					return ;
				}
				else
				{//����֧�ָ��ļ��汾
					//��ȡ���Ʊ�ʶ
					ar >>ctrlFlag;

					if ( ctrlFlag & FILE_CTRL_LOCKED ) // �ļ��Ѽ���
					{
						//��ȡ��������
						ar>> password;
						//��֤����
						ValidatePassword(password);
					}
				}
			}
		}

	}
	/*
	if ( majorVersion < appSupportMajorVersion )
	{//1.x�汾
		//ȡ���Ͱ汾�ļ�֧��
		THROW( new   CUserException( TRUE , IDS_EXCEPTION_LOW_VERSION_FILE )) ;
		return ;
	}
	else//2.x��
	{
		ar>>minorVersion;
		if ( minorVersion > appMinjorVersion )
		{
			THROW( new   CUserException( TRUE , IDS_EXCEPTION_VERSION_LOW )) ;
			return ;
		}	
		if ( minorVersion < minSupportMinjorVersion)
		{
			//ȡ���Ͱ汾�ļ�֧��
			THROW( new   CUserException( TRUE , IDS_EXCEPTION_LOW_VERSION_FILE )) ;
			return ;
		}
		ar >>ctrlFlag;
		if ( ctrlFlag & FILE_CTRL_LOCKED )
		{
			ar>> password;
			ValidatePassword(password);
		}
	}
*/
	commonInfo.Serialize( ar ,majorVersion , minorVersion);
	maleInfo.Serialize(ar);
	femaleInfo.Serialize( ar ,majorVersion , minorVersion);
}

void CPrintCaseInfo2xDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << fileTypeString;
		ar << appMarjorVersion;	
		ar << appMinjorVersion;
		ar << ctrlFlag;
		if ( ctrlFlag & FILE_CTRL_LOCKED )
		{
			ar<< Ser( password );
		}
		commonInfo.Serialize( ar ,majorVersion, minorVersion );
		maleInfo.Serialize(ar);
		femaleInfo.Serialize(ar,majorVersion , minorVersion);
	}
	else
	{   
		ReadFile( ar );
	}


}


// CPrintCaseInfo2xDoc ���

#ifdef _DEBUG
void CPrintCaseInfo2xDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPrintCaseInfo2xDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPrintCaseInfo2xDoc ����

CString   CPrintCaseInfo2xDoc::Ser(CString   yuanwen)    
{   
	TCHAR   charyou;   
	CString miwen;
	for(int   i=0;i<yuanwen.GetLength()+1;i++)   
	{                   
		charyou=yuanwen.GetAt(i)+1;   
		miwen.AppendChar( charyou )   ;
	}   
	return miwen;
}  

CString   CPrintCaseInfo2xDoc::unSer(CString   miwen)
{   
	TCHAR   charyou;  
	CString yuanwen;
	for(int   i=0;i<miwen.GetLength()+1;i++)   
	{                 
		charyou=miwen.GetAt(i)-1;   
		yuanwen.AppendChar( charyou )  ;
	}     
	return yuanwen;
} 

void CPrintCaseInfo2xDoc::ReportSaveLoadException(LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDPDefault)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (e->IsKindOf( RUNTIME_CLASS( CUserException ) ) )
	{
		e->ReportError();

	} 
	else if (e->IsKindOf( RUNTIME_CLASS( CArchiveException ) ) )
	{
		AfxMessageBox(IDS_EXCEPTION_FILE_TYPE_ERROR);            
		//e->Delete();
	} 
	else
	{
		CDocument::ReportSaveLoadException(lpszPathName, e, bSaving, nIDPDefault);
	}
}

void CPrintCaseInfo2xDoc::SetModifiedFlag(BOOL bModified) 
{ 
	TRACE_FUNC();
	CDocument::SetModifiedFlag(bModified); 
 	if(AfxGetMainWnd())
 		AfxGetMainWnd() -> SendMessage(WM_UPDATE_FRAME_TITLE);
}


void CPrintCaseInfo2xDoc::DeleteContents()
{
	// TODO: �ڴ����ר�ô����/����û���
	maleInfo=CMaleInfo();
	femaleInfo=CFemaleInfo();
	commonInfo =CCommonInfo();
	majorVersion = 0;
	minorVersion = 0;
	ctrlFlag = 0 ;
	CDocument::DeleteContents();
}

BOOL CPrintCaseInfo2xDoc::UpdateDocFromView()
{
	TRACE_FUNC();
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CPrintCaseInfoView* pView = (CPrintCaseInfoView*)GetNextView(pos);
		ASSERT_VALID(pView);
		if( ! pView->OnUpdateDocFromView() )
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CPrintCaseInfo2xDoc::DoFileSave( )
{
		TRACE_FUNC();
		//�����ĵ���ͼ����ͬ��
		if ( ! UpdateDocFromView() )
		{
			return FALSE;
		}
		return CDocument::DoFileSave();
}


void CPrintCaseInfo2xDoc::OnExportToWord()
{
	// TODO: �ڴ���������������
//CWinThread*  p = AfxBeginThread(RUNTIME_CLASS(CDocExportThread));
		AfxMessageBox(_T("������Ϊ���ţ�"),MB_OK);
	/*	CDocExportDlg dlg;
		dlg.pCidDoc = this;
		dlg.DoModal();
		*/
}

void CPrintCaseInfo2xDoc::OnMenuFileLock()
{
	// TODO: �ڴ���������������
	CPasswordDlg dlg;
	dlg.dlgFlag = CPasswordDlg::DKF_SET;
	if(dlg.DoModal() ==IDOK)
	{
		password = dlg.m_password;
		ctrlFlag |= FILE_CTRL_LOCKED;
		SetModifiedFlag(TRUE);
		AfxMessageBox(_T("���ļ�����Ϊ:")+password+_T("\r\n���μǣ�"));	
	}
}

void CPrintCaseInfo2xDoc::OnMenuDelFileLock()
{
	// TODO: �ڴ���������������

	if(ValidatePassword(password))
	{
		ctrlFlag &= ~FILE_CTRL_LOCKED;
		SetModifiedFlag(TRUE);
		AfxMessageBox(_T("������ɾ����")) ;
	}
}

void CPrintCaseInfo2xDoc::OnUpdateMenuFileLock(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
		if(! ctrlFlag&FILE_CTRL_LOCKED)
		{
			pCmdUI->SetText(_T("��������(&P)"));			
		}
		else
		{
			pCmdUI->SetText(_T("��������(&M)"));
		}
}

void CPrintCaseInfo2xDoc::OnUpdateMenuDelFileLock(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(ctrlFlag&FILE_CTRL_LOCKED);
}
