#pragma once

// CCommonInfo ����Ŀ��

class AFX_EXT_CLASS CCommonInfo : public CObject
{
protected:
    DECLARE_DYNCREATE(CCommonInfo)
public:
	CCommonInfo();
	virtual ~CCommonInfo();
    virtual void Serialize(CArchive& ar);
    void operator=(const CCommonInfo& ci);
public:
    CString     bing_li_hao;      //������
    CTime       date_ye_mei;      //����
    CTime       date_shou_ci_bing_cheng_ji_lu; //�״β��̼�¼
    CString     bing_li_te_dian;         //�����ص�
    //CString     zhen_liao_ji_hua;       //���Ƽƻ�
    CString     ni_xing_AIH_fang_shi;   //1������AIH�ķ�ʽ��
    CString     fu_he_AIH_zhi_zheng;   //2������AIH��ָ����
    CString     jin_ji_zheng;      //3������֢��
    CString     ni_xing_zhi_liao_fang_an;      // 4���������Ʒ�����
    CString     fu_zhu_jian_cha_yi_chang_jie_guo;//5����������쳣�����
    CString     bing_cheng_ji_lu_qi_ta;        //6��������
    CString     bing_cheng_ji_lu_yi_shi;       //ҽʦ
};


