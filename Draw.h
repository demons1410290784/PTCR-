/*
**	FILENAME			Draw.h
**
**	PURPOSE				此类用于绘制窗口内的形状与文字，可以通过显示设置
**						与曲线设置的改变，修改曲线与数据为相应的输出格式
*/

#if !defined(AFX_DRAW_H__F16F4BD4_EE34_11D4_BB0A_A4F4FDB2E4C0__INCLUDED_)
#define AFX_DRAW_H__F16F4BD4_EE34_11D4_BB0A_A4F4FDB2E4C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#define  QXResRange  9
#include "ptcrdoc.h"
#include "Gridctrl.h"
class CDraw  
{
public:
	void PrintRef(CGridCtrl& grid,CDC *pDC,CRect rect,CRT rt,int,int,int,int);
	CString Draw10(float x);
	float GetAny(int index,int i,int j,float t);
	float GetR(int i,float t);
	void DrawRef(CGridCtrl& grid,CRT rt, int CPptc);
	void DrawData(CGridCtrl& grid,CRT rt);
	void DrawDataRT(CGridCtrl& grid,CRT rt);//lby
	void PrintMulText(CDC *pDC,CRT rt,CRect rect,int *index);
	void DrawHor(CDC *pDC,CPoint pnt);
	void DrawRect(CDC *pDC,CPoint pnt);
	void DrawCross(CDC *pDC,CPoint pnt);
	void DrawCircle(CDC *pDC,CPoint pnt);
	void PrintText(CDC *pDC,CRT rt,CRect rct,int index,int style);

    void DrawPolymerRef(CDC *pDC, CRT rt, CRect rect, int index, CRect rect1 ,int CPptc,int m_client);
	void DrawMultiCurves(CDC *pDC,CRT rt,CRect rect,int *index,int tempstep,UINT maxtemp,CString minres,CString maxres,int mintemp,bool showdot,bool Only_MeaDot);
    void DrawCoordinate(CDC *pDC, CRT rt, CRect rect, int *index,int tempstep,UINT maxtemp,CString minres,CString maxres,int mintemp,bool showdot,bool Only_MeaDot);
	void DrawCurve(CDC *pDC,CRT rt,CRect rect,int index,int tempstep,UINT maxtemp,CString minres,CString maxres,int mintemp,bool showdot,bool Only_MeaDot,int Sel_Coor_Kind,bool m_outrect);
    void DrawRTMea(CDC *pDC,CRT rt,CRect rect,int index);
    void DrawRTMeaRef(CDC *pDC,CRT rt,CRect rect,int index);
//	构造与析构	
	CDraw();
	virtual ~CDraw();

private:
	float xc[MAXOFSPL],yc[MAXOFSPL];
	COLORREF pencol[MULNMBOFSPL];
};

#endif // !defined(AFX_DRAW_H__F16F4BD4_EE34_11D4_BB0A_A4F4FDB2E4C0__INCLUDED_)
