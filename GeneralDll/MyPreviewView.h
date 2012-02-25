#pragma once
#include "afxpriv.h"
#include "afxres.h"

// CMyPreviewView ��ͼ

class CMyPreviewView : public CPreviewView
{
	DECLARE_DYNCREATE(CMyPreviewView)

protected:
	CMyPreviewView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMyPreviewView();

public:

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	//�Զ���ر�Ԥ��
	afx_msg void OnPreviewClose();
protected:
	//����һ/��ҳ��ť
	afx_msg void OnUpdateNumPageChange(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


