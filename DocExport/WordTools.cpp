#include "WordTools.h"
// WordTools.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Resource.h"
#include "DocExport.h"


// CWordTools

CWordTools::CWordTools()
{
	
}

CWordTools::~CWordTools()
{
	COleVariant vTrue((short)TRUE),    
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	//m_wdDoc.Save();
// 	m_wdApp.Quit(vFalse,    // SaveChanges.
// 		vTrue,            // OriginalFormat.
// 		vFalse            // RouteDocument.
// 		);
	//�ͷ��ڴ�������Դ
	//m_wdBookmark.ReleaseDispatch();
	m_wdBookmarks.ReleaseDispatch();
	m_wdInlineShape.ReleaseDispatch();
	m_wdInlineShapes.ReleaseDispatch();
	//m_wdTb.ReleaseDispatch();
	m_wdRange.ReleaseDispatch();
	m_wdSel.ReleaseDispatch();
	//m_wdFt.ReleaseDispatch();
	m_wdDoc.ReleaseDispatch();
	m_wdDocs.ReleaseDispatch();
	m_wdApp.ReleaseDispatch();
}



BOOL CWordTools::CreateApp()
{
	if (FALSE == m_wdApp.CreateDispatch(_T("Word.Application")))
	{
		AfxMessageBox(_T("Application����ʧ�ܣ���ȷ����װ��word 2000�����ϰ汾!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	return TRUE;
}

BOOL CWordTools::CreateDocuments()
{
	if (FALSE == CreateApp()) 
	{
		return FALSE;
	}
	m_wdDocs.AttachDispatch(m_wdApp.GetDocuments());
	if (!m_wdDocs.m_lpDispatch) 
	{
		AfxMessageBox(_T("Documents����ʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	return TRUE;
}
BOOL CWordTools::CreateDocument(CString DocTemplate/* = _T("")*/)
{
	if (!m_wdDocs.m_lpDispatch) 
	{
		AfxMessageBox(_T("DocumentsΪ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	if (DocTemplate.IsEmpty())
	{
		//CString strDotName;
		//CHAR szSknName [ MAX_PATH ];
		if( !ResToFile( IDR_PCI_DOT,_T("DOT"), DocTemplate))
		{
			//AfxMessageBox(_T("d"));
			return FALSE;
		}	
	}
	COleVariant varTrue(short(1),VT_BOOL),vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	CComVariant Template(DocTemplate);    //û��ʹ��WORD���ĵ�ģ��
	CComVariant NewTemplate(false),DocumentType(0),Visible;

	m_wdDocs.Add(&Template,&NewTemplate,&DocumentType,&Visible);    

	//�õ�document����
	m_wdDoc = m_wdApp.GetActiveDocument();
	if (!m_wdDoc.m_lpDispatch) 
	{
		AfxMessageBox(_T("Document��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	//�õ�selection����
	m_wdSel = m_wdApp.GetSelection();
	if (!m_wdSel.m_lpDispatch) 
	{
		AfxMessageBox(_T("Select��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	//�õ�Range����
	m_wdRange = m_wdDoc.Range(vOptional,vOptional);
	if(!m_wdRange.m_lpDispatch)
	{
		AfxMessageBox(_T("Range��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	//�õ�Bookmark����
	m_wdBookmarks = m_wdDoc.GetBookmarks();
	if(!m_wdBookmarks.m_lpDispatch)
	{
		AfxMessageBox(_T("Bookmark��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	return TRUE;
}

BOOL CWordTools::Create(CString DocTemplate/* = _T("")*/)
{
	if (FALSE == CreateDocuments()) 
	{
		return FALSE;
	}
	return CreateDocument(DocTemplate);
}

void CWordTools::ShowApp()
{
	m_wdApp.SetVisible(TRUE);
	m_wdApp.Activate();
}

void CWordTools::PrintPreview()
{
	m_wdApp.SetVisible(TRUE);
	m_wdApp.Activate();
	m_wdDoc.PrintPreview();

}

void CWordTools::HideApp()
{
	m_wdApp.SetVisible(FALSE);
}

BOOL CWordTools::OpenDocument(CString fileName)
{
	if (!m_wdDocs.m_lpDispatch) 
	{
		AfxMessageBox(_T("DocumentsΪ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}

	COleVariant vTrue((short)TRUE),    
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		vZ((short)0);
	COleVariant     vFileName(fileName);

	//�õ�document����
	m_wdDoc.AttachDispatch(m_wdDocs.Open(
		vFileName,        // FileName
		vTrue,            // Confirm Conversion.
		vFalse,            // ReadOnly.
		vFalse,            // AddToRecentFiles.
		vOptional,        // PasswordDocument.
		vOptional,        // PasswordTemplate.
		vOptional,        // Revert.
		vOptional,        // WritePasswordDocument.
		vOptional,        // WritePasswordTemplate.
		vOptional,        // Format. // Last argument for Word 97
		vOptional,        // Encoding // New for Word 2000/2002
		vOptional,        // Visible
		//*����4����word2003��Ҫ�Ĳ��������汾��word2000��
			vOptional,    // OpenAndRepair
			vZ,            // DocumentDirection wdDocumentDirection LeftToRight
			vOptional,    // NoEncodingDialog
			vOptional
			)                // Close Open parameters
			);                    // Close AttachDispatch

	if (!m_wdDoc.m_lpDispatch) 
	{
		AfxMessageBox(_T("Document��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	//�õ�selection����
	m_wdSel = m_wdApp.GetSelection();
	if (!m_wdSel.m_lpDispatch) 
	{
		AfxMessageBox(_T("Select��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	//�õ�ȫ��DOC��Range����
	m_wdRange = m_wdDoc.Range(vOptional,vOptional);
	if(!m_wdRange.m_lpDispatch)
	{
		AfxMessageBox(_T("Range��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	return TRUE;
}

BOOL CWordTools::Open(CString fileName)
{
	if (FALSE == CreateDocuments()) 
	{
		return FALSE;
	}
	return OpenDocument(fileName);
}

BOOL CWordTools::SetActiveDocument(short i)
{
	COleVariant     vIndex(i),vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	m_wdDoc.AttachDispatch(m_wdDocs.Item(vIndex));
	m_wdDoc.Activate();
	if (!m_wdDoc.m_lpDispatch) 
	{
		AfxMessageBox(_T("Document��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	//�õ�selection����
	m_wdSel = m_wdApp.GetSelection();
	if (!m_wdSel.m_lpDispatch) 
	{
		AfxMessageBox(_T("Select��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	//�õ�ȫ��DOC��Range����
	m_wdRange = m_wdDoc.Range(vOptional,vOptional);
	if(!m_wdRange.m_lpDispatch)
	{
		AfxMessageBox(_T("Range��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	HideApp();
	return TRUE;
}

BOOL CWordTools::SaveDocument()
{
	if (!m_wdDoc.m_lpDispatch) 
	{
		AfxMessageBox(_T("Document��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	m_wdDoc.Save();
	return TRUE;
}

BOOL CWordTools::SaveDocumentAs(CString fileName)
{
	if (!m_wdDoc.m_lpDispatch) 
	{
		AfxMessageBox(_T("Document��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	COleVariant vTrue((short)TRUE),    
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vFileName(fileName);

	m_wdDoc.SaveAs(
		vFileName,		//Filename
		COleVariant( (long) wdFormatDocument),				//wdFormatDOSText   =   4 
		vFalse,				//LockComments   
		COleVariant(_T("")),		//Password   
		vFalse,				//Add   to   recent   files
		COleVariant(_T("")),		//Write   password  
		vFalse,			//ReadOnlyRecommended   
		vFalse,			//Embed   TrueType   fonts   
		vFalse,			//SaveNativePictureFormat   
		vFalse,			//SaveForms   data   
		vFalse,			//SaveAsAOCELetter
		vFalse,			//Encoding   
		vFalse,			//InsertLineBreaks   
		vFalse,			//AllowSubstitutions   
		vFalse,			//LineEnding   
		vFalse			//AddBiDiMarks   
		); 

	return    TRUE;
}

BOOL CWordTools::CloseDocument()
{
	COleVariant vTrue((short)TRUE),    
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	m_wdDoc.Close(vFalse,    // SaveChanges.
		vTrue,            // OriginalFormat.
		vFalse            // RouteDocument.
		);
	m_wdDoc.AttachDispatch(m_wdApp.GetActiveDocument());
	if (!m_wdDoc.m_lpDispatch) 
	{
		AfxMessageBox(_T("Document��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	//�õ�selection����
	m_wdSel = m_wdApp.GetSelection();
	if (!m_wdSel.m_lpDispatch) 
	{
		AfxMessageBox(_T("Select��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	//�õ�ȫ��DOC��Range����
	m_wdRange = m_wdDoc.Range(vOptional,vOptional);
	if(!m_wdRange.m_lpDispatch)
	{
		AfxMessageBox(_T("Range��ȡʧ��!"), MB_OK|MB_ICONWARNING);
		return FALSE;
	}
	return TRUE;
}

void CWordTools::CloseApp()
{
	COleVariant vTrue((short)TRUE),    
		vFalse((short)FALSE);
	m_wdApp.Quit(vFalse,    // SaveChanges.
		vTrue,            // OriginalFormat.
		vFalse            // RouteDocument.
		);
	//�ͷ��ڴ�������Դ
	//m_wdBookmark.ReleaseDispatch();
	m_wdBookmarks.ReleaseDispatch();
	m_wdInlineShape.ReleaseDispatch();
	m_wdInlineShapes.ReleaseDispatch();
	//m_wdTb.ReleaseDispatch();
	m_wdRange.ReleaseDispatch();
	m_wdSel.ReleaseDispatch();
	//m_wdFt.ReleaseDispatch();
	m_wdDoc.ReleaseDispatch();
	m_wdDocs.ReleaseDispatch();
	m_wdApp.ReleaseDispatch();
}

void CWordTools::WriteText(CString szText)
{
	m_wdSel.TypeText(szText);
}

void CWordTools::WriteNewLineText(CString szText, int nLineCount /**//* = 1 */)
{
	int i;
	if (nLineCount <= 0)
	{
		nLineCount = 0;
	}
	for (i = 0; i < nLineCount; i++)
	{
		m_wdSel.TypeParagraph();
	}
	WriteText(szText);
}

void CWordTools::WriteEndLine(CString szText)
{
	m_wdRange.InsertAfter(szText);
}

void CWordTools::WholeStory()
{
	m_wdRange.WholeStory();
}

void CWordTools::Copy()
{
	m_wdRange.CopyAsPicture();
}

void CWordTools::InsertFile(CString fileName)
{
	COleVariant     vFileName(fileName),
		vTrue((short)TRUE),
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR),
		vNull(_T(""));
	/**//*
		void InsertFile(LPCTSTR FileName, VARIANT* Range, VARIANT* ConfirmConversions, VARIANT* Link, VARIANT* Attachment);
		*/
	m_wdSel.InsertFile(
		fileName,
		vNull,
		vFalse,
		vFalse,
		vFalse
		);
}

void CWordTools::InsertShapes(CString fileName)
{
	COleVariant vTrue((short)TRUE),    
		vFalse((short)FALSE),
		vOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	m_wdInlineShapes=m_wdSel.GetInlineShapes();
	m_wdInlineShape=m_wdInlineShapes.AddPicture(fileName,vFalse,vTrue,vOptional);
}

void CWordTools::InsertHyperlink(CString fileLink)
{
	COleVariant     vAddress(fileLink),vSubAddress(_T(""));
	Range aRange = m_wdSel.GetRange();
	Hyperlinks vHyperlinks(aRange.GetHyperlinks());

	vHyperlinks.Add(
		aRange,            //Object�����衣ת��Ϊ�����ӵ��ı���ͼ�Ρ�
		vAddress,         //Variant ���ͣ���ѡ��ָ�������ӵĵ�ַ���˵�ַ�����ǵ����ʼ���ַ��Internet ��ַ���ļ�������ע�⣬Microsoft Word �����õ�ַ����ȷ�ԡ�
		vSubAddress,     //Variant ���ͣ���ѡ��Ŀ���ļ��ڵ�λ����������ǩ���������������õ�Ƭ��š�
		vAddress,         //Variant ���ͣ���ѡ�������ָ�����ָ���ĳ�������ʱ��ʾ�Ŀ���������Ļ��ʾ�����ı���Ĭ��ֵΪ Address��
		vAddress,         //Variant ���ͣ���ѡ��ָ���ĳ����ӵ���ʾ�ı����˲�����ֵ��ȡ���� Anchor ָ�����ı���ͼ�Ρ�
		vSubAddress        //Variant ���ͣ���ѡ��Ҫ�����д�ָ���ĳ����ӵĿ�ܻ򴰿ڵ����֡�
		); 
	vHyperlinks.ReleaseDispatch();
}
// ����bkName��ǩ�����޸�����ΪbkText���ɹ�����TRUE��ʧ�ܷ���FALSE
BOOL CWordTools::BookmarkText(CString bkName, CString bkText)
{
	if(!m_wdBookmarks.Exists(bkName))
	{
	//	AfxMessageBox(bkName_T("������"));
		return FALSE;
	}
	COleVariant  vWhat((long)wdGoToBookmark),//����ֵ��-1
		vWhich,//¼�ƺ���û�������
		vCount((short)0),//¼�ƺ���û��������������ǵڼ�����ǩ
		vName(bkName);//��ǩ��
	m_wdSel.GoTo(vWhat,vWhich,vCount,vName);
	m_wdSel.TypeText(bkText);
	return TRUE;
}

// ɾ����ǩ���ɹ�����TRUE��ʧ�ܷ���FALSE
BOOL CWordTools::DeleteAllBookmarks()
{
/*
	for (int i=0;i<m_wdBookmarks.GetCount();i++)
	{
		COleVariant vI((long)i);
		((Bookmark*)m_wdBookmarks.Item(vI))->Delete();
	}
	return TRUE;
	*/
	return FALSE;
}



void CWordTools::ActivateApp(void)
{
	m_wdApp.Activate();
}
