/*
**	FILENAME			PtcrView.h
**
**	PURPOSE				此类可用于主窗口的框架相关操作，包含菜单栏内
**						各个选项的功能与操作，此外还包含数据、曲线等
**						的绘制方式
*/

#include "SelPrintData.h"

#if !defined(AFX_PTCRVIEW_H__10310810_5067_11D5_B28F_5254AB329367__INCLUDED_)
#define AFX_PTCRVIEW_H__10310810_5067_11D5_B28F_5254AB329367__INCLUDED_
#include "draw.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPtcrView : public CView
{
protected: // create from serialization only
	CPtcrView();
	DECLARE_DYNCREATE(CPtcrView)

// 属性
public:
	CPtcrDoc* GetDocument();
	
    SelPrintData printdata;

	void OnPlot(int i);
	void OnUpdatePlot(int i,CCmdUI* pUI);
    bool SetSr253Exec();
    void ReadResiAll(int j); 
	void DetectCom(); 
    void JudgeTempStage(int j);
    void JudgeTempStage_ZWXB(int j); 
    void JudgeTempStage_ZWXC(int j); 
    void JudgeTempStage_ZWXD(int j); 
    void SetTemp(int j);
    void SetTemp_ZWXB(int j); 
    void SetTemp_ZWXC(int j); 
    void SetTemp_ZWXD(int j); 

    bool SetSr253Temp(int Sv, float temp);
	float m_PV,m_SV,m_Resistance;
    int m_SvNumber;

	CString	m_Pt100PV;
	CString	m_Sr253SV;
	CString	m_Sr253PV;
	int m_printstyle;  //1:原始记录 2：温度取整后记录;0 不打印

private:
	BOOL m_Only_MeaDot;
	BOOL m_show_dot;
	int m_Sel_Coor_Kind;
	bool m_OutterRect;

	CString m_max_res;
	CString m_min_res;
	int m_min_temp;
	UINT m_temp_step;
	CRect m_rectRegion;
	CDraw m_draw;
	int  m_uFlag;//1->single;2->mult;3->data;4->ref;
	BOOL  m_bButton;//true->menu is selected;
	BOOL  m_bCtrlCreate,m_bClickMenu[NMBOFSPL];
//	int	  m_iMulIndex[5];		
	int	  m_iMulIndex[MULNMBOFSPL];		
	CGridCtrl m_gCtrl;
// 操作
public:

// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPtcrView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
//	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// 实现
public:
	bool DiaDataCheck;
	void CalculateStemp(float tt, int start);
	int m_max_temp;
	
	void UpdateDT( void );
	void OnWnd();
	void OnUpdateWnd(CCmdUI* pUI,int i);
	void Sorting();
//lby 	afx_msg bool OnCmdStop();

	virtual ~CPtcrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息响应函数
protected:
	//{{AFX_MSG(CPtcrView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPlot0();
	afx_msg void OnPlot1();
	afx_msg void OnPlot2();
	afx_msg void OnPlot3();
	afx_msg void OnPlot4();
	afx_msg void OnPlot5();
	afx_msg void OnPlot6();
	afx_msg void OnPlot7();
	afx_msg void OnPlot8();
	afx_msg void OnPlot9();
	afx_msg void OnPlot10();
	afx_msg void OnPlot11();
	afx_msg void OnPlot12();
	afx_msg void OnPlot13();
	afx_msg void OnPlot14();
	afx_msg void OnPlot15();
	afx_msg void OnPlot16();
	afx_msg void OnPlot17();
	afx_msg void OnPlot18();
	afx_msg void OnPlot19();
	afx_msg void OnPlot20();
	afx_msg void OnPlot21();
	afx_msg void OnPlot22();
	afx_msg void OnPlot23();
	afx_msg void OnPlot24();
	afx_msg void OnPlot25();
	afx_msg void OnPlot26();
	afx_msg void OnPlot27();
	afx_msg void OnPlot28();
	afx_msg void OnPlot29();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnWndData();
	afx_msg void OnWndMulti();
	afx_msg void OnWndReference();
	afx_msg void OnWndSingle();
	afx_msg void OnUpdatePlot0(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot1(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot10(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot11(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot12(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot13(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot14(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot15(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot16(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot17(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot18(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot19(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot2(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot20(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot21(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot22(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot23(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot24(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot25(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot26(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot27(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot28(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot29(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot3(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot4(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot5(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot6(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot7(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot8(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlot9(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWndData(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWndMulti(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWndReference(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWndSingle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnSerialportF45settings();
	afx_msg void OnManualCmd();
	afx_msg void OnSerialportSettings();
	afx_msg void OnCmdGo();
	afx_msg void OnChanSet();
	afx_msg void OnSr253Cmd();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnManMea();
	afx_msg void SetRTRange();
	afx_msg void OnUpdateRtsetRange(CCmdUI* pCmdUI);
	afx_msg void OnGetAnyres();
	afx_msg void OnUpdateGetAnyres(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDigitControllerSettings(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSr253Cmd(CCmdUI* pCmdUI);
	afx_msg void OnSetTempStage();
	afx_msg void OnCeramicPTC();
	afx_msg void OnUpdateCeramicPTC(CCmdUI* pCmdUI);
	afx_msg void OnPolymerPTC();
	afx_msg void OnUpdatePolymerPTC(CCmdUI* pCmdUI);
	afx_msg void OnToolConbind();
	afx_msg void OnOptimize();
	afx_msg void OnUpdateOptimize(CCmdUI* pCmdUI);
	afx_msg void OnMenuprintdata();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg bool OnCmdStop();
	afx_msg void OnUpdateManualCmd(CCmdUI* pCmdUI);
	afx_msg void OnPensonnelCurve();
	afx_msg void OnUpdatePensonnelCurve(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PtcrView.cpp
inline CPtcrDoc* CPtcrView::GetDocument()
   { return (CPtcrDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTCRVIEW_H__10310810_5067_11D5_B28F_5254AB329367__INCLUDED_)
