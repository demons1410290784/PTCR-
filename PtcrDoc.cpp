/*
**	FILENAME			PtcrDoc.cpp
**
**	PURPOSE				此类可用于文档相关的操作，包含文件
**						的打开与保存、文件的修改以及命令/信
**						号的读取与写入的等
*/

#include "stdafx.h"
#include "Ptcr.h"
#include "fstream.h"
#include "PtcrDoc.h"
#include "PtcrView.h"
#include "combindlg.h"
#include "MainFrm.h"
#include "conio.h"
#include "stdlib.h"
#include "non.h"
#include "SETUSER.h"
//#include "SetTemp.h"
//#include "BasicExcelVC6.hpp"
#include <windows.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString m_setusername;

/////zjun///

/////////////////////////////////////////////////////////////////////////////
// CPtcrDoc

IMPLEMENT_DYNCREATE(CPtcrDoc, CDocument)

BEGIN_MESSAGE_MAP(CPtcrDoc, CDocument)
	//{{AFX_MSG_MAP(CPtcrDoc)
	ON_UPDATE_COMMAND_UI(ID_TOOL_CONBIND, OnUpdateToolConbind)
	ON_COMMAND(ID_TOOL_CONVERT, OnToolConvert)
	ON_UPDATE_COMMAND_UI(ID_TOOL_CONVERT, OnUpdateToolConvert)
	ON_COMMAND(ID_TOOL_CONVERTEXCEL, OnToolConvertExcel)
	ON_UPDATE_COMMAND_UI(ID_TOOL_CONVERTEXCEL, OnUpdateToolConvertExcel)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_MENUISETUSER, OnMenuSetUser)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPtcrDoc 构造/析构

//
//	构造函数：初始化各参数
//
CPtcrDoc::CPtcrDoc()
{
	// TODO: add one-time construction code here

	//   m_rt.client=10;// client=0 ZWX-C; client=1 keter;//by zj----------
       //client=2 dongguan weiqing; client=3  GAOLI
//  pOut=new BYTE[16];
  bool bResult;

  OSver=GetOSVersion();
  if(OSver==1)
  {
	bResult=InitializeWinIo();
	{
	for(int aa=0;aa<10;aa++)
	{
	if(!bResult)
	bResult=InitializeWinIo();
	else break;
	}
	}
  }
	//  if (openDirectIO(NULL)==-1) 
 //AfxMessageBox("Failed to Open Direct IO !");//---------by zj



CPptc=0;    //0 CPtc, 1 PPtc
    HeatCool=0;
    m_rt.Cooling=0;//Cool制冷
	m_rt.client=4;// client=0 ZWX-C; client=1 keter;  =9 Changshu linzi
      //client=2 dongguan weiqing; client=3  GAOLI; client=4  Tiancheng; 
	   //  client=5  shenzhen fuli  client=6  changzhou xingqing,;==7 715new
    m_rt.isChangeRange=TRUE;//TURE Change Range;False No
		ZWX=0;//0=zwx-b 1=zwx-c,2=ZWX-d
    m_rt.ZWX=ZWX;
   m_Tempvias=0;
	if( ZWX==1) Init8253();
    Pidtime=10;//10sec

	ChanSet=FALSE; //设置通道 FALSE未设置, TRUE设置
    m_sPort.m_rxdata.Sr253BCC=2;
	m_Running=FALSE; //1 RUN, 0 non-Run
	m_rt.isRunning=m_Running; //1 RUN, 0 non-Run
	if(ZWX==1){//ZWX_C
	w2w4=0;//0 2wires, 1 4 wires
    MultiMeter=1;//1 0 无万用表, 1 FLUKE45, 2 Tonghui2512, 3 Esort3146A富贵/艾克, 4 HP34401A ,5 2000
	DigitController=0; //0 无温控表, 1 SR253;
	Pt100Chan_1=16;
	Pt100Chan_2=16;
	m_HT12D=0;//0 8255; 1 HT12D
    m_rt.m_Number=10;
	m_rt.m_rtSave.m_SpecialR=3e8;
	}
	else if(ZWX==2){//ZWX_D
	w2w4=0;//0 2wires, 1 4 wires
    MultiMeter=5;//1 0 无万用表, 1 FLUKE45, 2 Tonghui2512, 3 Esort3146A富贵/艾克, 4 HP34401A ,5 2000
	DigitController=0; //0 无温控表, 1 SR253;
	Pt100Chan_1=16;
	Pt100Chan_2=16;
	m_HT12D=0;//0 8255; 1 HT12D
    m_rt.m_Number=10;
	m_rt.m_rtSave.m_SpecialR=1e8;
	}
	else{
    DigitController=1; //1 SR253;
    Pt100Chan_1=-1;
    Pt100Chan_2=-1;
	m_HT12D=1;//0 8255; 1 HT12D
    if(m_rt.client==1) {
		m_rt.m_Number=12;
	m_HT12D=1;//0 8255; 1 HT12D
	    w2w4=1;//0 2wires, 1 4 wires
		MultiMeter=2;//2 Tonghui2512
	    m_rt.m_rtSave.m_SpecialR=2e6;
	}
    else if(m_rt.client==2) {
		m_rt.m_Number=8;
        ZWX=0;       
        m_rt.ZWX=ZWX;
	    w2w4=1;//0 2wires, 1 4 wires
		MultiMeter=4;// 1 Fluke45
	m_rt.m_rtSave.m_SpecialR=1e8;
	}
    else if(m_rt.client==3) {//gaoli
		m_rt.m_Number=30;
        ZWX=0;       
        m_rt.ZWX=ZWX;
	    w2w4=0;//0 2wires, 1 4 wires
		MultiMeter=1;// 1 Fluke45
    	m_HT12D=0;//0 8255; 1 HT12D

	    m_rt.m_rtSave.m_SpecialR=3e8;
	}
   else if((m_rt.client==4)||(m_rt.client==5)||(m_rt.client==11)){
        ZWX=0;       
        m_rt.ZWX=ZWX;
	    w2w4=0;//0 2wires, 1 4 wires
		MultiMeter=1;// 1,F45,4 HP34401A 
	    m_rt.m_rtSave.m_SpecialR=3e8;
 if((m_rt.client==4)||(m_rt.client==11)){
        ZWX=0;       
	 m_rt.m_Number=12;
	 m_sPort.m_rxdata.Sr253BCC=4;//zjun2004/4/1
     m_sPort.m_rxdata.sr=83;//zjun2004/4/1
     //  m_sPort.m_rxdata.sr=93;//zjun2004/4/1
 }
 else if(m_rt.client==5){
	 m_rt.m_Number=15;
//	 m_rt.m_Number=20;  Fuliyuan
	 m_sPort.m_rxdata.Sr253BCC=4;//zjun2004/4/1
     m_sPort.m_rxdata.sr=93;//zjun2004/4/1
 } 
}
 else if(m_rt.client==6){
        ZWX=0;       
        m_rt.ZWX=ZWX;
	    w2w4=1;//0 2wires, 1 4 wires
		MultiMeter=4;// 1,F45,4 HP34401A ,5, 2000
	    m_rt.m_rtSave.m_SpecialR=1e8;
	 m_rt.m_Number=16;
	 m_sPort.m_rxdata.Sr253BCC=4;//zjun2004/4/1
     m_sPort.m_rxdata.sr=13;//zjun2004/4/1 93:sr93, 83:sr83, 13:mr13
      CPptc=1;    //0 CPtc, 1 PPtc
    //  m_sPort.m_rxdata.sr=93;//zjun2004/4/1
 } //	 m_sPort.m_rxdata.Sr253BCC=2; 
 else if(m_rt.client==7){
        ZWX=0;       
        m_rt.ZWX=ZWX;
	    w2w4=1;//0 2wires, 1 4 wires
		MultiMeter=1;// 1,F45,4 HP34401A ,5, 2000
	    m_rt.m_rtSave.m_SpecialR=3e8;
	 m_rt.m_Number=30;
	 m_sPort.m_rxdata.Sr253BCC=2;//zjun2004/4/1
     m_sPort.m_rxdata.sr=253;//zjun2004/4/1 93:sr93, 83:sr83, 13:mr13
      CPptc=2;    //0 CPtc, 1 PPtc

	  //  m_sPort.m_rxdata.sr=93;//zjun2004/4/1
 } //	 m_sPort.m_rxdata.Sr253BCC=2; 
 else if(m_rt.client==8){
        ZWX=0;       
        m_rt.ZWX=ZWX;
	    w2w4=1;//0 2wires, 1 4 wires
//		MultiMeter=1;// 1,F45,4 HP34401A ,5, 2000
    MultiMeter=5;//1 0 无万用表, 1 FLUKE45, 2 Tonghui2512, 3 Esort3146A富贵/艾克, 4 HP34401A ,5 2000
	    m_rt.m_rtSave.m_SpecialR=1e8;
	 m_rt.m_Number=16;
	 m_sPort.m_rxdata.Sr253BCC=4;//zjun2004/4/1
     m_sPort.m_rxdata.sr=83;//zjun2004/4/1 93:sr93, 83:sr83, 13:mr13
      CPptc=1;    //0 CPtc, 1 PPtc

	m_HT12D=1;//0 8255; 1 HT12D
	  //  m_sPort.m_rxdata.sr=93;//zjun2004/4/1
 } //	 m_sPort.m_rxdata.Sr253BCC=2; 
	else { w2w4=0;//0 2wires, 1 4 wires
		m_rt.m_Number=30;
    	m_rt.m_rtSave.m_SpecialR=1e8;
	}
	}

 // Temperature Controller =1;

   m_sPortF45.m_rxdata.Sr253BCC=6;//zjun2004/4/1

	m_sPortF45.m_rxdata.m_MultiMeter=MultiMeter;

  m_sPort.m_rxdata.m_MultiMeter=0;

     m_sPort.m_nPortNr=0;//Com1
	 m_sPort.m_baudno=4;//1200
   	m_sPort.m_stopno=0; // 1 stopbit
	m_sPort.m_parityno=2; //EVEN
	m_sPort.m_datano=1; // 7 databits
	//PID Controller

     m_sPortF45.m_nPortNr=1;//Com2
	m_sPortF45.m_baudno=3;
	m_sPortF45.m_stopno=0;
    m_sPortF45.m_parityno=0;
    m_sPortF45.m_datano=0;
//Multimeter

  if((MultiMeter==4)&&(m_rt.client==6)){
	;
  }
  else if(MultiMeter==4){
		m_sPortF45.m_stopno=2;
	    m_sPort.m_baudno=1;
	}
    else if(MultiMeter==1){
	    m_sPortF45.m_baudno=3;
	}
    else m_sPortF45.m_stopno=0;
  //	m_sPort.m_stopno=0;
	heatstop=0; //0 normal exit, 1 manual exit, 2 time-out exit, 
                //3 high limit temperature>20, 4 low limit temperature<20,
//    CPptc=0;    //0 CPtc, 1 PPtc
	if(CPptc==1){  m_rt.m_rtSave.m_TIME=0;
           m_rt.m_rtSave.MaxT[1]=150;
	}
	else{
		   m_rt.m_rtSave.m_TIME=0;//0 linear heating, 1 step heating
           m_rt.m_rtSave.MaxT[1]=250;
	}

    STARTDOT=0;	
	m_SaveAs=FALSE;

//    SavePtcRtIni();

}

//
//	析构函数
//
CPtcrDoc::~CPtcrDoc()
{
	
	//delete pOut;
 //ParaP.ExitDeviceLPT1();
 ShutdownWinIo();
}

//
//	打开“新建文件”对话框
//
BOOL CPtcrDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;


	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

		CString m_sStr[2];
        ChanSet=FALSE;
// m_rt.ReadZero();
	m_rt.Initialization();
	m_rt.m_rtSave.Initialization();

	CTime dt=CTime::GetCurrentTime();
	CString title=dt.Format("%Y%m%d.RT");
  m_sStr[0]=dt.Format("%Y/%m/%d");
  m_sStr[1]=dt.Format("%H:%M:%S-A");	
  strcpy(m_rt.m_rtSave.m_sStr[0],m_sStr[0]); 
  strcpy(m_rt.m_rtSave.m_sStr[1],m_sStr[1]); 
	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPtcrDoc 序列化

//
//	序列化函数：按运行状态与文件类型，按相应方式存储数据
//
void CPtcrDoc::Serialize(CArchive& ar)
{
	CString filenamestr;
	bool filestyle=0;
    const CFile* fp=ar.GetFile();
	filenamestr=fp->GetFileName();
	if(filenamestr.Find(".dat")!=-1)
	{
		filestyle=1;  //filestyle=1 is .dat file style
	}
//	filenamestr;//.m_pFile->m_srtFileName;
	static int Program_RUN=0; 
	if (ar.IsStoring())
	{
		
		if(m_rt.m_DatOrRtFile==0)
		{
			int i,j;
  				for(i=0;i<NMBOFSPL;i++)
					for(j=0;j<50;j++)
					{
//						ar<<r;
				    	ar<<m_rt.m_rtSave.m_fPtc[i][j];
					}

				for(i=0;i<NMBOFSPL;i++)
					for(j=0;j<50;j++)
					{
//						ar<<r;
					ar<<m_rt.m_rtSave.m_fTem[i][j];
					}
				
//				ar>>s;
		   	ar<<m_rt.m_rtSave.m_STEP;

            ar.Write(m_rt.m_rtSave.m_sStr,sizeof(m_rt.m_rtSave.m_sStr));
        
		}
		else
		{
/*		int filelength;
	    filelength=filenamestr.GetLength();
		filenamestr.TrimRight(".dat");
		filenamestr=filenamestr+".RT";
		ar.set
*/
		int i,j;
//		int m_startdot;
//		int i,j,k,i0,m_enddot,m_startdot;
//		BOOL m_EnableRemoveR,m_RemoveR;
//		BOOL m_SpecialDot;
		// TODO: add storing code here
		OpenFlag=FALSE;
//		float t;  	
 
		if(m_Running==TRUE) {

            m_SaveAs=FALSE;
			Program_RUN=1;
		}

			ar.Write(m_rt.m_rtSave.m_fPtc,sizeof(m_rt.m_rtSave.m_fPtc));	
///zjun


//	for(i=0;i<NMBOFSPL;i++)
//		 m_rt.m_rtSave.m_fTem[i][7]=29.9;
			
		for(i=0;i<NMBOFSPL;i++)
	    	for(j=0;j<MAXOFSPL;j++)
			{
//					ar>>r;
		    	if(m_rt.m_rtSave.m_fTem[i][j]<0) 
				{

				 if(i<4 && m_rt.m_rtSave.m_fTem[i+4][j]>=-50 && m_rt.m_rtSave.m_fTem[i+4][j]<=400)
					 m_rt.m_rtSave.m_fTem[i][j]=m_rt.m_rtSave.m_fTem[i+4][j];
				 else if(i<4)
                      m_rt.m_rtSave.m_fTem[i][j]= m_rt.m_rtSave.m_fTem[i+8][j];
				 if(i>7 && m_rt.m_rtSave.m_fTem[i+4][j]>=-50 && m_rt.m_rtSave.m_fTem[i+4][j]<=400)
					 m_rt.m_rtSave.m_fTem[i][j]=m_rt.m_rtSave.m_fTem[i-4][j];
				 else if(i>7)
                      m_rt.m_rtSave.m_fTem[i][j]= m_rt.m_rtSave.m_fTem[i-8][j];
				 if((i>3 && i<8) && m_rt.m_rtSave.m_fTem[i+4][j]>=-50 && m_rt.m_rtSave.m_fTem[i+4][j]<=400)
					 m_rt.m_rtSave.m_fTem[i][j]=m_rt.m_rtSave.m_fTem[i+4][j];
				 else if(i>3 && i<8)
                      m_rt.m_rtSave.m_fTem[i][j]= m_rt.m_rtSave.m_fTem[i-4][j];
				}
			}

			
///zjun

//	        m_rt.m_rtSave.m_fTem[0][8]=26.1;
//			m_rt.m_rtSave.m_fTem[0][9]=26.2;
//			m_rt.m_rtSave.m_fTem[0][10]=26.1;
			ar.Write(m_rt.m_rtSave.m_fTem,sizeof(m_rt.m_rtSave.m_fTem));	
			
			ar<<m_rt.m_rtSave.m_STEP;


   ar.Write(m_rt.m_rtSave.m_sStr,sizeof(m_rt.m_rtSave.m_sStr));	

   

   ar.Write(m_rt.m_rtSave.m_bChannels,sizeof(m_rt.m_rtSave.m_bChannels));	

   ar.Write(m_rt.m_rtSave.m_sChannelsName,sizeof(m_rt.m_rtSave.m_sChannelsName));	
  
   CString m_Time("",12);
 if(m_Running==TRUE)
 {
   m_rt.m_rtSave.m_endtime=CTime::GetCurrentTime();
   m_Time=m_rt.m_rtSave.m_endtime.Format("%H:%M:%S");
   strcpy(m_rt.m_rtSave.endTime[1],m_Time);
   m_Time=m_rt.m_rtSave.m_endtime.Format("%Y/%m/%d");
   strcpy(m_rt.m_rtSave.endTime[0],m_Time);
 }

//ar.Write(m_rt.m_rtSave.endTime,sizeof(m_rt.m_rtSave.endTime));	

	 ar.Write(m_rt.m_rtSave.endTime,sizeof(m_rt.m_rtSave.endTime));	

	 ar.Write(m_rt.m_rtSave.MaxT,sizeof(m_rt.m_rtSave.MaxT));	
	 ar.Write(m_rt.m_rtSave.soaking,sizeof(m_rt.m_rtSave.soaking));	
	 ar.Write(m_rt.m_rtSave.Step,sizeof(m_rt.m_rtSave.Step));	
	 ar.Write(m_rt.m_rtSave.Ramp,sizeof(m_rt.m_rtSave.Ramp));	

	 
	 //zjun 2002/8/6

	 ar<<MultiMeter;	
	 ar<<ZWX;	
	 ar<<DigitController;	
	 ar<<m_HT12D;	
	 ar<<w2w4;	//2Wire/4wire
	 ar<<Pt100Chan_1;
	 ar<<Pt100Chan_2;

	 ar<<m_rt.Cooling;
	 ar<<CPptc;
	 ar<<heatstop;
     ar<< m_rt.m_Number;
     ar<< m_rt.client;
	 int aaa[500];
	 ar.Write(aaa,sizeof(aaa));	

     OpenFlag=TRUE;
		}
	}
	else
	{
	  if(m_Running==1)return;
		// TODO: add loading code here
       if(filestyle==0)// *.RT
	   {
		OpenFlag=FALSE;
		try
		{
			int i,j;
			CString str("",15);
			float r;
			m_rt.m_DatOrRtFile=TRUE;			
			m_rt.Initialization();

	    	i=NMBOFSPL;
		    j=MAXOFSPL;
	    	for(i=0;i<NMBOFSPL;i++)
				for(j=0;j<MAXOFSPL;j++)
				{
					ar>>r;
					
				m_rt.m_rtSave.m_fPtc[i][j]=r;
				if(m_rt.m_rtSave.m_fPtc[i][j]>m_rt.m_rtSave.m_SpecialR)
					m_rt.m_rtSave.m_fPtc[i][j]=m_rt.m_rtSave.m_SpecialR;
				}
			

			ar.Read(m_rt.m_rtSave.m_fTem,sizeof(m_rt.m_rtSave.m_fTem));	
		   	ar>>m_rt.m_rtSave.m_STEP;

            ar.Read(m_rt.m_rtSave.m_sStr,sizeof(m_rt.m_rtSave.m_sStr));
            m_rt.m_rtSave.m_sStr[0][14]=NULL;
            m_rt.m_rtSave.m_sStr[1][14]=NULL;

			for(i=0;i<NMBOFSPL;i++)
			{
				j=10;
				if(fabs(m_rt.m_rtSave.m_fPtc[i][j]-1.0)<1e-2||fabs(m_rt.m_rtSave.m_fPtc[i][j]-0.01)<1e-2)
					m_rt.m_rtSave.m_bChannels[i]=0;//		LoadChannels(i,FALSE);

				else
					m_rt.m_rtSave.m_bChannels[i]=1;//LoadChannels(i,TRUE);	
			}
//	for(i=0;i<NMBOFSPL;i++)
//		 m_rt.m_rtSave.m_fTem[i][7]=27.9;


            if( strstr(m_rt.m_rtSave.m_sStr[1],"-A")!=NULL)
			{
	          ar.Read(m_rt.m_rtSave.m_bChannels,sizeof(m_rt.m_rtSave.m_bChannels));	

              ar.Read(m_rt.m_rtSave.m_sChannelsName,sizeof(m_rt.m_rtSave.m_sChannelsName));	
              ar.Read(m_rt.m_rtSave.endTime,sizeof(m_rt.m_rtSave.endTime));	
 
              ar.Read(m_rt.m_rtSave.MaxT,sizeof(m_rt.m_rtSave.MaxT));	
              ar.Read(m_rt.m_rtSave.soaking,sizeof(m_rt.m_rtSave.soaking));	
              ar.Read(m_rt.m_rtSave.Step,sizeof(m_rt.m_rtSave.Step));	
        	  ar.Read(m_rt.m_rtSave.Ramp,sizeof(m_rt.m_rtSave.Ramp));	

         	  ar>>MultiMeter;	
        	  ar>>ZWX;	
          	  m_rt.ZWX=ZWX;	
        	  ar>>DigitController;	
        	  ar>>m_HT12D;	
        	 ar>>w2w4;	//2Wire/4wire
         	 ar>>Pt100Chan_1;
        	 ar>>Pt100Chan_2;
          	 ar>>m_rt.Cooling;
         	 ar>>CPptc;
          	 ar>>heatstop;
             ar>>m_rt.m_Number;
             ar>>m_rt.client;//zjun2003/1/6

			}
          	else
			{
	       		str=ar.GetFile()->GetFileName();
	      		str.Format("%s.nam",str.Left(str.GetLength()-4));
				ifstream os;
		      	os.open(str,ifstream::out|ifstream::in|ifstream::nocreate);
		
		     	if(!os.fail())
				{
	 	          	char c[9];
				
		      		for(i=0;i<NMBOFSPL;i++)
					{
		      			os.getline(c,9);
		      			str="";
		      			str.Format("%s",c);
			      		if(str!="")
						strcpy(m_rt.m_rtSave.m_sChannelsName[i],str);
					}
				}
						
			}
			for(i=0;i<30;i++)
			{
				if(m_rt.m_rtSave.m_bChannels[i]==TRUE)
				{
					m_rt.Calculation(i);
				}
			}
			
			for(i=0;i<30;i++)
			{
				if(m_rt.m_rtSave.m_bChannels[i]==TRUE)
				{
					LoadIndex(i);
					break;
				}
			}

			OpenFlag=TRUE;

		}
	
		catch(CArchiveException* theException)
		{
			TCHAR str[255];
			theException->GetErrorMessage(str,255);
			MessageBox(GetActiveWindow(),str, "警告",MB_OK);
			UpdateAllViews(NULL);
		}
		
	}	
	else  //*.dat file
	{
		try
			{
				int i,j;
//				char c;
				CString str("",15);
				float r;
//				short int s;
				m_rt.m_DatOrRtFile=0;			
				m_rt.Initialization();

				for(i=0;i<NMBOFSPL;i++)
					for(j=0;j<50;j++)
					{
						ar>>r;
				    	m_rt.m_rtSave.m_fPtc[i][j]=r;
					}
				
				for(i=0;i<NMBOFSPL;i++)
					for(j=0;j<50;j++)
					{
						ar>>r;
					m_rt.m_rtSave.m_fTem[i][j]=r;
					}
				
//				ar>>s;
		   	ar>>m_rt.m_rtSave.m_STEP;

            ar.Read(m_rt.m_rtSave.m_sStr,sizeof(m_rt.m_rtSave.m_sStr));
            m_rt.m_rtSave.m_sStr[0][14]=NULL;
            m_rt.m_rtSave.m_sStr[1][14]=NULL;

//			}
			for(i=0;i<NMBOFSPL;i++)
			{
				j=10;
				if(fabs(m_rt.m_rtSave.m_fPtc[i][j]-1.0)<1e-2||fabs(m_rt.m_rtSave.m_fPtc[i][j]-0.01)<1e-2)
					m_rt.m_rtSave.m_bChannels[i]=0;//		LoadChannels(i,FALSE);

				else
					m_rt.m_rtSave.m_bChannels[i]=1;//LoadChannels(i,TRUE);	
			}

	  		for(i=0;i<30;i++)
			{
				if(m_rt.m_rtSave.m_bChannels[i]==TRUE)
				{
					m_rt.Calculation(i);
				}
			}
			
			for(i=0;i<30;i++)
			{
				if(m_rt.m_rtSave.m_bChannels[i]==TRUE)
				{
					LoadIndex(i);
					break;
				}
			}
						OpenFlag=TRUE;

		}
			catch(CArchiveException* theException)
			{
				TCHAR str[255];
				theException->GetErrorMessage(str,255);
				MessageBox(GetActiveWindow(),str, "警告",MB_OK);
				UpdateAllViews(NULL);
			}
			
	}
}
//	ar.Close();//oyj11-11

}

/////////////////////////////////////////////////////////////////////////////
// CPtcrDoc监测

#ifdef _DEBUG
void CPtcrDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPtcrDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPtcrDoc 命令

//
//	将通道i载入多曲线目录Index内
//
void CPtcrDoc::LoadIndex(int i)
{
	m_rt.m_DrawDotFlag=FALSE;//oyj 10-15为拟合曲线而写
	m_iIndex=i;
}
//
//	获取多曲线目录内通道号
//
int CPtcrDoc::GetIndex()
{
	return m_iIndex;
}

//
//	“工具->合并”选项设置可用
//
void CPtcrDoc::OnUpdateToolConbind(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();	
}

//
//	进行文件类型转换(txt)
//
void CPtcrDoc::OnToolConvert() 
{
	// TODO: Add your command handler code here
	int i,j;
	CString str;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"阻温数据文件(*.RT)|*.RT");
	
	if(dlg.DoModal()==IDOK)
	{
		str=dlg.GetFileName();
		CFile file(str,CFile::modeRead);
		CArchive ar(&file,CArchive::load);
		Serialize(ar);
		file.Close();
		
		if(OpenFlag==TRUE)
		{
			OpenFlag=FALSE;
			str.Format("%s.txt",str.Left(str.GetLength()-3));
			CFile txtfile(str,CFile::modeCreate|CFile::modeWrite);
			for(i=0;i<NMBOFSPL;i++)
				for(j=0;j<MAXOFSPL;j++)
				{
					str.Format("%.2f\t,%.2f\t\r\n",m_rt.m_rtSave.m_fTem[i][j],m_rt.m_rtSave.m_fPtc[i][j]);
					txtfile.Write(str,str.GetLength());
				}

			txtfile.Close();
		}
	}
}

//
//	进行文件类型转换(xls)
//
void CPtcrDoc::OnToolConvertExcel() 
{
	// TODO: Add your command handler code here
	int i,j;
	CString str,str_SavePath;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"阻温数据文件(*.RT)|*.RT");
//	CFileDialog save_dlg(FALSE,"xls",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Excel(*.xls)|*.xls");
	
	dlg.DoModal();
	
		str=dlg.GetPathName();/*修改部分*/
		CFile file(str,CFile::modeRead);
		CArchive ar(&file,CArchive::load);
		Serialize(ar);
		file.Close();
		
		if(OpenFlag==TRUE)
		{
			OpenFlag=FALSE;
			str=dlg.GetFileTitle();
			str.Format("%s.xls",str);
			CFileDialog save_dlg(FALSE,"xls",str,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Excel(*.xls)|*.xls");
			save_dlg.DoModal();
			str_SavePath=save_dlg.GetPathName();
//			CFile xlsfile(str,CFile::modeCreate|CFile::modeWrite);
			CFile xlsfile(str_SavePath,CFile::modeCreate|CFile::modeWrite);
/*
			for(i=0;i<NMBOFSPL;i++)
			{
				if(m_rt.m_rtSave.m_bChannels[i]==1)
				{
					str.Format("通道%d\t\t",i+1);
 					xlsfile.Write(str,str.GetLength());
				}
			}
			str.Format("\r\n");
 			xlsfile.Write(str,str.GetLength());
			for(i=0;i<NMBOFSPL;i++)
			{
				if(m_rt.m_rtSave.m_bChannels[i]==1)
				{
					str.Format("温度/℃\t阻值/Ω\t");
 					xlsfile.Write(str,str.GetLength());
				}
			}
			str.Format("\r\n");
 			xlsfile.Write(str,str.GetLength());
			for(j=0;j<MAXOFSPL;j++)
			{
				if(m_rt.m_rtSave.m_fTem[0][j]!=0)
				{
					for(i=0;i<NMBOFSPL;i++)
					{
						if(m_rt.m_rtSave.m_bChannels[i]==1)
						{
							str.Format("%.2f\t%.2f\t",m_rt.m_rtSave.m_fTem[i][j],m_rt.m_rtSave.m_fPtc[i][j]);
							xlsfile.Write(str,str.GetLength());
						}
					}
					str.Format("\r\n");
					xlsfile.Write(str,str.GetLength());
				}
			}
*/
//表头
			str.Format("通道\t起始阻值（Ω）\tR25（Ω）\tRmin（Ω）\t最小阻值对应温度（℃）\tTc25（℃）\t");
 			xlsfile.Write(str,str.GetLength());
			str.Format("Tc（℃）\t温度系数（10/25）\t温度系数（15/25）\t温度系数（0/15）\t居里温区\t升阻比（℃）\tRmin/R25\t\t温度（℃）\t");
 			xlsfile.Write(str,str.GetLength());
			for(j=0;j<MAXOFSPL;j++)
			{
				if(m_rt.m_rtSave.m_fTem[0][j]!=0)
				{
					str.Format("%.2f\t",m_rt.m_rtSave.m_fTem[0][j]);
 					xlsfile.Write(str,str.GetLength());
				}

			}
			str.Format("\n");
			xlsfile.Write(str,str.GetLength());
//内容

			for(i=0;i<NMBOFSPL;i++)
			{
				if(m_rt.m_rtSave.m_bChannels[i]==1)
				{
					str.Format("%d\t",i+1);										//通道号
 					xlsfile.Write(str,str.GetLength());
					str.Format("%.2f\t",(float)pow(10.0,m_rt.GetStartRes0(i)));	//起始阻值
 					xlsfile.Write(str,str.GetLength());
					if(m_rt.GetStartTem0(i)<=25)								//R25
					{
						str.Format("%.2f\t",(float)m_rt.GetRes25(i));	
 						xlsfile.Write(str,str.GetLength());
					}
					else
					{
						str.Format("——\t");
 						xlsfile.Write(str,str.GetLength());
					}
					str.Format("%.2f\t",(float)m_rt.GetResMin(i));				//Rmin
 					xlsfile.Write(str,str.GetLength());
					str.Format("%.2f\t",(float)m_rt.GetTemMin(i));				//最小阻值对应温度
 					xlsfile.Write(str,str.GetLength());
					str.Format("%.2f\t",(float)m_rt.m_fTemCur2R25[i]);			//Tc25
 					xlsfile.Write(str,str.GetLength());
					str.Format("%.2f\t",(float)m_rt.GetTemCurie(i));			//Tc
 					xlsfile.Write(str,str.GetLength());
					str.Format("%.2f%%\t",(float)m_rt.GetTemCoe10(i));			//温度系数（10/25）
 					xlsfile.Write(str,str.GetLength());
					str.Format("%.2f%%\t",(float)m_rt.GetTemCoe25(i));			//温度系数（15/25）
 					xlsfile.Write(str,str.GetLength());
					str.Format("%.2f%%\t",(float)m_rt.GetTemCoe50(i));			//温度系数（0/15）
 					xlsfile.Write(str,str.GetLength());
					str.Format("%.2f\t",(float)m_rt.GetCurieRange(i));			//居里温区
 					xlsfile.Write(str,str.GetLength());
					str.Format("%.2f\t",(float)m_rt.GetResRatio(i));			//升阻比
 					xlsfile.Write(str,str.GetLength());
					if(m_rt.GetStartTem0(i)<=25)				 				//Rmin/R25
					{
						str.Format("%.4f\t\t",(float)m_rt.GetResMin(i)/(float)m_rt.GetRes25(i));	
 						xlsfile.Write(str,str.GetLength());
					}
					else
					{
						str.Format("1\t\t");
 						xlsfile.Write(str,str.GetLength());
					}
					str.Format("阻值（Ω）\t");									//阻值
 					xlsfile.Write(str,str.GetLength());
					for(j=0;j<MAXOFSPL;j++)
					{
						if(m_rt.m_rtSave.m_fTem[0][j]!=0)
						{
							str.Format("%.2f\t",m_rt.m_rtSave.m_fPtc[i][j]);
 							xlsfile.Write(str,str.GetLength());
						}
					}

					str.Format("\n");
 					xlsfile.Write(str,str.GetLength());
				}
			}
			xlsfile.Close();
			AfxMessageBox("成功1？");
		}
		AfxMessageBox("成功2？");
	
	AfxMessageBox("成功3？");
}

//
//	设置“工具->dat—>txt”选项设置可用
//
void CPtcrDoc::OnUpdateToolConvert(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

//
//	设置“工具->dat—>xls”选项设置可用
//
void CPtcrDoc::OnUpdateToolConvertExcel(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

//
//	根据通讯协议修改命令cmd并写入测试仪器，读取wCount个数据加到字符串result内，时间限制为wTime。
//
bool CPtcrDoc::ReadPvsv(char * cmd, char * results, int wTime, int wCount,int Sr253BCC)
{
	//参数初始化
	int count=0;
	CTime ct1,ct2;
	CTimeSpan cts;
    MSG msg;

//	char cmd[100];
	char buf[100];
	unsigned char STX=2,ETX=3,EOT=4,ENQ=5,ACK=6,NAK=15;
	unsigned char CR=13,etxETX=0x3A;//etxETX==0x3A ":" zjun
char Addr[]="01";
char CmdAddr[100];

 	
	AfxGetApp()->DoWaitCursor(1);	//显示等待光标
 
	if (Sr253BCC==6) {//使用万能表
	while(count<wCount)
	{
        ::PostMessage(AfxGetMainWnd()->m_hWnd,WM_COMM_RXLINE,1,1);
	    GetMessage(&msg, NULL, 0, 0);
        m_sPortF45.m_rxdata.count=0;
        m_sPortF45.m_rxdata.theend=FALSE;
        m_sPortF45.m_rxdata.Sr253BCC=Sr253BCC;
		memset(m_sPortF45.m_rxdata.results,0,sizeof(m_sPortF45.m_rxdata.results));
		m_sPortF45.WriteToPort(cmd);	//向万用表写cmd命令
        ct1=CTime::GetCurrentTime();	//获取当前系统时间
		while(1)
		{
			if(m_sPortF45.m_rxdata.theend)	//若当前数据获取结束
			{
				strcpy(results,m_sPortF45.m_rxdata.results);	//将获取的数据结果存入result内
	            return TRUE;
	/*zjun				if(Verify(results,Sr253BCC))
				{
                	AfxGetApp()->DoWaitCursor(-1);
 					return TRUE;
				}
				else
					break;
	*/
			}
			
			  else
			{
				ct2=CTime::GetCurrentTime();
				cts=ct2-ct1;
				if(cts.GetTotalSeconds()>=wTime)	//若获取单个数据的等待时间超过wTime，准备接收下一个数据
					break;
			}
		}
		if(m_sPortF45.dwError==997){	//若错误代码为997
			if(strstr(cmd,"REM")){		//若命令内包含“REM”
				strcpy(results,"SET REMOTE");	//将“SET REMOTE”添加到结果内
			}
			return TRUE;}
       count++;
	}
			}//endif
 
	else if(Sr253BCC==2){	//使用温控表，通讯协议SR253

	memset(&buf, 0, sizeof(buf));

		memset(&CmdAddr, 0, sizeof(CmdAddr));
		CmdAddr[0]=EOT;	
		m_sPort.WriteToPort(CmdAddr);//close communication line	
		Sleep(500);
		memset(&CmdAddr, 0, sizeof(CmdAddr));
	CmdAddr[0]=EOT;
	strcat(CmdAddr,Addr);
	CmdAddr[strlen(CmdAddr)]=ENQ;

	m_sPort.WriteToPort(CmdAddr);	
		Sleep(1000);

memset(&CmdAddr, 0, sizeof(CmdAddr));

//strcpy(cmd,buf);
CmdAddr[0]=STX;
strcat(CmdAddr,cmd);
int aaa;
aaa=strlen(CmdAddr);
CmdAddr[aaa]=ETX;
//strcpy(cmd,CmdAddr);
cmd=CmdAddr;

//按SR253通讯协议修改cmd的格式	

		AddCrc(cmd,Sr253BCC);//计算并将CRC校验位添加在命令末尾
	while(count<wCount)
		{
        ::PostMessage(AfxGetMainWnd()->m_hWnd,WM_COMM_RXLINE,1,1);
	    GetMessage(&msg, NULL, 0, 0);
        m_sPort.m_rxdata.count=0;
        m_sPort.m_rxdata.theend=FALSE;
		memset(m_sPort.m_rxdata.results,0,sizeof(m_sPort.m_rxdata.results));
   	m_sPort.WriteToPort(cmd);	//命令cmd写入温控表内
	ct1=CTime::GetCurrentTime();	//获取当前系统时间
		while(1)
		{
			if(m_sPort.m_rxdata.theend)	//若当前数据获取结束
			{
				strcpy(results,m_sPort.m_rxdata.results);	//将获取数据结果添加到result内
				if(Verify(results,Sr253BCC))	//若获取的结果结构争正确且有效
				{
                	AfxGetApp()->DoWaitCursor(-1);	//等待光标结束

					return TRUE;
				}
				else
					break;
			}
			else
			{
				ct2=CTime::GetCurrentTime();
				cts=ct2-ct1;
				if(cts.GetTotalSeconds()>=wTime)	//若获取单个数据的等待时间超过wTime，准备接收下一个数据
					break;
			}
		}
		count++;
 	m_sPort.m_SPAvailable=0;
if(m_sPort.InitPort(m_sPort.m_pOwner))	//检查温控表通讯状态，若成功
	{
		m_sPort.StartMonitoring();	//继续串口监控
		AfxGetApp()->DoWaitCursor(1);	//显示等待光标
	}

	}
	
	}

else if(Sr253BCC==8){


memset(&CmdAddr, 0, sizeof(CmdAddr));

//strcpy(cmd,buf);
CmdAddr[0]='@';
strcat(CmdAddr,cmd);
int aaa;
aaa=strlen(CmdAddr);
CmdAddr[aaa]=ETX;
//strcpy(cmd,CmdAddr);//STX+CMD+ETX +BCC+CRLF
cmd=CmdAddr;

//	修改命令cmd格式	

		AddCrc(cmd,Sr253BCC);//计算并添加CRC校验位

	while(count<wCount)
		{
        ::PostMessage(AfxGetMainWnd()->m_hWnd,WM_COMM_RXLINE,1,1);
	    GetMessage(&msg, NULL, 0, 0);
        m_sPort.m_rxdata.count=0;
        m_sPort.m_rxdata.theend=FALSE;
		memset(m_sPort.m_rxdata.results,0,sizeof(m_sPort.m_rxdata.results));
//		m_sPort.WriteToPort(cmd);
   	m_sPort.WriteToPort(cmd); 
	ct1=CTime::GetCurrentTime();
		while(1)
		{
			if(m_sPort.m_rxdata.theend)
			{
				strcpy(results,m_sPort.m_rxdata.results);
				if(Verify(results,Sr253BCC))
				{
                	AfxGetApp()->DoWaitCursor(-1);

					return TRUE;
				}
				else
					break;
			}
			else
			{
				ct2=CTime::GetCurrentTime();
				cts=ct2-ct1;
				if(cts.GetTotalSeconds()>=wTime)
					break;
			}
		}
		count++;
 	m_sPort.m_SPAvailable=0;
if(m_sPort.InitPort(m_sPort.m_pOwner))
	{
		m_sPort.StartMonitoring();
//		MessageBox("温控表通讯成功!","提示",MB_OK);	
	AfxGetApp()->DoWaitCursor(1);
	}

	}
	
	}
	else if(Sr253BCC==4){//温控表：协议SR93
       if(strstr(cmd,"DS"))
        strcpy(cmd,"011R01005");
       else if(strstr(cmd,"SV"))
        strcpy(cmd,"011R01010");
       else if(strstr(cmd,"AT E"))
        strcpy(cmd,"011W01840,0001");
       else if(strstr(cmd,"AT S"))
        strcpy(cmd,"011W01840,0000");
       else if(strstr(cmd,"CM C"))
        strcpy(cmd,"011W018C0,0001");
       else if(strstr(cmd,"CM L"))
        strcpy(cmd,"011W018C0,0000");
       else if(strstr(cmd,"DP")){
         if(m_sPort.m_rxdata.sr==93)
           strcpy(cmd,"011R07070");
         else if(m_sPort.m_rxdata.sr==83)
           strcpy(cmd,"011R01130");
         else if(m_sPort.m_rxdata.sr==13)
           strcpy(cmd,"011R01130");
         else if(m_sPort.m_rxdata.sr==253)
           strcpy(cmd,"011R01130");
	   }

	memset(&CmdAddr, 0, sizeof(CmdAddr));
    //strcpy(cmd,buf);
    CmdAddr[0]='@';
    strcat(CmdAddr,cmd);
    int aaa;
    aaa=strlen(CmdAddr);
    CmdAddr[aaa]=':';
    //strcpy(cmd,CmdAddr);//STX+CMD+ETX +BCC+CRLF
     cmd=CmdAddr;
	 //修改cmd格式
	AddCrc(cmd,Sr253BCC);//计算并添加CRC校验位
	while(count<wCount)
		{
        ::PostMessage(AfxGetMainWnd()->m_hWnd,WM_COMM_RXLINE,1,1);
	    GetMessage(&msg, NULL, 0, 0);
        m_sPort.m_rxdata.count=0;
        m_sPort.m_rxdata.theend=FALSE;
		memset(m_sPort.m_rxdata.results,0,sizeof(m_sPort.m_rxdata.results));
		m_sPort.WriteToPort(cmd);
        ct1=CTime::GetCurrentTime();
		while(1)
		{
			if(m_sPort.m_rxdata.theend)
			{
				strcpy(results,m_sPort.m_rxdata.results);
				if(Verify(results,Sr253BCC))
				{
                	AfxGetApp()->DoWaitCursor(-1);

					return TRUE;
				}
				else
					break;
			}
			else
			{
				ct2=CTime::GetCurrentTime();
				cts=ct2-ct1;
				if(cts.GetTotalSeconds()>=wTime)
					break;
			}
		}
		count++;
	}
  }//end else
   
	AfxGetApp()->DoWaitCursor(-1);
    return FALSE;
}

//
//	计算CRC校验位
//
void CPtcrDoc::CalculateCRC(char *buf,char *crc,int Sr253BCC)
{
	//int Sr253BCC=2;

	char *pos;
int l;
	int i;
	int chtmp;

	if((Sr253BCC==1)||(Sr253BCC==4)){ //ADD STX-ETX-CR; BCC: ADD
 
//		例：
//STX    0     1     1     R     0     1     0     0     9     EXT    E    3   CR   LF
//(02H)+(30H)+(31H)+(31H)+(52H)+(30H)+(31H)+(30H)+(30H)+(39H)+（03H）=1E3H          
//BCC校验结果   ⒀："E"=45H         ⒁："3"=33H

		
		chtmp=0;
	l=(int)strlen(buf); 
	for(i=0;i<=l;i++){
			chtmp=chtmp + buf[i];
	}
       chtmp=chtmp%256;

	    if(chtmp/16<10) 
			crc[0]=chtmp/16+0x30;
		else 
			crc[0]=chtmp/16-10+0x41;
	    if(chtmp%16<10) 
			crc[1]=chtmp%16+0x30;
		else 
			crc[1]=chtmp%16-10+0x41;
		crc[2]=0;
return;
	}
	if((pos=strchr(buf,':'))!=NULL)
	{
		chtmp=0;
		for(i=1;i<=pos-buf;i++){
			chtmp=chtmp ^ buf[i];
		}
	
 	    if(chtmp/16<10) 
			crc[0]=chtmp/16+0x30;
		else 
			crc[0]=chtmp/16-10+0x41;
	    if(chtmp%16<10) 
			crc[1]=chtmp%16+0x30;
		else 
			crc[1]=chtmp%16-10+0x41;
		crc[2]=0;
return;
	}
	if((Sr253BCC==1)||(Sr253BCC==4)){ //ADD STX-ETX-CR; BCC: ADD
 
//		例：
//STX    0     1     1     R     0     1     0     0     9     EXT    E    3   CR   LF
//(02H)+(30H)+(31H)+(31H)+(52H)+(30H)+(31H)+(30H)+(30H)+(39H)+（03H）=1E3H          
//BCC校验结果   ⒀："E"=45H         ⒁："3"=33H

		
		chtmp=0;
	l=(int)strlen(buf); 
	for(i=0;i<=l;i++){
			chtmp=chtmp + buf[i];
	}
       chtmp=chtmp%256;

	    if(chtmp/16<10) 
			crc[0]=chtmp/16+0x30;
		else 
			crc[0]=chtmp/16-10+0x41;
	    if(chtmp%16<10) 
			crc[1]=chtmp%16+0x30;
		else 
			crc[1]=chtmp%16-10+0x41;
		crc[2]=0;
return;
	}

	if(Sr253BCC==2) { //ADD STX-ETX-CR; BCC: ADD
		chtmp=0;
	l=(int)strlen(buf); 
	for(i=1;i<=l;i++){
			chtmp=chtmp + buf[i];
	}
       chtmp=chtmp%128;


	   crc[0]=chtmp;
	   crc[2]=NULL;

	   return;
	}

	return;
}

//
//	计算并将校验位添加在cmd末尾
//
void CPtcrDoc::AddCrc(char * cmd,int Sr253BCC)
{
    char crc[3];
	char *pos;
	int l;

	CalculateCRC(cmd,crc,Sr253BCC);

//	int Sr253BCC=2; //Sr253=1 STX-ETX-CR;BCC ADD;
	            //Sr253=2 STX-ETX;BCC ADD;
	            //

	if((Sr253BCC==1)||(Sr253BCC==4)){//Sr253=4,SR93 STX-ETX-CR;BCC ADD;

		l=strlen(cmd);
		cmd[l]=crc[0];
		cmd[l+1]=crc[1];
		cmd[l+2]='\r';
//		cmd[l+3]='\n';

return;
	} 
	if(Sr253BCC==2){
		l=strlen(cmd);
		cmd[l]=crc[0];
		cmd[l+1]=NULL;
return;
	} 
	else{ pos=strchr(cmd,':');
	*(pos+1)=crc[0];
	*(pos+2)=crc[1];
	*(pos+3)='\r';
	*(pos+4)=0;
	}
    return ;
}

//
//	检查命令字符串strS是否符合规范（有效）
//
bool CPtcrDoc::Verify(char * strS,int Sr253BCC)
{
   	char *pos;
    char crc[3];
	if(strstr(strS,"ER"))
		return FALSE;

	if(Sr253BCC==6){
		if((pos=strchr(strS,'='))!=NULL) return TRUE;
		else 
			return FALSE;
	}

	if(Sr253BCC==2){
		if(((pos=strchr(strS,3))!=NULL)||((pos=strchr(strS,6))!=NULL)||((pos=strchr(strS,15))!=NULL)) return TRUE;
		else
			return FALSE;
	}

	if(Sr253BCC==4){
		if((strS[5]='0')&&(strS[6]='0')) return TRUE;
		else
			return FALSE;
	}


	if((pos=strchr(strS,':'))!=NULL)
	{
        CalculateCRC(strS,crc,Sr253BCC);
		pos++;
        if((*pos==crc[0])&&(*(pos+1)==crc[1]))
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
}

//
//	将result内读取到的数据存到数组buftmp内
//
int CPtcrDoc::Splint(char buftmp[10][35], char *results, int Sr253BCC)
{
    int i,j;
	char *pos;

   if(Sr253BCC==2){
	if((pos=strstr(results,"DS"))==NULL)return FALSE;
   pos++;
   pos++;
   i=0;j=0;
	for(;;)
	{
		while((*pos!=','))
		{
			if(*pos==' ')
			{
				pos++;
				continue;
			}
			buftmp[i][j]=*pos++;
			j++;if(j>14)break;
		}
		buftmp[i][j]=0;
		if(*pos==0)
			break;
		pos++;i++;j=0;if(i>9)break;
	}
	return (i+1);
	}
   else if(Sr253BCC==4){//sr93
	if((pos=strstr(results,"00,"))==NULL)return FALSE;
   pos++;
   pos++;
   pos++;
 //  i=0;j=0;
for(i=0;i<9;i++)
{
	for(j=0;j<4;j++)
	{		if(*pos==0)
			      break;
		buftmp[i][j]=*pos++;

	}
  buftmp[i][j]=0;
		if(*pos==0)
			      break;
}
   return (i+1);
	}
   else if((Sr253BCC==6)&&(MultiMeter==2)){
//TH2512
			if((pos=strchr(results,'='))==NULL)
			 return FALSE;
        pos++;
//        pos++;
        pos=strstr(results,"= ");
		pos++;
	if(pos==NULL)return FALSE;
	i=0;j=0;
	for(;;)
	{
		while((*pos!='\r'))
		{
			if(*pos==' ')
			{
				pos++;
				continue;
			}
			buftmp[i][j]=*pos++;
			j++;if(j>14)break;
		}
		buftmp[i][j]=0;
		if(*pos==0)
			break;
		pos++;i++;j=0;if(i>2)break;
	}
   strcpy(buftmp[1],buftmp[0]);
	return (i+1);
	} 
   else if((Sr253BCC==6)&&(MultiMeter==1)){
//FLUKE45   
			if((pos=strstr(results,"MEAS?"))==NULL)
			 return FALSE;
 
       i=0;j=0;
	for(;;)
	{
		while((*pos!='\n'))
		{
			if(*pos==' ')
			{
				pos++;
				continue;
			}
			buftmp[i][j]=*pos++;
			j++;if(j>14)break;
		}
		buftmp[i][j-1]=0;
		if(*pos==0)
			break;
		pos++;i++;j=0;if(i>2)break;
	}
	return (i+1);
	} 
   else if((Sr253BCC==6)&&(MultiMeter==4)){
//HP34401A   
	//		if((pos=strstr(results,"MEAS?"))==NULL)
	//		 return FALSE;
 i=3;
		strcpy(buftmp[0],results);
		strcpy(buftmp[1],results);
	return (i+1);
	} 
   else if((Sr253BCC==6)&&(MultiMeter==5)){
//Keith2000  
	//		if((pos=strstr(results,"MEAS?"))==NULL)
	//		 return FALSE;
 i=3;
		strcpy(buftmp[0],results);
		strcpy(buftmp[1],results);
	return (i+1);
	}   
   else if((Sr253BCC==6)&&(MultiMeter==3)){
//ESCORT 3146A   
			if((pos=strstr(results,"R1"))==NULL)
			 return FALSE;
 
       i=0;j=0;
	for(;;)
	{
		while((*pos!='\r'))
		{
			if((*pos=='\n')||(*pos==' '))
			{
				pos++;
				continue;
			}
			buftmp[i][j]=*pos++;
			j++;if(j>14)break;
		}
		buftmp[i][j]=0;
		if(*pos==0)
			break;
		pos++;i++;j=0;if(i>2)break;
	}
	return (i+1);
	} 



 else return(-1);
}

//
//	打开“保存”对话框
//
void CPtcrDoc::OnFileSave() 
{
	// TODO: Add your command handler code here
		if (!DoSave(m_strPathName))
		{
			MessageBox(NULL,"保存文件失败!","PTCR R_T",MB_OK);
		}
	return ;	
}

//
//	串口输出通道编号ch1值
//
void CPtcrDoc::OutChan(int ch1)
{
   int ch[]={4,3,2,1,5,6,7,8,17,18,19,20,21,22,23,24,1,2,3,4,5,6,7,8,17,18,19,20,21,22,23,24};

	if(m_HT12D==1)OutChanHT12D(ch1);
	else {
		if(w2w4==0) OutChan8255(ch1);
	    else {//ch1=16;
		      OutChan8255(ch[ch1-1]);
		}
	
	}
}

//
//	根据客户与ch值，向a口输出编码后的值
//
void CPtcrDoc::OutChanHT12D(int ch1)
{
   // int ch[]={4,3,2,1,5,6,7,8,20,19,18,17,21,22,23,24,9,10,11,15,14,13,12,16,25,26,27,31,30,29,28,32};
   // int ch[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,9,10,11,15,14,13,12,16,25,26,27,31,30,29,28,32};
//keter   int ch[]={1,7,2,8,13,3,9,4,10,5,11,6,12,14,15,16,9,10,11,15,14,13,12,16,25,26,27,31,30,29,28,32};

	int ch[]={1,2,3,4,5,6,7,8,17,18,19,20,21,22,23,24,9,10,11,12,13,14,15,16,25,26,27,28,29,30,31,32};

	int i,j,l;
	static cha=-1;

if(m_rt.client==5){//20工位HT12D
	ch[18]=25; 
	ch[19]=26;
}
if(m_rt.client==6){//4 wires HT12D

    for(i=0;i<16;i++)
		ch[i]=i+1;

}//   ch1=10;
     if(m_rt.client==8){//4 wires HT12D

       for(i=0;i<16;i++)
		ch[i]=i+1;
       for(i=9;i<16;i++)
		ch[i]=i;
	    ch[8]=16;
	  }

  	  if(m_rt.client==11){
          for(i=0;i<7;i++)
			      ch[i]=i+17;
          for(i=8;i<15;i++)
			      ch[i]=i-7;
	  } 
		  ch1=ch[ch1-1]-1;
       l=ch1/16;

if(cha!=(ch[ch1-1]))
	if(l==1)codd12(4,1);
	else codd12(4,0);

      ch1=ch1-l*16;


	  for(i=0;i<4;i++ )	{  if(i==ch1/4)continue;
                     codd12(i,0);
	  }

	  i=ch1/4;
			j=ch1-4*i;
			codd12(i,1<<j);
       cha=ch[ch1+l*16];

}

//
//	向a口输出nb、da编码后的值
//
void CPtcrDoc::codd12(int nb,char da)
{	int i,j,k,l;
	unsigned char asd[2][3]={0,1,1,0,0,1};
	for(l=0;l<2;l++) {
	for(i=0;i<4;i++) {
	   for(j=0;j<35;j++) outa12(0);
			     outa12(1);
	      for(j=0;j<8;j++)
		 for(k=0;k<3;k++) outa12( asd[(nb>>j)&1][k]);
	      for(j=0;j<4;j++)
		 for(k=0;k<3;k++) outa12( asd[(da>>j)&1][k]);
		}
		outa12(0);
		}
}

//
//	向a端口（888）输出j
//
void CPtcrDoc::outa12(int j)
{	long ii;
unsigned short D37a;
long fshe_yanshi1=55000;
int a=0x378,b=0x379,c=0x37a;
unsigned char d378=0;

	D37a=(D37a&0xfe)|j;
	_outp(a,D37a);
	for(ii=0;ii<fshe_yanshi1;ii++);
}

//
//	根据ch高位SetC，根据ch低3位向PA、PB输出相应值
//
void CPtcrDoc::OutChan8255(int ch)
{  int i,j;
 
   i=(int)((ch-1)/8);
   j=(ch-1)%8;

 
   if(i==0){
      SetC(0,0);
      _outp(PB,0);
      _outp(PA,1<<j);
   }
   if(i==1){
  SetC(0,1);
      _outp(PB,0);
      _outp(PA,1<<j);
   }

   if(i==2){
      SetC(0,0);
      _outp(PA,0);
      _outp(PB,1<<j);
   }
   if(i==3){
  SetC(0,1);
      _outp(PA,0);
      _outp(PB,1<<j);
   }
}

//
//	开关选定端口：向PCNTRL口输出通道号与操作值
//
void CPtcrDoc::SetC(int ch,int set)
{  int i=0;
      i=(ch<<1)+set;
      _outp(PCNTRL,i);
}

//
//	初始化8253
//
void CPtcrDoc::Init8253(void)
{
  _outp(TCNTRL,0x34);    /* Counter 0, load LSB and MSB, mode 2, Hex code */
  _outp(TCNTRL,0x74);    /* Counter 1, load LSB and MSB, mode 2, Hex code */
  _outp(TCNTRL,0xbf);    /* Counter 2, load LSB and MSB, mode 3, BCD code */

  _outp(CNT2,0);
  _outp(CNT2,0x10);      /*1 MHz wave to 1 kHz square wave;BCD code*/
  /*_outp(CNT2,0x20);2 MHz wave to 1 kHz square wave */

   _outp(PCNTRL,0x80);  /*Initialize 8255: mode 0, PA,PB,PC:output port */

/*   SetC(2,1);*/
   SetC(2,0);

   KP=1.8;
   KD=4.0;
   KI=30;
   HeatLimit=60;
   HeatRate=40;
   HeatStep=40;/*Limit for Heat;tt/HeatRate Lowest Heat*/

}

//
//	发出“停止加热”信号
//
void CPtcrDoc::StopHeat(void)
{
   _outp(PCNTRL,0x80);  /*Initialize 8255: mode 0, PA,PB,PC:output port */
  Init8253();
  SetC(7,1);

  SetC(2,1);
  DelayTime(2);
  SetC(2,0);
  SetC(2,1);
   /*open the 12V relay*/
}

//
//	计算加热时间
//
int CPtcrDoc::TempRange(float tm)
{
    int bb,ted;

    ted=(int)tm;
    bb=(ted-1)/HeatRate;
    if(HeatRate>200){bb=1;HeatStep=HeatLimit;}
    bb=bb<1 ? 1 : bb;

    return bb;
}

//
//	根据温度差diff和误差值b，计算加热信号wvn（占空比）
//
int CPtcrDoc::Pid(int diff,int b)
{
    float ctlv;
    static int e[2]={0,0};
    static int u[2]={0,0};
/*    static float ia;*/
    float ti=500,td=200,ts=20;

    KI=KP*ts/ti;
    KD=KP*td/ts;

   u[1]=u[0]+KP*(diff-e[1])+KI*diff+KD*((diff-e[1])-(e[1]-e[0]));
   ctlv=(int)u[1];
/*
    ctlv = KP*(float)e[1] + KD*(float)da + (float)b;
*/
    ctlv = ctlv<1 ? 1 : ctlv;
    ctlv = ctlv>HeatLimit ? HeatLimit : ctlv;
    ctlv = ctlv>(b+HeatStep) ? (b+HeatStep) : ctlv;
	e[0]=e[1];
	e[1]=diff;
	u[0]=u[1];

    return (int)ctlv;
}

//
//	发出“加热”信号
//
void CPtcrDoc::Heat(int wn)
{                      /*    wn = 1,2,...,99  */
    unsigned char xl,xh,yl,yh;
    unsigned int x,y;

// Init8253();
 if(wn==0) SetC(7,1);//unenable 74LS76
 else SetC(7,0);//enable 74LS76

    y=wn*10;
    x=1000-y;

    xl=x & 0xff;
    xh=(x>>8) & 0xff;
    yl=y & 0xff;
    yh=(y>>8) & 0xff;

    _outp(CNT0,xl);
    _outp(CNT0,xh);
    _outp(CNT1,yl);
    _outp(CNT1,yh);
}

//
//	计算加热时间
//
float CPtcrDoc::Temperature(float Resistance0,float tt00)
{
    double at=-5.802e-7,bt=3.90802e-3,ct=1;
    double ct0,ct2;
    float ttt0;

    ct0=(double)(4.0*at*((ct*100.0)-Resistance0)/100.0);
    ct2=sqrt( (double)((bt*bt)-ct0));
 if(ZWX==1)
    ttt0=(float)((-bt+ct2) / (2.0*at)+m_Tempvias);
 else
    ttt0=(float)((-bt+ct2) / (2.0*at)+tt00);

    return ttt0;
}

//
//	从温控表获取并保存PV、SV等数据
//
void CPtcrDoc::ReadSr253() 
{
	// TODO: Add your control notification handler code here
int Sr253BCC;
char results[128];
char buftmp[10][35];

int Read[10];

  char cmd[80]="DS";
 
 Sr253BCC=m_sPort.m_rxdata.Sr253BCC;
 // Sr253BCC=m_sPort.m_rxdata.Sr253BCC;
 if(Sr253BCC==2) { 
	ReadPvsv(cmd,results,4,3,Sr253BCC);

    Splint(buftmp,results,Sr253BCC);
      m_PV=atof(buftmp[0]);
        m_SV=atof(buftmp[2]);
        m_rt.m_tSr253=m_PV;       
        m_SvNum=atoi(buftmp[1]);
        m_rt.m_PV=m_PV;
        m_rt.m_SV=m_SV;

	 if((m_PV>450)||(m_PV==0)){//超量程，可能是仪表通讯不正常
		 //重新初始化
	 	m_sPort.m_SPAvailable=0;
        if(m_sPort.InitPort(m_sPort.m_pOwner))
		{
	       m_sPort.StartMonitoring();
	       AfxGetApp()->DoWaitCursor(1);
		}	
	ReadPvsv(cmd,results,4,3,Sr253BCC);

    Splint(buftmp,results,Sr253BCC);
      m_PV=atof(buftmp[0]);
        m_SV=atof(buftmp[2]);
        m_rt.m_tSr253=m_PV;       
        m_SvNum=atoi(buftmp[1]);
        m_rt.m_PV=m_PV;
        m_rt.m_SV=m_SV;
	 }

//zjun
    	m_Pt100=m_PV;
		m_rt.m_tPt100=m_PV;
//zjun
        if(Pt100Chan_1==-1){
			m_Pt100_1=m_PV;
			m_Pt100_2=m_PV;
		}
  return;
 }
  if(Sr253BCC==4) 
  {	 	
  int DP=0; 

//  DP=SrRead("DP",Read);//"011R07070"

  
 //   DP=SrRead("DP",Read);//"011R07070"
     DP=SrRead("DP",Read);//"011R07070"Sr93;"011R01130"
	 m_PV=SrRead("DS",Read)/pow(10.0,DP); //"011R01000"
     m_SV=Read[1]/pow(10.0,DP); //"011R01000"
	 if((m_PV>450)||(m_PV<=0)){//超量程，可能是仪表通讯不正常
		 //重新初始化
	 	m_sPort.m_SPAvailable=0;
        if(m_sPort.InitPort(m_sPort.m_pOwner))
		{
	       m_sPort.StartMonitoring();
	       AfxGetApp()->DoWaitCursor(1);
		}	
     DP=SrRead("DP",Read);//"011R07070"Sr93;"011R01130"
	 m_PV=SrRead("DS",Read)/pow(10.0,DP); //"011R01000"
     m_SV=Read[1]/pow(10.0,DP); //"011R01000"
 
	 }

   //   m_SV=SrRead("SV")/pow(10.0,DP);//"011R01010"

//        m_PV=SrRead("DS",Read)/pow(10.0,DP); //"011R01000"

  m_rt.m_tSr253=m_PV;       
        m_SvNum=1;
        m_rt.m_PV=m_PV;
        m_rt.m_SV=m_SV;

//zjun
	 	m_Pt100=m_PV;
     	m_rt.m_tPt100=m_PV;

		if(m_sPort.m_rxdata.sr!=13){
		if(Pt100Chan_1==-1){
			m_Pt100_1=m_Pt100;
			m_Pt100_2=m_Pt100;
		}
	}
	else {
       m_Pt100_1=SrRead("012R01005",Read)/pow(10.0,DP); //"012R01000"
       m_Pt100_2=SrRead("013R01005",Read)/pow(10.0,DP); //"013R01000"
	   
	}

		}
 m_rt.m_tPt100_1=m_Pt100_1;
 m_rt.m_tPt100_2=m_Pt100_2;
 m_rt.m_tPt100_3=(m_Pt100+m_Pt100_1+m_Pt100_2)/3;

  return;

}

//
//	延时函数
//
void CPtcrDoc::DelayTime(int sec)
{
	CTime ct1,ct2;
	CTimeSpan cts;

     ct1=CTime::GetCurrentTime();

	  while(1){
		  ct2=CTime::GetCurrentTime();
				cts=ct2-ct1;
				if(cts.GetTotalSeconds()>=sec)
					break;	
	  }
}

//
//	计算读取的n+1个阻值之和
//
float CPtcrDoc::ReadResiRepeat(int n) 
{
	// TODO: Add your control notification handler code here
    char *cmd="meas?\r\n";
  int i,j;
  float res[100];
  float rmin=0,rmax=0;
  float r=0;
  char results[128];
//  float r0;
 i=0;
        ReadResi(results);
		res[i]=m_Resistance;
        rmin=res[i];
		rmax=res[i];
        r=res[i];
	for(i=1;i<n+2;i++){
        ReadResi(results);
		res[i]=m_Resistance;
        r=r+res[i];
		if(res[i]>rmax)	rmax=res[i];
		if(res[i]<rmin) rmin=res[i];
	}

	for(j=0;j<n+2;j++){
		 for(i=0;i<n+1;i++){ //sorting
		if(res[i]<res[j]) {
			r=res[j];
			res[j]=res[i];
			res[i]=r;
		}
		 }
	}

	r=0;
	for(i=1;i<n+1;i++){
        r=r+res[i];
	}
 	m_Resistance=r/n;
		 if(MultiMeter==5){
	         cmd="MEAS?;:INIT:CONT ON\r\n";
	    	 ReadPvsv(cmd,results,4,3,m_sPortF45.m_rxdata.Sr253BCC);
		 }

	return m_Resistance;

}

//
//	获取字符串results且第一个数据写入m_Resistance，返回数据数
//
int CPtcrDoc::ReadResi(char * results) 
{//	char results[128];
   char *cmd="?\r";
   int Sr253BCC=6;
   int j;
   int i;
	char buftmp[10][35];
 
   if(MultiMeter==1)cmd="meas?\r\n";
   else if(MultiMeter==2)cmd="?\r\n";
   else if(MultiMeter==3)cmd="R1\r\n";
   else if(MultiMeter==4){
//	   if(w2w4==0)cmd="MEAS:RESISTANCE?\r\n";
	   if(w2w4==0)cmd="MEAS:RESISTANCE?\n";
       else cmd="MEAS:FRESISTANCE?\n";
   }
   else if(MultiMeter==5){
//zjun	   cmd="MEAS?;:INIT:CONT ON\r\n";

 	   cmd="MEAS?\r\n";
  } 
   else cmd="meas?\r\n";
     

	while(1){

	ReadPvsv(cmd,results,4,3,Sr253BCC);
		if((strstr(results,"E+37"))||(strstr(results,"E37"))){
			m_Resistance=m_rt.m_rtSave.m_SpecialR;
			return 5;
		}
		i=Splint(buftmp,results,Sr253BCC);
	break;
	if(i) break;
	}

      if(MultiMeter==1) m_Resistance=atof(buftmp[1]);

      else if(MultiMeter==2){
		if(strstr(results,"mO"))j=-3;
	    else if(strstr(results,"KO"))j=3;
	    else if(strstr(results,"MO"))j=6;
        else j=0;
//         m_Resistance=atof(buftmp[0]);//TH2512
        m_Resistance=atof(buftmp[0])*pow(10,j);//TH2512
		}
	  else if(MultiMeter==3) {
		   m_Resistance=atof(buftmp[1]);
	  }
	  else {//34401,K2000
		   m_Resistance=atof(buftmp[1]);
	  }
 return i;	
}

//
//	打开“另存为”窗口
//
void CPtcrDoc::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	CTime dt=CTime::GetCurrentTime();
	CString title=dt.Format("%Y%m%d.RT");
	SetTitle(title);
    SetPathName(title,FALSE);
//	m_SaveAs=TRUE;
      if (DoSave(NULL))
		m_SaveAs=TRUE;

}

//
//	计算拟合阻值
//
float CPtcrDoc::GetspecialRes( int j0, int j1 , int j2,float t)
{
 
	float a1,a2,a3,a,b,c;
    float r;

    a1 = (yc0[j1]-yc0[j0]) / (xc0[j1]-xc0[j0]);
    a2 = (yc0[j2]-yc0[j0]) / (xc0[j2]-xc0[j0]);
    a3 = (a2-a1) / (xc0[j2]-xc0[j1]);

    a = a3;
    b = a1 - a3*(xc0[j0]+xc0[j1]);
    c = a3*xc0[j0]*xc0[j1] - a1*xc0[j0] + yc0[j0];

    r = a*t*t + b*t + c;
    
	if(r>3e8)
		r=3e8;
    //if(r<0)
	//	r=0;
    
	return r;
}

//
//	打开“用户设置”对话框
//
void CPtcrDoc::OnMenuSetUser() 
{
	// TODO: Add your command handler code here
	if(m_setusername=="hust01" || m_setusername=="HUST01")
		;
	else
	{
    	AfxMessageBox("你无权进行用户设置，请用管理者用户登入！",MB_OK,0);
	    return;
	}
    CSETUSER setuser;
	if(setuser.DoModal()==IDOK)
	return;

}

//
//	获取并计算PT100电阻的温度，返回计算值
//
float CPtcrDoc::ReadPt100(int ChanNo) 
{
	// TODO: Add your control notification handler code here
    char *cmd="?\r";
	char results[128];
    int Sr253BCC=6;
   static float Pt=-100;

    OutChan(ChanNo);
    DelayTime(3);
	m_ReadingF45=1;

	m_Resistance= ReadResiRepeat(5);
	if((m_Resistance<80)||(m_Resistance>400))
   {
     Init8253();
  	 OutChan(ChanNo);
// return 20;
     DelayTime(3);
	 m_Resistance= ReadResiRepeat(3);
   }


	if(ChanNo==13){
		m_Pt100=Temperature(m_Resistance,-0.4);
	    m_rt.m_tPt100_1=m_Pt100;
	}
	else if(ChanNo==14){
		m_Pt100=Temperature(m_Resistance,-0.4);
	    m_rt.m_tPt100_2=m_Pt100;
	}
    else {
		m_Pt100=Temperature(m_Resistance,-0.2);


		m_rt.m_tPt100_1=m_Pt100;
		m_rt.m_tPt100_2=m_Pt100;
	}

	m_rt.m_tPt100=m_Pt100;
	m_rt.m_tPt100_3=(m_PV+m_rt.m_tPt100_1+m_rt.m_tPt100_2)/3;
    Pt=m_Pt100;
    m_Pt100_2=m_Pt100;
    return m_Pt100;

}

//
//	计算拟合阻值
//
float CPtcrDoc::GetOptimizeRes(int j0, int j1, int j2, float t)
{
	float a1,a2,a3,a,b,c;
    float r;
    a1 = (m_rt.GetY(j1)-m_rt.GetY(j0)) / (m_rt.GetX(j1)-m_rt.GetX(j0));
	if(m_rt.GetY(j2)==0) 
		  a2 = (m_rt.GetY(j0) / m_rt.GetX(j0));
    else
          a2 = (m_rt.GetY(j2)-m_rt.GetY(j0)) / (m_rt.GetX(j2)-m_rt.GetX(j0));
    a3 = (a2-a1) / (m_rt.GetX(j2)-m_rt.GetX(j1));
    a = a3;
    b = a1 - a3*(m_rt.GetX(j0)+m_rt.GetX(j1));
    c = a3*m_rt.GetX(j0)*m_rt.GetX(j1) - a1*m_rt.GetX(j0) + m_rt.GetY(j0);

    r = a*t*t + b*t + c;
    
	if(r>3e8)
		r=3e8;
    //if(r<0)
	//	r=0;
    
	return r;
}

//
//	窗口关闭前操作：弹出确认窗口并保存数据
//
BOOL CPtcrDoc::CanCloseFrame(CFrameWnd* pFrame) 
{

	char results[128];
    char cmd[80]="SB S";	
int Read[10];
//m_Running=1;
	if(m_Running)
	{
		if(::MessageBox(NULL,"确定要终止控制?","PTCR R-T",MB_YESNO|MB_ICONQUESTION)==IDNO)
	         return FALSE;	
		::SendMessage(AfxGetMainWnd()->m_hWnd,WM_STATUS_MESSAGE,0,AFX_IDS_SENDCMD);
    }
//		SendMessage(WM_COMMAND,ID_FILE_SAVE,0);
    if(ZWX==0){  
 //           ReadPvsv(cmd,results,4,3,2);
  //  	    ReadPvsv(cmd,results,4,3,2);
		 if(m_sPort.m_SPAvailable==TRUE)
		  if(m_sPort.m_rxdata.Sr253BCC==2){
			  ReadPvsv(cmd,results,4,3,2);
               Sleep(500);
    	      ReadPvsv(cmd,results,4,3,2);
               Sleep(500);
		  }
		  else if(m_sPort.m_rxdata.sr==13)
		  {
			   SetSr93("011W05010,",0,TRUE);
               Sleep(1000);
		       SetSr93Temp(0);//ZJ SV 0
               Sleep(1000);
  
		  }
		  else {
			    SrRead("011R05000",Read);
            	SetSr93("011W05090,",0,TRUE);
                Sleep(1000);
			    SetSr93("011W05090,",0,TRUE);
                Sleep(500);
		     	SetSr93Temp(0);//zjun SV 0
                Sleep(500);
             if(m_sPort.m_rxdata.sr==83)
				SetSr93("011W01860,",1,FALSE);//StdBy
		  }

	  }
	  else{
		  SetC(7,0);
          SetC(2,0);
          SetC(2,1); //stop Heat
	  }
    m_Running=FALSE; 
/*		if(m_sPortF45.m_SPAvailable==TRUE)  
			m_sPortF45.~CSerialPort();
		if(m_sPort.m_SPAvailable==TRUE)  
			m_sPortF45.~CSerialPort();
*/
	 if((m_sPortF45.m_SPAvailable==FALSE) && (m_sPort.m_SPAvailable==FALSE)) 
          _exit(0);
		if(m_sPortF45.m_SPAvailable==TRUE)  
			m_sPortF45.~CSerialPort();
		if(m_sPort.m_SPAvailable==TRUE)  
			m_sPort.~CSerialPort();


	::MessageBox(NULL,"测量控制已终止!","PTCR R_T",MB_OK);
	m_rt.isRunning=m_Running;

	     if(::MessageBox(NULL,"确定要退出RT系统?","PTCR R-T",MB_YESNO|MB_ICONQUESTION)==IDNO)
    		return FALSE; 
		 else
			 _exit(0);//zjun

    	return CDocument::CanCloseFrame(pFrame);


}

//
//	退出测试程序
//
void CPtcrDoc::OnAppExit() 
{
	// TODO: Add your command handler code here
	
	bool m_Exit;
    CFrameWnd* pFrame;
		 pFrame=(CFrameWnd * )AfxGetApp()->m_pMainWnd;
	
	 	m_Exit=CanCloseFrame(pFrame);

	if(m_Exit==TRUE)	{
		if(m_sPortF45.m_SPAvailable==TRUE)  
			m_sPortF45.~CSerialPort();
		if(m_sPort.m_SPAvailable==TRUE)  
			m_sPortF45.~CSerialPort();

		_exit(0);
	}
	else return;
}

//
//	将数据写入文件PTCRT.ini
//
BOOL CPtcrDoc::SavePtcRtIni()
{
//zjun2003/3/28
	FILE  *stream;
	CString filename;

	filename="PTCRT.ini";
	stream=fopen(filename,"w");


	if(stream!=NULL)
	{	

   	fprintf(stream,"%i\t",m_rt.client);
//  ZWX=0;//0=zwx-b 1=zwx-c,2=ZWX-d
   	fprintf(stream,"%i\t",ZWX);

    fprintf(stream,"%i\t",m_sPortF45.m_nPortNr);
    fprintf(stream,"%i\t",m_sPortF45.m_baudno);
    fprintf(stream,"%i\t",m_sPortF45.m_parityno);
    fprintf(stream,"%i\t",m_sPortF45.m_datano);
    fprintf(stream,"%i\t",m_sPortF45.m_stopno);
 
	fprintf(stream,"%i\t",m_sPort.m_nPortNr);
    fprintf(stream,"%i\t",m_sPort.m_baudno);
    fprintf(stream,"%i\t",m_sPort.m_parityno);
    fprintf(stream,"%i\t",m_sPort.m_datano);
	fprintf(stream,"%i\t",m_sPort.m_stopno);

   	fprintf(stream,"%i\t",w2w4);
 //  MultiMeter=5;// 0 无万用表, 1 FLUKE45, 2 Tonghui2512, 3 Esort3146A富贵/艾克, 4 HP34401A ,5 2000
   	fprintf(stream,"%i\t",MultiMeter);
//	DigitController=0; //0 无温控表, 1 SR253;
   	fprintf(stream,"%i\t",DigitController);
//	Pt100Chan_1=16;
   	fprintf(stream,"%i\t",Pt100Chan_1);
//	Pt100Chan_2=16;
   	fprintf(stream,"%i\t",Pt100Chan_2);
//	m_HT12D=0;//0 8255; 1 HT12D
    	fprintf(stream,"%i\t",m_HT12D);
//   m_rt.m_Number=10;
    	fprintf(stream,"%i\t", m_rt.m_Number);
//	m_rt.m_rtSave.m_SpecialR=3e8;
    	fprintf(stream,"%f\t", m_rt.m_rtSave.m_SpecialR);
char F45sn[10];
strcpy(F45sn,F45SN);
    	fprintf(stream,"%s\t", F45sn);
char a[50];
for(int i=0;i<50;i++)
    	fprintf(stream,"%c\t", a[i]);

	}

	fclose(stream);
	return TRUE;
	//2003/3/28
}

//
//	十六进制字符串转化为整型
//
int CPtcrDoc::HexToi(char *Hex)
{
int len;

len=strlen(Hex);
 
 int i;
int a=0;

if(Hex[0]<'8')
   for(i=0;i<len;i++)
 {
//  a=0  ;
  a=a+(int)((int)Hex[i]-48*(Hex[i]<58)-55*(Hex[i]>64))*pow(16.0,len-1-i);
 }

else if(Hex[0]>='8')
for(i=0;i<len;i++)
 {
 // a=0  ;
  a=a+(int)((int)Hex[i]-48*(Hex[i]<58)-55*(Hex[i]>64)-16*(i==0))*pow(16.0,len-1-i);
 }


	 return a;
}

//
//	整型转化为十六进制字符串
//
int CPtcrDoc::iToHex(char *Hex,int j)
{
int len;
int sign=0;//+
len=strlen(Hex);
 
 int i;
int a[5],b;
 int c;
 if(j<0){j=j*(-1)-1;
    sign=1;}
 else sign=0;

 a[0]=j;
  b=a[0];
 

   for(i=0;i<4;i++)
 {
 c=(int)pow(16.0,4-1-i);
 a[i]=b/c;
 b=b-a[i]*c;
//_itoa( i, buffer, 10 );
 itoa(a[i],&Hex[i],16);
   }
 
 
   if(sign==1)
   for(i=0;i<4;i++)
 {
 itoa(15-a[i],&Hex[i],16);
   }



a[i]=0;
_strupr(Hex);
//UPPER(Hex);
//uppercase(&Hex);
len=strlen(Hex);

	 return len;
}

//
//	将读取的PVSV数据以十六进制保存于数组Read内，返回Read[0]
//
int CPtcrDoc::SrRead(char *cmd,int *Read)
{
int Sr253BCC;
char results[128];
char buftmp[10][35];
// int DP[10]; 

 char Cmd[80];

strcpy(Cmd,cmd);
  Sr253BCC=m_sPort.m_rxdata.Sr253BCC;

  ReadPvsv(Cmd,results,4,3,Sr253BCC);//"011R07070"
   Splint(buftmp,results,Sr253BCC);
for(int i=0;i<10;i++)
   Read[i]=HexToi(buftmp[i]);
  


   return Read[0];

}

//
//	将命令cmd写入测试仪器
//
int CPtcrDoc::SrWrite(char *cmd)
{
int Sr253BCC;
char results[128];
char buftmp[10][35];
// int DP[10]; 

 char Cmd[80];

strcpy(Cmd,cmd);
 Sr253BCC=m_sPort.m_rxdata.Sr253BCC;

  ReadPvsv(Cmd,results,4,3,Sr253BCC);//"011R07070"
   Splint(buftmp,results,Sr253BCC);

//   for(int i=0;i<10;i++)
//   Read[i]=HexToi(buftmp[i]);
  
   return TRUE;

}

//
//	根据读取的PVSV值与参数temp设置温度（通讯协议Sr93）
//
int CPtcrDoc::SetSr93Temp(float temp) 
{
	// TODO: Add your control notification handler code here
int Sr253BCC;
//char results[128];
//char buftmp[10][35];

int temp0;

int Read[10];

  char cmd[80]="DS";
     char Temp[5];
  int DP=0; 
 
 Sr253BCC=m_sPort.m_rxdata.Sr253BCC;

 if(Sr253BCC==4) 
  {	 	
   
	 DP=SrRead("DP",Read);//"011R07070"
     temp0=temp*pow(10.0,DP);

	 iToHex(Temp,temp0);
	 Temp[4]=0;
    strcpy(cmd,"011W03000,");
     strcat(cmd,Temp);
	   SrWrite(cmd);
  m_PV=SrRead("DS",Read)/pow(10.0,DP); //"011R01000"

		if(Read[1]==temp0) {
		  m_SV=Read[1]/pow(10.0,DP);
          m_SvNum=1;
          m_rt.m_PV =m_PV;
	      m_rt.m_SV=m_SV;	
	    	return TRUE; 
		}
		else return FALSE;
		}
return TRUE;
}

//
//	根据参数设置温度（通讯协议Sr93）
//
int CPtcrDoc::SetSr93(char *cmd, float temp, int Coefficient) 
{
	// TODO: Add your control notification handler code here
int Sr253BCC;
// char results[128];
// char buftmp[10][35];

int temp0;

int Read[10];

  char Cmd[80]="DS";

      char Temp[5];
 int DP=0; 
 
 Sr253BCC=m_sPort.m_rxdata.Sr253BCC;

 if(Sr253BCC==4) 
  {	 	
     if(Coefficient==1){
	 DP=SrRead("DP",Read);//"011R07070"

     temp0=temp*pow(10.0,DP);
	 }
	 else temp0=temp;

	 iToHex(Temp,temp0);
   strcpy(Cmd,cmd);
     strcat(Cmd,Temp);
	   SrWrite(Cmd);
		}
   return TRUE;

}

//
//	若测试未进行，设置“打开”选项可用
//
void CPtcrDoc::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//	CPtcrDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);

	if(m_Running==FALSE)
	{
		pCmdUI->Enable();

	}
	else
		pCmdUI->Enable(FALSE);	
}

//
//	获取操作系统版本
//
int CPtcrDoc::GetOSVersion()
{
 OSVERSIONINFO OsVersionInfo;
 OsVersionInfo.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
 GetVersionEx (&OsVersionInfo);
 if(OsVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
	 OSver=0;//"95or98"
 else if(OsVersionInfo.dwPlatformId ==VER_PLATFORM_WIN32_NT)
	 OSver=1;//"NT,2000"
 else
 OSver=-1;
 return OSver;
}
