#pragma once

// CCascadeInfo ����Ŀ��

class  CCascadeInfo : public CObject
{
public:
	DECLARE_DYNCREATE(CCascadeInfo)
	CCascadeInfo();

	virtual ~CCascadeInfo();
	virtual void Serialize(CArchive& ar);
public:
	CString strBase;//������Ϣ
	CString strHasMore;//��ʾ��Ϣ
};


