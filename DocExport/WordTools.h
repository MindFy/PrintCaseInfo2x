#pragma once
#include "msword.h"
// CWordTools ����Ŀ��


#define  wdFormatDocument     0     
#define  wdFormatDOSText     4     
#define  wdFormatDOSTextLineBreaks     5     
#define  wdFormatEncodedText     7     
#define  wdFormatFilteredHTML     10     
#define  wdFormatHTML     8     
#define  wdFormatRTF     6     
#define  wdFormatTemplate     1     
#define  wdFormatText     2     
#define  wdFormatTextLineBreaks     3     
#define  wdFormatUnicodeText     7     
#define  wdFormatWebArchive     9     
#define  wdFormatXML     11   

#define wdGoToBookmark -1



class AFX_CLASS_EXPORT CWordTools : public CObject
{
private:
	_Application m_wdApp;
	Documents m_wdDocs;
	_Document m_wdDoc;
	Bookmarks  m_wdBookmarks;
	//Bookmark  m_wdBookmark;
	Selection m_wdSel;
	Range     m_wdRange;
	InlineShapes m_wdInlineShapes; 
	InlineShape m_wdInlineShape;
public:
	CWordTools();
	virtual ~CWordTools();
public:
	//**********************�������ĵ�*******************************************
	BOOL CreateApp();                    //����һ���µ�WORDӦ�ó���
	BOOL CreateDocuments();                //����һ���µ�Word�ĵ�����
	BOOL CreateDocument(CString DocTemplate = _T(""));                //����һ���µ�Word�ĵ�
	BOOL Create(CString DocTemplate = _T(""));                        //�����µ�WORDӦ�ó��򲢴���һ���µ��ĵ�
	void ShowApp();                        //��ʾWORD�ĵ�
	void HideApp();                        //����word�ĵ�
	void PrintPreview();
	//**********************���ĵ�*********************************************
	BOOL OpenDocument(CString fileName);//���Ѿ����ڵ��ĵ���
	BOOL Open(CString fileName);        //�����µ�WORDӦ�ó��򲢴�һ���Ѿ����ڵ��ĵ���
	BOOL SetActiveDocument(short i);    //���õ�ǰ������ĵ���

	//**********************�����ĵ�*********************************************
	BOOL SaveDocument();                //�ĵ����Դ���ʽ�����档
	BOOL SaveDocumentAs(CString fileName);//�ĵ��Դ�����ʽ�����档
	BOOL CloseDocument();
	void CloseApp(); 

	//**********************�ı���д����*****************************************
	void WriteText(CString szText);        //��ǰ��괦д�ı�
	void WriteNewLineText(CString szText, int nLineCount = 1); //��N��д��
	void WriteEndLine(CString szText);    //�ĵ���β��д�ı�
	void WholeStory();                    //ȫѡ�ĵ�����
	void Copy();                        //�����ı����ݵ�������
	void InsertFile(CString fileName);    //�����ص��ļ�ȫ������д�뵽��ǰ�ĵ��Ĺ�괦��

	//**********************ͼƬ�������*****************************************
	void InsertShapes(CString fileName);//�ڵ�ǰ����λ�ò���ͼƬ

	//**********************�����Ӳ������*****************************************
	void InsertHyperlink(CString fileLink);//�������ӵ�ַ�����������·����

public:
	// ����bkName��ǩ�����޸�����ΪbkText���ɹ�����TRUE��ʧ�ܷ���FALSE
	BOOL BookmarkText(CString bkName, CString bkText);
	//ɾ��������ǩ
	BOOL DeleteAllBookmarks();
public:
	void ActivateApp(void);
};


