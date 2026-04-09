/*
**	FILENAME			Login.cpp
**
**	PURPOSE				此类可唤起“登录”对话框，点击“确认”键
**						检查账号的存在以及密码是否正确，根据结果
**						返回最终登陆状态
*/

#include "stdafx.h"
#include "ptcr.h"
#include "Login.h"
extern CString m_setusername;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogin对话框

//
//	构造函数：初始化并打开对话框
//
CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CLogin::IDD, pParent)
{
    m_pass=FALSE;
    m_count=0;

	//{{AFX_DATA_INIT(CLogin)
	m_name = _T("");
	m_password = _T("");
	//}}AFX_DATA_INIT
}

//
//	对话框数据交换
//
void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogin)
	DDX_Text(pDX, IDC_EDITNAME, m_name);
	DDX_Text(pDX, IDC_EDITPASSWORD, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogin, CDialog)
	//{{AFX_MSG_MAP(CLogin)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogin消息处理函数

//
//	点击“确认”键检查登陆状态
//
void CLogin::OnOK() 
{
	// TODO: Add extra validation here
    UpdateData(TRUE);	//更新数据
	CFile cf;
	CFileStatus cfs;
    bool nameexist=FALSE;
	m_setusername=m_name;
	struct person{
		char name[20];
		char password[20];
		bool del;
	}pp;	//构建person结构体对象pp

	m_count++;
	if(!strcmp(m_name,"lbyptcrt0")||!strcmp(m_name,"LBYPTCRT0"))
			m_pass=TRUE;	//若用户名为“lbyptcrt0”或“LBYPTCRT0”则直接登陆成功
	else if(!strcmp(m_name,"hust01")||!strcmp(m_name,"HUST01"))	//若用户名为“hust01”或“HUST01”
	{
	CTime dt=CTime::GetCurrentTime();
    CString m_sStr[2];
 	m_sStr[0] = dt.Format("%Y%m%d"); 
    m_sStr[1]=dt.Format("%H:%M:%S-A");	//获取系统时间

	if((m_sStr[0]>"20260101")||(m_sStr[0]<"20031101"))
	{  //验证有效日期
			MessageBox("硬件错误，错误号：YearMonthDay!","验证",MB_OK);
            m_pass=FALSE;
	}
    else 	if(!strcmp(m_password,"12345"))	//若密码为12345
	{
   m_pass=TRUE;	//登陆成功
	}
		else 
		{
			MessageBox("密码不对!","验证",MB_OK);
            m_pass=FALSE;
		}
    }
	else
	{
		if(!cf.GetStatus("c:\\Windows\\npcera.ini",cfs))	//检查配置文件npcera.ini
		{
			MessageBox("配置文件缺失!","提示",MB_OK);
                m_pass=FALSE;
       }
        else if( !cf.Open( "c:\\Windows\\npcera.ini", CFile::modeRead ))	//打开配置文件npcera.ini
		{
		   MessageBox("配置文件不可用!","提示",MB_OK);
                m_pass=FALSE;
		}
		else
		{
        while(cf.Read(&pp,sizeof(pp))==sizeof(pp))	//读取配置文件内账户数据
		{   
			if(pp.del)
				continue;
			if(!strcmp(pp.name,m_name))	//若账户名存在
			{
				nameexist=TRUE;
				if(!strcmp(pp.password,m_password))	//若密码正确
				{
				    m_pass=TRUE;	//登陆成功
				}
				else
				{
					MessageBox("密码不对!","验证",MB_OK);
					m_pass=FALSE;
				}
				break;
			}
        }
		cf.Close();
		if(!nameexist)	//若账户名不存在
		{
			MessageBox("无此操作员!","验证",MB_OK);
			m_pass=FALSE;
		}
		}
	}
  if(m_pass||m_count>=3)	//若账号与密码均正确
	  CDialog::OnOK();		//退出“登录”对话库那个
  return;
}

//
//	绘制“登录”对话框界面
//
void CLogin::OnPaint() 
{

	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC cdc;
	CFont *pOldFont;
	CBitmap cb;
	BITMAP bp;
    CString ntext;
	int OldDC;
	CFont cf;

	//显示位图
	cb.LoadBitmap(IDB_BMPUNIVERSITY);
	cb.GetBitmap(&bp);
	cdc.CreateCompatibleDC(&dc);
	cdc.SelectObject(&cb);
	dc.BitBlt(0,0,bp.bmWidth,bp.bmHeight,&cdc,0,0,SRCCOPY);
	cb.DeleteObject();
	
	//显示文本
	cf.CreatePointFont(160,"Microsoft YaHei UI Bold",NULL);
	pOldFont=cdc.SelectObject(&cf);
	OldDC=dc.SaveDC();
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,0,0));
	dc.SelectObject(&cf);
	dc.TextOut(360,20,"敏感陶瓷教育部");
	dc.TextOut(370,45,"工程研究中心");
    dc.RestoreDC(OldDC);
	cf.DeleteObject();

	cf.CreatePointFont(130,"Microsoft YaHei UI Bold",NULL);
	pOldFont=cdc.SelectObject(&cf);
	OldDC=dc.SaveDC();
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,0,0));
	dc.SelectObject(&cf);
	ntext="用户:";
	dc.TextOut(370,105,ntext);
	ntext="密码:";
	dc.TextOut(370,155,ntext);

	cdc.DeleteDC();

	cf.DeleteObject();

	
	// Do not call CDialog::OnPaint() for painting messages
}
