#pragma once
#include "../GeneralDll/CascadeInt.h"
#include "../GeneralDll/CascadeString.h"
// CFemaleInfo ����Ŀ��

class AFX_EXT_CLASS CFemaleInfo : public CObject
{
protected:
	DECLARE_DYNCREATE(CFemaleInfo)
public:
	CFemaleInfo();
	virtual ~CFemaleInfo();
	virtual void Save2_1(CArchive& ar);
	virtual void Serialize(CArchive& ar,int marjorVersion, int minjorVersion);
	void operator=(const CFemaleInfo& fi);
public:
	/*��Ů����Ϣ����*/
	CString EN_name;				//����
	int EN_age;				//����
	CString EN_occupation ;			//ְҵ
	CString EN_knowledge_degree ;	//�Ļ��̶�
	CString EN_nation ;				//����
	CString EN_identity_card ;		//���֤���� 
	CString EN_company ;			//��λ 
	CString EN_address ;			//ͨ�ŵ�ַ 
	CString EN_phone ;				//��ϵ�绰 
	CString EN_postalcode          ;                       //��������
	CString  zhen_duan               ;                       //���	
	CString zhu_su ;				//���� 
	CString xian_bing_shi;			//�ֲ�ʷ
// 
// 	/*��IUIʱ�䣺��*/
// 	CString         EN_IUI_time_1;          //1
// 	CString         EN_IUI_time_2;          //2
// 	CString         EN_IUI_time_3;          //3
// 
// 	/*����֣���*/
// 	CString jie_ju;			//���


	/*��Ů����Ϣ-����ʷ��*/
	CCascadeString          cs_ji_wang_gan_yan;                        //����          *��|��
	CCascadeString          cs_jie_he;                 //���          *��|��
	CCascadeString          cs_shen_zang_ji_bing;                       //���༲��      *��|��
	CCascadeString          cs_xin_xue_guan_ji_bing;                   //��Ѫ�ܼ���    *��|��
	CCascadeString          cs_mi_niao_xi_tong_gan_ran;                        //����ϵ��Ⱦ    *��|��
	CCascadeString          cs_xing_chuan_bo_ji_bing_shi;       //�Դ�������ʷ  *��|��
	CCascadeString          cs_lan_wei_yan;                    //��β��                *��|��
	CCascadeString          cs_pen_qiang_yan;                  //��ǻ��                *��|��
	CCascadeString          cs_shou_shu_shi;                   //����ʷ                *��|��  -��գ��У�
	CString                 ji_wang_qi_ta;                  //����                  -���

	/*��Ů����Ϣ-����ʷ��*/
	CCascadeInt             ci_xi_yan;//����           *��|��  -���֣��У�
	CString                 xu_jiu;                 //���          *��|��
	CString                 xi_du;                  //����          *��|��
	CCascadeString          cs_yao_wu_guo_min;//ҩ�����ʷ   *��|��  -��գ��У�
	CString                 zhong_da_jing_shen_ci_ji;                       //�ش���̼�ʷ        *��|��
	CCascadeString			cs_jian_kang_zhuang_kuang; 
	CCascadeString          cs_chu_sheng_que_xian;//����ȱ��           *��|��  -��գ��У�
	/*��Ů����Ϣ-�¾�ʷ��*/
	int                     chu_chao;                       //����          -����
	CString                 yue_jing_shi_yue_jing_zhou_qi1;                       //�¾�����              -����   -����
	CString					yue_jing_shi_yue_jing_zhou_qi2;                       //�¾�����              -����   -����
	CString                 mo_ci_yue_jing;                 //ĩ���¾�              //����
	CString                 jing_liang;                     //����          *����|��|��
	CString                 tong_jing;                      //ʹ��          *��|��
	/*��Ů����Ϣ-����ʷ��*/
	CString                 jin_qin_jie_hun;                        //���׽��              *��|��
	CString                 zai_hun;                        //�ٻ�          *��|��
	CString                 ren_chen;                       //����          *��|��
	CString                 mo_ci_ren_shen;                 //ĩ������ʱ��  �����¡�
	int                 yun;                    //��            //����
	int                 chan;                   //��            //����
	int                     ren_gong_liu_chan;      //�˹�����      -����
	int                     zi_ran_liu_chan;        //��Ȼ����      -����
	int                     yao_liu;                //ҩ��          -����
	int                     yin_chan;               //����          -����
	int                     zao_chan;               //���          -����
	int                     gong_wai_yuan_zuo;      //�����У���    -����
	int                     gong_wai_yuan_you;      //�����У��ң�    -����
	int                     zu_yue_chan;            //���²�        -����
	int                     xian_you_zi_nv;         //������Ů      -����
	/*��Ů����Ϣ-����ʷ��*/
	CCascadeString          cs_yi_chuan_bing_shi;      //�Ŵ���ʷ      *��|��  -��գ�//������
	CCascadeString          cs_bu_yun_bu_yu_shi;       //���в���ʷ    *��|��  -��գ�//������

	/*��Ů����Ϣ-����顷*/
	float                     yi_ban_qing_kuang_T;    //һ�����T     -����
	int                     yi_ban_qing_kuang_P;    //һ�����P     -����
	int                     yi_ban_qing_kuang_R;    //һ�����R     -����
	int                     yi_ban_qing_kuang_BP1;   //һ�����BP    -����
	int                     yi_ban_qing_kuang_BP2;   //һ�����BP    -����
	int                     shen_gao;               //���          -����
	float                     ti_zhong;               //����          -����
	CCascadeString          cs_ying_yang;              //Ӫ��          *����|�쳣      -��գ��쳣��
	CCascadeString          cs_fa_yu;                  //����          *����|�쳣      -��գ��쳣��
	CCascadeString          cs_jing_shen;              //����          *����|�쳣      -��գ��쳣��
	CCascadeString          cs_mao_fa;                 //ë��          *����|�쳣      -��գ��쳣��
	CCascadeString          cs_pi_fu_nian_mo;          //Ƥ��ճĤ      *����|�쳣      -��գ��쳣��
	CCascadeString          cs_lin_ba_jie;             //�ܰͽ�        *����|�쳣      -��գ��쳣��
	CCascadeString          cs_ru_fang;                //�鷿          *����|�쳣      -��գ��쳣��
	CString          yi_ru;                  //����          *����|�쳣      -��գ��쳣��
	CCascadeString          cs_xin;                    //��            *����|�쳣      -��գ��쳣��
	CCascadeString          cs_fei;                    //��            *����|�쳣      -��գ��쳣��
	CCascadeString          cs_gan;                    //��            *����|�쳣      -��գ��쳣��
	CCascadeString          cs_pi;                     //Ƣ            *����|�쳣      -��գ��쳣��
	CCascadeString          cs_shen;                   //��            *����|�쳣      -��գ��쳣��
	CCascadeString          cs_ji_zhu_si_zhi;          //������֫      *����|�쳣      -��գ��쳣��
	/*��Ů����Ϣ-���Ƽ�顷*/
	CCascadeString          cs_wai_yin;                //����          *����|�쳣      -��գ��쳣��
	CCascadeString          cs_yin_dao;                //����          *����|�쳣      -��գ��쳣��
	CCascadeString          cs_gong_jing;              //����          *�⻬|����      *��|��|�أ����ã�
	CString                 gong_jing_qi_ta;     //��������              -���
	CString                 zi_gong;                //�ӹ�          *ǰλ|��λ|ƽλ
	CCascadeString          cs_fu_ke_jian_cha_zi_gong_da_xiao;        //�ӹ���С            
	CString                 zhi_di;                 //�ʵ�          *��|��|Ӳ
	CString                 huo_dong_du;            //���                *�|����|�̶�
	CString                 ya_tong;                //ѹʹ          *��|��
	CCascadeString          cs_fu_jian_zuo;            //��������      *����|�쳣      -��գ��쳣��
	CCascadeString          cs_fu_jian_you;            //�������ң�      *����|�쳣      -��գ��쳣��
	//CString                 qi_ta;                  //����          -���
	/*��Ů����Ϣ-.��*/
	CString         xue_chang_gui;          //Ѫ����                -���
	CString         niao_chang_gui;         //�򳣹�                -���
	/*��Ů����Ϣ-Ѫ�͡�*/
	CString         xue_xing;               //Ѫ��          //����
	CString         Rh_yin_zi;              //Rh����        //����
	/*��Ů����Ϣ-�����ڷ��ڡ�*/
	float             EN_FSH;                 //FSH           -����
	float             EN_E_2;                 //E���±�2��      -����
	float             EN_P;                   //P             -����
	float             EN_LH;                  //LH            -����
	float             EN_PRL;                 //PRL   -����
	float             EN_T;                   //T             -����
	/*��Ů����Ϣ-TORCH��*/
	CString         gong_xing_chong;                        //���γ�                //����
	CString         ju_xi_bao_bing_du;                      //��ϸ������    //����
	CString         feng_zhen_bing_du;                      //�����              //����
	CString         dan_chun_pao_zhen_bing_du_II_xing;      //���������II��       //����
	/*��Ů����Ϣ-���� HIV��*/
    CString         EN_HBSAG;
    CString         EN_HBSAB;
    CString         EN_HBEAG;

    CString         EN_HBEAB;
    CString         EN_HBCAB;
    CString         EN_HAVI;

    CString         EN_HCVAb;               //HCVAb         //����
	CString         EN_HCVAg;              //HCV-Ag        //����
	CString         EN_HIVAb;               //HIVAb         //����
	/*��Ů����Ϣ-�����Ŀ���*/
	CString         kang_zi_gong_nei_mo_kang_ti;    //���ӹ���Ĥ����//����
	CString         kang_luan_chao_kang_ti;         //���ѳ�����    //����
	CString         kang_tou_ming_dai_kang_ti;      //��͸��������  //����
	CString         kang_jing_zi_kang_ti;           //�����ӿ���    //����
	/*��Ů����Ϣ-.��*/
	CString gan_gong;//�ι�         //����
	CString shen_gong;//����                //����
	CString ran_se_ti;//Ⱦɫ��              //����

	/*��Ů����Ϣ-������Ƭ��*/
	CString gong_jing_gua_pian;		//������Ƭ                -���
	/*��Ů����Ϣ-����ͿƬ��*/
	CString         zhi_yuan_ti;            //֧ԭ��                //����
	CString         yi_yuan_ti;             //��ԭ��                //����
	CString         di_chong;               //�γ�                  //����
	CString         mei_jun;                //ù��                  //����
	CString         xian_suo_xi_bao;        //����ϸ��              //����
	CString         qing_jie_du;            //����                
	/*��Ů����Ϣ-�ӹ����ѹ���Ӱ��*/
	CString          zi_gong_xing_tai;              //�ӹ���̬      -���
	CString          zuo_ce_shu_luan_guan;          //������ѹ�    -���
	CString          you_ce_shu_luan_guan;          //�Ҳ����ѹ�    -���
	/*��Ů����Ϣ-����B����*/
	CString			fu_ke_Bchao_ri_qi;					//����B������
	CString             fu_ke_Bchao_zi_gong_da_xiao;        //�ӹ���С              -����
	float             fu_ke_Bchao_zi_gong_nei_mo;         //�ӹ���Ĥ              -����  
    CString     fu_ke_B_chao_zi_gong_lei_xing;      //������ABC��
	CString         fu_ke_B_chao_you_ce_luan_chao;       //�Ҳ��ѳ�              -���
	CString         fu_ke_B_chao_you_ce_luan_chao_Fc;       //�Ҳ��ѳ�Fc              -���
	CString         fu_ke_B_chao_zuo_ce_luan_chao;       //����ѳ�              -���
	CString         fu_ke_B_chao_zuo_ce_luan_chao_Fc;       //����ѳ�Fc              -���

	/*��Ů����Ϣ-��ǻ����*/
	CString         gong_qiang_jing;        //��ǻ��                -���
	//?????????????//����    ������ǰ��Ȼ�������Ѽ�⣺��
	/*��Ů����Ϣ-//������*/

    CString           nv_pai_luan_jian_ce_ri_qi1;
	CString         yue_jing_zhou_qi1;       //�¾�����              //����
	CString         luan_pao_zhi_jing1;      //����ֱ��              //����
	CString         zi_gong_nei_mo1;         //�ӹ���Ĥ              //����

    CString           nv_pai_luan_jian_ce_ri_qi2;
    CString         yue_jing_zhou_qi2;       //�¾�����              //����
    CString         luan_pao_zhi_jing2;      //����ֱ��              //����
    CString         zi_gong_nei_mo2;         //�ӹ���Ĥ              //����


    CString           nv_pai_luan_jian_ce_ri_qi3;
    CString         yue_jing_zhou_qi3;       //�¾�����              //����
    CString         luan_pao_zhi_jing3;      //����ֱ��              //����
    CString         zi_gong_nei_mo3;         //�ӹ���Ĥ              //����


    CString           nv_pai_luan_jian_ce_ri_qi4;
    CString         yue_jing_zhou_qi4;       //�¾�����              //����
    CString         luan_pao_zhi_jing4;      //����ֱ��              //����
    CString         zi_gong_nei_mo4;         //�ӹ���Ĥ              //����
	/*��Ů����Ϣ-��ʷС�ᡷ*/
	CString         bing_shi_xiao_jie;      //��ʷС��              -���
	/*��Ů����Ϣ-��ϡ�*/
	//CString         zhen_duan;              //���          -���
	/*��Ů����Ϣ-���Ƽƻ���*/
	CString          zheng_liao_ji_hua;     //���Ƽƻ�              -���
	/*��Ů����Ϣ-��*/
	CString         nv_yi_shi;              //ҽʦ          -���
	//CString         nv_nian_yue_ri;         //������                �������ա�
    CTime           nv_date_luo_kuan;
};


