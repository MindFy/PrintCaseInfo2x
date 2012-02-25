// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "PrintCaseInfo2x.h"
#include "PrintCaseInfo2xDoc.h"
#include "FemaleInputView.h"
#include "MaleInputView.h"
#include "MainFrm.h"
#include "ConfigDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_MENU_MALE_VIEW, &CMainFrame::OnMenuMaleView)
	ON_COMMAND(ID_MENU_FEMALE_VIEW, &CMainFrame::OnMenuFemaleView)
	ON_MESSAGE_VOID(WM_UPDATE_FRAME_TITLE, UpdateAppTitle)
	ON_MESSAGE_VOID(WM_UPDATE_DOC_FROM_VIEW, UpdateDocFromView)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_SPLIT, &CMainFrame::OnUpdateWindowSplit)
	ON_UPDATE_COMMAND_UI(ID_MENU_MALE_VIEW, &CMainFrame::OnUpdateMenuMaleView)
	ON_UPDATE_COMMAND_UI(ID_MENU_FEMALE_VIEW, &CMainFrame::OnUpdateMenuFemaleView)
	ON_COMMAND(ID_SOFT_CONFIG, &CMainFrame::OnSoftConfig)
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	XTPSkinManager()->SetApplyOptions(xtpSkinApplyFrame | xtpSkinApplyColors | xtpSkinApplyMetrics | xtpSkinApplyMenus);

}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

// 	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
// 		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
// 		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
// 	{
// 		TRACE0("δ�ܴ���������\n");
// 		return -1;      // δ�ܴ���
// 	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	//////////////////////////////////////////////////////////////////////////
	// Initialize the command bars
	if (!InitCommandBars())
		return -1;

	XTPPaintManager()->SetTheme(xtpThemeNativeWinXP);
	XTPPaintManager()->GetIconsInfo()->bUseFadedIcons = TRUE;

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	// Add the menu bar
	CXTPCommandBar* pMenuBar = pCommandBars->SetMenu(
		_T("�˵���"), IDR_MAINFRAME);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return -1;      // fail to create
	}

	// Create ToolBar
	CXTPToolBar* pToolBar= (CXTPToolBar*)	pCommandBars->Add(_T("������"), xtpBarTop);
	if (!pToolBar || !pToolBar->LoadToolBar(IDR_MAINFRAME , FALSE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}
	pCommandBars->GetImageManager()->SetIcons( IDR_MAINFRAME, IDR_TOOLBAR_ALPHA);
	pCommandBars->GetToolBar( IDR_MAINFRAME )->SetIconSize( CSize(30,30) );
	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

	// Load the previous state for toolbars and menus.
	LoadCommandBars(_T("CommandBars"));

	PostMessage(WM_SYSCOLORCHANGE);

	//////////////////////////////////////////////////////////////////////////
	// TODO: �������Ҫ��������ͣ������ɾ��������
// 	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
// 	EnableDocking(CBRS_ALIGN_ANY);
// 	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	int vs = theApp.GetProfileInt(  _T("Settings"), _T("Vscombo") , 0 );
	switch (vs)
	{
	case VS_COMBO_SWITCH:
		{
		viewStatus = eSwitchView;
		//////////////////////////////////////////////////////////////////////////
		//���ĵ�����ͼ���ָ�
		pContext->m_pNewViewClass   =   RUNTIME_CLASS(CFemaleInputView)  ;   
		pFView   = (CView*)CreateView(pContext,AFX_IDW_PANE_FIRST)   ; 	
		ASSERT(pFView   !=   NULL)   ; 
		pContext->m_pNewViewClass   =RUNTIME_CLASS(CMaleInputView)  ;   
		pMView   =   (CView*) CreateView(pContext,AFX_IDW_PANE_FIRST+1)   ;  
		ASSERT(pMView   !=   NULL)   ;   
		pMView->ShowWindow(SW_HIDE)   ;   
		pMView->OnInitialUpdate()   ;   
		//////////////////////////////////////////////////////////////////////////
		} 	 
		break;
	case VS_COMBO_SPLITTE_LR:
		{	
		viewStatus = eSplitteView;
		//pContext->m_pNewViewClass   =   RUNTIME_CLASS(CFemaleInputView)  ; 
		//////////////////////////////////////////////////////////////////////////
		//���ĵ�����ͼ�ָ�
		m_wndSplitter.CreateStatic(this, 1, 2 );
		// ���������� 
		m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CFemaleInputView), CSize(10, 10), pContext); 
		m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMaleInputView), CSize(10, 10), pContext); 

 		m_wndSplitter.SetColumnInfo(0, 400 ,30);
 		m_wndSplitter.SetColumnInfo(1,0,30);
		m_wndSplitter.RecalcLayout();
		pFView=(CView*)m_wndSplitter.GetPane(0,0);
		pMView=(CView*) m_wndSplitter.GetPane(0,1);		
		}
		break;
	case VS_COMBO_SPLITTE_UD:
		{	
			viewStatus = eSplitteView;
			//pContext->m_pNewViewClass   =   RUNTIME_CLASS(CFemaleInputView)  ; 
			//////////////////////////////////////////////////////////////////////////
			//���ĵ�����ͼ�ָ�
			m_wndSplitter.CreateStatic(this, 2, 1 );
			// ���������� 
			m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CFemaleInputView), CSize(10, 10), pContext); 
			m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CMaleInputView), CSize(10, 10), pContext); 

			m_wndSplitter.SetRowInfo(0, 400 ,30);
			m_wndSplitter.SetRowInfo(1,0,30);
			m_wndSplitter.RecalcLayout();
			pFView=(CView*)m_wndSplitter.GetPane(0,0);
			pMView=(CView*) m_wndSplitter.GetPane(1,0);		
		}
		break;
	}
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	//��ֹ�����Լ����ı�����
	cs.style &=   ~FWS_PREFIXTITLE;
	cs.style &= ~FWS_ADDTOTITLE;
	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame ��Ϣ�������




void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ( GetActiveView()->IsKindOf( RUNTIME_CLASS( CPreviewView ) ) )
	{
		((CPreviewView*)GetActiveView()) ->SendMessage(WM_COMMAND,AFX_ID_PREVIEW_CLOSE);
	} 
	else
	{
		SaveCommandBars(_T("CommandBars"));
		//��������
		CPrintCaseInfo2xDoc* pDoc =(CPrintCaseInfo2xDoc*) GetActiveDocument();
		if (pDoc)
		{
			if(pDoc->UpdateDocFromView())
			{
				AnimateWindow(300, AW_BLEND | AW_HIDE);
				CFrameWnd::OnClose();	
			}
		}
	}
}

//���±�������δ�����ĵ����Ǻ�
void CMainFrame::UpdateAppTitle()
{
	TRACE_FUNC();
	CDocument* pDocument = GetActiveDocument() ;
	CString lpszDocName =NULL ;
	CString WindowText = m_strTitle + _T(" - ") ;
	if ( pDocument )
	{
		WindowText += pDocument->GetTitle();	
		CString ext = WindowText.Right(4);
		ext.MakeLower();
		if ( _T(".cid") != ext )
		{//ȷ���������ļ�������չ��
			WindowText+= _T(".cid");
		}

		if ( pDocument->IsModified() )
		{
			WindowText += _T("*") ;
		}
	}
	AfxSetWindowText(m_hWnd , (LPCTSTR) WindowText) ;
}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ((nID & 0xfff0) == SC_MINIMIZE)
		GetActiveView()->SendMessage(WM_SAVEFOCUS);

	CFrameWnd::OnSysCommand(nID,lParam);
}

void CMainFrame::SwitchView(CView*pNewView)
{
	if ( ! pNewView)
	{
		return;
	}
	CView* pActiveView = GetActiveView();
	if (  pActiveView== pNewView )
	{
		return;
	}
	//������ݽ���ʧ�ܣ���ֹ��ͼ�л�
	if ( !pActiveView->UpdateData())
	{
		return;
	}
	UINT uActiveViewID = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);
	::SetWindowLong(pActiveView->m_hWnd, GWL_ID, ::GetWindowLong(pNewView->m_hWnd, GWL_ID));
	::SetWindowLong(pNewView->m_hWnd, GWL_ID, uActiveViewID);
	// ��ʾ�µ���ͼ������ǰһ����ͼ
	pActiveView->ShowWindow(SW_HIDE);
	pNewView->ShowWindow(SW_SHOW);
	SetActiveView(pNewView);
	RecalcLayout();
	pNewView->Invalidate();
}


void CMainFrame::OnMenuMaleView()
{
	SwitchView( pMView );
}

void CMainFrame::OnMenuFemaleView()
{
	SwitchView( pFView );
}

void CMainFrame::OnUpdateWindowSplit(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable(viewStatus==eSplitteView);
}

void CMainFrame::OnUpdateMenuMaleView(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable( (viewStatus==eSwitchView)&&(GetActiveView() == pFView) );
}

void CMainFrame::OnUpdateMenuFemaleView(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->Enable( (viewStatus==eSwitchView)&&(GetActiveView() == pMView ) );
}

//���±�������δ�����ĵ����Ǻ�
void CMainFrame::UpdateDocFromView()
{
	TRACE_FUNC();
	pMView->SendMessage(WM_UPDATE_DOC_FROM_VIEW);
	pFView->SendMessage(WM_UPDATE_DOC_FROM_VIEW);

}
void CMainFrame::OnSoftConfig()
{
	// TODO: �ڴ���������������
	CConfigDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnCustomize()
{
	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars != NULL)
	{
		// Instanciate the customize dialog object.
		CXTPCustomizeSheet dlg(pCommandBars);

		// Add the keyboard page to the customize dialog.
		CXTPCustomizeKeyboardPage pageKeyboard(&dlg);
		dlg.AddPage(&pageKeyboard);
		pageKeyboard.AddCategories(IDR_MAINFRAME);

		// Add the options page to the customize dialog.
		CXTPCustomizeOptionsPage pageOptions(&dlg);
		dlg.AddPage(&pageOptions);

		// Add the commands page to the customize dialog.
		CXTPCustomizeCommandsPage* pCommands = dlg.GetCommandsPage();
		pCommands->AddCategories(IDR_MAINFRAME);

		// Use the command bar manager to initialize the
		// customize dialog.
		pCommands->InsertAllCommandsCategory();
		pCommands->InsertBuiltInMenus(IDR_MAINFRAME);
		pCommands->InsertNewMenuCategory();

		// Dispaly the dialog.
		dlg.DoModal();
	}
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CXTPFrameWndBase<CFrameWnd>::OnActivate(nState, pWndOther, bMinimized);
	if ( WA_INACTIVE == nState)
	{
		//GetActiveView()->UpdateData();
	}		
	TRACE(_T("%d "),nState);
	TRACE_FUNC();
	// TODO: �ڴ˴������Ϣ����������
}
