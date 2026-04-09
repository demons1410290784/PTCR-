/*
**	FILENAME			SelRTRange.cpp
**
**	PURPOSE				此类可用于对曲线范围进行设置，可在对话框内
**						对曲线阻值的上下限、温度的上下限等参数进行
**						修改，还可以更改温度间隔与电阻的坐标形式
*/

#include "stdafx.h"
#include "ptcr.h"
#include "SelRTRange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelRTRange对话框

//
//	构造函数：初始化并打开对话框
//
CSelRTRange::CSelRTRange(CWnd* pParent /*=NULL*/)
	: CDialog(CSelRTRange::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelRTRange)
	m_tempstep = 0;
	m_minres = _T("");
	m_maxtemp = _T("");
	m_maxres = _T("");
	m_mintemp = _T("");
	m_showdot = FALSE;
	m_OnlyMeaDot = FALSE;
	m_SelCoorKind = FALSE;
	m_EndStopHeat = _T("");
	m_OutRect = TRUE;
	//}}AFX_DATA_INIT
}

//
//	对话框数据交换
//
void CSelRTRange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelRTRange)
	DDX_Text(pDX, IDC_EDIT2, m_tempstep);
	DDV_MinMaxUInt(pDX, m_tempstep, 10, 100);
	DDX_CBString(pDX, IDC_COMBO1, m_minres);
	DDV_MaxChars(pDX, m_minres, 20);
	DDX_CBString(pDX, IDC_COMBO2_MAXTEMP, m_maxtemp);
	DDV_MaxChars(pDX, m_maxtemp, 20);
	DDX_CBString(pDX, IDC_COMBO_MAXRES, m_maxres);
	DDV_MaxChars(pDX, m_maxres, 20);
	DDX_CBString(pDX, IDC_COMBO_MINTEMP, m_mintemp);
	DDV_MaxChars(pDX, m_mintemp, 20);
	DDX_Check(pDX, IDC_CHECK1, m_showdot);
	DDX_Check(pDX, IDC_CHECK2, m_OnlyMeaDot);
	DDX_Text(pDX, IDC_EDIT_EndStopHeat, m_EndStopHeat);
	DDV_MaxChars(pDX, m_EndStopHeat, 30);
	DDX_Check(pDX, IDC_CHECK3, m_OutRect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelRTRange, CDialog)
	//{{AFX_MSG_MAP(CSelRTRange)
	ON_COMMAND_RANGE(IDC_RADIO2,IDC_RADIO4,OnChioce)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelRTRange消息处理程序

//
//	选择并保存电阻坐标形式
//
UINT CSelRTRange::OnChioce(UINT nID)
{
  switch(nID)
	{                    

	case IDC_RADIO2:
       m_SelCoorKind=2;//科学记数
         break;
	case IDC_RADIO3:
       m_SelCoorKind=0;//指数
         break;
	case IDC_RADIO4:
       m_SelCoorKind=1;//对数
         break;
	default:
         break;

  }
          return m_SelCoorKind;
}

//
//	初始化对话框单选按钮选中状态
//
BOOL CSelRTRange::OnInitDialog() 
{
	CDialog::OnInitDialog();
//lby
	CButton * m_pRadio;
	// TODO: Add extra initialization here
  switch(m_SelCoorKind)
	{                    

	case 2:
	  m_pRadio=(CButton*)GetDlgItem(IDC_RADIO2);
       //科学记数
         break;
	case 0:
  	  m_pRadio=(CButton*)GetDlgItem(IDC_RADIO3);
     //指数
         break;
	case 1:
    	  m_pRadio=(CButton*)GetDlgItem(IDC_RADIO4);
     //对数
         break;
	default:
         break;	
  }
		 m_pRadio->SetCheck(1);

		 return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
