// FemaleInfo.cpp : ʵ���ļ�

#include "stdafx.h"
#include "FemaleInfo.h"
#include <shlwapi.h>


// CFemaleInfo
IMPLEMENT_DYNCREATE(CFemaleInfo, CObject)

CFemaleInfo::CFemaleInfo()
:EN_age(0),				//����
gong_jing_gua_pian(_T("δ��")),
/*��Ů����Ϣ-�¾�ʷ��*/
chu_chao(0),                       //����          -����
yue_jing_shi_yue_jing_zhou_qi1(0),                       //�¾�����              -����   -����
yue_jing_shi_yue_jing_zhou_qi2(_T("")),                       //�¾�����              -����   -����

/*��Ů����Ϣ-����ʷ��*/
yun(),
chan(0),
ren_gong_liu_chan(0),      //�˹�����      -����
zi_ran_liu_chan(0),        //��Ȼ����      -����
yao_liu(0),                //ҩ��          -����
yin_chan(0),               //����          -����
zao_chan(0),               //���          -����
gong_wai_yuan_zuo(0),      //�����У���    -����
gong_wai_yuan_you(0),      //�����У��ң�    -����
zu_yue_chan(0),            //���²�        -����
xian_you_zi_nv(0),         //������Ů      -����
/*��Ů����Ϣ-����顷*/
yi_ban_qing_kuang_T(0),    //һ�����T     -����
yi_ban_qing_kuang_P(0),    //һ�����P     -����
yi_ban_qing_kuang_R(0),    //һ�����R     -����
yi_ban_qing_kuang_BP1(0),   //һ�����BP    -����   -����
yi_ban_qing_kuang_BP2(0),
shen_gao(0),               //���          -����
ti_zhong(0),               //����          -����
/*��Ů����Ϣ-�����ڷ��ڡ�*/
EN_FSH(0),                 //FSH           -����
EN_E_2(0),                 //E���±�2��      -����
EN_P(0),                   //P             -����
EN_LH(0),                  //LH            -����
EN_PRL(0),                 //PRL   -����
EN_T(0),                   //T             -����
/* �� �ι� ��*/
ran_se_ti(_T("δ��")),
/*��Ů����Ϣ-����B����*/
fu_ke_Bchao_zi_gong_da_xiao(_T("")),        //�ӹ���С              -����
fu_ke_Bchao_zi_gong_nei_mo(0)         //�ӹ���Ĥ              -����   //������ABC��

{
	/*��Ů����Ϣ-����ʷ��*/
	cs_shou_shu_shi= CCascadeString(_T("��"));                  //����ʷ                *��|��  -��գ��У�
	/*��Ů����Ϣ-����ʷ��*/
	ci_xi_yan=CCascadeInt(_T("��"));//����           *��|��  -���֣��У�
	cs_yao_wu_guo_min=CCascadeString(_T("��"));//ҩ�����ʷ   *��|��  -��գ��У�
	cs_jian_kang_zhuang_kuang = CCascadeString( _T("����") );
	cs_chu_sheng_que_xian=CCascadeString(_T("��"));//����ȱ��           *��|��  -��գ��У�

	/*��Ů����Ϣ-����ʷ��*/
	cs_yi_chuan_bing_shi= CCascadeString(_T("��"));     //�Ŵ���ʷ      *��|��  -��գ�//������
	cs_bu_yun_bu_yu_shi= CCascadeString(_T("��"));      //���в���ʷ    *��|��  -��գ�//������

	/*��Ů����Ϣ-����顷*/

	cs_ying_yang= CCascadeString(_T("�쳣"));             //Ӫ��          *����|�쳣      -��գ��쳣��
	cs_fa_yu= CCascadeString(_T("�쳣"));                 //����          *����|�쳣      -��գ��쳣��
	cs_jing_shen= CCascadeString(_T("�쳣"));             //����          *����|�쳣      -��գ��쳣��
	cs_mao_fa= CCascadeString(_T("�쳣"));                //ë��          *����|�쳣      -��գ��쳣��
	cs_pi_fu_nian_mo= CCascadeString(_T("�쳣"));         //Ƥ��ճĤ      *����|�쳣      -��գ��쳣��
	cs_lin_ba_jie= CCascadeString(_T("�쳣"));            //�ܰͽ�        *����|�쳣      -��գ��쳣��
	cs_ru_fang= CCascadeString(_T("�쳣"));               //�鷿          *����|�쳣      -��գ��쳣��
	cs_xin= CCascadeString(_T("�쳣"));                   //��            *����|�쳣      -��գ��쳣��
	cs_fei= CCascadeString(_T("�쳣"));                   //��            *����|�쳣      -��գ��쳣��
	cs_gan= CCascadeString(_T("�쳣"));                   //��            *����|�쳣      -��գ��쳣��
	cs_pi= CCascadeString(_T("�쳣"));                    //Ƣ            *����|�쳣      -��գ��쳣��
	cs_shen= CCascadeString(_T("�쳣"));                  //��            *����|�쳣      -��գ��쳣��
	cs_ji_zhu_si_zhi= CCascadeString(_T("�쳣"));         //������֫      *����|�쳣      -��գ��쳣��
	/*��Ů����Ϣ-���Ƽ�顷*/
	cs_wai_yin= CCascadeString(_T("�쳣"));               //����          *����|�쳣      -��գ��쳣��
	cs_yin_dao= CCascadeString(_T("�쳣"));               //����          *����|�쳣      -��գ��쳣��
	cs_gong_jing= CCascadeString(_T("����"));             //����          *�⻬|����      *��|��|�أ����ã�
	cs_fu_ke_jian_cha_zi_gong_da_xiao= CCascadeString(_T("�쳣"));       //�ӹ���С              *����|�쳣      -��գ��쳣��
	cs_fu_jian_zuo= CCascadeString(_T("�쳣"));           //��������      *����|�쳣      -��գ��쳣��
	cs_fu_jian_you= CCascadeString(_T("�쳣"));           //�������ң�      *����|�쳣      -��գ��쳣��

	pen_qiang_yan = CCascadeString(_T("��"));           //��ǻ��      *��|��      -��գ��У�

    nv_date_luo_kuan = CTime::GetCurrentTime();//
}

CFemaleInfo::~CFemaleInfo()
{
}

void CFemaleInfo::Save2_1(CArchive& ar)
{
	/*��Ů����Ϣ����*/
	ar<< EN_name;				//����
	ar<< EN_age;				//����
	ar<< EN_occupation ;			//ְҵ
	ar<< EN_knowledge_degree ;	//�Ļ��̶�
	ar<< EN_nation ;				//����
	ar<< EN_identity_card ;		//���֤���� 
	ar<< EN_company ;			//��λ 
	ar<< EN_address ;			//ͨ�ŵ�ַ 
	ar<< EN_phone ;				//��ϵ�绰 
	ar<< EN_postalcode ;  //��������
	ar<< zhen_duan ;  //���	
	ar<< zhu_su ;				//���� 
	ar<< xian_bing_shi;			//�ֲ�ʷ

	/*��Ů����Ϣ-����ʷ��*/
	ar<<  ji_wang_gan_yan;  //���� *��|��
	ar<<  jie_he;  //��� *��|��
	ar<<  shen_zang_ji_bing;  //���༲�� *��|��
	ar<<  xin_xue_guan_ji_bing;  //��Ѫ�ܼ��� *��|��
	ar<<  mi_niao_xi_tong_gan_ran;  //����ϵ��Ⱦ *��|��
	ar<<  xing_chuan_bo_ji_bing_shi; //�Դ�������ʷ *��|��
	ar<<  lan_wei_yan;  //��β�� *��|��
	//ar<<  pen_qiang_yan;  //��ǻ�� *��|��
	pen_qiang_yan.Serialize(ar);
						AfxMessageBox( pen_qiang_yan.strBase+_T("*")+pen_qiang_yan.strHasMore+_T("*")+pen_qiang_yan.strMore );
	ar<<  ji_wang_qi_ta;  //����  -���

	/*��Ů����Ϣ-����ʷ��*/
	ar<<  xu_jiu;  //��� *��|��
	ar<<  xi_du;  //���� *��|��
	ar<<  zhong_da_jing_shen_ci_ji;  //�ش���̼�ʷ *��|��
	/*��Ů����Ϣ-�¾�ʷ��*/
	ar<<  chu_chao;  //���� -����
	ar<<  yue_jing_shi_yue_jing_zhou_qi1;  //�¾����� -���� -����
	ar<<  yue_jing_shi_yue_jing_zhou_qi2;  //�¾����� -���� -����
	ar<<  mo_ci_yue_jing;  //ĩ���¾� //����
	ar<<  jing_liang;  //���� *����|��|��
	ar<<  tong_jing;  //ʹ�� *��|��
	/*��Ů����Ϣ-����ʷ��*/
	ar<<  jin_qin_jie_hun;  //���׽�� *��|��
	ar<<  zai_hun;  //�ٻ� *��|��
	ar<<  ren_chen;  //���� *��|��
	ar<<  mo_ci_ren_shen;  //ĩ������ʱ�� �����¡�
	ar<<  yun;  //�� //����
	ar<<  chan;  //�� //����
	ar<<  ren_gong_liu_chan; //�˹����� -����
	ar<<  zi_ran_liu_chan; //��Ȼ���� -����
	ar<<  yao_liu; //ҩ�� -����
	ar<<  yin_chan; //���� -����
	ar<<  zao_chan; //��� -����
	ar<<  gong_wai_yuan_zuo; //�����У��� -����
	ar<<  gong_wai_yuan_you; //�����У��ң� -����
	ar<<  zu_yue_chan; //���²� -����
	ar<<  xian_you_zi_nv; //������Ů -����
	/*��Ů����Ϣ-����顷*/
	ar<<  yi_ban_qing_kuang_T; //һ�����T -����
	ar<<  yi_ban_qing_kuang_P; //һ�����P -����
	ar<<  yi_ban_qing_kuang_R; //һ�����R -����
	ar<<  yi_ban_qing_kuang_BP1; //һ�����BP -���� -����
	ar<< yi_ban_qing_kuang_BP2;
	ar<<  shen_gao; //��� -����
	ar<<  ti_zhong; //���� -����
	ar<< yi_ru; //���� - ��|��

	/*��Ů����Ϣ-���Ƽ�顷*/
	ar<<  gong_jing_qi_ta; //�������� -���
	ar<<  zi_gong; //�ӹ� *ǰλ|��λ|ƽλ
	ar<<  zhi_di;  //�ʵ� *��|��|Ӳ
	ar<<  huo_dong_du; //��� *�|����|�̶�
	ar<<  ya_tong; //ѹʹ *��|��
	/*��Ů����Ϣ-.��*/
	ar<< xue_chang_gui; //Ѫ���� -���
	ar<< niao_chang_gui; //�򳣹� -���
	/*��Ů����Ϣ-Ѫ�͡�*/
	ar<< xue_xing; //Ѫ�� //����
	ar<< Rh_yin_zi; //Rh���� //����
	/*��Ů����Ϣ-�����ڷ��ڡ�*/
	ar<< EN_FSH;  //FSH -����
	ar<< EN_E_2;  //E���±�2�� -����
	ar<< EN_P;  //P -����
	ar<< EN_LH;  //LH -����
	ar<< EN_PRL;  //PRL -����
	ar<< EN_T;  //T -����
	/*��Ů����Ϣ-TORCH��*/
	ar<< gong_xing_chong;  //���γ� //����
	ar<< ju_xi_bao_bing_du;  //��ϸ������ //����
	ar<< feng_zhen_bing_du;  //����� //����
	ar<< dan_chun_pao_zhen_bing_du_II_xing; //���������II�� //����
	/*��Ů����Ϣ-���� HIV��*/
	ar<< EN_HBSAG;
	ar<< EN_HBSAB;
	ar<<  EN_HBEAG;

	ar<< EN_HBEAB;
	ar<<EN_HBCAB;
	ar<< EN_HAVI;

	ar<< EN_HCVAb; //HCVAb //����
	ar<< EN_HCVAg; //HCV-Ag //����
	ar<< EN_HIVAb; //HIVAb //����
	/*��Ů����Ϣ-�����Ŀ��塷*/
	ar<< kang_zi_gong_nei_mo_kang_ti; //���ӹ���Ĥ����//����
	ar<< kang_luan_chao_kang_ti; //���ѳ����� //����
	ar<< kang_tou_ming_dai_kang_ti; //��͸�������� //����
	ar<< kang_jing_zi_kang_ti; //�����ӿ��� //����
	/*��Ů����Ϣ-.��*/
	ar<< gan_gong;//�ι� //����
	ar<< shen_gong;//���� //����
	ar<< ran_se_ti;//Ⱦɫ�� //����
	/*��Ů����Ϣ-������Ƭ��*/
	ar<< gong_jing_gua_pian;		//������Ƭ -���
	/*��Ů����Ϣ-����ͿƬ��*/
	ar<< zhi_yuan_ti; //֧ԭ�� //����
	ar<< yi_yuan_ti; //��ԭ�� //����
	ar<< di_chong; //�γ�  //����
	ar<< mei_jun; //ù��  //����
	ar<< xian_suo_xi_bao; //����ϸ�� //����
	ar<< qing_jie_du; //���� 
	/*��Ů����Ϣ-�ӹ����ѹ���Ӱ��*/
	ar<< zi_gong_xing_tai; //�ӹ���̬ -���
	ar<< zuo_ce_shu_luan_guan; //������ѹ� -���
	ar<< you_ce_shu_luan_guan; //�Ҳ����ѹ� -���
	/*��Ů����Ϣ-����B����*/
	ar<<fu_ke_Bchao_ri_qi;
	ar<< fu_ke_Bchao_zi_gong_da_xiao; //�ӹ���С -����
	ar<< fu_ke_Bchao_zi_gong_nei_mo; //�ӹ���Ĥ -���� 
	ar<< fu_ke_B_chao_zi_gong_lei_xing; //������ABC��
	ar<< fu_ke_B_chao_you_ce_luan_chao; //�Ҳ��ѳ� -���
	ar<< fu_ke_B_chao_you_ce_luan_chao_Fc; //�Ҳ��ѳ� -���
	ar<< fu_ke_B_chao_zuo_ce_luan_chao; //����ѳ� -���
	ar<< fu_ke_B_chao_zuo_ce_luan_chao_Fc; //����ѳ� -���
	/*��Ů����Ϣ-��ǻ����*/
	ar<< gong_qiang_jing; //��ǻ�� -���
	/*��Ů����Ϣ-����ǰ��Ȼ�������Ѽ�⡷*/

	ar<< nv_pai_luan_jian_ce_ri_qi1;
	ar<< yue_jing_zhou_qi1; //�¾����� //����
	ar<< luan_pao_zhi_jing1; //����ֱ�� //����
	ar<< zi_gong_nei_mo1; //�ӹ���Ĥ //����

	ar<< nv_pai_luan_jian_ce_ri_qi2;
	ar<< yue_jing_zhou_qi2; //�¾����� //����
	ar<< luan_pao_zhi_jing2; //����ֱ�� //����
	ar<< zi_gong_nei_mo2; //�ӹ���Ĥ //����

	ar<< nv_pai_luan_jian_ce_ri_qi3;
	ar<< yue_jing_zhou_qi3; //�¾����� //����
	ar<< luan_pao_zhi_jing3; //����ֱ�� //����
	ar<< zi_gong_nei_mo3; //�ӹ���Ĥ //����

	ar<< nv_pai_luan_jian_ce_ri_qi4;
	ar<< yue_jing_zhou_qi4; //�¾����� //����
	ar<< luan_pao_zhi_jing4; //����ֱ�� //����
	ar<< zi_gong_nei_mo4; //�ӹ���Ĥ //����
	/*��Ů����Ϣ-��ʷС�ᡷ*/
	ar<< bing_shi_xiao_jie; //��ʷС�� -���
	/*��Ů����Ϣ-��ϡ�*/
	//ar<< zhen_duan; //��� -���
	/*��Ů����Ϣ-���Ƽƻ���*/
	ar<< zheng_liao_ji_hua; //���Ƽƻ� -���
	/*��Ů����Ϣ-��*/
	ar<< nv_yi_shi; //ҽʦ -���

	/*��Ů����Ϣ-����ʷ��*/
	cs_shou_shu_shi.Serialize(ar);                  //����ʷ                *��|��  -��գ��У�
	/*��Ů����Ϣ-����ʷ��*/
	ci_xi_yan.Serialize(ar);//����           *��|��  -���֣��У�
	cs_yao_wu_guo_min.Serialize(ar);//ҩ�����ʷ   *��|��  -��գ��У�
	cs_jian_kang_zhuang_kuang .Serialize( ar );
	cs_chu_sheng_que_xian.Serialize(ar);//����ȱ��           *��|��  -��գ��У�

	/*��Ů����Ϣ-����ʷ��*/
	cs_yi_chuan_bing_shi.Serialize(ar);     //�Ŵ���ʷ      *��|��  -��գ�//������
	cs_bu_yun_bu_yu_shi.Serialize(ar);      //���в���ʷ    *��|��  -��գ�//������

	/*��Ů����Ϣ-����顷*/

	cs_ying_yang.Serialize(ar);             //Ӫ��          *����|�쳣      -��գ��쳣��
	cs_fa_yu.Serialize(ar);                 //����          *����|�쳣      -��գ��쳣��
	cs_jing_shen.Serialize(ar);             //����          *����|�쳣      -��գ��쳣��
	cs_mao_fa.Serialize(ar);                //ë��          *����|�쳣      -��գ��쳣��
	cs_pi_fu_nian_mo.Serialize(ar);         //Ƥ��ճĤ      *����|�쳣      -��գ��쳣��
	cs_lin_ba_jie.Serialize(ar);            //�ܰͽ�        *����|�쳣      -��գ��쳣��
	cs_ru_fang.Serialize(ar);               //�鷿          *����|�쳣      -��գ��쳣��
	cs_xin.Serialize(ar);                   //��            *����|�쳣      -��գ��쳣��
	cs_fei.Serialize(ar);                   //��            *����|�쳣      -��գ��쳣��
	cs_gan.Serialize(ar);                   //��            *����|�쳣      -��գ��쳣��
	cs_pi.Serialize(ar);                    //Ƣ            *����|�쳣      -��գ��쳣��
	cs_shen.Serialize(ar);                  //��            *����|�쳣      -��գ��쳣��
	cs_ji_zhu_si_zhi.Serialize(ar);         //������֫      *����|�쳣      -��գ��쳣��
	/*��Ů����Ϣ-���Ƽ�顷*/
	cs_wai_yin.Serialize(ar);               //����          *����|�쳣      -��գ��쳣��
	cs_yin_dao.Serialize(ar);               //����          *����|�쳣      -��գ��쳣��
	cs_gong_jing.Serialize(ar);             //����          *�⻬|����      *��|��|�أ����ã�
	cs_fu_ke_jian_cha_zi_gong_da_xiao.Serialize(ar);       //�ӹ���С              *����|�쳣      -��գ��쳣��
	cs_fu_jian_zuo.Serialize(ar);           //��������      *����|�쳣      -��գ��쳣��
	cs_fu_jian_you.Serialize(ar);           //�������ң�      *����|�쳣      -��գ��쳣��

	nv_date_luo_kuan.Serialize64( ar );
}
void CFemaleInfo::Serialize(CArchive& ar,int marjorVersion, int minjorVersion)
{
	if (ar.IsStoring())
	{
		Save2_1(ar);
	} 
	else
	{
		CString tmpstr ;

		/*��Ů����Ϣ����*/
		ar>> EN_name;				//����
		ar>> EN_age;				//����
		ar>> EN_occupation ;			//ְҵ
		ar>> EN_knowledge_degree ;	//�Ļ��̶�
		ar>> EN_nation ;				//����
		ar>> EN_identity_card ;		//���֤���� 
		ar>> EN_company ;			//��λ 
		ar>> EN_address ;			//ͨ�ŵ�ַ 
		ar>> EN_phone ;				//��ϵ�绰 
		ar>> EN_postalcode ;  //��������
		ar>> zhen_duan ;  //���	
		ar>> zhu_su ;				//���� 
		ar>> xian_bing_shi;			//�ֲ�ʷ

		/*��Ů����Ϣ-����ʷ��*/
		ar>>  ji_wang_gan_yan;  //���� *��|��
		ar>>  jie_he;  //��� *��|��
		ar>>  shen_zang_ji_bing;  //���༲�� *��|��
		ar>>  xin_xue_guan_ji_bing;  //��Ѫ�ܼ��� *��|��
		ar>>  mi_niao_xi_tong_gan_ran;  //����ϵ��Ⱦ *��|��
		ar>>  xing_chuan_bo_ji_bing_shi; //�Դ�������ʷ *��|��
		ar>>  lan_wei_yan;  //��β�� *��|��

		if(marjorVersion>=2 && minjorVersion>2){
			AfxMessageBox( pen_qiang_yan.strBase+_T("*")+pen_qiang_yan.strHasMore+_T("*")+pen_qiang_yan.strMore );
			pen_qiang_yan.Serialize(ar) ; //��ǻ�� *��|��
					AfxMessageBox( pen_qiang_yan.strBase+_T("*")+pen_qiang_yan.strHasMore+_T("*")+pen_qiang_yan.strMore );
		}else{
			AfxMessageBox( _T("/") );
			ar>>tmpstr;
			pen_qiang_yan.strBase = tmpstr; 
		}
		ar>>  ji_wang_qi_ta;  //����  -���

		/*��Ů����Ϣ-����ʷ��*/
		ar>>  xu_jiu;  //��� *��|��
		ar>>  xi_du;  //���� *��|��
		ar>>  zhong_da_jing_shen_ci_ji;  //�ش���̼�ʷ *��|��
		/*��Ů����Ϣ-�¾�ʷ��*/
		ar>>  chu_chao;  //���� -����
		ar>>  yue_jing_shi_yue_jing_zhou_qi1;  //�¾����� -���� -����
		ar>>  yue_jing_shi_yue_jing_zhou_qi2;  //�¾����� -���� -����
		ar>>  mo_ci_yue_jing;  //ĩ���¾� //����
		ar>>  jing_liang;  //���� *����|��|��
		ar>>  tong_jing;  //ʹ�� *��|��
		/*��Ů����Ϣ-����ʷ��*/
		ar>>  jin_qin_jie_hun;  //���׽�� *��|��
		ar>>  zai_hun;  //�ٻ� *��|��
		ar>>  ren_chen;  //���� *��|��
		ar>>  mo_ci_ren_shen;  //ĩ������ʱ�� �����¡�
		ar>>  yun;  //�� //����
		ar>>  chan;  //�� //����
		ar>>  ren_gong_liu_chan; //�˹����� -����
		ar>>  zi_ran_liu_chan; //��Ȼ���� -����
		ar>>  yao_liu; //ҩ�� -����
		ar>>  yin_chan; //���� -����
		ar>>  zao_chan; //��� -����
		ar>>  gong_wai_yuan_zuo; //�����У��� -����
		ar>>  gong_wai_yuan_you; //�����У��ң� -����
		ar>>  zu_yue_chan; //���²� -����
		ar>>  xian_you_zi_nv; //������Ů -����
		/*��Ů����Ϣ-����顷*/
		ar>>  yi_ban_qing_kuang_T; //һ�����T -����
		ar>>  yi_ban_qing_kuang_P; //һ�����P -����
		ar>>  yi_ban_qing_kuang_R; //һ�����R -����
		ar>>  yi_ban_qing_kuang_BP1; //һ�����BP -���� -����
		ar>>  yi_ban_qing_kuang_BP2;
		ar>>  shen_gao; //��� -����
		ar>>  ti_zhong; //���� -����
		ar>> yi_ru; //���� - ��|��
		/*��Ů����Ϣ-���Ƽ�顷*/
		ar>>  gong_jing_qi_ta; //�������� -���
		ar>>  zi_gong; //�ӹ� *ǰλ|��λ|ƽλ
		ar>>  zhi_di;  //�ʵ� *��|��|Ӳ
		ar>>  huo_dong_du; //��� *�|����|�̶�
		ar>>  ya_tong; //ѹʹ *��|��
		/*��Ů����Ϣ-.��*/
		ar>> xue_chang_gui; //Ѫ���� -���
		ar>> niao_chang_gui; //�򳣹� -���
		/*��Ů����Ϣ-Ѫ�͡�*/
		ar>> xue_xing; //Ѫ�� //����
		ar>> Rh_yin_zi; //Rh���� //����
		/*��Ů����Ϣ-�����ڷ��ڡ�*/
		ar>> EN_FSH;  //FSH -����
		ar>> EN_E_2;  //E���±�2�� -����
		ar>> EN_P;  //P -����
		ar>> EN_LH;  //LH -����
		ar>> EN_PRL;  //PRL -����
		ar>> EN_T;  //T -����
		/*��Ů����Ϣ-TORCH��*/
		ar>> gong_xing_chong;  //���γ� //����
		ar>> ju_xi_bao_bing_du;  //��ϸ������ //����
		ar>> feng_zhen_bing_du;  //����� //����
		ar>> dan_chun_pao_zhen_bing_du_II_xing; //���������II�� //����
		/*��Ů����Ϣ-���� HIV��*/
		ar>> EN_HBSAG;
		ar>> EN_HBSAB;
		ar>>  EN_HBEAG;

		ar>> EN_HBEAB;
		ar>> EN_HBCAB;
		ar>> EN_HAVI;

		ar>> EN_HCVAb; //HCVAb //����
		ar>> EN_HCVAg; //HCV-Ag //����
		ar>> EN_HIVAb; //HIVAb //����
		/*��Ů����Ϣ-�����Ŀ��塷*/
		ar>> kang_zi_gong_nei_mo_kang_ti; //���ӹ���Ĥ����//����
		ar>> kang_luan_chao_kang_ti; //���ѳ����� //����
		ar>> kang_tou_ming_dai_kang_ti; //��͸�������� //����
		ar>> kang_jing_zi_kang_ti; //�����ӿ��� //����
		/*��Ů����Ϣ-.��*/
		ar>> gan_gong;//�ι� //����
		ar>> shen_gong;//���� //����
		ar>> ran_se_ti;//Ⱦɫ�� //����
		/*��Ů����Ϣ-������Ƭ��*/
		ar>> gong_jing_gua_pian;		//������Ƭ -���
		/*��Ů����Ϣ-����ͿƬ��*/
		ar>> zhi_yuan_ti; //֧ԭ�� //����
		ar>> yi_yuan_ti; //��ԭ�� //����
		ar>> di_chong; //�γ�  //����
		ar>> mei_jun; //ù��  //����
		ar>> xian_suo_xi_bao; //����ϸ�� //����
		ar>> qing_jie_du; //���� 
		/*��Ů����Ϣ-�ӹ����ѹ���Ӱ��*/
		ar>> zi_gong_xing_tai; //�ӹ���̬ -���
		ar>> zuo_ce_shu_luan_guan; //������ѹ� -���
		ar>> you_ce_shu_luan_guan; //�Ҳ����ѹ� -���
		/*��Ů����Ϣ-����B����*/
		ar >> fu_ke_Bchao_ri_qi;
		ar>> fu_ke_Bchao_zi_gong_da_xiao; //�ӹ���С -����
		ar>> fu_ke_Bchao_zi_gong_nei_mo; //�ӹ���Ĥ -����
		ar>> fu_ke_B_chao_zi_gong_lei_xing; //������ABC��
		ar>> fu_ke_B_chao_you_ce_luan_chao; //�Ҳ��ѳ� -���
		ar>> fu_ke_B_chao_you_ce_luan_chao_Fc; //�Ҳ��ѳ� -���
		ar>> fu_ke_B_chao_zuo_ce_luan_chao; //����ѳ� -���
		ar>> fu_ke_B_chao_zuo_ce_luan_chao_Fc; //����ѳ� -���
		/*��Ů����Ϣ-��ǻ����*/
		ar>> gong_qiang_jing; //��ǻ�� -���
		/*��Ů����Ϣ- ����ǰ��Ȼ�������Ѽ�⡷*/

		ar>> nv_pai_luan_jian_ce_ri_qi1;
		ar>> yue_jing_zhou_qi1; //�¾����� //����
		ar>> luan_pao_zhi_jing1; //����ֱ�� //����
		ar>> zi_gong_nei_mo1; //�ӹ���Ĥ //����

		ar>> nv_pai_luan_jian_ce_ri_qi2;
		ar>> yue_jing_zhou_qi2; //�¾����� //����
		ar>> luan_pao_zhi_jing2; //����ֱ�� //����
		ar>> zi_gong_nei_mo2; //�ӹ���Ĥ //����

		ar>> nv_pai_luan_jian_ce_ri_qi3;
		ar>> yue_jing_zhou_qi3; //�¾����� //����
		ar>> luan_pao_zhi_jing3; //����ֱ�� //����
		ar>> zi_gong_nei_mo3; //�ӹ���Ĥ //����

		ar>> nv_pai_luan_jian_ce_ri_qi4;
		ar>> yue_jing_zhou_qi4; //�¾����� //����
		ar>> luan_pao_zhi_jing4; //����ֱ�� //����
		ar>> zi_gong_nei_mo4; //�ӹ���Ĥ //����

		/*��Ů����Ϣ-��ʷС�ᡷ*/
		ar>> bing_shi_xiao_jie; //��ʷС�� -���
		/*��Ů����Ϣ-��ϡ�*/
		//ar>> zhen_duan; //��� -���
		/*��Ů����Ϣ-���Ƽƻ���*/
		ar>> zheng_liao_ji_hua; //���Ƽƻ� -���
		/*��Ů����Ϣ-��*/
		ar>> nv_yi_shi; //ҽʦ -���
		/*��Ů����Ϣ-����ʷ��*/
		cs_shou_shu_shi.Serialize(ar);                  //����ʷ                *��|��  -��գ��У�
		/*��Ů����Ϣ-����ʷ��*/
		ci_xi_yan.Serialize(ar);//����           *��|��  -���֣��У�
		cs_yao_wu_guo_min.Serialize(ar);//ҩ�����ʷ   *��|��  -��գ��У�
		cs_jian_kang_zhuang_kuang .Serialize( ar );
		cs_chu_sheng_que_xian.Serialize(ar);//����ȱ��           *��|��  -��գ��У�

		/*��Ů����Ϣ-����ʷ��*/
		cs_yi_chuan_bing_shi.Serialize(ar);     //�Ŵ���ʷ      *��|��  -��գ�//������
		cs_bu_yun_bu_yu_shi.Serialize(ar);      //���в���ʷ    *��|��  -��գ�//������

		/*��Ů����Ϣ-����顷*/

		cs_ying_yang.Serialize(ar);             //Ӫ��          *����|�쳣      -��գ��쳣��
		cs_fa_yu.Serialize(ar);                 //����          *����|�쳣      -��գ��쳣��
		cs_jing_shen.Serialize(ar);             //����          *����|�쳣      -��գ��쳣��
		cs_mao_fa.Serialize(ar);                //ë��          *����|�쳣      -��գ��쳣��
		cs_pi_fu_nian_mo.Serialize(ar);         //Ƥ��ճĤ      *����|�쳣      -��գ��쳣��
		cs_lin_ba_jie.Serialize(ar);            //�ܰͽ�        *����|�쳣      -��գ��쳣��
		cs_ru_fang.Serialize(ar);               //�鷿          *����|�쳣      -��գ��쳣��
		cs_xin.Serialize(ar);                   //��            *����|�쳣      -��գ��쳣��
		cs_fei.Serialize(ar);                   //��            *����|�쳣      -��գ��쳣��
		cs_gan.Serialize(ar);                   //��            *����|�쳣      -��գ��쳣��
		cs_pi.Serialize(ar);                    //Ƣ            *����|�쳣      -��գ��쳣��
		cs_shen.Serialize(ar);                  //��            *����|�쳣      -��գ��쳣��
		cs_ji_zhu_si_zhi.Serialize(ar);         //������֫      *����|�쳣      -��գ��쳣��
		/*��Ů����Ϣ-���Ƽ�顷*/
		cs_wai_yin.Serialize(ar);               //����          *����|�쳣      -��գ��쳣��
		cs_yin_dao.Serialize(ar);               //����          *����|�쳣      -��գ��쳣��
		cs_gong_jing.Serialize(ar);             //����          *�⻬|����      *��|��|�أ����ã�
		cs_fu_ke_jian_cha_zi_gong_da_xiao.Serialize(ar);       //�ӹ���С              *����|�쳣      -��գ��쳣��
		cs_fu_jian_zuo.Serialize(ar);           //��������      *����|�쳣      -��գ��쳣��
		cs_fu_jian_you.Serialize(ar);           //�������ң�      *����|�쳣      -��գ��쳣��

		nv_date_luo_kuan.Serialize64( ar );
	}
}


void CFemaleInfo::operator=(const CFemaleInfo& fi)
{
	/*��Ů����Ϣ����*/
	EN_name=fi.EN_name;				//����
	EN_age=fi.EN_age;				//����
	EN_occupation =fi.EN_occupation ;			//ְҵ
	EN_knowledge_degree =fi.EN_knowledge_degree ;	//�Ļ��̶�
	EN_nation =fi.EN_nation ;				//����
	EN_identity_card =fi.EN_identity_card ;		//���֤���� 
	EN_company =fi.EN_company ;			//��λ 
	EN_address =fi.EN_address ;			//ͨ�ŵ�ַ 
	EN_phone =fi.EN_phone ;				//��ϵ�绰 
	EN_postalcode =fi.EN_postalcode ;  //��������
	zhen_duan =fi.zhen_duan ;  //���	
	zhu_su =fi.zhu_su ;				//���� 
	xian_bing_shi=fi.xian_bing_shi;			//�ֲ�ʷ


	/*��Ů����Ϣ-����ʷ��*/
	ji_wang_gan_yan=fi.ji_wang_gan_yan;  //���� *��|��
	jie_he=fi.jie_he;  //��� *��|��
	shen_zang_ji_bing=fi.shen_zang_ji_bing;  //���༲�� *��|��
	xin_xue_guan_ji_bing=fi.xin_xue_guan_ji_bing;  //��Ѫ�ܼ��� *��|��
	mi_niao_xi_tong_gan_ran=fi.mi_niao_xi_tong_gan_ran;  //����ϵ��Ⱦ *��|��
	xing_chuan_bo_ji_bing_shi=fi.xing_chuan_bo_ji_bing_shi; //�Դ�������ʷ *��|��
	lan_wei_yan=fi.lan_wei_yan;  //��β�� *��|��
	pen_qiang_yan=fi.pen_qiang_yan;  //��ǻ�� *��|��
	
	ji_wang_qi_ta=fi.ji_wang_qi_ta;  //����  -���
	/*��Ů����Ϣ-����ʷ��*/
	xu_jiu=fi.xu_jiu;  //��� *��|��
	xi_du=fi.xi_du;  //���� *��|��
	zhong_da_jing_shen_ci_ji=fi.zhong_da_jing_shen_ci_ji;  //�ش���̼�ʷ *��|��
	/*��Ů����Ϣ-�¾�ʷ��*/
	chu_chao=fi.chu_chao;  //���� -����
	yue_jing_shi_yue_jing_zhou_qi1=fi.yue_jing_shi_yue_jing_zhou_qi1;  //�¾����� -���� -����
	yue_jing_shi_yue_jing_zhou_qi2=fi.yue_jing_shi_yue_jing_zhou_qi2;  //�¾����� -���� -����
	mo_ci_yue_jing=fi.mo_ci_yue_jing;  //ĩ���¾� //����
	jing_liang=fi.jing_liang;  //���� *����|��|��
	tong_jing=fi.tong_jing;  //ʹ�� *��|��
	/*��Ů����Ϣ-����ʷ��*/
	jin_qin_jie_hun=fi.jin_qin_jie_hun;  //���׽�� *��|��
	zai_hun=fi.zai_hun;  //�ٻ� *��|��
	ren_chen=fi.ren_chen;  //���� *��|��
	mo_ci_ren_shen=fi.mo_ci_ren_shen;  //ĩ������ʱ�� �����¡�
	yun=fi.yun;  //�� //����
	chan=fi.chan;  //�� //����
	ren_gong_liu_chan=fi.ren_gong_liu_chan; //�˹����� -����
	zi_ran_liu_chan=fi.zi_ran_liu_chan; //��Ȼ���� -����
	yao_liu=fi.yao_liu; //ҩ�� -����
	yin_chan=fi.yin_chan; //���� -����
	zao_chan=fi.zao_chan; //��� -����
	gong_wai_yuan_zuo=fi.gong_wai_yuan_zuo; //�����У��� -����
	gong_wai_yuan_you=fi.gong_wai_yuan_you; //�����У��ң� -����
	zu_yue_chan=fi.zu_yue_chan; //���²� -����
	xian_you_zi_nv=fi.xian_you_zi_nv; //������Ů -����
	/*��Ů����Ϣ-����顷*/
	yi_ban_qing_kuang_T=fi.yi_ban_qing_kuang_T; //һ�����T -����
	yi_ban_qing_kuang_P=fi.yi_ban_qing_kuang_P; //һ�����P -����
	yi_ban_qing_kuang_R=fi.yi_ban_qing_kuang_R; //һ�����R -����
	yi_ban_qing_kuang_BP1=fi.yi_ban_qing_kuang_BP1; //һ�����BP -���� -����
    yi_ban_qing_kuang_BP2=fi.yi_ban_qing_kuang_BP2;
	shen_gao=fi.shen_gao; //��� -����
	ti_zhong=fi.ti_zhong; //���� -����
	/*��Ů����Ϣ-���Ƽ�顷*/
	gong_jing_qi_ta=fi.gong_jing_qi_ta; //�������� -���
	zi_gong=fi.zi_gong; //�ӹ� *ǰλ|��λ|ƽλ
	zhi_di=fi.zhi_di;  //�ʵ� *��|��|Ӳ
	huo_dong_du=fi.huo_dong_du; //��� *�|����|�̶�
	ya_tong=fi.ya_tong; //ѹʹ *��|��
	//qi_ta=fi.qi_ta;  //���� -���
	/*��Ů����Ϣ-.��*/
	xue_chang_gui=fi.xue_chang_gui; //Ѫ���� -���
	niao_chang_gui=fi.niao_chang_gui; //�򳣹� -���
	/*��Ů����Ϣ-Ѫ�͡�*/
	xue_xing=fi.xue_xing; //Ѫ�� //����
	Rh_yin_zi=fi.Rh_yin_zi; //Rh���� //����
	/*��Ů����Ϣ-�����ڷ��ڡ�*/
	EN_FSH=fi.EN_FSH;  //FSH -����
	EN_E_2=fi.EN_E_2;  //E���±�2�� -����
	EN_P=fi.EN_P;  //P -����
	EN_LH=fi.EN_LH;  //LH -����
	EN_PRL=fi.EN_PRL;  //PRL -����
	EN_T=fi.EN_T;  //T -����
	/*��Ů����Ϣ-TORCH��*/
	gong_xing_chong=fi.gong_xing_chong;  //���γ� //����
	ju_xi_bao_bing_du=fi.ju_xi_bao_bing_du;  //��ϸ������ //����
	feng_zhen_bing_du=fi.feng_zhen_bing_du;  //����� //����
	dan_chun_pao_zhen_bing_du_II_xing=fi.dan_chun_pao_zhen_bing_du_II_xing; //���������II�� //����
	/*��Ů����Ϣ-���� HIV��*/
    EN_HBSAG=fi.EN_HBSAG ;
    EN_HBSAB=fi.EN_HBSAB ;
     EN_HBEAG=fi. EN_HBEAG;

    EN_HBEAB=fi. EN_HBEAB;
    EN_HBCAB=fi.EN_HBCAB;
    EN_HAVI=fi. EN_HAVI;
	
    EN_HCVAb=fi.EN_HCVAb; //HCVAb //����
	EN_HCVAg=fi.EN_HCVAg; //HCV-Ag //����
	EN_HIVAb=fi.EN_HIVAb; //HIVAb //����
	/*��Ů����Ϣ-�����Ŀ��塷*/
	kang_zi_gong_nei_mo_kang_ti=fi.kang_zi_gong_nei_mo_kang_ti; //���ӹ���Ĥ����//����
	kang_luan_chao_kang_ti=fi.kang_luan_chao_kang_ti; //���ѳ����� //����
	kang_tou_ming_dai_kang_ti=fi.kang_tou_ming_dai_kang_ti; //��͸�������� //����
	kang_jing_zi_kang_ti=fi.kang_jing_zi_kang_ti; //�����ӿ��� //����
	/*��Ů����Ϣ-.��*/
	gan_gong=fi.gan_gong;//�ι� //����
	shen_gong=fi.shen_gong;//���� //����
	ran_se_ti=fi.ran_se_ti;//Ⱦɫ�� //����
	/*��Ů����Ϣ-������Ƭ��*/
	gong_jing_gua_pian=fi.gong_jing_gua_pian;		//������Ƭ -���
	/*��Ů����Ϣ-����ͿƬ��*/
	zhi_yuan_ti=fi.zhi_yuan_ti; //֧ԭ�� //����
	yi_yuan_ti=fi.yi_yuan_ti; //��ԭ�� //����
	di_chong=fi.di_chong; //�γ�  //����
	mei_jun=fi.mei_jun; //ù��  //����
	xian_suo_xi_bao=fi.xian_suo_xi_bao; //����ϸ�� //����
	qing_jie_du=fi.qing_jie_du; //���� 
	/*��Ů����Ϣ-�ӹ����ѹ���Ӱ��*/
	zi_gong_xing_tai=fi.zi_gong_xing_tai; //�ӹ���̬ -���
	zuo_ce_shu_luan_guan=fi.zuo_ce_shu_luan_guan; //������ѹ� -���
	you_ce_shu_luan_guan=fi.you_ce_shu_luan_guan; //�Ҳ����ѹ� -���
	/*��Ů����Ϣ-����B����*/
	fu_ke_Bchao_ri_qi  = fi.fu_ke_Bchao_ri_qi;
	fu_ke_Bchao_zi_gong_da_xiao=fi.fu_ke_Bchao_zi_gong_da_xiao; //�ӹ���С -����
	fu_ke_Bchao_zi_gong_nei_mo=fi.fu_ke_Bchao_zi_gong_nei_mo; //�ӹ���Ĥ -���� 
    fu_ke_B_chao_zi_gong_lei_xing=fi.fu_ke_B_chao_zi_gong_lei_xing;//������ABC��
	fu_ke_B_chao_you_ce_luan_chao=fi.fu_ke_B_chao_you_ce_luan_chao; //�Ҳ��ѳ� -���
	fu_ke_B_chao_zuo_ce_luan_chao=fi.fu_ke_B_chao_zuo_ce_luan_chao; //����ѳ� -���
	fu_ke_B_chao_you_ce_luan_chao_Fc=fi.fu_ke_B_chao_you_ce_luan_chao_Fc; //�Ҳ��ѳ� -���
	fu_ke_B_chao_zuo_ce_luan_chao_Fc=fi.fu_ke_B_chao_zuo_ce_luan_chao_Fc; //����ѳ� -���
	/*��Ů����Ϣ-��ǻ����*/
	gong_qiang_jing=fi.gong_qiang_jing; //��ǻ�� -���
	//?????????????///?????????????//���� ������ǰ��Ȼ�������Ѽ�⣺��
	/*��Ů����Ϣ-���Ѽ�⡷*/

    nv_pai_luan_jian_ce_ri_qi1 = fi.nv_pai_luan_jian_ce_ri_qi1;
    nv_pai_luan_jian_ce_ri_qi2 = fi.nv_pai_luan_jian_ce_ri_qi2;
    nv_pai_luan_jian_ce_ri_qi3 = fi.nv_pai_luan_jian_ce_ri_qi3;
    nv_pai_luan_jian_ce_ri_qi4 = fi.nv_pai_luan_jian_ce_ri_qi4;
	yue_jing_zhou_qi1=fi.yue_jing_zhou_qi1; //�¾����� //����
	luan_pao_zhi_jing1=fi.luan_pao_zhi_jing1; //����ֱ�� //����
	zi_gong_nei_mo1=fi.zi_gong_nei_mo1; //�ӹ���Ĥ //����


    yue_jing_zhou_qi2=fi.yue_jing_zhou_qi2; //�¾����� //����
    luan_pao_zhi_jing2=fi.luan_pao_zhi_jing2; //����ֱ�� //����
    zi_gong_nei_mo2=fi.zi_gong_nei_mo2; //�ӹ���Ĥ //����


    yue_jing_zhou_qi3=fi.yue_jing_zhou_qi3; //�¾����� //����
    luan_pao_zhi_jing3=fi.luan_pao_zhi_jing3; //����ֱ�� //����
    zi_gong_nei_mo3=fi.zi_gong_nei_mo3; //�ӹ���Ĥ //����


    yue_jing_zhou_qi4=fi.yue_jing_zhou_qi4; //�¾����� //����
    luan_pao_zhi_jing4=fi.luan_pao_zhi_jing4; //����ֱ�� //����
    zi_gong_nei_mo4=fi.zi_gong_nei_mo4; //�ӹ���Ĥ //����
	/*��Ů����Ϣ-��ʷС�ᡷ*/
	bing_shi_xiao_jie=fi.bing_shi_xiao_jie; //��ʷС�� -���
	/*��Ů����Ϣ-��ϡ�*/
	// =fi.// zhen_duan; //��� -���
	/*��Ů����Ϣ-���Ƽƻ���*/
	zheng_liao_ji_hua=fi.zheng_liao_ji_hua; //���Ƽƻ� -���
	/*��Ů����Ϣ-��*/
	nv_yi_shi=fi.nv_yi_shi; //ҽʦ -���

	
	/*��Ů����Ϣ-����ʷ��*/
	cs_shou_shu_shi=fi.cs_shou_shu_shi;                  //����ʷ                *��|��  -��գ��У�
	/*��Ů����Ϣ-����ʷ��*/
	ci_xi_yan=fi.ci_xi_yan;//����           *��|��  -���֣��У�
	cs_yao_wu_guo_min=fi.cs_yao_wu_guo_min;//ҩ�����ʷ   *��|��  -��գ��У�
	cs_jian_kang_zhuang_kuang = fi.cs_jian_kang_zhuang_kuang; //����״����������
	cs_chu_sheng_que_xian=fi.cs_chu_sheng_que_xian;//����ȱ��           *��|��  -��գ��У�
	/*��Ů����Ϣ-����ʷ��*/
	cs_yi_chuan_bing_shi=fi.cs_yi_chuan_bing_shi;     //�Ŵ���ʷ      *��|��  -��գ�//������
	cs_bu_yun_bu_yu_shi=fi.cs_bu_yun_bu_yu_shi;      //���в���ʷ    *��|��  -��գ�//������
	/*��Ů����Ϣ-����顷*/
	cs_ying_yang=fi.cs_ying_yang;             //Ӫ��          *����|�쳣      -��գ��쳣��
	cs_fa_yu=fi.cs_fa_yu;                 //����          *����|�쳣      -��գ��쳣��
	cs_jing_shen=fi.cs_jing_shen;             //����          *����|�쳣      -��գ��쳣��
	cs_mao_fa=fi.cs_mao_fa;                //ë��          *����|�쳣      -��գ��쳣��
	cs_pi_fu_nian_mo=fi.cs_pi_fu_nian_mo;         //Ƥ��ճĤ      *����|�쳣      -��գ��쳣��
	cs_lin_ba_jie=fi.cs_lin_ba_jie;            //�ܰͽ�        *����|�쳣      -��գ��쳣��
	cs_ru_fang=fi.cs_ru_fang;               //�鷿          *����|�쳣      -��գ��쳣��
	yi_ru=fi.yi_ru;                 //����          *����|�쳣      -��գ��쳣��
	cs_xin=fi.cs_xin;                   //��            *����|�쳣      -��գ��쳣��
	cs_fei=fi.cs_fei;                   //��            *����|�쳣      -��գ��쳣��
	cs_gan=fi.cs_gan;                   //��            *����|�쳣      -��գ��쳣��
	cs_pi=fi.cs_pi;                    //Ƣ            *����|�쳣      -��գ��쳣��
	cs_shen=fi.cs_shen;                  //��            *����|�쳣      -��գ��쳣��
	cs_ji_zhu_si_zhi=fi.cs_ji_zhu_si_zhi;         //������֫      *����|�쳣      -��գ��쳣��
	/*��Ů����Ϣ-���Ƽ�顷*/
	cs_wai_yin=fi.cs_wai_yin;               //����          *����|�쳣      -��գ��쳣��
	cs_yin_dao=fi.cs_yin_dao;               //����          *����|�쳣      -��գ��쳣��
	cs_gong_jing=fi.cs_gong_jing;             //����          *�⻬|����      *��|��|�أ����ã�
	cs_fu_ke_jian_cha_zi_gong_da_xiao=fi.cs_fu_ke_jian_cha_zi_gong_da_xiao;       //�ӹ���С              *����|�쳣      -��գ��쳣��
	cs_fu_jian_zuo=fi.cs_fu_jian_zuo;           //��������      *����|�쳣      -��գ��쳣��
	cs_fu_jian_you=fi.cs_fu_jian_you;           //�������ң�      *����|�쳣      -��գ��쳣��
    nv_date_luo_kuan = fi.nv_date_luo_kuan; //���ʱ��
}
// CFemaleInfo ��Ա����


