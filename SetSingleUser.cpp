/*
**	FILENAME			SetSingleUser.cpp
**
**	PURPOSE				此类可用于注册新的账户，信息包含用户名称以及用户密码
*/

#include "stdafx.h"
#include "ptcr.h"
#include "SetSingleUser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetSingleUser对话框

//
//	构造函数：初始化并打开对话框
//
CSetSingleUser::CSetSingleUser(CWnd* pParent /*=NULL*/)
	: CDialog(CSetSingleUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetSingleUser)
	m_Name = _T("");
	m_Password = _T("");
	//}}AFX_DATA_INIT
}

//
//	对话框数据交换
//
void CSetSingleUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetSingleUser)
	DDX_Text(pDX, IDC_USERNAME, m_Name);
	DDX_Text(pDX, IDC_PASSWORD, m_Password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetSingleUser, CDialog)
	//{{AFX_MSG_MAP(CSetSingleUser)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetSingleUser 消息处理程序
