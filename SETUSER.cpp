/*
**	FILENAME			SETUSER.cpp
**
**	PURPOSE				此类可用于进行用户设置，仅在拥有相关权限
**						的用户登录后才可使用此功能。“用户设置”
**						对话框可以浏览已经注册的账户信息，并可以
**						新建或删除账户数据
*/

#include "stdafx.h"
#include "ptcr.h"
#include "SETUSER.h"
#include "SetSingleUser.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSETUSER对话框

//
//	构造函数：初始化并打开窗口
//
CSETUSER::CSETUSER(CWnd* pParent /*=NULL*/)
	: CDialog(CSETUSER::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSETUSER)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

//
//	对话框数据交换
//
void CSETUSER::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSETUSER)
	DDX_Control(pDX, IDC_LIST1, m_NPList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSETUSER, CDialog)
	//{{AFX_MSG_MAP(CSETUSER)
	ON_BN_CLICKED(IDC_BUTTONADDUSER, OnAddUser)
	ON_BN_CLICKED(IDC_BUTTONDELETEUSER, OnDeleteUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSETUSER消息处理程序

//
//	新增账户信息
//
void CSETUSER::OnAddUser() 
{
	// TODO: Add your control notification handler code here
	CSetSingleUser d;	//开启“用户注册”对话框
	CFile cf;
	CFile cfn,cfo;
	CString nptext;
	struct person{
		char name[20];
		char password[20];
		bool del;
	}pp;

	if(d.DoModal()==IDOK)
	{
		UpdateData(TRUE);
		if(cf.Open("C:\\Windows\\npcera.ini",CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite))	//打开配置文件npcera.ini
		{
			cf.SeekToEnd();
			strcpy(pp.name,d.m_Name);
			strcpy(pp.password,d.m_Password);
			pp.del=FALSE;
			cf.Write(&pp,sizeof(pp));
			cf.Close();
			nptext="               ";
			nptext+=pp.name;
			nptext+="                                       ";
			nptext+=pp.password;
			m_NPList.AddString(nptext.GetBuffer(100));	//将“用户注册”对话框内收集到的信息写入配置文件npcera.ini
		}
		else
		{
			MessageBox("写文件失败!","ptc",MB_OK);
		    return ;
		}
	}

//	if(!cfo.Open("ptc.cpx",CFile::modeRead))
	if(!cfo.Open("c:\\Windows\\npcera.ini",CFile::modeRead))
	{
		MessageBox("无法打开配置文件!","ptc",MB_OK);
		return;
	}
//	if(!cfn.Open("ptc1.cpx",CFile::modeCreate|CFile::modeWrite))
	if(!cfn.Open("c:\\Windows\\npcera1.ini",CFile::modeCreate|CFile::modeWrite))
	{
		MessageBox("无法写文件!","ptc",MB_OK);
		cfo.Close();
		return;
	}
	while(cfo.Read(&pp,sizeof(pp))==sizeof(pp))
		if(!pp.del)
			cfn.Write(&pp,sizeof(pp));
	cfo.Close();
	cfn.Close();
//	CFile::Remove("ptc.cpx");
	CFile::Remove("c:\\Windows\\npcera.ini");
//	CFile::Rename("ptc1.cpx","ptc.cpx");
	CFile::Rename("c:\\Windows\\npcera1.ini","c:\\Windows\\npcera.ini");
//	MessageBox("整理完毕!","ptc",MB_OK);


}

//
//	删除账户
//
void CSETUSER::OnDeleteUser() 
{
	// TODO: Add your control notification handler code here
    int rcount,j;
	CFile cf;
	struct person{
		char name[20];
		char password[20];
		bool del;
	}pp;
	if(!m_NPList.GetCount())
	{
		MessageBox("不存在可删除的操作员!","ptc",MB_OK);
		return;
	}
    j=m_NPList.GetCurSel();
//	if( !cf.Open( "ptc.cpx", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite))
	if( !cf.Open( "c:\\Windows\\npcera.ini", CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite))
		{
		   MessageBox("不能打开配置文件,删除失败!","ptc",MB_OK);
		}
	else
	{
    	rcount=0;
        while(cf.Read(&pp,sizeof(pp))==sizeof(pp))
		{
			if(pp.del)
				continue;
            if(rcount==j)
			{
				pp.del=TRUE;
                cf.Seek(-long(sizeof(pp)),CFile::current);
				cf.Write(&pp,sizeof(pp));
    			m_NPList.DeleteString(j);
				break;
			}
			rcount++;
        }
		cf.Close();
	}

	
}

//
//	对话框初始化
//
BOOL CSETUSER::OnInitDialog() 
{
	CDialog::OnInitDialog();
		CFile cf;
	CFileStatus cfs;
    CString nptext;
	struct person{
		char name[20];
		char password[20];
		bool del;
	}pp;

//	if(!cf.GetStatus("stea.cfg",cfs))
	if(!cf.GetStatus("c:\\Windows\\npcera.ini",cfs))
		return TRUE;
//	if( !cf.Open( "ptc.cpx", CFile::modeRead ))
	if( !cf.Open( "c:\\Windows\\npcera.ini", CFile::modeRead ))
		{
		   MessageBox("配置文件不可用,请重设所有操作员!","ptc",MB_OK);
		}
	else
	{
        while(cf.Read(&pp,sizeof(pp))==sizeof(pp))
		{
			if(pp.del)
				continue;
			nptext="               ";
			nptext+=pp.name;
			nptext+="                                       ";
			nptext+=pp.password;
			m_NPList.AddString(nptext.GetBuffer(100));
        }
		cf.Close();
	}

	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
