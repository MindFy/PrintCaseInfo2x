// ScorllCenterFormView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "ScorllCenterFormView.h"
#include <locale.h>

// CScorllCenterFormView

IMPLEMENT_DYNCREATE(CScorllCenterFormView, CFormView)

CScorllCenterFormView::CScorllCenterFormView(UINT nIDTemplate)
	: CFormView(nIDTemplate)
	, bAlwaysScrollWithWheel(false)
{
	//ʹTRACE���������������
	setlocale(LC_ALL, "chs");
	this->bCtrlFocus = true;
}

CScorllCenterFormView::~CScorllCenterFormView()
{
}

void CScorllCenterFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScorllCenterFormView, CFormView)
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEACTIVATE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CScorllCenterFormView ���

#ifdef _DEBUG
void CScorllCenterFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CScorllCenterFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CScorllCenterFormView ��Ϣ�������

void CScorllCenterFormView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	if ( cx>viewWidth )
	{
		newSeek = ( cx-viewWidth)/2 ;
	} 
	else
	{
		newSeek = 0 ;
	}
	MoveAllCtrl( newSeek-oldSeek );
	//TRACE( _T("** %d %d  %d\n") , cx, cy , newSeek-oldSeek);	
	oldSeek = newSeek;
}

void CScorllCenterFormView::MoveAllCtrl(  int x )
{
	CWnd   *pWndCtrl   = GetWindow(GW_CHILD);//�õ���һ���ؼ�   
	while ( pWndCtrl )
	{
		CRect rc;
		pWndCtrl->GetWindowRect(rc);
		ScreenToClient( rc );
		rc.left += x ;
		rc.right += x;
		pWndCtrl ->MoveWindow(rc);
		pWndCtrl   =   pWndCtrl->GetWindow(GW_HWNDNEXT);//�õ���һ��
	}
	//�ػ棬��ֹ�ؼ���Ӱ
	RedrawWindow();
}

void CScorllCenterFormView::CheckAllComboBox(  )
{
	CWnd   *pWndCtrl   = GetWindow(GW_CHILD);//�õ���һ���ؼ�   
	while ( pWndCtrl )
	{
		if( pWndCtrl->IsKindOf( RUNTIME_CLASS( CMyComboBox ) ) )
		{
			((CMyComboBox*) pWndCtrl)->Check();
		}
		pWndCtrl   =   pWndCtrl->GetWindow(GW_HWNDNEXT);//�õ���һ��
	}
}

void CScorllCenterFormView::resetAllComboBox(  )
{
	//TRACE("CScorllCenterFormView::resetAllComboBox(  )");

	CWnd   *pWndCtrl   = GetWindow(GW_CHILD);//�õ���һ���ؼ�   
	while ( pWndCtrl )
	{
		if ( IsCombBox( pWndCtrl ))
		{   
			((CComboBox*) pWndCtrl)->SetCurSel(0);
		}
		pWndCtrl   =   pWndCtrl->GetWindow(GW_HWNDNEXT);//�õ���һ��
	}
	
}

BOOL  CScorllCenterFormView::IsCombBox(   CWnd*   pWnd   )   
{   
	ASSERT(   pWnd   !=   NULL   );   
	HWND   hWnd   =   pWnd->GetSafeHwnd();   
	if   (hWnd   ==   NULL)   
		return   FALSE;   

	TCHAR   szClassName[6];   
	if (  ::GetClassName(hWnd,   szClassName,   6)   &&  _tcsicmp(szClassName,   _T("Combo"))   ==   0 )
	{
		return TRUE;   
	}
	return FALSE;
}    

BOOL   CScorllCenterFormView::IsMultEdit(   CWnd*   pWnd   )   
{   
	ASSERT(   pWnd   !=   NULL   );   
	HWND   hWnd   =   pWnd->GetSafeHwnd();   
	if   (hWnd   ==   NULL)   
		return   FALSE;   

	TCHAR   szClassName[6];   
	if (  ::GetClassName(hWnd,   szClassName,   6)   &&  _tcsicmp(szClassName,   _T("Edit"))   ==   0 )
	{
		if ( pWnd->GetStyle()&ES_MULTILINE )
		{
			return TRUE;   
		}
	}
	return FALSE;
}  

//������ͼλ������һTAB�ؼ�
BOOL CScorllCenterFormView::MoveViewToNextTAB( )
{
	if( !UpdateDataOneCtrl( GetFocus()->GetDlgCtrlID() ))
		return FALSE;

	CWnd * pNextCtrl =  GetNextDlgTabItem( GetFocus() );
	CWnd * pView = pNextCtrl->GetParent();
	CRect rcCtrl ,rcView;
	pNextCtrl->GetWindowRect( rcCtrl );
	pView->GetWindowRect( rcView );
	//posΪ�ؼ����������ͼԭ���ƫ����
	CPoint pos ( rcCtrl.CenterPoint().x - rcView.left , rcCtrl.CenterPoint().y-rcView.top );
//	TRACE( _T("pos %d %d\n")  , pos.x,pos.y);
	//���ؼ�λ�ý�ƫ��������ͼ��ʹ�ؼ�����
	if( pos .y<20 || pos.y>rcView.Height()-20 || pos.x<20 || pos.x>rcView.Width()-20 )
	{
		pos += GetScrollPosition();
		pos.x-=rcView.Width()/2;
		pos.y-=rcView.Height()/2;
		CScrollView::ScrollToPosition( pos );
	}
	return TRUE;
}
// CPrintCaseInfoView ��Ϣ�������

void CScorllCenterFormView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CFormView::OnPrepareDC(pDC, pInfo);
}

BOOL CScorllCenterFormView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CFormView::DoPreparePrinting(pInfo);
}

void CScorllCenterFormView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CFormView::OnBeginPrinting(  pDC,  pInfo);
}

void CScorllCenterFormView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	//��Ӵ�ӡ����е��������
	CFormView::OnEndPrinting(  pDC,  pInfo);
}

void CScorllCenterFormView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CFormView::OnPrint(  pDC,  pInfo);
}

void CScorllCenterFormView::OnFilePrintPreview()
{	
	//CFormView::OnFilePrintPreview();
	//�Զ����ӡԤ������
	CPrintPreviewState* pState = new CPrintPreviewState;
	if (!DoPrintPreview(AFX_IDD_PREVIEW_TOOLBAR, this, RUNTIME_CLASS(CMyPreviewView), pState))
	{
		//TRACE0(_T("Error: OnFileImprovedprintpreview failed.\n"));
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		delete pState;      
	}

}
void CScorllCenterFormView::OnInitialUpdate()
{
	resetAllComboBox(  );
	CFormView::OnInitialUpdate();

	GetParentFrame()->RecalcLayout();
	// TODO: �ڴ����ר�ô����/����û���
}

BOOL CScorllCenterFormView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN)
	{ 
		short nKeyState = GetKeyState(VK_CONTROL);
		BOOL bCtrlCKeyDown = (nKeyState &	0x80);
		//Ctrl������
		if  (bCtrlCKeyDown)   
		{   
			switch (pMsg->wParam)   
			{   
			case   65  : //A  
				::SendMessage(pMsg->hwnd, EM_SETSEL, 0, -1 );
				return true;
			case   67  : //C 
				::SendMessage(pMsg->hwnd, WM_COPY, 0, 0 );
				return true;
			case   86  : //V 
				::SendMessage(pMsg->hwnd, WM_PASTE, 0, 0 );
				return true;
			case   88  : //X  
				::SendMessage(pMsg->hwnd, WM_CUT, 0, 0 );
				return true;
			case   90  : //Z 
				::SendMessage(pMsg->hwnd, WM_UNDO, 0, 0 );
				return true;
			}   
		}  
		if ( pMsg->wParam == VK_TAB)
		{
			if( ! MoveViewToNextTAB())
				return TRUE;
		}
		else if(pMsg->wParam==VK_RETURN )
		{

			if(  ! IsMultEdit( GetFocus() ))
			{
				if( ! MoveViewToNextTAB())
					return TRUE;
				//GetNextDlgTabItem( GetFocus() )->SetFocus();
				//return true;
				//�޸İ�����ϢΪTAB���Ա�֤��һ������ؼ���ý���ʱ����Ϊȫѡ״̬
				pMsg->wParam = VK_TAB;
			}
		}
	}
	else if ( pMsg->message == WM_MOUSEWHEEL)
	{
		if (bAlwaysScrollWithWheel)
		{
			pMsg->hwnd= this->m_hWnd;
		}
	}
	else if ( pMsg->message ==WM_ACTIVATE )
	{
		TRACE("Q 0x%04x\n", pMsg->message);
	}
	return CFormView::PreTranslateMessage(pMsg);
}

void CScorllCenterFormView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(false);
	CheckAllComboBox( );
}

void CScorllCenterFormView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	
	//if(this->bCtrlFocus){//�ӿؼ��н���
	//	::SendMessage(this->m_hWndFocus,WM_KILLFOCUS,0,0);
	//	this->SetFocus();//��ͼ��ȡ���㣬���������ֹ���
	//	this->bCtrlFocus= true; //��־λ
	/*
	}else{//�ӿؼ��޽���
		//�����ӿؼ�����
		::SetFocus(this->m_hWndFocus);

		//��־λ
		this->bCtrlFocus = false;
	}
	*/
//	this->m_hWndFocus

/*
	TCHAR   szClassName[6];   
	::GetClassName(this->m_hWndFocus,   szClassName,   6);
	TRACE( szClassName );//   &&  _tcsicmp(szClassName,   _T("Edit")) 
*/
	CFormView::OnLButtonDown(nFlags, point);
}

BOOL CScorllCenterFormView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this->DoMouseWheel(nFlags, zDelta, pt);
	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}

void CScorllCenterFormView::AlwaysScrollWithWheel(bool bAlways)
{
	bAlwaysScrollWithWheel = bAlways;
}

AFX_STATIC void AFX_CDECL _Afx_DDX_TextWithFormat(CDataExchange* pDX, int nIDC,
												  LPCTSTR lpszFormat, UINT nIDPrompt, ...)
												  // only supports windows output formats - no floating point
{
	va_list pData;
	va_start(pData, nIDPrompt);

	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	ASSERT( hWndCtrl != NULL );

	const int SZT_SIZE = 64;
	TCHAR szT[SZT_SIZE];
	if (pDX->m_bSaveAndValidate)
	{
		void* pResult;

		pResult = va_arg( pData, void* );
		// the following works for %d, %u, %ld, %lu
		::GetWindowText(hWndCtrl, szT, _countof(szT));

		CString str(szT);
		str.Trim();
		if (str.IsEmpty())
		{	//�ؼ�����Ϊ�գ��ո�������
			szT[0] ='0';
			szT[1] ='\0';
		}
		if ( _sntscanf_s(szT, _countof(szT), lpszFormat, pResult) != 1)
		{
			AfxMessageBox(nIDPrompt);
			pDX->Fail();        // throws exception
		}
	}
	else
	{

		ATL_CRT_ERRORCHECK_SPRINTF(_vsntprintf_s(szT, _countof(szT), _countof(szT) - 1, lpszFormat, pData));
		// does not support floating point numbers - see dlgfloat.cpp
		AfxSetWindowText(hWndCtrl, szT);
	}

	va_end(pData);
}

//�Զ���ռ�������������������ĵ����޸ı�־
void  CScorllCenterFormView::AfxTextFloatFormat(CDataExchange* pDX, int nIDC,
							   void* pData, double value, int nSizeGcvt)
{
	ASSERT(pData != NULL);

	pDX->PrepareEditCtrl(nIDC);
	HWND hWndCtrl;
	pDX->m_pDlgWnd->GetDlgItem(nIDC, &hWndCtrl);

	const int TEXT_BUFFER_SIZE = 400;
	TCHAR szBuffer[TEXT_BUFFER_SIZE];
	if (pDX->m_bSaveAndValidate)
	{
		::GetWindowText(hWndCtrl, szBuffer, _countof(szBuffer));
		CString str(szBuffer);
		str.Trim();
		if (str.IsEmpty())
		{	//�ؼ�����Ϊ�գ��ո�������
			szBuffer[0] ='0';
			szBuffer[1] ='\0';
		}
		double d;
		if (_sntscanf_s(szBuffer, _countof(szBuffer), _T("%lf"), &d) != 1)
		{
			AfxMessageBox(AFX_IDP_PARSE_REAL);
			pDX->Fail();            // throws exception
		}
		if (nSizeGcvt == FLT_DIG)
		{
			float newValue = (float)d;
			if ( newValue != (float)value )
			{
				*((float*)pData) = newValue;
				if ( ! GetDocument()->IsModified())
				{
					GetDocument()->SetModifiedFlag();
				}
			}
		}
		else
		{
			double newValue = (double)d;
			if ( newValue != value )
			{
				*((double*)pData) = newValue;
				if ( ! GetDocument()->IsModified())
				{
					GetDocument()->SetModifiedFlag();
				}
			}
		}
	}
	else
	{
		ATL_CRT_ERRORCHECK_SPRINTF(_sntprintf_s(szBuffer, _countof(szBuffer), _countof(szBuffer) -1, _T("%.*g"), nSizeGcvt, value));
		AfxSetWindowText(hWndCtrl, szBuffer);
	}
}

void CScorllCenterFormView::DDX_Text_UINT(CDataExchange* pDX, int nIDC, UINT& value)
{
	if (pDX->m_bSaveAndValidate)
	{
		int newValue ;// 
		_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_UINT, &newValue);
		if ( newValue != value )
		{
			value = newValue;
			if ( ! GetDocument()->IsModified())
			{
				GetDocument()->SetModifiedFlag();
			}
		}
	}	
	else
		_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%u"), AFX_IDP_PARSE_UINT, value);
}

void CScorllCenterFormView::DDX_Text_INT(CDataExchange* pDX, int nIDC, int& value)
{

	if (pDX->m_bSaveAndValidate)
	{
		int newValue ;// 
		_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%d"), AFX_IDP_PARSE_INT, &newValue);
		if ( newValue != value )
		{
			value = newValue;
			if ( ! GetDocument()->IsModified())
			{
				GetDocument()->SetModifiedFlag();
			}
		}
	}
	else
		_Afx_DDX_TextWithFormat(pDX, nIDC, _T("%d"), AFX_IDP_PARSE_INT, value);
}
//DDX_Text()
void CScorllCenterFormView::DDX_Text_CSTRING(CDataExchange* pDX, int nIDC, CString& value)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	if (pDX->m_bSaveAndValidate)
	{
		CString newValue;
		int nLen = ::GetWindowTextLength(hWndCtrl);
		::GetWindowText(hWndCtrl, newValue.GetBufferSetLength(nLen), nLen+1);
		newValue.ReleaseBuffer();
		if ( newValue != value )
		{			
			value = newValue;
			if ( ! GetDocument()->IsModified())
			{
				GetDocument()->SetModifiedFlag();
			}
		}
	}
	else
	{
		AfxSetWindowText(hWndCtrl, value);
	}
}

void CScorllCenterFormView::DDX_CBString_CSTRING(CDataExchange* pDX, int nIDC, CString& value)
{
	pDX->PrepareCtrl(nIDC);
	HWND hWndCtrl;
	pDX->m_pDlgWnd->GetDlgItem(nIDC, &hWndCtrl);
	if (pDX->m_bSaveAndValidate)
	{
		CString newValue;
		// just get current edit item text (or drop list static)
		int nLen = ::GetWindowTextLength(hWndCtrl);
		if (nLen > 0)
		{
			// get known length
			::GetWindowText(hWndCtrl, newValue.GetBufferSetLength(nLen), nLen+1);
		}
		else
		{
			// for drop lists GetWindowTextLength does not work - assume
			//  max of 255 characters
			::GetWindowText(hWndCtrl, newValue.GetBuffer(255), 255+1);
		}
		newValue.ReleaseBuffer();
		if ( newValue != value )
		{			
			value = newValue;
			if ( ! GetDocument()->IsModified())
			{
				GetDocument()->SetModifiedFlag();
			}
			
		}
	}
	else
	{
		// set current selection based on model string
		if (::SendMessage(hWndCtrl, CB_SELECTSTRING, (WPARAM)-1,
			(LPARAM)(LPCTSTR)value) == CB_ERR)
		{
			// just set the edit text (will be ignored if DROPDOWNLIST)
			AfxSetWindowText(hWndCtrl, value);
		}
	}
}

void CScorllCenterFormView::DDX_Text_FLOAT(CDataExchange* pDX, int nIDC, float& value)
{
	AfxTextFloatFormat(pDX, nIDC, &value, value, FLT_DIG);
}

void CScorllCenterFormView::DDX_DateTimeCtrl_CTIME(CDataExchange* pDX, int nIDC, CTime& value)
{
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	CDateTimeCtrl* pWnd = (CDateTimeCtrl*) CWnd::FromHandle(hWndCtrl);

	ENSURE(pWnd);
	if (pDX->m_bSaveAndValidate)
	{
		CTime newValue;
		pWnd->GetTime(newValue);
		if ( newValue != value )
		{			
			value = newValue;
			if ( ! GetDocument()->IsModified())
			{
				GetDocument()->SetModifiedFlag();
			}
		}

	}
	else
	{
		pWnd->SetTime(&value);
	}
}

BOOL CScorllCenterFormView::UpdateDataOneCtrl( UINT id , BOOL bSaveAndValidate)
{
	ASSERT(::IsWindow(m_hWnd)); // calling UpdateData before DoModal?

	CDataExchange dx(this, bSaveAndValidate);

	// prevent control notifications from being dispatched during UpdateData
	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	HWND hWndOldLockout = pThreadState->m_hLockoutNotifyWindow;
	ASSERT(hWndOldLockout != m_hWnd);   // must not recurse
	pThreadState->m_hLockoutNotifyWindow = m_hWnd;

	BOOL bOK = FALSE;       // assume failure
	TRY
	{
		DoDataExchangeOneCtrl( id , &dx);
		bOK = TRUE;         // it worked
	}
	CATCH(CUserException, e)
	{
		// validation failed - user already alerted, fall through
		ASSERT(!bOK);											
		// Note: DELETE_EXCEPTION_(e) not required
	}
	AND_CATCH_ALL(e)
	{
		// validation failed due to OOM or other resource failure
		e->ReportError(MB_ICONEXCLAMATION, AFX_IDP_INTERNAL_FAILURE);
		ASSERT(!bOK);
		DELETE_EXCEPTION(e);
	}
	END_CATCH_ALL

		pThreadState->m_hLockoutNotifyWindow = hWndOldLockout;
	
	return bOK;
}

void CScorllCenterFormView::DoDataExchangeOneCtrl( UINT id , CDataExchange* pDX)
{
	//CFormView::DoDataExchange(pDX);
	//ʲô�����������麯���ᱻ���า��
}
int CScorllCenterFormView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TRACE(_T("%x %x %x\n") , pDesktopWnd ,nHitTest ,message);//WM_CLOSE
	UINT id = ::GetDlgCtrlID(GetFocus()->GetSafeHwnd());
	
	//this->m_hWndFocus = GetFocus()->GetSafeHwnd();
	//this->bCtrlFocus = true;

	//TRACE(_T("sssssssssssssss\n"));
	if(UpdateDataOneCtrl(id))
		return CFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
	else
		return MA_NOACTIVATEANDEAT;
}


void CScorllCenterFormView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CFormView::OnActivate(nState, pWndOther, bMinimized);
	TRACE(_T(" CScorllCenterFormView::OnActivate\n"));
	// TODO: �ڴ˴������Ϣ����������
}
