/*
**	FILENAME			SelRTRange.h
**
**	PURPOSE				此类可用于对曲线范围进行设置，可在对话框内
**						对曲线阻值的上下限、温度的上下限等参数进行
**						修改，还可以更改温度间隔与电阻的坐标形式
*/

#if !defined(AFX_SELRTRANGE_H__F72C5FC1_8B85_11D6_85E9_00105CB716C8__INCLUDED_)
#define AFX_SELRTRANGE_H__F72C5FC1_8B85_11D6_85E9_00105CB716C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelRTRange.h : 头文件
//

/////////////////////////////////////////////////////////////////////////////
// CSelRTRange对话框

class CSelRTRange : public CDialog
{
// 构造
public:
	afx_msg UINT OnChioce(UINT nID);
	CSelRTRange(CWnd* pParent = NULL);   //标准构造函数

// 对话框数据
	//{{AFX_DATA(CSelRTRange)
	enum { IDD = IDD_RTSET };
	UINT	m_tempstep;
	CString	m_minres;
	CString	m_maxtemp;
	CString	m_maxres;
	CString	m_mintemp;
	BOOL	m_showdot;
	BOOL	m_OnlyMeaDot;
	BOOL	m_SelCoorKind;
	CString	m_EndStopHeat;
	BOOL	m_OutRect;
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelRTRange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelRTRange)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELRTRANGE_H__F72C5FC1_8B85_11D6_85E9_00105CB716C8__INCLUDED_)
