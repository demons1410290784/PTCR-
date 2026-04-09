/*
**	FILENAME			ManCmd1.cpp
**
**	PURPOSE				此类可用于将“命令”文本框内的命令字符串
**						按相应的通讯协议修改后传输入万用表或温控
**						表，若仪表有结果返回则将结果字符串显示在
**						相应文本框内
*/

#include "stdafx.h"
#include "ptcr.h"
#include "ManCmd1.h"
#include "ptcrdoc.h"
#include "string.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int F45;
/////////////////////////////////////////////////////////////////////////////
// CManCmd对话框

//
//	构造函数：初始化并打开对话框
//
CManCmd::CManCmd(CPtcrDoc *pDoc,CWnd* pParent /*=NULL*/)
	: CDialog(CManCmd::IDD, pParent)
{
    m_pDoc=pDoc;
	//{{AFX_DATA_INIT(CManCmd)
	m_Cmd = _T("");
	m_Result = _T("");
	//}}AFX_DATA_INIT
}

//
//	对话框数据交换
//
void CManCmd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManCmd)
	DDX_Text(pDX, IDC_CMD_EDIT, m_Cmd);
	DDX_Text(pDX, IDC_RESULT_EDIT, m_Result);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManCmd, CDialog)
	//{{AFX_MSG_MAP(CManCmd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManCmd消息处理程序

//
//	点击“发送”键发送命令，显示返回的结果
//
void CManCmd::OnOK() 
{
	// TODO: Add extra validation here
    int Sr253BCC;
if(F45==0)Sr253BCC=m_pDoc->m_sPort.m_rxdata.Sr253BCC;
else Sr253BCC=m_pDoc->m_sPortF45.m_rxdata.Sr253BCC;	//根据通讯目标为万用表或电子表，选择通讯协议
	char cmd[50];
	char results[128];
	results[0]=0;
	UpdateData(TRUE);
	if(m_Cmd.IsEmpty())
		return;


	if(Sr253BCC==6){//万用表
			strcpy(cmd,m_Cmd.GetBuffer(50));
		if(m_pDoc->MultiMeter==1)  strcat(cmd,"\r");
		if(m_pDoc->MultiMeter==4)  strcat(cmd,"\n");
		if(m_pDoc->MultiMeter==5)  strcat(cmd,"\r\n");	//修改命令格式
	}
    else if(Sr253BCC==2){//温控表，协议SR253
		strcpy(cmd,m_Cmd.GetBuffer(50));		//修改命令格式
	}
	else if(Sr253BCC==3){
		strcpy(cmd,"@");
		strcat(cmd,m_Cmd.GetBuffer(50));
		strcat(cmd,":\r");
	}
	else if(Sr253BCC==4){//温控表，协议SR93

		strcpy(cmd,m_Cmd.GetBuffer(50));
	}

		::SendMessage(AfxGetMainWnd()->m_hWnd,WM_STATUS_MESSAGE,0,AFX_IDS_SENDCMD);
  if(!m_pDoc->ReadPvsv(cmd,results,4,3,Sr253BCC))	//向仪器发送cmd命令，获取结果到result，若通讯不成功：
	{
		MessageBox("操作不成功!","提示",MB_OK);	//弹出消息提示对话框
	}
	if(strlen(results))	//若存在返回结果
		results[strlen(results)-1]=0;
    m_Result=results;	//结果最后一位置零
    UpdateData(FALSE);
	::SendMessage(AfxGetMainWnd()->m_hWnd,WM_STATUS_MESSAGE,0,AFX_IDS_FINISH);
//lby	return;
//	CDialog::OnOK();
}
