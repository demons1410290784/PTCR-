/*
**	FILENAME			SetSingleUser.h
**
**	PURPOSE				此类可用于注册新的账户，信息包含用户名称以及用户密码
*/

#if !defined(AFX_SETSINGLEUSER_H__C2612C83_A4C1_11D6_822C_5254AB1E742B__INCLUDED_)
#define AFX_SETSINGLEUSER_H__C2612C83_A4C1_11D6_822C_5254AB1E742B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetSingleUser.h : 头文件
//

/////////////////////////////////////////////////////////////////////////////
// CSetSingleUser对话框

class CSetSingleUser : public CDialog
{
// 构造
public:
	CSetSingleUser(CWnd* pParent = NULL);   // 标准构造函数

// 对话框数据
	//{{AFX_DATA(CSetSingleUser)
	enum { IDD = IDD_SETSINGLEUSER };
	CString	m_Name;
	CString	m_Password;
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetSingleUser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// 实现
protected:

	// 生成的消息响应函数
	//{{AFX_MSG(CSetSingleUser)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETSINGLEUSER_H__C2612C83_A4C1_11D6_822C_5254AB1E742B__INCLUDED_)
