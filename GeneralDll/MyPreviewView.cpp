// MyPreviewView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyPreviewView.h"



// CMyPreviewView

IMPLEMENT_DYNCREATE(CMyPreviewView, CPreviewView)

CMyPreviewView::CMyPreviewView()
{

}

CMyPreviewView::~CMyPreviewView()
{

}

BEGIN_MESSAGE_MAP(CMyPreviewView, CPreviewView)
		ON_COMMAND(AFX_ID_PREVIEW_CLOSE, CMyPreviewView::OnPreviewClose)
		ON_UPDATE_COMMAND_UI(AFX_ID_PREVIEW_NUMPAGE, OnUpdateNumPageChange)
		ON_WM_CREATE()
		ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CMyPreviewView ���

#ifdef _DEBUG
void CMyPreviewView::AssertValid() const
{
	CPreviewView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyPreviewView::Dump(CDumpContext& dc) const
{
	CPreviewView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyPreviewView ��Ϣ�������


void CMyPreviewView::OnPreviewClose()
{
	CPreviewView::OnPreviewClose();
}


void CMyPreviewView::OnUpdateNumPageChange(CCmdUI* pCmdUI)
{
	/*UINT nPages = m_nZoomState == ZOOM_OUT ? m_nPages : m_nZoomOutPages;

	if (m_bOne) 
	{
		if (nPages == 1) 
		{

			m_bOne = FALSE;
			(m_pToolBar->GetDlgItem(AFX_ID_PREVIEW_NUMPAGE))->SetWindowText(_T("��ҳ"));
		}
	}
	else 
	{
		if (nPages != 1) 
		{
			m_bOne = TRUE;
			(m_pToolBar->GetDlgItem(AFX_ID_PREVIEW_NUMPAGE))->SetWindowText(_T("һҳ"));

		}
	}

	// enable it only if valid to display another page and not zoomed
	pCmdUI->Enable(m_nZoomState == ZOOM_OUT && m_nMaxPages != 1 &&
		(m_pPreviewInfo->GetMaxPage() > 1 || m_nPages > 1));
		*/
	UINT nPages = m_nZoomState == ZOOM_OUT ? m_nPages : m_nZoomOutPages;
	if (nPages==1)
	{
		(m_pToolBar->GetDlgItem(AFX_ID_PREVIEW_NUMPAGE))->SetWindowText(_T("��ҳ"));
	}
	else
	{
		(m_pToolBar->GetDlgItem(AFX_ID_PREVIEW_NUMPAGE))->SetWindowText(_T("һҳ"));
	}

	pCmdUI->Enable(m_nZoomState == ZOOM_OUT && m_nMaxPages != 1 &&
		(m_pPreviewInfo->GetMaxPage() > 1 || m_nPages > 1));
}

BOOL CMyPreviewView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//CFileTreeDoc* pDoc = (CFileTreeDoc*)GetDocument();
	TRACE(_T("#\n"));
	CPoint point = GetScrollPosition();
	if(zDelta==120)
	{
		if( point.y >= 20 )
		{
// 			EndPoint.x = point.x;
// 			EndPoint.y = point.y;
// 			EndPoint.x = EndPoint.x;
// 			EndPoint.y = EndPoint.y - 20;
			TRACE(_T("a\n"));
		}
		else
		{
			TRACE(_T("b\n"));
		}
	}
	if(zDelta==-120)
	{
// 		if( point.y <= pDoc->intDiagramRowCount * pDoc->intRowHeight - 20 )
// 		{
// 			EndPoint.x = point.x;
// 			EndPoint.y = point.y;
// 			EndPoint.x = EndPoint.x;
// 			EndPoint.y = EndPoint.y + 20;
// 		}
// 		else
// 		{
// 			EndPoint.x = EndPoint.x;
// 			EndPoint.y = EndPoint.y;
// 		}
			TRACE(_T("c\n"));
	}
	//ScrollToPosition(EndPoint);
	InvalidateRect(NULL,TRUE);
	return CPreviewView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CMyPreviewView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEWHEEL)
	{
		TRACE(_T("dd\n"));
	} 
	else
	{
	}
	return CPreviewView::PreTranslateMessage(pMsg);
}
