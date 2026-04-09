/*
**	FILENAME			Draw.cpp
**
**	PURPOSE				此类用于绘制窗口内的形状与文字，可以通过显示设置
**						与曲线设置的改变，修改曲线与数据为相应的输出格式
*/

#include "stdafx.h"
#include "Ptcr.h"
#include "Draw.h"

//#include "PtcrView.h"

extern CString m_devicename;
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 构造/析构

//
//	构造函数：初始化笔刷颜色
//
CDraw::CDraw()
{
	pencol[0]=RGB(0,0,0);
	pencol[1]=RGB(255,0,0);
	pencol[2]=RGB(0,255,0);
	pencol[3]=RGB(0,0,255);
	pencol[4]=RGB(0,255,255);
    pencol[5]=RGB(128,128,128);
	for(int i=6;i<MULNMBOFSPL;i++)
	{
	    if(i<=10)
		  pencol[i]=RGB((i-5)*50,255-(i-5)*50,(i-5)*50);
		else if(i<=15)
		          pencol[i]=RGB(0,(i-10)*50,255-(i-10)*50);
		     else if(i<=20)
				     pencol[i]=RGB((i-15)*50,0,255-(i-15)*50);
			      else if(i<25) 
                         pencol[i]=RGB((i-20)*50,(i-20)*50,255-(i-20)*40);
				       else 
                           pencol[i]=RGB((i-25)*50,255-(i-20)*40,255-(i-25)*50);
	}
}

//
//	析构函数
//
CDraw::~CDraw()
{

}

//
//	绘制强制测试RT曲线
//
void CDraw::DrawRTMea(CDC *pDC, CRT rt, CRect rect, int index)
{
	CFont Font;
	CFont* pOldFont;
	CPen Pen;
	CPen* pOldPen;
	double width,height;
	CString str("",2000);
    
	CString  strdisp[20];
		
	CRect rect1,rect2;
	int i,j,k,l;
	int lby;

lby=0;
	CPoint pnt;
  int OldDC;

	OldDC=pDC->SaveDC();
	height=fabs(rect.Height()/10);	
	Font.CreateFont((long)height,(long)(height*0.5),0,0,700,0,0,0,0,0,0,0,0,"宋体");
	pOldFont=pDC->SelectObject(&Font);

	str="PTC电阻温度特性曲线";
	pDC->DrawText(str,rect,DT_TOP|DT_CENTER);

	rect.top-=(long)(height*1.2);
	str="";

	height=fabs(rect.Height()/20.0);
	width=fabs(rect.Width()/80.0);
	
	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
	Font.CreateFont((long)height,(long)width,0,0,400,0,0,0,0,0,0,0,0,"宋体");
	pDC->SelectObject(&Font);

	CTime dt=CTime::GetCurrentTime();
    CString m_sStr[2];
	strdisp[lby++].Format("样品名称:%s\n",rt.m_rtSave.m_sChannelsName[index]);

	m_sStr[0] = dt.Format("%Y-%m-%d"); 
    m_sStr[1]=dt.Format("%H:%M:%S-A"); 
	strdisp[lby++].Format("测试日期:%s\n",m_sStr[0]);

	strdisp[lby++].Format("开始时间:%s\n",rt.m_rtSave.m_sStr[1]);

	strdisp[lby++].Format("测试时间:%s\n\n",m_sStr[1]);
	strdisp[lby++].Format(" 升温方式: \n");
    strdisp[lby++].Format("  To-%3i℃ 间隔 %2i ℃\n  %3i℃-%3i℃ 间隔 %2i ℃\n",rt.m_rtSave.MaxT[0],rt.m_rtSave.Step[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.MaxT[1],rt.m_rtSave.Step[1]);
	if(rt.m_rtSave.soaking[0]==0) 
	{
		
		strdisp[lby++].Format("  分段匀速升温\n\n");
	}
    else 
	{
		strdisp[lby++].Format("  保温时间%02i 分钟\n\n",rt.m_rtSave.soaking[0]);
	}
 
	
	if(rt.ZWX==0)	strdisp[lby++].Format(" SR 温度: %6.1f ℃\n",rt.m_tSr253);
	else strdisp[lby++].Format(" F45 温度:%6.1f ℃\n",rt.m_tPt100);
	strdisp[lby++].Format(" 设定温度:%6.1f ℃\n",rt.m_SV);
	strdisp[lby++].Format(" 占空比 :  %i  \n",rt.wvn);

	if((rt.m_Raising==1)||(rt.m_Raising==2)){
		if(rt.Cooling==0)strdisp[lby++].Format(" 测量状态:  升温  %i \n",rt.m_Raising);
		else strdisp[lby++].Format(" 测量状态:  降温  %i \n",rt.m_Raising);

	}
    else if(rt.m_Raising==3)	strdisp[lby++].Format(" 测量状态: 保温  %i\n",rt.m_rtSave.Soaking);
    else if((rt.m_Raising==0)||(rt.m_Raising==7))	strdisp[lby++].Format(" 测量状态: 测阻 %i \n",rt.m_Raising);

	strdisp[lby++].Format("\n前测试温度 :%6.1f ℃\n",rt.m_Pt);
	for(i=0;i<20;i++)
          str+=strdisp[i];


	
  pDC->DrawText(str,CRect(rect.left+rect.Width()/100,rect.top,rect.right,rect.bottom),DT_LEFT|DT_EXPANDTABS);
	
	rect1.CopyRect(rect);
	rect1.left=(long)fabs(rect.Width()/4);
	rect2.CopyRect(rect1);

	pDC->LPtoDP(rect1);

	if(rect1.Width()>rect1.Height())
	{
		height=0.9*rect1.Height();
		width=height*0.85;
		rect1.bottom=rect1.top+(long)height;
		rect1.right=rect1.right-(long)(width/9);
		rect1.left=rect1.right-(long)width;
	}
	else
	{
		width=0.9*rect1.Width();
		height=width/0.75;
		rect1.right-=(long)width/27;
		rect1.left=rect1.right-(long)width;
		rect1.top+=(long)height/18;
		rect1.bottom=rect1.top+(long)height;
	}
	
	pDC->DPtoLP(rect1);

	width=rect1.Width()/7;
	height=rect1.Height()/9;

	pDC->MoveTo(rect1.left,rect1.top);
	pDC->LineTo(rect1.right,rect1.top);
	pDC->LineTo(rect1.right,rect1.bottom);
	pDC->LineTo(rect1.left,rect1.bottom);
	pDC->LineTo(rect1.left,rect1.top);

	if(rt.GetX(0)<0)
	{
		rect1.left+=long(width);
		rect1.right+=long(width);
	}

float rtyc[MAXOFSPL],rtxc[MAXOFSPL];//lby2002/4/11
 
 for(i=0;i<MAXOFSPL;i++)//lby2002/4/11
  { if(rt.m_rtSave.m_fTem[index][i]==0.0)continue;
	rtyc[i]= (float) log10( (double)rt.m_rtSave.m_fPtc[index][i]); /*yc[0]...yc[count-1]:log of PTCR R value*/
	rtxc[i]=rt.m_rtSave.m_fTem[index][i];        /*xc[0]...xc[count-1]:Temperature value*/
	
	pnt.x=rect1.left+(long)(rtxc[i]/50*width);
	pnt.y=rect1.bottom-(long)(rtyc[i]*height);
	pDC->MoveTo(pnt);
	DrawCircle(pDC,pnt);
  }

	Pen.CreatePen(PS_DOT,1,RGB(0,0,0));
	pOldPen=pDC->SelectObject(&Pen);

	//restore
	//R<1 or T<0
/*lby	if (rt.GetResMin(index)<1)
	{
		rect1.top+=long(2*height);
		rect1.bottom+=long(2*height);
	}
	*/

	if(rt.GetX(0)<0)
	{
		rect1.left-=long(width);
		rect1.right-=long(width);
	}

	for(i=1;i<=8;i++)
	{
		pDC->MoveTo(rect1.right,rect1.top+(long)(i*height));
		pDC->LineTo(rect1.left,rect1.top+(long)(i*height));
	}

	for(i=1;i<=6;i++)
	{
		pDC->MoveTo(rect1.left+(long)(i*width),rect1.top);
		pDC->LineTo(rect1.left+(long)(i*width),rect1.bottom);
	}


	pnt.x=(long)(rect1.left-width/5);
	pnt.y=(long)(rect1.bottom+height/10);
	//T<0
	if(rt.GetX(0)<0)
	{
		k=-1;
		l=5;
		pDC->TextOut(pnt.x,pnt.y,"-50");
		
	}
	else
	{
		k=0;
		l=6;
		pDC->TextOut(pnt.x,pnt.y,"0");
	}

	pnt.x=(long)(rect1.left-width/3);
	
	for(;k<=l;k++)
	{
		pnt.x+=(long)(width);
		str.Format("%3d",(k+1)*50);
		pDC->TextOut(pnt.x,pnt.y,str);
	}

	str="T/℃";
	pnt.x-=(long)(width);
	pnt.y=rect1.bottom+(long)(height/2);
	pDC->TextOut(pnt.x,pnt.y,str);

	pnt.x=rect1.left-(long)(width/3*2);
	pnt.y=rect1.bottom-(long)(height/6);
	//R<1
/*	if (rt.GetResMin(index)<1)
	{
		i=-2;
		j=7;
		pDC->TextOut(pnt.x,pnt.y,"-2");
	}
	else
	{
		i=0;
		j=9;
		pDC->TextOut(pnt.x,pnt.y,"0");
	}
*/
	i=0;
		j=9;
		pDC->TextOut(pnt.x,pnt.y,"0");

	for(;i<j;i++)
	{
		pnt.y-=(long)height;
		str.Format("%d",i+1);
		pDC->TextOut(pnt.x,pnt.y,str);
	}

	pnt.x-=long(1.5*width);
	str="lgR/Ω";
	pnt.y+=(long)(2*height);
	rect2.top=pnt.y;
	rect2.left=pnt.x;
	rect2.right=rect1.left;
	rect2.bottom=rect1.bottom/2;
	pDC->DrawText(str,rect2,DT_LEFT);
	
    pDC->RestoreDC(OldDC);
	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
	pOldFont->DeleteObject();
	Pen.DeleteObject();

}

//
//	绘制单曲线
//
void CDraw::DrawCurve(CDC *pDC, CRT rt, CRect rect, int index,int tempstep,UINT maxtemp,CString minres,CString maxres,int mintemp,bool showdot,bool Only_MeaDot,int Sel_Coor_Kind,bool m_outrect)
{ 
	//参数初始化
	CFont Font;
	CFont* pOldFont;
	CPen Pen;
	CPen* pOldPen;
	double width,height,widthcopy,heightcopy;
	double width0,height0;
	CString str("",4000),str1("",200),str2;
	CRect rect1,rect2;
	int i,j,index0,loop=0;
	int m_ShowDot;
	int OffsetY0,OffsetY1;
	int QXResRange;
	CPoint pnt;
	float x,y,numstep;
	BOOL m_BeyondRange=FALSE;
	//2003-5-21 oyj
	BOOL m_LineWidthSet=FALSE;
	CPoint CurPoint;
  int OldDC;
	OldDC=pDC->SaveDC();
	index0=index;
	rt.Calculation(index);		

if(rt.isRunning==FALSE)	height=fabs(rect.Height()/10);	//lby  /10
else height=fabs(rect.Height()/15);	//lby  /10
		CRect rect0; 
	rect0.CopyRect(rect);		//根据程序的运行状态，调整输出范围上方空白的高度
if(pDC->IsPrinting())
	{
	rect1.top=0;
	rect1.top+=rect.Height()/16;
	rect1.bottom=rect.bottom;
	rect1.left=rect.left;
	rect1.right=rect.right;
	}//end of pDC->IsPrinting()
	else
	{
	   rect1.top=0;
	   rect1.top+=rect.Height()/23;
	   rect1.bottom=rect.bottom;
	   rect1.left=rect.left;
	   rect1.right=rect.right;
	}							//根据设备上下文是否用于打印，调整显示区域的位置

//lby 2002/8/17 
   	rect.top-=(long)height;
	height=fabs(rect.Height()/20.0);
	width=fabs(rect.Width()/80.0);	//计算显示范围四周空白区域的宽度
 
 if(rt.isRunning==FALSE)
	 rect.top-=(long)(height*3);//lby *3	
 else	 rect.top-=(long)(height*1);//lby *3	 根据程序的运行状态，调整显示区域的垂直位置
		rect1.CopyRect(rect);		
 rect2.CopyRect(rect1);
	rect2.left+=(long)width*0.7*35;	//调整输出范围的水平位置
	rect1.CopyRect(rect);
	rect2.CopyRect(rect1);
	pDC->LPtoDP(rect1);		//将设备坐标转换为逻辑坐标
	if(rect1.Width()>rect1.Height())	//显示区域宽大于高时
	{
		height=0.9*rect1.Height();
		width=0.93*rect1.Width()/2.25659;
		rect1.bottom=rect1.top+(long)height;
		rect1.right=rect1.right-(long)(width/29);
    	rect1.left=rect1.right-(long)width*1.28;	//再次调整显示区域的尺寸与位置

	}	
	pDC->DPtoLP(rect1);		//将逻辑坐标转换为设备坐标

   if(m_outrect==TRUE){
	 pDC->MoveTo(rect1.left,rect1.top);  //画曲线图的大外筐
	 pDC->LineTo(rect1.right,rect1.top);
	 pDC->LineTo(rect1.right,rect1.bottom);
	 pDC->LineTo(rect1.left,rect1.bottom);
	 pDC->LineTo(rect1.left,rect1.top);  
   }


	rect2.CopyRect(rect1);
	height=fabs(rect.Height()/20.0);//lby /20
	width=fabs(rect.Width()/80.0);
    heightcopy=height;
	widthcopy=width;	//根据显示范围的大小确认字号
	Font.CreateFont((long)height*0.8,(long)width*0.7,0,0,400,0,0,0,0,0,0,0,0,"宋体");
	pOldFont=pDC->SelectObject(&Font);
    pDC->DrawText("       Temperature  ℃",rect1,DT_SINGLELINE|DT_BOTTOM|DT_CENTER);	//在显示区域底部居中显示“Temperature  ℃”
 
   	pDC->SelectObject(pOldFont);
    	Font.DeleteObject();
        if(!pDC->IsPrinting())
           Font.CreateFont((long)width*1.973*0.8,(long)height/1.973*0.7,2700,0,400,0,0,0,0,0,0,0,0,"宋体");
    	else if(m_devicename.Find("HP")==-1)
                 Font.CreateFont((long)width*1.973*0.8,(long)height/1.973*0.7,2700,0,400,0,0,0,0,0,0,0,0,"宋体");
		     else
    	         Font.CreateFont((long)width*1.973*0.8,(long)height/1.973*0.7,900,0,400,0,0,0,0,0,0,0,0,"宋体");
    	pOldFont=pDC->SelectObject(&Font);		//根据设备上下文是否用于打印以及设备名是否带“HP”，修改字体的方向与粗细

	if(Sel_Coor_Kind!=TRUE)		//显示方式为指数显示
	{
	   pDC->TextOut(rect1.left+rect1.Width()/68.5,rect1.top+rect1.Height()/1.76,"Resistance  Ω");//DT_LEFT|
	   //显示区域左侧纵向显示“Resistance  Ω”
	}
	else						//显示方式为对数或科学计数显示
        pDC->TextOut(rect1.left+rect1.Width()/30,rect1.top+rect1.Height()/1.76,"lgR/Ω");
		//显示区域左侧纵向显示“lgR/Ω”
	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
	Font.CreateFont((long)height*0.8,(long)width*0.7,0,0,400,0,0,0,0,0,0,0,0,"宋体");	//修改字体尺寸与方向
	pOldFont=pDC->SelectObject(&Font);
	pnt.x=rect1.left+(long)(rt.GetX(0)/50*width);
	pnt.y=rect1.bottom-(long)(rt.GetY(0)*height);

   	rect2.CopyRect(rect1);

	pDC->LPtoDP(rect1);

		height=0.85*rect1.Height();
		width=0.9*rect1.Width()/1.2234;
		rect1.top=rect1.top+height/20.0;
		rect1.bottom=rect1.top+(long)height;		
		rect1.right=rect1.right-(long)(width/18);
		rect1.left=rect1.right-(long)width;		//调整（曲线）显示区域的位置与尺寸
	pDC->DPtoLP(rect1);
	//oyj 2003-5-21

	if(pDC->IsPrinting())
	{
		m_LineWidthSet=TRUE;
    	Pen.CreatePen(PS_SOLID,rect1.Width()/300,RGB(0,0,0));    //创建黑色实线笔刷
    	pOldPen=pDC->SelectObject(&Pen);
	}


//oyj
	pDC->MoveTo(rect1.left,rect1.top);   //画小框
	pDC->LineTo(rect1.right,rect1.top);
	pDC->LineTo(rect1.right,rect1.bottom);
	pDC->LineTo(rect1.left,rect1.bottom);
	pDC->LineTo(rect1.left,rect1.top);
    
	//oyj2003-5-21

	if(m_LineWidthSet==TRUE)		//若设备上下文用于打印
	{
   Pen.DeleteObject();				//删除笔刷对象
	}
   //5-21-2003
	Pen.CreatePen(PS_DOT,1,RGB(0,0,0));		//创建宽度为1的黑色虚线笔刷
	pOldPen=pDC->SelectObject(&Pen);
	numstep=(float)(maxtemp-mintemp)/(float)tempstep;
	width0=(rect1.right-rect1.left)/numstep;	//确认横坐标数量与间隔
	pDC->SetTextAlign(TA_RIGHT);//|TA_CENTER);	//将文本与边框右侧对齐
	str=maxres.GetAt(4);
    str+=maxres.GetAt(5);
	OffsetY1=atoi(str);		//最大数量级
	str=minres.GetAt(4);
	str+=minres.GetAt(5);
	OffsetY0=atoi(str);		//最小数量级	
	QXResRange=OffsetY1-OffsetY0;		//确认纵坐标的数量级范围
    height0=(rect1.top-rect1.bottom)/QXResRange;	//计算各纵分区的高度
	j=atoi(str);

	if(Sel_Coor_Kind==TRUE)
	{//对数
		for(i=0;i<=QXResRange;i++)	//对于各个纵坐标数量级：
	   {
	   	
		if(i==0 || i==QXResRange)	//对于顶部与底部纵坐标
		{
			str.Format("%d",j);
        	pDC->TextOut(rect1.left-width0/3,rect1.bottom+(long)(i*height0)+height0/4,str);	//在曲线左侧底部或顶部显示对应数量级
		}
		if(i>0 && i<=QXResRange-1)	//对于其他纵坐标
		
		 {
	   		pDC->MoveTo(rect1.right,rect1.bottom+(long)(i*height0));
	   	    pDC->LineTo(rect1.left,rect1.bottom+(long)(i*height0));			//绘制该纵坐标水平虚线
        	pDC->TextOut(rect1.left-width0/3,rect1.bottom+(long)(i*height0)+height0/4,str);		//左侧显示对应数量级
		 }
            j++;
			str.Format("%d",j);
	   }
	}	

//Sel_Coor_Kind=2;	
else if(Sel_Coor_Kind==0)
	{//指数
		for(i=0;i<=QXResRange;i++)	//对于各个纵坐标数量级：
	   {
	   	
		if(i==0 || i==QXResRange)	//对于顶部与底部纵坐标
		{
			str.Format("%d",j);
        	pDC->TextOut(rect1.left-width0/3,rect1.bottom+(long)(i*height0)+height0/4,str);	//在曲线左侧底部或顶部显示对应数量级
		}
		if(i>0 && i<=QXResRange-1)	//对于其他纵坐标
		
		 {
	   		pDC->MoveTo(rect1.right,rect1.bottom+(long)(i*height0));
	   	    pDC->LineTo(rect1.left,rect1.bottom+(long)(i*height0));			//绘制该纵坐标水平虚线
        	pDC->TextOut(rect1.left-width0/3,rect1.bottom+(long)(i*height0)+height0/4,str);		//左侧显示对应数量级
		 }
           
    //zjun         
			 
		 pDC->TextOut(rect1.left-width0/3-width0/3,rect1.bottom+(long)(i*height0)+height0/4-height0/4,"10");	//数量级左侧加上“10”
 j++;
			str.Format("%d",j);
	   }
	}
	else   
	{//指数-科学记数
    	if(j<0)
		{ 	
    	   	int j1;
    		j1=fabs(j);
      	    str.Format("1.0E-0%d",j1);
		}
    	else if(j>=0 && j<=9)
      		    str.Format("1.0E+0%d",j);
      	     else
      	        str.Format("1.0E+%d",j);	//修改纵坐标（str）为科学计数法
 
     	for(i=0;i<=QXResRange;i++)	//对于各个纵坐标数量级：
		{
    		if(i>0 && i<=QXResRange-1)	//对于中间纵坐标
		
			{
    			pDC->MoveTo(rect1.right,rect1.bottom+(long)(i*height0));
    		    pDC->LineTo(rect1.left,rect1.bottom+(long)(i*height0));	//绘制水平虚线
			}
       			pDC->TextOut(rect1.left-width0/6.39,rect1.bottom+(long)(i*height0)+height0/4,str);	//边框左侧显示对应的科学计数法表示的纵坐标
       		j=j+1;
   	        
			if(j<0)
			{
     			int j1;
     			j1=fabs(j);
       	        str.Format("1.0E-0%d",j1);
			}
    	    else if(j>=0 && j<=9)//R axial
	    	       str.Format("1.0E+0%d",j);
	        else
	               str.Format("1.0E+%d",j);	//修改纵坐标（str）为科学计数法

		}
	}
   	m_ShowDot=width0;	//显示测量点数量为横坐标数量
   	str="";
   	pDC->SetTextAlign(TA_CENTER); //设置文本水平居中
   	str.Format("%d",mintemp);
    pDC->TextOut(rect1.left,rect1.bottom-height0/5.4,str);	//边框左下方显示最小温度	
    for(i=1;i<=numstep;i++)	//对于各个横坐标温度
	{
        if(i<numstep)	//非最右侧横坐标
		{
		   pDC->MoveTo(rect1.left+(long)(i*width0),rect1.top);
		   pDC->LineTo(rect1.left+(long)(i*width0),rect1.bottom);	//绘制垂直虚线
		}
        if(m_ShowDot>rect1.Width()/11.0)	//若横坐标超过曲线显示范围的1/11
		{
		  str.Format("%d",i*tempstep+mintemp);
		  pDC->TextOut(rect1.left+(long)(i*width0),rect1.bottom-height0/5.4,str);	//显示对应横坐标
		  m_ShowDot=width0;
		}
		else
			m_ShowDot+=width0;
	}
	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
	Font.CreateFont((long)height*0.9,(long)width*0.8,0,0,400,0,0,0,0,0,0,0,0,"宋体");
	pOldFont=pDC->SelectObject(&Font);

	width0=rect1.right-rect1.left;
	height0=rect1.top-rect1.bottom;
    pnt.x=rect1.left+(long)(((rt.GetX(0)-mintemp)/tempstep)*(width0/((maxtemp-mintemp)/(float)tempstep)));//zjun
	pnt.y=rect1.bottom+(long)(rt.GetY(0)*height0/QXResRange)-OffsetY0*(height0/QXResRange);	//计算曲线起始点坐标
	pDC->MoveTo(pnt);
	Pen.DeleteObject();  
	Pen.CreatePen(PS_SOLID,1,RGB(0,0,255));	//创建宽度为1的蓝色实线笔刷
	pOldPen=pDC->SelectObject(&Pen);
//9-29 oyj
	if((showdot==TRUE|| Only_MeaDot==TRUE) && pnt.x<rect1.right && pnt.x>rect1.left && pnt.y>rect1.bottom && pnt.y<rect1.top)
	//若正在绘制强制测试RT曲线且曲线位置在绘制范围内
	{
        CBrush brush;
	    CBrush *poldbrush;
	    brush.CreateSolidBrush(RGB(0,0,255));	//创建蓝色逻辑画笔
	    poldbrush=pDC->SelectObject(&brush);	//指针指向该画笔
		pDC->Ellipse(pnt.x-60,pnt.y+60,pnt.x+60,pnt.y-60);	//绘制曲线起始点上的椭圆
	    pDC->SelectObject(poldbrush);
	    poldbrush->DeleteObject();
	    brush.DeleteObject();

	}					
//9-29 oyj
	for(i=1;i<rt.GetCount(index);i++)	//对于各个显示的测量点：
	{
		if(index>5){	//通道号大于6时iiii置零
		    int iiii;
			iiii=0;
		}

		if((showdot==TRUE|| Only_MeaDot==TRUE) && pnt.x<rect1.right && pnt.x>rect1.left && pnt.y>rect1.bottom && pnt.y<rect1.top)
		//若正在绘制强制测试RT曲线且曲线位置在绘制范围内
		{
   			pnt.x=rect1.left+(long)(((rt.GetX(i)-mintemp)/tempstep)*(width0/((maxtemp-mintemp)/(float)tempstep)));//lby(long)--(float)
			pnt.y=rect1.bottom+(long)(rt.GetY(i)*height0/QXResRange)-OffsetY0*(height0/QXResRange);	//获取当前测量点在区域内坐标
            CBrush brush;
	        CBrush *poldbrush;
	        brush.CreateSolidBrush(RGB(0,0,255)); //创建蓝色笔刷
	        poldbrush=pDC->SelectObject(&brush);

			pDC->Ellipse(pnt.x-60,pnt.y+60,pnt.x+60,pnt.y-60);	//该测量点上绘制椭圆

	        pDC->SelectObject(poldbrush);
	        poldbrush->DeleteObject();
	        brush.DeleteObject();

		}					
		for(x=rt.GetX(i-1);x<rt.GetX(i);x+=(float)0.01)	//对于曲线上每个单位为0.01的小段
		{
//9-30 oyj			y=rt.GetX(i);
	   float ll0,ll1;
	   ll0=rt.GetX(i)-rt.GetX(i-1);	//与前一段的温度差
	   ll1=rt.GetX(i+1)-rt.GetX(i);	//与后一段的温度差
	if( ll0==0 ){
	   y= rt.GetY(i);	//与前一段无温度差时，y取该测量点阻值
	}
	else if( (ll0<1)&&(ll0>-1) ){
	   y= rt.GetY(i-1)+(x-rt.GetX(i-1)) * (rt.GetY(i)-rt.GetY(i-1)) /(rt.GetX(i)-rt.GetX(i-1));	//与前一段温度差小于1时直线拟合
	}
	else if( (ll1<1)&&(ll1>-1) ){
	   y= rt.GetY(i-1)+(x-rt.GetX(i-1)) * (rt.GetY(i)-rt.GetY(i-1)) /(rt.GetX(i)-rt.GetX(i-1));	//与后一段温度差小于1时直线拟合
	}
    else y=rt.GetAnyR(x,index);	//否则计算对应拟合点阻值
//			y=rt.GetAnyR(x,index);

	pnt.x=rect1.left+(long)(((x-mintemp)/tempstep)*(width0/((maxtemp-mintemp)/(float)tempstep)));//zjun
	pnt.y=rect1.bottom+(long)(y*height0/QXResRange)-OffsetY0*(height0/QXResRange);	//计算该拟合点对应坐标
			if(pnt.x<rect1.left||pnt.x>rect1.right||pnt.y>rect1.top||pnt.y<rect1.bottom)
			{
				pDC->MoveTo(pnt);
				m_BeyondRange=TRUE;
			}
			else if(Only_MeaDot==FALSE)	//座标为超出范围时进行与前一个拟合点的连线
		     	     pDC->LineTo(pnt);
			     else
					 pDC->MoveTo(pnt);

		}
	}
//	{
/* 9-30 oyj	  if((showdot==TRUE ||Only_MeaDot==TRUE) && pnt.x<rect1.right && pnt.x>rect1.left && pnt.y>rect1.bottom && pnt.y<rect1.top)
		{
            
			pDC->Ellipse(pnt.x-60,pnt.y+60,pnt.x+60,pnt.y-60);
		}
 9-30 oyj */
	if(rt.m_DrawDotFlag==TRUE )	//如果在菜单栏内选择了“工具->拟合”
	{
    	Pen.DeleteObject();  
		Pen.CreatePen(PS_DOT,1,RGB(255,0,0));	//创建宽度为1红色虚线笔刷
        pOldPen=pDC->SelectObject(&Pen);
 		pnt.x=rect1.left+(long)(((rt.GetX(rt.m_DataNum-1)-mintemp)/tempstep)*(width0/((maxtemp-mintemp)/(long)tempstep)));
    	pnt.y=rect1.bottom+(long)(rt.GetY(rt.m_DataNum-1)*height0/QXResRange)-OffsetY0*(height0/QXResRange);
		DrawCross(pDC,pnt);		//在直线拟合点绘制交叉线
    	pnt.y=rect1.bottom+(long)(log10((double)rt.m_TempResVal)*height0/QXResRange)-OffsetY0*(height0/QXResRange);
 		DrawCircle(pDC,pnt);	//在（二次函数）计算拟合点上绘制圆
		rt.m_DrawDotFlag=FALSE;
	}
  
	pDC->RestoreDC(OldDC);

	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
	pOldFont->DeleteObject();
	Pen.DeleteObject();  //删除字体与笔刷对象
} 

//
//	绘制多曲线
//
void CDraw::DrawMultiCurves(CDC *pDC, CRT rt, CRect rect, int *index,int tempstep,UINT maxtemp,CString minres,CString maxres,int mintemp,bool showdot,bool Only_MeaDot)
{
	CFont Font;
	CFont* pOldFont;
	CPen Pen;
	CPen* pOldPen;
	double width,height;
	CString str("",2000);
	CRect rect1,rect2,rect3;
	int i,j,k,kk;
	CPoint pnt;
	float x,y;
	float numstep;
	int OffsetY0,OffsetY1;
	int QXResRange;
	int m_ShowDot;
    BOOL m_BeyondRange=FALSE;

	height=fabs(rect.Height()/10);	
	Font.CreateFont((long)height,(long)(height*0.5),0,0,700,0,0,0,0,0,0,0,0,"宋体");
	pOldFont=pDC->SelectObject(&Font);

	str="PTC电阻温度特性曲线";
	pDC->DrawText(str,rect,DT_TOP|DT_CENTER);

	rect.top-=(long)(height*1.2);
	str="";

	height=fabs(rect.Height()/20.0);
	width=fabs(rect.Width()/80.0);
	
	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
	Font.CreateFont((long)height,(long)width,0,0,400,0,0,0,0,0,0,0,0,"宋体");
	pDC->SelectObject(&Font);
	
	rect1.CopyRect(rect);
	rect1.left+=(long)(fabs(rect.Width()/3.5));
	rect1.right=rect1.left+long(rect.Width());
	rect2.CopyRect(rect1);


	pDC->LPtoDP(rect1);

	if(rect1.Width()>rect1.Height())
	{
 		height=0.9*rect1.Height();
		width=height*0.85;
		rect1.bottom=rect1.top+(long)height;
		rect1.right=rect1.left+(long)(width);	
	}
	else
	{
		width=0.9*rect1.Width();
		height=width/0.75;
		rect1.right=rect1.left+(long)width;
		rect1.top+=(long)height/18;
		rect1.bottom=rect1.top+(long)height;
	}
	
	pDC->DPtoLP(rect1);


	numstep=(float)(maxtemp-mintemp)/(float)tempstep;
	width=(rect1.right-rect1.left)/numstep;
	m_ShowDot=width;
    str=maxres.GetAt(4);
    str+=maxres.GetAt(5);
	OffsetY1=atoi(str);
	str=minres.GetAt(4);
	str+=minres.GetAt(5);
	OffsetY0=atoi(str);	
	QXResRange=OffsetY1-OffsetY0;
	height=rect1.Height()/QXResRange;



	pDC->MoveTo(rect1.left,rect1.top);
	pDC->LineTo(rect1.right,rect1.top);
	pDC->LineTo(rect1.right,rect1.bottom);
	pDC->LineTo(rect1.left,rect1.bottom);
	pDC->LineTo(rect1.left,rect1.top);
	
//	for(kk=0;kk<5;kk++)
	for(kk=0;kk<MULNMBOFSPL;kk++)
		if(index[kk]==100)
			break;

	
    for(j=0;j<kk;j++)
	{
		Pen.CreatePen(PS_SOLID,1,pencol[j]);
		pOldPen=pDC->SelectObject(&Pen);

		for(i=0;i<MAXOFSPL;i++)
		{
			xc[i]=0;
			yc[i]=0;
		}

		for(i=0;i<rt.GetCount(index[j]);i++)
		{
			k=i+rt.GetStart(index[j]);
			yc[i]= (float) log10((double)rt.m_rtSave.m_fPtc[index[j]][k]); /*yc[0]...yc[count-1]:log of PTCR R value*/
    		xc[i]=rt.m_rtSave.m_fTem[index[j]][k];        /*xc[0]...xc[count-1]:Temperature value*/
  //  		xc[i]=rt.m_rtSave.m_fTem[index[j]][k];        /*xc[0]...xc[count-1]:Temperature value*/
		}
	
	
//		pnt.x=rect1.left+(long)(xc[0]/50*width);
//		pnt.y=rect1.bottom-(long)(yc[0]*height);

		
		pnt.x=rect1.left+(long)((xc[0]/(float)tempstep)*width)-(long)((mintemp/(float)tempstep)*width);
		pnt.y=rect1.bottom+(long)(yc[0]/((float)QXResRange/fabs(rect1.Height())))-(OffsetY0/((float)QXResRange/fabs(rect1.Height())));
		pDC->MoveTo(pnt);
	    
//9-30 oyj
    /*	if(showdot==TRUE || Only_MeaDot==TRUE)
			{
			   switch(j)
			   {
			      case 0:
				     break;
			      case 1:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				        DrawCircle(pDC,pnt);
				     break;
			      case 2:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
			     	    DrawRect(pDC,pnt);
				     break;
		          case 3:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
  				        DrawCross(pDC,pnt);
				     break;
			      case 4:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				        DrawHor(pDC,pnt);
			    	 break;
			   }
			}*/
// 9-30 oyj		
		for(i=1;i<rt.GetCount(index[j]);i++)
//		for(i=1;i<=rt.GetCount(index[j]);i++)
		{
			if(showdot==TRUE || Only_MeaDot==TRUE)
			{ 
		    	switch(j)
				{
			     case 0:
				    break;
			     case 1:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				       DrawCircle(pDC,pnt);
				    break;
			     case 2:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				       DrawRect(pDC,pnt);
				    break;
			     case 3:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				       DrawCross(pDC,pnt);
				    break;
			     case 4:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				       DrawHor(pDC,pnt);
				    break;
				}
			}
			
			for(x=xc[i-1];x<=xc[i];x+=(float)0.1)
			{

				y=GetAny(index[j],rt.GetEnd(index[j]),rt.GetStart(index[j]),x);

    		    pnt.x=rect1.left+(long)((x/(float)tempstep)*width)-(long)((mintemp/(float)tempstep)*width);
	        	pnt.y=rect1.bottom+(long)(y/((float)QXResRange/fabs(rect1.Height())))-(OffsetY0/((float)QXResRange/fabs(rect1.Height())));
                if(pnt.x<rect1.left||pnt.x>rect1.right||pnt.y>rect1.top||pnt.y<rect1.bottom)
				{
					pDC->MoveTo(pnt);
					m_BeyondRange=TRUE;
				}
			    else if(Only_MeaDot==FALSE)
		        	pDC->LineTo(pnt);
				     else pDC->MoveTo(pnt);
			}
       	} 

//		rect3.top=rect1.top+long(height*0.5*j);
		rect3.top=rect1.top+long(rect1.Height()/18*j);
//		rect3.left=rect1.right+long(width/2);
		rect3.left=rect1.right+long(rect1.Width()/9);
//		rect3.right=rect3.left+long(width/2);
		rect3.right=rect3.left+long(rect1.Width()/9);
//		rect3.bottom=rect3.top+long(height*0.5);
		rect3.bottom=rect3.top+long(rect1.Height()/18);

		pnt.x=rect3.left;
		pnt.y=long((rect3.top+rect3.bottom)/2);
		pDC->MoveTo(pnt);
		pnt.x=rect3.right;
		pDC->LineTo(pnt);
		pnt.x=(rect3.left+rect3.right)/2;
		if(showdot==TRUE)
		{
		   switch(j)
		   {
			  case 0:
				break;
			  case 1:
				DrawCircle(pDC,pnt);
				break;
		      case 2:
				DrawRect(pDC,pnt);
				break;
			  case 3:
				DrawCross(pDC,pnt);
				break;
			  case 4:
				DrawHor(pDC,pnt);
				break;
		   }
		}
    	rect3.left+=long(rect1.Width()/8);
		rect3.right+=long((rect1.Width()/8)*2);
		str.Format("%s",rt.m_rtSave.m_sChannelsName[index[j]]);
		pDC->DrawText(str,rect3,DT_LEFT);

		pDC->SelectObject(pOldPen);
		Pen.DeleteObject();
	}

	Pen.CreatePen(PS_DOT,1,RGB(0,0,0));
	pOldPen=pDC->SelectObject(&Pen);

 	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
  	Font.CreateFont(fabs((long)rect1.Height()/19.635),(long)rect1.Width()/44,0,0,400,0,0,0,0,0,0,0,0,"宋体");

	pOldFont=pDC->SelectObject(&Font);


	str=maxres.GetAt(4);
	str+=maxres.GetAt(5);
	j=atoi(str);
	str.Format("%d",j);
	pDC->SetTextAlign(TA_RIGHT);
	pDC->TextOut(rect1.left-(long)rect1.Width()/33,rect1.top-(long)rect1.Height()/54,str);

	for(i=1;i<=QXResRange-1;i++)
	{
		pDC->MoveTo(rect1.right,rect1.top+(long)(i*height));
		pDC->LineTo(rect1.left,rect1.top+(long)(i*height));
		j=j-1;
		str.Format("%d",j);
		pDC->TextOut(rect1.left-(long)rect1.Width()/33,rect1.top+(long)(i*height)-rect1.Height()/54,str);

	}
	
	j=j-1;
	str.Format("%d",j);
	pDC->TextOut(rect1.left-(long)rect1.Width()/33,rect1.top+(long)(i*height)-rect1.Height()/54,str);

	m_ShowDot=width;
	str="";
	pDC->SetTextAlign(TA_CENTER); 
	str.Format("%d",mintemp);
    pDC->TextOut(rect1.left,rect1.bottom+long(height/8),str);
	for(i=1;i<=numstep;i++)
	{

		  if(i<numstep)
		{
		   pDC->MoveTo(rect1.left+(long)(i*width),rect1.top);
		   pDC->LineTo(rect1.left+(long)(i*width),rect1.bottom);
		}
        if(m_ShowDot>800)
		{
		  str.Format("%d",i*tempstep+mintemp);
		  pDC->TextOut(rect1.left+(long)(i*width),rect1.bottom+long(rect1.Height()/72),str);
		  m_ShowDot=width;
		}
		else
			m_ShowDot+=width;

	}


	str="T/℃";
//	pnt.x-=(long)(width);
//	pnt.y=rect1.bottom+(long)(height/2);
//	pDC->TextOut(pnt.x,pnt.y,str);
    pDC->TextOut(rect1.right-(long)width,rect1.bottom+(long)rect1.Height()/18,str);

	str="lgR/Ω";
	pDC->TextOut(rect1.left-0.1364*rect1.Width(),rect1.top+rect1.Height()/9.006,str);

	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
	pOldFont->DeleteObject();
	Pen.DeleteObject();
	
}   

//
//	绘制坐标
//
void CDraw::DrawCoordinate(CDC *pDC, CRT rt, CRect rect, int *index,int tempstep,UINT maxtemp,CString minres,CString maxres,int mintemp,bool showdot,bool Only_MeaDot)
{
	CFont Font;
	CFont* pOldFont;
	CPen Pen;
	CPen* pOldPen;
	double width,height;
	CString str("",2000);
	CRect rect1,rect2,rect3;
	int i,j,k,kk;
	CPoint pnt;
	float x,y;
	float numstep;
	int OffsetY0,OffsetY1;
	int QXResRange;
	int m_ShowDot;
    BOOL m_BeyondRange=FALSE;

	height=fabs(rect.Height()/10);	
	Font.CreateFont((long)height,(long)(height*0.5),0,0,700,0,0,0,0,0,0,0,0,"宋体");
	pOldFont=pDC->SelectObject(&Font);

	str="PTC电阻温度特性曲线";
	pDC->DrawText(str,rect,DT_TOP|DT_CENTER);

	rect.top-=(long)(height*1.2);
	str="";

	height=fabs(rect.Height()/20.0);
	width=fabs(rect.Width()/80.0);
	
	pDC->SelectObject(pOldFont);
	Font.DeleteObject();

	Font.CreateFont((long)height,(long)width,0,0,400,0,0,0,0,0,0,0,0,"宋体");
	pDC->SelectObject(&Font);
	
	rect1.CopyRect(rect);
	rect1.left+=(long)(fabs(rect.Width()/3.5));
	rect1.right=rect1.left+long(rect.Width());

	rect2.CopyRect(rect1);


	pDC->LPtoDP(rect1);

	if(rect1.Width()>rect1.Height())
	{
 		height=0.9*rect1.Height();
		width=height*0.85;
		rect1.bottom=rect1.top+(long)height;
		rect1.right=rect1.left+(long)(width);	
	}
	else
	{
		width=0.9*rect1.Width();
		height=width/0.75;
		rect1.right=rect1.left+(long)width;
		rect1.top+=(long)height/18;
		rect1.bottom=rect1.top+(long)height;
	}
	
	pDC->DPtoLP(rect1);


	numstep=(float)(maxtemp-mintemp)/(float)tempstep;
	width=(rect1.right-rect1.left)/numstep;
	m_ShowDot=width;
    str=maxres.GetAt(4);
    str+=maxres.GetAt(5);
	OffsetY1=atoi(str);
	str=minres.GetAt(4);
	str+=minres.GetAt(5);
	OffsetY0=atoi(str);	
	QXResRange=OffsetY1-OffsetY0;
	height=rect1.Height()/QXResRange;



	pDC->MoveTo(rect1.left,rect1.top);
	pDC->LineTo(rect1.right,rect1.top);
	pDC->LineTo(rect1.right,rect1.bottom);
	pDC->LineTo(rect1.left,rect1.bottom);
	pDC->LineTo(rect1.left,rect1.top);
	
	for(kk=0;kk<5;kk++)
		if(index[kk]==100)
			break;

	
    for(j=0;j<kk;j++)
	{
		Pen.CreatePen(PS_SOLID,1,pencol[j]);
		pOldPen=pDC->SelectObject(&Pen);

		for(i=0;i<MAXOFSPL;i++)
		{
			xc[i]=0;
			yc[i]=0;
		}

		for(i=0;i<rt.GetCount(index[j]);i++)
		{
			k=i+rt.GetStart(index[j]);
			yc[i]= (float) log10((double)rt.m_rtSave.m_fPtc[index[j]][k]); /*yc[0]...yc[count-1]:log of PTCR R value*/
    		xc[i]=rt.m_rtSave.m_fTem[index[j]][k];        /*xc[0]...xc[count-1]:Temperature value*/
  //  		xc[i]=rt.m_rtSave.m_fTem[index[j]][k];        /*xc[0]...xc[count-1]:Temperature value*/
		}
	
	
//		pnt.x=rect1.left+(long)(xc[0]/50*width);
//		pnt.y=rect1.bottom-(long)(yc[0]*height);

		
		pnt.x=rect1.left+(long)((xc[0]/(float)tempstep)*width)-(long)((mintemp/(float)tempstep)*width);
		pnt.y=rect1.bottom+(long)(yc[0]/((float)QXResRange/fabs(rect1.Height())))-(OffsetY0/((float)QXResRange/fabs(rect1.Height())));
		pDC->MoveTo(pnt);
	    
		
		for(i=1;i<rt.GetCount(index[j]);i++)
//		for(i=1;i<=rt.GetCount(index[j]);i++)
		{
			if(showdot==TRUE || Only_MeaDot==TRUE)
			{ 
		    	switch(j)
				{
			     case 0:
				    break;
			     case 1:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				       DrawCircle(pDC,pnt);
				    break;
			     case 2:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				       DrawRect(pDC,pnt);
				    break;
			     case 3:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				       DrawCross(pDC,pnt);
				    break;
			     case 4:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				       DrawHor(pDC,pnt);
				    break;
				}
			}
			
			for(x=xc[i-1];x<=xc[i];x+=(float)0.1)
			{

				y=GetAny(index[j],rt.GetEnd(index[j]),rt.GetStart(index[j]),x);

    		    pnt.x=rect1.left+(long)((x/(float)tempstep)*width)-(long)((mintemp/(float)tempstep)*width);
	        	pnt.y=rect1.bottom+(long)(y/((float)QXResRange/fabs(rect1.Height())))-(OffsetY0/((float)QXResRange/fabs(rect1.Height())));
                if(pnt.x<rect1.left||pnt.x>rect1.right||pnt.y>rect1.top||pnt.y<rect1.bottom)
				{
					pDC->MoveTo(pnt);
					m_BeyondRange=TRUE;
				}
			    else if(Only_MeaDot==FALSE)
		        	pDC->LineTo(pnt);
				     else pDC->MoveTo(pnt);
			}
       	} 
		if(showdot==TRUE || Only_MeaDot==TRUE)
			{
			   switch(j)
			   {
			      case 0:
				     break;
			      case 1:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				        DrawCircle(pDC,pnt);
				     break;
			      case 2:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
			     	    DrawRect(pDC,pnt);
				     break;
		          case 3:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
  				        DrawCross(pDC,pnt);
				     break;
			      case 4:
                    if(pnt.x>rect1.left&&pnt.x<rect1.right&&pnt.y<rect1.top&&pnt.y>rect1.bottom)
				        DrawHor(pDC,pnt);
			    	 break;
			   }
			}
	
		//restore
		//R<1 or T<0
/*oyj
		kk--;
		if (rt.GetResMin(index[kk])<1)
		{
			rect1.top+=long(2*height);
			rect1.bottom+=long(2*height);
		}
		kk++;

		if(xc[0]<0)
		{
			rect1.left-=long(width);
			rect1.right-=long(width);
		}
		
oyj */

//		rect3.top=rect1.top+long(height*0.5*j);
		rect3.top=rect1.top+long(rect1.Height()/18*j);
//		rect3.left=rect1.right+long(width/2);
		rect3.left=rect1.right+long(rect1.Width()/9);
//		rect3.right=rect3.left+long(width/2);
		rect3.right=rect3.left+long(rect1.Width()/9);
//		rect3.bottom=rect3.top+long(height*0.5);
		rect3.bottom=rect3.top+long(rect1.Height()/18);

		pnt.x=rect3.left;
		pnt.y=long((rect3.top+rect3.bottom)/2);
		pDC->MoveTo(pnt);
		pnt.x=rect3.right;
		pDC->LineTo(pnt);
		pnt.x=(rect3.left+rect3.right)/2;
		if(showdot==TRUE)
		{
		   switch(j)
		   {
			  case 0:
				break;
			  case 1:
				DrawCircle(pDC,pnt);
				break;
		      case 2:
				DrawRect(pDC,pnt);
				break;
			  case 3:
				DrawCross(pDC,pnt);
				break;
			  case 4:
				DrawHor(pDC,pnt);
				break;
		   }
		}
    	rect3.left+=long(rect1.Width()/8);
		rect3.right+=long((rect1.Width()/8)*2);
		str.Format("%s",rt.m_rtSave.m_sChannelsName[index[j]]);
		pDC->DrawText(str,rect3,DT_LEFT);

		pDC->SelectObject(pOldPen);
		Pen.DeleteObject();
	}

	Pen.CreatePen(PS_DOT,1,RGB(0,0,0));
	pOldPen=pDC->SelectObject(&Pen);

 	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
  	Font.CreateFont(fabs((long)rect1.Height()/19.635),(long)rect1.Width()/44,0,0,400,0,0,0,0,0,0,0,0,"宋体");

	pOldFont=pDC->SelectObject(&Font);


	str=maxres.GetAt(4);
	str+=maxres.GetAt(5);
	j=atoi(str);
	str.Format("%d",j);
	pDC->SetTextAlign(TA_RIGHT);
	pDC->TextOut(rect1.left-(long)rect1.Width()/33,rect1.top-(long)rect1.Height()/54,str);

	for(i=1;i<=QXResRange-1;i++)
	{
		pDC->MoveTo(rect1.right,rect1.top+(long)(i*height));
		pDC->LineTo(rect1.left,rect1.top+(long)(i*height));
		j=j-1;
		str.Format("%d",j);
		pDC->TextOut(rect1.left-(long)rect1.Width()/33,rect1.top+(long)(i*height)-rect1.Height()/54,str);

	}
	
	j=j-1;
	str.Format("%d",j);
	pDC->TextOut(rect1.left-(long)rect1.Width()/33,rect1.top+(long)(i*height)-rect1.Height()/54,str);

	m_ShowDot=width;
	str="";
	pDC->SetTextAlign(TA_CENTER); 
	str.Format("%d",mintemp);
    pDC->TextOut(rect1.left,rect1.bottom+long(height/8),str);
	for(i=1;i<=numstep;i++)
	{

		  if(i<numstep)
		{
		   pDC->MoveTo(rect1.left+(long)(i*width),rect1.top);
		   pDC->LineTo(rect1.left+(long)(i*width),rect1.bottom);
		}
        if(m_ShowDot>800)
		{
		  str.Format("%d",i*tempstep+mintemp);
		  pDC->TextOut(rect1.left+(long)(i*width),rect1.bottom+long(rect1.Height()/72),str);
		  m_ShowDot=width;
		}
		else
			m_ShowDot+=width;

	}

/* oyj
	pnt.x=(long)(rect1.left-width/5);
	pnt.y=(long)(rect1.bottom+height/10);
	//T<0
	if(xc[0]<0)
	{
		k=-1;
		l=5;
		pDC->TextOut(pnt.x,pnt.y,"-50");
		
	}
	else
	{
		k=0;
		l=6;
		pDC->TextOut(pnt.x,pnt.y,"0");
	}

	pnt.x=(long)(rect1.left-width/3);
	
	for(;k<=l;k++)
	{
		pnt.x+=(long)(width);
		str.Format("%3d",(k+1)*50);
		pDC->TextOut(pnt.x,pnt.y,str);
	}
oyj */
	str="T/℃";
//	pnt.x-=(long)(width);
//	pnt.y=rect1.bottom+(long)(height/2);
//	pDC->TextOut(pnt.x,pnt.y,str);
    pDC->TextOut(rect1.right-(long)width,rect1.bottom+(long)rect1.Height()/18,str);
/* oyj
    pnt.x=rect1.left-(long)(width/3*2);
	pnt.y=rect1.bottom-(long)(height/6);
	//R<1
	kk--;
	if (rt.GetResMin(index[kk])<1)
	{
		i=-2;
		j=7;
		pDC->TextOut(pnt.x,pnt.y,"-2");
	}
	else
	{
		i=0;
		j=9;
		pDC->TextOut(pnt.x,pnt.y,"0");
	}
	kk++;
	

	for(;i<j;i++)
	{
		pnt.y-=(long)height;
		str.Format("%d",i+1);
		pDC->TextOut(pnt.x,pnt.y,str);
	}

	pnt.x-=long(1.5*width);
oyj */
	str="lgR/Ω";
	pDC->TextOut(rect1.left-0.1364*rect1.Width(),rect1.top+rect1.Height()/9.006,str);
/* oyj
	pnt.y+=(long)(2*height);
	rect2.top=pnt.y;
	rect2.left=pnt.x;
	rect2.right=rect1.left;
	rect2.bottom=rect1.bottom/2;
	pDC->DrawText(str,rect2,DT_LEFT);
oyj */
//	if(m_BeyondRange==TRUE && !pDC->IsPrinting())
//		AfxMessageBox("曲线超出边界，重新设置边界请在菜单窗口项中设定!",MB_OK,0);

	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
	pOldFont->DeleteObject();
	Pen.DeleteObject();
	
}   

//
//	数据显示
//
void CDraw::PrintText(CDC *pDC, CRT rt, CRect rct, int index,int style)
{
	CFont Font;
	CFont *pOldFont;
	CString str("",15000);
//   	Font.CreateFont(490,190,0,0,300,0,0,0,0,0,0,0,0,"宋体");
	if(style==0) return;

	if(style==1)
	{
       Font.CreateFont(490,190,0,0,300,0,0,0,0,0,0,0,0,"宋体");
  	   pOldFont=pDC->SelectObject(&Font);
	   str.Format("\n\n\t温度\t电阻\t温度\t电阻\t温度\t电阻\t温度\t电阻\t温度\t电阻\t温度\t电阻\n");
	   int j=0;
	   str.Format("%s\t",str);
	   for(int i=rt.GetStart(index);i<rt.GetEnd(index);i++)
	   {
	   	if(rt.m_rtSave.m_fPtc[index][i]<1)
		   	str.Format("%s%.1f\t%.4f\t",str,rt.m_rtSave.m_fTem[index][i],rt.m_rtSave.m_fPtc[index][i]);
		else if(rt.m_rtSave.m_fPtc[index][i]<100)
			str.Format("%s%.1f\t%.3f\t",str,rt.m_rtSave.m_fTem[index][i],rt.m_rtSave.m_fPtc[index][i]);
		else if(rt.m_rtSave.m_fPtc[index][i]<1000)
			str.Format("%s%.1f\t%.2f\t",str,rt.m_rtSave.m_fTem[index][i],rt.m_rtSave.m_fPtc[index][i]);
		else if(rt.m_rtSave.m_fPtc[index][i]>=1e9)
			str.Format("%s%.1f\t%1.3fG\t",str,rt.m_rtSave.m_fTem[index][i],rt.m_rtSave.m_fPtc[index][i]/1e9);
		else if(rt.m_rtSave.m_fPtc[index][i]>=1e8)
			str.Format("%s%.1f\t%1.1fM\t",str,rt.m_rtSave.m_fTem[index][i],rt.m_rtSave.m_fPtc[index][i]/1e6);
		else if(rt.m_rtSave.m_fPtc[index][i]>=1e7)
			str.Format("%s%.1f\t%1.2fM\t",str,rt.m_rtSave.m_fTem[index][i],rt.m_rtSave.m_fPtc[index][i]/1e6);
		else if(rt.m_rtSave.m_fPtc[index][i]>=1e6)
			str.Format("%s%.1f\t%1.3fM\t",str,rt.m_rtSave.m_fTem[index][i],rt.m_rtSave.m_fPtc[index][i]/1e6);
		else if(rt.m_rtSave.m_fPtc[index][i]>=1e5)
			str.Format("%s%.1f\t%1.1fK\t",str,rt.m_rtSave.m_fTem[index][i],rt.m_rtSave.m_fPtc[index][i]/1e3);
		else if(rt.m_rtSave.m_fPtc[index][i]>=1e4)
			str.Format("%s%.1f\t%1.2fK\t",str,rt.m_rtSave.m_fTem[index][i],rt.m_rtSave.m_fPtc[index][i]/1e3);
		else
			str.Format("%s%.1f\t%1.3fK\t",str,rt.m_rtSave.m_fTem[index][i],rt.m_rtSave.m_fPtc[index][i]/1e3);
		j++;
		if(j==6)
		{ 
			j=0;
			str.Format("%s\n\t",str);
		}
	   }
   }
	else if(style==2)

	{
//       str.Format("\n\n\t温度\t电阻\t温度\t电阻\t温度\t电阻\t温度\t电阻\t温度\t电阻\t温度\t电阻\n");
	   int j=0,i,range;
	   float k;
       Font.CreateFont(300,120,0,0,300,0,0,0,0,0,0,0,0,"宋体");
       pOldFont=pDC->SelectObject(&Font);

       rt.Calculation(index);
	   str.Format("%s\t",str);
	   for(i=0;i<10;i++)
		   str.Format("%s%d\t\t",str,i);
    
	   for( i=rt.GetStart(index);i<rt.GetEnd(index);i++)
	   {
	    if(i!=rt.GetStart(index) && rt.m_rtSave.m_fTem[index][i]<range+10)
			continue;
	 	str.Format("%s\n",str);  
        range=(int(rt.m_rtSave.m_fTem[index][i]/10))*10;
		str.Format("%s%d\t",str,(int(rt.m_rtSave.m_fTem[index][i]/10))*10);
		for(j=0;j<10;j++)
		{ 
   //             k=int(rt.m_rtSave.m_fTem[index][i]/10)*10+j;
        if((int(rt.m_rtSave.m_fTem[index][i]/10)*10)+j<=rt.m_rtSave.m_fTem[index][rt.GetStart(index)] || (int(rt.m_rtSave.m_fTem[index][i]/10))*10+j>=rt.m_rtSave.m_fTem[index][rt.GetEnd(index)-1])
		{
			str.Format("%s\t\t",str);
			continue;
		}
		k=pow(10,rt.GetAnyR(int(rt.m_rtSave.m_fTem[index][i]/10)*10+j,index));
//k=int(rt.m_rtSave.m_fTem[index][i]/10)*10+j;
	   	if(k<1)
		   	str.Format("%s%.4f\t\t",str,k);
		else if(k<100)
//			str.Format("%s%.3f\t\t",str,pow(10,rt.GetR(i-rt.GetStart(index),int(rt.m_rtSave.m_fTem[index][i]/10)*10+j)));
			str.Format("%s%.3f\t\t",str,k);
		else if(k<1000)
			str.Format("%s%.2f\t\t",str,k);
		else if(k>=1e9)
			str.Format("%s%1.3G\t\t",str,k/1e9);
		else if(k>=1e8)
			str.Format("%s%1.1fM\t\t",str,k/1e6);
		else if(k>=1e7)
			str.Format("%s%1.2fM\t\t",str,k/1e6);
		else if(k>=1e6)
			str.Format("%s%1.3fM\t\t",str,k/1e6);
		else if(k>=1e5)
			str.Format("%s%1.1fK\t\t",str,k/1e3);
		else if(k>=1e4)
			str.Format("%s%1.2fK\t\t",str,k/1e3);
		else
			str.Format("%s%1.3fK\t\t",str,k/1e3);
		
//		j++;
//		if(j==10)
		
 	            		
//			str.Format("%s%f%t",str,pow(10,GetAnyR((index,int(rt.m_rtSave.m_fTem[index][i]/10))*10+j)));
		}
	 }
   }
	pDC->DrawText(str,rct,DT_LEFT|DT_EXPANDTABS);
   	pDC->SelectObject(pOldFont);
   	Font.DeleteObject();
   	pOldFont->DeleteObject();

}

//
//	绘制圆形
//
void CDraw::DrawCircle(CDC *pDC, CPoint pnt)
{
	CRect rect;
	CBrush brush;
	CBrush *poldbrush;
	brush.CreateSolidBrush(pencol[1]);
	poldbrush=pDC->SelectObject(&brush);
/*	rect.top=pnt.y-75;
	rect.bottom=pnt.y+75;
	rect.left=pnt.x-75;
	rect.right=pnt.x+75;*/
	rect.top=pnt.y-65;
	rect.bottom=pnt.y+65;
	rect.left=pnt.x-65;
	rect.right=pnt.x+65;
	pDC->Ellipse(rect);
	pDC->SelectObject(poldbrush);
	poldbrush->DeleteObject();
	brush.DeleteObject();
}

//
//	绘制交叉线
void CDraw::DrawCross(CDC *pDC, CPoint pnt)
{
	CPoint point[4];
	point[0].x=pnt.x-75;
	point[0].y=pnt.y-75;
	point[1].x=pnt.x+75;
	point[1].y=pnt.y-75;
	point[2].x=pnt.x-75;
	point[2].y=pnt.y+75;
	point[3].x=pnt.x+75;
	point[3].y=pnt.y+75;
	pDC->MoveTo(point[0]);
	pDC->LineTo(point[3]);
	pDC->MoveTo(point[2]);
	pDC->LineTo(point[1]);
	pDC->MoveTo(pnt);
}

//
//	绘制矩形
//
void CDraw::DrawRect(CDC *pDC, CPoint pnt)
{
	CRect rect;
	CBrush brush;
	brush.CreateSolidBrush(pencol[2]);
	rect.top=pnt.y-75;
	rect.bottom=pnt.y+75;
	rect.left=pnt.x-75;
	rect.right=pnt.x+75;
	pDC->FillRect(rect,&brush);
	brush.DeleteObject();
}

//
//	绘制垂直线
//
void CDraw::DrawHor(CDC *pDC, CPoint pnt)
{
	pDC->MoveTo(pnt.x,pnt.y-75);
	pDC->LineTo(pnt.x,pnt.y+75);
	pDC->MoveTo(pnt);
}	

//
//	绘制多曲线参数
//
void CDraw::PrintMulText(CDC *pDC, CRT rt, CRect rect, int *index)
{
	CString str("",4000);
	CString string0("",200),string1("",2000),string2("",2000),string3("",2000),
			string4("",2000),string5("",2000),string6("",200),string7("",2000),
			string8("",2000),string9("",2000),string10("",2000),string11("",2000),
			string12("",200);
	int i,j;

	for(i=0;i<5;i++)
		if(index[i]==100)
			break;
	
		
	j=0;
	string0.Format(" \t样品名称:\t%s\t",rt.m_rtSave.m_sChannelsName[index[j]]);
	string1.Format("\t室温阻值(Ω):\t%.2f\t",rt.GetRes25(index[j]));
	string2.Format("\t居里温度(℃):\t%.2f\t",rt.GetTemCurie(index[j]));
	string3.Format("\t居里阻值(Ω):\t%.2f\t",rt.GetResCurie(index[j]));
	string4.Format("\t最小阻值(Ω):\t%.2f\t",rt.GetResMin(index[j]));
	string5.Format("\t对应温度(℃):\t%.2f\t",rt.GetTemMin(index[j]));
	string6.Format("\t最大阻值(Ω):\t%s\t",Draw10(rt.GetResMax(index[j])));
	string7.Format("\t对应温度(℃):\t%.2f\t",rt.GetTemMax(index[j]));
	string8.Format("\t温度系数(%%):\t%.2f\t",rt.GetTemCoe10(index[j]));
	string9.Format("\t温度系数(%%):\t%.2f\t",rt.GetTemCoe25(index[j]));
	string10.Format("\t温度系数(%%):\t%.2f\t",rt.GetTemCoe50(index[j]));
	string11.Format("\t居里温区(℃):\t%.2f\t",rt.GetCurieRange(index[j]));
	string12.Format("\t升 阻 比 :\t%s\t",Draw10(rt.GetResRatio(index[j])));
	j=1;

	while(j<i)
	{
		string0.Format("%s\t%s\t",string0,rt.m_rtSave.m_sChannelsName[index[j]]);
		string1.Format("%s\t%.2f\t",string1,rt.GetRes25(index[j]));
		string2.Format("%s\t%.2f\t",string2,rt.GetTemCurie(index[j]));
		string3.Format("%s\t%.2f\t",string3,rt.GetResCurie(index[j]));
		string4.Format("%s\t%.2f\t",string4,rt.GetResMin(index[j]));
		string5.Format("%s\t%.2f\t",string5,rt.GetTemMin(index[j]));
		string6.Format("%s%s\t",string6,Draw10(rt.GetResMax(index[j])));
		string7.Format("%s\t%.2f\t",string7,rt.GetTemMax(index[j]));
		string8.Format("%s\t%.2f\t",string8,rt.GetTemCoe10(index[j]));
		string9.Format("%s\t%.2f\t",string9,rt.GetTemCoe25(index[j]));
		string10.Format("%s\t%.2f\t",string10,rt.GetTemCoe50(index[j]));
		string11.Format("%s\t%.2f\t",string11,rt.GetCurieRange(index[j]));
		string12.Format("%s%s\t",string12,Draw10(rt.GetResRatio(index[j])));
		j++;
	}

	str.Format("%s\n",string0);
	str.Format("%s%s\n",str,string1);
	str.Format("%s%s\n",str,string2);
	str.Format("%s%s\n",str,string3);
	str.Format("%s%s\n",str,string4);
	str.Format("%s%s\n",str,string5);
	str.Format("%s%s\n",str,string6);
	str.Format("%s%s\n",str,string7);
	str.Format("%s%s\n",str,string8);
	str.Format("%s%s\n",str,string9);
	str.Format("%s%s\n",str,string10);
	str.Format("%s%s\n",str,string11);
	str.Format("%s%s\n",str,string12);
	
	pDC->DrawText(str,CRect(rect.left+rect.Width()/100,rect.top,rect.right,rect.bottom),DT_EXPANDTABS);
}

//
//	数据显示
//
void CDraw::DrawData(CGridCtrl &grid, CRT rt)
{
	int i,j=0,k=0,l;
	int m_groupTemOne=0,m_groupTemTwo=0,m_groupTemThree=0,loop=0,m_CurCol;
	CString str;

	if(rt.client!=1){
		DrawDataRT(grid, rt);
		return;}
	
	for(i=0;i<30;i++)
	{
		if(rt.m_rtSave.m_bChannels[i]==TRUE)
		{			
			j++;
//keter demand 7-30/2002
			if(i<4)
				m_groupTemOne++;
			else if(i>=4 && i<8)
			    	m_groupTemTwo++;
			     else if(i>=8 && i<12)
					m_groupTemThree++;
			
//keter demand 7-30/2002
//			k=rt.GetCount(i);
			if(k<rt.GetCount(i))
				k=rt.GetCount(i);
			grid.SetRows(k+1);
		}
	}
	
//	grid.SetCols(j+1);
	grid.SetCols(j+3);
	
//	j=-1;

//	grid.SetCol(0);
	
//	for(i=0;i<30;i++)   //7-30
 for(loop=0;loop<3;loop++)
 {
		if(loop==0 && m_groupTemOne!=0)
		{
			m_CurCol=0;
		    grid.SetCol(m_CurCol);
		}
	    else if(loop==0 && m_groupTemOne==0)
		  continue;  
		if(loop==1 && m_groupTemTwo!=0)
		{
			m_CurCol=m_groupTemOne+1;
		    grid.SetCol(m_CurCol);
		}
		 else if(loop==1 && m_groupTemTwo==0)
		    continue;
		 if(loop==2 && m_groupTemThree!=0)
		 {
			 m_CurCol=m_groupTemOne+1+m_groupTemTwo+1;
			 grid.SetCol(m_CurCol);
		 }
		 else if(loop==2 && m_groupTemThree==0)
		    break;
						    

    	for(i=loop*4;i<loop*4+4;i++)
		{
	    	if(rt.m_rtSave.m_bChannels[i]==TRUE)
			{			
	  
		    	for(l=0;l<k;l++) // oyj7-29
				{
			      	grid.SetRow(l+1);
			
			    	str.Format("%2.1f",rt.m_rtSave.m_fTem[i][rt.GetStart(i)+l]);
			      	grid.SetText(str);
				}
		    	break;
			}

		}
//	}
	grid.SetFixedCols(0);
//	grid.SetFixedCols(m_CurCol);
	grid.SetFixedRows(0);

//	grid.SetColWidth(0,1000);
	grid.SetColWidth(m_CurCol,1000);
//	grid.SetCol(0);
	grid.SetCol(m_CurCol);
	grid.SetRow(0);
	grid.SetText("温度");

//	for(i=0;i<30;i++)
	for(i=loop*4;i<loop*4+4;i++)
	{
		if(rt.m_rtSave.m_bChannels[i]==TRUE)
		{	
			CString str1;
//			j++;	        
//			grid.SetColWidth(j+1,1200);
			m_CurCol++;
	    	grid.SetColWidth(m_CurCol,1200);
			grid.SetRow(0);
//			grid.SetCol(j+1);
			grid.SetCol(m_CurCol);

			str.Format("%s",rt.m_rtSave.m_sChannelsName[i]);
			grid.SetText(str);


			for(l=0;l<k;l++)  //oyj7-29
			{
				grid.SetRow(l+1);
				str.Format("%s",Draw10(rt.m_rtSave.m_fPtc[i][rt.GetStart(i)+l]));
				if(str=="1.000E+0" && l>0)//
				{
					grid.SetRow(l);
                    str1=grid.GetText();
					grid.SetRow(l+1);
				    if(str1!="超量程")
					{
						float m_data;
						m_data=atof(str1);
						if(m_data>=1)
                           grid.SetText("超量程");
						else
	                       grid.SetText(str);
					}
					else
                        grid.SetText("超量程");
				}
				else
 						grid.SetText(str);
			}
		}
	}
}	

}

//
//	绘制数据显示用的表格
//
void CDraw::DrawDataRT(CGridCtrl &grid, CRT rt)
{
	int i,j=0,k=0,l;
	CString str;
	
	for(i=0;i<30;i++)
	{
		if(rt.m_rtSave.m_bChannels[i]==TRUE)
		{			
			j++;
			
			k=rt.GetCount(i);
			grid.SetRows(k+1);
		}
	}
	
	grid.SetCols(j+1);
	
	j=-1;

	grid.SetCol(0);
	
	for(i=0;i<30;i++)
	{
		if(rt.m_rtSave.m_bChannels[i]==TRUE)
		{			
	
			for(l=0;l<k;l++)
			{
				grid.SetRow(l+1);
			
				str.Format("%2.1f",rt.m_rtSave.GetT(i,rt.GetStart(i)+l));
				grid.SetText(str);
			}
			break;
		}

	}
	grid.SetFixedCols(0);
	grid.SetFixedRows(0);

	grid.SetColWidth(0,1000);
	grid.SetCol(0);
	grid.SetRow(0);
	grid.SetText("温度");

	for(i=0;i<30;i++)
	{
		if(rt.m_rtSave.m_bChannels[i]==TRUE)
		{			
			j++;
	
			grid.SetColWidth(j+1,1200);
			grid.SetRow(0);
			grid.SetCol(j+1);
			str.Format("%s",rt.m_rtSave.m_sChannelsName[i]);
			grid.SetText(str);

			for(l=0;l<k;l++)
			{
				grid.SetRow(l+1);
				str.Format("%s",Draw10(rt.m_rtSave.m_fPtc[i][rt.GetStart(i)+l]));
				grid.SetText(str);
			}
		}
	}
	
}

//
//	参数显示
//
void CDraw::DrawRef(CGridCtrl &grid, CRT rt,int CPptc)
{
   if(CPptc==1)
   {
	int i,j=-1,k=0;
	CString str;
	grid.SetFixedCols(0);
	grid.SetFixedRows(0);

	grid.SetColWidth(0,1500);

	grid.SetRows(15);
	grid.SetCol(0);
	grid.SetRow(0);
	str.Format("样品名称　");
	grid.SetText(str);
	grid.SetRow(1);
	str.Format("起始温度(℃)");
	grid.SetText(str);
	grid.SetRow(2);
	str.Format("起始电阻(Ω)");
	grid.SetText(str);
	grid.SetRow(3);
	str.Format("25℃电阻(Ω)");
	grid.SetText(str);
	grid.SetRow(4);
	str.Format("最小阻值(Ω)");
	grid.SetText(str);
	grid.SetRow(5);
//	str.Format("对应温度(℃)");
	str.Format("Rmin时温度(℃)");
	grid.SetText(str);
	grid.SetRow(6);
	str.Format("最大阻值(Ω)");
	grid.SetText(str);
	grid.SetRow(7);
//	str.Format("对应温度(℃)");
	str.Format("Rmax时温度(℃)");
	grid.SetText(str);
	grid.SetRow(8);
//	if(rt.GetStartTem0(index)<=25.0)

	str.Format("1.5倍R25对应温度");
	grid.SetText(str);
	grid.SetRow(9);
	str.Format("2.0倍R25对应温度");
	grid.SetText(str);
	grid.SetRow(10);
	str.Format("3.0倍R25对应温度");
	grid.SetText(str);
	grid.SetRow(11);
	str.Format("5.0倍R25对应温度");
	grid.SetText(str);
    grid.SetRow(12);
	str.Format("10.倍R25对应温度");
	grid.SetText(str);	grid.SetRow(13);
	str.Format("升  阻  比");
	grid.SetText(str);
	grid.SetRow(14);
	str.Format("测试结束温度(℃)");
	grid.SetText(str);
	j=0;
	for(i=0;i<30;i++)
	{
		if(rt.m_rtSave.m_bChannels[i]==TRUE)
		{
			j++;
		}
	}

	grid.SetCols(j+1);
	j=-1;		


			
 	for(i=0;i<30;i++)
	{

		if(rt.m_rtSave.m_bChannels[i]==TRUE)
		{
			j++;
			grid.SetCol(j+1);
			grid.SetColWidth(j+1,800);

			
			grid.SetRow(0);
			str.Format("%s",rt.m_rtSave.m_sChannelsName[i]);
			grid.SetText(str);
			
			grid.SetRow(1);
			str.Format("%.2f",rt.GetStartTem0(i));
			grid.SetText(str);
			grid.SetRow(2);
        	str.Format("%s",Draw10((float)pow(10.0,rt.GetStartRes0(i))));

			grid.SetText(str);
    		grid.SetRow(3);
			str.Format("%s",Draw10(rt.GetRes25(i)));
			grid.SetText(str);
			grid.SetRow(4);
			str.Format("%s",Draw10(rt.GetResMin(i)));//Draw10(rt.GetResMin(index))
			grid.SetText(str);
			grid.SetRow(5);
			str.Format("%.2f",rt.GetTemMin(i));
			grid.SetText(str);
			grid.SetRow(6);
			str.Format("%s",Draw10(rt.GetResMax(i)));
			grid.SetText(str);
			grid.SetRow(7);
			str.Format("%.2f",rt.GetTemMax(i));
			grid.SetText(str);
			rt.Calculation(i);
			grid.SetRow(8);
            if(rt.GetAnyT(log10(1.5*rt.GetRes25(i)),i)==-100)
//				str="无此数据";
				str="无";
			
			else
				str.Format("%.2f",rt.GetAnyT(log10(1.5*rt.GetRes25(i)),i));
			grid.SetText(str);
			grid.SetRow(9);
			 if(rt.GetAnyT(log10(2.0*rt.GetRes25(i)),i)==-100)
//				str="无此数据";
				str="无";
			
			else
		    	str.Format("%.2f",rt.GetAnyT(log10(2.0*rt.GetRes25(i)),i));
			grid.SetText(str);
			grid.SetRow(10);
			 if(rt.GetAnyT(log10(3.0*rt.GetRes25(i)),i)==-100)
//				str="无此数据";
				str="无";
			
			else
			    str.Format("%.2f",rt.GetAnyT(log10(3.0*rt.GetRes25(i)),i));
			grid.SetText(str);
			grid.SetRow(11);
			 if(rt.GetAnyT(log10(5.0*rt.GetRes25(i)),i)==-100)
//				str="无此数据";
				str="无";

			else
			    str.Format("%.2f",rt.GetAnyT(log10(5.0*rt.GetRes25(i)),i));
			grid.SetText(str);
			grid.SetRow(12);
			 if(rt.GetAnyT(log10(10.0*rt.GetRes25(i)),i)==-100)
//				str="无此数据";			
				str="无";

			else
		     	str.Format("%.2f",rt.GetAnyT(log10(10.0*rt.GetRes25(i)),i));
			grid.SetText(str);
            grid.SetRow(13);
			str.Format("%s",Draw10(rt.GetResRatio(i)));
			grid.SetText(str);
			grid.SetRow(14);
			str.Format("%.2f",rt.GetEndTem(i));
			grid.SetText(str);


		}
	}
   }
   else  
   {//CPptc==0
	int i,j=-1,k=0;
	CString str;

	grid.SetFixedCols(0);
	grid.SetFixedRows(0);

	grid.SetColWidth(0,1500);

//oyj10-11	grid.SetRows(13);
    grid.SetRows(14);
	grid.SetCol(0);
	grid.SetRow(0);
	str.Format("样品名称　");
	grid.SetText(str);
	grid.SetRow(1);
	str.Format("室温电阻(Ω)");
	grid.SetText(str);
	grid.SetRow(2);
	str.Format("居里温度(℃)");
	grid.SetText(str);
	grid.SetRow(3);
	str.Format("居里阻值(Ω)");
	grid.SetText(str);
	grid.SetRow(4);
	str.Format("最小阻值(Ω)");
	grid.SetText(str);
	grid.SetRow(5);
	str.Format("对应温度(℃)");
	grid.SetText(str);
	grid.SetRow(6);
	str.Format("最大阻值(Ω)");
	grid.SetText(str);
	grid.SetRow(7);
	str.Format("对应温度(℃)");
	grid.SetText(str);
	grid.SetRow(8);
	str.Format("温度系数(10-25)");
	grid.SetText(str);
	grid.SetRow(9);
	str.Format("温度系数(15-25)");
	grid.SetText(str);
	grid.SetRow(10);
	str.Format("温度系数(0-15)");
	grid.SetText(str);
	grid.SetRow(11);
	str.Format("居里温区(℃)");
	grid.SetText(str);
	grid.SetRow(12);
	str.Format("升  阻  比");
	grid.SetText(str);
	grid.SetRow(13);
	str.Format("Rmin/R25");
	grid.SetText(str);
	j=0;
	for(i=0;i<30;i++)
	{
		if(rt.m_rtSave.m_bChannels[i]==TRUE)
		{
			j++;
		}
	}

	grid.SetCols(j+1);
	j=-1;		
	for(i=0;i<30;i++)
	{
		if(rt.m_rtSave.m_bChannels[i]==TRUE)
		{
			j++;
			grid.SetCol(j+1);
			grid.SetColWidth(j+1,800);

			
			grid.SetRow(0);
			str.Format("%s",rt.m_rtSave.m_sChannelsName[i]);
			grid.SetText(str);
			
			grid.SetRow(1);
			if(rt.GetRes25(i)<1)
    			str.Format("%.4f",rt.GetRes25(i));
            else
    			str.Format("%.2f",rt.GetRes25(i));
			grid.SetText(str);
			grid.SetRow(2);
			str.Format("%.2f",rt.GetTemCurie(i));
			grid.SetText(str);
			grid.SetRow(3);
			str.Format("%.2f",rt.GetResCurie(i));
			grid.SetText(str);
			grid.SetRow(4);
			if(rt.GetResMin(i)<1)
		    	str.Format("%.4f",rt.GetResMin(i));
			else
		    	str.Format("%.2f",rt.GetResMin(i));
			grid.SetText(str);
			grid.SetRow(5);
			str.Format("%.2f",rt.GetTemMin(i));
			grid.SetText(str);
			grid.SetRow(6);
			str.Format("%s",Draw10(rt.GetResMax(i)));
			grid.SetText(str);
			grid.SetRow(7);
			str.Format("%.2f",rt.GetTemMax(i));
			grid.SetText(str);
			grid.SetRow(8);
			str.Format("%.2f%%",rt.GetTemCoe10(i));
			grid.SetText(str);
			grid.SetRow(9);
			str.Format("%.2f%%",rt.GetTemCoe25(i));
			grid.SetText(str);
			grid.SetRow(10);
			str.Format("%.2f%%",rt.GetTemCoe50(i));
			grid.SetText(str);
			grid.SetRow(11);
			str.Format("%.2f",rt.GetCurieRange(i));
			grid.SetText(str);
			grid.SetRow(12);
			str.Format("%s",Draw10(rt.GetResRatio(i)));
			grid.SetText(str);
			grid.SetRow(13);
			str.Format("%s",Draw10(rt.GetResMin(i)/rt.GetRes25(i)));
			grid.SetText(str);

		}
	}
	}
}

//
//	获取温度为t对应的拟合阻值
//
float CDraw::GetR(int i, float t)
{
	float a1,a2,a3,a,b,c;
    float r;

    a1 = (yc[i+1]-yc[i]) / (xc[i+1]-xc[i]);
    a2 = (yc[i+2]-yc[i]) / (xc[i+2]-xc[i]);
    a3 = (a2-a1) / (xc[i+2]-xc[i+1]);

    a = a3;
    b = a1 - a3*(xc[i]+xc[i+1]);
    c = a3*xc[i]*xc[i+1] - a1*xc[i] + yc[i];

    r = a*t*t + b*t + c;
    
	if(r>3e8)
		r=3e8;
    //if(r<0)
	//	r=0;
    
	return r;
}

//
//	获取i到j点之间，温度大于t时的阻值
//
float CDraw::GetAny(int index,int i,int j, float t)
{
	float r;
    int gi;

	for(gi=0;gi<i-j;gi++)
	    if(xc[gi]>t) break;

	r=GetR(gi-1,t);
	return  r;
}

//
//	将浮点数以指数形式字符串输出
//
CString CDraw::Draw10(float x)
{
	CString str1,str2,str3;
	CString str("",2000);

	str3.Format("%4.3e",x);
	str1=str3.Left(5);
	str2=str3.Right(1);
	str3=str3.Mid(6,1);
	str.Format("%sE%s%s",str1,str3,str2);

	return str;
}

//
//	显示“数据显示”或“参数显示”参数
//
void CDraw::PrintRef(CGridCtrl &grid,CDC *pDC, CRect rect,CRT rt,int index1,int index2,int m_uFlag,int CPptc)
{
	CFont Font;
	CRect rect1;
	CFont *pOldFont;
	
	CString string,string1("",200),str("",8000);
 //   CString str1("",8000);
	int i,j,k,endk;
	int loop;
    int m_SampleNum=0;

//	GetClientRect(rect);  //oyj 7-22

//	str1.Format("%s",rt.m_rtSave.m_sStr[1]);
//    str1=str1.Left(8);

//	str.Format("%s   3     升温方式:             %.1f℃-%3i℃ 间隔 %2i ℃\n                                   %3i-%3i℃ 间隔%02i ℃\n",str,rt.GetStartTem0(index),rt.m_rtSave.MaxT[0],rt.m_rtSave.Step[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.MaxT[1],rt.m_rtSave.Step[1]);

//	str.Format("测试时间： %s  升温方式:  %.1f℃-%3i℃ 间隔 %2i ℃  %3i℃-%3i℃ 间隔%02i ℃   ",rt.m_rtSave.m_sStr[0],rt.GetStartTem0(0),rt.m_rtSave.MaxT[0],rt.m_rtSave.Step[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.MaxT[1],rt.m_rtSave.Step[1]);
//	str.Format("测试时间： %s                      升温方式:  To(始温)-%3i℃ 间隔 %2i ℃ \n                                                                         %3i℃-%3i℃ 间隔%02i ℃\n",rt.m_rtSave.m_sStr[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.Step[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.MaxT[1],rt.m_rtSave.Step[1]);
	if(m_uFlag==3)
	{
		
		string1="R/T测试数据记录";
		rect1.CopyRect(rect);
   		rect1.top-=rect.Height()/9;
       	pDC->DrawText(string1,rect1,DT_CENTER|DT_EXPANDTABS);	
/*7-30		for(k=0;k<NMBOFSPL;k++)
		{
			if(rt.m_rtSave.m_bChannels[k]==1)

				m_SampleNum++;
		}

 
*/		
    	if(rect.Width()<rect.Height())
		{
 //       	Font.CreateFont((long)90*0.8,(long)60*0.7,0,0,400,0,0,0,0,0,0,0,0,"宋体");
 //        	Font.CreateFont((long)35*0.8,(long)20*0.7,0,0,400,0,0,0,0,0,0,0,0,"宋体");
 //	     	Font.CreateFont((long)rect.Height()/72.25,(long)rect.Width()/100.2,0,0,400,0,0,0,0,0,0,0,0,"宋体");
        	Font.CreateFont((long)rect.Height()/60,(long)rect.Width()/90,0,0,400,0,0,0,0,0,0,0,0,"宋体");

        	pOldFont=pDC->SelectObject(&Font);
 
			grid.SetRow(1);
			grid.SetCol(index1);
        	str.Format("测试时间： %s                      升温方式:  %s℃-%3i℃ 间隔 %2i ℃ \n                                                                        %3i℃-%3i℃ 间隔 %2i ℃\n",rt.m_rtSave.m_sStr[0],grid.GetText(),rt.m_rtSave.MaxT[0],rt.m_rtSave.Step[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.MaxT[1],rt.m_rtSave.Step[1]);
            if(rt.m_rtSave.soaking[0]==0) 
			{
        		str.Format("%s                                                                        分段匀速升温\n\n",str);
			}
            else 
			{
       		str.Format("%s                                                                            保温时间%02i 分钟\n\n",str,rt.m_rtSave.soaking[0]);
			}
        	j=grid.GetRows();		
        	grid.SetRow(0);//oyj from
/*7-30			if(index2>=m_SampleNum)
				index2=m_SampleNum;
*/
	     	for(k=index1;k<=index2;k++)
			{
		    	grid.SetCol(k);
//		    	string+=grid.GetText()+"\t\t";
				string1=grid.GetText();
				if(string1.GetLength( )>6)
//						string+=grid.GetText()+"\t";
						string+=grid.GetText()+"\t";
				else
						string+=grid.GetText()+"\t\t";
			}
			string1=string;
			string.Format("%s\n\t",string1);
	     	for(k=index1+1;k<=index2;k++)
			{
				string1=string;
				string.Format("%s\t\t电阻值",string1);
			}

	    	str.Format("%s\t%s\n",str,string);
	    	string="";//to oyj
        	for(i=1;i<j;i++) 
			{
	        	grid.SetRow(i);
	        	for(k=index1;k<=index2;k++)
				{
		        	grid.SetCol(k);
			    	string1=grid.GetText();
			    	if(string1.GetLength( )>7)
						string+=grid.GetText()+"\t";
				    else
					    string+=grid.GetText()+"\t\t";


/*oyj7-25			    	if(string1.GetLength( )>7)
						string+=grid.GetText()+"\t";
			    	else if(string1!="超量程")
						   string+=grid.GetText()+"\t\t";
					     else
						   string+=grid.GetText()+"\t\t\t";
*/
//		        	string+=grid.GetText()+"\t";
				}
//	        	grid.SetCol(0);
//	    	    str.Format("%s%s\t%s\n",str,grid.GetText(),string);
				if(j<=31)
                    str.Format("%s\t%s\n\n",str,string);
				else
	    	        str.Format("%s\t%s\n",str,string);
//	        	pDC->DrawText(str,rect,DT_EXPANDTABS);
	        	string="";
			}
    		rect.top-=rect.Height()/15;
			rect.bottom+=rect.Height()/16;
        	pDC->DrawText(str,rect,DT_EXPANDTABS);	
    	   	string="";
/*            if(j<30 && m_SampleNum>index2)
			{
                str="";
	        	grid.SetRow(0);//oyj from
//	        	for(k=index2+1;k<=index2+6;k++)
	        	for(k=index2+1;k<=m_SampleNum;k++)
				{
	    	    	grid.SetCol(k);
//		    	    string+=grid.GetText()+"\t\t";
				string1=grid.GetText();
				if(string1.GetLength( )>6)
						string+=grid.GetText()+"\t";
				else
						string+=grid.GetText()+"\t\t";
	
				}
    			string1=string;
//		    	string.Format("%s\n\t电阻值\t\t电阻值\t\t电阻值\t\t电阻值\t\t电阻值\t\t电阻值",string1);
		    	string.Format("%s\n\t电阻值",string1);
	        	for(k=index2+2;k<=m_SampleNum;k++)
				{
			    	string1=string;
			    	string.Format("%s\t\t电阻值",string1);
				}


				grid.SetCol(0);
	        	str.Format("%s\t%s\n",grid.GetText(),string);
//	        	pDC->DrawText(str,rect,DT_EXPANDTABS);
	    	    string="";//to oyj
             	for(i=1;i<j;i++) 
				{
     	        	grid.SetRow(i);
//	            	for(k=index2+1;k<=index2+6;k++)
	            	for(k=index2+1;k<=m_SampleNum;k++)
					{
      		        	grid.SetCol(k);
//      		        	string+=grid.GetText()+"\t";
				string1=grid.GetText();
				if(string1.GetLength( )>7)
						string+=grid.GetText()+"\t";
				else
						string+=grid.GetText()+"\t\t";
	
					}
      	        	grid.SetCol(0);
      	        	str.Format("%s%s\t%s\n",str,grid.GetText(),string);
//	            	pDC->DrawText(str,rect,DT_EXPANDTABS);
	              	string="";
				}
                rect.top+=rect.Height()/2;

              	pDC->DrawText(str,rect,DT_EXPANDTABS);	
			}
			*/
          	pDC->SelectObject(pOldFont);
          	Font.DeleteObject();
         	pOldFont->DeleteObject();
		}
    	else  //rect.Width()>=rect.Height()
		{
			grid.SetRow(1);
			grid.SetCol(index1);
        	str.Format("测试时间： %s                      升温方式:  %s℃-%3i℃ 间隔 %2i ℃ \n                                                      %3i℃-%3i℃ 间隔 %2i ℃\n",rt.m_rtSave.m_sStr[0],grid.GetText(),rt.m_rtSave.MaxT[0],rt.m_rtSave.Step[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.MaxT[1],rt.m_rtSave.Step[1]);
            if(rt.m_rtSave.soaking[0]==0) 
			{
        		str.Format("%s                                                      分段匀速升温\n\n",str);
			}
            else 
			{
       		str.Format("%s                                                          保温时间%02i 分钟\n\n",str,rt.m_rtSave.soaking[0]);
			}

	    	j=grid.GetRows();
         	grid.SetRow(0);//oyj from
/*7-30			if( index2>=m_SampleNum)
		    	index2=m_SampleNum;
*/
      		for(k=index1;k<=index2;k++)
//	      	for(k=index1;k<=12;k++)
			{
      			grid.SetCol(k);
      			string+=grid.GetText()+"\t\t";
			}
//      		grid.SetCol(0);
//     		str.Format("%s%s\t%s\n",str,grid.GetText(),string);
    		string1=string;
//			string.Format("%s\n\t电阻值",string1);
			string.Format("%s\n\t",string1);
	     	for(k=index1+1;k<=index2;k++)
			{
				string1=string;
				string.Format("%s\t\t电阻值",string1);
			}

//	    	grid.SetCol(0);
//	    	str.Format("%s%s\t%s\n",str,grid.GetText(),string);
	    	str.Format("%s\t%s\n",str,string);


//    		pDC->DrawText(str,rect,DT_EXPANDTABS);
     		string="";//to oyj
//      	for(i=0;i<j;i++) 
         	for(i=1;i<j;i++) 
			{
     	     	grid.SetRow(i);
     	           	for(k=index1;k<=index2;k++)
					{
    	          		grid.SetCol(k);
//      	          		string+=grid.GetText()+"\t";
						string1=grid.GetText();
			         	if(string1.GetLength( )>7)
					      	string+=grid.GetText()+"\t";
			            else
					      	string+=grid.GetText()+"\t\t";

					}
//      	    	grid.SetCol(0);
//      	      	str.Format("%s%s\t%s\n",str,grid.GetText(),string);
      	        	str.Format("%s\t%s\n",str,string);
//    	     	pDC->DrawText(str,rect,DT_EXPANDTABS);
     	      	string="";
			}
      		pDC->DrawText(str,rect,DT_EXPANDTABS);

		}
	}
	else   //m_uFlag==4
	{

		string1="R/T测试主要参数记录";
		rect1.CopyRect(rect);
   		rect1.top-=rect.Height()/9;
       	pDC->DrawText(string1,rect1,DT_CENTER|DT_EXPANDTABS);
		for(k=0;k<NMBOFSPL;k++)
		{
			if(rt.m_rtSave.m_bChannels[k]==1)
				m_SampleNum++;
		}

	 
    	if(rect.Width()<rect.Height())
		{
//			int loop;
//         	Font.CreateFont((long)40*0.8,(long)25*0.7,0,0,400,0,0,0,0,0,0,0,0,"宋体");
//          	Font.CreateFont((long)40*0.87,(long)80*0.7,0,0,400,0,0,0,0,0,0,0,0,"宋体");
 //        	Font.CreateFont((long)120*0.87,(long)80*0.7,0,0,400,0,0,0,0,0,0,0,0,"宋体");
         	Font.CreateFont((long)rect.Height()/52.59,(long)rect.Width()/76.93,0,0,400,0,0,0,0,0,0,0,0,"宋体");

        	pOldFont=pDC->SelectObject(&Font);
     		str.Format("测试时间： %s                      升温方式:  %.1f℃(始温)-%3i℃ 间隔 %2i ℃ \n                                                                   %3i℃-%3i℃ 间隔 %2i ℃\n",rt.m_rtSave.m_sStr[0],rt.GetStartTem0(1),rt.m_rtSave.MaxT[0],rt.m_rtSave.Step[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.MaxT[1],rt.m_rtSave.Step[1]);
            if(rt.m_rtSave.soaking[0]==0) 
			{
           		str.Format("%s                                                                   分段匀速升温\n\n",str);
			}
            else 
			{
          		str.Format("%s                                                                   保温时间%02i 分钟\n\n",str,rt.m_rtSave.soaking[0]);
			}
	    	j=grid.GetRows();
			string="";
			string1="";
	    for(loop=1;loop<=3;loop++)
		{
        	grid.SetRow(0);//oyj from
//	     	for(k=index1;k<=index2;k++)
			if((loop-1)*4+4<=m_SampleNum)
				endk=(loop-1)*4+4;
			else
				endk=m_SampleNum;
			if((loop-1)*4+1>m_SampleNum)
				break;
//			for(k=(loop-1)*4+1;k<=(loop-1)*4+4;k++)
			for(k=(loop-1)*4+1;k<=endk;k++)

			{
		    	grid.SetCol(k);
//		    	string+=grid.GetText()+"\t\t";
				string1=grid.GetText();
				if(string1.GetLength( )>6)
						string+=grid.GetText()+"\t";
				else
						string+=grid.GetText()+"\t\t";
			}
			string1=string;
//			string.Format("%s\n\t\t电阻值\t\t电阻值\t\t电阻值\t\t电阻值",string1);
//		   	string.Format("%s\n\t\t电阻值",string1);
//			if((loop-1)*4+2<=m_SampleNum)
//			{
//	       	    for(k=(loop-1)*4+2;k<=endk;k++)
//				{
//		        	string1=string;
//		        	string.Format("%s\t\t电阻值",string1);
//				}
//			}

			grid.SetCol(0);
	    	str.Format("%s%s\t%s\n",str,grid.GetText(),string);
//  		pDC->DrawText(str,rect,DT_EXPANDTABS);
	    	string="";//to oyj
       	for(i=1;i<j;i++) 
		{
	        	grid.SetRow(i);
//	        	for(k=index1;k<=index2;k++)
//			    for(k=(loop-1)*4+1;k<=(loop-1)*4+4;k++)
			  if(CPptc==1)
			  {  
				  for(k=(loop-1)*4+1;k<=endk;k++)
				{
		        	grid.SetCol(k);
					if(i==1 || i==5 ||(i>=7 && i<=12) || i==14) 
						string+=grid.GetText()+"\t\t";
					else
		            	string+=grid.GetText()+"\t";
				}
	        	grid.SetCol(0);
//			    str1=str;
         
				if(i==2 ||(i>3 && i<5)|| i==6)
				{
					string1=grid.GetText();
					string1=string1.Left(8);
					str.Format("%s%s (Ω)\t%s\n",str,string1,string);
				}
			    if(i>=8 && i<=12)
				{       
					 
						if(rt.GetStartTem0((loop-1)*4+1)<=25.0)
//					str.Format("%s%s%s\n",str,grid.GetText(),string);
						{
				    	  if(i==8)
							str.Format("%s1.5倍R25时温度%s\n",str,string);
						  else if(i==9)
  							str.Format("%s2.0倍R25时温度%s\n",str,string);
							  else if(i==10)
						    	str.Format("%s3.0倍R25时温度%s\n",str,string);
							       else if(i==11)
						        	str.Format("%s5.0倍R25时温度%s\n",str,string);
								         else if(i==12)
					                		str.Format("%s10.倍R25时温度%s\n",str,string);
						}
						else
						{
				    	  if(i==8)
							str.Format("%s1.5倍Ro时温度℃ %s\n",str,string);
						  else if(i==9)
  							str.Format("%s2.0倍Ro时温度℃ %s\n",str,string);
							  else if(i==10)
						    	str.Format("%s3.0倍Ro时温度℃ %s\n",str,string);
							       else if(i==11)
						        	str.Format("%s5.0倍Ro时温度℃ %s\n",str,string);
								         else if(i==12)
					                		str.Format("%s10.倍Ro时温度℃ %s\n",str,string);
						}
	
				}			
//	    	    else
				if(i==1||i==3 ||i==5||i==7||i==13 ||i==14)
				       str.Format("%s%s\t%s\n",str,grid.GetText(),string);
			  }
//	        	pDC->DrawText(str,rect,DT_EXPANDTABS);
	
	    	else  //CPptc==0 cerimac
	//			str.Format("%s%s",string,string1);
			{
			  for(k=(loop-1)*4+1;k<=endk;k++)
				{
		        	grid.SetCol(k);
					if(i==6 || i==12 ||i==13) 
						string+=grid.GetText()+"\t";
					else
		            	string+=grid.GetText()+"\t\t";
	//		       str.Format("%s%s\t%s\n",str,grid.GetText(),string);

				}
	        	grid.SetCol(0);
//			    str1=str;
         
//				if(i==2 ||(i>3 && i<5)|| i==6)
//				{
					string1=grid.GetText();
//					string1=string1.Left(8);
//					str.Format("%s%s (Ω)\t%s\n",str,string1,string);
//				}
                if(i==8 || i==9)
					str.Format("%s%s %s\n",str,string1,string);
                else
					str.Format("%s%s \t%s\n",str,string1,string);
	
	
			}
			
				//	        	pDC->DrawText(str,rect,DT_EXPANDTABS);
	        	string="";
		}
			str.Format("%s\n\n",str);
		}
    		rect.top-=rect.Height()/15;
			rect.left-=rect.Width()/40;
        	pDC->DrawText(str,rect,DT_EXPANDTABS);	
    	   	string="";
        	pDC->SelectObject(pOldFont);
          	Font.DeleteObject();
         	pOldFont->DeleteObject();
		}
    	else  //rect.Width()>rect.Height()
		{
        	str.Format("测试时间： %s                      升温方式:  %.1f℃(始温)-%3i℃ 间隔 %2i ℃ \n                                                       %3i℃-%3i℃ 间隔 %2i ℃\n",rt.m_rtSave.m_sStr[0],rt.GetStartTem0(1),rt.m_rtSave.MaxT[0],rt.m_rtSave.Step[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.MaxT[1],rt.m_rtSave.Step[1]);
            if(rt.m_rtSave.soaking[0]==0) 
			{
          		str.Format("%s                                                       分段匀速升温\n\n",str);
			}
            else 
			{
        		str.Format("%s                                                       保温时间%02i 分钟\n\n",str,rt.m_rtSave.soaking[0]);
			}

       	for(loop=1;loop<=2;loop++)
		{
	    	j=grid.GetRows();
         	grid.SetRow(0);//oyj from
 //     		for(k=index1;k<=index2;k++)
			string="";
			if((loop-1)*6+6<=m_SampleNum)
				endk=(loop-1)*6+6;
			else
				endk=m_SampleNum;
			if((loop-1)*6+1>m_SampleNum)
				break;

//			for(k=(loop-1)*6+1;k<=(loop-1)*6+6;k++)
			for(k=(loop-1)*6+1;k<=endk;k++)
			{
      			grid.SetCol(k);
				
      			 string+=grid.GetText()+"\t\t";
			}
      		grid.SetCol(0);
			string1=string;
//			string.Format("%s\n\t\t电阻值\t\t电阻值\t\t电阻值\t\t电阻值\t\t电阻值\t\t电阻值",string1);
//		   	string.Format("%s\n\t\t电阻值",string1);
//			if((loop-1)*6+2<=m_SampleNum)
//			{
//	       	    for(k=(loop-1)*6+2;k<=endk;k++)
//				{
//		        	string1=string;
//		        	string.Format("%s\t\t电阻值",string1);
//				}
//			}

			str.Format("%s%s\t%s\n",str,grid.GetText(),string);
 //   		pDC->DrawText(str,rect,DT_EXPANDTABS);
     		string="";//to oyj
//      	for(i=0;i<j;i++) 
         	for(i=1;i<j;i++) 
			{
     	     	grid.SetRow(i);
				string="";
				if(CPptc==1)
				{
//     	           	for(k=index1;k<=index2;k++)
//		        	for(k=(loop-1)*6+1;k<=(loop-1)*6+6;k++)
		        	for(k=(loop-1)*6+1;k<=endk;k++)
					{
						
    	          		grid.SetCol(k);
				    	if(i==1 || i==5 ||(i>=7 && i<=12) || i==14) 
      	          		    string+=grid.GetText()+"\t\t";
						else 
							string+=grid.GetText()+"\t";

					}
      	        	grid.SetCol(0);
  /*  	7-22		if((i>=8 && i<=12) || i==1 || i==14)
     	        	str.Format("%s%s %s\n",str,grid.GetText(),string);
				else
     	        	str.Format("%s%s\t%s\n",str,grid.GetText(),string);
//    	     	pDC->DrawText(str,rect,DT_EXPANDTABS);
				*/
   //  	      	string="";
//				if(i==2 ||(i>3 && i<8))
			     	if(i==2 ||(i>3 && i<5)|| i==6)
					{
			      		string1=grid.GetText();
				       	string1=string1.Left(8);
				     	str.Format("%s%s (Ω)\t%s\n",str,string1,string);
					}
			        if(i>=8 && i<=12)
					{
					   
//						if(rt.GetStartTem0((loop-1)*4+1)<=25.0)
//					str.Format("%s%s%s\n",str,grid.GetText(),string);
//						if(rt.GetStartTem0(index1)<=25.0)
						if(rt.GetStartTem0((loop-1)*6+1)<=25.0)
						{
				    	  if(i==8)
							str.Format("%s1.5倍R25时温度℃ %s\n",str,string);
						  else if(i==9)
  							str.Format("%s2.0倍R25时温度℃ %s\n",str,string);
							  else if(i==10)
						    	str.Format("%s3.0倍R25时温度℃ %s\n",str,string);
							       else if(i==11)
						        	str.Format("%s5.0倍R25时温度℃ %s\n",str,string);
								         else if(i==12)
					                		str.Format("%s10.倍R25时温度℃ %s\n",str,string);
						}
						else
						{
				    	  if(i==8)
							str.Format("%s1.5倍Ro时温度℃  %s\n",str,string);
						  else if(i==9)
  							str.Format("%s2.0倍Ro时温度℃  %s\n",str,string);
							  else if(i==10)
						    	str.Format("%s3.0倍Ro时温度℃  %s\n",str,string);
							       else if(i==11)
						        	str.Format("%s5.0倍Ro时温度℃  %s\n",str,string);
								         else if(i==12)
					                		str.Format("%s10.倍Ro时温度℃  %s\n",str,string);
						}
	
					}			
//	    	    else
	    			if(i==1||i==3 ||i==5||i==7||i==13 ||i==14)
				       str.Format("%s%s\t%s\n",str,grid.GetText(),string);
//	        	pDC->DrawText(str,rect,DT_EXPANDTABS);
				}
	        	else  //CPptc==0 cerimac
				{
		      	  for(k=(loop-1)*6+1;k<=endk;k++)
				  {
		        	grid.SetCol(k);
					if(i==6 || i==12 ||i==13) 
						string+=grid.GetText()+"\t";
					else
		            	string+=grid.GetText()+"\t\t";

				  }
	            	grid.SetCol(0);
					string1=grid.GetText();
					if(i==8||i==9)
	                  str.Format("%s%s %s\n",str,string1,string);
					else
				    	str.Format("%s%s \t%s\n",str,string1,string);		
				}

			}
			str.Format("%s\n\n",str);
		}
      		pDC->DrawText(str,rect,DT_EXPANDTABS);

		}
    }
}

//
//	绘制高分子PTC曲线
//
void CDraw::DrawPolymerRef(CDC *pDC, CRT rt, CRect rect, int index,CRect rect0,int CPptc,int m_client)
{ 

	CFont Font;
	CFont* pOldFont;
	CPen Pen;
	double width,height,heightcopy;
	double width0;
	CString str("",4000),str1("",200),str2;
	CRect rect2;
	CRect rect1;
	int i,index0,loop=0;
	int m_ShowDot;
	int QXResRange;
	CPoint pnt;
	float R25,r;
	BOOL m_BeyondRange=FALSE;
	CPoint CurPoint;
	index0=index;
	rt.Calculation(index);
/*  8-19
	while(rt.GetCount(index)<3 && loop<NMBOFSPL)
	{
		index=index+1;
		loop++;
	}
    if(index0!=index)
	   rt.Calculation(index);
	8-19   */
	height=fabs(rect.Height()/10);	
	Font.CreateFont((long)height*0.4,(long)(height*0.2),0,0,600,0,0,0,0,0,0,0,0,"宋体");
	pOldFont=pDC->SelectObject(&Font);

	if(pDC->IsPrinting())
	{
	rect1.top=0;
	rect1.top+=rect.Height()/16;
	rect1.bottom=rect.bottom;
	rect1.left=rect.left;
	rect1.right=rect.right;
	}
	else
	{
	   rect1.top=0;
	   rect1.top+=rect.Height()/23;
	   rect1.bottom=rect.bottom;
	   rect1.left=rect.left;
	   rect1.right=rect.right;
	}

    //  else if(m_client==5)
   //    str="深圳市富利源电子有限公司  电阻~温度特性测试报告";//SR93 HT12D F45
    if(m_client==1)
       str="上海科特高分子材料有限公司  电阻~温度特性测试报告";//TH2512 253 HT12D
    else if(m_client==6)
       str="兴勤(常州)电子有限公司  电阻~温度特性测试报告";//MR13 HT12D HP34401/KEITHLEY2000
    else if(m_client==7)
       str="成都宏明电子股份有限公司  电阻~温度特性测试报告";//MR13 HT12D HP34401/KEITHLEY2000
    else if(m_client==2)
       str="东莞为勤电子有限公司  电阻~温度特性测试报告";//253 HP34401 HT12D
    else if(m_client==3)
       str="华工科技高理电子分公司  电阻~温度特性测试报告";//253 shen gong da F45 ISA SHUnKang
    else if(m_client==9)
       str="西无二电子信息集团有限公司 电阻~温度特性测试报告";//253  F45 HT12D
    else if(m_client==4)
       str=" 敏感陶瓷教育部工程研究中心 电阻~温度特性测试报告";//83  F45 HT12D
//	   str="电阻~温度特性测试报告";//83  F45 HT12D
    else if(m_client==11)
       str="林芝电子有限责任公司  电阻~温度特性测试报告";//83  F45 HT12D
    else
	   str="电阻～温度特性测试报告";//ZWX-C F45
	//oyj 2003-5-21
	if(pDC->IsPrinting())
	{
	rect2.CopyRect(rect1);
	rect2.top=rect2.top+rect2.Height()/25;
    pDC->DrawText(str,rect2,DT_TOP|DT_CENTER);  
	}
	else pDC->DrawText(str,rect1,DT_TOP|DT_CENTER);
// oyj 2003-5-21
	rect.top-=(long)height;
	height=fabs(rect.Height()/20.0);
	width=fabs(rect.Width()/80.0);
	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
//	Font.CreateFont((long)height*0.9,(long)width*0.8,0,0,400,0,0,0,0,0,0,0,0,"宋体");
	Font.CreateFont((long)height*0.8,(long)width*0.7,0,0,400,0,0,0,0,0,0,0,0,"宋体");
   
	pOldFont=pDC->SelectObject(&Font);
	str="";

	CString EquipName;
		if(rt.ZWX==0) EquipName="ZW-A R/T特性测试仪";
        else EquipName = "ZWX-C R/T特性测试仪";
//zjun 2002/8/7	str.Format("  样品名称:%s     测量设备名称:    ZWX-B R/T特性测试仪     测试日期:%s     测试人员:\n\n",rt.m_rtSave.m_sChannelsName[index],rt.m_rtSave.m_sStr[0]);
 str.Format("  样品名称:%s     测量设备名称:    %s     测试日期:%s     测试人员:\n\n",rt.m_rtSave.m_sChannelsName[index],EquipName,rt.m_rtSave.m_sStr[0]);


//	str.Format("   样品 名称:%s   测量设备名称:\t\t      测试日期:%s\t    测试人员:\n\n",rt.m_rtSave.m_sChannelsName[index],rt.m_rtSave.m_sStr[0]);
   	str.Format("%s   一、主要参数:\t\t\t\t\t      二、  电阻温度特性曲线:",str);
	
    pDC->DrawText(str,rect,DT_LEFT|DT_EXPANDTABS);
 	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
//	Font.CreateFont((long)height*0.9,(long)width*0.8,0,0,400,0,0,0,0,0,0,0,0,"宋体");
	Font.CreateFont((long)height*0.8,(long)width*0.7,0,0,400,0,0,0,0,0,0,0,0,"宋体");
	pOldFont=pDC->SelectObject(&Font);
	str1.Format("%s",rt.m_rtSave.m_sStr[1]);
    str1=str1.Left(8);
	str="";
//	str.Format("   1     测试起始时间:       %s  %s\n",rt.m_rtSave.m_sStr[0],str1);
	str.Format("   1     测试起始时间: \n");
    str2.Format("%s  %s\n",rt.m_rtSave.m_sStr[0],str1);
//	str.Format("%s   2     测试结束时间:       %s  %s\n",str,rt.m_rtSave.endTime[0],rt.m_rtSave.endTime[1]);
	if(rt.m_DatOrRtFile==1) //*.RT file
	{
	str.Format("%s   2     测试结束时间: \n",str);
	str1=str2;
    str2.Format("%s%s  %s\n",str1,rt.m_rtSave.endTime[0],rt.m_rtSave.endTime[1]);
	}
	else
	{
	str.Format("%s   2     测试结束时间: \n",str);
	str1=str2;
    str2.Format("%s%s  %s\n",str1,"","");
	}
	//	str.Format("%s   3     升温方式:             %.1f℃-%3i℃ 间隔 %2i ℃\n                                   %3i-%3i℃ 间隔%02i ℃\n",str,rt.GetStartTem0(index),rt.m_rtSave.MaxT[0],rt.m_rtSave.Step[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.MaxT[1],rt.m_rtSave.Step[1]);
	str.Format("%s   3     升温方式: \n\n\n",str);
	str1=str2;
    str2.Format("%s%.1f℃-%3i℃ 间隔 %2i ℃\n%3i℃ -%3i℃ 间隔 %2i ℃\n",str1,rt.GetStartTem0(index),rt.m_rtSave.MaxT[0],rt.m_rtSave.Step[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.MaxT[1],rt.m_rtSave.Step[1]);
//	if(rt.m_rtSave.soaking[0]==0)str.Format("%s                                 分段匀速升温\n",str);
//    else str.Format("%s                                   保温时间%02i 分钟\n",str,rt.m_rtSave.soaking[0]);
	if(rt.m_rtSave.soaking[0]==0) 
	{
		str1=str2;
		str2.Format("%s分段匀速升温\n",str1);
	}
    else 
	{
		str1=str2;
		str2.Format("%s保温时间%02i 分钟\n",str1,rt.m_rtSave.soaking[0]);
	}
    rect.top-=(long)(height*3);	
	rect2.CopyRect(rect);
	rect2.left+=(long)width*0.7*25;
	pDC->DrawText(str2,rect2,DT_LEFT|DT_EXPANDTABS);

   if(CPptc<2)
   {
	str.Format("%s   4     测试起始温度To: \n",str);
    str2.Format("\n\n\n\n\n%.1f ℃\n",rt.GetStartTem0(index));

	str.Format("%s   5     起始电阻值Ro: \n",str);
    str1=str2;
	str2.Format("%s%s Ω\n",str1,Draw10((float)pow(10.0,rt.GetStartRes0(index))));
 
	R25=rt.GetRes25(index);//zjun
	
    if(rt.GetStartTem0(index)>25.0)
	{
    	str.Format("%s   6     25℃电阻值R25: \n",str);
		str1=str2;
		str2.Format("%s\n",str1);
	}
    else 
	{
		str.Format("%s   6     25℃电阻值R25: \n",str);
        str1=str2;
		str2.Format("%s%s Ω\n",str1,Draw10(R25));
	}
	str.Format("%s   7     最小电阻值Rmin: \n",str);
	str1=str2;
	str2.Format("%s%s Ω\n",str1,Draw10(rt.GetResMin(index)));
	str.Format("%s   8     最大电阻值Rmax: \n",str);
	str1=str2;
	str2.Format("%s%s Ω\n",str1,Draw10(rt.GetResMax(index)));
   }//old
  
   else 
   {//==7chengduhongming

	str.Format("%s                    \n",str);
    str2.Format("\n\n\n\n\n");

//	str.Format("%s                    \n",str);
    str1=str2;
	str2.Format("%s%s   \n",str1," ");

	R25=rt.GetRes25(index);//zjun
	

		str.Format("%s   4     25℃电阻值R25: \n",str);
        str1=str2;
		str2.Format("%s%s Ω\n",str1,Draw10(R25));

		str.Format("%s   5     最小电阻值Rmin: \n",str);
	str1=str2;
	str2.Format("%s%s Ω\n",str1,Draw10(rt.GetResMin(index)));
	str.Format("%s   6     最大电阻值Rmax: \n",str);
	str1=str2;
	str2.Format("%s%s Ω\n",str1,Draw10(rt.GetResMax(index)));

   }


    rect2.CopyRect(rect);
	rect2.left+=(long)width*0.7*30;

 if(CPptc==1)
	    pDC->DrawText(str2,rect2,DT_LEFT|DT_EXPANDTABS);
   

 if(CPptc==1)
 {
 //	str.Format("%s   9     电阻最小时对应温度TRmin:        %.1f ℃\n",str,rt.GetTemMin(index));
	str.Format("%s   9     电阻最小时对应温度TRmin:        \n",str);
	str1.Format("\n\n\n\n\n\n\n\n\n\n%.1f ℃\n",rt.GetTemMin(index));
 
	if(rt.GetStartTem0(index)<=25.0)
	{
    	if(rt.GetAnyT(log10(1.5*R25),index)==-100)
		{str.Format("%s   10   1.5倍R25时对应温度TR1.5:  \n",str);
		 str1.Format("%s\n",str1);
		}
        else 
		{
//        	str.Format("%s   10   1.5倍R25时对应温度TR1.5:       %.1f ℃\n",str,rt.GetAnyT(log10(1.5*rt.GetRes25(index)),index));
 //lby    	str.Format("%s   10   1.5倍R25时对应温度TR1.5:         %s  ℃\n",str,Draw10(rt.GetAnyT(log10(1.5*rt.GetRes25(index)),index)));
			str.Format("%s   10   1.5倍R25时对应温度TR1.5:         \n",str);
//            str1.Format("%s  %.1f ℃\n",str1,rt.GetAnyT(log10(1.5*rt.GetRes25(index)),index));
            str2=str1;
			str1.Format("%s%.1f ℃\n",str2,rt.GetAnyT(log10(1.5*rt.GetRes25(index)),index));
		}
        if(rt.GetAnyT(log10(2.0*rt.GetRes25(index)),index)==-100)
		{
			str.Format("%s   11   2.0倍R25时对应温度TR2.0:  \n",str);
    		str1.Format("%s\n",str1);
		}

	    else
//     	    str.Format("%s   11   2.0倍R25时对应温度TR2.0:       %.1f ℃\n",str,rt.GetAnyT(log10(2.0*rt.GetRes25(index)),index));
		{
			str.Format("%s   11   2.0倍R25时对应温度TR2.0:         \n",str);
		    str2=str1;
			str1.Format("%s%.1f ℃\n",str2,rt.GetAnyT(log10(2.0*rt.GetRes25(index)),index));
		}
 
    	if(rt.GetAnyT(log10(3.0*rt.GetRes25(index)),index)==-100)
		{
			str.Format("%s   12   3.0倍R25时对应温度TR3.0:\n",str);     
    		str1.Format("%s\n",str1);
		}
        else
//     	    str.Format("%s   12   3.0倍R25时对应温度TR3.0:       %.1f ℃\n",str,rt.GetAnyT(log10(3.0*rt.GetRes25(index)),index));     
		{
			str.Format("%s   12   3.0倍R25时对应温度TR3.0:         \n",str);     
			str2=str1;
			str1.Format("%s%.1f ℃\n",str2,rt.GetAnyT(log10(3.0*rt.GetRes25(index)),index));     
		}

    	if(rt.GetAnyT(log10(5.0*rt.GetRes25(index)),index)==-100)
	    {
			str.Format("%s   13   5.0倍R25时对应温度TR5.0:   \n",str);
    		str1.Format("%s\n",str1);
		}
    	else
//	        str.Format("%s   13   5.0倍R25时对应温度TR5.0:       %.1f ℃ \n",str,rt.GetAnyT(log10(5.0*rt.GetRes25(index)),index));
	    {
			str.Format("%s   13   5.0倍R25时对应温度TR5.0:          \n",str);
		    str2=str1;
            str1.Format("%s%.1f ℃ \n",str2,rt.GetAnyT(log10(5.0*rt.GetRes25(index)),index));
		}

	    if(rt.GetAnyT(log10(10.0*rt.GetRes25(index)),index)==-100)
        {
			str.Format("%s   14   10.0倍R25时对应温度TR10.0:\n",str);
    		str1.Format("%s\n",str1);
		}
	    else
//            str.Format("%s   14   10.0倍R25时对应温度TR10.0:    %.1f ℃\n",str,rt.GetAnyT(log10(10.0*rt.GetRes25(index)),index));
        {
			str.Format("%s   14   10.0倍R25时对应温度TR10.0:     \n",str);
			str2=str1;
			str1.Format("%s%.1f ℃\n",str2,rt.GetAnyT(log10(10.0*rt.GetRes25(index)),index));
		}

    }
	else   //rt.GetStartTem0(index)>25.0
	{
	if(rt.GetAnyT(log10(1.5*R25),index)==-100)
		{str.Format("%s   10   1.5倍Ro时对应温度TR1.5:  \n",str);
		    str1.Format("%s\n",str1);
		}
        else   
		{                                                              //     rt.GetAnyT(log10(1.5*rt.GetRes25(i)),i)
//			str.Format("%s   10   1.5倍Ro时对应温度TR1.5:         %.1f ℃\n",str,rt.GetAnyT(log10(1.5*rt.GetRes25(index)),index));
			str.Format("%s   10   1.5倍Ro时对应温度TR1.5:         \n",str);
//            str1.Format("%s  %.1f ℃\n",str1,rt.GetAnyT(log10(1.5*rt.GetRes25(index)),index));
            str2=str1;
			str1.Format("%s%.1f ℃\n",str2,rt.GetAnyT(log10(1.5*rt.GetRes25(index)),index));
		}
			//zjun    	str.Format("%s   10   1.5倍R25时对应温度TR1.5:         %s  ℃\n",str,Draw10(rt.GetAnyT(log10(1.5*rt.GetRes25(index)),index)));
	    if(rt.GetAnyT(log10(2.0*rt.GetRes25(index)),index)==-100)
		{ str.Format("%s   11   2.0倍Ro时对应温度TR2.0:  \n",str);
		  str1.Format("%s\n",str1);
		}
	    else
//     	    str.Format("%s   11   2.0倍Ro时对应温度TR2.0:         %.1f ℃\n",str,rt.GetAnyT(log10(2.0*rt.GetRes25(index)),index));
		{
			str.Format("%s   11   2.0倍Ro时对应温度TR2.0:         \n",str);
		    str2=str1;
			str1.Format("%s%.1f ℃\n",str2,rt.GetAnyT(log10(2.0*rt.GetRes25(index)),index));
		}

     	if(rt.GetAnyT(log10(3.0*rt.GetRes25(index)),index)==-100)
		{ str.Format("%s   12   3.0倍Ro时对应温度TR3.0:\n",str);   
		  str1.Format("%s\n",str1);
		}
        else
//     	    str.Format("%s   12   3.0倍Ro时对应温度TR3.0:         %.1f ℃\n",str,rt.GetAnyT(log10(3.0*rt.GetRes25(index)),index));     
		{
			str.Format("%s   12   3.0倍Ro时对应温度TR3.0:         \n",str);     
			str2=str1;
			str1.Format("%s%.1f ℃\n",str2,rt.GetAnyT(log10(3.0*rt.GetRes25(index)),index));     
		}
    	if(rt.GetAnyT(log10(5.0*rt.GetRes25(index)),index)==-100)
		{
			str.Format("%s   13   5.0倍Ro时对应温度TR5.0:   \n",str);
			str1.Format("%s\n",str1);
		}
    	else
//	        str.Format("%s   13   5.0倍Ro时对应温度TR5.0:         %.1f ℃ \n",str,rt.GetAnyT(log10(5.0*rt.GetRes25(index)),index));
	    {
			str.Format("%s   13   5.0倍Ro时对应温度TR5.0:          \n",str);
		    str2=str1;
            str1.Format("%s%.1f ℃ \n",str2,rt.GetAnyT(log10(5.0*rt.GetRes25(index)),index));
		}
	    if(rt.GetAnyT(log10(5.0*rt.GetRes25(index)),index)==-100)
		{
			str.Format("%s   14   10.0倍Ro时对应温度TR10.0:\n",str);
			str1.Format("%s\n",str1);
		}
	    else
//            str.Format("%s   14   10.0倍Ro时对应温度TR10.0:     %.1f ℃\n",str,rt.GetAnyT(log10(10.0*rt.GetRes25(index)),index));
        {
			str.Format("%s   14   10.0倍Ro时对应温度TR10.0:     \n",str);
			str2=str1;
			str1.Format("%s%.1f ℃\n",str2,rt.GetAnyT(log10(10.0*rt.GetRes25(index)),index));
		}
	}
//	str.Format("%s   15   电阻最大时对应温度TRmax:       %.1f ℃\n",str,rt.GetTemMax(index));
	str.Format("%s   15   电阻最大时 对应温度TRmax:       \n",str);
	str2=str1;
	str1.Format("%s%.1f ℃\n",str2,rt.GetTemMax(index));
    if(rt.GetStartTem0(index)>25.0)
//	   str.Format("%s   16   升阻比Rmax/Ro:                     %s\n",str,Draw10(rt.GetResRatio(index)));
	   str.Format("%s   16   升阻比Rmax/Ro:                     \n",str);
	else
//	   str.Format("%s   16   升阻比Rmax/R25:                   %s\n",str,Draw10(rt.GetResRatio(index)));
	   str.Format("%s   16   升阻比Rmax/R25:                     \n",str);
	str2=str1;
	str1.Format("%s%s\n",str2,Draw10(rt.GetResRatio(index)));
//	str.Format("%s   17   测试结束温度:                          %.1f ℃\n",str,rt.GetEndTem(index));
	str.Format("%s   17   测试结束温度:                          \n",str);
	str2=str1;
	str1.Format("%s%.1f ℃\n",str2,rt.GetEndTem(index));
//	rect.top-=(long)(height*3);

	pDC->DrawText(str,rect,DT_LEFT|DT_EXPANDTABS);
	rect1.CopyRect(rect);
	rect2.CopyRect(rect1);
	rect2.left+=(long)width*0.7*35;
	pDC->DrawText(str1,rect2,DT_LEFT|DT_EXPANDTABS);

 } //end of if(CPptc==1)
 else if(CPptc==0)
 {//Ceramic  PTCR

//	str.Format("%s最小阻值:%.2f Ω\n",str,rt.GetResMin(index));
//	str.Format("%s   9     最小阻值对应温度:%.2f ℃\n",str,rt.GetTemMin(index));
	str.Format("%s   9     最小阻值对应温度:\n",str);
    str1=str2;
	str2.Format("%s%.1f ℃\n",str1,  rt.GetTemMin(index));
//	str.Format("%s   10    最大阻值对应温度:%.2f ℃\n",str,rt.GetTemMax(index));
 	str.Format("%s   10   最大阻值对应温度:\n",str);
    str1=str2;
	str2.Format("%s%.1f ℃\n",str1, rt.GetTemMax(index));

//	str.Format("%s   9     电阻最小时对应温度TRmin:        \n",str);
//	str.Format("%s样品名称:%s\n",str,rt.m_rtSave.m_sChannelsName[index]);
//	str.Format("%s测试日期:%s\n",str,rt.m_rtSave.m_sStr[0]);
//	str.Format("%s测试时间:%s\n\n",str,rt.m_rtSave.m_sStr[1]);
//	str.Format("%s   11   室温阻值:%.2f Ω\n",str,rt.GetRes25(index));

    if(rt.GetStartTem0(index)>25.0)
	{
   	    str.Format("%s   11   居里温度(Tc25):\n",str);
		str1=str2;
		str2.Format("%s%.1f ℃\n",str1,rt.m_fTemCur2R25[index]);
//		str2.Format("%s\n",str1);
	}
    else 
	{
   	str.Format("%s   11   居里温度(Tc25):\n",str);
        str1=str2;
//    rt.m_fTemCur2R25[index] = rt.GetAnyT(log10(2*m_fRes25[index]),index);

		str2.Format("%s%.1f ℃\n",str1,rt.m_fTemCur2R25[index]);
	}

/*zjun	str.Format("%s   11   室温阻值:\n",str);
    str1=str2;
	str2.Format("%s%.2f Ω\n",str1,rt.GetRes25(index));
*/
	
	str.Format("%s   12   居里温度(Tc):\n",str);
    str1=str2;
	str2.Format("%s%.1f ℃\n",str1,rt.GetTemCurie(index));

//	str.Format("%s   13   居里阻值:%.2f Ω\n",str,rt.GetResCurie(index));
	str.Format("%s   13   居里阻值:\n",str);
    str1=str2;
	str2.Format("%s%.2f Ω\n",str1,rt.GetResCurie(index));
//	str.Format("%s最小阻值:%.2f Ω\n",str,rt.GetResMin(index));
//	str.Format("%s对应温度:%.2f ℃\n",str,rt.GetTemMin(index));
//	str.Format("%s最大阻值:%s Ω\n",str,Draw10(rt.GetResMax(index)));
//	str.Format("%s对应温度:%.2f ℃\n",str,rt.GetTemMax(index));
//	str.Format("%s   14   温度系数(10/25):%.2f%%\n",str,rt.GetTemCoe10(index));
	str.Format("%s   14   温度系数(10/25):\n",str);
    str1=str2;
	str2.Format("%s%.2f%%\n",str1,rt.GetTemCoe10(index));

//	str.Format("%s   15   温度系数(15/25):%.2f%%\n",str,rt.GetTemCoe25(index));
	str.Format("%s   15   温度系数(15/25):\n",str);
    str1=str2;
	str2.Format("%s%.2f%%\n",str1,rt.GetTemCoe25(index));

//	str.Format("%s   16   温度系数(0/15):%.2f%%\n",str,rt.GetTemCoe50(index));
	str.Format("%s   16   温度系数(0/15):\n",str);
    str1=str2;
	str2.Format("%s%.2f%%\n",str1,rt.GetTemCoe50(index));

//	str.Format("%s   17   居里温区:%.2f ℃\n",str,rt.GetCurieRange(index));
	str.Format("%s   17   居里温区:\n",str);
    str1=str2;
	str2.Format("%s%.1f ℃\n",str1,rt.GetCurieRange(index));

//	str.Format("%s   18   升阻比:\t%s",str,Draw10(rt.GetResRatio(index)));
	str.Format("%s   18   升阻比:\n",str);
    str1=str2;
	str2.Format("%s%s\n",str1,Draw10(rt.GetResRatio(index)));
    str.Format("%s   19   Rmin/R25:",str);
    if(rt.GetStartTem0(index)>25.0)
    {
		str1=str2;
		str2.Format("%s%s\n",str1,"1");
	}
	else
	{
    	str1=str2;
       str2.Format("%s%s\n",str1, Draw10(rt.GetResMin(index)/R25));
	}

	pDC->DrawText(str,rect,DT_LEFT|DT_EXPANDTABS);
    pDC->DrawText(str2,rect2,DT_LEFT|DT_EXPANDTABS); //8-20

 }
 else 
 {//Ceramic  PTCR 个性化

//	str.Format("%s最小阻值:%.2f Ω\n",str,rt.GetResMin(index));
//	str.Format("%s   9     最小阻值对应温度:%.2f ℃\n",str,rt.GetTemMin(index));
	str.Format("%s   7     最小阻值对应温度:\n",str);
    str1=str2;
	str2.Format("%s%.1f ℃\n",str1,  rt.GetTemMin(index));
//	str.Format("%s   10    最大阻值对应温度:%.2f ℃\n",str,rt.GetTemMax(index));
 	str.Format("%s   8     最大阻值对应温度:\n",str);
    str1=str2;
	str2.Format("%s%.1f ℃\n",str1, rt.GetTemMax(index));

//	str.Format("%s   9     电阻最小时对应温度TRmin:        \n",str);
//	str.Format("%s样品名称:%s\n",str,rt.m_rtSave.m_sChannelsName[index]);
//	str.Format("%s测试日期:%s\n",str,rt.m_rtSave.m_sStr[0]);
//	str.Format("%s测试时间:%s\n\n",str,rt.m_rtSave.m_sStr[1]);
//	str.Format("%s   11   室温阻值:%.2f Ω\n",str,rt.GetRes25(index));

    if(rt.GetStartTem0(index)>25.0)
	{
   	    str.Format("%s   9     居里温度(Tc25):\n",str);
		str1=str2;
		str2.Format("%s%.1f ℃\n",str1,rt.m_fTemCur2R25[index]);
//		str2.Format("%s\n",str1);
	}
    else 
	{
   	str.Format("%s   9     居里温度(Tc25):\n",str);
        str1=str2;
//    rt.m_fTemCur2R25[index] = rt.GetAnyT(log10(2*m_fRes25[index]),index);

		str2.Format("%s%.1f ℃\n",str1,rt.m_fTemCur2R25[index]);
	}

/*lby	str.Format("%s   11   室温阻值:\n",str);
    str1=str2;
	str2.Format("%s%.2f Ω\n",str1,rt.GetRes25(index));
*/
	
	str.Format("%s   10   居里温度(Tc):\n",str);
    str1=str2;
	str2.Format("%s%.1f ℃\n",str1,rt.GetTemCurie(index));

//	str.Format("%s   13   居里阻值:%.2f Ω\n",str,rt.GetResCurie(index));
	str.Format("%s   11   居里阻值:\n",str);
    str1=str2;
	str2.Format("%s%.2f Ω\n",str1,rt.GetResCurie(index));

	
	str.Format("%s   12   温度系数(10/25):\n",str);
    str1=str2;
	str2.Format("%s%.2f%%\n",str1,rt.GetTemCoe10(index));

//	str.Format("%s   13   温度系数(15/25):%.2f%%\n",str,rt.GetTemCoe25(index));
	str.Format("%s   13   温度系数(15/25):\n",str);
    str1=str2;
	str2.Format("%s%.2f%%\n",str1,rt.GetTemCoe25(index));

//	str.Format("%s   16   温度系数(0/15):%.2f%%\n",str,rt.GetTemCoe50(index));

	str.Format("%s   14   温度系数(0/15):\n",str);
    str1=str2;
	str2.Format("%s%.2f%%\n",str1,rt.GetTemCoe50(index));

//	str.Format("%s   17   居里温区:%.2f ℃\n",str,rt.GetCurieRange(index));
	str.Format("%s   15   居里温区:\n",str);
    str1=str2;
	str2.Format("%s%.1f ℃\n",str1,rt.GetCurieRange(index));

//	str.Format("%s   18   升阻比:\t%s",str,Draw10(rt.GetResRatio(index)));
	str.Format("%s   16   升阻比:\n",str);
    str1=str2;
	str2.Format("%s%s\n",str1,Draw10(rt.GetResRatio(index)));
 /*   str.Format("%s   19   Rmin/R25:",str);
    if(rt.GetStartTem0(index)>25.0)
    {
		str1=str2;
		str2.Format("%s%s\n",str1,"1");
	}
	else
	{
    	str1=str2;
       str2.Format("%s%s\n",str1, Draw10(rt.GetResMin(index)/R25));
	}
*/
	pDC->DrawText(str,rect,DT_LEFT|DT_EXPANDTABS);
    pDC->DrawText(str2,rect2,DT_LEFT|DT_EXPANDTABS); //8-20

 }


	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
	pOldFont->DeleteObject();
//	Pen.DeleteObject();  
} 

//
//	绘制强制测试RT参数
//
void CDraw::DrawRTMeaRef(CDC *pDC, CRT rt, CRect rect, int index)
{
	CFont Font;
	CFont* pOldFont;
	CPen Pen;
	double width,height;
	CString str("",2000);
    
	CString  strdisp[20];
		
	CRect rect1,rect2;
//	int i,j,k,l;
	int i;
	int lby;

lby=0;
	CPoint pnt;
  int OldDC;

	OldDC=pDC->SaveDC();
	
	height=fabs(rect.Height()/10);	
	Font.CreateFont((long)height,(long)(height*0.5),0,0,700,0,0,0,0,0,0,0,0,"宋体");
	pOldFont=pDC->SelectObject(&Font);

	str="PTC电阻温度特性曲线";
	pDC->DrawText(str,rect,DT_TOP|DT_CENTER);

	rect.top-=(long)(height*1.2);
	str="";

	height=fabs(rect.Height()/20.0);
	width=fabs(rect.Width()/80.0);
	
	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
	Font.CreateFont((long)height,(long)width,0,0,400,0,0,0,0,0,0,0,0,"宋体");
	pDC->SelectObject(&Font);

	CTime dt=CTime::GetCurrentTime();
    CString m_sStr[2];
	strdisp[lby++].Format("样品名称:%s\n",rt.m_rtSave.m_sChannelsName[index]);
	m_sStr[0] = dt.Format("%Y-%m-%d"); 
    m_sStr[1]=dt.Format("%H:%M:%S-A"); 
	strdisp[lby++].Format("测试日期:%s\n",m_sStr[0]);
	strdisp[lby++].Format("开始时间:%s\n",rt.m_rtSave.m_sStr[1]);
	strdisp[lby++].Format("测试时间:%s\n\n",m_sStr[1]);
	strdisp[lby++].Format(" 升温方式: \n");
    strdisp[lby++].Format("  To-%3i℃ 间隔 %2i ℃\n  %3i℃-%3i℃ 间隔 %2i ℃\n",rt.m_rtSave.MaxT[0],rt.m_rtSave.Step[0],rt.m_rtSave.MaxT[0],rt.m_rtSave.MaxT[1],rt.m_rtSave.Step[1]);
	if(rt.m_rtSave.soaking[0]==0) 
	{
		strdisp[lby++].Format("  分段匀速升温\n\n");
	}
    else 
	{
		strdisp[lby++].Format("  保温时间%02i 分钟\n\n",rt.m_rtSave.soaking[0]);
	}
 
	
	if(rt.ZWX==0)
	  if(rt.client!=6)	strdisp[lby++].Format(" SR 温度: %6.1f ℃\n",rt.m_tSr253);
	  else {
		  strdisp[lby++].Format(" PV1 温度: %6.1f ℃\n",rt.m_tSr253);
		  strdisp[lby++].Format(" PV2 温度: %6.1f ℃\n",rt.m_tPt100_1);
		  strdisp[lby++].Format(" PV3 温度: %6.1f ℃\n",rt.m_tPt100_2);
		  strdisp[lby++].Format(" PV  均温: %6.1f ℃\n",rt.m_tPt100_3);
	  }

	else strdisp[lby++].Format(" F45 温度:%6.1f ℃\n",rt.m_tPt100);
	strdisp[lby++].Format(" 设定温度:%6.1f ℃\n",rt.m_SV);
if(rt.ZWX==1)	strdisp[lby++].Format(" 占空比 :  %i  \n",rt.wvn);

if((rt.m_Raising==1)||(rt.m_Raising==2)) 
{
			if(rt.Cooling==0)strdisp[lby++].Format(" 测量状态:  升温  %i \n",rt.m_Raising);
		else strdisp[lby++].Format(" 测量状态:  降温  %i \n",rt.m_Raising);

//strdisp[lby++].Format(" 测量状态:  升温  %i \n",rt.m_Raising);
}
else if(rt.m_Raising==3)	strdisp[lby++].Format(" 测量状态: 保温  %i\n",rt.m_rtSave.Soaking);
else if((rt.m_Raising==0)||(rt.m_Raising==7))	strdisp[lby++].Format(" 测量状态: 测阻 %i \n",rt.m_Raising);

	strdisp[lby++].Format("\n前测试温度 :%6.1f ℃\n",rt.m_Pt);
	for(i=0;i<20;i++)
          str+=strdisp[i];
  pDC->DrawText(str,CRect(rect.left+rect.Width()/100,rect.top,rect.right,rect.bottom),DT_LEFT|DT_EXPANDTABS);

  
    pDC->RestoreDC(OldDC);
	pDC->SelectObject(pOldFont);
	Font.DeleteObject();
	pOldFont->DeleteObject();
	Pen.DeleteObject();

}


