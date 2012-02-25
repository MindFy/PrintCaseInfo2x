// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once

class CMainFrame :public CXTPFrameWndBase<CFrameWnd>
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
protected:
	enum eViewStatus
	{
		eSplitteView ,
		eSwitchView			
	};
private:
	eViewStatus  viewStatus;
	CView* pFView,*pMView;
public:
	CSplitterWnd m_wndSplitter;
public:

// ����
public:

// ��д
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void UpdateAppTitle();
	afx_msg void UpdateDocFromView();
public:
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
public:
	afx_msg void OnMenuMaleView();
public:
	afx_msg void OnMenuFemaleView();
	void SwitchView(CView*pNewView);
	//CView* ReplaceView(/*int nRow, int nCol,*/ CView* pNewView);
	//CView* ReplaceView(int nRow, int nCol, CRuntimeClass* pViewClass);
public:
	afx_msg void OnUpdateWindowSplit(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuMaleView(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuFemaleView(CCmdUI *pCmdUI);
	afx_msg void OnCustomize();
public:
	afx_msg void OnSoftConfig();
public:
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};


