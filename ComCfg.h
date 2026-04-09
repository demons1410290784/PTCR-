/*
**	FILENAME			ComCfg.h
**
**	PURPOSE				此类可在进行万用表、温控表设置时，
**						对串行通讯设置、事件响应、发送缓冲
**						区大小等参数进行改变
*/

#if !defined(AFX_CMDCFG_H__311AD621_D1F6_11D5_A239_0010DC09E70D__INCLUDED_)
#define AFX_CMDCFG_H__311AD621_D1F6_11D5_A239_0010DC09E70D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 //CmdCfg.h : 头文件
//
#include "PtcrDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CCmdCfg 对话框

/////////////////////////////////////////////////////////////////////////////
// CComCfg 对话框

class CComCfg : public CDialog
{
// 构造
public:
	CPtcrDoc *m_pDoc;
	CComCfg(CPtcrDoc *pDoc,CWnd* pParent = NULL);   // 标准构造函数

// 对话框数据
	//{{AFX_DATA(CComCfg)
	enum { IDD = IDD_COMSETTINGS };
	int		m_BaudRate;
	BOOL	m_CommRingDetected;
	BOOL	m_CommBreakDetected;
	BOOL	m_CommRxchar;
	BOOL	m_CommCTSDetected;
	BOOL	m_CommDSRDetected;
	BOOL	m_CommERRDetected;
	BOOL	m_CommRLSDDetected;
	BOOL	m_CommTXEmpty;
	BOOL	m_CommRxcharFlag;
	int		m_DataBits;
	int		m_Parity;
	CString	m_strSendBuffer;
	int		m_SerialPort;
	int		m_StopBits;
	CString m_F45Result;//modiefied on 1/18/2000
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComCfg)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// 实现
protected:

	// 生成的消息映射函数
	//{{AFX_MSG(CComCfg)
	virtual void OnOK();
	afx_msg void OnFileOpen();
	afx_msg void OnSelchangeMultiMeter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CCmdCfg 对话框

class CCmdCfg : public CDialog
{
// 构造
public:
	CCmdCfg(CWnd* pParent = NULL);   // 标准构造函数

// 对话框数据
	//{{AFX_DATA(CCmdCfg)
	enum { IDD = IDD_COMSETTINGS };
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmdCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// 实现
protected:

	// 生成的消息映射函数
	//{{AFX_MSG(CCmdCfg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMDCFG_H__311AD621_D1F6_11D5_A239_0010DC09E70D__INCLUDED_)
