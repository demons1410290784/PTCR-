/*
**	FILENAME			ManCmd1.h
**
**	PURPOSE				此类可用于将“命令”文本框内的命令字符串
**						按相应的通讯协议修改后传输入万用表或温控
**						表，若仪表有结果返回则将结果字符串显示在
**						相应文本框内
*/

#if !defined(AFX_MANCMD1_H__446832CC_D225_11D5_A239_0010DC09E70D__INCLUDED_)
#define AFX_MANCMD1_H__446832CC_D225_11D5_A239_0010DC09E70D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManCmd1.h : 头文件
//

#include "PtcrDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CManCmd对话框

class CManCmd : public CDialog
{
// 构造
public:
	CPtcrDoc *m_pDoc;
	CManCmd(CPtcrDoc *pDoc,CWnd* pParent = NULL);   //标准构造函数

// 对话框数据
	//{{AFX_DATA(CManCmd)
	enum { IDD = IDD_MANUALCMD };
	CString	m_Cmd;
	CString	m_Result;
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManCmd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// 实现
protected:

	// Generated message map functions
	//{{AFX_MSG(CManCmd)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANCMD1_H__446832CC_D225_11D5_A239_0010DC09E70D__INCLUDED_)
