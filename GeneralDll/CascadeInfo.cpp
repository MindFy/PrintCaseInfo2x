// CascadeInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CascadeInfo.h"

IMPLEMENT_DYNCREATE(CCascadeInfo, CObject)
// CCascadeInfo

CCascadeInfo::CCascadeInfo()
{
}

CCascadeInfo::~CCascadeInfo()
{
}


// CCascadeInfo ��Ա����
// CPrintCaseInfoDoc ���л�

void CCascadeInfo::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{
		ar<<strBase<<strHasMore;
	}
	else
	{
		ar>>strBase>>strHasMore;
	}
	//TRACE(_T("Serialize ")+strBase+_T("-")+strHasMore+_T(" \n"));
    //TRACE("*******************END CCascadeInfo::Serialize\n");
}
