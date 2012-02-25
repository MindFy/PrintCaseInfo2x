#pragma once
#include "stdafx.h"
#include "float.h"
#include "resource.h"
#include "MyComboBox.h"
#include "MyPreviewView.h"


// CScorllCenterFormView ������ͼ
class AFX_EXT_CLASS CScorllCenterFormView : public CFormView
{
	DECLARE_DYNCREATE(CScorllCenterFormView)

protected:
	CScorllCenterFormView(UINT nIDTemplate=IDD);           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CScorllCenterFormView();

public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	//�����ؼ����еı���
	int viewWidth;
private:
	// �����ù��ֹ�����ͼ
	bool bAlwaysScrollWithWheel;
	int newSeek;
	int oldSeek;
	bool bCtrlFocus;
public:
	void resetAllComboBox(  );
	void CheckAllComboBox(  );
private:
	//������ͼλ������һTAB�ؼ�
	BOOL MoveViewToNextTAB(  );
	//�ƶ�ʹ����
	void MoveAllCtrl(  int x );
	//�ж��Ƿ�Ϊ���б༭��
	BOOL   IsMultEdit(   CWnd*   pWnd   ) ;
	//�ж��Ƿ�Ϊ��Ͽ�
	BOOL   IsCombBox(   CWnd*   pWnd   )   ;
protected: 
	/****          ��CFormView��Ӵ�ӡ֧��         *****/
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	/***************************************************/
	//��ӡԤ��
	afx_msg void OnFilePrintPreview();
public:
	virtual void OnInitialUpdate();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	//�ָ���ͼ��������Ϣ����Ӧ��Ҫ����������������
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	//������ʼ�����Թ�����ͼ
	void AlwaysScrollWithWheel(bool bAlways);
protected:
	//����һ���ؼ�������
	virtual BOOL UpdateDataOneCtrl( UINT id , BOOL bSaveAndValidate = TRUE );
	virtual void DoDataExchangeOneCtrl( UINT id , CDataExchange* pDX);
protected:
	//�Զ���ؼ��������������������ĵ����޸ı�־
	void DDX_Text_UINT(CDataExchange* pDX, int nIDC, UINT& value);
	void DDX_Text_CSTRING(CDataExchange* pDX, int nIDC, CString& value);
	void DDX_Text_INT(CDataExchange* pDX, int nIDC, int& value);
	void DDX_Text_FLOAT(CDataExchange* pDX, int nIDC, float& value);
	void DDX_CBString_CSTRING(CDataExchange* pDX, int nIDC, CString& value);
	void DDX_DateTimeCtrl_CTIME(CDataExchange* pDX, int nIDC, CTime& value);
private:
	//�Զ���Float��Double��������������DDX_Text_FLOAT����øú���
	void  AfxTextFloatFormat(CDataExchange* pDX, int nIDC,
		void* pData, double value, int nSizeGcvt);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
//�ؼ���������������Ҫ���øú���
extern  void AFX_CDECL _Afx_DDX_TextWithFormat(CDataExchange* pDX, int nIDC,
												  LPCTSTR lpszFormat, UINT nIDPrompt, ...);

