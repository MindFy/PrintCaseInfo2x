#pragma once
#include "CascadeInfo.h"
// CCascadString ����Ŀ��

class AFX_EXT_CLASS CCascadeString : public CCascadeInfo
{
public:
	CCascadeString();
	CCascadeString(CString strFlag);
	virtual ~CCascadeString();
	CString strMore;//��ϸ��Ϣ
public:
	virtual void Serialize(CArchive& ar);
	void operator=(const CCascadeString& cs);
    CString toString(CString name);
};


