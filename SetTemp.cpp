/*
**	FILENAME			SetTemp.cpp
**
**	PURPOSE				此类可用于设置升温方式，设置内容包含两段数据最高
**						温度、温度间隔、保温时间、升温速度，以及升温方式
**						和保温时间等
*/

#include "stdafx.h"
#include "ptcr.h"
#include "SetTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetTemp对话框

//
//	构造函数：初始化并打开对话框
//
CSetTemp::CSetTemp(	CPtcrDoc *pDoc,CWnd* pParent /*=NULL*/)
	: CDialog(CSetTemp::IDD, pParent)
{
	m_pDoc=pDoc;
	//{{AFX_DATA_INIT(CSetTemp)
	m_MaxT1 = _T("100");
	m_MaxT2 = _T("150");
	m_TempRamp1 = _T("0.8");
	m_TempRamp2 = _T("0.8");
	m_TempStep1 = _T("2");
	m_TempStep2 = _T("2");
	m_TempTime2 = _T("0");
	m_MinTemp = _T("");
	m_RoomTemp = _T("");
	m_TempTime0 = _T("");
	select=1;
   m_MaxT1_save=_T("150");
   m_MaxT2_save=_T("250");
   m_TempRamp1_save=_T("1.0");
   m_TempRamp2_save=_T("1.0");
   m_TempStep1_save=_T("10");
   m_TempStep2_save=_T("10");
   m_TempTime1_save=_T("3");
   m_TempTime2_save=_T("3");
	m_tempvias = 0.0f;
	//}}AFX_DATA_INIT
//	FILE  *stream;
//	CString filename;
//	filename="c:\\Windows\\nptem.ini";

 OpenNptem();
/*
	filename="nptem.ini";
	stream=fopen(filename,"r");
//	CString mm;
	if(stream!=NULL)
	{

	fscanf(stream,"%s\t",m_MaxT1_rise);
	m_MaxT1_rise.Format("%s",m_MaxT1_rise);
	m_MaxT1.Format("%s",m_MaxT1_rise);
    fscanf(stream,"%s\t",m_MaxT1_save);

	fscanf(stream,"%s\t",m_MaxT2_rise);
	m_MaxT2.Format("%s",m_MaxT2_rise);
	m_MaxT2_rise.Format("%s",m_MaxT2_rise);
	fscanf(stream,"%s\t",m_MaxT2_save);

	fscanf(stream,"%s\t",m_TempRamp1_rise);
	m_TempRamp1.Format("%s",m_TempRamp1_rise);
    m_TempRamp1_rise.Format("%s",m_TempRamp1_rise);
	fscanf(stream,"%s\t",m_TempRamp1_save);

	fscanf(stream,"%s\t",m_TempRamp2_rise);
	m_TempRamp2.Format("%s",m_TempRamp2_rise);
    m_TempRamp2_rise.Format("%s",m_TempRamp2_rise);
	fscanf(stream,"%s\t",m_TempRamp2_save);

	fscanf(stream,"%s\t",m_TempStep1_rise);
	m_TempStep1.Format("%s",m_TempStep1_rise);
    m_TempStep1_rise.Format("%s",m_TempStep1_rise);
	fscanf(stream,"%s\t",m_TempStep1_save);

	fscanf(stream,"%s\t",m_TempStep2_rise);
	m_TempStep2.Format("%s",m_TempStep2_rise);
    m_TempStep2_rise.Format("%s",m_TempStep2_rise);
	fscanf(stream,"%s\t",m_TempStep2_save);

	fscanf(stream,"%s\t",m_TempTime1_rise);
	m_TempTime0.Format("%s",m_TempTime1_rise);
    m_TempTime1_rise.Format("%s",m_TempTime1_rise);
	fscanf(stream,"%s\t",m_TempTime1_save);

	fscanf(stream,"%s\t",m_TempTime2_rise);
	m_TempTime2.Format("%s",m_TempTime2_rise);
    m_TempTime2_rise.Format("%s",m_TempTime2_rise);
	fscanf(stream,"%s\t",m_TempTime2_save);

	fscanf(stream,"%d\t",&select);
	fscanf(stream,"%d\t",&select);//lby
	fscanf(stream,"%s\t",m_MinTemp);//lby
	fscanf(stream,"%d\t",&m_pDoc->m_rt.m_TempSoakingCondition);
	fscanf(stream,"%f\t",&m_tempvias);

//  fprintf(stream,"%s\t",m_MinTemp);//lby
fclose(stream);


 if(m_pDoc->m_rt.Cooling==0){
  m_MinTemp.Format("%s","室温");
 }	

}

*/


  if((pDoc->m_PV>300)||(pDoc->m_PV<-50))
	if(pDoc->ZWX==0){ 
		pDoc->ReadSr253();
        pDoc->m_Pt100=pDoc->m_PV;
	    m_pDoc->m_rt.m_PV=pDoc->m_PV;
	}
      else {
   	   pDoc->m_PV=pDoc->ReadPt100(pDoc->Pt100Chan_1);
	  m_pDoc->m_rt.m_PV=pDoc->m_PV;
	  }
m_RoomTemp.Format("%.1f",m_pDoc->m_rt.m_PV);
//     m_pDoc->m_rt.m_roomtemp=m_pDoc->m_rt.m_PV;
// 	m_Rom_RoomTempomTemp.Format("%.1f",m_pDoc->m_rt.m_PV);
 

}

//
//	对话框数据交换
//
void CSetTemp::DoDataExchange(CDataExchange* pDX)
{

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetTemp)
	DDX_CBString(pDX, IDC_COMBO_MaxTemp1, m_MaxT1);
	DDV_MaxChars(pDX, m_MaxT1, 10);
	DDX_CBString(pDX, IDC_COMBO_MaxTemp2, m_MaxT2);
	DDV_MaxChars(pDX, m_MaxT2, 10);
	DDX_CBString(pDX, IDC_COMBO_TempRamp1, m_TempRamp1);
	DDV_MaxChars(pDX, m_TempRamp1, 10);
	DDX_CBString(pDX, IDC_COMBO_TempRamp2, m_TempRamp2);
	DDV_MaxChars(pDX, m_TempRamp2, 10);
	DDX_CBString(pDX, IDC_COMBO_TempStep1, m_TempStep1);
	DDV_MaxChars(pDX, m_TempStep1, 10);
	DDX_CBString(pDX, IDC_COMBO_TempStep2, m_TempStep2);
	DDV_MaxChars(pDX, m_TempStep2, 6);
	DDX_CBString(pDX, IDC_COMBO_TempTime2, m_TempTime2);
	DDV_MaxChars(pDX, m_TempTime2, 10);
	DDX_CBString(pDX, IDC_COMBO_MiniumTemp, m_MinTemp);
	DDV_MaxChars(pDX, m_MinTemp, 10);
	DDX_Text(pDX, IDC_EDIT_RoomTemp, m_RoomTemp);
	DDV_MaxChars(pDX, m_RoomTemp, 10);
	DDX_CBString(pDX, IDC_COMBO_TempTime0, m_TempTime0);
	DDV_MaxChars(pDX, m_TempTime0, 10);
	DDX_Text(pDX, IDC_EDIT_TempVias, m_tempvias);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetTemp, CDialog)
	//{{AFX_MSG_MAP(CSetTemp)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_COMMAND_RANGE(IDC_RADIO1,IDC_RADIO2,OnChioce)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetTemp消息处理程序

//
//	点击“OK”键，保存窗口内参数与选项，写入文件nptem.ini内
//
void CSetTemp::OnOK() 
{
	// TODO: Add extra validation here   
 	UpdateData(TRUE);
	if(select==1)
	{
		m_MaxT1_rise.Format("%s",m_MaxT1);
		m_MaxT2_rise.Format("%s",m_MaxT2);
        m_TempRamp1_rise.Format("%s",m_TempRamp1);
        m_TempRamp2_rise.Format("%s",m_TempRamp2);
        m_TempStep1_rise.Format("%s",m_TempStep1);
        m_TempStep2_rise.Format("%s",m_TempStep2);
	    m_TempTime1_rise.Format("%s","0");
	    m_TempTime2_rise.Format("%s","0");
	}
	else
	{
		m_MaxT1_save.Format("%s",m_MaxT1);
		m_MaxT2_save.Format("%s",m_MaxT2);
 
//lby	    m_TempTime1_save.Format("%s",m_TempTime0);

//lby	    m_TempTime2_save.Format("%s",m_TempTime2);

        m_TempRamp1_save.Format("%s",m_TempRamp1);
        m_TempRamp2_save.Format("%s",m_TempRamp2);
        m_TempStep1_save.Format("%s",m_TempStep1);
        m_TempStep2_save.Format("%s",m_TempStep2);

	}


 

	UpData();

	UpdateData(FALSE);
 //   m_pDoc->m_rt.m_rtSave.m_SetTemp=TRUE;

//	filename="c:\\Windows\\nptem.ini";
	filename="nptem.ini";
	stream=fopen(filename,"w");
	if(stream!=NULL)
	{	
    
	fprintf(stream,"%s\t",m_MaxT1_rise);
	fprintf(stream,"%s\t",m_MaxT1_save);

	fprintf(stream,"%s\t",m_MaxT2_rise);
	fprintf(stream,"%s\t",m_MaxT2_save);

	fprintf(stream,"%s\t",m_TempRamp1_rise);
	fprintf(stream,"%s\t",m_TempRamp1_save);

	fprintf(stream,"%s\t",m_TempRamp2_rise);	
	fprintf(stream,"%s\t",m_TempRamp2_save);	
	fprintf(stream,"%s\t",m_TempStep1_rise);
	fprintf(stream,"%s\t",m_TempStep1_save);

	fprintf(stream,"%s\t",m_TempStep2_rise);
	fprintf(stream,"%s\t",m_TempStep2_save);

	fprintf(stream,"%s\t",m_TempTime1_rise);

	//lby 
	if(select==2)
		fprintf(stream,"%s\t",m_TempTime0);
	else 
        fprintf(stream,"%s\t",m_TempTime1_save);


	fprintf(stream,"%s\t",m_TempTime2_rise);

	if(select==2)
	   	 fprintf(stream,"%s\t",m_TempTime2);    //lby	
	else
		fprintf(stream,"%s\t",m_TempTime2_save);


	fprintf(stream,"%d\t",select);
	fprintf(stream,"%d\t",select);
 

		fprintf(stream,"%s\t",m_MinTemp);//lby
		fprintf(stream,"%i\t",m_pDoc->m_rt.m_TempSoakingCondition);
		fprintf(stream,"%f\t",m_tempvias);

for(int i=0;i<10;i++)	fprintf(stream,"%s\t",m_MinTemp);//lby 冗余
//	fprintf(stream,"%s\t",m_TempRamp2_save);

	fclose(stream);
	}
	CDialog::OnOK();
}

//
//	更新数据
//
void CSetTemp::UpData() 
{
	// TODO: Add extra validation here
//	CPtcrDoc *m_pDoc;
 	
int i=atoi(m_MaxT2);	//

    m_pDoc->m_Tempvias=m_tempvias;
	m_pDoc->m_rt.m_rtSave.m_TIME=atoi(m_TempTime2);
 	m_pDoc->m_rt.m_rtSave.m_STEP=atoi(m_TempStep2);
 	m_pDoc->m_rt.m_rtSave.m_iStep=m_pDoc->m_rt.m_rtSave.m_STEP;


	m_pDoc->m_rt.m_rtSave.MaxT[0]=atoi(m_MaxT1);
	m_pDoc->m_rt.m_rtSave.m_MaxTemp=atoi(m_MaxT2);
 	m_pDoc->m_rt.m_rtSave.MaxT[1]=atoi(m_MaxT2);
	m_pDoc->m_rt.m_rtSave.soaking[0]=atoi(m_TempTime0);
	m_pDoc->m_rt.m_rtSave.soaking[1]=atoi(m_TempTime2);
 	m_pDoc->m_rt.m_rtSave.Step[0]=atoi(m_TempStep1);
 	m_pDoc->m_rt.m_rtSave.Step[1]=atoi(m_TempStep2);
 	m_pDoc->m_rt.m_rtSave.Ramp[0]=atof(m_TempRamp1);
	m_pDoc->m_rt.m_rtSave.Ramp[1]=atof(m_TempRamp2);

	if(strstr(m_MinTemp,"室温")){
				m_pDoc->m_rt.Cooling=0;
				m_pDoc->m_rt.m_rtSave.m_MinTemp=m_pDoc->m_rt.m_PV;
	}
	else {
		m_pDoc->m_rt.Cooling=1;
		m_pDoc->m_rt.m_rtSave.m_MinTemp=atof(m_MinTemp);
	}


    if((m_pDoc->m_rt.m_rtSave.MaxT[0]/ 	m_pDoc->m_rt.m_rtSave.Step[0]+
	   (m_pDoc->m_rt.m_rtSave.MaxT[1]-m_pDoc->m_rt.m_rtSave.MaxT[0])/m_pDoc->m_rt.m_rtSave.Step[1])>(MAXOFSPL-1))
	{
	m_pDoc->m_rt.m_rtSave.MaxT[1]=m_pDoc->m_rt.m_rtSave.MaxT[0]+(MAXOFSPL-1-m_pDoc->m_rt.m_rtSave.MaxT[0]/	m_pDoc->m_rt.m_rtSave.Step[0])*m_pDoc->m_rt.m_rtSave.Step[1]+1;
int i=0;
 i=1;
// m_MaxT2.Format();
	m_MaxT2.Format("%d", m_pDoc->m_rt.m_rtSave.MaxT[1]);
	}
	   


}	

//
//	选择保温条件后，判断各个选项是否可用并保存窗口内参数与选项
//
void CSetTemp::OnChioce(UINT nID)
{
 //  if((m_pDoc->m_rt.m_rtSave.m_SetTemp==FALSE)||m_pDoc->m_Running==FALSE)
  	   GetDlgItem(IDC_EDIT_RoomTemp)->EnableWindow(FALSE);
     if(m_pDoc->m_rt.client==6)
	   GetDlgItem(IDC_COMBO_MiniumTemp)->EnableWindow(TRUE);
	 else  GetDlgItem(IDC_COMBO_MiniumTemp)->EnableWindow(FALSE);

	 if(m_pDoc->m_Running){
	    GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE);
	 }

  switch(nID)
	{                    

	case IDC_RADIO1:

    select=1;
    m_MinTemp.Format("%s","室温");
	GetDlgItem(IDC_COMBO_MiniumTemp)->EnableWindow(FALSE);
    m_MaxT1.Format("%s",m_MaxT1_rise);
	m_MaxT2.Format("%s",m_MaxT2_rise);
	m_TempRamp1.Format("%s",m_TempRamp1_rise);
	m_TempRamp2.Format("%s",m_TempRamp2_rise);
	m_TempStep1.Format("%s",m_TempStep1_rise);
	m_TempStep2.Format("%s",m_TempStep2_rise);

	m_TempTime0.Format("%s","0");
	m_TempTime2.Format("%s","0");
    GetDlgItem(IDC_COMBO_TempTime0)->EnableWindow(FALSE);
    GetDlgItem(IDC_COMBO_TempTime2)->EnableWindow(FALSE);

		break;
	case IDC_RADIO2:

	select=2;
   	m_MaxT1.Format("%s",m_MaxT1_save);
	m_MaxT2.Format("%s",m_MaxT2_save);

	m_TempRamp1.Format("%s",m_TempRamp1_save);
	m_TempRamp2.Format("%s",m_TempRamp2_save);
	m_TempStep1.Format("%s",m_TempStep1_save);
	m_TempStep2.Format("%s",m_TempStep2_save);
	m_TempTime0.Format("%s",m_TempTime1_save);
	m_TempTime2.Format("%s",m_TempTime2_save);
    GetDlgItem(IDC_COMBO_TempTime0)->EnableWindow(TRUE);
    GetDlgItem(IDC_COMBO_TempTime2)->EnableWindow(TRUE);
		
		break;
	}
//	m_pDoc->m_rt.m_rtSave.MaxT[1]=atoi(m_MaxT2);
        if(m_pDoc->CPptc==1){
			if(m_pDoc->m_rt.m_rtSave.MaxT[1]>200)m_pDoc->m_rt.m_rtSave.MaxT[1]=200;
				m_MaxT2_save.Format("%d",m_pDoc->m_rt.m_rtSave.MaxT[1]);
		}
    m_MaxT2.Format("%s",m_MaxT2_save);
   
 		UpdateData(FALSE);
 
		//		UpdateData(TRUE);

	//	CWnd * pWnd = GetDlgItem(IDC_EDIT1);

//	pWnd->Invalidate();
}

//
//	初始化对话框
//
BOOL CSetTemp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CButton * m_pRadio;

	if(m_pDoc->m_rt.m_TempSoakingCondition==1){
	  m_pRadio=(CButton*)GetDlgItem(IDC_RADIO7);
      m_pRadio->SetCheck(1);
	}
	else {
	  m_pRadio=(CButton*)GetDlgItem(IDC_RADIO6);
      m_pRadio->SetCheck(1);
      m_pDoc->m_rt.m_TempSoakingCondition=0	;
	}

	if(select==2)
  {
	  m_pRadio=(CButton*)GetDlgItem(IDC_RADIO2);
      m_pRadio->SetCheck(1);
   //   if(m_pDoc->m_rt.m_rtSave.m_SetTemp==FALSE)
		  OnChioce(IDC_RADIO2);
  }
  else
  {
	  m_pRadio=(CButton*)GetDlgItem(IDC_RADIO1);
      m_pRadio->SetCheck(1);
   //   if(m_pDoc->m_rt.m_rtSave.m_SetTemp==FALSE) 
		  OnChioce(IDC_RADIO1);
  }
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//
//	选择保温条件为“保温时间到测量”
//
void CSetTemp::OnRadio6() 
{
	// TODO: Add your control notification handler code here
    m_pDoc->m_rt.m_TempSoakingCondition=0;	

}

//
//	选择保温条件为“满足一定温差”
//
void CSetTemp::OnRadio7() 
{
	// TODO: Add your control notification handler code here
    m_pDoc->m_rt.m_TempSoakingCondition=1;	
	
}

//
//	开启并读取临时文件nptem.ini中数据
//
void CSetTemp::OpenNptem()
{

	filename="nptem.ini";
	stream=fopen(filename,"r");
//	CString mm;
	if(stream!=NULL)
	{

	fscanf(stream,"%s\t",m_MaxT1_rise);
	m_MaxT1_rise.Format("%s",m_MaxT1_rise);
	m_MaxT1.Format("%s",m_MaxT1_rise);
    fscanf(stream,"%s\t",m_MaxT1_save);

	fscanf(stream,"%s\t",m_MaxT2_rise);
	m_MaxT2.Format("%s",m_MaxT2_rise);
	m_MaxT2_rise.Format("%s",m_MaxT2_rise);
	fscanf(stream,"%s\t",m_MaxT2_save);

	fscanf(stream,"%s\t",m_TempRamp1_rise);
	m_TempRamp1.Format("%s",m_TempRamp1_rise);
    m_TempRamp1_rise.Format("%s",m_TempRamp1_rise);
	fscanf(stream,"%s\t",m_TempRamp1_save);

	fscanf(stream,"%s\t",m_TempRamp2_rise);
	m_TempRamp2.Format("%s",m_TempRamp2_rise);
    m_TempRamp2_rise.Format("%s",m_TempRamp2_rise);
	fscanf(stream,"%s\t",m_TempRamp2_save);

	fscanf(stream,"%s\t",m_TempStep1_rise);
	m_TempStep1.Format("%s",m_TempStep1_rise);
    m_TempStep1_rise.Format("%s",m_TempStep1_rise);
	fscanf(stream,"%s\t",m_TempStep1_save);

	fscanf(stream,"%s\t",m_TempStep2_rise);
	m_TempStep2.Format("%s",m_TempStep2_rise);
    m_TempStep2_rise.Format("%s",m_TempStep2_rise);
	fscanf(stream,"%s\t",m_TempStep2_save);

	fscanf(stream,"%s\t",m_TempTime1_rise);
	m_TempTime0.Format("%s",m_TempTime1_rise);
    m_TempTime1_rise.Format("%s",m_TempTime1_rise);
	fscanf(stream,"%s\t",m_TempTime1_save);

	fscanf(stream,"%s\t",m_TempTime2_rise);
	m_TempTime2.Format("%s",m_TempTime2_rise);
    m_TempTime2_rise.Format("%s",m_TempTime2_rise);
	fscanf(stream,"%s\t",m_TempTime2_save);

	fscanf(stream,"%d\t",&select);
	fscanf(stream,"%d\t",&select);//lby
	fscanf(stream,"%s\t",m_MinTemp);//lby
	fscanf(stream,"%d\t",&m_pDoc->m_rt.m_TempSoakingCondition);
	fscanf(stream,"%f\t",&m_tempvias);

//   			fprintf(stream,"%s\t",m_MinTemp);//lby
fclose(stream);
m_pDoc->m_Tempvias=m_tempvias;
if(m_pDoc->m_rt.Cooling==0){
  m_MinTemp.Format("%s","室温");
 }	

}
}
