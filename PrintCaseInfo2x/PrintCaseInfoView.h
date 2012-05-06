#pragma once
#include "../GeneralDll/ScorllCenterFormView.h"


// CPrintCaseInfoView ������ͼ

class CPrintCaseInfoView : public CScorllCenterFormView
{
	DECLARE_DYNCREATE(CPrintCaseInfoView)

public:
	CPrintCaseInfoView(UINT nIDTemplate);         
protected:	
	CPrintCaseInfoView( ); // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPrintCaseInfoView();

public:
	enum { IDD = IDD_PRINTCASEINFOVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
// 	int PAGE_WIDTH;
// 	int PAGE_HEIGHT;
// 	int PHY_LEFT;
// 	int PHY_RIGHT;
// 	int PHY_TOP;
// 	int PHY_BOTTOM;
	CFont titleFont;
	CFont mainFont;
	CFont boldFont;
	CFont smaleFont;
protected:
		CString getPrintStringForNumWithUnit(CString num,CString unit);
public:	//������ͼ��С��ʱ���н���Ŀؼ��ľ��
	afx_msg LRESULT OnSaveFocus(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnUpdateDocFromView();
	//��ӡ
	afx_msg void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//����ҳ�߾�
	void SetPageMargin(CDC *pDC, CPrintInfo *pInfo, int l, int t, int r, int b);
	//ҳüҳ��
	void PageHeaderFooter(CDC* pDC, CPrintInfo* pInfo , CString nv_fang_xing_ming ,CString bing_li_hao , CTime time);

	void PrintText(CDC* pDC, CPrintInfo* pInfo,CString text, int blankNum =3 ,int minWord=0,bool center=false);
	void PrintTextScript(CDC* pDC, CPrintInfo* pInfo,CString text , CString scriptText ,bool superscript, int blankNum=3 ,bool vCenter = true );
	//   void PrintTextMult(CDC* pDC, CPrintInfo* pInfo,CString text,int blankNum=3 );
	void PrintTextMult2(CDC* pDC, CPrintInfo* pInfo,CString text,int blankNum=3 );
	void PrintTextV(CDC* pDC, CPrintInfo* pInfo,CString text);
	void NewLine(CDC* pDC, CPrintInfo* pInfo ,  bool force = false );
	void NewHalfLine(CDC* pDC, CPrintInfo* pInfo , bool force);
	void NewSmallHalfLine(CDC* pDC, CPrintInfo* pInfo , bool force);

public:
	virtual void OnInitialUpdate();
};


