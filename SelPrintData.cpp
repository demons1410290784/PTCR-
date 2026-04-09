/*
**	FILENAME			SelPrintData.cpp
**
**	PURPOSE				此类可用于打印数据的选择，选项包含“打印原始测试数据”
**						、“打印温度取整后测试记录”和“不打印原始测试数据”
*/

#include "stdafx.h"
#include "ptcr.h"
#include "SelPrintData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelPrintData对话框

//
//	构造函数：初始化并打开对话框
//
SelPrintData::SelPrintData(CWnd* pParent /*=NULL*/)
	: CDialog(SelPrintData::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelPrintData)
	m_order = -1;
	//}}AFX_DATA_INIT
}

//
//	对话框数据交换：更改窗口内选择状态则立即保存当前进行的选择
//
void SelPrintData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelPrintData)
	DDX_Radio(pDX, IDC_RADIO3, m_order);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelPrintData, CDialog)
	//{{AFX_MSG_MAP(SelPrintData)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelPrintData消息处理程序

//
//	选择“打印原始数据”
//
void SelPrintData::OnRadio3() 
{
	// TODO: Add your control notification handler code here
   m_PriStyle=1;
	
}

//
//	选择“打印温度取整后测试记录”
//
void SelPrintData::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	m_PriStyle=2;
	
}

//
//	选择“不打印原始数据”
//
void SelPrintData::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	m_PriStyle=0;
	
}

//
//	初始化对话框
//
BOOL SelPrintData::OnInitDialog() 
{
	CDialog::OnInitDialog();
  	// TODO: Add extra initialization here

	if((m_PriStyle<0)||	(m_PriStyle>2)) m_PriStyle=0;
//lby
	CButton * m_pRadio;
	// TODO: Add extra initialization here
 int m_SelCoorKind;
     m_SelCoorKind=m_PriStyle;
	switch(m_SelCoorKind)
	{                    

	case 2:
	  m_pRadio=(CButton*)GetDlgItem(IDC_RADIO4);
       //科学记数
         break;
	case 0:
  	  m_pRadio=(CButton*)GetDlgItem(IDC_RADIO5);
     //指数
         break;
	case 1:
    	  m_pRadio=(CButton*)GetDlgItem(IDC_RADIO3);
     //对数
         break;
	default:
         break;	
  }
		 m_pRadio->SetCheck(1);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
