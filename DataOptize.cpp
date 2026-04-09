/*
**	FILENAME			DataOptize.cpp
**
**	PURPOSE				此类可以将曲线中个别点进行修正，通过
**						修改各个拟合点的编号与数值，计算待拟
**						合点的拟合值并进行保存
*/

#include "stdafx.h"
#include "ptcr.h"
#include "DataOptize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//#include "PtcrDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CDataOptize对话框

//
//	构造函数：初始化并打开对话框
//
CDataOptize::CDataOptize(CPtcrDoc* pDoc,CWnd* pParent /*=NULL*/)
	: CDialog(CDataOptize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataOptize)
	m_firstData = _T("");
	m_secondData = _T("");
	m_OptiData = _T("");
	m_fourthData = _T("");
	m_fifthData = _T("");
	m_num1 = 0;
	m_num2 = 0;
	m_num4 = 0;
	m_num5 = 0;
	m_pDoc=pDoc;
	m_DataNum3 = _T("0");

	//}}AFX_DATA_INIT
}

//
//	对话框数据交换
//
void CDataOptize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataOptize)
	DDX_Control(pDX, IDC_EDIT3, m_COptiData);
	DDX_Control(pDX, IDC_EDIT1, m_CfirstData);
	DDX_Text(pDX, IDC_EDIT1, m_firstData);
	DDX_Text(pDX, IDC_EDIT2, m_secondData);
	DDX_Text(pDX, IDC_EDIT3, m_OptiData);
	DDX_Text(pDX, IDC_EDIT4, m_fourthData);
	DDX_Text(pDX, IDC_EDIT5, m_fifthData);
	DDX_Text(pDX, IDC_EDITTEXT1, m_num1);
	DDX_Text(pDX, IDC_EDITTEXT2, m_num2);
	DDX_Text(pDX, IDC_EDITTEXT4, m_num4);
	DDX_Text(pDX, IDC_EDITTEXT5, m_num5);
	DDX_Text(pDX, IDC_EDIT6, m_DataNum3);
	//}}AFX_DATA_MAP
	
}


BEGIN_MESSAGE_MAP(CDataOptize, CDialog)
	//{{AFX_MSG_MAP(CDataOptize)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, OnDeltaposSpin3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, OnDeltaposSpin4)
	ON_EN_UPDATE(IDC_EDIT6, OnUpdateEdit6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN5, OnDeltaposSpin5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataOptize消息处理程序

//
//	编辑数据点1后，计算拟合值并在对应文本框内显示
//
void CDataOptize::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
    int index;
	float data;
	CString str;
	int DataNum3;
	DataNum3=atoi(m_DataNum3);	//拟合点

    m_num1-=pNMUpDown->iDelta;	//数据点1编号减去控件位置更改值
	index=m_pDoc->GetIndex();	//获取多曲线列表Index内通道号
	if(m_num1>m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index])	//编号超过范围时，数据点1编号置1
		m_num1=1;
	if(m_num1<1)
		m_num1=m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index];	//编号过小时，编号置最大编号
    data=m_pDoc->m_rt.GetY(m_num1-1);
    data=pow(10,data);	//data取该编号测量点的阻值（常数表示）
	str.Format("%f",data);
  

	char tbuf[8];
	sprintf(tbuf,"%d",m_num1);
	SetDlgItemText(IDC_EDITTEXT1,tbuf);	//将编辑后的数据点1编号显示在数据点1文本框内
    SetDlgItemText(IDC_EDIT1,str);	//将data显示在数据值1的文本框内
    if(m_num1==m_num2 || m_num1==DataNum3 ||  m_num1== m_num4 || m_num1== m_num5)	//若四个数据点之间存在重复
	{
		MessageBox("不能有一个数据点进行两次拟合",NULL,MB_OK);
        SetDlgItemText(IDC_EDIT3,"");
        SetDlgItemText(IDC_EDIT3,"");

		return;	//弹出消息提醒对话框并退出当前程序
	}
	if(DataNum3>=3 &&DataNum3<=m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]-2 )	//若拟合点大于3且小于最大范围减去2
            data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));	//计算对应拟合值
	if(DataNum3==m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]-1)					//若拟合点为范围内倒数第二个测量点
            data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));	//计算对应拟合点
	if(DataNum3==m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index] )					//若拟合点为范围内最后一个测量点
            data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));	//计算对应拟合值
    if(DataNum3==1)																					//若拟合点为第一个测量点
	        data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));	//计算对应拟合值
    if(DataNum3==2)																					//若拟合点为第二个测量点
             data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));	//计算对应拟合值
    data=pow(10,data);    //将拟合值以常数形式表示
    m_OptiData.Format("%f",data);
    SetDlgItemText(IDC_EDIT3,m_OptiData);	//将计算得到的拟合值显示在拟合值文本框内

	
	*pResult = 0;
}

//
//	编辑数据点2后，计算拟合值并在对应文本框内显示
//

void CDataOptize::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
   int index;
	float data;
	CString str;
	int DataNum3;
	DataNum3=atoi(m_DataNum3);
    m_num2-=pNMUpDown->iDelta;
	index=m_pDoc->GetIndex();
	if(m_num2>m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index])
		m_num2=1;
	if(m_num2<1)
		m_num2=m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index];
//	validate(FALSE);
    data=m_pDoc->m_rt.GetY(m_num2-1);
    data=pow(10,data);
	str.Format("%f",data);
  

	char tbuf[8];
	sprintf(tbuf,"%d",m_num2);
	SetDlgItemText(IDC_EDITTEXT2,tbuf);
    SetDlgItemText(IDC_EDIT2,str);
    if(m_num2==m_num1 || m_num2==DataNum3 ||  m_num2== m_num4 || m_num2== m_num5)
	{
		MessageBox("不能有一个数据点进行两次拟合",NULL,MB_OK);
        SetDlgItemText(IDC_EDIT3,"");

		return;
	}

	if(DataNum3>=3 &&DataNum3<=m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]-2 )
            data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));
	if(DataNum3==m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]-1)
            data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
	if(DataNum3==m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index] )
            data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));
    if(DataNum3==1)
	        data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
    if(DataNum3==2)
             data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
    data=pow(10,data);    
    m_OptiData.Format("%f",data);
    SetDlgItemText(IDC_EDIT3,m_OptiData);
	
	*pResult = 0;
}

//
//	编辑数据点3后，计算拟合值并在对应文本框内显示
//
void CDataOptize::OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
   int index;
	float data;
	CString str;
	int DataNum3;
	DataNum3=atoi(m_DataNum3);
    m_num4-=pNMUpDown->iDelta;
	index=m_pDoc->GetIndex();
	if(m_num4>m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index])
		m_num4=1;
	if(m_num4<1)
		m_num4=m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index];
//	validate(FALSE);
    data=m_pDoc->m_rt.GetY(m_num4-1);
    data=pow(10,data);
	str.Format("%f",data);
  

	char tbuf[8];
	sprintf(tbuf,"%d",m_num4);
	SetDlgItemText(IDC_EDITTEXT4,tbuf);
    SetDlgItemText(IDC_EDIT4,str);
    if(m_num4==m_num1 || m_num4==DataNum3 ||  m_num4== m_num2 || m_num4== m_num5)
	{
		MessageBox("不能有一个数据点进行两次拟合",NULL,MB_OK);
        SetDlgItemText(IDC_EDIT3,"");

		return;
	}

	if(DataNum3>=3 &&DataNum3<=m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]-2 )
            data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));
	if(DataNum3==m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]-1)
            data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
	if(DataNum3==m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index] )
            data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));
    if(DataNum3==1)
	        data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
    if(DataNum3==2)
             data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
	//    data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));
//            data=m_pDoc->GetOptimizeRes(DataNum3-1,DataNum3+1,DataNum3+2,m_pDoc->m_rt.GetX(DataNum3));
    data=pow(10,data);    
    m_OptiData.Format("%f",data);
//	        m_COptiData.SetWindowText(m_OptiData);
    SetDlgItemText(IDC_EDIT3,m_OptiData);
	*pResult = 0;
}

//
//	编辑数据点4后，计算拟合值并在对应文本框内显示
//
void CDataOptize::OnDeltaposSpin4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
   int index;
	float data;
	CString str;
 	int DataNum3;
	DataNum3=atoi(m_DataNum3);
    m_num5-=pNMUpDown->iDelta;
	index=m_pDoc->GetIndex();
	if(m_num5>m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index])
		m_num5=1;
	if(m_num5<1)
		m_num5=m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index];
//	validate(FALSE);
    data=m_pDoc->m_rt.GetY(m_num5-1);
    data=pow(10,data);
	str.Format("%f",data);
  

	char tbuf[8];
	sprintf(tbuf,"%d",m_num5);
	SetDlgItemText(IDC_EDITTEXT5,tbuf);
    SetDlgItemText(IDC_EDIT5,str);
    if(m_num5==m_num1 || m_num5==DataNum3 ||  m_num5== m_num4 || m_num5== m_num2)
	{
		MessageBox("不能有一个数据点进行两次拟合",NULL,MB_OK);
        SetDlgItemText(IDC_EDIT3,"");

		return;
	}
	
	if(DataNum3>=3 &&DataNum3<=m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]-2 )
            data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));
	if(DataNum3==m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]-1)
            data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
	if(DataNum3==m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index] )
            data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));
    if(DataNum3==1)
	        data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
    if(DataNum3==2)
             data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
	//    data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));
//            data=m_pDoc->GetOptimizeRes(DataNum3-1,DataNum3+1,DataNum3+2,m_pDoc->m_rt.GetX(DataNum3));
    data=pow(10,data);    
    m_OptiData.Format("%f",data);
//	        m_COptiData.SetWindowText(m_OptiData);
    SetDlgItemText(IDC_EDIT3,m_OptiData);
	*pResult = 0;
}

//
//	“确认”键操作：保存拟合数据
//
void CDataOptize::OnOK() 
{
	// TODO: Add extra validation here
    if(MessageBox("实验原始数据将丢失!请先将原始数据文件备份!","警告!",MB_OKCANCEL)==IDOK)
	{
		if(MessageBox("原始数据文件是否已备份!!! 未备份数据丢失后果自负","警告!",MB_OKCANCEL)==IDCANCEL)
		   return;
	}
	else
	   return ;
	int index;
	index=m_pDoc->GetIndex();
    int j;
	j=m_pDoc->m_rt.m_DataNum-1+m_pDoc->m_rt.m_iStartDot[index];
    m_pDoc->m_rt.m_rtSave.m_fPtc[index][j]=m_pDoc->m_rt.m_TempResVal;
//    	SendMessage(AfxGetMainWnd()->m_hWnd,WM_COMMAND,ID_FILE_SAVE_AS,0);
	CDialog::OnOK();
}

//
//	修改拟合值后，将最近的数据点编号与数据值显示在对应文本框内，
//	同时将计算后的拟合值显示在拟合值文本框内
//
void CDataOptize::OnUpdateEdit6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int DataNum3;
	float data;
    int index;
	CString strnum,str;
	DataNum3=atoi(m_DataNum3);
	
	index=m_pDoc->GetIndex();
	m_pDoc->m_rt.Calculation(index);

	if(DataNum3<=0 )
	{
		MessageBox("输入实验数据点应大于0!",NULL,MB_OK);
		return;
	}
	if(DataNum3>m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index])
	{
		MessageBox("输入实验数据点太大，无此数据点!",NULL,MB_OK);
		return;
	}
    if(m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]<=5)
	{
	   MessageBox("实验数据太少，无法拟合",NULL,MB_OK);
	   return ;
	}
	if(DataNum3>=3 &&DataNum3<=m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]-1 )
	{
		m_num1=DataNum3-2;
		strnum.Format("%d",m_num1);
	    data=m_pDoc->m_rt.GetY(m_num1-1);
		data=pow(10,data);
		str.Format("%f",data);
	    SetDlgItemText(IDC_EDITTEXT1,strnum);
	    SetDlgItemText(IDC_EDIT1,str);
		m_num2=DataNum3-1;
		strnum.Format("%d",m_num2);
	    data=m_pDoc->m_rt.GetY(m_num2-1);
		data=pow(10,data);
		str.Format("%f",data);
	    SetDlgItemText(IDC_EDITTEXT2,strnum);
	    SetDlgItemText(IDC_EDIT2,str);
        if(DataNum3<=m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]-2)
		{
			m_num4=DataNum3+1;
			strnum.Format("%d",m_num4);
		    data=m_pDoc->m_rt.GetY(m_num4-1);
    		data=pow(10,data);
    		str.Format("%f",data);
    	    SetDlgItemText(IDC_EDITTEXT4,strnum);
	        SetDlgItemText(IDC_EDIT4,str);
			m_num5=DataNum3+2;
			strnum.Format("%d",m_num5);
		    data=m_pDoc->m_rt.GetY(m_num5-1);
    		data=pow(10,data);
    		str.Format("%f",data);
    	    SetDlgItemText(IDC_EDITTEXT5,strnum);
	        SetDlgItemText(IDC_EDIT5,str);
            data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));
//            data=m_pDoc->GetOptimizeRes(DataNum3-1,DataNum3+1,DataNum3+2,m_pDoc->m_rt.GetX(DataNum3));
      	    data=pow(10,data);    
			m_pDoc->m_rt.m_TempResVal=data;
			m_pDoc->m_rt.m_DrawDotFlag=TRUE;
			m_pDoc->m_rt.m_DataNum=DataNum3;
            m_OptiData.Format("%f",data);
//	        m_COptiData.SetWindowText(m_OptiData);
	        SetDlgItemText(IDC_EDIT3,m_OptiData);
			m_pDoc->UpdateAllViews(NULL);
//			m_pDoc->m_rt.m_DrawDotFlag=FALSE;
		}
		else if(DataNum3==m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index]-1)
		{
          	m_num4=DataNum3+1;
			strnum.Format("%d",m_num4);
		    data=m_pDoc->m_rt.GetY(m_num4-1);
    		data=pow(10,data);
    		str.Format("%f",data);
    	    SetDlgItemText(IDC_EDITTEXT4,strnum);
	        SetDlgItemText(IDC_EDIT4,str);

			m_num5=0;
			strnum.Format("%d",m_num5);
			str="";
    	    SetDlgItemText(IDC_EDITTEXT5,strnum);
	        SetDlgItemText(IDC_EDIT5,str);
 
//			data=m_pDoc->GetOptimizeRes(DataNum3-2,DataNum3-1,DataNum3+1,m_pDoc->m_rt.GetX(DataNum3));
            data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
      	    data=pow(10,data);    
			m_pDoc->m_rt.m_TempResVal=data;
			m_pDoc->m_rt.m_DrawDotFlag=TRUE;
			m_pDoc->m_rt.m_DataNum=DataNum3;

            m_OptiData.Format("%f",data);
//	        m_COptiData.SetWindowText(m_OptiData);
	        SetDlgItemText(IDC_EDIT3,m_OptiData);
			m_pDoc->UpdateAllViews(NULL);
//	     		m_pDoc->m_rt.m_DrawDotFlag=FALSE;

		}
	}
    if(DataNum3==m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index])
	  {
                m_num1=DataNum3-4;
               	strnum.Format("%d",m_num1);
	            data=m_pDoc->m_rt.GetY(m_num1-1);
	        	data=pow(10,data);
        		str.Format("%f",data);
	            SetDlgItemText(IDC_EDITTEXT1,strnum);
        	    SetDlgItemText(IDC_EDIT1,str);

        		m_num2=DataNum3-3;
        		strnum.Format("%d",m_num2);
        	    data=m_pDoc->m_rt.GetY(m_num2-1);
          		data=pow(10,data);
          		str.Format("%f",data);
         	    SetDlgItemText(IDC_EDITTEXT2,strnum);
        	    SetDlgItemText(IDC_EDIT2,str);

				m_num4=DataNum3-2;		
				strnum.Format("%d",m_num4);	
				data=m_pDoc->m_rt.GetY(m_num4-1);    
				data=pow(10,data);    
				str.Format("%f",data);   
				SetDlgItemText(IDC_EDITTEXT4,strnum);	  
				SetDlgItemText(IDC_EDIT4,str);
    
       			m_num5=DataNum3-1;
	      		strnum.Format("%d",m_num5);
				data=m_pDoc->m_rt.GetY(m_num5-1);    
				data=pow(10,data);    
				str.Format("%f",data);   
    	        SetDlgItemText(IDC_EDITTEXT5,strnum);
	            SetDlgItemText(IDC_EDIT5,str);


                data=m_pDoc->GetOptimizeRes(m_num2-1,m_num4-1,m_num5-1,m_pDoc->m_rt.GetX(DataNum3-1));
        	    data=pow(10,data);    
              	m_pDoc->m_rt.m_TempResVal=data;
	     		m_pDoc->m_rt.m_DrawDotFlag=TRUE;
		    	m_pDoc->m_rt.m_DataNum=DataNum3;
                m_OptiData.Format("%f",data);
//	        m_COptiData.SetWindowText(m_OptiData);
	            SetDlgItemText(IDC_EDIT3,m_OptiData);	
	    		m_pDoc->UpdateAllViews(NULL);
//			m_pDoc->m_rt.m_DrawDotFlag=FALSE;
	}

	 if(DataNum3==1)	
	     {
        	 m_num1=DataNum3+1;
             strnum.Format("%d",m_num1);
        	 data=m_pDoc->m_rt.GetY(m_num1-1);
             data=pow(10,data);
             str.Format("%f",data);
             SetDlgItemText(IDC_EDITTEXT1,strnum);
	         SetDlgItemText(IDC_EDIT1,str);

	         m_num2=DataNum3+2;
             strnum.Format("%d",m_num2);
	         data=m_pDoc->m_rt.GetY(m_num2-1);
             data=pow(10,data);
             str.Format("%f",data);
             SetDlgItemText(IDC_EDITTEXT2,strnum);
	         SetDlgItemText(IDC_EDIT2,str);

	         m_num4=DataNum3+3;
             strnum.Format("%d",m_num4);
	         data=m_pDoc->m_rt.GetY(m_num4-1);
             data=pow(10,data);
             str.Format("%f",data);
             SetDlgItemText(IDC_EDITTEXT4,strnum);
	         SetDlgItemText(IDC_EDIT4,str);


             m_num5=DataNum3+4;
             strnum.Format("%d",m_num5);
	         data=m_pDoc->m_rt.GetY(m_num5-1);
             data=pow(10,data);
             str.Format("%f",data);
             SetDlgItemText(IDC_EDITTEXT5,strnum);
	         SetDlgItemText(IDC_EDIT5,str);


             data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
		 //    data=m_pDoc->GetOptimizeRes(DataNum3+1,DataNum3+2,DataNum3+3,m_pDoc->m_rt.GetX(DataNum3));
      	     data=pow(10,data);    
             	m_pDoc->m_rt.m_TempResVal=data;
	     		m_pDoc->m_rt.m_DrawDotFlag=TRUE;
		    	m_pDoc->m_rt.m_DataNum=DataNum3;
             m_OptiData.Format("%f",data);
	         SetDlgItemText(IDC_EDIT3,m_OptiData);
	    		m_pDoc->UpdateAllViews(NULL);
//			m_pDoc->m_rt.m_DrawDotFlag=FALSE;

	      }
	  else if(DataNum3==2)
		  {
        	 m_num1=DataNum3-1;
             strnum.Format("%d",m_num1);
	         data=m_pDoc->m_rt.GetY(m_num1-1);
             data=pow(10,data);
             str.Format("%f",data);
             SetDlgItemText(IDC_EDITTEXT1,strnum);
	         SetDlgItemText(IDC_EDIT1,str);

	         m_num2=DataNum3+1;
             strnum.Format("%d",m_num2);
	         data=m_pDoc->m_rt.GetY(m_num2-1);
             data=pow(10,data);
             str.Format("%f",data);
             SetDlgItemText(IDC_EDITTEXT2,strnum);
	         SetDlgItemText(IDC_EDIT2,str);

	         m_num4=DataNum3+2;
             strnum.Format("%d",m_num4);
	         data=m_pDoc->m_rt.GetY(m_num4-1);
             data=pow(10,data);
             str.Format("%f",data);
             SetDlgItemText(IDC_EDITTEXT4,strnum);
	         SetDlgItemText(IDC_EDIT4,str);


             m_num5=DataNum3+3;
             strnum.Format("%d",m_num5);
	         data=m_pDoc->m_rt.GetY(m_num5-1);
             data=pow(10,data);
             str.Format("%f",data);
             SetDlgItemText(IDC_EDITTEXT5,strnum);
	         SetDlgItemText(IDC_EDIT5,str);


             data=m_pDoc->GetOptimizeRes(m_num1-1,m_num2-1,m_num4-1,m_pDoc->m_rt.GetX(DataNum3-1));
     	     data=pow(10,data);    
              	m_pDoc->m_rt.m_TempResVal=data;
	     		m_pDoc->m_rt.m_DrawDotFlag=TRUE;
		    	m_pDoc->m_rt.m_DataNum=DataNum3;
             m_OptiData.Format("%f",data);
	         SetDlgItemText(IDC_EDIT3,m_OptiData);
	    		m_pDoc->UpdateAllViews(NULL);
//	     		m_pDoc->m_rt.m_DrawDotFlag=FALSE;
	      }


}

//
//	修改拟合点后，将编辑后的拟合点编号在对应文本框内显示
//
void CDataOptize::OnDeltaposSpin5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
    int index;
	float data;
	CString str;
	int DataNum3;
	DataNum3=atoi(m_DataNum3);
    DataNum3-=pNMUpDown->iDelta;
	index=m_pDoc->GetIndex();
	if(DataNum3>m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index])
		DataNum3=1;
	if(DataNum3<1)
		DataNum3=m_pDoc->m_rt.m_iEndDot[index]-m_pDoc->m_rt.m_iStartDot[index];
//	validate(FALSE);
	char tbuf[8];
	sprintf(tbuf,"%d",DataNum3);
	SetDlgItemText(IDC_EDIT6,tbuf);

	*pResult = 0;
}
