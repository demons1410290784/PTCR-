/*
**	FILENAME			SETUSER.h
**
**	PURPOSE				此类可用于进行用户设置，仅在拥有相关权限
**						的用户登录后才可使用此功能。“用户设置”
**						对话框可以浏览已经注册的账户信息，并可以
**						新建或删除账户数据
*/

#if !defined(AFX_SETUSER_H__C2612C82_A4C1_11D6_822C_5254AB1E742B__INCLUDED_)
#define AFX_SETUSER_H__C2612C82_A4C1_11D6_822C_5254AB1E742B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SETUSER.h : 头文件
//

/////////////////////////////////////////////////////////////////////////////
// CSETUSER对话框

class CSETUSER : public CDialog
{
// 构造
public:
	CSETUSER(CWnd* pParent = NULL);   //标准构造函数

// 对话框数据
	//{{AFX_DATA(CSETUSER)
	enum { IDD = IDD_SETUSER };
	CListBox	m_NPList;
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSETUSER)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// 实现
protected:

	// 生成的消息处理函数
	//{{AFX_MSG(CSETUSER)
	afx_msg void OnAddUser();
	afx_msg void OnDeleteUser();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUSER_H__C2612C82_A4C1_11D6_822C_5254AB1E742B__INCLUDED_)
