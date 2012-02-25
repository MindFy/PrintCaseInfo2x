// PrintCaseInfoView.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "PrintCaseInfo2x.h"
#include "PrintCaseInfoView.h"
#include "PrintCaseInfo2xDoc.h"
#include "PrintInfoEx.h"
#include "DocExportInfo.h"

#define PAGE_LEFT 300
#define PAGE_TOP 200
#define PAGE_RIGHT 200
#define PAGE_BOTTOM 200
#define LINE_HEIGHT 71
#define  MUTI_TEXT_BLANK_WIDTH 150

extern inline CString toStringFomat( int num,CString formater);
extern inline CString toStringFomat( float num,CString formater);
extern inline CString toString(CString str,CString itemName);
extern inline CString toString( CTime time , CString itemName=_T("") ,  bool hasHour = false);

inline CString toString(CString str,CString itemName)
{
    return itemName +_T(":")+ str ;
}





/*
inline CString toStringNotNull( CString str,CString itemName)
{
return (str == _T("")) ? _T("")  : itemName+str;
}
*/
inline CString toStringFomat( int num,CString formater)
{
    CString text;
    text.Format( formater ,num  );
    return text;
}

inline CString toStringFomat( float num,CString formater)
{
    CString text;
    text.Format( formater ,num  );
    return text;
}

inline CString toString( CTime time ,CString itemName ,   bool hasHour )
{
    CString t;
    if ( hasHour )
    {  
        t.Format( _T("%4d��%02d��%02d��%02dʱ") , time.GetYear() ,time.GetMonth() , time.GetDay() , time.GetHour());
    }
    else
    {
        t.Format( _T("%4d��%02d��%02d��") , time.GetYear() ,time.GetMonth() , time.GetDay() );
    }
    return itemName +t;
}

// CPrintCaseInfoView

IMPLEMENT_DYNCREATE(CPrintCaseInfoView, CScorllCenterFormView)

CPrintCaseInfoView::CPrintCaseInfoView( )
: CScorllCenterFormView(CPrintCaseInfoView::IDD)
{
// 	PHY_LEFT= 0;
// 	PHY_RIGHT = 0;
// 	PHY_TOP = 0;
// 	PHY_BOTTOM = 0;
// 	PAGE_WIDTH=2100;
// 	PAGE_HEIGHT=2970;
}

CPrintCaseInfoView::CPrintCaseInfoView(UINT nIDTemplate )
    : CScorllCenterFormView(nIDTemplate)
{
// 	PHY_LEFT= 0;
// 	PHY_RIGHT = 0;
// 	PHY_TOP = 0;
// 	PHY_BOTTOM = 0;
// 	PAGE_WIDTH=2100;
// 	PAGE_HEIGHT=2970;
}

CPrintCaseInfoView::~CPrintCaseInfoView()
{
}

void CPrintCaseInfoView::DoDataExchange(CDataExchange* pDX)
{
    CScorllCenterFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPrintCaseInfoView, CScorllCenterFormView)
    // ��׼��ӡ����
    ON_COMMAND(ID_FILE_PRINT_DIRECT, &OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, &OnFilePrintPreview)
    ON_COMMAND(ID_FILE_PRINT, &OnFilePrint)
    ON_MESSAGE(WM_SAVEFOCUS, OnSaveFocus)
	ON_MESSAGE_BOOL(WM_UPDATE_DOC_FROM_VIEW, OnUpdateDocFromView)
END_MESSAGE_MAP()


// CPrintCaseInfoView ���

#ifdef _DEBUG
void CPrintCaseInfoView::AssertValid() const
{
    CScorllCenterFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPrintCaseInfoView::Dump(CDumpContext& dc) const
{
    CScorllCenterFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPrintCaseInfoView ��Ϣ�������

LRESULT CPrintCaseInfoView::OnSaveFocus(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    CScorllCenterFormView::SaveFocusControl();
    return (LRESULT)0;
}

// CPrintCaseInfoView ��ӡ
BOOL CPrintCaseInfoView::OnPreparePrinting(CPrintInfo* pInfo)
{
    //��������
    UpdateData(TRUE);
    pInfo->SetMaxPage(7);
    //	pInfo->m_bDirect=TRUE;
    return DoPreparePrinting(pInfo);
}

void CPrintCaseInfoView::SetPageMargin(CDC *pDC, CPrintInfo *pInfo, int l, int t, int r, int b)
{
    double scaleX = 254.0 / (double)GetDeviceCaps(pDC->m_hAttribDC, LOGPIXELSX);
    double scaleY = 254.0 / (double)GetDeviceCaps(pDC->m_hAttribDC, LOGPIXELSY);

    int x = GetDeviceCaps(pDC->m_hAttribDC,	PHYSICALOFFSETX); 
    int y = GetDeviceCaps(pDC->m_hAttribDC,	PHYSICALOFFSETY); 
    int w = GetDeviceCaps(pDC->m_hAttribDC,	PHYSICALWIDTH); 
    int h = GetDeviceCaps(pDC->m_hAttribDC,	PHYSICALHEIGHT); 

    int PAGE_WIDTH = (int)((double)w*scaleX);//ֽ�ſ�ȣ���λ0.1mm
    int PAGE_HEIGHT= (int)((double)h*scaleY);//ֽ�Ÿ߶ȣ���λ0.1mm
    int PHY_LEFT = (int)((double)x*scaleY);//������߾࣬��λ0.1mm
    int PHY_TOP = (int)((double)y*scaleY);// �����ϱ߾࣬��λ0.1mm

    CRect rcTemp =pInfo->m_rectDraw;
    //TRACE("RECT-1 %d %d %d %d %d %d\n",rcTemp.left,rcTemp.top,rcTemp.right,rcTemp.bottom,rcTemp.Width(),rcTemp.Height());
    rcTemp.NormalizeRect();
    //TRACE("RECT-2 %d %d %d %d %d %d\n",rcTemp.left,rcTemp.top,rcTemp.right,rcTemp.bottom,rcTemp.Width(),rcTemp.Height());
    int PHY_RIGHT = PAGE_WIDTH - rcTemp.Width() - PHY_LEFT; // �����ұ߾࣬��λ0.1mm
    int PHY_BOTTOM= PAGE_HEIGHT - rcTemp.Height() - PHY_TOP; // �����±߾࣬��λ0.1mm
    if(PHY_RIGHT<0) PHY_RIGHT=0;
    if(PHY_BOTTOM<0) PHY_BOTTOM=0;
    //TRACE("��ӡ������߾� ��%d ��%d ��%d ��%d \n",PHY_LEFT,PHY_TOP,PHY_RIGHT,PHY_BOTTOM);

    // ���߾�С������߾࣬���������
    if (l < PHY_LEFT) l = PHY_LEFT;
    if (t < PHY_TOP) t = PHY_TOP;
    if (r < PHY_RIGHT) r = PHY_RIGHT;
    if (b < PHY_BOTTOM) b = PHY_BOTTOM;

    pInfo->m_rectDraw.left +=(l-PHY_LEFT);
    pInfo->m_rectDraw.top -=(t-PHY_TOP) ;
    pInfo->m_rectDraw.right -=  (r-PHY_RIGHT);
    pInfo->m_rectDraw.bottom += (b-PHY_BOTTOM);

}
void CPrintCaseInfoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* pInfo)
{
    pInfo->m_strPageDesc=_T("������ӡԤ�� ��%uҳ\n������ӡԤ�� ��%u-%uҳ\n");
    if ( ! pInfo->m_lpUserData)
    {
        pInfo->m_lpUserData=new CPrintInfoEx(pInfo->m_rectDraw);
    }
}

void CPrintCaseInfoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* pInfo)
{
    //��Ӵ�ӡ����е��������
    if(pInfo->m_lpUserData)
    {
        delete (CPrintInfoEx*)pInfo->m_lpUserData;
        pInfo->m_lpUserData=NULL;
    }
}





// CPrintCaseInfoView ��Ϣ�������

void CPrintCaseInfoView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    CScorllCenterFormView::OnPrepareDC(pDC, pInfo);
    pDC->SetMapMode(MM_LOMETRIC);
// 	if(pDC->IsPrinting())//�����ڽ��д�ӡ���жϵ�ǰҳ���ݣ�
// 	{
// 		//pDC->SetWindowOrg(PHY_LEFT,-(PAGE_HEIGHT-PHY_BOTTOM-PHY_TOP)*(pInfo->m_nCurPage-1)-PHY_TOP);
// 
// 	}
}

void CPrintCaseInfoView::PageHeaderFooter(CDC* pDC, CPrintInfo* pInfo, CString nv_fang_xing_ming ,CString bing_li_hao ,CTime time)
{


    CFont *oldFont = pDC->SelectObject(&mainFont);
    // ҳü
    UINT oldTextAlign = pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);

    int mid = (pInfo->m_rectDraw.left + pInfo->m_rectDraw.right) / 2;
    pDC->TextOut(mid, pInfo->m_rectDraw.top , _T("����������ҽԺ��ֳҽѧ��"));
    pInfo->m_rectDraw.top -=40;
    pDC->MoveTo(pInfo->m_rectDraw.TopLeft());
    pDC->LineTo(pInfo->m_rectDraw.right,pInfo->m_rectDraw.top);
    //  int xh = pInfo->m_rectDraw.top-50;
    pInfo->m_rectDraw.top -=60;   
    pDC->SelectObject(&titleFont);
    pDC->SetTextAlign(TA_CENTER | TA_TOP);
    switch ( pInfo->m_nCurPage )
    {
    case 2:
        pDC->TextOut(mid, pInfo->m_rectDraw.top , _T("���ศ����ֳ������1��"));
        break;
    case 3:
        pDC->TextOut(mid, pInfo->m_rectDraw.top , _T("���ศ����ֳ������2��"));
        break;
    case 4:
        pDC->TextOut(mid, pInfo->m_rectDraw.top , _T("���ศ����ֳ������3��"));
        break;
    case 5:
        pDC->TextOut(mid, pInfo->m_rectDraw.top , _T("���ศ����ֳ�з�������1��"));
        break;
    case 6:
        pDC->TextOut(mid, pInfo->m_rectDraw.top , _T("���ศ����ֳ�з�������2��"));
        break;
    case 7:
        pDC->TextOut(mid, pInfo->m_rectDraw.top , _T("���ศ����ֳ����"));
        break;
    }
    pDC->SetTextAlign(oldTextAlign);
    pDC->SelectObject(&smaleFont);
    CPrintInfoEx* pInfoEx=(CPrintInfoEx*)pInfo->m_lpUserData;
    pInfoEx->setRect( pInfo->m_rectDraw);
    pInfoEx->rc.top +=30;
    pInfoEx->setLeft( pInfo->m_rectDraw.right - 450 );
    pInfoEx->setRectHeight( 60);
    if ( pInfo->m_nCurPage ==2 )
    {
        //pInfoEx->drawBox( pDC );
        PrintText( pDC ,pInfo ,  toString( time , _T("��    �ڣ�") ,false ) );
    }
    else
    {
        PrintText( pDC ,pInfo ,  _T("Ů��������") + nv_fang_xing_ming  );
    }
    pInfoEx->MoveDown();
    pInfoEx->setRectHeight( 60);
    PrintText( pDC ,pInfo ,  _T("�� �� �ţ�") + bing_li_hao );
    pDC->SelectObject(&mainFont);

    //ҳ��
    CString buf;
    if ( pInfo->m_nCurPage==7 )
    {
        buf = _T( "��1ҳ" );
    } 
    else
    {
        buf.Format(_T("�� %d ҳ"), pInfo->m_nCurPage-1);
    }

    pDC->SetTextAlign(TA_RIGHT | TA_TOP);
    pDC->TextOut(pInfo->m_rectDraw.right, pInfo->m_rectDraw.bottom - 20, buf);
    pDC->SelectObject(oldFont);
    pDC->SetTextAlign(oldTextAlign);
}

void CPrintCaseInfoView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    pDC->LineTo(100,100);

    CPrintCaseInfo2xDoc* pDoc =(CPrintCaseInfo2xDoc*) GetDocument();
    if (!pDoc)
    {
        AfxMessageBox(_T("Err!"));
        return;
    }
    CCommonInfo *pCommonInfo =&pDoc->commonInfo;
    CMaleInfo *pMaleInfo=&pDoc->maleInfo;      
    CFemaleInfo *pFemaleInfo=&pDoc->femaleInfo;   
    CPrintInfoEx* pInfoEx=(CPrintInfoEx*)pInfo->m_lpUserData;


    SetPageMargin(pDC,pInfo, PAGE_LEFT, PAGE_TOP, PAGE_RIGHT, PAGE_BOTTOM);
    //�����Աߵ���Ϣ -- ���
    smaleFont.CreatePointFont(105,_T("����"),pDC);

    //С�������� -- С�ĺ�
    boldFont.CreatePointFont(105,_T("����"),pDC);
    LOGFONT lf;
    boldFont.GetLogFont(&lf);
    lf.lfWeight = FW_BOLD;
    boldFont.DeleteObject();
    boldFont.CreateFontIndirect(&lf);
    //�������� --  С��
    mainFont.CreatePointFont(102,_T("����"),pDC);
    mainFont.GetLogFont(&lf);
    mainFont.DeleteObject();
    mainFont.CreateFontIndirect(&lf);
    mainFont.GetLogFont(&lf);
    TRACE("# %ld #\n",lf.lfHeight);
    //ҳ�������� -- ��������
    titleFont.CreatePointFont(150,_T("����"),pDC);
    titleFont.GetLogFont(&lf);
    lf.lfWeight = FW_BOLD;
    titleFont.DeleteObject();
    titleFont.CreateFontIndirect(&lf);

    CBrush   br;   
    br.CreateStockObject(NULL_BRUSH);
    CBrush*oldBrush = pDC->SelectObject(&br);
    CFont *oldFont = pDC->SelectObject(&mainFont);    
    int oldBkMode = pDC->SetBkMode(TRANSPARENT);   
    COLORREF oldTextColor = pDC->SetTextColor(RGB(0,0,0));
    if(pInfo->m_nCurPage!=1)
    {
        PageHeaderFooter(pDC,pInfo , pFemaleInfo->EN_name , pCommonInfo->bing_li_hao ,pCommonInfo->date_ye_mei);
        pInfo->m_rectDraw.top-=100;
    }
    CString text;
    int tmpX=0; 
    int tmpY=0;

    CFont ft;

    switch (pInfo->m_nCurPage)
    {
    case 1:
        //	pDC->Rectangle(pInfo->m_rectDraw);
        pInfoEx->setRect(pInfo->m_rectDraw);
        pInfoEx->setRectHeight( 5*LINE_HEIGHT);
        ft.CreatePointFont(350 ,_T("����"),pDC);
        PrintTextMult2(pDC,pInfo,toString( pCommonInfo->bing_li_hao , _T("���") ) );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        //pInfoEx->drawBox( pDC );
        ft.DeleteObject();
        ft.CreatePointFont(160 ,_T("����"),pDC);
        pDC->SelectObject(&ft);
        PrintText(pDC,pInfo, _T("����������ҽԺ��ֳҽѧ��") , 0 , 0 , true );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 3*LINE_HEIGHT);
        //pInfoEx->drawBox( pDC );
        ft.DeleteObject();
        ft.CreatePointFont(360 ,_T("����"),pDC);
        pDC->SelectObject( &ft);
		//VER_DO:2.2 
        //PrintText(pDC,pInfo, _T("���˹��ھ�����") , 0 , 0 , true );
        PrintText(pDC,pInfo, _T("���ศ����ֳ��������") , 0 , 0 , true );
        //��һ��
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);        

        tmpX = pInfoEx->rc.Width()/2 + pInfo->m_rectDraw.left ;

        //Ů������ 
        pInfoEx->MoveDown();
        pInfoEx->SetRight( tmpX );
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        //pInfoEx->drawBox( pDC );
        pDC->SelectObject( &titleFont );
        PrintTextMult2(pDC,pInfo, _T("Ů������:") , 1 );
        ft.DeleteObject();
        ft.CreatePointFont(160 ,_T("����"),pDC);
        pDC->SelectObject( &ft );
        PrintTextMult2(pDC,pInfo, pFemaleInfo->EN_name);
        //�з�����
        pInfoEx->MoveRight();
        pInfoEx->SetRight(  pInfo->m_rectDraw.right );
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        //pInfoEx->drawBox( pDC );
        pDC->SelectObject( &titleFont );
        PrintTextMult2(pDC,pInfo, _T("�з�����:") , 1 );
        pDC->SelectObject( &ft );
        PrintTextMult2(pDC,pInfo, pMaleInfo->EN_name);
        //Ů���绰
        pInfoEx->MoveDown();
        pInfoEx->setLeft( pInfo->m_rectDraw.left );
        pInfoEx->SetRight( tmpX );
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        //pInfoEx->drawBox( pDC );
        pDC->SelectObject( &titleFont );
        PrintTextMult2(pDC,pInfo, _T("�绰:") , 1 );
        pDC->SelectObject( &ft );
        PrintTextMult2(pDC,pInfo, pFemaleInfo->EN_phone);
        //�з��绰
        pInfoEx->MoveRight();
        pInfoEx->SetRight(  pInfo->m_rectDraw.right );
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        //pInfoEx->drawBox( pDC );
        pDC->SelectObject( &titleFont );
        PrintTextMult2(pDC,pInfo, _T("�绰:") , 1 );
        pDC->SelectObject( &ft );
        PrintTextMult2(pDC,pInfo, pMaleInfo->EN_phone);

        //Ů����λ
        pInfoEx->MoveDown();
        pInfoEx->setLeft( pInfo->m_rectDraw.left );
        pInfoEx->SetRight( tmpX );
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        //pInfoEx->drawBox( pDC );
        pDC->SelectObject( &titleFont );
        PrintTextMult2(pDC,pInfo, _T("��λ:") , 1 );
        pDC->SelectObject( &ft );
        PrintTextMult2(pDC,pInfo, pFemaleInfo->EN_company);
        //�з���λ
        pInfoEx->MoveRight();
        pInfoEx->SetRight(  pInfo->m_rectDraw.right );
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        //pInfoEx->drawBox( pDC );
        pDC->SelectObject( &titleFont );
        PrintTextMult2(pDC,pInfo, _T("��λ:") , 1 );
        pDC->SelectObject( &ft );
        PrintTextMult2(pDC,pInfo, pMaleInfo->EN_company);
        //ͨѶ��ַ
        pInfoEx->MoveDown();
        pInfoEx->setLeft( pInfo->m_rectDraw.left );
        pInfoEx->SetRight( pInfo->m_rectDraw.right );
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        //pInfoEx->drawBox( pDC );
        pDC->SelectObject( &titleFont );
        PrintTextMult2(pDC,pInfo, _T("ͨѶ��ַ:")  ,1 );
        pDC->SelectObject( &ft );
        PrintTextMult2(pDC,pInfo, pFemaleInfo->EN_address);
        //ͨѶ��ַ
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        //pInfoEx->drawBox( pDC );
        pDC->SelectObject( &titleFont );
        PrintTextMult2(pDC,pInfo, _T("��������:")  ,1 );
        pDC->SelectObject( &ft );
        PrintTextMult2(pDC,pInfo, pFemaleInfo->EN_postalcode);
        //���
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        //pInfoEx->drawBox( pDC );
        pDC->SelectObject( &titleFont );
        PrintText(pDC,pInfo, _T("���:")   );
        pInfoEx->MoveDown();
        pInfoEx->rc.left += MUTI_TEXT_BLANK_WIDTH;
        pInfoEx->rc.right -= MUTI_TEXT_BLANK_WIDTH;
        pInfoEx->setRectHeight( 5*LINE_HEIGHT );
        //	pInfoEx->drawBox( pDC );
        pDC->SelectObject( &ft );
        PrintTextMult2(pDC,pInfo, pFemaleInfo->zhen_duan+_T("\r\n")+pMaleInfo->chu_bu_zhen_duan);
        // 		NewLine( pDC , pInfo );
        // 		PrintTextMult2(pDC,pInfo, pMaleInfo->chu_bu_zhen_duan);
        pInfoEx->SetRight( pInfo->m_rectDraw.right);
        pInfoEx->setLeft( pInfo->m_rectDraw.left);

        //IUIʱ�䣺
        pInfoEx->MoveDown();
        pInfoEx->setLeft( pInfo->m_rectDraw.left );
        pInfoEx->SetRight( tmpX );
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        //pInfoEx->drawBox( pDC );
        pDC->SelectObject( &titleFont );
        PrintTextMult2(pDC,pInfo, _T("IUIʱ��:") , 1 );
        //���
        pInfoEx->MoveRight();
        pInfoEx->SetRight(  pInfo->m_rectDraw.right );
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        //pInfoEx->drawBox( pDC );
        pDC->SelectObject( &titleFont );
        PrintTextMult2(pDC,pInfo, _T("���:") , 1 );
        pDC->SelectObject( &ft );

        break;
    case 2:
        pInfo->m_rectDraw.bottom += 2*LINE_HEIGHT;
        pDC->Rectangle(pInfo->m_rectDraw);

        pInfoEx->setRect(pInfo->m_rectDraw);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        text=_T("Ů������:")+pFemaleInfo->EN_name;
        pDC->SelectObject( & mainFont );
        PrintText(pDC,pInfo,text,1,16);
        text.Format(_T("����:%d"),pFemaleInfo->EN_age);
        PrintText(pDC,pInfo,text,1,8);
        text=_T("ְҵ:")+pFemaleInfo->EN_occupation;
        PrintText(pDC,pInfo,text,1,12);

        text=_T("�Ļ��̶�:")+pFemaleInfo->EN_knowledge_degree;
        PrintText(pDC,pInfo,text,1,16);
        text=_T("����:")+pFemaleInfo->EN_nation;
        PrintText(pDC,pInfo,text,1,10);
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        text=_T("���֤����:")+pFemaleInfo->EN_identity_card;
        PrintText(pDC,pInfo,text);
        //////////////////////////////////////////////////////////////////////////

        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);

        text.Format(_T("�ɷ�����:%s"),pMaleInfo->EN_name);
        PrintText(pDC,pInfo, text, 1 ,16);

        text.Format(_T("����:%d"),pMaleInfo->EN_age);
        PrintText(pDC,pInfo,text , 1 , 8 );
        text=_T("ְҵ:")+pMaleInfo->EN_occupation;
        PrintText(pDC,pInfo,text ,1 ,12);
        text=_T("�Ļ��̶�:")+pMaleInfo->EN_knowledge_degree;
        PrintText(pDC,pInfo,text, 1 , 16);
        text=_T("����:")+pMaleInfo->EN_nation;
        PrintText(pDC,pInfo,text, 1 ,10);

        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        text=_T("���֤����:")+pMaleInfo->EN_identity_card;
        PrintText(pDC,pInfo,text);

        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);

        text= _T("ͨѶ��ַ:")+pFemaleInfo->EN_address;
        PrintText(pDC,pInfo,text, 1 , 42);
        text= _T("��ϵ�绰:")+pFemaleInfo->EN_phone;
        PrintText(pDC,pInfo,text);


        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pDC->SelectObject(&boldFont);
        PrintText(pDC,pInfo,_T("���ߣ�"),0);
        text = pFemaleInfo->zhu_su;
        pDC->SelectObject(&mainFont);
        PrintText(pDC,pInfo,text);

        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(6*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight( 6*LINE_HEIGHT);
       
		pDC->SelectObject(&boldFont);
        PrintTextMult2(pDC,pInfo,_T("�ֲ�ʷ��") , 0 );
		tmpX = pInfoEx->cur.x;
		pInfoEx->setLeft( pInfoEx->rc.left + 10);
		pInfoEx->SetRight( pInfoEx->rc.right - 10);
		pInfoEx->cur.x =tmpX ;
        pDC->SelectObject(&mainFont);
        PrintTextMult2(pDC,pInfo,pFemaleInfo->xian_bing_shi);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft( pInfo->m_rectDraw.left);
        pInfoEx->setRectHeight(5*LINE_HEIGHT);
        pInfoEx->setRectWidth(2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintTextV(pDC,pInfo,_T("����ʷ"));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        NewLine( pDC ,pInfo , true);
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->ji_wang_gan_yan , _T(" ����") ) , 12 );
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->jie_he , _T("���") ) , 12);
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->shen_zang_ji_bing , _T("���༲��") ) );
        NewLine(pDC,pInfo);
        NewHalfLine( pDC ,pInfo , true);
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->xin_xue_guan_ji_bing , _T(" ��Ѫ�ܼ���") ) ,6);
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->mi_niao_xi_tong_gan_ran, _T("����ϵͳ��Ⱦ") ) , 4 );
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->xing_chuan_bo_ji_bing_shi, _T("�Դ�������ʷ") ) );
        NewLine(pDC,pInfo);
        NewHalfLine( pDC ,pInfo , true);
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->lan_wei_yan , _T(" ��β��") )  , 10);
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->pen_qiang_yan , _T("��ǻ��") ) );
        NewLine(pDC,pInfo);
        NewHalfLine( pDC ,pInfo , true);
        PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_shou_shu_shi.toString(_T(" ����ʷ")) ,4);
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->ji_wang_qi_ta, _T("����") ));

        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(4*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        NewLine( pDC ,pInfo , true);
        PrintTextMult2(pDC,pInfo, pFemaleInfo->ci_xi_yan.toString( _T(" ����:%d֧/��") , _T(" ����:��") )  , 6);        
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->xu_jiu , _T("���") )  , 12 );
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->xi_du , _T("����") ) );
        NewLine(pDC,pInfo);
        NewHalfLine( pDC ,pInfo , true);
        PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_yao_wu_guo_min.toString(_T(" ҩ�����ʷ")) , 6);
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->zhong_da_jing_shen_ci_ji , _T("�ش���̼�") )  ,4);
        NewLine(pDC,pInfo);
        NewHalfLine( pDC ,pInfo , true);
        PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_chu_sheng_que_xian.toString( _T(" ����״��") ) ,6);
        PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_chu_sheng_que_xian.toString(_T("����ȱ��")));

        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectWidth(2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintTextV(pDC,pInfo,_T("����ʷ"));
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();

        pInfoEx->setRectHeight(3*LINE_HEIGHT);
        pInfoEx->setRectWidth(2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintTextV(pDC,pInfo,_T("�¾�ʷ"));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        NewLine( pDC ,pInfo , true);
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->chu_chao, _T(" ����%d��") ));
        //�¾�����
        text.Format( _T("�¾�����: %d ��/%s ��" ) , pFemaleInfo->yue_jing_shi_yue_jing_zhou_qi1 , pFemaleInfo->yue_jing_shi_yue_jing_zhou_qi2);
        PrintTextMult2(pDC,pInfo, text, 6 );
        //ĩ���¾�
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->mo_ci_yue_jing ,_T("ĩ���¾�" ) ) , 6 );
        NewLine(pDC,pInfo);
        NewHalfLine( pDC ,pInfo , true);
        //����
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->jing_liang ,_T(" ����" ) ) , 12 );
        //ʹ��
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->tong_jing , _T("ʹ��") ) );

        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(5*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        NewLine( pDC ,pInfo , true);
        //���׽��
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->jin_qin_jie_hun , _T(" ���׽��")  ) );
        //�ٻ�
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->zai_hun , _T("�ٻ�") ) );    
        //����
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->ren_chen , _T("����")  ) );  
        NewLine(pDC,pInfo);
        NewHalfLine( pDC ,pInfo , true);
        //ĩ������ʱ��     
        PrintTextMult2(pDC,pInfo, toString( pFemaleInfo->mo_ci_ren_shen ,_T(" ĩ������ʱ��" ) ) );
        //��
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->yun, _T("��%d��") ) , 6 );    
        //��
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->chan, _T("��%d��") ) , 6 );    
        //�˹�����
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->ren_gong_liu_chan, _T("�˹�����%d��") ));   
        NewLine(pDC,pInfo);
        NewHalfLine( pDC ,pInfo , true);
        //��Ȼ����
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->zi_ran_liu_chan, _T(" ��Ȼ����%d��") ) , 6 );    
        //ҩ��
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->yao_liu, _T("ҩ��%d��") ) , 6 );    
        //����
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->yin_chan , _T("����%d��") ) , 6 );    
        //���
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->zao_chan, _T("���%d��") ));    
        NewLine(pDC,pInfo);
        NewHalfLine( pDC ,pInfo , true);
        //��������
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->gong_wai_yuan_zuo, _T(" ��������%d��") ) , 6); 
        //��������
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->gong_wai_yuan_you, _T("��������%d��") ) , 6 );  
        //���²�
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->zu_yue_chan, _T("���²�%d��") ) , 6 ); 
        //������Ů
        PrintTextMult2(pDC,pInfo, toStringFomat( pFemaleInfo->xian_you_zi_nv, _T("������Ů%d��") ) , 6 ); 
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectWidth(2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintTextV(pDC,pInfo,_T("����ʷ"));
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->SetBottom(pInfo->m_rectDraw.bottom);
        pInfoEx->setRectWidth(2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintTextV(pDC,pInfo,_T("����ʷ"));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        //�Ŵ���ʷ
        NewLine( pDC ,pInfo , true);
        PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_yi_chuan_bing_shi.toString(_T(" �Ŵ���ʷ")));  
        NewLine(pDC,pInfo);
        NewHalfLine( pDC ,pInfo , true);
        //���в�����ʷ
        PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_bu_yun_bu_yu_shi.toString(_T(" ���в�����ʷ")));      
        break;
    case 3:
        pDC->Rectangle(pInfo->m_rectDraw);
        pInfoEx->setRect(pInfo->m_rectDraw);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->setRectHeight(9*LINE_HEIGHT);
        pInfoEx->setRectWidth(2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintTextV(pDC,pInfo,_T("�����"));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        // 		pInfoEx->setRectHeight( LINE_HEIGHT/2 );
        // 		pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        //һ�����T
        PrintText(pDC,pInfo, toStringFomat(pFemaleInfo->yi_ban_qing_kuang_T ,_T(" һ�����: T %.1f��")) , 2 , 20 );       
        //һ�����P
        PrintText(pDC,pInfo, toStringFomat(pFemaleInfo->yi_ban_qing_kuang_P ,_T("P %d ��/��")) , 2 , 12 );      
        //һ�����R
        PrintText(pDC,pInfo, toStringFomat(pFemaleInfo->yi_ban_qing_kuang_R ,_T("R %d ��/��")) , 2 , 12 );      
        //һ�����BP
        text.Format( _T("BP %d/%d mmHg"),pFemaleInfo->yi_ban_qing_kuang_BP1,pFemaleInfo->yi_ban_qing_kuang_BP2 );
        PrintText(pDC,pInfo, text);   
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        //���
        PrintText(pDC,pInfo, toStringFomat(pFemaleInfo->shen_gao ,_T(" ���: %d cm")) , 0 , 34 );    
        //����
        PrintText(pDC,pInfo, toStringFomat(pFemaleInfo->ti_zhong ,_T("����: %.1f kg"))); 
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        //Ӫ��
        PrintText(pDC,pInfo, pFemaleInfo->cs_ying_yang.toString(_T(" Ӫ��")) , 0 , 34 );
        //����
        PrintText(pDC,pInfo, pFemaleInfo->cs_fa_yu.toString(_T("����")) );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        //����
        PrintText(pDC,pInfo, pFemaleInfo->cs_jing_shen.toString(_T(" ����"))  , 0 , 34 );
        //ë��
        PrintText(pDC,pInfo, pFemaleInfo->cs_mao_fa.toString(_T("ë��")));
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        //Ƥ���Ĥ
        PrintText(pDC,pInfo, pFemaleInfo->cs_pi_fu_nian_mo.toString(_T(" Ƥ���Ĥ")) , 0 , 34 );
        //�ܰͽ�
        PrintText(pDC,pInfo, pFemaleInfo->cs_lin_ba_jie.toString(_T("�ܰͽ�")));
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        //�鷿
        PrintText(pDC,pInfo, pFemaleInfo->cs_ru_fang.toString(_T(" �鷿")) , 0 , 34 );
        //����
        PrintText(pDC,pInfo, toString(pFemaleInfo->yi_ru, _T("����") ));
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        //��
        PrintText(pDC,pInfo, pFemaleInfo->cs_xin.toString(_T(" ��")) , 0 , 34 );
        //��
        PrintText(pDC,pInfo, pFemaleInfo->cs_fei.toString(_T("��")));
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        //��
        PrintText(pDC,pInfo, pFemaleInfo->cs_gan.toString(_T(" ��")) , 0 , 34 );
        //Ƣ
        PrintText(pDC,pInfo, pFemaleInfo->cs_pi.toString(_T("Ƣ")));
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        //��
        PrintText(pDC,pInfo, pFemaleInfo->cs_shen.toString(_T(" ��")) , 0 , 34 );
        //������֫
         PrintText(pDC,pInfo, pFemaleInfo->cs_ji_zhu_si_zhi.toString(_T("������֫")));

        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(4*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        NewHalfLine( pDC , pInfo , true );
        //����
        PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_wai_yin.toString(_T(" ����")) , 6 );        
        //����
        PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_yin_dao.toString(_T("����")));        
        NewLine(pDC,pInfo);
        NewSmallHalfLine( pDC , pInfo , true );
        //����
        if (  pFemaleInfo->cs_gong_jing.strBase == _T( "����"))
        {
            PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_gong_jing.toString(_T(" ���������ã�"))  , 6 ); 
        } 
        else
        {
            PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_gong_jing.toString(_T(" ����"))  , 6 ); 
        }
        //��������
        PrintTextMult2(pDC,pInfo, toString(pFemaleInfo->gong_jing_qi_ta,_T("����")) );  
        NewLine(pDC,pInfo);
        NewSmallHalfLine( pDC , pInfo , true );
        //�ӹ�
        PrintTextMult2(pDC,pInfo, toString(pFemaleInfo->zi_gong,_T(" �ӹ�")) , 6 );  
        //�ӹ���С
        PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_fu_ke_jian_cha_zi_gong_da_xiao.toString(_T("��С"))); 
        NewLine(pDC,pInfo);
        NewSmallHalfLine( pDC , pInfo , true );
        //�ӹ��ʵ�
        PrintTextMult2(pDC,pInfo, toString(pFemaleInfo->zhi_di,_T(" �ӹ��ʵ�")) , 6 );  
        //�ӹ����
        PrintTextMult2(pDC,pInfo, toString(pFemaleInfo->huo_dong_du,_T("�ӹ����"))  , 6 );  
        //ѹʹ
        PrintTextMult2(pDC,pInfo, toString(pFemaleInfo->ya_tong,_T("ѹʹ")) );
        NewLine(pDC,pInfo);
        NewSmallHalfLine( pDC , pInfo , true );
        //��฽��
        PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_fu_jian_zuo.toString(_T(" ��฽��")) , 6); 
        //�Ҳ฽��
        PrintTextMult2(pDC,pInfo, pFemaleInfo->cs_fu_jian_you.toString(_T("�Ҳ฽��"))); 
        // PCI-V1.2 ȥ���ˡ����Ƽ�顿�ġ���������
        // 		NewLine(pDC,pInfo);
        // 		NewSmallHalfLine( pDC , pInfo , true );
        // 		//����
        // 		PrintTextMult2(pDC,pInfo, toString(pFemaleInfo->qi_ta,_T(" ����")) );  
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectWidth(2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintTextV(pDC,pInfo,_T("���Ƽ��"));
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->MoveRight();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->setRectWidth( (pInfo->m_rectDraw.Width() - 142)/2);
        //pInfoEx->drawBox(pDC);
        //Ѫ����
        PrintText(pDC,pInfo,_T("       Ѫ����"),0);
        PrintText(pDC,pInfo, toString(pFemaleInfo->xue_chang_gui,_T("")) );         
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        //�򳣹�
        PrintText(pDC,pInfo,_T(" �򳣹�"),0);
        PrintText(pDC,pInfo, toString(pFemaleInfo->niao_chang_gui,_T("")) );      
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->setRectWidth(3*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        text = _T("Ѫ ��");
        PrintText(pDC,pInfo,text,0,0,true);
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        //Ѫ��
        PrintText(pDC,pInfo, toString(pFemaleInfo->xue_xing,_T(" Ѫ��")) ,3,10);  
        //Rh����
        PrintText(pDC,pInfo, toString(pFemaleInfo->Rh_yin_zi,_T("Rh����")) );  
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        tmpY= pInfoEx->rc.top;
        tmpX=pInfoEx->rc.Width()/3;
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toStringFomat( pFemaleInfo->EN_FSH ,  _T(" FSH %.2f miu/ml") ));
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintTextScript(pDC , pInfo , _T(" E"),_T("2") , false , 0 ) ;
        PrintText(pDC,pInfo,toStringFomat( pFemaleInfo->EN_E_2 ,  _T(" %.2f pg/ml") ));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toStringFomat( pFemaleInfo->EN_P ,  _T(" P %.2f ng/ml") ));
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left+3*LINE_HEIGHT);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        tmpX=pInfoEx->rc.Width()/3;
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toStringFomat( pFemaleInfo->EN_LH ,  _T(" LH %.2f miu/ml") ));
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toStringFomat( pFemaleInfo->EN_PRL ,  _T(" PRL %.2f ng/ml") ));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);      
        PrintText(pDC,pInfo,toStringFomat( pFemaleInfo->EN_T ,  _T(" T %.2f ng/ml") ));

        //////////////////////////////////////////////////////////////////////////
        pInfoEx->rc.top = tmpY;
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectWidth(3*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC,pInfo,_T("����"),0,0,true);
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC,pInfo,_T("�ڷ���"),0,0,true);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,_T("TORCH"),0,0,true);
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        tmpX=pInfoEx->rc.Width()/4;
        pInfoEx->setRectWidth(tmpX*2/3);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString( pFemaleInfo->gong_xing_chong , _T("���γ�")));
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString( pFemaleInfo->ju_xi_bao_bing_du , _T(" ��ϸ������")));
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString( pFemaleInfo->feng_zhen_bing_du , _T(" �����")));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);      
        PrintText(pDC,pInfo,toString( pFemaleInfo->dan_chun_pao_zhen_bing_du_II_xing , _T(" �������������")));
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->setLeft(pInfo->m_rectDraw.left+3*LINE_HEIGHT);
        tmpY= pInfoEx->rc.top;
        tmpX=pInfoEx->rc.Width()/3;
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString( pFemaleInfo->EN_HBSAG , _T(" HBsAg")));
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString( pFemaleInfo->EN_HBSAB , _T(" HBsAb")));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString( pFemaleInfo->EN_HBEAG , _T(" HBeAg")));
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left+3*LINE_HEIGHT);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        tmpX=pInfoEx->rc.Width()/3;
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString( pFemaleInfo->EN_HBEAB , _T(" HBeAb")));
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString( pFemaleInfo->EN_HBCAB , _T(" HBcAb")));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);      
        PrintText(pDC,pInfo,toString( pFemaleInfo->EN_HAVI , _T(" HAV-I")));
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left+3*LINE_HEIGHT);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        tmpX=pInfoEx->rc.Width()/3;
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString( pFemaleInfo->EN_HCVAb , _T(" HCVAb")));
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString( pFemaleInfo->EN_HCVAg , _T(" HCV-Ag")));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);      
        PrintText(pDC,pInfo,toString( pFemaleInfo->EN_HIVAb , _T(" HIVAb")));
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->rc.top = tmpY;
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectWidth(3*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC,pInfo,_T("����"),0,0,true);
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC,pInfo,_T("HIV"),0,0,true);
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectWidth(3*LINE_HEIGHT);
        pInfoEx->setRectHeight(2*LINE_HEIGHT);
        PrintText(pDC,pInfo,_T("�����Ŀ�") , 0 , 0 , true);
        pInfoEx->drawBox(pDC);
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC,pInfo,toString( pFemaleInfo->kang_zi_gong_nei_mo_kang_ti , _T(" ���ӹ���Ĥ����"))  , 1, 30 );
        PrintText(pDC,pInfo,toString( pFemaleInfo->kang_luan_chao_kang_ti , _T(" ���ѳ�����"))  , 1, 30 );
        pInfoEx->MoveDown();     
        pInfoEx->setRectHeight(LINE_HEIGHT);
		//����͸�������塿��Ϊ����HCG���塿
        PrintText(pDC,pInfo,toString( pFemaleInfo->kang_tou_ming_dai_kang_ti , _T(" ��HCG����")) , 1, 30 );
        PrintText(pDC,pInfo,toString( pFemaleInfo->kang_jing_zi_kang_ti , _T(" �����ӿ���"))  , 1, 30 );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        tmpX=pInfo->m_rectDraw.Width()/3;
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString(pFemaleInfo->gan_gong , _T("    �ι�") ) );
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString(pFemaleInfo->shen_gong , _T(" ����") ) );
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);    
        PrintText(pDC,pInfo,toString(pFemaleInfo->ran_se_ti , _T(" Ⱦɫ��") ) );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->setRectWidth(3*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,_T("������Ƭ"),0,0,true);
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);        
        PrintText(pDC,pInfo,pFemaleInfo->gong_jing_gua_pian);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pDC->SelectObject(&smaleFont);
        PrintText(pDC,pInfo,toString(pFemaleInfo->zhi_yuan_ti , _T(" ֧ԭ��") ) ,1 );
        PrintText(pDC,pInfo,toString(pFemaleInfo->yi_yuan_ti , _T("��ԭ��") ) , 1 );
        PrintText(pDC,pInfo,toString(pFemaleInfo->di_chong , _T("�γ�") )  , 1 );
        PrintText(pDC,pInfo,toString(pFemaleInfo->mei_jun , _T("ù��") ) , 1  );
        PrintText(pDC,pInfo,toString(pFemaleInfo->xian_suo_xi_bao , _T("����ϸ��") )  ,  1 );
       // PrintText(pDC,pInfo,toString(pFemaleInfo->qing_jie_du,_T("����")));
        pDC->SelectObject(&mainFont);
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectWidth(3*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,_T("����ͿƬ"),0,0,true);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC,pInfo,_T("�ӹ����ѹ�"),0,0,true);
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString(pFemaleInfo->zi_gong_xing_tai, _T(" �ӹ���̬") ));
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        //������ѹ�
        PrintText(pDC,pInfo, toString(pFemaleInfo->zuo_ce_shu_luan_guan,_T(" ������ѹ�") ),0,28);
        //�Ҳ����ѹ�
        PrintText(pDC,pInfo, toString(pFemaleInfo->you_ce_shu_luan_guan,_T("�Ҳ����ѹ�") ));
        pInfoEx->MoveLeft();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        PrintText(pDC,pInfo,_T("��Ӱ"),0,0,true);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(4*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,_T("����B��"),0,0,true);
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        //����B�� ����
		PrintText(pDC,pInfo, toString( pFemaleInfo->fu_ke_Bchao_ri_qi, _T(" ����") ) , 0 , 34 );	
		pInfoEx->MoveDown();
		pInfoEx->setRectHeight( LINE_HEIGHT );
        //����B�� �ӹ���С
        PrintText(pDC,pInfo,  _T(" �ӹ���С:")+ pFemaleInfo->fu_ke_Bchao_zi_gong_da_xiao +_T("cm"));
        //����B�� �ӹ���Ĥ
        PrintText(pDC,pInfo, toStringFomat( pFemaleInfo->fu_ke_Bchao_zi_gong_nei_mo , _T("�ӹ���Ĥ:%.1f cm") ));
        //����B�� �ӹ�����
        PrintText(pDC,pInfo, toString( pFemaleInfo->fu_ke_B_chao_zi_gong_lei_xing , _T("����") )+_T("��"));
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        //	pInfoEx->SetBottom( pInfo->m_rectDraw.bottom);
        //����B�� ����ѳ�
        PrintText(pDC,pInfo, toString( pFemaleInfo->fu_ke_B_chao_zuo_ce_luan_chao , _T(" ����ѳ�") )+_T(" cm"),0);
        PrintText(pDC,pInfo, _T("������:")  + pFemaleInfo->fu_ke_B_chao_zuo_ce_luan_chao_Fc);		
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        //����B�� �Ҳ��ѳ�
        PrintText(pDC,pInfo, toString( pFemaleInfo->fu_ke_B_chao_you_ce_luan_chao , _T(" �Ҳ��ѳ�") )+_T(" cm"),0);
        PrintText(pDC,pInfo, _T("������:")  + pFemaleInfo->fu_ke_B_chao_you_ce_luan_chao_Fc);		
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->SetBottom(pInfo->m_rectDraw.bottom);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->gong_qiang_jing);
        pInfoEx->MoveLeft();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,_T("��  ǻ  ��"),0,0,true);   
        //////////////////////////////////////////////////////////////////////////*/
        break;
    case 4:
        // pDC->Rectangle(pInfo->m_rectDraw);
        pInfoEx->setRect(pInfo->m_rectDraw);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC,pInfo,_T("����ǰ��Ȼ�������Ѽ�⣺"));
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->setRectWidth(4*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,_T("��    ��"),0,0,true);
        tmpX = (pInfo->m_rectDraw.right-pInfoEx->rc.right)/4;
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo, pFemaleInfo->nv_pai_luan_jian_ce_ri_qi1 ,0,0,true);
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo, pFemaleInfo->nv_pai_luan_jian_ce_ri_qi2 ,0,0,true);
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo, pFemaleInfo->nv_pai_luan_jian_ce_ri_qi3 ,0,0,true);
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,  pFemaleInfo->nv_pai_luan_jian_ce_ri_qi4 ,0,0,true);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->setRectWidth(4*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,_T("�¾�����"),0,0,true);
        tmpX = (pInfo->m_rectDraw.right-pInfoEx->rc.right)/4;
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->yue_jing_zhou_qi1,0,0,true);
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->yue_jing_zhou_qi2 , 0 ,0, true );
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->yue_jing_zhou_qi3 , 0 ,0, true );
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->yue_jing_zhou_qi4 , 0 ,0, true );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->setRectWidth(4*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,_T("����ֱ��"),0,0,true);
        tmpX = (pInfo->m_rectDraw.right-pInfoEx->rc.right)/4;
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->luan_pao_zhi_jing1 , 0 ,0, true );
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->luan_pao_zhi_jing2 , 0 , 0,  true );
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->luan_pao_zhi_jing3, 0 ,0, true );
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->luan_pao_zhi_jing4 , 0 ,0, true );     
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->setRectWidth(4*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,_T("�ӹ���Ĥ"),0,0,true);
        tmpX = (pInfo->m_rectDraw.right-pInfoEx->rc.right)/4;
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->zi_gong_nei_mo1 , 0 ,0, true );
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->zi_gong_nei_mo2 , 0,0 , true );
        pInfoEx->MoveRight();
        pInfoEx->setRectWidth(tmpX);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->zi_gong_nei_mo3 , 0 ,0, true );
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,pFemaleInfo->zi_gong_nei_mo4 , 0  ,0, true );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->setRectHeight(2*LINE_HEIGHT);
        pDC->SelectObject(&titleFont);
        PrintText(pDC,pInfo,_T("�� ʷ С ��"),0,0,true);
        pDC->SelectObject(&mainFont);
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(9*LINE_HEIGHT);
        pInfoEx->drawBox( pDC );
        pInfoEx->rc.left += MUTI_TEXT_BLANK_WIDTH;
        pInfoEx->rc.right -= MUTI_TEXT_BLANK_WIDTH;
        NewLine( pDC , pInfo , true );
        PrintTextMult2( pDC,pInfo, pFemaleInfo->bing_shi_xiao_jie );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft( pInfo->m_rectDraw.left);
        pInfoEx->SetRight( pInfo->m_rectDraw.right  );
        pInfoEx->setRectHeight(LINE_HEIGHT);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        //pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,_T("���") , 1 );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 5* LINE_HEIGHT);
        pInfoEx->rc.left += MUTI_TEXT_BLANK_WIDTH;
        pInfoEx->rc.right -= MUTI_TEXT_BLANK_WIDTH;
        PrintTextMult2( pDC,pInfo, pFemaleInfo->zhen_duan );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft( pInfo->m_rectDraw.left );
        pInfoEx->SetRight( pInfo->m_rectDraw.right );
        pInfoEx->setRectHeight(LINE_HEIGHT);
        //pInfoEx->drawBox(pDC);
        PrintTextMult2( pDC , pInfo , _T("���Ƽƻ�") , 1 );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 5* LINE_HEIGHT);
        pInfoEx->rc.left += MUTI_TEXT_BLANK_WIDTH;
        pInfoEx->rc.right -= MUTI_TEXT_BLANK_WIDTH;
        PrintTextMult2( pDC,pInfo, pFemaleInfo->zheng_liao_ji_hua );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfoEx->rc.left+pInfoEx->rc.Width()*2/3);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC,pInfo, toString( pFemaleInfo->nv_yi_shi , _T("ҽʦ") ) );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC,pInfo,toString(  pFemaleInfo->nv_date_luo_kuan , _T("")  ));  
        //////////////////////////////////////////////////////////////////////////
        break;
    case 5:
        pInfo->m_rectDraw.bottom += 3*LINE_HEIGHT;
        pDC->Rectangle(pInfo->m_rectDraw);
        pInfoEx->setRect(pInfo->m_rectDraw);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        text=_T("�з�����:")+pMaleInfo->EN_name;
        PrintText(pDC,pInfo,text, 1,16);
        text.Format(_T("����:%d"),pMaleInfo->EN_age);
        PrintText(pDC,pInfo,text, 1,10);
        text=_T("ְҵ:")+pMaleInfo->EN_occupation;
        PrintText(pDC,pInfo,text, 1,12);
        text=_T("�Ļ��̶�:")+pMaleInfo->EN_knowledge_degree;
        PrintText(pDC,pInfo,text, 1 ,18);
        text=_T("����:")+pMaleInfo->EN_nation;
        PrintText(pDC,pInfo,text, 1 ,10);
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        text=_T("ͨѶ��ַ��")+pMaleInfo->EN_address ;
        PrintText( pDC,pInfo,text, 1,40);    
        text=_T("��ϵ�绰��")+pMaleInfo->EN_phone ;
        PrintText(pDC,pInfo,text);    
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,toString( pMaleInfo->date_chu_zhen , _T("����ʱ�䣺") ));    
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pDC->SelectObject(&boldFont);
        PrintText(pDC,pInfo,_T("���ߣ�") , 1 );
        pDC->SelectObject(&mainFont);
        PrintText(pDC , pInfo , pMaleInfo->zhu_su );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
		pInfoEx->MoveDown();
		pInfoEx->setRectHeight(4*LINE_HEIGHT);
		pInfoEx->drawBox(pDC);
		pInfoEx->setRectHeight( 4*LINE_HEIGHT);
		pDC->SelectObject(&boldFont);
		PrintTextMult2(pDC,pInfo,_T("�ֲ�ʷ��") , 0 );
		tmpX = pInfoEx->cur.x;
		pInfoEx->setLeft( pInfoEx->rc.left + 10);
		pInfoEx->SetRight( pInfoEx->rc.right - 10);
		pInfoEx->cur.x =tmpX ;
		pDC->SelectObject(&mainFont);
        PrintTextMult2(pDC,pInfo,pMaleInfo->xian_bing_shi);
        pInfoEx->SetRight( pInfo->m_rectDraw.right );
        pInfoEx->setLeft( pInfo->m_rectDraw.left );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 6*LINE_HEIGHT);
        pInfoEx->setRectWidth(2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintTextV(pDC,pInfo,_T("������ʷ"));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight( LINE_HEIGHT );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        PrintText(pDC,pInfo, toString( pMaleInfo->ji_wang_gan_yan , _T(" ����") ) , 0,34 );
        PrintText(pDC,pInfo, toString( pMaleInfo->jie_he , _T("���") ) );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        PrintText(pDC,pInfo, toString( pMaleInfo->xin_xue_guan, _T(" ��Ѫ�ܼ���")) , 0,34 );
        PrintText(pDC,pInfo, toString( pMaleInfo->xing_chuan_bo, _T("�Դ�������ʷ") ) );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        PrintText(pDC,pInfo, pMaleInfo->cs_mi_niao_sheng_zhi.toString( _T(" ������ֳ��ʷ") ) , 0,34 );
        PrintText(pDC,pInfo, toString( pMaleInfo->ji_wang_bing_shi_qi_ta ,_T( " ����" ) ) );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectHeight( 8*LINE_HEIGHT);
        pInfoEx->setRectWidth(2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintTextV(pDC,pInfo,_T("����ʷ"));
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight( LINE_HEIGHT );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        PrintText(pDC,pInfo, pMaleInfo->ci_xi_yan.toString( _T(" ����:%d֧/��") ,_T(" ����:��") ) );  
        PrintText( pDC , pInfo , toString( pMaleInfo->xu_jiu , _T( "���" ) ) );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        PrintText(pDC,pInfo, pMaleInfo->cs_yao_wu_guo_min.toString( _T(" ҩ�����ʷ") ) );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        PrintText( pDC , pInfo , toString( pMaleInfo->zhong_da_jing_sheng_ci_ji , _T( " �ش���̼�ʷ" ) ) );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        PrintText (pDC , pInfo , toString( pMaleInfo->jian_kang_zhuang_kuang_guo_qu , _T( " ����״������ȥ" ) ) );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        PrintText( pDC , pInfo , toString( pMaleInfo->jian_kang_zhuang_kuang_xian_zai , _T( "           ����" ) ) );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );    
        PrintText( pDC , pInfo , pMaleInfo->cs_chu_sheng_que_xian .toString(  _T( " ����ȱ��" ) ) );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );    
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectHeight(2*LINE_HEIGHT);
        pInfoEx->setRectWidth(2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pDC->SelectObject(&boldFont);
        PrintTextV(pDC , pInfo , _T("����ʷ") );
        pDC->SelectObject(&mainFont);
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo, toString( pMaleInfo->jin_qin_jie_hun, _T(" ���׽��") )  , 1, 20 );
        PrintText(pDC,pInfo, toString( pMaleInfo->zai_hun, _T("�ٻ�") )  );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->setRectHeight(4*LINE_HEIGHT);
        pInfoEx->setRectWidth(2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pDC->SelectObject(&boldFont);
        PrintTextV(pDC , pInfo , _T("����ʷ") );
        pDC->SelectObject(&mainFont);
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        pDC->SelectObject(&mainFont);
        pInfoEx->setRectHeight( LINE_HEIGHT);
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        PrintText( pDC , pInfo , pMaleInfo->cs_yi_chuan_bing_shi .toString(  _T( " �Ŵ���ʷ" ) ) );  
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        PrintText(pDC,pInfo, pFemaleInfo->cs_bu_yun_bu_yu_shi.toString(_T(" ���в�����ʷ")));
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->SetBottom( pInfo->m_rectDraw.bottom );
        pInfoEx->setRectWidth(4*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pDC->SelectObject(&boldFont);
        PrintText(pDC , pInfo , _T("һ�������") , 0 ,0 , true);
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        pDC->SelectObject(&mainFont);
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->shen_gao , _T(" ���:%d cm") ) );     
        PrintText(pDC,pInfo, toStringFomat(pMaleInfo->ti_zhong ,_T("����: %.1f Kg")));       
        text.Format(  _T("Ѫѹ:%d/%d mmHg" ) , pMaleInfo->xue_ya1, pMaleInfo->xue_ya2);
        PrintText(pDC,pInfo, text);     
        //TODO
        //////////////////////////////////////////////////////////////////////////
        break;
    case 6:
        pDC->Rectangle(pInfo->m_rectDraw);
        pInfoEx->setRect(pInfo->m_rectDraw);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->setRectHeight(3*LINE_HEIGHT);
        pInfoEx->setRectWidth(4*LINE_HEIGHT);        
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , _T("�ڶ�����") , 0 , 0,true);        
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight( LINE_HEIGHT );
        PrintText(pDC,pInfo, toString( pMaleInfo->hu_xu , _T(" ����") ) , 0, 20 ); 
        PrintText(pDC,pInfo, toString( pMaleInfo->hou_jie , _T("���") ) ); 
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        PrintTextMult2(pDC,pInfo,  pMaleInfo->cs_ru_fang.toString( _T(" �鷿") ) ); 
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft( pInfo->m_rectDraw.left);
        pInfoEx->setRectWidth(4*LINE_HEIGHT);
        pInfoEx->setRectHeight( 9*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , _T("��ֳϵͳ���") , 0 , 0,true);       
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight( LINE_HEIGHT);
        PrintText(pDC,pInfo,  pMaleInfo->cs_yin_jing.toString( _T(" ����") ) , 0  ,28 ); 
        PrintText(pDC,pInfo, toString( pMaleInfo->yin_mao , _T("��ë") ) ); 
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight( LINE_HEIGHT);
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->gao_wan_ti_ji_zuo , _T(" غ�裺��� �� %d ml") ) );
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->gao_wan_ti_ji_zuo , _T("�� %d ml") ) ); 
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        PrintText(pDC,pInfo,  pMaleInfo->cs_gao_wan_zhi_di_zuo.toString( _T("       �ʵ� ��") ) ); 
        PrintText(pDC,pInfo,  pMaleInfo->cs_gao_wan_zhi_di_you.toString( _T("��") ) ); 

        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo,  pMaleInfo->cs_fu_gao_zuo.toString( _T(" ��غ: ��") ) ); 
        PrintText(pDC,pInfo,  pMaleInfo->cs_fu_gao_you.toString( _T("��") ) ); 
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight( LINE_HEIGHT);
        PrintText(pDC,pInfo,  pMaleInfo->cs_shu_jing_guan_zuo.toString( _T(" �侫�ܣ���") ) ); 
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        PrintText(pDC,pInfo,  pMaleInfo->cs_shu_jing_guan_you.toString( _T("         ��") ) ); 

        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight( LINE_HEIGHT);
        PrintText(pDC,pInfo,  pMaleInfo->cs_jing_suo_jing_mai_zuo.toString( _T(" ������������") ) ); 
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        PrintText(pDC,pInfo,  pMaleInfo->cs_jing_suo_jing_mai_you.toString( _T("           ��") ) ); 

        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        PrintText(pDC,pInfo,  toString( pMaleInfo->sheng_zhi_qi_ta , _T(" ����") ) );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setLeft( pInfo->m_rectDraw.left);
        pInfoEx->setRectWidth(4*LINE_HEIGHT);
        pInfoEx->setRectHeight( 5*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , _T("��Һ�������") , 0 , 0,true);       
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        tmpX = pInfoEx->rc.left;
        tmpY = pInfoEx->rc.Width()/2;
        pInfoEx->setRectHeight( LINE_HEIGHT);
        pInfoEx->setRectWidth(pInfoEx->rc.Width()/2);
        pInfoEx->drawBox( pDC );
        PrintText(pDC,pInfo, toString(  pMaleInfo->date_jing_ye_fen_xi , _T(" ���ڣ�") ) );
        pInfoEx->MoveRight();
        pInfoEx->SetRight( pInfo->m_rectDraw.right );
        pInfoEx->drawBox( pDC );
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->jin_yu_tian_shu , _T(" ���� %d ��") ) ); 
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        pInfoEx->drawBox( pDC );
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->EN_PH , _T(" PH %.1f") ) ); 
        pInfoEx->MoveLeft();
        pInfoEx->setLeft( tmpX );
        pInfoEx->drawBox( pDC );
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->jing_ye_liang , _T(" ��Һ�� %.1f ml") ) ); 
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        pInfoEx->drawBox( pDC );
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->ye_hua_shi_jian , _T(" Һ��ʱ�� %d min") ) ); 
        pInfoEx->MoveRight();
        pInfoEx->SetRight( pInfo->m_rectDraw.right );
        pInfoEx->drawBox( pDC );
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->mi_du , _T(" �ܶ� %.2f ��") ) , 0 , 0 );
        PrintTextScript( pDC ,pInfo , _T("10") , _T("6") ,true , 0 );
        PrintText( pDC ,pInfo , _T("/ml") );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        pInfoEx->setLeft( tmpX );
        pInfoEx->drawBox( pDC );
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->huo_li_A_ji , _T(" ��� A��:%.2f %%") ) ,1  );
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->huo_li_B_ji , _T("  B��:%.2f %%") ) , 1 );
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->huo_li_C_ji , _T("  C��:%.2f %%") ) , 1 );
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->huo_li_D_ji , _T("  D��:%.2f %%") ), 1 );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        pInfoEx->setRectWidth(pInfoEx->rc.Width()/2);
        pInfoEx->drawBox( pDC );
        PrintText(pDC,pInfo, toStringFomat( pMaleInfo->zheng_chang_xing_tai_lv , _T(" ������̬�� %d %%") ) );
        pInfoEx->MoveRight();
        pInfoEx->SetRight( pInfo->m_rectDraw.right );
        pInfoEx->drawBox( pDC );
        PrintText(pDC,pInfo, toString( pMaleInfo->bai_xi_bao , _T(" ��ϸ��") ) +_T(" HP"));

        //////////////////////////////////////////////////////////////////////////
        pInfoEx->setLeft( tmpX );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC,pInfo, toString(pMaleInfo->xue_xing,_T(" Ѫ��")) ,3,10);  
        PrintText(pDC,pInfo, toString(pMaleInfo->Rh_yin_zi,_T("Rh����")) );  
        pInfoEx->MoveLeft();
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , _T("Ѫ  ��") , 0 , 0,true);  
        //////////////////////////////////////////////////////////////////////////
		  pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , _T("΢������") , 0 , 0,true);  
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight( LINE_HEIGHT );
        pInfoEx->setRectWidth( pInfoEx->rc.Width()/2 );
        pInfoEx->drawBox( pDC );
		PrintText(pDC , pInfo ,  toString( pMaleInfo->zhi_yuan_ti , _T(" ֧ԭ��") ) );  
        pInfoEx->MoveRight();
        pInfoEx->SetRight( pInfo->m_rectDraw.right );

        PrintText(pDC , pInfo ,  toString( pMaleInfo->zhi_yuan_ti , _T(" ֧ԭ��") ) );  
		PrintText(pDC , pInfo ,  toString( pMaleInfo->yi_yuan_ti , _T(" ��ԭ��") ) );  
        /*
		pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        pInfoEx->drawBox( pDC );
        pInfoEx->MoveLeft();
        pInfoEx->setLeft( tmpX );
        pInfoEx->drawBox( pDC );
        PrintText(pDC , pInfo ,  toString( pMaleInfo->yi_yuan_ti , _T(" ��ԭ��") ) );  
		*/
      
/*   
		pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , _T("΢������") , 0 , 0,true);  
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight( LINE_HEIGHT );
        pInfoEx->setRectWidth( pInfoEx->rc.Width()/2 );
        pInfoEx->drawBox( pDC );
        PrintText(pDC , pInfo ,  toString( pMaleInfo->lin_qiu_jun , _T(" �����") ) );  
        pInfoEx->MoveRight();
        pInfoEx->SetRight( pInfo->m_rectDraw.right );

        PrintText(pDC , pInfo ,  toString( pMaleInfo->zhi_yuan_ti , _T(" ֧ԭ��") ) );  
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        pInfoEx->drawBox( pDC );
        pInfoEx->MoveLeft();
        pInfoEx->setLeft( tmpX );
        pInfoEx->drawBox( pDC );
        PrintText(pDC , pInfo ,  toString( pMaleInfo->yi_yuan_ti , _T(" ��ԭ��") ) );  
*/      
		//////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo ,  pMaleInfo->gan_yan );
        pInfoEx->MoveRight();
        pInfoEx->SetRight( pInfo->m_rectDraw.right );
        PrintText(pDC , pInfo ,  toString( pMaleInfo->EN_HIV , _T(" HIV") ) );  
        pInfoEx->setLeft(pInfo->m_rectDraw.left);
        pInfoEx->SetRight( tmpX );
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , _T("��  ��") , 0 , 0,true);  
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , _T("��ֳ����") , 0 , 0,true);  
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->setRectWidth( pInfoEx->rc.Width() /2);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , pMaleInfo->sheng_zhi_ji_su);  
        pInfoEx->MoveRight();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo ,   toString( pMaleInfo->yi_chuan_xue_jian_cha , _T("�Ŵ�ѧ���") )); 
        //todo
        ///////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->SetRight(pInfo->m_rectDraw.right);
        pInfoEx->setLeft( pInfo->m_rectDraw.left);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC , pInfo , _T("�������:") );
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 9*LINE_HEIGHT);
        pInfoEx->rc.left += MUTI_TEXT_BLANK_WIDTH;
        pInfoEx->rc.right -= MUTI_TEXT_BLANK_WIDTH;

        PrintTextMult2(pDC,pInfo, pMaleInfo->chu_bu_zhen_duan);
        //////////////////////////////////////////////////////////////////////////

        pInfoEx->MoveDown();
        pInfoEx->setLeft(pInfoEx->rc.left+pInfoEx->rc.Width()*2/3);
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC,pInfo,  toString( pMaleInfo->nan_yi_shi  ,  _T("ҽʦ") ) );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(LINE_HEIGHT);
        PrintText(pDC,pInfo,toString( pMaleInfo->date_luo_kuan , _T("") ));  
        break;
    case 7:
        //pDC->Rectangle(pInfo->m_rectDraw);
        pInfoEx->setRect(pInfo->m_rectDraw);
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->setRectHeight( LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo ,toString( pCommonInfo->date_shou_ci_bing_cheng_ji_lu , _T("") , true ) );    
        pInfoEx->resetCur();
        pDC->SelectObject( &boldFont);
        PrintText(pDC , pInfo , _T("�״β��̼�¼") , 0 , 0,true);        
        pDC->SelectObject( &mainFont );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 6* LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight(  LINE_HEIGHT);
        PrintText(pDC , pInfo , _T("�����ص�") , 1); 
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 5* LINE_HEIGHT);
        pInfoEx->rc.left += MUTI_TEXT_BLANK_WIDTH;
        pInfoEx->rc.right -= MUTI_TEXT_BLANK_WIDTH;
        PrintTextMult2( pDC,  pInfo , pCommonInfo->bing_li_te_dian );
        pInfoEx->SetRight( pInfo->m_rectDraw.right );
        pInfoEx->setLeft( pInfo->m_rectDraw.left );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 6* LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight(  LINE_HEIGHT);
        PrintText(pDC , pInfo , _T("�������") , 1); 
        pInfoEx->MoveDown();
        pInfoEx->rc.left += MUTI_TEXT_BLANK_WIDTH;
        pInfoEx->rc.right -= MUTI_TEXT_BLANK_WIDTH;
        pInfoEx->setRectHeight( 5* LINE_HEIGHT);
        PrintTextMult2(pDC,pInfo, pFemaleInfo->zhen_duan+_T("\r\n")+pMaleInfo->chu_bu_zhen_duan);
        pInfoEx->setLeft( pInfo->m_rectDraw.left );

        pInfoEx->SetRight( pInfo->m_rectDraw.right );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(  2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , _T("���Ƽƻ�"  ) );       
        NewLine( pDC , pInfo );
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(  2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , toString( pCommonInfo->ni_xing_AIH_fang_shi , _T("1������AIH�ķ�ʽ")  ) );
		//////////////////////////////////////////////////////////////////////////
/*       TODODO
		pInfoEx->MoveDown();
        pInfoEx->setRectHeight(  2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , toString( pCommonInfo->fu_he_AIH_zhi_zheng , _T("2������AIH��ָ��")  ) ); 
		*/
		//��������
		CString a = pCommonInfo->fu_he_AIH_zhi_zheng;
		a = a.Trim();
		int index = 0;
		int lcount = 1;
		do{
			index = a.Find(_T("\n"),index+1);
			lcount ++;
		}while( index !=-1 );


		pInfoEx->MoveDown();
        pInfoEx->setRectHeight( lcount*36 );
        pInfoEx->drawBox(pDC);
        pInfoEx->setRectHeight( lcount*36 );
		pInfoEx->SetTop(pInfoEx->cur.y -= 10);

        PrintTextMult2(pDC,pInfo,_T("2������AIH��ָ����") , 0 );
		tmpX = pInfoEx->cur.x;
		pInfoEx->setLeft( pInfoEx->rc.left + 10);
		pInfoEx->SetRight( pInfoEx->rc.right - 10);
		pInfoEx->cur.x =tmpX ;
        PrintTextMult2(pDC,pInfo, pCommonInfo->fu_he_AIH_zhi_zheng );

        pInfoEx->setLeft( pInfo->m_rectDraw.left);
		pInfoEx->SetRight( pInfo->m_rectDraw.right);

/*
		pInfoEx->MoveDown();
        pInfoEx->setRectHeight(  lcount*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , toString( pCommonInfo->fu_he_AIH_zhi_zheng , _T("2������AIH��ָ��")  ) ); 
*/

		
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(  2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , toString( pCommonInfo->jin_ji_zheng , _T("3������֢")  ) );   
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(2*  LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , toString( pCommonInfo->ni_xing_zhi_liao_fang_an , _T("4���������Ʒ���")  ) );  
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(  2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , toString( pCommonInfo->fu_zhu_jian_cha_yi_chang_jie_guo , _T("5����������쳣���")  ) );  
        //////////////////////////////////////////////////////////////////////////
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight(  2*LINE_HEIGHT);
        pInfoEx->drawBox(pDC);
        PrintText(pDC , pInfo , toString( pCommonInfo->bing_cheng_ji_lu_qi_ta , _T("6������")  ) );    
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( 2*LINE_HEIGHT );
        pInfoEx->drawBox( pDC ); 
        pInfoEx->MoveDown();
        pInfoEx->setRectHeight( LINE_HEIGHT );
        pInfoEx->cur.x = pInfoEx->rc.right - 400;
        PrintText(pDC , pInfo , toString( pCommonInfo->bing_cheng_ji_lu_yi_shi , _T("ҽʦ")  ) );
    }

    pDC->SelectObject(oldBrush);
    pDC->SelectObject(oldFont);
    pDC->SetBkMode(oldBkMode);
    pDC->SetTextColor(oldTextColor);
    titleFont.DeleteObject();
    mainFont.DeleteObject();
    boldFont.DeleteObject();
    smaleFont.DeleteObject();
}



//�����ַ�
void CPrintCaseInfoView::PrintText(CDC* pDC, CPrintInfo* pInfo,CString text , int blankNum ,int minWord,bool center)
{
    CPrintInfoEx* pInfoEx=(CPrintInfoEx*)pInfo->m_lpUserData; 
    TEXTMETRIC tm;
    pDC->GetTextMetrics (&tm);
    int fontWidht = tm.tmAveCharWidth;
    int textWidth = max(pDC->GetTextExtent(text).cx,minWord*fontWidht);
// 	int textHeitht = tm.tmHeight+tm.tmExternalLeading;
    UINT f = DT_VCENTER|DT_SINGLELINE;
    if (center)
    {
        f |= DT_CENTER;
    }
    else
    {
        f |= DT_LEFT;
    }
    pDC->DrawText(text,CRect(pInfoEx->cur,pInfoEx->rc.BottomRight()),f);
    pInfoEx->cur.x +=textWidth+blankNum*fontWidht;
}

void CPrintCaseInfoView::PrintTextScript(CDC* pDC, CPrintInfo* pInfo,CString text , CString scriptText ,bool superscript, int blankNum ,bool vCenter )
{
    CPrintInfoEx* pInfoEx=(CPrintInfoEx*)pInfo->m_lpUserData; 
    TEXTMETRIC tm;
    pDC->GetTextMetrics (&tm);
    int fontWidht = tm.tmAveCharWidth;
    int textWidth = pDC->GetTextExtent(text).cx;
//	int textHeitht = tm.tmHeight+tm.tmExternalLeading;
    UINT f =DT_LEFT ;
    if (vCenter)
    {
        f = DT_VCENTER |DT_SINGLELINE;
    }
    pDC->DrawText(text,CRect(pInfoEx->cur,pInfoEx->rc.BottomRight()) , f);
    pInfoEx->cur.x +=textWidth;

    CFont scriptFont;
    scriptFont.CreatePointFont(80 ,_T("����"),pDC);

    UINT oldTextAlign ;
    CFont *pOldFont = pDC->SelectObject(&scriptFont);
    pDC->GetTextMetrics (&tm);
    fontWidht = tm.tmAveCharWidth;
    textWidth =  pDC->GetTextExtent(scriptText).cx ;
    if ( superscript )
    {
        oldTextAlign = pDC->SetTextAlign( TA_LEFT| TA_TOP);
        pDC->TextOut( pInfoEx->cur.x ,pInfoEx->cur.y ,  scriptText );
    } 
    else
    {
        oldTextAlign = pDC->SetTextAlign( TA_LEFT| TA_BOTTOM);
        pDC->TextOut( pInfoEx->cur.x , pInfoEx->rc.bottom +8,  scriptText );
    }

    pInfoEx->cur.x +=textWidth+blankNum*fontWidht;
    pDC->SelectObject(pOldFont);
    pDC->SetTextAlign( oldTextAlign);
}

void CPrintCaseInfoView::PrintTextMult2(CDC* pDC, CPrintInfo* pInfo,CString text ,int blankNum )
{
    if (text == _T(""))
    {
        return;
    }
    CPrintInfoEx* pInfoEx=(CPrintInfoEx*)pInfo->m_lpUserData; 
    TEXTMETRIC tm;
    pDC->GetTextMetrics (&tm);
    int fontWidht = tm.tmAveCharWidth;
    CString blankStr;
    for ( int i=0 ; i< ( pInfoEx->cur.x-pInfoEx->rc.left)/tm.tmAveCharWidth ; i++)
    {
        blankStr +=_T(" ");
    }
    text = blankStr + text ;
    int textWidth = pDC->GetTextExtent(text).cx;
    int textHeitht = tm.tmHeight+tm.tmExternalLeading;
    if ( textWidth < abs(pInfoEx->rc.Width()) )
    {
        pDC->DrawText( text , CRect( pInfoEx->rc.left, pInfoEx->cur.y,  pInfoEx->rc.right , pInfoEx->rc.bottom ) , DT_LEFT|DT_WORDBREAK);
        pInfoEx->cur.x = pInfoEx->rc.left + textWidth ;
    } 
    else
    {   
        int drawHeight = pDC->DrawText(text,CRect( pInfoEx->rc.left, pInfoEx->cur.y,  pInfoEx->rc.right , pInfoEx->rc.bottom ),DT_LEFT|DT_WORDBREAK);
        pInfoEx->cur.x = pInfoEx->rc.left + textWidth % pInfoEx->rc.Width();
        pInfoEx->cur.y += drawHeight;
        pInfoEx->cur.y += textHeitht;
    }
    pInfoEx->cur.x +=blankNum*fontWidht;
}

//����
void CPrintCaseInfoView::NewLine(CDC* pDC, CPrintInfo* pInfo , bool force)
{
    CPrintInfoEx* pInfoEx=(CPrintInfoEx*)pInfo->m_lpUserData; 
    if( !force )
    {
        if( pInfoEx->cur.x == pInfoEx->rc.left )
        {
            return ;
        }
    }
    TEXTMETRIC tm;
    pDC->GetTextMetrics (&tm);
    int textHeitht = tm.tmHeight+tm.tmExternalLeading+tm.tmInternalLeading;
    pInfoEx->cur.x = pInfoEx->rc.left;
    pInfoEx->cur.y -= textHeitht;
}

//����
void CPrintCaseInfoView::NewHalfLine(CDC* pDC, CPrintInfo* pInfo , bool force)
{
    CPrintInfoEx* pInfoEx=(CPrintInfoEx*)pInfo->m_lpUserData; 
    if( !force )
    {
        if( pInfoEx->cur.x == pInfoEx->rc.left )
        {
            return ;
        }
    }
    TEXTMETRIC tm;
    pDC->GetTextMetrics (&tm);
    int textHeitht = tm.tmHeight+tm.tmExternalLeading+tm.tmInternalLeading;
    pInfoEx->cur.x = pInfoEx->rc.left;
    pInfoEx->cur.y -= textHeitht/2;
}

//����
void CPrintCaseInfoView::NewSmallHalfLine(CDC* pDC, CPrintInfo* pInfo , bool force)
{
    CPrintInfoEx* pInfoEx=(CPrintInfoEx*)pInfo->m_lpUserData; 
    if( !force )
    {
        if( pInfoEx->cur.x == pInfoEx->rc.left )
        {
            return ;
        }
    }
    TEXTMETRIC tm;
    pDC->GetTextMetrics (&tm);
    int textHeitht = tm.tmHeight+tm.tmExternalLeading+tm.tmInternalLeading;
    pInfoEx->cur.x = pInfoEx->rc.left;
    pInfoEx->cur.y -= textHeitht/5;
}

//�����ı�
void CPrintCaseInfoView::PrintTextV(CDC* pDC, CPrintInfo* pInfo,CString text)
{
    CPrintInfoEx* pInfoEx=(CPrintInfoEx*)pInfo->m_lpUserData; 
    CFont *pOldFont=pDC->SelectObject(&boldFont);//ѡ���豸������

    int textL=text.GetLength();
    TEXTMETRIC tm;
    pDC->GetTextMetrics (&tm);
    int textHeitht = (tm.tmHeight/*+tm.tmExternalLeading*/)*textL;
    int textWidth = tm.tmMaxCharWidth;

    CPoint centerPoint = pInfoEx->rc.CenterPoint();
    CRect rc = CRect( centerPoint.x-textWidth/2-2, centerPoint.y+textHeitht/2 , centerPoint.x+textWidth/2+2 ,  centerPoint.y-textHeitht/2 );

    //   pDC->Rectangle(rc);
    pDC->DrawText(text,rc,DT_WORDBREAK);
    pDC->SelectObject(pOldFont); //��myFont���豸�����з���
}

void CPrintCaseInfoView::OnInitialUpdate()
{
    TRACE_FUNC();
    CScorllCenterFormView::OnInitialUpdate();
    //�����ĵ����ݣ���Ҫ�������б���Ϊ�½�ʱ�����б�����ĵ�����Ϊ�գ���������ΪĬ��ֵ
    UpdateData(TRUE);
    //����ʵ����Ч�����޸ģ�����ĵ��޸ı�־
    GetDocument()->SetModifiedFlag(FALSE);
    // TODO: �ڴ����ר�ô����/����û���
}

BOOL CPrintCaseInfoView::OnUpdateDocFromView()
{
	//TRACE_FUNC();
	return UpdateData(TRUE);

}
