/*
**	FILENAME			RTSave.cpp
**
**	PURPOSE				此类可用于对阻值、温度等数据进行读写
*/

#include "stdafx.h"
#include "Ptcr.h"
#include "RTSave.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 构造/析构
//////////////////////////////////////////////////////////////////////

//
//	构造函数：初始化参数
//
CRTSave::CRTSave()
{
	Initialization();
	m_TIME=1;//0 linear heating;1=0 step heating
	MaxT[0]=100;
	MaxT[1]=200;
	MaxT[2]=250;
    soaking[0]=3;
    soaking[1]=3;
	soaking[2]=3;
	Step[0]=10;
	Step[1]=3;
	Step[2]=10;
    Ramp[0]=1.0;
    Ramp[1]=0.8;
    Ramp[2]=1.0;
	m_MaxTemp=MaxT[1];
//lby following 
	m_SpecialR=1e8; //特殊阻值
    m_SetTemp=FALSE;  //设置温度段
    m_CheckZero=FALSE;  //通道电阻检测

}

//
//	析构函数
//
CRTSave::~CRTSave()
{

}

//
//	读取i通道、测试点j温度
//
float CRTSave::GetT(int i, int j)
{
	return m_fTem[i][j];
}

//
//	将温度tem加载到i通道、测试点j上
//
void CRTSave::LoadT(int i, int j,float tem)
{
	m_fTem[i][j]=tem;
}

//
//	加载步长为i
//
void CRTSave::LoadStep(short int i)
{
	m_iStep=i;
}

//
//	读取步长
//
short int CRTSave::GetStep()
{
	return m_iStep;
}

//
//	初始化函数
//
void CRTSave::Initialization()
{
	int i,j;

	for(i=0;i<NMBOFSPL;i++)
	{
		CString str;
		str.Format("%d",i+1);
		m_bChannels[i]=FALSE;	//全通道设置为未启用

		strcpy(m_sChannelsName[i],str);	//全通道样品名称为空
		for(j=0;j<MAXOFSPL;j++)
		{
			m_fPtc[i][j]=1.0;	//全电阻置1
			m_fTem[i][j]=0;		//全温度置0
		}
	}

	m_iStep=10;

	for(i=0;i<2;i++)
		strcpy(m_sStr[i],"");


}


