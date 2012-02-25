// DocExportDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PrintCaseInfo2x.h"
#include "DocExportDlg.h"


// CDocExportDlg �Ի���

IMPLEMENT_DYNAMIC(CDocExportDlg, CDialog)

CDocExportDlg::CDocExportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDocExportDlg::IDD, pParent)

{

}

CDocExportDlg::~CDocExportDlg()
{
	if (pInfo)
	{
		delete pInfo;
	}
}

void CDocExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX ,IDC_PROGRESS1 ,m_progressCtrl);
}


BEGIN_MESSAGE_MAP(CDocExportDlg, CDialog)
	ON_BN_CLICKED(IDC_OPEN_WORD, &CDocExportDlg::OnBnClickedOpenWord)
	ON_BN_CLICKED(IDC_PREVIEW_WORD, &CDocExportDlg::OnBnClickedPreviewWord)
	ON_BN_CLICKED(IDC_SAVE_WORD, &CDocExportDlg::OnBnClickedSaveWord)
	ON_BN_CLICKED(IDCANCEL, &CDocExportDlg::OnBnClickedCancel)
	ON_MESSAGE_VOID(WM_DLG_CLOSE,CloseIt )
	ON_MESSAGE_VOID(WM_EXPORT_FINISHED,OnExportFinished )	
	ON_MESSAGE_VOID(WM_EXPORT_STEP_IT,OnStepIt )	
END_MESSAGE_MAP()


// CDocExportDlg ��Ϣ�������

BOOL CDocExportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_progressCtrl.SetRange32(0,1000);
	m_progressCtrl.SetStep(1);
	pInfo=new CDocExportInfo( this , pCidDoc);
	pThread = AfxBeginThread(DocExportThreadProc,(LPVOID) pInfo, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	pThread->ResumeThread();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//�رնԻ��򣬴�ʱӦȷ���߳��Ѿ��˳�
void CDocExportDlg::CloseIt(void)
{
	//�������ݽ�����ֱ�ӵ���OnCancel
	CDialog::OnCancel();
}

//��Word��
void CDocExportDlg::OnBnClickedOpenWord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pInfo->bExit = DOC_EXPORT_OPEN;
	pThread->ResumeThread();
}

//��Word��Ԥ��
void CDocExportDlg::OnBnClickedPreviewWord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pInfo->bExit = DOC_EXPORT_PREVIEW;
	pThread->ResumeThread();
}

//����ΪWord�ĵ�
void CDocExportDlg::OnBnClickedSaveWord()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pInfo->bExit = DOC_EXPORT_SAVE;
	pThread->ResumeThread();
}

//���ȡ����ť
void CDocExportDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_STATIC_MSG)->SetWindowText(_T("����ȡ�������Ժ�..."));
	//֪ͨ�߳��˳�
	pInfo->bExit =DOC_EXPORT_CANCEL;	
	pThread->ResumeThread();
}

//������ϣ����Ľ���״̬
void CDocExportDlg::OnExportFinished(void)
{
	GetDlgItem(IDC_OPEN_WORD)->EnableWindow();
	GetDlgItem(IDC_PREVIEW_WORD)->EnableWindow();
	GetDlgItem(IDC_SAVE_WORD)->EnableWindow();
	GetDlgItem(IDC_STATIC_MSG)->SetWindowText(_T("������ϣ�"));

}

// �ƽ�������
void CDocExportDlg::OnStepIt(void)
{
	m_progressCtrl.StepIt();
}

