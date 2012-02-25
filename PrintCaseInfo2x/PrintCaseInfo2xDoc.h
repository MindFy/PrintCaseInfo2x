// PrintCaseInfo2xDoc.h : CPrintCaseInfo2xDoc ��Ľӿ�
//
#pragma once
#include "../PciCoreDll/FemaleInfo.h"
#include "../PciCoreDll/MaleInfo.h"
#include "../PciCoreDll/CommonInfo.h"

#define  FILE_CTRL_LOCKED 0x01
#define  FILE_CTRL_MINOR_VERSION 0x02	//�����ΰ汾����Ϣ




class CPrintCaseInfo2xDoc : public CDocument
{
protected: // �������л�����
	CPrintCaseInfo2xDoc();
	DECLARE_DYNCREATE(CPrintCaseInfo2xDoc)

// ����
public:
public:
	CCommonInfo commonInfo;    //ͨ����Ϣ
	CMaleInfo maleInfo; //��ʿ��Ϣ
	CFemaleInfo femaleInfo;//Ůʿ��Ϣ

	int    majorVersion;            //�ļ��ĳ������汾��
	int	minorVersion;		//�ļ��ĳ���ΰ汾��		

	UINT ctrlFlag;       //������Ϣλ
	CString  password;   //�ļ���������

// ����
public:

// ��д
public:
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CPrintCaseInfo2xDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString   Ser(CString   yuanwen) ;
	CString   unSer(CString   yuanwen) ;
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void ReportSaveLoadException(LPCTSTR lpszPathName, CException* e, BOOL bSaving, UINT nIDPDefault);
	//����Ϊ���޸��ĵ��������
	virtual void SetModifiedFlag(BOOL bModified);
public:
	virtual void DeleteContents();
public:
	//������ͼ���ݣ������ĵ�
	virtual BOOL UpdateDocFromView();
	//����Ϊ��ͬ�������ٱ����ļ�
	virtual BOOL DoFileSave( );
	//�������
	BOOL ValidatePassword( const CString password);
	//��ȡ�ļ�
	void ReadFile(CArchive& ar);

public:
	afx_msg void OnExportToWord();
public:
	afx_msg void OnMenuFileLock();
public:
	afx_msg void OnMenuDelFileLock();
public:
	afx_msg void OnUpdateMenuFileLock(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateMenuDelFileLock(CCmdUI *pCmdUI);
};


