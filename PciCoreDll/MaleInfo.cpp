// mi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MaleInfo.h"

IMPLEMENT_DYNCREATE(CMaleInfo, CObject)
// CMaleInfo

CMaleInfo::CMaleInfo()
:
EN_age(0),				//����     
/*���з���Ϣ-������ʷ��*/
ji_wang_bing_shi_qi_ta( _T("��") ),
/*������ʷ��*/
  
/*������ʷ��*/


/*��һ������顷*/
shen_gao(0),				//���		-����
ti_zhong(0),				//����		-����
xue_ya1(0),				//Ѫѹ		-����
xue_ya2(0),				//Ѫѹ		-����
/*���ڶ�������*/
/*����ֳϵͳ��顷*/
sheng_zhi_qi_ta(_T("��")),	
gao_wan_ti_ji_zuo(0),		//غ�������	-����
gao_wan_ti_ji_you(0),		//غ�������	-����

/*����Һ���������*/
jin_yu_tian_shu(0),			//��������	-����
jing_ye_liang(0),	//��Һ��	-����
EN_PH(0),				//PH		-����
ye_hua_shi_jian(0),	//Һ��ʱ��	-����
mi_du(0),				//�ܶ�		-����
huo_li_A_ji(0),		//����A��		-����
huo_li_B_ji(0),		//����B��		-����
huo_li_C_ji(0),		//����C��		-����
huo_li_D_ji(0),		//����D��		-����
zheng_chang_xing_tai_lv(0),//������̬��	-����


/*��Ѫ�͡�*/

/*��΢�����顷*/

/*�����ס�*/

/*����ֳ���ء�*/
sheng_zhi_ji_su(_T("δ��"))	,//��ֳ����
yi_chuan_xue_jian_cha(_T("δ��"))	

{
	cs_mi_niao_sheng_zhi = CCascadeString(_T("��"));	//������ֳ��ʷ	*��|��	-��գ��У�  
	ci_xi_yan = CCascadeInt(_T("��"));				//����		*��|��	-���֣��У�
	cs_yao_wu_guo_min = CCascadeString(_T("��"));			//ҩ�����ʷ	*��|��	-��գ��У�
    cs_chu_sheng_que_xian = CCascadeString(_T("��"));		//����ȱ��	*��|��	-��գ��У� 
	/*������ʷ��*/
	cs_yi_chuan_bing_shi=CCascadeString(_T("��"));	//�Ŵ���ʷ	*��|��	-��գ��У�
	cs_bu_yun_bu_yu=CCascadeString(_T("��"));		//���в�����ʷ	*��|��	-��գ��У�
    /*���ڶ�������*/
    cs_ru_fang = CCascadeString(_T("�쳣"));
	/*����ֳϵͳ��顷*/
	cs_yin_jing=CCascadeString(_T("�쳣"));				//����		*����|�쳣	-��գ��쳣��
	cs_gao_wan_zhi_di_zuo=CCascadeString(_T("�쳣"));		//غ���ʵ���	*����|�쳣	-��գ��쳣��
	cs_gao_wan_zhi_di_you=CCascadeString(_T("�쳣"));		//غ���ʵ���	*����|�쳣	-��գ��쳣��
	cs_fu_gao_zuo=CCascadeString(_T("�쳣"));			//��غ��	*����|�쳣	-��գ��쳣��
	cs_fu_gao_you=CCascadeString(_T("�쳣"));			//��غ��	*����|�쳣	-��գ��쳣��
	cs_shu_jing_guan_zuo=CCascadeString(_T("�쳣"));		//�侫����	*����|�쳣	-��գ��쳣��
	cs_shu_jing_guan_you=CCascadeString(_T("�쳣"));		//�侫����	*����|�쳣	-��գ��쳣��
	cs_jing_suo_jing_mai_zuo=CCascadeString(_T("�쳣"));	//����������	*����|�쳣	-��գ��쳣��
	cs_jing_suo_jing_mai_you=CCascadeString(_T("�쳣"));	//����������	*����|�쳣	-��գ��쳣��
    date_jing_ye_fen_xi = CTime::GetCurrentTime();
    date_luo_kuan = CTime::GetCurrentTime();
    date_chu_zhen = CTime::GetCurrentTime();
}

CMaleInfo::~CMaleInfo()
{
}


// CMaleInfo ��Ա����
// CMaleInfo ���л�

void CMaleInfo::Serialize(CArchive& ar,int marjorVersion, int minjorVersion)
{
	if (ar.IsStoring())
	{
		ar<< EN_name;//����
		ar<< EN_age;//����
 		ar<< EN_occupation ;//ְҵ
		ar<< EN_knowledge_degree ;//�Ļ��̶�
		ar<< EN_nation ;//����
		ar<< EN_identity_card ;//���֤���� 
		ar<< EN_company ;//��λ 
		ar<< EN_address ;//ͨ�ŵ�ַ 
		ar<< EN_phone ;//��ϵ�绰 
		ar<< zhu_su ;//���� 
		ar<< xian_bing_shi;		//! �ֲ�ʷ  

		/*���з���Ϣ-������ʷ��*/
		ar<< ji_wang_gan_yan;		//����		*��|��                               
		ar<< jie_he;			//���		*��|��                               
		ar<< xin_xue_guan;		//��Ѫ�ܼ���	*��|��                               
		ar<< xing_chuan_bo;		//�Դ�������	*��|��                               
		ar<< ji_wang_bing_shi_qi_ta;	//����		-��� 
			/*������ʷ��*/
		ar<< xu_jiu;				//���		*��|��               
		ar<< zhong_da_jing_sheng_ci_ji;		//�ش���̼�ʷ	*��|��               
		ar<< jian_kang_zhuang_kuang_guo_qu;		//����״����ȥ	-���
		ar<< jian_kang_zhuang_kuang_xian_zai	;//����״������	-���  
		/*������ʷ��*/
		ar<<  jin_qin_jie_hun;       //���׽��              *��|��  
		ar<<zai_hun;                        //�ٻ�          *��|��

		/*��һ������顷*/
		ar<< shen_gao;    //���          -����
		ar<< ti_zhong;     //����          -����
		ar<<xue_ya1;         //Ѫѹ          -����
		ar<<xue_ya2;         //Ѫѹ          -����
		/*���ڶ�������*/
		ar<< hu_xu;        // ����            *��|��
		ar<< hou_jie;      //���          *����|�쳣
		/*����ֳϵͳ��顷*/
		ar<< yin_mao;                               //��ë          *����|�쳣
		ar<< gao_wan_ti_ji_zuo;              //غ�������    -����
		ar<< gao_wan_ti_ji_you;              //غ�������    -����
		ar<< sheng_zhi_qi_ta;                //����          -���
		/*����Һ���������*/

		ar<< jin_yu_tian_shu;                //��������      -����
		ar<< jing_ye_liang;                  //��Һ��        -����
		ar<< EN_PH;                          //PH            -����
		ar<< ye_hua_shi_jian;                //Һ��ʱ��      -����
		ar<< mi_du;                          //�ܶ�          -����
		ar<< huo_li_A_ji;                    //����A��               -����
		ar<< huo_li_B_ji;                    //����B��               -����
		ar<< huo_li_C_ji;                    //����C��               -����
		ar<< huo_li_D_ji;                    //����D��               -����
		ar<< zheng_chang_xing_tai_lv;//������̬��    -����
		ar<< bai_xi_bao;                     //��ϸ��                -����

		/*��Ѫ�͡�*/ //???????????????????????????????��������
		ar<< xue_xing;       //Ѫ��          //����
		ar<< Rh_yin_zi;      //Rh����        //����
		/*��΢�����顷*/
		ar<< lin_qiu_jun;    //�����                
		ar<< zhi_yuan_ti;    //֧ԭ��
		ar<< yi_yuan_ti;     //��ԭ��
		/*�����ס�*/
		
		if(false){
			ar<< gan_yan;        //����
			ar<< EN_HIV;         //HIV
		}else{
			/*��������Ϣ-���� HIV��*/
			ar<< EN_HBSAG;
			ar<< EN_HBSAB;
			ar<<  EN_HBEAG;

			ar<< EN_HBEAB;
			ar<< EN_HBCAB;
			ar<< EN_HAVI;

			ar<< EN_HCVAb; //HCVAb //����
			ar<< EN_HCVAg; //HCV-Ag //����
			ar<< EN_HIVAb; //HIVAb //����
		}

		/*����ֳ���ء�*/
		ar<< sheng_zhi_ji_su;        //��ֳ����
		ar<< yi_chuan_xue_jian_cha;  //�Ŵ�ѧ���
		ar<< chu_bu_zhen_duan;     //�������
		/*����*/
		ar<< nan_yi_shi;                     //ҽʦ          -���


	}
	else
	{
		ar>> EN_name;//����
		ar>> EN_age;//����
 		ar>> EN_occupation ;//ְҵ
		ar>> EN_knowledge_degree ;//�Ļ��̶�
		ar>> EN_nation ;//����
		ar>> EN_identity_card ;//���֤���� 
		ar>> EN_company ;//��λ 
		ar>> EN_address ;//ͨ�ŵ�ַ 
		ar>> EN_phone ;//��ϵ�绰 
		ar>> zhu_su ;//���� 
		ar>> xian_bing_shi;		//! �ֲ�ʷ  

		/*���з���Ϣ-������ʷ��*/
		ar>> ji_wang_gan_yan;		//����		*��|��                               
		ar>> jie_he;			//���		*��|��                               
		ar>> xin_xue_guan;		//��Ѫ�ܼ���	*��|��                               
		ar>> xing_chuan_bo;		//�Դ�������	*��|��                               
		ar>> ji_wang_bing_shi_qi_ta;	//����		-��� 
			/*������ʷ��*/
		ar>> xu_jiu;				//���		*��|��               
		ar>> zhong_da_jing_sheng_ci_ji;		//�ش���̼�ʷ	*��|��               
		ar>> jian_kang_zhuang_kuang_guo_qu;		//����״����ȥ	-���
		ar>> jian_kang_zhuang_kuang_xian_zai	;//����״������	-���  
		/*������ʷ��*/
		ar>>  jin_qin_jie_hun;       //���׽��              *��|��  
		ar>>zai_hun;                        //�ٻ�          *��|��

		/*��һ������顷*/
		ar>> shen_gao;    //���          -����
		ar>> ti_zhong;     //����          -����
		ar>>xue_ya1;         //Ѫѹ          -����
		ar>>xue_ya2;         //Ѫѹ          -����
		/*���ڶ�������*/
		ar>> hu_xu;        // ����            *��|��
		ar>> hou_jie;      //���          *����|�쳣
		/*����ֳϵͳ��顷*/
		ar>> yin_mao;                               //��ë          *����|�쳣
		ar>> gao_wan_ti_ji_zuo;              //غ�������    -����
		ar>> gao_wan_ti_ji_you;              //غ�������    -����
		ar>> sheng_zhi_qi_ta;                //����          -���
		/*����Һ���������*/

		ar>> jin_yu_tian_shu;                //��������      -����
		ar>> jing_ye_liang;                  //��Һ��        -����
		ar>> EN_PH;                          //PH            -����
		ar>> ye_hua_shi_jian;                //Һ��ʱ��      -����
		ar>> mi_du;                          //�ܶ�          -����
		ar>> huo_li_A_ji;                    //����A��               -����
		ar>> huo_li_B_ji;                    //����B��               -����
		ar>> huo_li_C_ji;                    //����C��               -����
		ar>> huo_li_D_ji;                    //����D��               -����
		ar>> zheng_chang_xing_tai_lv;//������̬��    -����
		ar>> bai_xi_bao;                     //��ϸ��               

		/*��Ѫ�͡�*/ //???????????????????????????????��������
		ar>> xue_xing;       //Ѫ��          //����
		ar>> Rh_yin_zi;      //Rh����        //����
		/*��΢�����顷*/
		ar>> lin_qiu_jun;    //�����                
		ar>> zhi_yuan_ti;    //֧ԭ��
		ar>> yi_yuan_ti;     //��ԭ��
		if(marjorVersion>=2 && minjorVersion>2){
			ar>> EN_HBSAG;
			ar>> EN_HBSAB;
			ar>>  EN_HBEAG;

			ar>> EN_HBEAB;
			ar>> EN_HBCAB;
			ar>> EN_HAVI;

			ar>> EN_HCVAb; //HCVAb //����
			ar>> EN_HCVAg; //HCV-Ag //����
			ar>> EN_HIVAb; //HIVAb //����
		}else{
			CString unuseful;
			/*�����ס�*/
			ar>> unuseful;//gan_yan;        //����
			ar>> unuseful;// EN_HIV;         //HIV
		}
		/*����ֳ���ء�*/
		ar>> sheng_zhi_ji_su;        //��ֳ����
		ar>> yi_chuan_xue_jian_cha;  //�Ŵ�ѧ���
		ar>> chu_bu_zhen_duan;     //�������
		/*����*/
		ar>> nan_yi_shi;                     //ҽʦ          -���



	}
	/*���з���Ϣ-������ʷ��*/
	cs_mi_niao_sheng_zhi.Serialize(ar);	//������ֳ��ʷ	*��|��	-��գ��У�  
	/*������ʷ��*/
	ci_xi_yan.Serialize(ar);				//����		*��|��	-���֣��У�
	cs_yao_wu_guo_min.Serialize(ar);			//ҩ�����ʷ	*��|��	-��գ��У�
	cs_chu_sheng_que_xian.Serialize(ar);		//����ȱ��	*��|��	-��գ��У� 
	/*������ʷ��*/
	cs_yi_chuan_bing_shi.Serialize(ar);      //�Ŵ���ʷ      *��|��  -��գ��У�
	cs_bu_yun_bu_yu.Serialize(ar);           //���в�����ʷ  *��|��  -��գ��У�
    /*�ڶ�����*/
  //  if ( ar.IsStoring())
    {
        cs_ru_fang.Serialize( ar );
    }
	/*����ֳϵͳ��顷*/
	cs_yin_jing.Serialize(ar);                       //����          *����|�쳣      -��գ��쳣��
	cs_gao_wan_zhi_di_zuo.Serialize(ar);             //غ���ʵ���    *����|�쳣      -��գ��쳣��
	cs_gao_wan_zhi_di_you.Serialize(ar);             //غ���ʵ���    *����|�쳣      -��գ��쳣��
	cs_fu_gao_zuo.Serialize(ar);                     //��غ��        *����|�쳣      -��գ��쳣��
	cs_fu_gao_you.Serialize(ar);                     //��غ��        *����|�쳣      -��գ��쳣��
	cs_shu_jing_guan_zuo.Serialize(ar);              //�侫����      *����|�쳣      -��գ��쳣��
	cs_shu_jing_guan_you.Serialize(ar);              //�侫����      *����|�쳣      -��գ��쳣��
	cs_jing_suo_jing_mai_zuo.Serialize(ar);  //����������    *����|�쳣      -��գ��쳣��
	cs_jing_suo_jing_mai_you.Serialize(ar);  //����������    *����|�쳣      -��գ��쳣��
    date_jing_ye_fen_xi.Serialize64( ar );  //��Һ�������-����
    date_luo_kuan.Serialize64( ar );
    date_chu_zhen.Serialize64( ar );
    if (ar.IsStoring())
{
    
}
			
}

void CMaleInfo::operator=(const CMaleInfo& mi)
{
	EN_name=mi. EN_name;//����
	EN_age=mi. EN_age;//����
	EN_occupation=mi. EN_occupation ;//ְҵ
	EN_knowledge_degree=mi. EN_knowledge_degree ;//�Ļ��̶�
	EN_nation=mi. EN_nation ;//����
	EN_identity_card=mi. EN_identity_card ;//���֤���� 
	EN_company=mi. EN_company ;//��λ 
	EN_address =mi. EN_address ;//ͨ�ŵ�ַ 
	EN_phone =mi. EN_phone ;//��ϵ�绰 
	zhu_su =mi. zhu_su ;//���� 
    date_chu_zhen = mi.date_chu_zhen ;//����ʱ��
	xian_bing_shi=mi. xian_bing_shi;		//! �ֲ�ʷ  



	/*���з���Ϣ-������ʷ��*/
	ji_wang_gan_yan=mi. ji_wang_gan_yan;		//����		*��|��                               
	jie_he=mi. jie_he;			//���		*��|��                               
	xin_xue_guan=mi. xin_xue_guan;		//��Ѫ�ܼ���	*��|��                               
	xing_chuan_bo=mi. xing_chuan_bo;		//�Դ�������	*��|��                               
	ji_wang_bing_shi_qi_ta=mi. ji_wang_bing_shi_qi_ta;	//����		-��� 


	/*������ʷ��*/
	xu_jiu=mi. xu_jiu;				//���		*��|��               
	zhong_da_jing_sheng_ci_ji=mi. zhong_da_jing_sheng_ci_ji;		//�ش���̼�ʷ	*��|��               
	jian_kang_zhuang_kuang_guo_qu=mi. jian_kang_zhuang_kuang_guo_qu;		//����״����ȥ	-���
	jian_kang_zhuang_kuang_xian_zai	=mi. jian_kang_zhuang_kuang_xian_zai	;//����״������	-���  


	/*������ʷ��*/
	jin_qin_jie_hun=mi.  jin_qin_jie_hun;       //���׽��              *��|��  
	zai_hun=mi.zai_hun;                        //�ٻ�          *��|��


	//*��һ������顷*/
	shen_gao=mi. shen_gao;    //���          -����
	ti_zhong=mi. ti_zhong;     //����          -����
	xue_ya1=mi.xue_ya1;         //Ѫѹ          -����
	xue_ya2=mi.xue_ya2;         //Ѫѹ          -����
	/*���ڶ�������*/
	hu_xu=mi. hu_xu;        // ����            *��|��
	hou_jie=mi. hou_jie;      //���          *����|�쳣
	cs_ru_fang=mi. cs_ru_fang;     //�鷿          *����|�쳣


	/*����ֳϵͳ��顷*/
	yin_mao=mi. yin_mao;                               //��ë          *����|�쳣
	gao_wan_ti_ji_zuo=mi. gao_wan_ti_ji_zuo;              //غ�������    -����
	gao_wan_ti_ji_you=mi. gao_wan_ti_ji_you;              //غ�������    -����
	sheng_zhi_qi_ta=mi. sheng_zhi_qi_ta;                //����          -���

	/*����Һ���������*/
    date_jing_ye_fen_xi = mi.date_jing_ye_fen_xi;   //��Һ�������-����
	jin_yu_tian_shu=mi. jin_yu_tian_shu;                //��������      -����
	jing_ye_liang=mi. jing_ye_liang;                  //��Һ��        -����
	EN_PH=mi. EN_PH;                          //PH            -����
	ye_hua_shi_jian=mi. ye_hua_shi_jian;                //Һ��ʱ��      -����
	mi_du=mi. mi_du;                          //�ܶ�          -����
	huo_li_A_ji=mi. huo_li_A_ji;                    //����A��               -����
	huo_li_B_ji=mi. huo_li_B_ji;                    //����B��               -����
	huo_li_C_ji=mi. huo_li_C_ji;                    //����C��               -����
	huo_li_D_ji=mi. huo_li_D_ji;                    //����D��               -����
	zheng_chang_xing_tai_lv=mi. zheng_chang_xing_tai_lv;//������̬��    -����
	bai_xi_bao=mi. bai_xi_bao;                     //��ϸ��                -����

	 /*��Ѫ�͡�*/ //???????????????????????????????��������
	xue_xing=mi. xue_xing;       //Ѫ��          //����
	Rh_yin_zi=mi. Rh_yin_zi;      //Rh����        //����


	/*��΢�����顷*/
	lin_qiu_jun=mi. lin_qiu_jun;    //�����                
	zhi_yuan_ti=mi. zhi_yuan_ti;    //֧ԭ��
	yi_yuan_ti=mi. yi_yuan_ti;     //��ԭ��


	/*�����ס�*/
	gan_yan=mi. gan_yan;        //����
	EN_HIV=mi. EN_HIV;         //HIV


	/*����ֳ���ء�*/
	sheng_zhi_ji_su=mi. sheng_zhi_ji_su;        //��ֳ����
	yi_chuan_xue_jian_cha=mi. yi_chuan_xue_jian_cha;  //�Ŵ�ѧ���
	chu_bu_zhen_duan=mi. chu_bu_zhen_duan;     //�������

	/*���з���Ϣ-������ʷ��*/
	cs_mi_niao_sheng_zhi=mi.cs_mi_niao_sheng_zhi;	//������ֳ��ʷ	*��|��	-��գ��У�  

	/*������ʷ��*/
	ci_xi_yan=mi.ci_xi_yan;				//����		*��|��	-���֣��У�
	cs_yao_wu_guo_min=mi.cs_yao_wu_guo_min;			//ҩ�����ʷ	*��|��	-��գ��У�
	cs_chu_sheng_que_xian=mi.cs_chu_sheng_que_xian;		//����ȱ��	*��|��	-��գ��У� 
	/*������ʷ��*/
	cs_yi_chuan_bing_shi=mi.cs_yi_chuan_bing_shi;      //�Ŵ���ʷ      *��|��  -��գ��У�
	cs_bu_yun_bu_yu=mi.cs_bu_yun_bu_yu;           //���в�����ʷ  *��|��  -��գ��У�

	/*����ֳϵͳ��顷*/
	cs_yin_jing=mi.cs_yin_jing;                       //����          *����|�쳣      -��գ��쳣��
	cs_gao_wan_zhi_di_zuo=mi.cs_gao_wan_zhi_di_zuo;             //غ���ʵ���    *����|�쳣      -��գ��쳣��
	cs_gao_wan_zhi_di_you=mi.cs_gao_wan_zhi_di_you;             //غ���ʵ���    *����|�쳣      -��գ��쳣��
	cs_fu_gao_zuo=mi.cs_fu_gao_zuo;                     //��غ��        *����|�쳣      -��գ��쳣��
	cs_fu_gao_you=mi.cs_fu_gao_you;                     //��غ��        *����|�쳣      -��գ��쳣��
	cs_shu_jing_guan_zuo=mi.cs_shu_jing_guan_zuo;              //�侫����      *����|�쳣      -��գ��쳣��
	cs_shu_jing_guan_you=mi.cs_shu_jing_guan_you;              //�侫����      *����|�쳣      -��գ��쳣��
	cs_jing_suo_jing_mai_zuo=mi.cs_jing_suo_jing_mai_zuo;  //����������    *����|�쳣      -��գ��쳣��
	cs_jing_suo_jing_mai_you=mi.cs_jing_suo_jing_mai_you;  //����������    *����|�쳣      -��գ��쳣��
    /*����*/
    nan_yi_shi=mi. nan_yi_shi;                     //ҽʦ          -���
    date_luo_kuan = mi.date_luo_kuan;
    date_chu_zhen = mi.date_chu_zhen; //����ʱ��

	EN_HBSAG=mi.EN_HBSAG ;
    EN_HBSAB=mi.EN_HBSAB ;
    EN_HBEAG=mi. EN_HBEAG;

    EN_HBEAB=mi. EN_HBEAB;
    EN_HBCAB=mi.EN_HBCAB;
    EN_HAVI=mi.EN_HAVI;
	
    EN_HCVAb=mi.EN_HCVAb; //HCVAb //����
	EN_HCVAg=mi.EN_HCVAg; //HCV-Ag //����
	EN_HIVAb=mi.EN_HIVAb; //HIVAb //����
}