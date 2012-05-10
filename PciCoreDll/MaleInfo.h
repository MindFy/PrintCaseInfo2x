#pragma once
#include "../GeneralDll/CascadeString.h"
#include "../GeneralDll/CascadeInt.h"
// CMaleInfo ����Ŀ��

class AFX_EXT_CLASS CMaleInfo : public CObject
{
protected:

	DECLARE_DYNCREATE(CMaleInfo)
public:
	CMaleInfo();
	virtual ~CMaleInfo();
	virtual void Serialize(CArchive& ar,int marjorVersion, int minjorVersion);
	void operator=(const CMaleInfo& mi);
public:
	CString EN_name;				//����
	UINT EN_age;				//����
	CString EN_occupation ;			//ְҵ
	CString EN_knowledge_degree ;	//�Ļ��̶�
	CString EN_nation ;				//����
	CString EN_identity_card ;		//���֤���� 
	CString EN_company ;			//��λ 
	CString EN_address ;			//ͨ�ŵ�ַ 
	CString EN_phone ;				//��ϵ�绰 
    CTime   date_chu_zhen;    //����ʱ��
	CString zhu_su ;				//���� 
	CString xian_bing_shi;			//�ֲ�ʷ


	/*���з���Ϣ-������ʷ��*/
	CString ji_wang_gan_yan;		//����		*��|��
	CString jie_he;			//���		*��|��
	CString xin_xue_guan;		//��Ѫ�ܼ���	*��|��
	CString	xing_chuan_bo;		//�Դ�������	*��|��
	CCascadeString cs_mi_niao_sheng_zhi;	//������ֳ��ʷ	*��|��	-��գ��У�
	CString	ji_wang_bing_shi_qi_ta;	//����		-���
	/*������ʷ��*/
	CCascadeInt ci_xi_yan;				//����		*��|��	-���֣��У�
	CString	xu_jiu;					//���		*��|��
	CCascadeString cs_yao_wu_guo_min;			//ҩ�����ʷ	*��|��	-��գ��У�
	CString zhong_da_jing_sheng_ci_ji;		//�ش���̼�ʷ	*��|��
	CString jian_kang_zhuang_kuang_guo_qu;		//����״����ȥ	-���
	CString jian_kang_zhuang_kuang_xian_zai;	//����״������	-���
	CCascadeString cs_chu_sheng_que_xian;		//����ȱ��	*��|��	-��գ��У�

	/*������ʷ��*/
	CString		jin_qin_jie_hun;	//���׽��		*��|��	
	CString		zai_hun;			//�ٻ�		*��|��
	/*������ʷ��*/
	CCascadeString		cs_yi_chuan_bing_shi;	//�Ŵ���ʷ	*��|��	-��գ��У�
	CCascadeString		cs_bu_yun_bu_yu;		//���в�����ʷ	*��|��	-��գ��У�
	/*��һ������顷*/
	int	 shen_gao;				//���		-����
	float	 ti_zhong;				//����		-����
	int	 xue_ya1;				//Ѫѹ		-����
	int	 xue_ya2;				//Ѫѹ		-����
	/*���ڶ�������*/
	CString hu_xu;                  // ����            *��|��
	CString	hou_jie;				//���		*����|�쳣
	CCascadeString	cs_ru_fang;				//�鷿		*����|�쳣
	/*����ֳϵͳ��顷*/
	CCascadeString	 cs_yin_jing;				//����		*����|�쳣	-��գ��쳣��
	CString			 yin_mao;				//��ë		*����|�쳣
	int				gao_wan_ti_ji_zuo;		//غ�������	-����
	int				gao_wan_ti_ji_you;		//غ�������	-����
	CCascadeString	cs_gao_wan_zhi_di_zuo;		//غ���ʵ���	*����|�쳣	-��գ��쳣��
	CCascadeString	cs_gao_wan_zhi_di_you;		//غ���ʵ���	*����|�쳣	-��գ��쳣��
	CCascadeString	cs_fu_gao_zuo;			//��غ��	*����|�쳣	-��գ��쳣��
	CCascadeString	cs_fu_gao_you;			//��غ��	*����|�쳣	-��գ��쳣��
	CCascadeString	cs_shu_jing_guan_zuo;		//�侫����	*����|�쳣	-��գ��쳣��
	CCascadeString	cs_shu_jing_guan_you;		//�侫����	*����|�쳣	-��գ��쳣��
	CCascadeString	cs_jing_suo_jing_mai_zuo;	//����������	*����|�쳣	-��գ��쳣��
	CCascadeString	cs_jing_suo_jing_mai_you;	//����������	*����|�쳣	-��գ��쳣��
	CString sheng_zhi_qi_ta;				//����		-���
		/*����Һ���������*/
    CTime   date_jing_ye_fen_xi;
	int		jin_yu_tian_shu;		//��������	-����
	float		jing_ye_liang;			//��Һ��	-����
	float		EN_PH;				//PH		-����
	int		ye_hua_shi_jian;		//Һ��ʱ��	-����
	float		mi_du;				//�ܶ�		-����
	float		huo_li_A_ji;			//����A��		-����
	float		huo_li_B_ji;			//����B��		-����
	float		huo_li_C_ji;			//����C��		-����
	float		huo_li_D_ji;			//����D��		-����
	int		zheng_chang_xing_tai_lv;//������̬��	-����
	CString		bai_xi_bao;			//��ϸ��		-����

	/*��Ѫ�͡�*/ 
	CString xue_xing;	//Ѫ��		//����
	CString Rh_yin_zi;	//Rh����	//����
	/*��΢�����顷*/
	CString lin_qiu_jun;	//�����		
	CString	zhi_yuan_ti;	//֧ԭ��
	CString	yi_yuan_ti;	//��ԭ��
	/*�����ס�*/
	CString gan_yan;	//����
	CString	EN_HIV;		//HIV
	/*����ֳ���ء�*/
	CString	sheng_zhi_ji_su;	//��ֳ����
	CString	yi_chuan_xue_jian_cha;	//�Ŵ�ѧ���

	CString chu_bu_zhen_duan;	//�������
	/*����*/
	CString nan_yi_shi;			//ҽʦ		-���
    CTime   date_luo_kuan;


	CString         EN_HBSAG;
    CString         EN_HBSAB;
    CString         EN_HBEAG;

    CString         EN_HBEAB;
    CString         EN_HBCAB;
    CString         EN_HAVI;

    CString         EN_HCVAb;               //HCVAb         //����
	CString         EN_HCVAg;              //HCV-Ag        //����
	CString         EN_HIVAb;               //HIVAb         //����

};


