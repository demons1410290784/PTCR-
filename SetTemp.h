/*
**	FILENAME			SetTemp.h
**
**	PURPOSE				此类可用于设置升温方式，设置内容包含两段数据最高
**						温度、温度间隔、保温时间、升温速度，以及升温方式
**						和保温时间等
*/

#if !defined(AFX_SETTEMP_H__CBE244E0_929E_11D6_822C_5254AB1E742B__INCLUDED_)
#define AFX_SETTEMP_H__CBE244E0_929E_11D6_822C_5254AB1E742B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetTemp.h : 头文件e
//
#include "PTCRDOC.h"
/////////////////////////////////////////////////////////////////////////////
// CSetTemp对话框

class CSetTemp : public CDialog
{
// 构造
public:
	CPtcrDoc *m_pDoc;
	FILE  *stream;
	CString filename;
	int select ;  // 1 is rise temp ,2 is soak temp;
/*	CString m_MaxT1_rise,m_MaxT2_rise,m_TempRamp1_rise,m_TempRamp2_rise;
	CString m_TempStep1_rise,m_TempStep2_rise,m_TempTime1_rise,m_TempTime2_rise;
    CString m_MaxT1_save,m_MaxT2_save,m_TempRamp1_save,m_TempRamp2_save;
    CString m_TempStep1_save,m_TempStep2_save,m_TempTime1_save,m_TempTime2_save;
lby*/

	CSetTemp(CPtcrDoc *pDoc, CWnd* pParent = NULL);   // 标准构造函数
   void UpData();
	virtual void OpenNptem();

// 对话框数据 
	//{{AFX_DATA(CSetTemp)
	enum { IDD = IDD_SETTemp };
	CString	m_MaxT1;
	CString	m_MaxT2;
	CString	m_TempRamp1;
	CString	m_TempRamp2;
	CString	m_TempStep1;
	CString	m_TempStep2;
	CString	m_TempTime2;
	CString	m_MinTemp;
	CString	m_RoomTemp;
	CString	m_TempTime0;
	float	m_tempvias;
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetTemp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CString m_MaxT1_rise,m_MaxT2_rise,m_TempRamp1_rise,m_TempRamp2_rise;
	CString m_TempStep1_rise,m_TempStep2_rise,m_TempTime1_rise,m_TempTime2_rise;
    CString m_MaxT1_save,m_MaxT2_save,m_TempRamp1_save,m_TempRamp2_save;
    CString m_TempStep1_save,m_TempStep2_save,m_TempTime2_save;
  //	CString str("",2000);
    CString m_TempTime1_save;
	// Generated message map functions
	//{{AFX_MSG(CSetTemp)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	//}}AFX_MSG
	afx_msg void OnChioce(UINT nID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTEMP_H__CBE244E0_929E_11D6_822C_5254AB1E742B__INCLUDED_)
