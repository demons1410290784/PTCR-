/*
**	FILENAME			RTSave.h
**
**	PURPOSE				此类可用于对阻值、温度等数据进行读写
*/

#if !defined(AFX_RTSAVE_H__F16F4BD0_EE34_11D4_BB0A_A4F4FDB2E4C0__INCLUDED_)
#define AFX_RTSAVE_H__F16F4BD0_EE34_11D4_BB0A_A4F4FDB2E4C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MULNMBOFSPL 30 //8-24 oyj 画多曲线数量
#define NMBOFSPL 30 /*SAMPLE NUMBER*/
#define MAXOFSPL 200 /*SAMPLE TEMPERATURE NUMBER*/

class CRTSave  
{
public:
	void Initialization();
	short int GetStep();
	void LoadStep(short int i);
	void LoadT(int i,int j,float tem=0);
	float GetT(int i,int j);
	CRTSave();
	virtual ~CRTSave();
//lby//private:	
public:
	bool m_CheckZero;
	bool m_SetTemp;
	float m_SpecialR;//lby

	CTime m_starttime;//开始时间
	CTime m_endtime;//结束时间
	char endTime[2][12];//结束时间

	    int soaking[3];////设定保温时间
	    int MaxT[3];//中间设定温度//设定温度间隔
	    short int Step[3];//设定温度间隔
	    float Ramp[3];//设定温度速率

	int m_MaxTemp1;//中间设定温度
	int Soaking;//设定保温时间

	float m_MinTemp;//最低设定温度

	int m_MaxTemp;//最高设定温度
	short int m_STEP;//设定温度间隔
	int m_TIME;//设定保温时间

 	float m_fPtc[NMBOFSPL][MAXOFSPL];//	样品阻值
    float m_fTem[NMBOFSPL][MAXOFSPL];//测试温度
    short int m_iStep;//测试次数
    char m_sStr[2][15];//测试时间、日期
	BOOL m_bChannels[NMBOFSPL+1];
	char m_sChannelsName[NMBOFSPL+1][15];
private:

};

#endif // !defined(AFX_RTSAVE_H__F16F4BD0_EE34_11D4_BB0A_A4F4FDB2E4C0__INCLUDED_)
