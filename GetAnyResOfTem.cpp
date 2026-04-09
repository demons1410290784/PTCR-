/*
**	FILENAME			GetAnyResOfTem.cpp
**
**	PURPOSE				此类可唤起“获取任意温度阻值”对话框，点击“确认”键
**						时，可根据设置的通道号与温度，读取样品名称和电阻值显
**						示在对应的文本框内
*/

#include "stdafx.h"
#include "ptcr.h"
#include "GetAnyResOfTem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

// CGetAnyResOfTem对话框

//
//	构造函数：初始化并打开对话框
//
CGetAnyResOfTem::CGetAnyResOfTem(CPtcrDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialog(CGetAnyResOfTem::IDD, pParent)
{
    m_pDoc=pDoc;
	//{{AFX_DATA_INIT(CGetAnyResOfTem)
	m_ResVal = _T("");
	m_ChanNum = 1;
	m_TemVal = 0.0f;
	m_SampleName = _T("");
	//}}AFX_DATA_INIT
}

//
//	对话框数据交换
//
void CGetAnyResOfTem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetAnyResOfTem)
	DDX_Text(pDX, IDC_RESVALUE, m_ResVal);
	DDX_Text(pDX, IDC_CHANNELNUM, m_ChanNum);
	DDX_Text(pDX, IDC_TEMINPUT, m_TemVal);
	DDX_Text(pDX, IDC_SAMPLENAME, m_SampleName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGetAnyResOfTem, CDialog)
	//{{AFX_MSG_MAP(CGetAnyResOfTem)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpinChanNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetAnyResOfTem消息处理程序

//
//	通道号选择
//
void CGetAnyResOfTem::OnDeltaposSpinChanNum(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
    m_ChanNum-=pNMUpDown->iDelta;
	if(m_ChanNum>30)
		m_ChanNum=1;
	if(m_ChanNum<1)
		m_ChanNum=12;
//	validate(FALSE);
	char tbuf[8];
	sprintf(tbuf,"%d",m_ChanNum);
	SetDlgItemText(IDC_CHANNELNUM,tbuf);
	
	*pResult = 0;
}

//
//	点击“确认”键：显示所求阻值
//
void CGetAnyResOfTem::OnOK() 
{
	// TODO: Add extra validation here
     UpdateData(TRUE);	
	float resval;
	m_pDoc->m_rt.Calculation(m_ChanNum-1);	//计算该通道数据居里点、最值、范围、温度系数α
	if(m_ChanNum<1 || m_ChanNum>30)	//若通道号超出范围
	
	{
		AfxMessageBox("通道号应在1-30之间",MB_OK,0);	//弹出消息提示对话框
		return;
	}


   if(m_pDoc->m_rt.m_rtSave.m_bChannels[m_ChanNum-1]==FALSE)	//若所选通道未启用
   {
	   m_SampleName="无";	
	   m_ResVal="无";	//样品名称与阻值设为“无”
   }  
    else if(m_TemVal>m_pDoc->m_rt.GetTemMax(m_ChanNum-1))	//若所选温度高于范围
	{
		m_ResVal="温度太高";	//阻值设为“温度太高”
	   	m_SampleName=m_pDoc->m_rt.m_rtSave.m_sChannelsName[m_ChanNum-1];	//获取样品名称
	}
	     else if(m_TemVal<m_pDoc->m_rt.GetTemMin(m_ChanNum-1) && m_TemVal<10)	//若所选温度低于范围
		 {
			    m_ResVal="温度太低";	//阻值设为“温度太低”
	           	m_SampleName=m_pDoc->m_rt.m_rtSave.m_sChannelsName[m_ChanNum-1];	//获取样品名称
		 }
		      else

			  {
	         	resval=pow(10,m_pDoc->m_rt.GetAnyR(m_TemVal,m_ChanNum-1));

           		m_ResVal.Format("%f",resval);	//获取常数表示的该温度对应阻值
	           	m_SampleName=m_pDoc->m_rt.m_rtSave.m_sChannelsName[m_ChanNum-1];	//获取样品名称
			  }


	char tbuf[12];
	sprintf(tbuf,"%s",m_ResVal);
	SetDlgItemText(IDC_RESVALUE,tbuf);
	SetDlgItemText(IDC_SAMPLENAME,m_SampleName);	//文本框内显示样品名称和电阻值

//	
}
