/*
**	FILENAME			PtcrView.cpp
**
**	PURPOSE				此类可用于主窗口的框架相关操作，包含菜单栏内
**						各个选项的功能与操作，此外还包含数据、曲线等
**						的绘制方式
*/

#include "stdafx.h"
#include "Ptcr.h"
#include <afxadv.h>
#include "PtcrDoc.h"
#include "PtcrView.h"
#include "mancmd1.h"
#include "ComCfg.h"
#include "MainFrm.h"
#include <conio.h>
#include "stdio.h"
#include "NameResi.h"
#include "Non.h"
#include "SelRTRange.h"
#include "GetAnyResOfTem.h"
#include "setTemp.h"
#include "CombinDlg.h"
#include "DataOptize.h"
//#include "SelPrintData.h"

extern int F45; //modified on 1/18/2000
int NameResi0=0;
CString m_devicename;
extern CString m_setusername;
//int pj;
//int InitPortData=0x80;
//int InitPortControl=0x00;
//int GroupVoltageChangeRelayNum[13]={200,300,400,500,600,700,780,800,890,500,340,450,600};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*..................................
   ht12d直接控制子程序
   Adress:对应ht12d的地址
   ControlData:所要输出4位控制数据，如0x08，则对应ht12d的第一位
   输出为1，其余3位为0
*///..................................


/////////////////////////////////////////////////////////////////////////////
// CPtcrView

IMPLEMENT_DYNCREATE(CPtcrView, CView)

BEGIN_MESSAGE_MAP(CPtcrView, CView)
	//{{AFX_MSG_MAP(CPtcrView)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_PLOT0, OnPlot0)
	ON_COMMAND(ID_PLOT1, OnPlot1)
	ON_COMMAND(ID_PLOT2, OnPlot2)
	ON_COMMAND(ID_PLOT3, OnPlot3)
	ON_COMMAND(ID_PLOT4, OnPlot4)
	ON_COMMAND(ID_PLOT5, OnPlot5)
	ON_COMMAND(ID_PLOT6, OnPlot6)
	ON_COMMAND(ID_PLOT7, OnPlot7)
	ON_COMMAND(ID_PLOT8, OnPlot8)
	ON_COMMAND(ID_PLOT9, OnPlot9)
	ON_COMMAND(ID_PLOT10, OnPlot10)
	ON_COMMAND(ID_PLOT11, OnPlot11)
	ON_COMMAND(ID_PLOT12, OnPlot12)
	ON_COMMAND(ID_PLOT13, OnPlot13)
	ON_COMMAND(ID_PLOT14, OnPlot14)
	ON_COMMAND(ID_PLOT15, OnPlot15)
	ON_COMMAND(ID_PLOT16, OnPlot16)
	ON_COMMAND(ID_PLOT17, OnPlot17)
	ON_COMMAND(ID_PLOT18, OnPlot18)
	ON_COMMAND(ID_PLOT19, OnPlot19)
	ON_COMMAND(ID_PLOT20, OnPlot20)
	ON_COMMAND(ID_PLOT21, OnPlot21)
	ON_COMMAND(ID_PLOT22, OnPlot22)
	ON_COMMAND(ID_PLOT23, OnPlot23)
	ON_COMMAND(ID_PLOT24, OnPlot24)
	ON_COMMAND(ID_PLOT25, OnPlot25)
	ON_COMMAND(ID_PLOT26, OnPlot26)
	ON_COMMAND(ID_PLOT27, OnPlot27)
	ON_COMMAND(ID_PLOT28, OnPlot28)
	ON_COMMAND(ID_PLOT29, OnPlot29)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_WND_DATA, OnWndData)
	ON_COMMAND(ID_WND_MULTI, OnWndMulti)
	ON_COMMAND(ID_WND_REFERENCE, OnWndReference)
	ON_COMMAND(ID_WND_SINGLE, OnWndSingle)
	ON_UPDATE_COMMAND_UI(ID_PLOT0, OnUpdatePlot0)
	ON_UPDATE_COMMAND_UI(ID_PLOT1, OnUpdatePlot1)
	ON_UPDATE_COMMAND_UI(ID_PLOT10, OnUpdatePlot10)
	ON_UPDATE_COMMAND_UI(ID_PLOT11, OnUpdatePlot11)
	ON_UPDATE_COMMAND_UI(ID_PLOT12, OnUpdatePlot12)
	ON_UPDATE_COMMAND_UI(ID_PLOT13, OnUpdatePlot13)
	ON_UPDATE_COMMAND_UI(ID_PLOT14, OnUpdatePlot14)
	ON_UPDATE_COMMAND_UI(ID_PLOT15, OnUpdatePlot15)
	ON_UPDATE_COMMAND_UI(ID_PLOT16, OnUpdatePlot16)
	ON_UPDATE_COMMAND_UI(ID_PLOT17, OnUpdatePlot17)
	ON_UPDATE_COMMAND_UI(ID_PLOT18, OnUpdatePlot18)
	ON_UPDATE_COMMAND_UI(ID_PLOT19, OnUpdatePlot19)
	ON_UPDATE_COMMAND_UI(ID_PLOT2, OnUpdatePlot2)
	ON_UPDATE_COMMAND_UI(ID_PLOT20, OnUpdatePlot20)
	ON_UPDATE_COMMAND_UI(ID_PLOT21, OnUpdatePlot21)
	ON_UPDATE_COMMAND_UI(ID_PLOT22, OnUpdatePlot22)
	ON_UPDATE_COMMAND_UI(ID_PLOT23, OnUpdatePlot23)
	ON_UPDATE_COMMAND_UI(ID_PLOT24, OnUpdatePlot24)
	ON_UPDATE_COMMAND_UI(ID_PLOT25, OnUpdatePlot25)
	ON_UPDATE_COMMAND_UI(ID_PLOT26, OnUpdatePlot26)
	ON_UPDATE_COMMAND_UI(ID_PLOT27, OnUpdatePlot27)
	ON_UPDATE_COMMAND_UI(ID_PLOT28, OnUpdatePlot28)
	ON_UPDATE_COMMAND_UI(ID_PLOT29, OnUpdatePlot29)
	ON_UPDATE_COMMAND_UI(ID_PLOT3, OnUpdatePlot3)
	ON_UPDATE_COMMAND_UI(ID_PLOT4, OnUpdatePlot4)
	ON_UPDATE_COMMAND_UI(ID_PLOT5, OnUpdatePlot5)
	ON_UPDATE_COMMAND_UI(ID_PLOT6, OnUpdatePlot6)
	ON_UPDATE_COMMAND_UI(ID_PLOT7, OnUpdatePlot7)
	ON_UPDATE_COMMAND_UI(ID_PLOT8, OnUpdatePlot8)
	ON_UPDATE_COMMAND_UI(ID_PLOT9, OnUpdatePlot9)
	ON_UPDATE_COMMAND_UI(ID_WND_DATA, OnUpdateWndData)
	ON_UPDATE_COMMAND_UI(ID_WND_MULTI, OnUpdateWndMulti)
	ON_UPDATE_COMMAND_UI(ID_WND_REFERENCE, OnUpdateWndReference)
	ON_UPDATE_COMMAND_UI(ID_WND_SINGLE, OnUpdateWndSingle)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_SERIALPORT_F45SETTINGS, OnSerialportF45settings)
	ON_COMMAND(ID_MANUAL_CMD, OnManualCmd)
	ON_COMMAND(ID_SERIALPORT_SETTINGS, OnSerialportSettings)
	ON_COMMAND(ID_CMD_GO, OnCmdGo)
	ON_COMMAND(ID_Chan_Set, OnChanSet)
	ON_COMMAND(ID_SR253_CMD, OnSr253Cmd)
	ON_WM_TIMER()
	ON_COMMAND(ID_ManMea, OnManMea)
	ON_COMMAND(ID_RTSET_RANGE, SetRTRange)
	ON_UPDATE_COMMAND_UI(ID_RTSET_RANGE, OnUpdateRtsetRange)
	ON_COMMAND(ID_MENUANYRES, OnGetAnyres)
	ON_UPDATE_COMMAND_UI(ID_MENUANYRES, OnUpdateGetAnyres)
	ON_UPDATE_COMMAND_UI(ID_SERIALPORT_SETTINGS, OnUpdateDigitControllerSettings)
	ON_UPDATE_COMMAND_UI(ID_SR253_CMD, OnUpdateSr253Cmd)
	ON_COMMAND(ID_SetTempStage, OnSetTempStage)
	ON_COMMAND(ID_CeramicPTC, OnCeramicPTC)
	ON_UPDATE_COMMAND_UI(ID_CeramicPTC, OnUpdateCeramicPTC)
	ON_COMMAND(ID_PolymerPTC, OnPolymerPTC)
	ON_UPDATE_COMMAND_UI(ID_PolymerPTC, OnUpdatePolymerPTC)
	ON_COMMAND(ID_TOOL_CONBIND, OnToolConbind)
	ON_COMMAND(ID_OPTIMIZE, OnOptimize)
	ON_UPDATE_COMMAND_UI(ID_OPTIMIZE, OnUpdateOptimize)
	ON_COMMAND(ID_MENUPRINTDATA, OnMenuprintdata)
	ON_WM_CHAR()
	ON_WM_COPYDATA()
	ON_COMMAND(ID_CMD_STOP, OnCmdStop)
	ON_UPDATE_COMMAND_UI(ID_MANUAL_CMD, OnUpdateManualCmd)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_Pensonnel, OnPensonnelCurve)
	ON_UPDATE_COMMAND_UI(ID_Pensonnel, OnUpdatePensonnelCurve)
	//}}AFX_MSG_MAP

	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPtcrView 构造/析构

//
//	构造函数：初始化各参数
//
CPtcrView::CPtcrView()
{
	// TODO: add construction code here
	//m_bButton=FALSE;
    DiaDataCheck=FALSE;
	m_bCtrlCreate=FALSE;	
	m_uFlag=1;
	m_min_temp=0;
    m_max_temp=250;
 //  m_max_temp=pDoc->220;

	m_temp_step=20;

	m_min_res="1.0E-2";
//	m_min_res="1.0E00";
    m_printstyle=0;//0:none  1:原始记录 2：温度取整后记录
	m_max_res="1.0E+9";

	m_show_dot=TRUE;

    m_Only_MeaDot=FALSE;
    m_OutterRect=TRUE;
	m_Sel_Coor_Kind=0;//FALSE
//	for(int i=0;i<5;i++)
	for(int i=0;i<MULNMBOFSPL;i++)
		m_iMulIndex[i]=100;
	for(i=0;i<NMBOFSPL;i++)
		m_bClickMenu[i]=FALSE;
}

//
//	析构函数
//
CPtcrView::~CPtcrView()
{
}

BOOL CPtcrView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPtcrView窗口绘制

//
//	绘制界面曲线与数据
//
void CPtcrView::OnDraw(CDC* pDC)
{
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	
	CRect rect;
	int i=0;


	GetClientRect(rect);	//获取工作区域坐标
	
	if(!m_bCtrlCreate)		//若未创建窗口
	{
		m_gCtrl.Create("PTC",WS_VISIBLE|WS_HSCROLL,rect,this,0xffff);	//在工作区创建名为“PTC”、ID为ffff、可见且带水平滚动条的窗口

		m_gCtrl.ShowWindow(SW_HIDE);									//隐藏此窗口并将激活传递给另一个窗口

		m_bCtrlCreate=TRUE;												//窗口创建成功
	}
	
		
if((pDoc->OpenFlag==TRUE)&&(!(pDoc->m_Running)))	//若文件打开成功且测量程序未运行
	{
     if(DiaDataCheck==FALSE) m_max_temp=pDoc->m_rt.m_rtSave.MaxT[1];	//若温度、阻值等数据出现谬误，则保存最高温度

		i=pDC->SetMapMode(MM_HIMETRIC);									//i为之前的映射模式；指定新映射模式：每个逻辑单元转换为 0.01 毫米，正x向右；正y向上

		if(!pDC->IsPrinting())				//若设备上下文未用于打印
		{
			m_rectRegion.CopyRect(&rect);	//将矩形rect复制到m_rectRegion
		}
							
		pDC->DPtoLP(m_rectRegion);			//将设备坐标转换为逻辑坐标
			
		if(m_uFlag==1)//单曲线显示
		{
			int lby;
            lby=pDoc->GetIndex();//选中且启用的通道号
		
			switch(lby)
			{
			case 100:		//无启用的通道
				break;
				default:
	if(pDoc->CPptc==1){//选中高分子PTC曲线
		
		m_draw.DrawCurve(pDC,pDoc->m_rt,m_rectRegion,pDoc->GetIndex(), m_temp_step,m_max_temp,m_min_res,m_max_res,m_min_temp,m_show_dot,m_Only_MeaDot,m_Sel_Coor_Kind,m_OutterRect);	//绘制曲线

		m_draw.DrawPolymerRef(pDC,pDoc->m_rt,m_rectRegion,pDoc->GetIndex(),m_rectRegion,pDoc->CPptc,pDoc->m_rt.client);																	//显示参数
	}
	else {//选中陶瓷PTC曲线
		m_draw.DrawCurve(pDC,pDoc->m_rt,m_rectRegion,pDoc->GetIndex(), m_temp_step,m_max_temp,m_min_res,m_max_res,m_min_temp,m_show_dot,m_Only_MeaDot,m_Sel_Coor_Kind,m_OutterRect);	//绘制曲线
		m_draw.DrawPolymerRef(pDC,pDoc->m_rt,m_rectRegion,pDoc->GetIndex(),m_rectRegion,pDoc->CPptc,pDoc->m_rt.client);																	//显示参数
	}

			}

			}
		else if(m_uFlag==2)//多曲线显示
			m_draw.DrawMultiCurves(pDC,pDoc->m_rt,m_rectRegion,&m_iMulIndex[0],m_temp_step,m_max_temp,m_min_res,m_max_res,m_min_temp,m_show_dot,m_Only_MeaDot);		//绘制多曲线
		else if(m_uFlag==3)//数据显示
			m_draw.DrawData(m_gCtrl,pDoc->m_rt);//显示数据
		else if(m_uFlag==4)//参数显示
			m_draw.DrawRef(m_gCtrl,pDoc->m_rt, pDoc->CPptc);//显示参数
		
		pDC->LPtoDP(m_rectRegion);		//将矩形m_rectRegion从逻辑单元映射到设备单元
			
		pDC->SetMapMode(i);				//指定映射模式为之前的映射模式
	}
	else if(pDoc->m_Running) //若测试程序正在运行中		//lby2001.11.10
	{
		i=pDC->SetMapMode(MM_HIMETRIC);		//i为之前的映射模式；指定新映射模式：每个逻辑单元转换为 0.01 毫米，正x向右；正y向上

		if(!pDC->IsPrinting())		//若设备上下文未用于打印
		{
			m_rectRegion.CopyRect(rect);		//将矩形rect复制到m_rectRegion
		}
		
		pDC->DPtoLP(m_rectRegion);		//将设备坐标转换为逻辑坐标
		if(m_uFlag==1){	//单曲线显示	
			int lby;
             lby = pDoc->GetIndex();//选中且启用的通道号
			 if((lby==100)||((lby>=0)&&(lby<=29))){;}//若Index内读取的通道号规范则无操作
             else {lby=0;pDoc->LoadIndex(0);}//否则默认选择通道1
				 
			switch(lby)
			{
			case 100:		//无启用的通道
				break;
			default:
 if(pDoc->STARTDOT-pDoc->m_rt.StartDot<0)	
	 m_draw.DrawRTMea(pDC,pDoc->m_rt,m_rectRegion,pDoc->GetIndex());		//绘制强制测试RT曲线
 else {  //zjun 2002/8/18
	m_show_dot=1;	
    m_Only_MeaDot=1;
  	m_draw.DrawRTMeaRef(pDC, pDoc->m_rt, m_rectRegion, pDoc->GetIndex());	//显示强制测试RT参数
	m_draw.DrawCurve(pDC,pDoc->m_rt,m_rectRegion,pDoc->GetIndex(), m_temp_step,m_max_temp,m_min_res,m_max_res,m_min_temp,m_show_dot,m_Only_MeaDot,m_Sel_Coor_Kind,m_OutterRect);	//绘制曲线
			}
			}
		}
	else if(m_uFlag==2)	//多曲线显示
			m_draw.DrawMultiCurves(pDC,pDoc->m_rt,m_rectRegion,&m_iMulIndex[0],m_temp_step,m_max_temp,m_min_res,m_max_res,m_min_temp,m_show_dot,m_Only_MeaDot);	//绘制多曲线

		pDC->LPtoDP(m_rectRegion);			//将矩形m_rectRegion从逻辑单元映射到设备单元
			
		pDC->SetMapMode(i);					//指定映射模式为之前的映射模式
	}			

	
}

/////////////////////////////////////////////////////////////////////////////
// CPtcrView打印

//
//	准备打印时，设置最大页码、显示“打印”对话框并创建打印机设备上下文
//
BOOL CPtcrView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	if(m_uFlag==1 || m_uFlag==2 || m_uFlag==4)
    	pInfo->SetMaxPage(1);
	else 
		pInfo->SetMaxPage(3);
	//pInfo->m_nNumPreviewPages=1;
//	pInfo->m_pPD->m_pd.nToPage=1;
	return DoPreparePrinting(pInfo);
}

//
//	开始打印前：获取设备名称
//
void CPtcrView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
    m_devicename=pInfo->m_pPD->GetDeviceName();
}

//
//	结束打印
//
void CPtcrView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


/////////////////////////////////////////////////////////////////////////////
// CPtcrView消息处理函数

//
//	确认绘制区域并进行曲线、数据绘制
//
void CPtcrView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	double width,height;
	int k;
	BOOL Flag;
	CRect rect,rct;
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);	//参数初始化
	if(pDoc->OpenFlag==TRUE)
	{
	
		rect=pInfo->m_rectDraw;
		if(m_uFlag==1||m_uFlag==2)
		{
			if(rect.Width()>rect.Height())
			{
				pInfo->SetMaxPage(2);
				height=0.8*rect.Height();
				width=height/0.75;
				rect.top+=(long)height/8;
				rect.bottom-=(long)height/8;
				rect.left+=(long)fabs((rect.Width()-width)/2.0);
				rect.right=rect.left+(long)width;
				m_rectRegion.CopyRect(&rect);
				rct.CopyRect(&rect);
				Flag=TRUE;
			}
			else
			{
				pInfo->SetMaxPage(1);
				rct.CopyRect(&rect);
				width=rect.Width();
				width=0.75*rect.Width();
				height=width*0.8;
				rect.left+=(long)width/8;
				rect.right-=(long)width/8;
				rect.top+=(long)width/8;
				rect.bottom=rect.top+(long)height;
                rct.left=rect.left-(long)width/8;//lby
				rct.right=rect.right+(long)width/8;
			    rct.top+=(long)(rect.bottom+long(width/20));
				rct.bottom=long(rct.bottom-long(width/8));
				m_rectRegion.CopyRect(&rect);
				Flag=FALSE;
			}
		}
		else
		{
			rect.top+=(long)(rect.Height()/10);
			rect.bottom-=(long)(rect.Height()/10);
			rect.left+=(long)(rect.Width()/25);
			rect.right-=(long)(rect.Width()/25);
		}
//根据显示区域形状与显示设置，调整显示范围的尺寸
		switch(m_uFlag)
		{
		case 1://单曲线显示
			if(Flag)//显示区域宽大于高
			{
				if(pInfo->m_nCurPage==1)//若当前打印页码为1
				{
					pDC->StartPage();
					OnDraw(pDC);		//绘制参数与曲线
                    
				}
			}
			else
			{
				OnDraw(pDC);			//绘制参数与曲线
				k=pDC->SetMapMode(MM_HIMETRIC);
				pDC->DPtoLP(rct);
  		    	m_draw.PrintText(pDC,pDoc->m_rt,rct,pDoc->GetIndex(),m_printstyle);	
			}
			break;
		case 2://多曲线显示
			if(Flag)//显示区域宽大于高
			{
				
				if(pInfo->m_nCurPage==1)//当前打印页码为1
				{
					pDC->StartPage();
					OnDraw(pDC);	//绘制参数与曲线
				}
				else if(pInfo->m_nCurPage==2)//当前打印页码为2
				{
					k=pDC->SetMapMode(MM_TEXT);
					pDC->DPtoLP(rct);
					m_draw.PrintMulText(pDC,pDoc->m_rt,rct,&m_iMulIndex[0]);//打印参数
					pDC->EndPage();
				}
				
			}
			else
			{
				OnDraw(pDC);//绘制参数与曲线
				k=pDC->SetMapMode(MM_HIMETRIC);
				pDC->DPtoLP(rct);
			}
			break;
		case 3://数据显示
		case 4://参数显示
			{
				int i,j;
				int rows;
              	int m_groupTemOne=0,m_groupTemTwo=0,m_groupTemThree=0;
				
				i=m_gCtrl.GetCols();
				rows=m_gCtrl.GetRows();

				k=pDC->SetMapMode(MM_TEXT);
				pDC->DPtoLP(rect);
            	for(i=0;i<30;i++)
				{
	             	if(pDoc->m_rt.m_rtSave.m_bChannels[i]==TRUE)
					{			
		            	j++;
//keter demand 7-30/2002
		        	if(i<4)
	        			m_groupTemOne++;
           			else if(i>=4 && i<8)
	           		    	m_groupTemTwo++;
	           		     else if(i>=8 && i<12)
							m_groupTemThree++;
					}
				}
			
//keter demand 7-30/2002

				
	        	if(i>7)
				{
					if(i%7!=0)				
					    j=i/7+1;	
	  			    else 
						j=i/7;
					if(m_uFlag==3)
					{					 
						if(pInfo->m_nCurPage==1)
						{

                            if(m_groupTemOne!=0)
							    m_draw.PrintRef(m_gCtrl,pDC,rect,pDoc->m_rt,0,m_groupTemOne,m_uFlag,pDoc->CPptc);
							return;
						}
						else if(pInfo->m_nCurPage==2)
						{
							if(m_groupTemTwo!=0 && m_groupTemOne!=0)
		            	    	m_draw.PrintRef(m_gCtrl,pDC,rect,pDoc->m_rt,m_groupTemOne+1,m_groupTemOne+1+m_groupTemTwo,m_uFlag,pDoc->CPptc);
							else if(m_groupTemTwo!=0 && m_groupTemOne==0)	
		            	    	m_draw.PrintRef(m_gCtrl,pDC,rect,pDoc->m_rt,0,m_groupTemOne+1+m_groupTemTwo,m_uFlag,pDoc->CPptc);
								
								return;
						}
						      else    //pInfo->m_nCurPage==3
							  {
								 if(m_groupTemThree!=0 && m_groupTemTwo!=0 && m_groupTemOne!=0)
               	                    	m_draw.PrintRef(m_gCtrl,pDC,rect,pDoc->m_rt,m_groupTemOne+1+m_groupTemTwo+1,m_groupTemOne+1+m_groupTemTwo+1+m_groupTemThree,m_uFlag,pDoc->CPptc);
								 else if(m_groupTemThree!=0  && m_groupTemOne!=0 && m_groupTemTwo==0)
               	                    	m_draw.PrintRef(m_gCtrl,pDC,rect,pDoc->m_rt,m_groupTemOne+1,m_groupTemOne+1+m_groupTemThree,m_uFlag,pDoc->CPptc);
      							   	 else if(m_groupTemThree!=0  && m_groupTemOne==0 && m_groupTemTwo!=0)
               	                    	m_draw.PrintRef(m_gCtrl,pDC,rect,pDoc->m_rt,m_groupTemTwo+1,m_groupTemTwo+1+m_groupTemThree,m_uFlag,pDoc->CPptc);
						     	return;
							  }

					}
						

					else
					{
//						pInfo->SetMaxPage(1);
						if(pInfo->m_nCurPage==1)
							m_draw.PrintRef(m_gCtrl,pDC,rect,pDoc->m_rt,1,6,m_uFlag,pDoc->CPptc);

					}
				}
				else
				{
					pInfo->SetMaxPage(1);
					m_draw.PrintRef(m_gCtrl,pDC,rect,pDoc->m_rt,1,i-1,m_uFlag,pDoc->CPptc);
				}

				pDC->LPtoDP(rect);
			}
			break;
		}
		pDC->LPtoDP(rct);
		pDC->SetMapMode(k);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPtcrView 诊断

#ifdef _DEBUG
void CPtcrView::AssertValid() const
{
	CView::AssertValid();
}

void CPtcrView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPtcrDoc* CPtcrView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPtcrDoc)));
	return (CPtcrDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPtcrView消息处理程序

//
//	截获消息键盘和鼠标消息
//
BOOL CPtcrView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CView::PreTranslateMessage(pMsg);
}

//
//	擦除功能：绘制覆盖区域的矩形
//
BOOL CPtcrView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(rect);
//	pDC->FillSolidRect(rect,RGB(128,128,128));
	pDC->FillSolidRect(rect,RGB(255,255,255));
	return TRUE;

}

//
//	设置通道1~30选中
//
void CPtcrView::OnPlot0() 
{
	// TODO: Add your command handler code here
	OnPlot(0);
}

void CPtcrView::OnPlot1() 
{
	// TODO: Add your command handler code here
	OnPlot(1);
}

void CPtcrView::OnPlot2() 
{
	// TODO: Add your command handler code here
	OnPlot(2);
}

void CPtcrView::OnPlot3() 
{
	// TODO: Add your command handler code here
	OnPlot(3);
}

void CPtcrView::OnPlot4() 
{
	// TODO: Add your command handler code here
	OnPlot(4);
}

void CPtcrView::OnPlot5() 
{
	// TODO: Add your command handler code here
	OnPlot(5);
}

void CPtcrView::OnPlot6() 
{
	// TODO: Add your command handler code here
	OnPlot(6);
}

void CPtcrView::OnPlot7() 
{
	// TODO: Add your command handler code here
	OnPlot(7);
}

void CPtcrView::OnPlot8() 
{
	// TODO: Add your command handler code here
	OnPlot(8);
}

void CPtcrView::OnPlot9() 
{
	// TODO: Add your command handler code here
	OnPlot(9);
}


void CPtcrView::OnPlot20() 
{
	// TODO: Add your command handler code here
	OnPlot(20);
}

void CPtcrView::OnPlot21() 
{
	// TODO: Add your command handler code here
	OnPlot(21);
}

void CPtcrView::OnPlot22() 
{
	// TODO: Add your command handler code here
	OnPlot(22);
}

void CPtcrView::OnPlot23() 
{
	// TODO: Add your command handler code here
	OnPlot(23);
}

void CPtcrView::OnPlot24() 
{
	// TODO: Add your command handler code here
	OnPlot(24);
}

void CPtcrView::OnPlot25() 
{
	// TODO: Add your command handler code here
	OnPlot(25);
}

void CPtcrView::OnPlot26() 
{
	// TODO: Add your command handler code here
	OnPlot(26);
}

void CPtcrView::OnPlot27() 
{
	// TODO: Add your command handler code here
	OnPlot(27);
}

void CPtcrView::OnPlot28() 
{
	// TODO: Add your command handler code here
	OnPlot(28);
}

void CPtcrView::OnPlot29() 
{
	// TODO: Add your command handler code here
	OnPlot(29);
}


void CPtcrView::OnPlot10() 
{
	// TODO: Add your command handler code here
	OnPlot(10);
}

void CPtcrView::OnPlot11() 
{
	// TODO: Add your command handler code here
	OnPlot(11);
}

void CPtcrView::OnPlot12() 
{
	// TODO: Add your command handler code here
	OnPlot(12);
}

void CPtcrView::OnPlot13() 
{
	// TODO: Add your command handler code here
	OnPlot(13);
}

void CPtcrView::OnPlot14() 
{
	// TODO: Add your command handler code here
	OnPlot(14);
}

void CPtcrView::OnPlot15() 
{
	// TODO: Add your command handler code here
	OnPlot(15);
}

void CPtcrView::OnPlot16() 
{
	// TODO: Add your command handler code here
	OnPlot(16);
}

void CPtcrView::OnPlot17() 
{
	// TODO: Add your command handler code here
	OnPlot(17);
}

void CPtcrView::OnPlot18() 
{
	// TODO: Add your command handler code here
	OnPlot(18);
}

void CPtcrView::OnPlot19() 
{
	// TODO: Add your command handler code here
	OnPlot(19);
}


//
//	设置通道i+1选中
//
void CPtcrView::OnPlot(int i)
{
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int j;
	
	for(j=0;j<NMBOFSPL;j++)
	{
		m_bClickMenu[j]=FALSE;
	}
	
	if(pDoc->OpenFlag==TRUE)
	{  
		pDoc->OnPlot_Renew=1;//lby2002/05/01
		if(m_uFlag==1 )
		{
			pDoc->LoadIndex(i);
			m_bClickMenu[i]=TRUE;		
		}
		else if(m_uFlag==2)
		{
			for(j=0;j<NMBOFSPL;j++)
			{
				if(m_iMulIndex[j]!=100)
				{
					if(m_iMulIndex[j]==i)
					{
						m_iMulIndex[j]=100;
						break;
					}
				}
				else
				{
					m_iMulIndex[j]=i;

					break;
				}
			}
			Sorting();

			for(j=0;j<MULNMBOFSPL;j++)
			{
				if(m_iMulIndex[j]==100)
					break;
				else
					m_bClickMenu[m_iMulIndex[j]]=TRUE;
			}
		}
	}

	pDoc->UpdateAllViews(NULL);
}

//
//	按下鼠标右键时，在光标右侧显示包含启用“通道i”菜单项的快捷菜单
//
void CPtcrView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu menu;
	int i;
	CString str;

	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	menu.CreatePopupMenu();
	
	if(pDoc->OpenFlag==TRUE)
	{
		for(i=0;i<NMBOFSPL;++i)
		{
			if(pDoc->m_rt.m_rtSave.m_bChannels[i]==TRUE)
			{
				str.Format("通道%d",i+1);
				menu.AppendMenu(MF_STRING,ID_PLOT0+i,str);
				if(m_bClickMenu[i]==TRUE)
					menu.CheckMenuItem(ID_PLOT0+i,MF_CHECKED);
			}
		}
	}
	
	GetCursorPos(&point);
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);

	CView::OnRButtonDown(nFlags, point);
}

//
//	按下键盘按键后，单曲线显示时，显示启用的通道；鼠标右侧显示快捷菜单
//
void CPtcrView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i;

	if(pDoc->OpenFlag==	TRUE && m_uFlag==1)
	{
		if(pDoc->GetIndex()!=100)
		{
			if(nChar==38)
			{
				i=pDoc->GetIndex();
				do
				{
					i+=1;
					if(i>29)
						i=0;
					pDoc->LoadIndex(i);
				}while(!pDoc->m_rt.m_rtSave.m_bChannels[i]);
				OnPlot(i);
			}
			else if(nChar==40)
			{
				i=pDoc->GetIndex();
				do
				{
					i-=1;
					if(i<0)
						i=29;
					pDoc->LoadIndex(i);
				}while(!pDoc->m_rt.m_rtSave.m_bChannels[i]);
				OnPlot(i);
			}
		}
	}

	if(nChar==93)
	{
		CPoint point;
		GetCursorPos(&point);
		OnRButtonDown(nFlags,point);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//
//	选择“数据显示”
//
void CPtcrView::OnWndData() 
{
	// TODO: Add your command handler code here
	m_uFlag=3;
	OnWnd();
}

//
//	选择“多曲线显示”
//
void CPtcrView::OnWndMulti() 
{
	// TODO: Add your command handler code here
	m_uFlag=2;
	for(int i=0;i<MULNMBOFSPL;i++)
		m_iMulIndex[i]=100;
	OnWnd();
}

//
//	选择“参数显示”
//
void CPtcrView::OnWndReference() 
{
	// TODO: Add your command handler code here
	m_uFlag=4;
	OnWnd();
}

//
//	选择“单曲线显示”
//
void CPtcrView::OnWndSingle() 
{
	// TODO: Add your command handler code here
	m_uFlag=1;
	OnWnd();
}

//
//	对多曲线通道编号列表进行排序
//
void CPtcrView::Sorting()
{
	int i,j,k;
	for(i=0;i<MULNMBOFSPL-1;i++)
		for(j=i+1;j<MULNMBOFSPL;j++)
		{
			if(m_iMulIndex[i]>m_iMulIndex[j])
			{
				k=m_iMulIndex[i];
				m_iMulIndex[i]=m_iMulIndex[j];
				m_iMulIndex[j]=k;
			}
		}
}

//
//	根据通道1~30是否启用，设置对应选项可否被选中
//
void CPtcrView::OnUpdatePlot0(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(0,pCmdUI);
}

void CPtcrView::OnUpdatePlot1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(1,pCmdUI);
}

void CPtcrView::OnUpdatePlot2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(2,pCmdUI);
}

void CPtcrView::OnUpdatePlot3(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(3,pCmdUI);
}

void CPtcrView::OnUpdatePlot4(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(4,pCmdUI);
}

void CPtcrView::OnUpdatePlot5(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(5,pCmdUI);
}

void CPtcrView::OnUpdatePlot6(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(6,pCmdUI);
}

void CPtcrView::OnUpdatePlot7(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(7,pCmdUI);
}

void CPtcrView::OnUpdatePlot8(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(8,pCmdUI);
}

void CPtcrView::OnUpdatePlot9(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(9,pCmdUI);
}

void CPtcrView::OnUpdatePlot10(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(10,pCmdUI);
}

void CPtcrView::OnUpdatePlot11(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(11,pCmdUI);
}

void CPtcrView::OnUpdatePlot12(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(12,pCmdUI);
}

void CPtcrView::OnUpdatePlot13(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(13,pCmdUI);
}

void CPtcrView::OnUpdatePlot14(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(14,pCmdUI);
}

void CPtcrView::OnUpdatePlot15(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(15,pCmdUI);
}

void CPtcrView::OnUpdatePlot16(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(16,pCmdUI);
}

void CPtcrView::OnUpdatePlot17(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(17,pCmdUI);
}

void CPtcrView::OnUpdatePlot18(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(18,pCmdUI);
}

void CPtcrView::OnUpdatePlot19(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(19,pCmdUI);
}

void CPtcrView::OnUpdatePlot20(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(20,pCmdUI);
}

void CPtcrView::OnUpdatePlot21(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(21,pCmdUI);
}

void CPtcrView::OnUpdatePlot22(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(22,pCmdUI);
}

void CPtcrView::OnUpdatePlot23(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(23,pCmdUI);
}

void CPtcrView::OnUpdatePlot24(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(24,pCmdUI);
}

void CPtcrView::OnUpdatePlot25(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(25,pCmdUI);
}

void CPtcrView::OnUpdatePlot26(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(26,pCmdUI);
}

void CPtcrView::OnUpdatePlot27(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(27,pCmdUI);
}

void CPtcrView::OnUpdatePlot28(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(28,pCmdUI);
}

void CPtcrView::OnUpdatePlot29(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdatePlot(29,pCmdUI);
}

//
//	根据通道i+1是否启用，设置对应选项可否被选中
//
void CPtcrView::OnUpdatePlot(int i, CCmdUI *pUI)
{

	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->OpenFlag==TRUE)
		if(pDoc->m_rt.m_rtSave.m_bChannels[i]==TRUE)
			pUI->Enable();
		else
			pUI->Enable(FALSE);
	else
		pUI->Enable(FALSE);
	
	if(pDoc->OpenFlag==TRUE)
	{
		if(m_bClickMenu[i]==TRUE)
			pUI->SetCheck();
		else
			pUI->SetCheck(0);
	}
		
}

//
//	根据程序运行状态、文件打开、显示方式，设置“数据显示”选项是否可被选中
//
void CPtcrView::OnUpdateWndData(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdateWnd(pCmdUI,3);
}

//
//	根据程序运行状态、文件打开、显示方式，设置“多曲线显示”选项是否可被选中
//
void CPtcrView::OnUpdateWndMulti(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdateWnd(pCmdUI,2);
}

//
//	根据程序运行状态、文件打开、显示方式，设置“参数显示”选项是否可被选中
//
void CPtcrView::OnUpdateWndReference(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdateWnd(pCmdUI,4);
}

//
//	根据程序运行状态、文件打开、显示方式，设置“单曲线显示”选项是否可被选中
//
void CPtcrView::OnUpdateWndSingle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdateWnd(pCmdUI,1);	
}

//
//	根据程序运行状态、文件打开、显示方式，设置对应的显示设置选项是否可被选中
//
void CPtcrView::OnUpdateWnd(CCmdUI *pUI, int i)
{
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

 if(pDoc->m_Running==FALSE)
 {
	 if(pDoc->OpenFlag==TRUE)
	{;
		pUI->Enable();
		
		if(i==m_uFlag )
			pUI->SetCheck(1);
    	else
			pUI->SetCheck(0);
	}
	else
		pUI->Enable(FALSE);
 }
  else if(pDoc->m_Running==TRUE)
	if((i==1)||(i==5))
	{;
		pUI->Enable();
		
		if(i==m_uFlag )
			pUI->SetCheck(1);
    	else
			pUI->SetCheck(0);
	}
	else
		pUI->Enable(FALSE);
}

//
//	根据显示设置，操作窗口，更新多曲线列表和选中状态
//
void CPtcrView::OnWnd()
{
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i;

	if(m_uFlag==3 || m_uFlag==4)
	{
		m_gCtrl.ShowWindow(SW_SHOW);
		Invalidate();
	}
	else
		m_gCtrl.ShowWindow(SW_HIDE);

	if(m_uFlag!=2)
	{
//		for(i=0;i<5;i++)
		for(i=0;i<MULNMBOFSPL;i++)

		m_iMulIndex[i]=100;
	}
	
	if(m_uFlag!=1||m_uFlag!=2)
		for(i=0;i<NMBOFSPL;i++)
			m_bClickMenu[i]=FALSE;
	
	if(m_uFlag==1)
		m_bClickMenu[pDoc->GetIndex()]=TRUE;
		
	pDoc->UpdateAllViews(NULL);
}

//
//	根据显示对象为曲线或数字，设置“复制”选项可用
//
void CPtcrView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_uFlag==3||m_uFlag==4)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

//
//	将显示的数据或参数复制到剪贴板
//
void CPtcrView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CSharedFile sf(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT);
		
	// Place clipboard data in the shared memory file
	sf.Write(m_gCtrl.GetClip(),m_gCtrl.GetClip().GetLength()); 

	if (sf.GetLength() > 0)
	{
		// Put the data on the clipboard
		if ( !OpenClipboard() )
		{
			AfxMessageBox( "Cannot open the Clipboard" );
			return;
		}

		if(!EmptyClipboard() )
		{
			AfxMessageBox( "Cannot empty the Clipboard" );
			return;
		}

		if (SetClipboardData(CF_TEXT, sf.Detach()) == NULL )
		{
			AfxMessageBox( "Unable to set Clipboard data" );
			CloseClipboard();
			return;
		}
			
		CloseClipboard();					
	}
}

//
//	进行“万用表…”设置
//
void CPtcrView::OnSerialportF45settings() 
{
	// TODO: Add your command handler code here
	F45=1;
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_sPortF45.m_SPAvailable==TRUE)
  {
		MessageBox("万用表已通讯成功!","提示",MB_OK);
		return;
  }

	CComCfg *dlg=new CComCfg(pDoc);
	
	dlg->DoModal();
		
	delete dlg;

	CManCmd *d=new CManCmd(pDoc);
 
	char *cmd;
	if(pDoc->MultiMeter==1) cmd="OHMS";
	else if(pDoc->MultiMeter==2) cmd="R0";
	else if(pDoc->MultiMeter==3){
	   if(pDoc->w2w4==0)cmd="S120M";
	   else cmd="S130S";}
   else if(pDoc->MultiMeter==4){
	   if(pDoc->w2w4==0)cmd="SYST:REMOTE";
	   else cmd="SYST:REMOTE";
   }
   else if(pDoc->MultiMeter==5){
	   if(pDoc->w2w4==0)cmd=":INIT:CONT ON;:ABORT;:SENS:FUNC 'RES'";
//	   else cmd=":INIT:CONT ON;:ABORT;:SENS:FUNC 'FRES'";
 	   else cmd=":INIT:CONT ON;:SENS:FUNC 'FRES'";
  } 
   else { cmd="OHMS";
	}

	d->m_Cmd=cmd;

	d->DoModal();
	delete d; 

	return ;
	
}

//
//	路由和调度命令消息
//
BOOL CPtcrView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//
//	进行“万用表命令”
//
void CPtcrView::OnManualCmd() 
{
    char *cmd="meas?";
//	char results[128];
	// TODO: Add your command handler code here

	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

F45=1;

   if(pDoc->MultiMeter==1)cmd="meas?";
   else if(pDoc->MultiMeter==2)cmd="?";
   else if(pDoc->MultiMeter==3){
	   if(pDoc->w2w4==0)cmd="S120M";
	   else cmd="S130S";
   }
   else if(pDoc->MultiMeter==4){
	   if(pDoc->w2w4==0)cmd="MEAS:RESISTANCE?";
	   else cmd="MEAS:FRESISTANCE?";
   }
   else  if(pDoc->MultiMeter==5){
	   if(pDoc->w2w4==0)cmd="MEAS:RESISTANCE?;:INIT:CONT ON";
	   else cmd="MEAS:RESISTANCE?;:INIT:CONT ON";
   }
   else cmd="meas?";

	CManCmd *d=new CManCmd(pDoc);
d->m_Cmd=cmd;
	d->DoModal();
	delete d;
	return;	
}

//
//	进行“温控表…”设置
//
void CPtcrView::OnSerialportSettings() 
{
	// TODO: Add your command handler code here
   F45=0;
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_sPort.m_SPAvailable==TRUE)
  {
		MessageBox("温控表已通讯成功!","提示",MB_OK);
		return;
  }
    CComCfg *dlg=new CComCfg(pDoc);
	
	dlg->DoModal();
		
	delete dlg;

	CManCmd *d=new CManCmd(pDoc);
 char *cmd="DS";
d->m_Cmd=cmd;

	d->DoModal();
	delete d; 
	
	return ;	
}

//
//	停止测试程序
//
bool CPtcrView::OnCmdStop() 
{

	// TODO: Add your command handler code here
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    CMainFrame *pmWnd;
	pmWnd=(CMainFrame *)AfxGetMainWnd();
 	
	char results[128];
    char cmd[80]="SB S";	
    int Read[10];

//	pDoc->OnAppExit();
//	return TRUE;

if(pDoc->m_Running)
	{
		if(::MessageBox(NULL,"确定要终止控制?","PTCR R-T",MB_YESNO|MB_ICONQUESTION)==IDNO)
    		return FALSE;
	    ::SendMessage(AfxGetMainWnd()->m_hWnd,WM_STATUS_MESSAGE,0,AFX_IDS_SENDCMD);

	    SendMessage(WM_COMMAND,ID_FILE_SAVE,0);

	}

 	  if(pDoc->ZWX==0){  
	   if(pDoc->m_sPort.m_SPAvailable)
		  if(pDoc->m_sPort.m_rxdata.Sr253BCC==2){
			  pDoc->ReadPvsv(cmd,results,4,3,2);
    	      pDoc->ReadPvsv(cmd,results,4,3,2);
		  }
		  else if((pDoc->m_sPort.m_rxdata.sr==93)|| (pDoc->m_sPort.m_rxdata.sr==83)){
			    pDoc->SrRead("011R05000",Read);
            	pDoc->SetSr93("011W05090,",0,TRUE);
               Sleep(500);
		    	pDoc->SetSr93Temp(0);//lby SV 0
               Sleep(500);
		   	pDoc->SetSr93("011W05090,",0,TRUE);
            if(pDoc->m_sPort.m_rxdata.sr==83)
				pDoc->SetSr93("011W01860,",1,FALSE);//StdBy
		  }
		  else if(pDoc->m_sPort.m_rxdata.sr==13)
		  {
			   pDoc->SetSr93("011W05010,",0,TRUE);
               Sleep(1000);
		       pDoc->SetSr93Temp(0);//lby SV 0
               Sleep(500);
 
		  }
	  
	  }
	  else{
		  pDoc->Heat(0);
		  pDoc->SetC(7,0);
          pDoc->SetC(2,0);
          pDoc->SetC(2,1); //stop Heat
	  } 
    pDoc->m_Running=FALSE; 
	 pDoc->m_rt.isRunning=pDoc->m_Running;

	 if((pDoc->m_sPortF45.m_SPAvailable==FALSE) && (pDoc->m_sPort.m_SPAvailable==FALSE)) 
          _exit(0);
/*lby		if(pDoc->m_sPortF45.m_SPAvailable==TRUE)  
			pDoc->m_sPortF45.~CSerialPort();
		if(pDoc->m_sPort.m_SPAvailable==TRUE)  
			pDoc->m_sPort.~CSerialPort();
*/
	 // ::MessageBox(NULL,"测量控制已终止!","PTCR R_T",MB_OK);
	KillTimer(10004);
		if(::MessageBox(NULL,"确定要退出RT系统?","PTCR R-T",MB_YESNO|MB_ICONQUESTION)==IDNO)
    		return FALSE; 
		else _exit(0);
	return TRUE;
}

//
//	根据参数设置温度（通讯协议Sr253）
//
bool CPtcrView::SetSr253Exec()
{
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	char results[128];
    char cmd[80]="SB C";	
	::SendMessage(AfxGetMainWnd()->m_hWnd,WM_STATUS_MESSAGE,0,AFX_IDS_SENDCMD);
	pDoc->ReadPvsv(cmd,results,4,3,2);

	pDoc->m_Running=TRUE;
	pDoc->m_rt.isRunning=pDoc->m_Running;
	return TRUE;
}

//
//	根据读取的PVSV值与参数temp，设置温度（通讯协议Sr253）
//
bool CPtcrView::SetSr253Temp(int Sv, float temp) 
{	char results[128];
    char cmd[80]="SV 01,+000.0";
	float temp0=1.5;
		// TODO: Add your command handler code here
	int Sr253BCC=2;

	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  Sr253BCC=pDoc->m_sPort.m_rxdata.Sr253BCC;
  if(Sr253BCC==2){
	   sprintf(cmd,"SV %02d,%+06.1f",Sv,temp);
		pDoc->ReadPvsv(cmd,results,4,3,Sr253BCC);
        m_SvNumber=Sv;
  }
  else {//Sr253BCC=4
  
   pDoc->SetSr93Temp(temp);
   m_SvNumber=1;
  }
  return TRUE;	
}

//
//	进行“通道电阻设置”
//
void CPtcrView::OnChanSet() 
{
	// TODO: Add your command handler code here
  char results[80];
  char *p;
  int Read[10];
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
  
	if(pDoc->m_rt.ReadZeroResi==FALSE){
		pDoc->m_rt.ReadZero(); 
		pDoc->OnNewDocument();
	}
	
	DetectCom();

	CSetTemp *dd=new CSetTemp(pDoc);
    dd->OpenNptem();
	delete dd;
 //lby  if( pDoc->MultiMeter==1)
//lby if(pDoc->STARTDOT==0) OnSetTempStage();

 if(pDoc->ZWX!=1)
//	 if(pDoc->m_sPort.m_rxdata.sr==93)
	 if(pDoc->m_Running==0)
	 if(pDoc->m_sPort.m_rxdata.Sr253BCC==4)
  {
	 if(pDoc->m_sPort.m_rxdata.sr==13)
		 pDoc->SetSr93("011W05060,",1,FALSE);//EV_CH

	     pDoc->SetSr93("011W05000,",5,FALSE);//EV1 AH
	  	//	pDoc->SetSr93("011W05030,",3,FALSE);

		 pDoc->ReadSr253();
 	 if(pDoc->m_sPort.m_rxdata.sr==93)
	 {
         pDoc->SrRead("011R07050",Read);

	     if(pDoc->m_rt.isChangeRange==TRUE){
	    if(( pDoc->m_PV<0)&&(Read[0]!=31))
			pDoc->SetSr93("011W07050,",31,FALSE);//change range 0.0-200.0
        else if(( pDoc->m_PV>=0)&&(Read[0]==31)&&(pDoc->m_PV<180))
			pDoc->SetSr93("011W07050,",34,FALSE);//change range 0.0-200.0 to -200~600

	  }
	 }
  }

	if(pDoc->m_Running==0)
  if(( pDoc->MultiMeter==1)||( pDoc->MultiMeter==5))
  {
	strcpy(results,F45SN);
 if( pDoc->MultiMeter==1)pDoc->ReadPvsv("ohms\r",results,4,3,6);
	pDoc->ReadPvsv("*idn?\r",results,4,3,6);
	p=strstr(results,F45SN);
  /* if(p==NULL)
	{ if(!strstr(results,"6961036"))//gaoli8048002
     if(!strstr(results,"7726014"))//蜂窝
    if(!strstr(results,"6814027"))//陶瓷中心
     if(!strstr(results,"9036027"))//new 
	 if(!strstr(results,"8581046"))//new 
     if(!strstr(results,"8581027"))//new Linzhi
      if(!strstr(results,"8518018"))//new Linzhi
      if(!strstr(results,"8641018"))//new fenxiao
       if(!strstr(results,"8581059"))//new
      if(!strstr(results,"8579019"))//dongguan长龙
	  if(!strstr(results,"7815001")) //xi'an radiao 2 //7874042shenggd
	  if(!strstr(results,"7620047"))//anpeilong
	  if(!strstr(results,"8452005"))//ZWXCnewLuwenzhong
	  if(!strstr(results,"8451044"))//ZWXCnew桂林电子工业学院
     if(!strstr(results,"8159024"))// 天成 
      if(!strstr(results,"8145048"))//newanhuiheqingyuan
	  if(!strstr(results,"7856014"))// NAnjing gongda gaoli
     if(!strstr(results,"8048002"))//NAnjing gongda
      if(!strstr(results,"8048022"))//anhuiheqingyuan  
	  if(!strstr(results,"8421006"))//new 715  //7645056 7688048JK
	  if(!strstr(results,"7645056"))//new 715  //7645056 7688048JK
	  if(!strstr(results,"7688048"))//new 715  //7645056 7688048JK
      if(!strstr(results,"8048019"))//长沙.tongbao  7645106RT7868045VISK
      if(!strstr(results,"7865019"))//长沙.luoyang  7301183better 
	  if(!strstr(results,"8048020"))//Shenzhen.FM 
	  if(!strstr(results,"2000,0921455"))
	  {//keithley 2000
		      MessageBox("请使用正确的万用表!","提示",MB_OK);
		   return;
		 }
	}*/
  }//	Detect F45;

	   
	   CNameResi *d=new CNameResi(pDoc);
       pDoc->Init8253();
	   d->DoModal();
      delete d ;	

	if(pDoc->m_Running==0){
	  if(::MessageBox(NULL,"控温方式设置?","PTCR R-T",MB_YESNO|MB_ICONQUESTION)==IDNO)
	    return;	
	  else 	OnSetTempStage();

	  if(::MessageBox(NULL,"开始RT测试?","PTCR R-T",MB_YESNO|MB_ICONQUESTION)==IDNO)
	    return;	
	  else 	
		  OnCmdGo();
	}
}

//
//	进行“温控表命令”
//
void CPtcrView::OnSr253Cmd() 
{
	// TODO: Add your command handler code here
 F45=0;
    char cmd[80];
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
   int Read[10];
   char results[80];


 
	 CManCmd *d=new CManCmd(pDoc);
 
    d->m_Cmd=cmd;
	d->DoModal();
	delete d;
	return;		
}

//
//	读取并处理测量的阻值数据
//
void CPtcrView::ReadResiAll(int j) 
{
	// TODO: Add your control notification handler code here
    char *cmd="S120S\r";
	char results[128];
    int Sr253BCC=6;
   float resi0;
    int ChanNo;
	static int SwitchRange=0;
	int RepeatTimes=3;

	CPtcrDoc* m_pDoc = GetDocument();
	ASSERT_VALID(m_pDoc);

    m_pDoc->m_ReadingF45=0;

	for(ChanNo=0;ChanNo<NMBOFSPL;ChanNo++){
		if(m_pDoc->m_rt.m_rtSave.m_bChannels[ChanNo]==FALSE)continue;
		m_pDoc->OutChan(ChanNo+1);
		m_pDoc->OutChan(ChanNo+1);
	   if((m_pDoc->m_sPortF45.m_rxdata.m_MultiMeter==4)||(m_pDoc->m_sPortF45.m_rxdata.m_MultiMeter==5))
		   m_pDoc->DelayTime(1);
	   else
		   m_pDoc->DelayTime(4);

    	m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(RepeatTimes);

 if((m_pDoc->MultiMeter==3)&&(m_pDoc->w2w4==1)&&(SwitchRange==0))
 {	if(m_pDoc->m_Resistance<10){
	    m_pDoc->ReadPvsv("S130S\r\n",results,4,3,6);
			m_pDoc->DelayTime(4);
    	m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(RepeatTimes);
			 SwitchRange=1;
		}
 }
 if((m_pDoc->MultiMeter==3)&&(m_pDoc->w2w4==1)&&(SwitchRange==1))
 {
	if(m_pDoc->m_Resistance>1e8){
	    m_pDoc->ReadPvsv("S130M\r\n",results,4,3,6);
			m_pDoc->DelayTime(4);
    	m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(RepeatTimes);
			 SwitchRange=0;
		}
 }


 if(m_pDoc->m_Resistance>=m_pDoc->m_rt.m_rtSave.m_SpecialR)
 {
   if(m_pDoc->m_HT12D==0)m_pDoc->Init8253();
   m_pDoc->OutChan(ChanNo+1); //lby2003/3/26
   m_pDoc->DelayTime(3);
   m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(RepeatTimes);
 }
 else if(m_pDoc->m_Resistance>=1e7)
 {
		m_pDoc->DelayTime(2);
    	m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(RepeatTimes);
 }
// else if(m_pDoc->m_Resistance>=1e5){
//			m_pDoc->DelayTime(1);
 //   	m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(RepeatTimes);
//		}


 if(m_pDoc->m_rt.m_rtSave.m_fPtc[ChanNo][j-1]<m_pDoc->m_Resistance/10)
 {//当前电阻值大于前一电阻值10倍，即发生跳变时重测，变大
   if(m_pDoc->m_HT12D==0)m_pDoc->Init8253();
   m_pDoc->OutChan(ChanNo+1); //lby2003/3/26
   m_pDoc->DelayTime(3);
   m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(RepeatTimes);
  }
else if(m_pDoc->m_rt.m_rtSave.m_fPtc[ChanNo][j-1]>2*m_pDoc->m_Resistance)
 {//前一电阻值大于当前电阻值4倍，即发生跳变时重测,变小
   if(m_pDoc->m_HT12D==0)m_pDoc->Init8253();
   m_pDoc->OutChan(ChanNo+1); //lby2003/3/26
   m_pDoc->DelayTime(3);
   m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(RepeatTimes);
  }	
	
resi0=m_pDoc->m_Resistance;

if(m_pDoc->m_Resistance>=m_pDoc->m_rt.m_rtSave.m_SpecialR)
 {
   if(m_pDoc->m_HT12D==0)m_pDoc->Init8253();
   m_pDoc->OutChan(ChanNo+1); //lby2003/3/26
   m_pDoc->DelayTime(3);
   m_pDoc->m_Resistance=m_pDoc->ReadResiRepeat(RepeatTimes);
 }

   //     m_pDoc->m_Resistance=resi0;
		m_pDoc->m_rt.m_rtSave.m_fPtc[ChanNo][j]=m_pDoc->m_Resistance;
        
		if(m_pDoc->m_rt.m_rtSave.m_CheckZero==TRUE){
           m_pDoc->m_rt.m_fResi[ChanNo]=m_pDoc->m_Resistance-m_pDoc->m_rt.m_Zeroresi[ChanNo];
	   	m_pDoc->m_rt.m_rtSave.m_fPtc[ChanNo][j]=m_pDoc->m_Resistance-m_pDoc->m_rt.m_Zeroresi[ChanNo];
        m_pDoc->m_Resistance=m_pDoc->m_Resistance-m_pDoc->m_rt.m_Zeroresi[ChanNo];
		}
        if(m_pDoc->m_rt.m_fResi[ChanNo]<0)m_pDoc->m_rt.m_fResi[ChanNo]=0.0001;
	}


   if(m_pDoc->m_HT12D==0) m_pDoc->Init8253();

		  if(m_pDoc->ZWX==1) {
	m_pDoc->m_Pt100_1=m_pDoc->ReadPt100(m_pDoc->Pt100Chan_1);
    m_pDoc->m_PV=m_pDoc->m_Pt100_1;
    m_PV=m_pDoc->m_PV;
		  }
}

//
//	检测串口
//
void CPtcrView::DetectCom() 
{
	// TODO: Add your command handler code here
     CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();

	if(pDoc->m_Running)
	{
		MessageBox("控温已经开始!","Ptcr",MB_OK);
		return;
	}
	if(!pDoc->m_sPortF45.m_SPAvailable)
	{
		MessageBox("初始化万用表串行口!","Ptcr",MB_OK);
		F45=1;
//	ASSERT_VALID(pDoc);
    CComCfg *dlg=new CComCfg(pDoc);
	
	dlg->DoModal();

    delete dlg;
	}

if(pDoc->DigitController!=0)
	if(!pDoc->m_sPort.m_SPAvailable)
	{
		MessageBox("初始化温控表串行口!","Ptcr",MB_OK);
		F45=0;
//	ASSERT_VALID(pDoc);
       CComCfg *dlg=new CComCfg(pDoc);
	   dlg->DoModal();
	   delete dlg;	
	}
}

//
//	设备ZWX_B温度报警设定，温度设定，温度斜率运行设定
//
void CPtcrView::SetTemp_ZWXB(int j) 
{
     CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();
char results[128];

	   char cmd1[128];
	   char cmd[128];

//pDoc->m_rt.m_Raising=1;
//pDoc->m_rt.m_Raising=1; 
 if(pDoc->m_rt.m_Raising==1){
       sprintf(cmd1,"ED 1,0,4,%+06.1f;",(pDoc->stemp[j]+30));
	   pDoc->ReadPvsv(cmd1,results,4,3,2);
 
	   //    if(j==pDoc->m_rt.StartDot)

      if(j==pDoc->m_rt.m_roomtemp_dot)
	  {
        if(pDoc->m_rt.m_rtSave.Ramp[0]>=0.3)   sprintf(cmd,"RP 000.3,001.0");
        else sprintf(cmd,"RP %05.1f,%05.1f",pDoc->m_rt.m_rtSave.Ramp[0],1.000);
	    pDoc->ReadPvsv(cmd,results,4,3,2);
	  }
      else if((j>=pDoc->m_rt.m_roomtemp_dot+1)&&(j<=pDoc->m_rt.m_roomtemp_dot+5))
	  {
        if(pDoc->m_rt.m_rtSave.Ramp[0]>=0.5)   sprintf(cmd,"RP 000.5,001.0");
        else sprintf(cmd,"RP %05.1f,%05.1f",pDoc->m_rt.m_rtSave.Ramp[0],1.000);
	    pDoc->ReadPvsv(cmd,results,4,3,2);
	  }
	  else if(pDoc->m_Pt100 < pDoc->m_rt.m_rtSave.MaxT[0])
	  {
 	    sprintf(cmd,"RP %05.1f,%05.1f",pDoc->m_rt.m_rtSave.Ramp[0],1.000);
	    pDoc->ReadPvsv(cmd,results,4,3,2);
	  }
	  else 
	  {
	      sprintf(cmd,"RP %05.1f,%05.1f",pDoc->m_rt.m_rtSave.Ramp[1],1.000);
          pDoc->ReadPvsv(cmd,results,4,3,2);
	  }

	     if(j%2){
		   SetSr253Temp(2, pDoc->stemp[j]-0.1);
		   SetSr253Temp(2, pDoc->stemp[j]);
           sprintf(cmd,"SN 02");
	       pDoc->ReadPvsv(cmd,results,4,3,2);
           sprintf(cmd,"SN 02");
	       pDoc->ReadPvsv(cmd,results,4,3,2);
		 }
	  	 else {
	       SetSr253Temp(1, pDoc->stemp[j]-0.1);
	       SetSr253Temp(1, pDoc->stemp[j]);
  //         SetSr253Exec();
 //        sprintf(cmd,"SN 01");
//	       pDoc->ReadPvsv(cmd,results,4,3,2);
 //             SetSr253Exec();
      sprintf(cmd,"SN 01");
	       pDoc->ReadPvsv(cmd,results,4,3,2);
           sprintf(cmd,"SN 01");
	       pDoc->ReadPvsv(cmd,results,4,3,2);
		 }


		 pDoc->m_rt.m_Raising=2;
	
	 }//温度设定

}

//
//	设备ZWX_C温度报警设定，温度设定，温度斜率运行设定
//
void CPtcrView::SetTemp_ZWXC(int j) 
{
     CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();

    int ediff;
	int bpid;
	int wvn;

	int PidTimes;
	PidTimes=60/pDoc->Pidtime;


  if(pDoc->m_rt.m_rtSave.m_TIME==0){
	if(pDoc->m_Pt100 <= pDoc->m_rt.m_rtSave.MaxT[0]){
 //    pDoc->m_SV=	pDoc->m_Pt100;
	  if(pDoc->STARTDOT<=1)pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[0]/PidTimes/2+pDoc->m_SV;
	  else pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[0]/PidTimes+pDoc->m_SV;
	}
    else 
	  pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[1]/PidTimes+pDoc->m_SV;

  }
  else {

  if(pDoc->m_rt.m_Raising==1){
	 if(pDoc->m_Pt100 <= pDoc->m_rt.m_rtSave.MaxT[0]){
	  pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[0]/PidTimes+pDoc->stemp[j-1];
	}
    else 
	  pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[1]/PidTimes+pDoc->stemp[j-1];
  pDoc->m_rt.m_Raising=2;
// 			pDoc->m_rt.m_Pt=pDoc->m_rt.m_PV;
 }
  else{
	if(pDoc->m_Pt100 <= pDoc->m_rt.m_rtSave.MaxT[0]){
 //    pDoc->m_SV=	pDoc->m_Pt100;
	pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[0]/PidTimes+pDoc->m_SV;
	}
    else 
	  pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[1]/PidTimes+pDoc->m_SV;
  }
	if(pDoc->m_SV > pDoc->stemp[j]) pDoc->m_SV = pDoc->stemp[j];
 
  }
 		pDoc->m_rt.m_SV=pDoc->m_SV;
		pDoc->m_rt.m_PV=pDoc->m_PV;
        pDoc->m_rt.m_tSr253=pDoc->m_rt.m_PV;
    bpid= pDoc->TempRange(pDoc->m_SV);
	ediff=( pDoc->m_SV- pDoc->m_PV)*5.0;
	  /*Remedy 2*/
// pDoc->KP=1.8;
// pDoc->KI=30;
// pDoc->KD=4.0;

	wvn=pDoc->Pid(ediff,bpid);
      wvn = (wvn<bpid) ? bpid : wvn;
	wvn = (wvn<0) ? 0 : wvn;
    pDoc->m_rt.wvn=wvn;
	pDoc->Heat(wvn);
}

//
//	设备ZWX_D温度报警设定，温度设定，温度斜率运行设定
//
void CPtcrView::SetTemp_ZWXD(int j) 
{
     CPtcrDoc *pDoc;
  	 pDoc=(CPtcrDoc *)GetDocument();
    static int change=0;
    static int times=0;
 
//		change=0;
//		pDoc->SetSr93("011W07050,",34,FALSE);
//		pDoc->SetSr93("011W05090,",pDoc->stemp[j]+20,TRUE);
		
      static float SetV=0;
	int PidTimes;
	PidTimes=60/pDoc->Pidtime;

	if(j==pDoc->m_rt.m_roomtemp_dot){
		  pDoc->STARTDOT++;
          pDoc->m_rt.Cooling=0;
          j=pDoc->STARTDOT;
	  }
  if(pDoc->m_rt.isChangeRange==TRUE){
/*	    change=0;
		pDoc->SetSr93("011W05080,",0,FALSE);//EV2 OFF
	 	pDoc->SetSr93("011W07050,",34,FALSE);
 		pDoc->SetSr93("011W05080,",5,FALSE);//EV2 HA
        pDoc->SetSr93("011W05090,",pDoc->stemp[j]+10,TRUE);
*/

    if(pDoc->m_rt.m_Raising==1)
	 if(pDoc->m_sPort.m_rxdata.sr==93)
	  if((pDoc->stemp[j]>=180)&&(change==0)&&(pDoc->m_PV>=180)){
		
		pDoc->SetSr93("011W05080,",0,FALSE);//EV2 OFF
        Sleep(500);
		pDoc->SetSr93("011W07050,",31,FALSE);
        Sleep(1000);
 		pDoc->SetSr93("011W05080,",5,FALSE);//EV2 HA
        Sleep(200);
        pDoc->SetSr93("011W05090,",pDoc->stemp[j]+10,TRUE);
        Sleep(200);
			 pDoc->SetSr93Temp(pDoc->m_SV);
	    change=1;
	  }
  }

  if(pDoc->m_rt.m_rtSave.m_TIME==0){
        if(pDoc->m_rt.m_Raising==1)pDoc->m_SV =pDoc->m_PV;//lby2003/5/21
		else pDoc->m_SV =SetV;

//	  pDoc->m_SV = SetV; 
  
//  pDoc->m_SV=38;

//	 pDoc->m_SV=25;
	 if(pDoc->m_rt.m_Raising==1)
		  pDoc->SetSr93("011W05010,",pDoc->stemp[j]+40,TRUE);//设置上限保护温度
		
//	  if(pDoc->m_rt.Cooling==0)
//		  pDoc->SetSr93("011W05090,",pDoc->stemp[j]+20,TRUE);//设置上限保护温度


	  if(pDoc->m_Pt100 <= pDoc->m_rt.m_rtSave.MaxT[0]){
 //    pDoc->m_SV=	pDoc->m_Pt100;
	  
//			pDoc->SetSr93("011W05090,",pDoc->stemp[j]+20,TRUE);//设置上限保护温度
//pDoc->m_SV=35;
	    if(pDoc->STARTDOT-pDoc->m_rt.StartDot <=1)//lby2003/6
		  pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[0]/PidTimes/2+pDoc->m_SV;
	    else pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[0]/PidTimes+pDoc->m_SV;
	
	  }
      else 
	   pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[1]/PidTimes+pDoc->m_SV;
       SetV=pDoc->m_SV;
  }
  else {//间隔升温
       
	  if((j==pDoc->m_rt.StartDot)&&(pDoc->m_rt.Cooling==1)){
		  pDoc->m_SV=pDoc->stemp[j];
	  }
	  else {

          if(pDoc->m_rt.m_Raising==1){
			  pDoc->m_SV =pDoc->m_PV;//lby2003/5/21
              if(pDoc->m_SV<pDoc->stemp[j-1])
				  pDoc->m_SV=pDoc->stemp[j-1];
		  }
	      else pDoc->m_SV =SetV;
	 

    if(pDoc->m_rt.m_Raising==1){

/*		 if(pDoc->m_Pt100 <= pDoc->m_rt.m_rtSave.MaxT[0])
			 pDoc->SetSr93("011W04070",0.8,TRUE);//设置超调系数
         else 
			 pDoc->SetSr93("011W04070",0.4,TRUE);//设置超调系数
*/
	  if(pDoc->m_sPort.m_rxdata.sr!=13)
		  pDoc->SetSr93("011W05090,",pDoc->stemp[j]+20,TRUE);//设置上限保护温度
      else 
		  pDoc->SetSr93("011W05010,",pDoc->stemp[j]+20,TRUE);//设置上限保护温度

		if(pDoc->m_Pt100 <= pDoc->m_rt.m_rtSave.MaxT[0]){
	    pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[0]/PidTimes+pDoc->stemp[j-1];
	 }
     else 
	  pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[1]/PidTimes+pDoc->stemp[j-1];
      pDoc->m_rt.m_Raising=2;
	}
    else{
 //     pDoc->m_SV =SetV;
		if(pDoc->m_Pt100 <= pDoc->m_rt.m_rtSave.MaxT[0]){
	 
		
       

          if(j==pDoc->m_rt.StartDot)
		    pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[0]/PidTimes/2+pDoc->m_SV;
          else if(j<pDoc->m_rt.StartDot+3)
		    pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[0]/PidTimes/1.5+pDoc->m_SV;
          else 	
		    pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[0]/PidTimes+pDoc->m_SV;
		}
        else  pDoc->m_SV=pDoc->m_rt.m_rtSave.Ramp[1]/PidTimes+pDoc->m_SV;
	}
//    SetV=pDoc->m_SV;

	if(pDoc->m_SV > pDoc->stemp[j]) pDoc->m_SV = pDoc->stemp[j];
 
	  }
  }
//        pDoc->m_rt.m_SV=pDoc->m_SV;
//		pDoc->m_rt.m_PV=pDoc->m_PV;
//        pDoc->m_rt.m_tSr253=pDoc->m_rt.m_PV;
        SetV=pDoc->m_SV;
         if(pDoc->m_rt.m_SV!=pDoc->m_SV)
			 pDoc->SetSr93Temp(pDoc->m_SV);
        pDoc->m_rt.m_SV=pDoc->m_SV;
		pDoc->m_rt.m_PV=pDoc->m_PV;
        pDoc->m_rt.m_tSr253=pDoc->m_rt.m_PV;
//		pDoc->SetSr93("011W05090,",pDoc->stemp[j]+20,TRUE);
     

}

//
//	温度报警设定，温度设定，温度斜率运行设定
//
void CPtcrView::SetTemp(int j) 
{
	CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();
   
	if(pDoc->ZWX==0){
		if(pDoc->m_sPort.m_rxdata.Sr253BCC==2)
			SetTemp_ZWXB(j);//Ramp
        else  SetTemp_ZWXD(j);	
	}
    else SetTemp_ZWXC(j);
}

//
//	判断升温、保温、测量状态
//
void CPtcrView::JudgeTempStage(int j) 
{
	CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();
   
	  if(pDoc->ZWX==0){
		    if(pDoc->m_sPort.m_rxdata.Sr253BCC==2)
		        JudgeTempStage_ZWXB(j);
	        else  JudgeTempStage_ZWXD(j);
	  }
      else JudgeTempStage_ZWXC(j);
}

//
//	判断设备ZWX_D升温、保温、测量状态
//
void CPtcrView::JudgeTempStage_ZWXD(int j) 
{
char results[128];
	   char cmd[128];
	CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();  
	
 if(pDoc->m_rt.m_Raising!=7)
	if(pDoc->m_rt.m_rtSave.m_TIME==0){
   
//匀速升温
	 pDoc->m_rt.m_PV=pDoc->m_Pt100;
 
	 if(pDoc->m_rt.m_PV < pDoc->m_rt.m_rtSave.MaxT[0])
		 pDoc->m_rt.m_rtSave.m_STEP=pDoc->m_rt.m_rtSave.Step[0];
	else pDoc->m_rt.m_rtSave.m_STEP=pDoc->m_rt.m_rtSave.Step[1];

	
	 SetTemp(j);

 
	pDoc->m_rt.m_Raising=2;
	if((pDoc->m_rt.m_PV - pDoc->m_Pt)>=pDoc->m_rt.m_rtSave.m_STEP-0.0)
		{
			pDoc->m_Pt=pDoc->m_rt.m_PV;
            pDoc->m_rt.m_Raising=7;
		}
 }
 else
 {//间隔升温

 	if(j==pDoc->m_rt.m_roomtemp_dot){
		  pDoc->STARTDOT++;
          pDoc->m_rt.Cooling=0;
          j=pDoc->STARTDOT;
	  }

	if(pDoc->stemp[j]<= pDoc->m_rt.m_rtSave.MaxT[0])
	{
		 pDoc->m_rt.m_rtSave.m_TIME=pDoc->m_rt.m_rtSave.soaking[0];
	}
	else {
		pDoc->m_rt.m_rtSave.m_TIME=pDoc->m_rt.m_rtSave.soaking[1];
	}

	 pDoc->m_rt.m_PV=pDoc->m_Pt100;
	 SetTemp(j);
	 pDoc->m_PV=pDoc->m_Pt100;
//	 pDoc->m_rt.m_Raising=2;//lby
    //pDoc->m_rt.m_Raising=2;
	 if(pDoc->m_rt.m_Raising==2)//lby 判断保温状态	  
		 if((pDoc->m_rt.m_rtSave.Step[0]>=8)&&(pDoc->m_PV<=pDoc->m_rt.m_rtSave.MaxT[0])){
				if((pDoc->m_PV>=(pDoc->stemp[j]-2))&&(pDoc->m_PV<=(pDoc->stemp[j]+2.5))){
			         pDoc->m_rt.m_Raising=3;
					 pDoc->m_rt.m_rtSave.m_starttime=CTime::GetCurrentTime();
				}
		 }
		 else if((pDoc->m_rt.m_rtSave.Step[0]>4)&&(pDoc->m_PV<=pDoc->m_rt.m_rtSave.MaxT[0])){
				if((pDoc->m_PV>=(pDoc->stemp[j]-1.5))&&(pDoc->m_PV<=(pDoc->stemp[j]+2))){
			         pDoc->m_rt.m_Raising=3;
					 pDoc->m_rt.m_rtSave.m_starttime=CTime::GetCurrentTime();
				}
		 }
		 else if((pDoc->m_rt.m_rtSave.Step[1]>=8)&&(pDoc->m_PV>pDoc->m_rt.m_rtSave.MaxT[0])){
				if((pDoc->m_PV>=(pDoc->stemp[j]-2))&&(pDoc->m_PV<=(pDoc->stemp[j]+2.5))){
			         pDoc->m_rt.m_Raising=3;
					 pDoc->m_rt.m_rtSave.m_starttime=CTime::GetCurrentTime();
				}
		 }
		 else if((pDoc->m_rt.m_rtSave.Step[1]>=4)&&(pDoc->m_PV>pDoc->m_rt.m_rtSave.MaxT[0])){
				if((pDoc->m_PV>=(pDoc->stemp[j]-1.5))&&(pDoc->m_PV<=(pDoc->stemp[j]+2))){
			         pDoc->m_rt.m_Raising=3;
					 pDoc->m_rt.m_rtSave.m_starttime=CTime::GetCurrentTime();
				}
		 }

		 else {
					if((pDoc->m_PV>=(pDoc->stemp[j]-1.0))&&(pDoc->m_PV<=(pDoc->stemp[j]+1.0))){
			            pDoc->m_rt.m_Raising=3;
					    pDoc->m_rt.m_rtSave.m_starttime=CTime::GetCurrentTime();
					}
//  	   pDoc->UpdateAllViews(NULL);	
		 }
 }
      if(pDoc->m_rt.m_Raising==3){//lby 判断保温时间到否、温度是否达到设定要求，保温结束	  
//lby///
//		   pDoc->DelayTime(pDoc->m_rt.m_rtSave.m_TIME*60);		
         pDoc->m_rt.m_rtSave.m_endtime=CTime::GetCurrentTime();
         CTimeSpan cts;
         cts=pDoc->m_rt.m_rtSave.m_endtime-pDoc->m_rt.m_rtSave.m_starttime;
         pDoc->m_rt.m_rtSave.Soaking = cts.GetTotalSeconds();
 
		 if(pDoc->m_rt.m_TempSoakingCondition==0)
              if( pDoc->m_rt.m_rtSave.Soaking>=pDoc->m_rt.m_rtSave.m_TIME*60)
				          		pDoc->m_rt.m_Raising=0;


        if( pDoc->m_rt.m_rtSave.Soaking>=pDoc->m_rt.m_rtSave.m_TIME*60)
		 {
//		  if(((pDoc->m_Pt100 - pDoc->stemp[j])>=-3)&&((pDoc->m_Pt100 - pDoc->stemp[j])<=3))
   if(pDoc->m_sPort.m_rxdata.sr==13)

			 if((pDoc->m_rt.m_rtSave.Step[0]>=4)&&(pDoc->m_PV<=pDoc->m_rt.m_rtSave.MaxT[0])){
			 if(((pDoc->m_PV - pDoc->stemp[j])>=-2)&&((pDoc->m_PV - pDoc->stemp[j])<=2))
        		pDoc->m_rt.m_Raising=0;
			}
		if((pDoc->m_rt.m_rtSave.Step[1]>=4)&&(pDoc->m_PV>pDoc->m_rt.m_rtSave.MaxT[0])){
			 if(((pDoc->m_PV - pDoc->stemp[j])>=-2)&&((pDoc->m_PV - pDoc->stemp[j])<=2))
        		pDoc->m_rt.m_Raising=0;
			}
  if(((pDoc->m_PV - pDoc->stemp[j])>=-1)&&((pDoc->m_PV - pDoc->stemp[j])<=1))
        		pDoc->m_rt.m_Raising=0;
        

 	   if(pDoc->m_sPort.m_rxdata.sr==13){
          if(pDoc->m_rt.m_TempSoakingCondition==1)
			  if(fabs(pDoc->m_rt.m_tPt100_1-pDoc->m_rt.m_tPt100_2)>1.5)
			     pDoc->m_rt.m_Raising=3;
	   }

      if( pDoc->m_rt.m_rtSave.Soaking>=(pDoc->m_rt.m_rtSave.m_TIME+30)*60)
        		pDoc->m_rt.m_Raising=7;
 

	   pDoc->UpdateAllViews(NULL);	
	  }
 }//end of else

//zjun 2003/5/28
// if(pDoc->m_rt.m_rtSave.m_TIME==0){
int i=0; 
while(1){//判断是否超温\断线/不加热
 pDoc->heatstop=0;

 if(pDoc->m_rt.Cooling==0){
 if(pDoc->m_Pt100_1 > (pDoc->stemp[pDoc->STARTDOT]+20)) 
  { i++;
    pDoc->ReadSr253();
    pDoc->m_PV=pDoc->m_Pt100_1;
    m_PV=pDoc->m_PV;
    if(i>4) {pDoc->heatstop=3;break;}
  }
  else if(pDoc->m_Pt100_1 < (pDoc->stemp[pDoc->STARTDOT]-40)){
    i++;
    pDoc->ReadSr253();
    pDoc->m_PV=pDoc->m_Pt100_1;
    m_PV=pDoc->m_PV;
	if(i>4) {pDoc->heatstop=4;break;}
  }
  else break;
  if(i>1)
    if(pDoc->ZWX!=1){
	  pDoc->m_sPort.m_SPAvailable=0;
      if(pDoc->m_sPort.InitPort(pDoc->m_sPort.m_pOwner))
	  {
	       pDoc->m_sPort.StartMonitoring();
	       AfxGetApp()->DoWaitCursor(1);
	  }	
	}

 }
else break;
 
 }//end of while(1)
//}
    if(pDoc->heatstop==4||pDoc->heatstop==3)
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		OnCmdStop();
		return;
	}

	 if((pDoc->m_rt.m_Raising==0)||(pDoc->m_rt.m_Raising==7)){  //lby 保温结束,开始测量
//if(pDoc->ZWX==0) KillTimer(10001);
  	   pDoc->UpdateAllViews(NULL);	
 pDoc->m_rt.m_Pt=pDoc->m_Pt100_1;
//pDoc->Heat(0);

  if(pDoc->m_sPort.m_rxdata.sr==13)
	  if(pDoc->m_rt.m_Number+6<31){
	pDoc->m_rt.m_rtSave.m_fTem[pDoc->m_rt.m_Number+3][j]= pDoc->m_rt.m_tSr253;
	pDoc->m_rt.m_rtSave.m_fTem[pDoc->m_rt.m_Number+4][j]= pDoc->m_rt.m_tPt100_1;
 	pDoc->m_rt.m_rtSave.m_fTem[pDoc->m_rt.m_Number+5][j]= pDoc->m_rt.m_tPt100_2;
 	pDoc->m_rt.m_rtSave.m_fTem[pDoc->m_rt.m_Number+6][j]= pDoc->m_rt.m_tPt100_3;
 }

 ReadResiAll(j); 
 pDoc->ReadSr253();
pDoc->m_rt.m_Pt=(pDoc->m_rt.m_Pt+pDoc->m_Pt100_1)/2.0;
//pDoc->m_Pt100_1=pDoc->m_rt.m_Pt;
for(int i=0;i<NMBOFSPL;i++){
    if(i<pDoc->m_rt.m_Number)
	{
		if(pDoc->m_sPort.m_rxdata.sr!=13)
		  pDoc->m_rt.m_rtSave.m_fTem[i][j]= pDoc->m_rt.m_Pt;
        else {
			if(i<4)pDoc->m_rt.m_rtSave.m_fTem[i][j]=pDoc->m_rt.m_tPt100;
	        else if(i<8)
		        pDoc->m_rt.m_rtSave.m_fTem[i][j]=pDoc->m_rt.m_tPt100_1;
	        else if(i<12)
		        pDoc->m_rt.m_rtSave.m_fTem[i][j]=pDoc->m_rt.m_tPt100_2;
            else 
	        	pDoc->m_rt.m_rtSave.m_fTem[i][j]=pDoc->m_rt.m_tPt100_3;

		}
	}
 //m_rt.m_tPt100_1=m_Pt100_1;
 //m_rt.m_tPt100_2=m_Pt100_2;
 //m_rt.m_tPt100_3=(m_Pt100+m_Pt100_1+m_Pt100_2)/3;

}
       pDoc->m_rt.m_Raising=1;

  if(pDoc->m_sPort.m_rxdata.sr==13)
	  if(pDoc->m_rt.m_Number+10<31){
	pDoc->m_rt.m_rtSave.m_fTem[pDoc->m_rt.m_Number+7][j]= pDoc->m_rt.m_tSr253;
	pDoc->m_rt.m_rtSave.m_fTem[pDoc->m_rt.m_Number+8][j]= pDoc->m_rt.m_tPt100_1;
 	pDoc->m_rt.m_rtSave.m_fTem[pDoc->m_rt.m_Number+9][j]= pDoc->m_rt.m_tPt100_2;
 	pDoc->m_rt.m_rtSave.m_fTem[pDoc->m_rt.m_Number+10][j]= pDoc->m_rt.m_tPt100_3;
 }	//pDoc->m_rt.m_rtSave.m_fTem[i][j]=pDoc->m_Pt100_1;//lby

       SendMessage(WM_COMMAND,ID_FILE_SAVE,0);	 
       pDoc->m_rt.m_Raising=1;
 
	   

if(pDoc->m_rt.m_rtSave.m_TIME==0){
    if(pDoc->m_PV>(pDoc->m_rt.m_rtSave.m_MaxTemp+1))
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		pDoc->heatstop=2;
		OnCmdStop();
		return;
	}
	   }
else if(pDoc->m_PV>(pDoc->m_rt.m_rtSave.m_MaxTemp+1))
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		pDoc->heatstop=2;
		OnCmdStop();
		return;
	}

 if(pDoc->stemp[pDoc->STARTDOT]>=pDoc->m_rt.m_rtSave.m_MaxTemp)
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		pDoc->heatstop=8;
		OnCmdStop();
		return;
	}


if(pDoc->STARTDOT>=pDoc->m_rt.EndDot)
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		pDoc->heatstop=6;
		OnCmdStop();
		return;
	}

    
    if(pDoc->heatstop==4||pDoc->heatstop==3)
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		OnCmdStop();
		return;
	}
	  
	pDoc->STARTDOT++;
    pDoc->ReadSr253();
 //   pDoc->ReadSr253();
//	pDoc->m_Pt100_1=pDoc->ReadPt100(pDoc->Pt100Chan_1);
    pDoc->m_PV=pDoc->m_Pt100_1;
    m_PV=pDoc->m_PV;
//		 m_SV=pDoc->m_SV; 

	   JudgeTempStage(pDoc->STARTDOT);
	   pDoc->UpdateAllViews(NULL);	
   	   
       if(!SetTimer(10001,pDoc->Pidtime*1000,NULL))
	   {
         MessageBox("定时器资源不足,请退出所有程序后再启动本程序.","错误",MB_OK);
		 return;//20秒刷新界面
	   }

	 }
	return;

}

//
//	判断设备ZWX_C升温、保温、测量状态
//
void CPtcrView::JudgeTempStage_ZWXC(int j) 
{
char results[128];
	   char cmd[128];
	CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();	  
	
 if(pDoc->m_rt.m_Raising!=7)
	if(pDoc->m_rt.m_rtSave.m_TIME==0){
   
//匀速升温
	 pDoc->m_rt.m_PV=pDoc->m_Pt100;
 
	 if(pDoc->m_rt.m_PV < pDoc->m_rt.m_rtSave.MaxT[0]) pDoc->m_rt.m_rtSave.m_STEP=pDoc->m_rt.m_rtSave.Step[0];
	else pDoc->m_rt.m_rtSave.m_STEP=pDoc->m_rt.m_rtSave.Step[1];

	 SetTemp(j);

	 pDoc->m_rt.m_Raising=2;
 
		if((pDoc->m_rt.m_PV - pDoc->m_Pt)>=pDoc->m_rt.m_rtSave.m_STEP-0.0)
		{
			pDoc->m_Pt=pDoc->m_rt.m_PV;
//			pDoc->m_rt.m_Pt=pDoc->m_rt.m_PV;
            pDoc->m_rt.m_Raising=7;
		}
 }
 else
 {//间隔升温

 	if(pDoc->stemp[j]<= pDoc->m_rt.m_rtSave.MaxT[0])
		 pDoc->m_rt.m_rtSave.m_TIME=pDoc->m_rt.m_rtSave.soaking[0];
	else pDoc->m_rt.m_rtSave.m_TIME=pDoc->m_rt.m_rtSave.soaking[1];

	 pDoc->m_rt.m_PV=pDoc->m_Pt100;
	 SetTemp(j);
	 pDoc->m_PV=pDoc->m_Pt100;
//	 pDoc->m_rt.m_Raising=2;
 
	 if(pDoc->m_rt.m_Raising==2)//lby 判断保温状态	  
		    if(pDoc->m_PV>=(pDoc->stemp[j]-2)){
			 pDoc->m_rt.m_Raising=3;
             pDoc->m_rt.m_rtSave.m_starttime=CTime::GetCurrentTime();
//  	   pDoc->UpdateAllViews(NULL);	
			}
      if(pDoc->m_rt.m_Raising==3){//lby 判断保温时间到否、温度是否达到设定要求，保温结束	  
//lby///
//		   pDoc->DelayTime(pDoc->m_rt.m_rtSave.m_TIME*60);		
         pDoc->m_rt.m_rtSave.m_endtime=CTime::GetCurrentTime();
         CTimeSpan cts;
         cts=pDoc->m_rt.m_rtSave.m_endtime-pDoc->m_rt.m_rtSave.m_starttime;
         pDoc->m_rt.m_rtSave.Soaking = cts.GetTotalSeconds();
  
		 if(pDoc->m_rt.m_TempSoakingCondition==0)
              if( pDoc->m_rt.m_rtSave.Soaking>=pDoc->m_rt.m_rtSave.m_TIME*60)
				          		pDoc->m_rt.m_Raising=0;
		 
		 if( pDoc->m_rt.m_rtSave.Soaking>=pDoc->m_rt.m_rtSave.m_TIME*60)
		 {
//		  if(((pDoc->m_Pt100 - pDoc->stemp[j])>=-3)&&((pDoc->m_Pt100 - pDoc->stemp[j])<=3))
	 if(pDoc->m_PV < pDoc->m_rt.m_rtSave.MaxT[0]){
		 if(((pDoc->m_PV - pDoc->stemp[j])>=-2)&&((pDoc->m_PV - pDoc->stemp[j])<=2))
        		pDoc->m_rt.m_Raising=0;
	 }
	 else{	 if(((pDoc->m_PV - pDoc->stemp[j])>=-2)&&((pDoc->m_PV - pDoc->stemp[j])<=1))
        		pDoc->m_rt.m_Raising=0;
	 }
 	     if( pDoc->m_rt.m_rtSave.Soaking>=(pDoc->m_rt.m_rtSave.m_TIME+40)*60)
        		pDoc->m_rt.m_Raising=7;
	   pDoc->UpdateAllViews(NULL);	
		 }
	  }
 }//end of else

//zjun 2002/8/17
// if(pDoc->m_rt.m_rtSave.m_TIME==0){
int i=0; 
while(1){//判断是否超温\断线/不加热
 pDoc->heatstop=0;

  if(pDoc->m_Pt100_1 > pDoc->stemp[pDoc->STARTDOT]+20) 
  { i++;
    pDoc->Init8253();
	pDoc->m_Pt100_1=pDoc->ReadPt100(pDoc->Pt100Chan_1);
    pDoc->m_PV=pDoc->m_Pt100_1;
    m_PV=pDoc->m_PV;
    if(i>4) {pDoc->heatstop=3;break;}
  }
  else if(pDoc->m_Pt100_1 < pDoc->stemp[pDoc->STARTDOT]-40){
    i++;
	pDoc->Init8253();
	pDoc->m_Pt100_1=pDoc->ReadPt100(pDoc->Pt100Chan_1);
    pDoc->m_PV=pDoc->m_Pt100_1;
    m_PV=pDoc->m_PV;
	if(i>4) {pDoc->heatstop=4;break;}
  }
  else break;
 }//end of while(1)
//}
    if(pDoc->heatstop==4||pDoc->heatstop==3)
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		OnCmdStop();
		return;
	}  
    
	 if((pDoc->m_rt.m_Raising==0)||(pDoc->m_rt.m_Raising==7)){  //lby 保温结束,开始测量
//if(pDoc->ZWX==0) KillTimer(10001);
  	   pDoc->UpdateAllViews(NULL);	
 pDoc->m_rt.m_Pt=pDoc->m_Pt100_1;
//pDoc->Heat(0);
 ReadResiAll(j); 

for(int i=0;i<NMBOFSPL;i++)
    pDoc->m_rt.m_rtSave.m_fTem[i][j]= pDoc->m_Pt100_1;

       SendMessage(WM_COMMAND,ID_FILE_SAVE,0);	 
 if(pDoc->m_rt.m_rtSave.m_TIME==0){
    if(pDoc->m_PV>(pDoc->m_rt.m_rtSave.m_MaxTemp+10))
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		pDoc->heatstop=1;
		OnCmdStop();
		return;
	}
	   }
else if(pDoc->m_PV>(pDoc->m_rt.m_rtSave.m_MaxTemp))
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		pDoc->heatstop=1;
		OnCmdStop();
		return;
	}

if(pDoc->stemp[pDoc->STARTDOT]>=pDoc->m_rt.m_rtSave.m_MaxTemp)
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		pDoc->heatstop=8;
		OnCmdStop();
		return;
	}

if(pDoc->STARTDOT>=pDoc->m_rt.EndDot)
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		pDoc->heatstop=6;
		OnCmdStop();
		return;
	}
//	   pDoc->UpdateAllViews(NULL);	

    
    if(pDoc->heatstop==4||pDoc->heatstop==3)
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		OnCmdStop();
		return;
	}  
    
	pDoc->m_rt.m_Raising=1;
    pDoc->STARTDOT++;

	pDoc->m_Pt100_1=pDoc->ReadPt100(pDoc->Pt100Chan_1);
    pDoc->m_PV=pDoc->m_Pt100_1;
    m_PV=pDoc->m_PV;
//		 m_SV=pDoc->m_SV; 

	   JudgeTempStage(pDoc->STARTDOT);
//	   pDoc->UpdateAllViews(NULL);	


   	   
       if(!SetTimer(10001,pDoc->Pidtime*1000,NULL))
	   {
         MessageBox("定时器资源不足,请退出所有程序后再启动本程序.","错误",MB_OK);
		 return;//20秒刷新界面
	   }

	 }
	return;

}

//
//	判断设备ZWX_B升温、保温、测量状态
//
void CPtcrView::JudgeTempStage_ZWXB(int j) 
{
   char results[128];
   char cmd[128];
	CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();	  
	
 if(pDoc->m_rt.m_rtSave.m_TIME==0){
		pDoc->m_rt.m_Raising=2;
 

		if((pDoc->m_rt.m_tPt100-pDoc->m_rt.m_rtSave.MaxT[0]>-5)&&(pDoc->m_rt.m_tPt100-pDoc->m_rt.m_rtSave.MaxT[0]<5)){
			sprintf(cmd,"RP %05.1f,%+05.1f",pDoc->m_rt.m_rtSave.Ramp[1],1.000);
	        pDoc->ReadPvsv(cmd,results,4,3,2);
		}

  	if(pDoc->m_rt.m_PV < pDoc->m_rt.m_rtSave.MaxT[0]) pDoc->m_rt.m_rtSave.m_STEP=pDoc->m_rt.m_rtSave.Step[0];
	else pDoc->m_rt.m_rtSave.m_STEP=pDoc->m_rt.m_rtSave.Step[1];

//lby		if((pDoc->m_rt.m_PV-pDoc->m_rt.m_rtSave.m_fTem[0][j-1])>=pDoc->m_rt.m_rtSave.m_STEP-0.4)
		if((pDoc->m_rt.m_PV - pDoc->m_Pt)>=pDoc->m_rt.m_rtSave.m_STEP-0.0)
		{
			pDoc->m_Pt=pDoc->m_rt.m_PV;
            pDoc->m_rt.m_Raising=7;
		}
 }
 else
 {
 	if(pDoc->stemp[j]<= pDoc->m_rt.m_rtSave.MaxT[0])
		 pDoc->m_rt.m_rtSave.m_TIME=pDoc->m_rt.m_rtSave.soaking[0];
	else pDoc->m_rt.m_rtSave.m_TIME=pDoc->m_rt.m_rtSave.soaking[1];

	if(pDoc->m_rt.m_Raising==1)//lby 判断保温状态	  
  	   pDoc->UpdateAllViews(NULL);	
   
 SetTemp(j);

				if(pDoc->m_rt.m_Raising==2)//lby 判断保温状态	  
		    if(pDoc->m_PV>=(pDoc->stemp[j]-2)){
			 pDoc->m_rt.m_Raising=3;
             pDoc->m_rt.m_rtSave.m_starttime=CTime::GetCurrentTime();
  	   pDoc->UpdateAllViews(NULL);	
			}
      if(pDoc->m_rt.m_Raising==3){//lby 判断保温时间到否、温度是否达到设定要求，保温结束	  
//lby///
//		   pDoc->DelayTime(pDoc->m_rt.m_rtSave.m_TIME*60);		
         pDoc->m_rt.m_rtSave.m_endtime=CTime::GetCurrentTime();
         CTimeSpan cts;
         cts=pDoc->m_rt.m_rtSave.m_endtime-pDoc->m_rt.m_rtSave.m_starttime;
         pDoc->m_rt.m_rtSave.Soaking = cts.GetTotalSeconds();
         
		 if(pDoc->m_rt.m_TempSoakingCondition==0)
              if( pDoc->m_rt.m_rtSave.Soaking>=pDoc->m_rt.m_rtSave.m_TIME*60)
				          		pDoc->m_rt.m_Raising=0;

		 
		 if( pDoc->m_rt.m_rtSave.Soaking>=pDoc->m_rt.m_rtSave.m_TIME*60)
		 {
//		  if(((pDoc->m_Pt100 - pDoc->stemp[j])>=-3)&&((pDoc->m_Pt100 - pDoc->stemp[j])<=3))
	 
			 if(pDoc->m_PV < pDoc->m_rt.m_rtSave.MaxT[0]){
		 if(((pDoc->m_PV - pDoc->stemp[j])>=-2)&&((pDoc->m_PV - pDoc->stemp[j])<=2))
        		pDoc->m_rt.m_Raising=0;
	 }
	 else{	 if(((pDoc->m_PV - pDoc->stemp[j])>=-2)&&((pDoc->m_PV - pDoc->stemp[j])<=1))
        		pDoc->m_rt.m_Raising=0;
	 }
 	     if( pDoc->m_rt.m_rtSave.Soaking>=(pDoc->m_rt.m_rtSave.m_TIME+40)*60)
        		pDoc->m_rt.m_Raising=7;
	   pDoc->UpdateAllViews(NULL);	
		 }
	  }
 }//end of else

//zjun 2003/5/28
// if(pDoc->m_rt.m_rtSave.m_TIME==0){
int i=0; 
while(1){//判断是否超温\断线/不加热
 pDoc->heatstop=0;

 //pDoc->m_Pt100_1=25.3;

	 if(pDoc->m_Pt100_1 > pDoc->stemp[pDoc->STARTDOT]+20) 
  { i++;
    pDoc->ReadSr253();
    pDoc->m_PV=pDoc->m_Pt100_1;
    m_PV=pDoc->m_PV;
    if(i>4) {pDoc->heatstop=3;break;}
  }
  else if(pDoc->m_Pt100_1 < pDoc->stemp[pDoc->STARTDOT]-40){
    i++;
    pDoc->ReadSr253();
    pDoc->m_PV=pDoc->m_Pt100_1;
    m_PV=pDoc->m_PV;
	if(i>4) {pDoc->heatstop=4;break;}
  }
  else break;
 }//end of while(1)//lby

    if(pDoc->heatstop==4||pDoc->heatstop==3)
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		OnCmdStop();
		return;
	}

	 if((pDoc->m_rt.m_Raising==0)||(pDoc->m_rt.m_Raising==7)){  //lby 保温结束,开始测量
	   KillTimer(10001);
       pDoc->m_Pt=pDoc->m_rt.m_PV;
       pDoc->m_rt.m_Pt=pDoc->m_rt.m_PV;
       ReadResiAll(j); 

for(i=0;i<NMBOFSPL;i++)
	   {
 //   pDoc->m_rt.m_rtSave.m_fTem[i][j-1]= 40.1;
	if(i<4)pDoc->m_rt.m_rtSave.m_fTem[i][j]= pDoc->m_Pt100_1;
    else if(i<8) {
	 pDoc->m_Pt100_3 = (pDoc->m_PV+pDoc->m_Pt100_1+pDoc->m_Pt100_2)/3;
     pDoc->m_rt.m_tPt100_3 = sqrt( (double)((pDoc->m_PV+pDoc->m_Pt100_1*pDoc->m_PV+pDoc->m_Pt100_1+pDoc->m_Pt100_2*pDoc->m_Pt100_2)/2));
     pDoc->m_rt.m_tPt100_3 = (pDoc->m_rt.m_tPt100_3+pDoc->m_Pt100_1+pDoc->m_Pt100_2)/3; 
	 pDoc->m_rt.m_rtSave.m_fTem[i][j]=pDoc->m_rt.m_tPt100_3;
	}
	else pDoc->m_rt.m_rtSave.m_fTem[i][j]= pDoc->m_Pt100_2;
	   }
  
    SendMessage(WM_COMMAND,ID_FILE_SAVE,0);	 
       pDoc->m_rt.m_Raising=1;
 
	   if((pDoc->STARTDOT>=pDoc->m_rt.EndDot)||(pDoc->stemp[pDoc->STARTDOT]>=pDoc->m_rt.m_rtSave.m_MaxTemp)||(pDoc->m_PV>pDoc->m_rt.m_rtSave.m_MaxTemp+2))
	{
		KillTimer(10001);
	    pDoc->m_Running=FALSE; 
		pDoc->heatstop=6;
		OnCmdStop();
		return;
//	SendMessage(WM_COMMAND,ID_FILE_SAVE,0);
	}

       pDoc->STARTDOT++;
  	   pDoc->UpdateAllViews(NULL);	

	   if(!SetTimer(10001,pDoc->Pidtime*1000,NULL))
	   {
         MessageBox("定时器资源不足,请退出所有程序后再启动本程序.","错误",MB_OK);
		 return;
	   }

	}
	return;

}

//
//	定时器信号处理函数
//
void CPtcrView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
   
     int i=0;

   switch(nIDEvent)
	  {
      case 10001:
 //  if((pDoc->m_rt.m_Raising==0)||(pDoc->m_rt.m_Raising==7))break;
pDoc->HeatCool++;
		  if(pDoc->ZWX==0){
			  pDoc->ReadSr253();
              m_PV=pDoc->m_rt.m_tSr253;
		  }
		  else {
	pDoc->m_Pt100_1=pDoc->ReadPt100(pDoc->Pt100Chan_1);
    pDoc->m_PV=pDoc->m_Pt100_1;
    m_PV=pDoc->m_PV;
		  }

		 m_SV=pDoc->m_SV;
  //   static	int i=0;
		 if(pDoc->m_rt.m_Raising==7) {
		 JudgeTempStage(pDoc->STARTDOT);
		 }
    	else JudgeTempStage(pDoc->STARTDOT);
		if(pDoc->HeatCool/3){	pDoc->UpdateAllViews(NULL);	
	pDoc->HeatCool=0;
		}
		 break;
         case 10004:
			UpdateDT();
			break;
		 default:
			 break;
	  }

	CView::OnTimer(nIDEvent);
}

//
//	开始运行测量程序
//     
void CPtcrView::OnCmdGo() 
{
	// TODO: Add your command handler code here
	CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();
	char cmd[128]="meas?\r\n";
	char results[128];								//参数初始化		
    int Sr253BCC=2;									//默认通讯协议为SR253
    // TODO: Add your message handler code here and/or call default
	if(  pDoc->m_Running==TRUE)						//若程序正在运行
	{	
		MessageBox("控制过程已经开始!","Ptcr",MB_OK);	//弹出消息提示“控制过程已经开始”
		return;
	}
	DetectCom();									//检测串口
	if(!pDoc->ChanSet)								//若未进行通道电阻设置
		OnChanSet();									//打开“通道电阻设置”对话框
	pDoc->m_rt.m_rtSave.m_starttime=CTime::GetCurrentTime(); //获取当前时间为程序运行开始时间
	pDoc->m_ReadingF45=0;

	float tt; 
	tt=pDoc->m_Pt100;			//tt取Pt100温度
	if(pDoc->m_rt.Cooling==1)	//若处于冷却模式
		pDoc->STARTDOT=pDoc->m_rt.StartDot;		//将第一个有效测量点改为相应编号
	if(pDoc->STARTDOT==0)		//若第一个有效测试点编号为0
		OnSetTempStage();			//将室温设为测量温度PV

	if(pDoc->ZWX==0)			//若测试仪器为ZXW_B
		if(pDoc->m_sPort.m_rxdata.Sr253BCC==4)	//若通讯协议为Sr93
		{
			pDoc->SetSr93Temp(tt);					//按Sr93通讯协议设置温度tt
			if((pDoc->m_sPort.m_rxdata.sr==93)||(pDoc->m_sPort.m_rxdata.sr==83)) //若使用设备为SR83或SR93
			{
				pDoc->SetSr93("011W05090,",pDoc->m_PV+20,TRUE);//设置温控器事件报警2的设定值为m_PV+20
 				pDoc->SetSr93("011W05090,",pDoc->m_PV+20,TRUE);//设置温控器事件报警2的设定值为m_PV+20
			}
			else if(pDoc->m_sPort.m_rxdata.sr==13)			//若使用设备为Mr13
			{
				pDoc->SetSr93("011W05000,",5,TRUE);				//设置EV1事件报警方式为上限绝对值
				pDoc->SetSr93("011W05010,",220,TRUE);			//设置EV1事件报警温度绝对值为220
			}
			if(pDoc->m_sPort.m_rxdata.sr==83)					//若使用设备为SR83
				pDoc->SetSr93("011W01860,",0,FALSE);				//设置脱机选项（STBY）为执行
			if(pDoc->m_sPort.m_rxdata.sr==83)					//若使用设备为SR83
				pDoc->SetSr93("011W01860,",0,FALSE);				//设置脱机选项（STBY）为执行
			if(pDoc->m_rt.m_rtSave.m_TIME==0)					//匀速升温时	
				if((pDoc->m_sPort.m_rxdata.sr==93)||(pDoc->m_sPort.m_rxdata.sr==83))	//若使用设备为SR83或SR93
				{
					pDoc->SetSr93("011W05090,",pDoc->m_PV+20,TRUE);//设置温控器事件报警2的设定值为m_PV+20
 					pDoc->SetSr93("011W05090,",pDoc->m_PV+20,TRUE);//设置温控器事件报警2的设定值为m_PV+20
				}
				else if(pDoc->m_sPort.m_rxdata.sr==13)			//若使用设备为Mr13
				{
					pDoc->SetSr93("011W05000,",5,TRUE);				//设置EV1事件报警方式为上限绝对值
					pDoc->SetSr93("011W05010,",pDoc->stemp[pDoc->m_rt.EndDot]+20,TRUE);//设置EV1事件报警温度绝对值为最大测量点温度+20
 				}
		}
		else if(!SetSr253Exec())			//若通讯协议不正确					
		{
			MessageBox("Sr253通讯不正确,无法开始控制过程!","Ptcr",MB_OK);	//弹出消息提示窗口
			return;
		}
	pDoc->m_Running=TRUE;
	pDoc->m_rt.isRunning=pDoc->m_Running;	//“正在运行”状态设为“是”
	int i;
	for(i=0;i<NMBOFSPL;i++)
	{
		pDoc->m_rt.m_rtSave.m_fPtc[i][pDoc->m_rt.m_roomtemp_dot]=pDoc->m_rt.m_fResi[i];	//设置第i组数据室温点阻值为初始阻值
		if(i<4)
			pDoc->m_rt.m_rtSave.m_fTem[i][pDoc->m_rt.m_roomtemp_dot]=pDoc->m_rt.m_roomtemp;
		else if(i<8)
			pDoc->m_rt.m_rtSave.m_fTem[i][pDoc->m_rt.m_roomtemp_dot]=pDoc->m_rt.m_roomtemp;
		else if(i<12)
			pDoc->m_rt.m_rtSave.m_fTem[i][pDoc->m_rt.m_roomtemp_dot]=pDoc->m_rt.m_roomtemp;
		else 
			pDoc->m_rt.m_rtSave.m_fTem[i][pDoc->m_rt.m_roomtemp_dot]=pDoc->m_rt.m_roomtemp;	//设置第i组数据室温点温度为室温
	}

	if(pDoc->ZWX==1)	//若测试仪器为ZWX_C
	{
		tt=pDoc->m_Pt100;	//tt设为Pt100温度
		pDoc->m_PV=tt;
		pDoc->m_SV=tt;
		pDoc->m_rt.wvn=0;
		pDoc->m_rt.m_Pt=tt;
		pDoc->m_rt.m_PV=tt;
		pDoc->m_rt.m_tSr253=tt;
		pDoc->m_rt.wvn=0;	//占空比wvn置零
		pDoc->m_Pt100_1=tt;
		pDoc->m_Pt100_2=tt;	//将PV、SV、Pt、Pt100均设为tt
	}
	else 
		tt=pDoc->m_PV;		//tt设为测量温度PV

	pDoc->m_Pt = pDoc->m_PV;
    pDoc->m_rt.m_Pt=tt;
    pDoc->m_rt.m_PV=tt;
	pDoc->m_rt.StartDot=pDoc->STARTDOT;	//设定第一个有效测量点编号
	SendMessage(WM_COMMAND,ID_FILE_SAVE_AS,0);	//启动“另存为...”功能
	
	if(pDoc->ZWX==1)	//若测试仪器为ZWX_C
	{
		MessageBox("启动恒温箱电源，开始控制过程!","Ptcr",MB_OK);
		pDoc->Init8253();	//初始化8253
		pDoc->ReadPt100(pDoc->Pt100Chan_1);	//读取Pt100、Pt100_1、Pt100_2温度
		pDoc->m_PV=tt;
		pDoc->m_SV=tt;
		pDoc->Heat(1);		//发出加热信号“1”
		pDoc->SetC(7,1);
	}
	int j;
	j=pDoc->m_rt.StartDot;

	if((pDoc->ZWX==0)&&pDoc->m_sPort.m_rxdata.Sr253BCC==2)	//若测试仪器为ZWC_B且使用通信协议SR253
	{    
		SetSr253Temp(1, tt);	//设置1号SV为tt
		sprintf(cmd,"SN 01,Q");
		pDoc->ReadPvsv(cmd,results,4,3,2);	//读取PVSV
		SetSr253Temp(2, tt);	//设置2号SV为tt
		if(pDoc->m_rt.m_rtSave.m_TIME==0)	//若当前正在匀速升温
		{
    		sprintf(cmd,"RP %05.1f,%05.1f",pDoc->m_rt.m_rtSave.Ramp[0],1.000);
			pDoc->ReadPvsv(cmd,results,4,3,2);
			sprintf(cmd,"SN 01,Q");
 			pDoc->ReadPvsv(cmd,results,4,3,2);
			SetSr253Temp(5, pDoc->m_rt.m_rtSave.m_MaxTemp+15);
			sprintf(cmd,"SN 05");
 			pDoc->ReadPvsv(cmd,results,4,3,2);
			MessageBox("启动恒温箱电源，开始控制过程!","Ptcr",MB_OK);
			sprintf(cmd,"SN 05");
 			pDoc->ReadPvsv(cmd,results,4,3,2);
		}
		else 
		{
			MessageBox("启动恒温箱电源，开始控制过程!","Ptcr",MB_OK);
			if(j%2)	//若j为奇数
			{
				SetSr253Temp(1, tt);
				sprintf(cmd,"SN 01,Q");
 				pDoc->ReadPvsv(cmd,results,4,3,2);
			}	
			else 
			{
				SetSr253Temp(2, tt);
				sprintf(cmd,"SN 02,Q");
				pDoc->ReadPvsv(cmd,results,4,3,2);
			}
		}
	}

	if((pDoc->ZWX==0)&&pDoc->m_sPort.m_rxdata.Sr253BCC==4)	//若设备为ZWX_B且通讯协议为SR93
	{    
		pDoc->SetSr93Temp(tt);		//设置SV1温度为tt
		if((pDoc->m_sPort.m_rxdata.sr==93)||(pDoc->m_sPort.m_rxdata.sr==83))	//温控器型号为SR93或SR83
			pDoc->SetSr93("011W05090,",tt+20,TRUE);									//设置事件报警2的设定值为tt+20
		else 
		{   
			pDoc->SetSr93("011W05000,",5,TRUE);										//设定事件报警1的模式为上限绝对值
			pDoc->SetSr93("011W05010,",pDoc->m_PV+20,TRUE);							//设定事件报警1的温度上限为m_PV+20
		}
		MessageBox("启动恒温箱电源，开始控制过程!","Ptcr",MB_OK);
	}

//开始测控	
	pDoc->m_rt.m_Raising=1;	//温度状态设为升温

	KillTimer(10001);	//销毁计时器10001
	if(!SetTimer(10001,pDoc->Pidtime*1000,NULL))	//新建ID为10001，10秒发送一次信号的计时器
	{
		MessageBox("定时器资源不足,请退出所有程序后再启动本程序.","错误",MB_OK);
		return;
	}
	KillTimer(10004);	//销毁计时器10004
  	if(!SetTimer(10004,1000,NULL))					//新建ID为10005，1秒发送一次信号的计时器
        MessageBox("定时器资源不足,请退出所有程序后再启动本程序.","错误",MB_OK);
	//lby 判断升温、保温和测量状态	  
	pDoc->UpdateAllViews(NULL);	
	return;
}

//
//	设置温控状态为“人工强制”：强制程序开始测量
//
void CPtcrView::OnManMea() 
{
	// TODO: Add your command handler code here
    CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();
	pDoc->m_rt.m_Raising=7;
}

//
//	更新日期、时间、PV、SV、Pt100
//
void CPtcrView::UpdateDT()
{
    CMainFrame *pmWnd;
    CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();

	pmWnd=(CMainFrame *)AfxGetMainWnd();
    CTime dt=CTime::GetCurrentTime();
	pmWnd->m_Date=dt.Format("%Y年%m月%d日 ");
	pmWnd->m_Time=dt.Format("%H:%M:%S ");
	pmWnd->m_PV.Format("PV:%+5.1f ",pDoc->m_PV);
	pmWnd->m_SV.Format("SV:%+5.1f ",pDoc->m_SV);
    pmWnd->m_PT100.Format("PT:%+5.1f ",pDoc->m_Pt100);
  }

//
//	打开“曲线范围设置”对话框
//
void CPtcrView::SetRTRange() 
{
	// TODO: Add your command handler code here
	CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();//lby

	CSelRTRange RTRangeDia;
	int minresvalue,maxresvalue;
	CString str1;

    RTRangeDia.m_maxres=m_max_res;
	RTRangeDia.m_minres=m_min_res;
	RTRangeDia.m_maxtemp.Format("%d",m_max_temp);
	RTRangeDia.m_mintemp.Format("%d",m_min_temp);
	RTRangeDia.m_tempstep=m_temp_step;
    RTRangeDia.m_showdot=m_show_dot;
	RTRangeDia.m_OnlyMeaDot=m_Only_MeaDot;
    RTRangeDia.m_SelCoorKind=m_Sel_Coor_Kind;
    RTRangeDia.m_OutRect=m_OutterRect ;
   if((pDoc->heatstop==0)||(pDoc->heatstop==6)) RTRangeDia.m_EndStopHeat.Format("NORMALexit %d",pDoc->heatstop);
   else if(pDoc->heatstop==3)RTRangeDia.m_EndStopHeat.Format("aNORMAL exit  %d",pDoc->heatstop); 
   else if(pDoc->heatstop==4)RTRangeDia.m_EndStopHeat.Format("aNORMAL exit %d",pDoc->heatstop); 
   else if(pDoc->heatstop==7)RTRangeDia.m_EndStopHeat.Format("Man Exit  %d",pDoc->heatstop); 
   else RTRangeDia.m_EndStopHeat.Format("Other Exit%d",pDoc->heatstop); 

 DiaDataCheck=FALSE;
	while(!DiaDataCheck)
	{
	    
        if(RTRangeDia.DoModal()==IDOK)
		
		{
	     	m_max_temp=atoi(RTRangeDia.m_maxtemp);
		    m_min_temp=atoi(RTRangeDia.m_mintemp);
		    m_max_res=RTRangeDia.m_maxres;
	    	m_min_res=RTRangeDia.m_minres;
		    m_temp_step=RTRangeDia.m_tempstep;
			m_show_dot=RTRangeDia.m_showdot;
			m_Only_MeaDot=RTRangeDia.m_OnlyMeaDot;
			m_Sel_Coor_Kind=RTRangeDia.m_SelCoorKind;
			m_OutterRect=RTRangeDia.m_OutRect;
		}
		str1=m_max_res.GetAt(4);
		str1+=m_max_res.GetAt(5);
		maxresvalue=atoi(str1);
		str1="";
		str1=m_min_res.GetAt(4);
		str1+=m_min_res.GetAt(5);
		minresvalue=atoi(str1);


		if(m_min_temp>=m_max_temp||m_temp_step==0 ||minresvalue>=maxresvalue)
		{
			AfxMessageBox("最高温度值应大于最低温度值,曲线温度间隔不能为零,最大阻值应大于最小阻值",MB_OK,0);

		}
		else
			if(( m_max_temp-m_min_temp )<m_temp_step)
				AfxMessageBox("最高温度值与最低温度值自之差应不小于一个温度间隔",MB_OK,0);
            else
              DiaDataCheck=TRUE;
      
		
	}
		 OnWnd();
	
}

//
//	根据程序运行状态、文件打开、显示方式，设置“曲线范围设置”选项可用
//
void CPtcrView::OnUpdateRtsetRange(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		OnUpdateWnd(pCmdUI,5);
	
}

//
//	打开“获取任意温度阻值”对话框
//
void CPtcrView::OnGetAnyres() 
{
	// TODO: Add your command handler code here
	int i;
	CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();
	CGetAnyResOfTem GetResDia(pDoc);
    i=GetResDia.DoModal();
	
}

//
//	根据程序运行状态、文件打开、显示方式，设置“获取任意温度阻值”选项可用
//
void CPtcrView::OnUpdateGetAnyres(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdateWnd(pCmdUI,6);
}

//
//	根据有无温控表，设置“温控表”选项可用
//
void CPtcrView::OnUpdateDigitControllerSettings(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

if(pDoc->DigitController!=0)
	{
		pCmdUI->Enable();
		
	}
	else
		pCmdUI->Enable(FALSE);	

}

//
//	根据温控表是否连接，设置“温控表命令”选项可用
//
void CPtcrView::OnUpdateSr253Cmd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
 	if(pDoc->m_sPort.m_SPAvailable==TRUE)
	{
		pCmdUI->Enable();
		
	}
	else
		pCmdUI->Enable(FALSE);		
}

//
//	打开“升温方式设置”对话框，保存对应数据
//
void CPtcrView::OnSetTempStage() 
{
	// TODO: Add your command handler code here
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(pDoc->m_Running)
	{
//		MessageBox("控温已经开始!","Ptcr",MB_OK);
//		return;
	}   
	else DetectCom();

	CSetTemp *d=new CSetTemp(pDoc);
    
   if((pDoc->m_PV>400)|| (pDoc->m_PV<-50))
	   	if(pDoc->ZWX==0){
			  pDoc->ReadSr253();
              m_PV=pDoc->m_rt.m_tSr253;
		}
		else {
	      pDoc->m_Pt100_1=pDoc->ReadPt100(pDoc->Pt100Chan_1);
          pDoc->m_PV=pDoc->m_Pt100_1;
          m_PV=pDoc->m_PV;
	  }
		if(pDoc->STARTDOT==0) {
            pDoc->m_rt.m_PV= pDoc->m_PV;
			pDoc->m_rt.m_roomtemp=pDoc->m_rt.m_PV;
            m_PV=pDoc->m_PV;
		}

	if(	d->DoModal()==IDOK) 
	  CalculateStemp(pDoc->m_Pt100,pDoc->STARTDOT);
 
//	delete d ;	

}

//
//	选择“陶瓷PTC曲线”
//
void CPtcrView::OnCeramicPTC() 
{
	// TODO: Add your command handler code here
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    pDoc->CPptc=0;
	OnWnd();
}

//
//	根据电阻类型，设置“陶瓷PTC曲线”选项是否可用
//
void CPtcrView::OnUpdateCeramicPTC(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

//		pCmdUI->Enable();
		
		if(pDoc->CPptc==0)	pCmdUI->SetCheck(1);
        else pCmdUI->SetCheck(0);
//
	
}

//
//	选择“高分子PTC曲线”
//
void CPtcrView::OnPolymerPTC() 
{
	// TODO: Add your command handler code here
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    pDoc->CPptc=1;
	OnWnd();	
}

//
//	根据电阻类型，设置“高分子PTC曲线”选项是否可用
//
void CPtcrView::OnUpdatePolymerPTC(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//		pCmdUI->Enable();
		
		if(pDoc->CPptc==1)	pCmdUI->SetCheck(1);
        else pCmdUI->SetCheck(0);

}

//
//	计算Stemp参数：范围、步长、各测量点温度等
//
void CPtcrView::CalculateStemp(float tt, int start)
{
    CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();
  int i,j;
  float stemp[MAXOFSPL],a=0;
//start=0;

	if(start==0)
	{ j=0;
     tt=pDoc->m_PV;

	  for(i=0;i<MAXOFSPL;i++){
		  stemp[i]=-30+i*pDoc->m_rt.m_rtSave.Step[0];
	       
	  }
     if(tt<pDoc->m_rt.m_rtSave.MaxT[0])
        pDoc->m_rt.m_rtSave.m_STEP=pDoc->m_rt.m_rtSave.Step[0];
     else 
        pDoc->m_rt.m_rtSave.m_STEP=pDoc->m_rt.m_rtSave.Step[1];

	 j=0;
	 if(pDoc->m_rt.m_rtSave.m_TIME==0){
      stemp[j]=tt;
//      a= pDoc->stemp[j];
           a= stemp[j]+pDoc->m_rt.m_rtSave.m_STEP;
            a=(int)( stemp[j]+pDoc->m_rt.m_rtSave.m_STEP+0.5);
      j++;

	 }
     else {
		if(pDoc->m_rt.m_rtSave.m_STEP<=7)while(a<=tt+pDoc->m_rt.m_rtSave.m_STEP/2.0)	 a=((j++-0))*pDoc->m_rt.m_rtSave.m_STEP-30;
        else while(a<=tt + pDoc->m_rt.m_rtSave.m_STEP/2.0)	 a=((j++-0))*pDoc->m_rt.m_rtSave.m_STEP-30;
        
		stemp[j-1]=a-pDoc->m_rt.m_rtSave.m_STEP;//lbym_rt.m_roomtemp_dot

	 }

     pDoc->STARTDOT=j;
     pDoc->m_rt.StartDot=pDoc->STARTDOT;
     pDoc->m_rt.m_roomtemp_dot=pDoc->STARTDOT-1;



 //    stemp[pDoc->STARTDOT-1]=tt;//lby

	}
    else{
	  j=start; 	
//lby     if(pDoc->m_Running==0)
	         a=pDoc->stemp[j];
	}
	while(a<=pDoc->m_rt.m_rtSave.m_MaxTemp){
		if(j>(MAXOFSPL-1))	break;
     if(a<pDoc->m_rt.m_rtSave.MaxT[0]-10)
		  pDoc->m_rt.m_rtSave.m_STEP=pDoc->m_rt.m_rtSave.Step[0];
	 
	 else	 if(a<=pDoc->m_rt.m_rtSave.MaxT[0]){
		 pDoc->m_rt.m_rtSave.m_STEP=(pDoc->m_rt.m_rtSave.Step[0]+pDoc->m_rt.m_rtSave.Step[1])/2;
		 }
     else if((a>pDoc->m_rt.m_rtSave.MaxT[0])&&(a==(int)(a/10)*10))
		 pDoc->m_rt.m_rtSave.m_STEP=pDoc->m_rt.m_rtSave.Step[1];

		  stemp[j] = a;
	    a=a+pDoc->m_rt.m_rtSave.m_STEP;
      if(pDoc->m_rt.m_rtSave.m_STEP<pDoc->m_rt.m_rtSave.Step[0])
		if((int)(a/10)>(int)((a-pDoc->m_rt.m_rtSave.m_STEP+pDoc->m_rt.m_rtSave.Step[1])/10))
		    a=(int)(a/10)*10;
	    j++;
	}

	if(j<=(MAXOFSPL-1)){ stemp[j]=a;
		pDoc->m_rt.EndDot=j;
	}
    else pDoc->m_rt.EndDot=MAXOFSPL-1;



	for(i=start;i<MAXOFSPL;i++)pDoc->stemp[i]=stemp[i];

	  pDoc->m_rt.StartDot=pDoc->STARTDOT;
 //     pDoc->stemp[pDoc->m_rt.m_roomtemp_dot]=pDoc->m_rt.m_roomtemp;

	for(j=pDoc->m_rt.EndDot;j<(MAXOFSPL-1);j++)
		pDoc->stemp[j]=pDoc->stemp[j-1]+pDoc->m_rt.m_rtSave.m_STEP;

	if(pDoc->m_rt.Cooling==1){
		for(j=pDoc->m_rt.m_roomtemp_dot-1;j>0;j--){
//		j=pDoc->STARTDOT-3;
		pDoc->stemp[j]=pDoc->stemp[j+1]-pDoc->m_rt.m_rtSave.Step[0];
	    	if(pDoc->stemp[j]<=pDoc->m_rt.m_rtSave.m_MinTemp)
			{
			  pDoc->m_rt.StartDot=j;
			  break;
			}
		}
	
	pDoc->stemp[pDoc->m_rt.StartDot]=pDoc->m_rt.m_rtSave.m_MinTemp;
	for(j=pDoc->m_rt.StartDot+1;j<pDoc->m_rt.m_roomtemp_dot;j++){
			pDoc->stemp[j]=pDoc->stemp[j-1]+pDoc->m_rt.m_rtSave.Step[0];

		}
	} 
 pDoc->stemp[pDoc->m_rt.m_roomtemp_dot]=pDoc->m_rt.m_roomtemp;

}

//
//	进行文件类型转换
//
void CPtcrView::OnToolConbind() 
{
	// TODO: Add your command handler code here
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
		CCombinDlg *dlg=new CCombinDlg(pDoc);
//	AfxGetMainWnd()->m_hWnd,
	if(MessageBox("此操作可能丢失部分数据，继续？","警告",MB_OKCANCEL|MB_ICONEXCLAMATION)==IDOK)
	{
		
		if(dlg->DoModal()==IDCANCEL)
		{
			delete dlg;
			return ;
		}
	    dlg->rtsave[2].m_endtime=dlg->rtsave[1].m_endtime;
    	dlg->rtsave[2].m_starttime=dlg->rtsave[1].m_starttime;
		strcpy(dlg->rtsave[2].m_sStr[0],dlg->rtsave[1].m_sStr[0]);
		strcpy(dlg->rtsave[2].m_sStr[1],dlg->rtsave[1].m_sStr[1]);
        strcpy(dlg->rtsave[2].endTime[0],dlg->rtsave[1].endTime[0]);
        strcpy(dlg->rtsave[2].endTime[1],dlg->rtsave[1].endTime[1]);

        pDoc->m_rt.m_rtSave=dlg->rtsave[2];
		pDoc->m_SaveAs=FALSE;
		int i;
		for(i=0;i<30;i++)
			{
				if(pDoc->m_rt.m_rtSave.m_bChannels[i]==TRUE)
				{
					pDoc->LoadIndex(i);
					break;
				}
			}
		delete dlg;
		SendMessage(WM_COMMAND,ID_FILE_SAVE_AS,0);
	}
	
}

void CPtcrView::OnOptimize() 
{
	// TODO: Add your command handler code here
   	if(m_setusername=="LBYPTCRT0")
		;
   	else if(m_setusername=="hust01" || m_setusername=="HUST01")
		;
	else
	{
    	AfxMessageBox("你无权进行用户设置，请用管理者用户登入！",MB_OK,0);
	    return;
	}
//	CString str="100";
//	if(dlg.m_OptimizeData.AddString("1")==CB_ERR)
//		MessageBox("no1",0,MB_OK);
	CPtcrDoc *pDoc;
	pDoc=(CPtcrDoc *)GetDocument();
//	CGetAnyResOfTem GetResDia(pDoc);
    CDataOptize dlg(pDoc);    
	if(dlg.DoModal()==IDOK)
	{
/*		if(pDoc->m_rt.m_DatOrRtFile==0)
		{
        	SendMessage(WM_COMMAND,ID_FILE_SAVE_AS,0);
            pDoc->m_rt.m_DatOrRtFile==1;
		}
        else*/
        	SendMessage(WM_COMMAND,ID_FILE_SAVE,0);
		pDoc->UpdateAllViews(NULL);
	
	}
	
}

//
//	根据程序运行状态、文件打开、显示方式，设置“拟合数据”选项是否可用
//
void CPtcrView::OnUpdateOptimize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	OnUpdateWnd(pCmdUI,7);
	
}

//
//	打开“打印选择”对话框
//
void CPtcrView::OnMenuprintdata() 
{
	// TODO: Add your command handler code here
	        //lby    SelPrintData printdata;
				printdata.DoModal();
				m_printstyle=printdata.m_PriStyle;	
}

//
//	对话框响应函数
//
void CPtcrView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnChar(nChar, nRepCnt, nFlags);
}

//
//	将数据从一个应用程序复制到另一个应用程序
//
BOOL CPtcrView::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CView::OnCopyData(pWnd, pCopyDataStruct);
}

//
//	根据万用表是否连接，设置“万用表命令”选项可用
//
void CPtcrView::OnUpdateManualCmd(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

if(pDoc->m_sPortF45.m_SPAvailable==TRUE)
	{
		pCmdUI->Enable();
		
	}
	else
		pCmdUI->Enable(FALSE);		

	}

//
//	选择“个性化曲线”
//
void CPtcrView::OnPensonnelCurve() 
{
	// TODO: Add your command handler code here

	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    pDoc->CPptc=2;
	OnWnd();	
}

	
//
//	根据PTC电阻类型，设置“个性化曲线”选项可用
//
void CPtcrView::OnUpdatePensonnelCurve(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPtcrDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
//		pCmdUI->Enable();
		
		if(pDoc->CPptc==2)	pCmdUI->SetCheck(1);
        else pCmdUI->SetCheck(0);

}
