/*
**	FILENAME			Login.h
**
**	PURPOSE				此类可唤起“登录”对话框，点击“确认”键
**						检查账号的存在以及密码是否正确，根据结果
**						返回最终登陆状态
*/

#if !defined(AFX_LOGIN_H__A33E3680_A4A9_11D6_822C_5254AB1E742B__INCLUDED_)
#define AFX_LOGIN_H__A33E3680_A4A9_11D6_822C_5254AB1E742B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Login.h : 头文件
//

/////////////////////////////////////////////////////////////////////////////
// CLogin对话框

class CLogin : public CDialog
{
// 构造
public:
	int m_count;
	bool m_pass;

	CLogin(CWnd* pParent = NULL);   // 标准构造函数

// 对话框数据
	//{{AFX_DATA(CLogin)
	enum { IDD = IDD_LOGIN };
	CString	m_name;
	CString	m_password;
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// 实现
protected:

	// 生成的消息处理函数
	//{{AFX_MSG(CLogin)
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIN_H__A33E3680_A4A9_11D6_822C_5254AB1E742B__INCLUDED_)
