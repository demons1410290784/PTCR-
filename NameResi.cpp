/*
**	FILENAME			NameResi.h
**
**	PURPOSE				此类可用于设置通道号启用、样品名称和室温阻值。
**						此外可以选择相应的温度、阻值进行读取，并进行通
**						道校零
*/

#include "stdafx.h"
#include "ptcr.h"
#include "NameResi.h"
//#include "ptcrdoc.h"
#include "ptcrview.h"

extern int NameResi0; 
int chan;
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNameResi对话框

//
//	构造函数：初始化并打开对话框
//
CNameResi::CNameResi(CPtcrDoc *pDoc,CWnd* pParent /*=NULL*/)
	: CDialog(CNameResi::IDD, pParent)
{
		m_pDoc=pDoc;
//{{AFX_DATA_INIT(CNameResi)

	m_Name1 = _T("PTC01");
	m_Name10 = _T("PTC10");
	m_Name11 = _T("PTC11");
	m_Name12 = _T("PTC12");
	m_Name13 = _T("PTC13");
	m_Name14 = _T("PTC14");
	m_Name15 = _T("PTC15");
	m_Name16 = _T("PTC16");
	m_Name17 = _T("PTC17");
	m_Name18 = _T("PTC18");
	m_Name19 = _T("PTC19");
	m_Name2 = _T("PTC02");
	m_Name20 = _T("PTC20");
	m_Name21 = _T("PTC21");
	m_Name22 = _T("PTC22");
	m_Name23 = _T("PTC23");
	m_Name24 = _T("PTC24");
	m_Name25 = _T("PTC25");
	m_Name26 = _T("PTC26");
	m_Name27 = _T("PTC27");
	m_Name28 = _T("PTC28");
	m_Name29 = _T("PTC29");
	m_Name3 = _T("PTC03");
	m_Name30 = _T("PTC30");
	m_Name4 = _T("PTC04");
	m_Name5 = _T("PTC05");
	m_Name6 = _T("PTC06");
	m_Name7 = _T("PTC07");
	m_Name8 = _T("PTC08");
	m_Name9 = _T("PTC09");
	m_Resi10 = _T("");
	m_Resi1 = _T("");
	m_Resi11 = _T("");
	m_Resi12 = _T("");
	m_Resi13 = _T("");
	m_Resi14 = _T("");
	m_Resi15 = _T("");
	m_Resi16 = _T("");
	m_Resi17 = _T("");
	m_Resi18 = _T("");
	m_Resi19 = _T("");
	m_Resi2 = _T("");
	m_Resi20 = _T("");
	m_Resi21 = _T("");
	m_Resi22 = _T("");
	m_Resi23 = _T("");
	m_Resi24 = _T("");
	m_Resi25 = _T("");
	m_Resi26 = _T("");
	m_Resi27 = _T("");
	m_Resi28 = _T("");
	m_Resi29 = _T("");
	m_Resi3 = _T("");
	m_Resi30 = _T("");
	m_Resi4 = _T("");
	m_Resi5 = _T("");
	m_Resi6 = _T("");
	m_Resi7 = _T("");
	m_Resi8 = _T("");
	m_Resi9 = _T("");
	m_ChanNo = 0;
	m_Resi = _T("");
    m_CheckZero=TRUE;
	m_Pt100_1 = _T("");
	m_Pt100_2 = _T("");
	//}}AFX_DATA_INIT

if(NameResi0==0)
{
    m_Ch1 = FALSE;
	m_Ch10 = FALSE;
	m_Ch11 = FALSE;
	m_Ch12 = FALSE;
	m_Ch13 = FALSE;
	m_Ch14 = FALSE;
	m_Ch15 = FALSE;
	m_Ch16 = FALSE;
	m_Ch17 = FALSE;
	m_Ch18 = FALSE;
	m_Ch19 = FALSE;
	m_Ch2 = FALSE;
	m_Ch20 = FALSE;
	m_Ch21 = FALSE;
	m_Ch22 = FALSE;
	m_Ch23 = FALSE;
	m_Ch24 = FALSE;
	m_Ch25 = FALSE;
	m_Ch26 = FALSE;
	m_Ch27 = FALSE;
	m_Ch28 = FALSE;
	m_Ch29 = FALSE;
	m_Ch3 = FALSE;
	m_Ch30 = FALSE;
	m_Ch4 = FALSE;
	m_Ch5 = FALSE;
	m_Ch6 = FALSE;
	m_Ch7 = FALSE;
	m_Ch8 = FALSE;
	m_Ch9 = FALSE;
	switch(m_pDoc->m_rt.m_Number){
	case 30 :
		m_Ch30 = TRUE;
	case 29 :
		m_Ch29 = TRUE;
	case 28 :
		m_Ch28 = TRUE;
	case 27 :
		m_Ch27 = TRUE;
	case 26 :
		m_Ch26 = TRUE;
	case 25 :
		m_Ch25 = TRUE;
	case 24 :
		m_Ch24 = TRUE;
	case 23 :
		m_Ch23 = TRUE;
	case 22 :
		m_Ch22 = TRUE;
	case 21 :
		m_Ch21 = TRUE;
	case 20 :
		m_Ch20 = TRUE;
	case 19 :
		m_Ch19 = TRUE;
	case 18 :
		m_Ch18 = TRUE;
	case 17 :
		m_Ch17 = TRUE;
	case 16 :
		m_Ch16 = TRUE;
	case 15 :
		m_Ch15 = TRUE;
	case 14 :
		m_Ch14 = TRUE;
	case 13 :
		m_Ch13 = TRUE;
	case 12 :
		m_Ch12 = TRUE;
	case 11 :
		m_Ch11 = TRUE;
	case 10 :
		m_Ch10 = TRUE;
	case 9 :
		m_Ch9 = TRUE;
	case 8 :
		m_Ch8 = TRUE;
	case 7 :
		m_Ch7 = TRUE;
	case 6 :
		m_Ch6 = TRUE;
	case 5 :
		m_Ch5 = TRUE;
	case 4 :
		m_Ch4 = TRUE;
	case 3 :
		m_Ch3 = TRUE;
	case 2 :
		m_Ch2 = TRUE;
	case 1 :
		m_Ch1 = TRUE;
		break;

	}
}

if(NameResi0==1){
   	m_Ch1 =m_pDoc->m_rt.m_rtSave.m_bChannels[0];
	m_Ch10 =m_pDoc->m_rt.m_rtSave.m_bChannels[9];
	m_Ch11 =m_pDoc->m_rt.m_rtSave.m_bChannels[10];
	m_Ch12 =m_pDoc->m_rt.m_rtSave.m_bChannels[11];
	m_Ch13 =m_pDoc->m_rt.m_rtSave.m_bChannels[12];
	m_Ch14 =m_pDoc->m_rt.m_rtSave.m_bChannels[13];
	m_Ch15 =m_pDoc->m_rt.m_rtSave.m_bChannels[14];
	m_Ch16 =m_pDoc->m_rt.m_rtSave.m_bChannels[15];
	m_Ch17 =m_pDoc->m_rt.m_rtSave.m_bChannels[16];
	m_Ch18 =m_pDoc->m_rt.m_rtSave.m_bChannels[17];
	m_Ch19 =m_pDoc->m_rt.m_rtSave.m_bChannels[18];
	m_Ch2 =m_pDoc->m_rt.m_rtSave.m_bChannels[1];
	m_Ch20 =m_pDoc->m_rt.m_rtSave.m_bChannels[19];
	m_Ch21 =m_pDoc->m_rt.m_rtSave.m_bChannels[20];
	m_Ch22 =m_pDoc->m_rt.m_rtSave.m_bChannels[21];
	m_Ch23 =m_pDoc->m_rt.m_rtSave.m_bChannels[22];
	m_Ch24 =m_pDoc->m_rt.m_rtSave.m_bChannels[23];
	m_Ch25 =m_pDoc->m_rt.m_rtSave.m_bChannels[24];
	m_Ch26 =m_pDoc->m_rt.m_rtSave.m_bChannels[25];
	m_Ch27 =m_pDoc->m_rt.m_rtSave.m_bChannels[26];
	m_Ch28 =m_pDoc->m_rt.m_rtSave.m_bChannels[27];
	m_Ch29 =m_pDoc->m_rt.m_rtSave.m_bChannels[28];
	m_Ch3 =m_pDoc->m_rt.m_rtSave.m_bChannels[2];
	m_Ch30 =m_pDoc->m_rt.m_rtSave.m_bChannels[29];
	m_Ch4 =m_pDoc->m_rt.m_rtSave.m_bChannels[3];
	m_Ch5 =m_pDoc->m_rt.m_rtSave.m_bChannels[4];
	m_Ch6 =m_pDoc->m_rt.m_rtSave.m_bChannels[5];
	m_Ch7 =m_pDoc->m_rt.m_rtSave.m_bChannels[6];
	m_Ch8 =m_pDoc->m_rt.m_rtSave.m_bChannels[7];
	m_Ch9 =m_pDoc->m_rt.m_rtSave.m_bChannels[8];
	
	m_Name1 = m_pDoc->m_rt.m_rtSave.m_sChannelsName[0];
	m_Name2=m_pDoc->m_rt.m_rtSave.m_sChannelsName[1];
	m_Name3=m_pDoc->m_rt.m_rtSave.m_sChannelsName[2];
	m_Name4=m_pDoc->m_rt.m_rtSave.m_sChannelsName[3];
	m_Name5=m_pDoc->m_rt.m_rtSave.m_sChannelsName[4];
	m_Name6=m_pDoc->m_rt.m_rtSave.m_sChannelsName[5];
	m_Name7=m_pDoc->m_rt.m_rtSave.m_sChannelsName[6];
	m_Name8=m_pDoc->m_rt.m_rtSave.m_sChannelsName[7];
	m_Name9=m_pDoc->m_rt.m_rtSave.m_sChannelsName[8];
	m_Name10=m_pDoc->m_rt.m_rtSave.m_sChannelsName[9];
	m_Name11=m_pDoc->m_rt.m_rtSave.m_sChannelsName[10];
	m_Name12=m_pDoc->m_rt.m_rtSave.m_sChannelsName[11];
	m_Name13=m_pDoc->m_rt.m_rtSave.m_sChannelsName[12];
	m_Name14=m_pDoc->m_rt.m_rtSave.m_sChannelsName[13];
	m_Name15=m_pDoc->m_rt.m_rtSave.m_sChannelsName[14];
	m_Name16=m_pDoc->m_rt.m_rtSave.m_sChannelsName[15];
	m_Name17=m_pDoc->m_rt.m_rtSave.m_sChannelsName[16];
	m_Name18=m_pDoc->m_rt.m_rtSave.m_sChannelsName[17];
	m_Name19=m_pDoc->m_rt.m_rtSave.m_sChannelsName[18];
    m_Name20=m_pDoc->m_rt.m_rtSave.m_sChannelsName[19];
	m_Name21=m_pDoc->m_rt.m_rtSave.m_sChannelsName[20];
    m_Name22=m_pDoc->m_rt.m_rtSave.m_sChannelsName[21];
	m_Name23=m_pDoc->m_rt.m_rtSave.m_sChannelsName[22];
	m_Name24=m_pDoc->m_rt.m_rtSave.m_sChannelsName[23];
	m_Name25=m_pDoc->m_rt.m_rtSave.m_sChannelsName[24];
	m_Name26=m_pDoc->m_rt.m_rtSave.m_sChannelsName[25];
	m_Name27=m_pDoc->m_rt.m_rtSave.m_sChannelsName[26];
	m_Name28=m_pDoc->m_rt.m_rtSave.m_sChannelsName[27];
	m_Name29=m_pDoc->m_rt.m_rtSave.m_sChannelsName[28];
	m_Name30=m_pDoc->m_rt.m_rtSave.m_sChannelsName[29];

	if(m_Ch1==TRUE)m_Resi1=ResiFormat(0);
	else m_Resi1=_T("");
	if(m_Ch2==TRUE)m_Resi2=ResiFormat(1);
	else m_Resi2=_T("");
	if(m_Ch3==TRUE)m_Resi3=ResiFormat(2);
	else m_Resi3=_T("");
	if(m_Ch4==TRUE)m_Resi4=ResiFormat(3);
	else m_Resi4=_T("");
	if(m_Ch5==TRUE)m_Resi5=ResiFormat(4);
	else m_Resi5=_T("");
	if(m_Ch6==TRUE)m_Resi6=ResiFormat(5);
	else m_Resi6=_T("");
	if(m_Ch7==TRUE)m_Resi7=ResiFormat(6);
	else m_Resi7=_T("");
	if(m_Ch8==TRUE)m_Resi8=ResiFormat(7);
	else m_Resi8=_T("");
	if(m_Ch9==TRUE)m_Resi9=ResiFormat(8);
	else m_Resi9=_T("");
	if(m_Ch10==TRUE)m_Resi10=ResiFormat(9);
	else m_Resi10=_T("");

	if(m_Ch11==TRUE)m_Resi11=ResiFormat(10);
	else m_Resi11=_T("");
	if(m_Ch12==TRUE)m_Resi12=ResiFormat(11);
	else m_Resi12=_T("");
	if(m_Ch13==TRUE)m_Resi13=ResiFormat(12);
	else m_Resi13=_T("");
	if(m_Ch14==TRUE)m_Resi14=ResiFormat(13);
	else m_Resi14=_T("");
	if(m_Ch15==TRUE)m_Resi15=ResiFormat(14);
	else m_Resi15=_T("");
	if(m_Ch16==TRUE)m_Resi16=ResiFormat(15);
	else m_Resi16=_T("");
	if(m_Ch17==TRUE)m_Resi17=ResiFormat(16);
	else m_Resi17=_T("");
	if(m_Ch18==TRUE)m_Resi18=ResiFormat(17);
	else m_Resi18=_T("");
	if(m_Ch19==TRUE)m_Resi19=ResiFormat(18);
	else m_Resi19=_T("");
	if(m_Ch20==TRUE)m_Resi20=ResiFormat(19);
	else m_Resi20=_T("");

	if(m_Ch21==TRUE)m_Resi21=ResiFormat(20);
	else m_Resi21=_T("");
	if(m_Ch22==TRUE)m_Resi22=ResiFormat(21);
	else m_Resi22=_T("");
	if(m_Ch23==TRUE)m_Resi23=ResiFormat(22);
	else m_Resi23=_T("");
	if(m_Ch24==TRUE)m_Resi24=ResiFormat(23);
	else m_Resi24=_T("");
	if(m_Ch25==TRUE)m_Resi25=ResiFormat(24);
	else m_Resi25=_T("");
	if(m_Ch26==TRUE)m_Resi26=ResiFormat(25);
	else m_Resi26=_T("");
	if(m_Ch27==TRUE)m_Resi27=ResiFormat(26);
	else m_Resi27=_T("");
	if(m_Ch28==TRUE)m_Resi28=ResiFormat(27);
	else m_Resi28=_T("");
	if(m_Ch29==TRUE)m_Resi29=ResiFormat(28);
	else m_Resi29=_T("");
	if(m_Ch30==TRUE)m_Resi30=ResiFormat(29);
	else m_Resi30=_T("");

	m_Pt100PV.Format("%+6.1f",m_pDoc->m_Pt100);
	m_Sr253PV.Format("%+6.1f",m_pDoc->m_PV);
	m_Sr253SV.Format("%+6.1f",m_pDoc->m_SV);
	m_Pt100_1.Format("%+6.1f",m_pDoc->m_Pt100_1);
	m_Pt100_2.Format("%+6.1f",m_pDoc->m_Pt100_2);

	m_CheckZero=m_pDoc->m_rt.m_rtSave.m_CheckZero;
	m_ChanNo = 0;
	m_Resi = _T("");
}	
//}}AFX_DATA_INIT
}


//
//	获取通道i室温下电阻输出格式
//
CString CNameResi::ResiFormat(int i)
{
   CString m_Res0;
     if(m_pDoc->m_rt.m_fResi[i]<0.0001)m_Res0.Format("%7.5f", 0.0001);
     else if(m_pDoc->m_rt.m_fResi[i]<1)m_Res0.Format("%7.4f", m_pDoc->m_rt.m_fResi[i]);
     else if(m_pDoc->m_rt.m_fResi[i]<10)m_Res0.Format("%6.3f", m_pDoc->m_rt.m_fResi[i]);
     else if(m_pDoc->m_rt.m_fResi[i]<100)m_Res0.Format("%6.3f", m_pDoc->m_rt.m_fResi[i]);
     else if(m_pDoc->m_rt.m_fResi[i]<1000)m_Res0.Format("%6.2f", m_pDoc->m_rt.m_fResi[i]);
     else if(m_pDoc->m_rt.m_fResi[i]<1e4)m_Res0.Format("%6.4fE+03", m_pDoc->m_rt.m_fResi[i]/1e3);
     else if(m_pDoc->m_rt.m_fResi[i]<1e5)m_Res0.Format("%6.3fE+03", m_pDoc->m_rt.m_fResi[i]/1e3);
     else if(m_pDoc->m_rt.m_fResi[i]<1e6)m_Res0.Format("%6.2fE+03", m_pDoc->m_rt.m_fResi[i]/1e3);
     else if(m_pDoc->m_rt.m_fResi[i]<1e7)m_Res0.Format("%6.4fE+06", m_pDoc->m_rt.m_fResi[i]/1e6);
     else if(m_pDoc->m_rt.m_fResi[i]<1e8)m_Res0.Format("%6.3fE+06", m_pDoc->m_rt.m_fResi[i]/1e6);
     else m_Res0.Format("%6.2fE+06", m_pDoc->m_rt.m_fResi[i]/1e6);

//	 m_Res0.Format("%10.3e", m_pDoc->m_rt.m_fResi[i]);
   return m_Res0;
}

//
//	对话框数据交换
//
void CNameResi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNameResi)
	DDX_Check(pDX, IDC_CHECK1, m_Ch1);
	DDX_Check(pDX, IDC_CHECK10, m_Ch10);
	DDX_Check(pDX, IDC_CHECK11, m_Ch11);
	DDX_Check(pDX, IDC_CHECK12, m_Ch12);
	DDX_Check(pDX, IDC_CHECK13, m_Ch13);
	DDX_Check(pDX, IDC_CHECK14, m_Ch14);
	DDX_Check(pDX, IDC_CHECK15, m_Ch15);
	DDX_Check(pDX, IDC_CHECK16, m_Ch16);
	DDX_Check(pDX, IDC_CHECK17, m_Ch17);
	DDX_Check(pDX, IDC_CHECK18, m_Ch18);
	DDX_Check(pDX, IDC_CHECK19, m_Ch19);
	DDX_Check(pDX, IDC_CHECK2, m_Ch2);
	DDX_Check(pDX, IDC_CHECK20, m_Ch20);
	DDX_Check(pDX, IDC_CHECK21, m_Ch21);
	DDX_Check(pDX, IDC_CHECK22, m_Ch22);
	DDX_Check(pDX, IDC_CHECK23, m_Ch23);
	DDX_Check(pDX, IDC_CHECK24, m_Ch24);
	DDX_Check(pDX, IDC_CHECK25, m_Ch25);
	DDX_Check(pDX, IDC_CHECK26, m_Ch26);
	DDX_Check(pDX, IDC_CHECK27, m_Ch27);
	DDX_Check(pDX, IDC_CHECK28, m_Ch28);
	DDX_Check(pDX, IDC_CHECK29, m_Ch29);
	DDX_Check(pDX, IDC_CHECK3, m_Ch3);
	DDX_Check(pDX, IDC_CHECK30, m_Ch30);
	DDX_Check(pDX, IDC_CHECK4, m_Ch4);
	DDX_Check(pDX, IDC_CHECK5, m_Ch5);
	DDX_Check(pDX, IDC_CHECK6, m_Ch6);
	DDX_Check(pDX, IDC_CHECK7, m_Ch7);
	DDX_Check(pDX, IDC_CHECK8, m_Ch8);
	DDX_Check(pDX, IDC_CHECK9, m_Ch9);
	DDX_Text(pDX, IDC_EDIT_N1, m_Name1);
	DDX_Text(pDX, IDC_EDIT_N10, m_Name10);
	DDX_Text(pDX, IDC_EDIT_N11, m_Name11);
	DDX_Text(pDX, IDC_EDIT_N12, m_Name12);
	DDX_Text(pDX, IDC_EDIT_N13, m_Name13);
	DDX_Text(pDX, IDC_EDIT_N14, m_Name14);
	DDX_Text(pDX, IDC_EDIT_N15, m_Name15);
	DDX_Text(pDX, IDC_EDIT_N16, m_Name16);
	DDX_Text(pDX, IDC_EDIT_N17, m_Name17);
	DDX_Text(pDX, IDC_EDIT_N18, m_Name18);
	DDX_Text(pDX, IDC_EDIT_N19, m_Name19);
	DDX_Text(pDX, IDC_EDIT_N2, m_Name2);
	DDX_Text(pDX, IDC_EDIT_N20, m_Name20);
	DDX_Text(pDX, IDC_EDIT_N21, m_Name21);
	DDX_Text(pDX, IDC_EDIT_N22, m_Name22);
	DDX_Text(pDX, IDC_EDIT_N23, m_Name23);
	DDX_Text(pDX, IDC_EDIT_N24, m_Name24);
	DDX_Text(pDX, IDC_EDIT_N25, m_Name25);
	DDX_Text(pDX, IDC_EDIT_N26, m_Name26);
	DDX_Text(pDX, IDC_EDIT_N27, m_Name27);
	DDX_Text(pDX, IDC_EDIT_N28, m_Name28);
	DDX_Text(pDX, IDC_EDIT_N29, m_Name29);
	DDX_Text(pDX, IDC_EDIT_N3, m_Name3);
	DDX_Text(pDX, IDC_EDIT_N30, m_Name30);
	DDX_Text(pDX, IDC_EDIT_N4, m_Name4);
	DDX_Text(pDX, IDC_EDIT_N5, m_Name5);
	DDX_Text(pDX, IDC_EDIT_N6, m_Name6);
	DDX_Text(pDX, IDC_EDIT_N7, m_Name7);
	DDX_Text(pDX, IDC_EDIT_N8, m_Name8);
	DDX_Text(pDX, IDC_EDIT_N9, m_Name9);
	DDX_Text(pDX, IDC_EDIT_R10, m_Resi10);
	DDX_Text(pDX, IDC_EDIT_R1, m_Resi1);
	DDX_Text(pDX, IDC_EDIT_R11, m_Resi11);
	DDX_Text(pDX, IDC_EDIT_R12, m_Resi12);
	DDX_Text(pDX, IDC_EDIT_R13, m_Resi13);
	DDX_Text(pDX, IDC_EDIT_R14, m_Resi14);
	DDX_Text(pDX, IDC_EDIT_R15, m_Resi15);
	DDX_Text(pDX, IDC_EDIT_R16, m_Resi16);
	DDX_Text(pDX, IDC_EDIT_R17, m_Resi17);
	DDX_Text(pDX, IDC_EDIT_R18, m_Resi18);
	DDX_Text(pDX, IDC_EDIT_R19, m_Resi19);
	DDX_Text(pDX, IDC_EDIT_R2, m_Resi2);
	DDX_Text(pDX, IDC_EDIT_R20, m_Resi20);
	DDX_Text(pDX, IDC_EDIT_R21, m_Resi21);
	DDX_Text(pDX, IDC_EDIT_R22, m_Resi22);
	DDX_Text(pDX, IDC_EDIT_R23, m_Resi23);
	DDX_Text(pDX, IDC_EDIT_R24, m_Resi24);
	DDX_Text(pDX, IDC_EDIT_R25, m_Resi25);
	DDX_Text(pDX, IDC_EDIT_R26, m_Resi26);
	DDX_Text(pDX, IDC_EDIT_R27, m_Resi27);
	DDX_Text(pDX, IDC_EDIT_R28, m_Resi28);
	DDX_Text(pDX, IDC_EDIT_R29, m_Resi29);
	DDX_Text(pDX, IDC_EDIT_R3, m_Resi3);
	DDX_Text(pDX, IDC_EDIT_R30, m_Resi30);
	DDX_Text(pDX, IDC_EDIT_R4, m_Resi4);
	DDX_Text(pDX, IDC_EDIT_R5, m_Resi5);
	DDX_Text(pDX, IDC_EDIT_R6, m_Resi6);
	DDX_Text(pDX, IDC_EDIT_R7, m_Resi7);
	DDX_Text(pDX, IDC_EDIT_R8, m_Resi8);
	DDX_Text(pDX, IDC_EDIT_R9, m_Resi9);
	DDX_CBIndex(pDX, IDC_ChanNo, m_ChanNo);
	DDX_Text(pDX, IDC_EDIT_Resi, m_Resi);
	DDX_Text(pDX, IDC_EDIT_PV, m_Sr253PV);
	DDX_Text(pDX, IDC_EDIT_SV, m_Sr253SV);
	DDX_Check(pDX, IDC_CHECKZero, m_CheckZero);
	DDX_Text(pDX, IDC_EDIT_Pt100, m_Pt100PV);
	DDX_Text(pDX, IDC_EDIT_PV2, m_Pt100_1);
	DDX_Text(pDX, IDC_EDIT_PV3, m_Pt100_2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNameResi, CDialog)
	//{{AFX_MSG_MAP(CNameResi)
	ON_BN_CLICKED(IDC_Read_F45, OnReadF45)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_Read_Resis0, OnReadResis0)
	ON_BN_CLICKED(IDC_Read_Sr253, OnReadSr253)
	ON_BN_CLICKED(IDC_Read_Pt100, OnReadPt100)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNameResi消息处理程序

//

//	确认键操作：控温已开始则提示不可改参数；否则更新数据
//
void CNameResi::OnOK() 
{
//	NameResi0=1;
	if(m_pDoc->m_Running)
	{
		MessageBox("控温已经开始!不能改变参数!","Ptcr",MB_OK);
		return;
	}
	m_pDoc->ChanSet=TRUE;
	UpData();

	CDialog::OnOK();
   if(NameResi0==0)NameResi0=1;

}
void CNameResi::UpData()
{
		UpdateData(TRUE);
	m_pDoc->m_rt.m_rtSave.m_bChannels[0]=m_Ch1 ;
	m_pDoc->m_rt.m_rtSave.m_bChannels[9]=m_Ch10;
	m_pDoc->m_rt.m_rtSave.m_bChannels[10]=m_Ch11;
	m_pDoc->m_rt.m_rtSave.m_bChannels[11]=m_Ch12;
	m_pDoc->m_rt.m_rtSave.m_bChannels[12]=m_Ch13;
	m_pDoc->m_rt.m_rtSave.m_bChannels[13]=m_Ch14;
	m_pDoc->m_rt.m_rtSave.m_bChannels[14]=m_Ch15;
	m_pDoc->m_rt.m_rtSave.m_bChannels[15]=m_Ch16;
	m_pDoc->m_rt.m_rtSave.m_bChannels[16]=m_Ch17;
	m_pDoc->m_rt.m_rtSave.m_bChannels[17]=m_Ch18;
	m_pDoc->m_rt.m_rtSave.m_bChannels[18]=m_Ch19;
	m_pDoc->m_rt.m_rtSave.m_bChannels[1]=m_Ch2;
	m_pDoc->m_rt.m_rtSave.m_bChannels[19]=m_Ch20;
	m_pDoc->m_rt.m_rtSave.m_bChannels[20]=m_Ch21;
	m_pDoc->m_rt.m_rtSave.m_bChannels[21]=m_Ch22;
	m_pDoc->m_rt.m_rtSave.m_bChannels[22]=m_Ch23;
	m_pDoc->m_rt.m_rtSave.m_bChannels[23]=m_Ch24;
	m_pDoc->m_rt.m_rtSave.m_bChannels[24]=m_Ch25;
	m_pDoc->m_rt.m_rtSave.m_bChannels[25]=m_Ch26;
	m_pDoc->m_rt.m_rtSave.m_bChannels[26]=m_Ch27;
	m_pDoc->m_rt.m_rtSave.m_bChannels[27]=m_Ch28;
	m_pDoc->m_rt.m_rtSave.m_bChannels[28]=m_Ch29;
	m_pDoc->m_rt.m_rtSave.m_bChannels[2]=m_Ch3;
	m_pDoc->m_rt.m_rtSave.m_bChannels[29]=m_Ch30;
	m_pDoc->m_rt.m_rtSave.m_bChannels[3]=m_Ch4;
	m_pDoc->m_rt.m_rtSave.m_bChannels[4]=m_Ch5;
	m_pDoc->m_rt.m_rtSave.m_bChannels[5]=m_Ch6;
	m_pDoc->m_rt.m_rtSave.m_bChannels[6]=m_Ch7;
	m_pDoc->m_rt.m_rtSave.m_bChannels[7]=m_Ch8;
	m_pDoc->m_rt.m_rtSave.m_bChannels[8]=m_Ch9;

    strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[0],m_Name1);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[1],m_Name2);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[2],m_Name3);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[3],m_Name4);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[4],m_Name5);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[5],m_Name6);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[6],m_Name7);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[7],m_Name8);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[8],m_Name9);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[9],m_Name10);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[10],m_Name11);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[11],m_Name12);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[12],m_Name13);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[13],m_Name14);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[14],m_Name15);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[15],m_Name16);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[16],m_Name17);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[17],m_Name18);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[18],m_Name19);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[19],m_Name20);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[20],m_Name21);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[21],m_Name22);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[22],m_Name23);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[23],m_Name24);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[24],m_Name25);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[25],m_Name26);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[26],m_Name27);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[27],m_Name28);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[28],m_Name29);
	 strcpy(m_pDoc->m_rt.m_rtSave.m_sChannelsName[29],m_Name30);

	 m_pDoc->m_rt.m_rtSave.m_CheckZero=m_CheckZero;

}

//
//	点击“测电阻”键，每两秒读取一次各启用通道阻值
//
void CNameResi::OnReadF45() 
{
	// TODO: Add your control notification handler code here
    char *cmd="?\r";
//	char results[128];
    int Sr253BCC=6;
 //   float resi0;

	if(m_pDoc->m_Running)
	{
		MessageBox("控温已经开始!不能改变参数!","Ptcr",MB_OK);
		return;
	}
	UpdateData(TRUE);
	if((m_ChanNo<0)||(m_ChanNo>31))
		return;

	chan = m_ChanNo+1;
	m_pDoc->OutChan(chan);
/*	DWORD tick;
	m_pDoc->relaycount=1;
	tick=GetTickCount();
	tick=GetTickCount()-tick;
	CString cs;
	cs.Format("%ld,%ld",tick,m_pDoc->relaycount);
	MessageBox(cs);
*/
    KillTimer(1);
    SetTimer(1,2000,NULL);

    UpdateData(FALSE);


	return;	
	
}

//
//	定时器消息处理函数
//
void CNameResi::OnTimer(UINT nIDEvent) 
{
	char *cmd="?\r";
	char results[128];
    int Sr253BCC=6;
	char buftmp[10][35];
    float resi0;

    	// TODO: Add your message handler code here and/or call default


	switch(nIDEvent)
	{
  case 1:
		 if(m_pDoc->MultiMeter==5){
	         cmd="MEAS?;:INIT:CONT ON\r\n";
	    	 m_pDoc->ReadPvsv(cmd,results,4,3,Sr253BCC);
		 }
	m_pDoc->m_ReadingF45=0;
//    m_pDoc->ReadResi(results);
   m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(5);
   if(m_pDoc->m_Resistance>1e7)
   {
		  m_pDoc->OutChan(m_ChanNo+1);
//		  m_pDoc->OutChan(m_ChanNo+1);
          m_pDoc->DelayTime(3);  
        m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(4);

   }
 //    m_pDoc->Splint(buftmp,results,Sr253BCC);
//    m_Resi=buftmp[1];
	if(m_CheckZero==TRUE){
     resi0=m_pDoc->m_Resistance-m_pDoc->m_rt.m_Zeroresi[m_ChanNo];
     if(resi0<0)resi0=0.001;
	}
   else  resi0=m_pDoc->m_Resistance;
       if(resi0<1)  sprintf(buftmp[1],"%+5.3fmO",resi0*1000);
       else if(resi0<1000)  sprintf(buftmp[1],"%6.3f",resi0);
	   else sprintf(buftmp[1],"%6.3E",resi0);

	m_pDoc->m_rt.m_fResi[m_ChanNo]=resi0;
  m_Resi=buftmp[1];
//	strcpy(buftmp[1],buftmp[0]);
	
    ChannelDisplay(m_ChanNo,buftmp) ;
    UpdateData(FALSE);
	KillTimer(1);
	break;
  case 2:
		 if(m_pDoc->MultiMeter==5){
	         cmd="MEAS?;:INIT:CONT ON\r\n";
	    	 m_pDoc->ReadPvsv(cmd,results,4,3,Sr253BCC);
		 }
    m_pDoc->m_ReadingF45=0;
 //   m_pDoc->ReadResi(results);
   m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(4);
//	m_Resi=buftmp[1];
   if(m_pDoc->m_Resistance>1e7)
   {
		  m_pDoc->OutChan(m_ChanNo+1);
//		  m_pDoc->OutChan(m_ChanNo+1);
          m_pDoc->DelayTime(3);  
        m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(5);

   }
   if(m_CheckZero==TRUE){
     resi0=m_pDoc->m_Resistance-m_pDoc->m_rt.m_Zeroresi[m_ChanNo];
     if(resi0<0)resi0=0.0001;
	}
   else  resi0=m_pDoc->m_Resistance;
       if(resi0<1)  sprintf(buftmp[1],"%+5.3fmO",resi0*1000);
       else if(resi0<1000)  sprintf(buftmp[1],"%6.3f",resi0);
	   else sprintf(buftmp[1],"%6.3E",resi0);

	   m_pDoc->m_rt.m_fResi[m_ChanNo]=resi0;
 m_Resi=buftmp[1];
	ChannelDisplay(m_ChanNo,buftmp); 
    UpdateData(FALSE);
		while(1){
		m_ChanNo++;
		if(m_ChanNo>29){
			KillTimer(2);
			break;
		}
	  if(m_pDoc->m_rt.m_rtSave.m_bChannels[m_ChanNo]){
		  m_pDoc->OutChan(m_ChanNo+1);
		  break;
	  }
	}
	  
	  break;
  case 3:
	m_pDoc->m_ReadingF45=1;
	m_pDoc->ReadPvsv(cmd,results,4,3,Sr253BCC);
    m_pDoc->Splint(buftmp,results,Sr253BCC);
    m_Resi=buftmp[1];
    resi0=atof(m_Resi);
    m_pDoc->m_Pt100=m_pDoc->Temperature((resi0-0.90),-0.2);
	m_Pt100PV.Format("%+06.1f",m_pDoc->m_Pt100);
//lby	m_pDoc->m_rt.m_tPt100=m_pDoc->m_Pt100;
    UpdateData(FALSE);
	KillTimer(3);
	break;	
 default:
	break;
	}

	CDialog::OnTimer(nIDEvent);
}

//
//	点击“测温”键，根据万用表型号，每3秒或5秒读取一次各启用通道测量温度参数
//
void CNameResi::OnReadResis0() 
{
	// TODO: Add your control notification handler code here
    char *cmd="?\r";
    int Sr253BCC=6,i;

	if(m_pDoc->m_Running)
	{
		MessageBox("控温已经开始!","Ptcr",MB_OK);
		return;
	}
    UpData();
   
   for(i=0;i<30;i++){

	   if(m_pDoc->m_rt.m_rtSave.m_bChannels[i]){
		  m_pDoc->OutChan(i+1);
//		  m_pDoc->OutChan(i+1);
     m_pDoc->DelayTime(4);  
	 m_ChanNo=i;

    KillTimer(2);
    if((m_pDoc->m_sPortF45.m_rxdata.m_MultiMeter==4)||(m_pDoc->m_sPortF45.m_rxdata.m_MultiMeter==5))
        SetTimer(2,3000,NULL);	
	else SetTimer(2,5000,NULL);
    UpdateData(FALSE);
	return;
	   }


   }
//turn;
}

//
//	通道显示：将buf[1]赋给通道i样品的阻值
//
void CNameResi::ChannelDisplay(int i,char buftmp[][35] ) 
{
	switch(i)
	  {
	  case 0:
	     m_Resi1=buftmp[1];
    	 break;
	  case 1:
	     m_Resi2=buftmp[1];
		 break; 
	  case 2:
	     m_Resi3=buftmp[1];
		 break;
	  case 3:
	     m_Resi4=buftmp[1];
		 break; 
	  case 4:
	     m_Resi5=buftmp[1];
		 break;
	  case 5:
	     m_Resi6=buftmp[1];
		 break; 
	  case 6:
	     m_Resi7=buftmp[1];
		 break;
	  case 7:
	     m_Resi8=buftmp[1];
		 break; 
	  case 8:
	     m_Resi9=buftmp[1];
		 break;
	  case 9:
	     m_Resi10=buftmp[1];
		 break;
	  case 10:
	     m_Resi11=buftmp[1];
		 break;
	  case 11:
	     m_Resi12=buftmp[1];
		 break; 
	  case 12:
	     m_Resi13=buftmp[1];
		 break;
	  case 13:
	     m_Resi14=buftmp[1];
		 break; 
	  case 14:
	     m_Resi15=buftmp[1];
		 break;
	  case 15:
	     m_Resi16=buftmp[1];
		 break; 
	  case 16:
	     m_Resi17=buftmp[1];
		 break;
	  case 17:
	     m_Resi18=buftmp[1];
		 break; 
	  case 18:
	     m_Resi19=buftmp[1];
		 break;
	  case 19:
	     m_Resi20=buftmp[1];
		 break;

	  case 20:
	     m_Resi21=buftmp[1];
		 break;
	  case 21:
	     m_Resi22=buftmp[1];
		 break; 
	  case 22:
	     m_Resi23=buftmp[1];
		 break;
	  case 23:
	     m_Resi24=buftmp[1];
		 break; 
	  case 24:
	     m_Resi25=buftmp[1];
		 break;
	  case 25:
	     m_Resi26=buftmp[1];
		 break; 
	  case 26:
	     m_Resi27=buftmp[1];
		 break;
	  case 27:
	     m_Resi28=buftmp[1];
		 break; 
	  case 28:
	     m_Resi29=buftmp[1];
		 break;
	  case 29:
	     m_Resi30=buftmp[1];
		 break;
	  }
    UpdateData(FALSE);
return;
}     

//
//	点击“顺序测量”键，按仪器型号与通信协议，从仪器读取PV、SV、PT100等数据并保存
//
void CNameResi::OnReadSr253() 
{
	// TODO: Add your control notification handler code here
int Sr253BCC;
char *cmd="DS";
 
  Sr253BCC=m_pDoc->m_sPort.m_rxdata.Sr253BCC;//zjun2003/4/1
  if(m_pDoc->ZWX==0){
  
  	m_pDoc->ReadSr253();
        m_Sr253PV.Format("%+06.1f",m_pDoc->m_PV);
        m_Sr253SV.Format("%+06.1f",m_pDoc->m_SV);
        m_pDoc->m_rt.m_PV= m_pDoc->m_PV;
        m_pDoc->m_rt.m_SV= m_pDoc->m_SV;

 if(m_pDoc->m_sPort.m_rxdata.sr!=13){

  if(m_pDoc->Pt100Chan_1!=-1)
   {
     m_pDoc->m_Pt100_1=m_pDoc->ReadPt100(m_pDoc->Pt100Chan_1);
     if(m_pDoc->Pt100Chan_2!=m_pDoc->Pt100Chan_1)
		 m_pDoc->m_Pt100_2=m_pDoc->ReadPt100(m_pDoc->Pt100Chan_2);
     else m_pDoc->m_Pt100_2=m_pDoc->m_Pt100_1;
   }
   else {m_pDoc->m_Pt100_1=m_pDoc->m_rt.m_PV;
           m_pDoc->m_Pt100_2=m_pDoc->m_Pt100_1;
   }
 }
         m_Pt100_1.Format("%+06.1f",m_pDoc->m_Pt100_1);
         m_Pt100_2.Format("%+06.1f",m_pDoc->m_Pt100_2);
 }
  else {m_pDoc->m_Pt100_1=m_pDoc->ReadPt100(m_pDoc->Pt100Chan_1);

        m_pDoc->m_PV=m_pDoc->m_Pt100_1;
        m_pDoc->m_SV=m_pDoc->m_Pt100_1;
		m_Sr253PV.Format("%+06.1f",m_pDoc->m_PV);
        m_Sr253SV.Format("%+06.1f",m_pDoc->m_SV);
        m_pDoc->m_rt.m_PV= m_pDoc->m_PV;
        m_pDoc->m_rt.m_SV= m_pDoc->m_SV;

         m_Pt100_1.Format("%+06.1f",m_pDoc->m_rt.m_tPt100_1);
         m_Pt100_2.Format("%+06.1f",m_pDoc->m_rt.m_tPt100_2);
  }
    UpdateData(FALSE);
  return;	
}

//
//	点击“存盘”键：若未校零，则调用WriteZero()将数据写入通道校零文件ZERORANG.RES
//
void CNameResi::OnReadPt100() 
{
	// TODO: Add your control notification handler code here
    char *cmd="?\r";
    int Sr253BCC=6;
	if(m_CheckZero==TRUE){
    MessageBox("已校零,不能存盘","PTCR校零",MB_OK);	
	return;
	};
	m_pDoc->m_rt.WriteZero();

}

