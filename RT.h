/*
**	FILENAME			RT.h
**
**	PURPOSE				此类可用于处理测试系统得到的温度、阻值等数据。
**						通过调用公式计算实验目标需要的PTCR重要参数，包
**						括温度系数、居里点等
*/

#if !defined(AFX_RT_H__F16F4BD2_EE34_11D4_BB0A_A4F4FDB2E4C0__INCLUDED_)
#define AFX_RT_H__F16F4BD2_EE34_11D4_BB0A_A4F4FDB2E4C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "rtsave.h"
#include "math.h"

class CRT  
{
public:
	int m_TempSoakingCondition;
	int Cooling;
	int m_roomtemp_dot;
	float m_roomtemp;
	bool m_DatOrRtFile; //0-Dat file 1-RT file
	int m_DataNum;
	bool m_DrawDotFlag;
	float m_TempResVal;
	int client;// client=0 ZWX-C; client=1 keter;client=2 dongguan weiqing;
	int m_Number; //Number of real Channel
	int ZWX; // 0 ZWX-B , 1 ZWX-C
	float GetAnyT(float r,int index);
	float GetEndTem(int i);
	float GetStartRes0(int i);
	float GetStartTem0(int i);
	bool isRunning;
	bool isChangeRange;
	bool ReadZeroResi;
	int ReadZero();
	int WriteZero();
	float m_Zeroresi[NMBOFSPL];
	int m_Raising;//=1 Raising Temp, =2 Maintain Temp, =0 Read Resistance
	int StartDot;
	int EndDot;
	float m_SV;
	float m_PV;
	int GetEnd(int index);
	int GetStart(int index);
	float GetY(int i);
	float GetX(int i);
	int GetCount(int index);
	float GetAnyR(float t,int index);
	float GetT(int index,float r);
	float GetR(int i,float t);
	float GetAlfa(int index,float T0,float T1);
	float GetTemCur(int i);
	void Calculation(int index);
	float GetCurieRange(int i);
	float GetTemCoe50(int i);
	float GetTemCoe25(int i);
	float GetTemCoe10(int i);
	float GetTemMax(int i);
	float GetTemMin(int i);
	float GetTemCurie(int i);
	float GetResRatio(int i);
	float GetResMax(int i);
	float GetResCurie(int i);
	float GetResMin(int i);
	float GetRes25(int i);
 
	float GetSpecialR(int i, float t,int index);

	void Initialization();
	CRT();
	virtual ~CRT();
	CRTSave m_rtSave;
    float m_fResi[NMBOFSPL+3],m_tPt100,m_tSr253;//m_tPt100 roomTemperature

    float m_tPt100_1;
    float m_tPt100_2;
    float m_tPt100_3;
	float m_fTemCur2R25[NMBOFSPL];
	int wvn;
    float m_Pt;
	int m_iEndDot[NMBOFSPL],m_iStartDot[NMBOFSPL];

private:
	float m_iEndTem[NMBOFSPL];
//oyj
	float m_iStartRes0[NMBOFSPL];
	float m_iStartTem0[NMBOFSPL];
//oyj	
	float m_fRes25[NMBOFSPL],m_fTemCurie[NMBOFSPL],m_fResCurie[NMBOFSPL],
		  m_fResMin[NMBOFSPL],m_fResMax[NMBOFSPL],m_fTemMin[NMBOFSPL],m_fTemMax[NMBOFSPL],
		  m_fTemCoe10[NMBOFSPL],m_fCurieRange[NMBOFSPL],m_fResRatio[NMBOFSPL],
		  m_fTemCoe25[NMBOFSPL],m_fTemCoe50[NMBOFSPL],m_fTemCur[NMBOFSPL];	
	float xc[MAXOFSPL],yc[MAXOFSPL];
	int m_iCount[NMBOFSPL];
//	int m_iEndDot[NMBOFSPL],m_iStartDot[NMBOFSPL];
};

#endif // !defined(AFX_RT_H__F16F4BD2_EE34_11D4_BB0A_A4F4FDB2E4C0__INCLUDED_)




