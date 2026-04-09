/*
**	FILENAME			CombinDlg.cpp
**
**	PURPOSE				此类可将两个文件中的相关数据合并到一个文件。
**						键入通道号或用逗号或-表示所选范围（如1，3，
**						6-10）后，将合并后对应通道显示在对话框下方的
**						文本框内
*/

#include "stdafx.h"
#include "Ptcr.h"
#include "CombinDlg.h"
#include "fstream.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCombinDlg对话框

//
//	构造函数：初始化并打开对话框
//
CCombinDlg::CCombinDlg(CPtcrDoc *pDoc,CWnd* pParent /*=NULL*/)
	: CDialog(CCombinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCombinDlg)
	//}}AFX_DATA_INIT
	rt3_ChanNum=0;
	rt_num=0;
	strpara="";
}

//
//	对话框数据交换
//
void CCombinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCombinDlg)
	DDX_Control(pDX, IDC_FILE3_EDIT2, m_File3Channel);
	DDX_Control(pDX, IDC_FILE2_EDIT2, m_File2Channel);
	DDX_Control(pDX, IDC_FILE2_EDIT, m_File2Edit);
	DDX_Control(pDX, IDC_FILE1_EDIT2, m_File1Channel);
	DDX_Control(pDX, IDC_FILE1_EDIT, m_File1Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCombinDlg, CDialog)
	//{{AFX_MSG_MAP(CCombinDlg)
	ON_BN_CLICKED(IDC_FILE1_CMD, OnFile1Cmd)
	ON_BN_CLICKED(IDC_FILE2_CMD, OnFile2Cmd)
	ON_EN_KILLFOCUS(IDC_FILE1_EDIT, OnKillfocusFile1Edit)
	ON_EN_KILLFOCUS(IDC_FILE2_EDIT, OnKillfocusFile2Edit)
	ON_EN_KILLFOCUS(IDC_FILE1_EDIT2, OnKillfocusFile1Edit2)
	ON_EN_KILLFOCUS(IDC_FILE2_EDIT2, OnKillfocusFile2Edit2)
	ON_EN_UPDATE(IDC_FILE3_EDIT2, OnUpdateFile3Edit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCombinDlg消息处理程序


//
//	文件一地址浏览操作
//
void CCombinDlg::OnFile1Cmd() 
{
	// TODO: Add your control notification handler code here
	CString str("",100);
	CFileDialog dlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"阻温数据文件(*.RT)|*.RT");
	

	if(dlg.DoModal()==IDOK)
	{
		str=dlg.GetFileName();
		CFile file(str,CFile::modeRead);
		str=dlg.GetPathName();
		CArchive ar(&file,CArchive::load);
		Open(ar,rtsave[0],0);
		ar.Close();
		file.Close();
		if(OpenOk==TRUE)
		{
			FileOpen[0]=TRUE;
			m_File1Edit.SetWindowText(str);
			FileName[0]=str;
		}
		else
		{
			FileOpen[0]=FALSE;
			m_File1Edit.SetWindowText("");
			FileName[0]="";
		}

	}		
}

//
//	文件二地址浏览操作
//
void CCombinDlg::OnFile2Cmd() 
{
	// TODO: Add your control notification handler code here
	CString str;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"阻温数据文件(*.RT)|*.RT");
	
	if(dlg.DoModal()==IDOK)
	{
		str=dlg.GetFileName();
		CFile file(str,CFile::modeRead);
		str=dlg.GetPathName();
		CArchive ar(&file,CArchive::load);
		Open(ar,rtsave[1],1);
		ar.Close();
		file.Close();
		if(OpenOk==TRUE)
		{
			FileOpen[1]=TRUE;
			m_File2Edit.SetWindowText(str);
			FileName[1]=str;
		}
		else
		{
			FileOpen[1]=FALSE;
			m_File2Edit.SetWindowText("");
			FileName[1]="";
		}

	}		
}

//
//“确认”键操作
//
void CCombinDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

//
//	读取文件内各数据
//
void CCombinDlg::Open(CArchive &ar, CRTSave &rt,int num)
{
	try
	{
		int i,j;
		char c;
		CString str("",15);
		float r,t;
		short int s;
					
		rt.Initialization();

		for(i=0;i<NMBOFSPL;i++)
			for(j=0;j<MAXOFSPL;j++)
			{
				ar>>r;
				rt.m_fPtc[i][j]=r;
			}
			
		for(i=0;i<NMBOFSPL;i++)
			for(j=0;j<MAXOFSPL;j++)
			{
				ar>>t;
				rt.LoadT(i,j,t);
			}
		ar>>s;
		rt.LoadStep(s);

		for(i=0;i<=1;i++)
		{
			str="";
			for(j=0;j<15;j++)
			{
				ar>>c;
				str+=c;
			}
					strcpy(rt.m_sStr[i],str);
		}

		str=ar.GetFile()->GetFileName();
//		str.Format("%s.nam",str.Left(str.GetLength()-4));
//oyj
			for(i=0;i<NMBOFSPL;i++)
			{
				j=10;
				if(fabs(rt.m_fPtc[i][j]-1.0)<1e-2||fabs(rt.m_fPtc[i][j]-0.01)<1e-2)
					rt.m_bChannels[i]=0;//		LoadChannels(i,FALSE);

				else
					rt.m_bChannels[i]=1;//LoadChannels(i,TRUE);	
			}
 
  if( strstr(rt.m_sStr[1],"-A")!=NULL)
  {
	 ar.Read(rt.m_bChannels,sizeof(rt.m_bChannels));	

     ar.Read(rt.m_sChannelsName,sizeof(rt.m_sChannelsName));	
     ar.Read(rt.endTime,sizeof(rt.endTime));	

	 ar.Read(rt.MaxT,sizeof(rt.MaxT));	
	 ar.Read(rt.soaking,sizeof(rt.soaking));	
	 ar.Read(rt.Step,sizeof(rt.Step));	
	 ar.Read(rt.Ramp,sizeof(rt.Ramp));	


  }
		ifstream os;
		os.open(str,ifstream::out|ifstream::in|ifstream::nocreate );
		
		if(!os.fail())
		{
			char c[9];
		
			for(i=0;i<NMBOFSPL;i++)
			{
				os.getline(c,9);
				str="";
				str.Format("%s",c);
				if(str!="")
					strcpy(rt.m_sChannelsName[i],str);
			}
		}
		OpenOk=TRUE;
	}
	
	catch(CArchiveException* theException)
	{
		TCHAR str[255];
		theException->GetErrorMessage(str,255);
		MessageBox(str, "警告",MB_OK);
	}
	
}

//
//	文件一地址编辑操作
//
void CCombinDlg::OnKillfocusFile1Edit() 
{
	// TODO: Add your control notification handler code here
	CString str;
	m_File1Edit.GetWindowText(str);
	if(str==FileName[0])
		return;
	else
	{
		try
		{
			CFile file(str,CFile::modeRead);
			CArchive ar(&file,CArchive::load);
			Open(ar,rtsave[0],0);
			file.Close();
			if(OpenOk==TRUE)
			{
				FileOpen[0]=TRUE;
				m_File1Edit.SetWindowText(str);
				FileName[0]=str;
			}
			else
			{
				FileOpen[0]=FALSE;
				m_File1Edit.SetWindowText("");
				FileName[0]="";
			}
		}
		catch( CFileException* e )
		{
			#ifdef _DEBUG
				afxDump << "File could not be opened " << e->m_cause << "\n";
			#endif
		}
	}
}

//
//	文件二地址编辑操作
//
void CCombinDlg::OnKillfocusFile2Edit() 
{
	// TODO: Add your control notification handler code here
	CString str;
	m_File2Edit.GetWindowText(str);
	if(str==FileName[1])
		return;
	else
	{
		try
		{
			CFile file(str,CFile::modeRead);
			CArchive ar(&file,CArchive::load);
			Open(ar,rtsave[1],1);
			file.Close();
			if(OpenOk==TRUE)
			{
				FileOpen[1]=TRUE;
				m_File2Edit.SetWindowText(str);
				FileName[1]=str;

			}
			else
			{
				FileOpen[1]=FALSE;
				m_File2Edit.SetWindowText("");
				FileName[1]="";
			}
		}
	
		catch( CFileException* e )
		{
			#ifdef _DEBUG
				afxDump << "File could not be opened " << e->m_cause << "\n";
			#endif
		}
	}
}

//
//	文件一通道编辑操作
//
void CCombinDlg::OnKillfocusFile1Edit2() 
{
	// TODO: Add your control notification handler code here
	CString str;
	m_File1Channel.GetWindowText(str);
	rt_num=0;
	if(FileCha[0]==str)
		return;
	else
	{	
		FileCha[0]=str;
		
		for(int i=0;i<NMBOFSPL;i++)
		{
			bChannelSelected[0][i]=FALSE;
			bChannelSelected[2][i]=FALSE;
		}

		ChaNum[0]=GetDotNum(str,0)+1;
		 
		OnUpdateFile3Edit2();
	}
	
}

//
//	文件二通道编辑操作
//
void CCombinDlg::OnKillfocusFile2Edit2() 
{
	// TODO: Add your control notification handler code here
	CString str;
	m_File2Channel.GetWindowText(str);
	rt_num=1;
	if(FileCha[1]==str)
		return;
	else
	{	
		FileCha[1]=str;
		for(int i=0;i<NMBOFSPL;i++)
		{
			bChannelSelected[1][i]=FALSE;
			bChannelSelected[2][i]=FALSE;
		}
		ChaNum[1]=GetDotNum(str,1)+1;
		OnUpdateFile3Edit2();
	}
}

//
//	计算字符串内顿点“，”数量
//
int CCombinDlg::GetDotNum(CString str,int index)
{
	int i,j;
	CString str1,str2;
	j=0;
	i=0;
	
	if(str=="")
		return -1;

	while(i!=-1)
	{
		if(str.Find(",")!=-1)
		{
			j++;
			i=str.Find(",")+1;
			str1=str.Left(i-1);
			if(GetSubNum(str1,index)==-1)
			{
				for(int k=1;k<=NMBOFSPL;k++)
				{
					str2.Format("%d",k);
					if(str1==str2)
					{
						bChannelSelected[index][k-1]=TRUE;
						break;
					}
				}
			}

			str=str.Right(str.GetLength()-i);
		}
		else if(str.Find("-")!=-1)
		{
//oyj10-10			GetSubNum(str,index);

			j=GetSubNum(str,index);
			i=-1;
		}
		else
		{
			str1=str;
			for(int k=1;k<=NMBOFSPL;k++)
			{
				str2.Format("%d",k);
				if(str1==str2)
				{
					bChannelSelected[index][k-1]=TRUE;
					break;
				}
			}

			i=-1;
		}
	}

	return j;
}

//
//	计算字符串内子串数量
//
int CCombinDlg::GetSubNum(CString str,int index)
{
	int i,j,k;
	i=0;
	CString str1,str2,str3;

	while(str.Find("-")!=-1)
	{
		j=str.Find("-");
		k=str.GetLength();
		str1=str.Left(j);
		str2=str.Right(k-j-1);
		for(i=1;i<=NMBOFSPL;i++)
		{
			str3.Format("%d",i);
			if(str3==str1)
				break;
		}

		for(j=1;j<=NMBOFSPL;j++)
		{
			str3.Format("%d",j);
			if(str3==str2)
				break;
		}
		
		if(j-i<0)
			return i-j;
		else
		{
			for(k=i-1;k<j;k++)
				bChannelSelected[index][k]=TRUE;
			
			return j-i;
		}
	}

	return -1;
}

//
//	完成文件一通道或文件二通道的编辑后立即调用
//	合并两个文件的通道号，并将合并后的通道号显示在下方文本框内
//
void CCombinDlg::OnUpdateFile3Edit2() 
{
	// TODO:如果这是一个RICHEDIT控件，则该控件将不会发送此通知，
	// 除非您重载CDialog::OnInitDialog()函数以将EM_SETEVENTMASK
	// 消息发送到带有ENM_UPDATE标志ORed的控件到lParam掩码中。
	
	// TODO: Add your control notification handler code here
	ChaNum[2]=ChaNum[0]+ChaNum[1];	//计算合并后总通道数

	if(ChaNum[2]>30)	//若总通道数大于30，则退出该函数
	{
		return;
	}
	
	int  j;

//oyj10-10	for(i=0;i<2;i++)
		for(j=0;j<NMBOFSPL;j++)
		{
			if(bChannelSelected[rt_num][j]==TRUE)	//将文件(rt_num+1)内各个启用的通道：
			{
				WriteChannels(rt_num,j,rt3_ChanNum,strpara);	//合并并显示在下方文本框内；
				bChannelSelected[2][rt3_ChanNum]=TRUE;			//在合并后的文件内设置启用
				rt3_ChanNum++;
			}
		}
	
	FileCha[2]=strpara;
	m_File3Channel.SetWindowText(strpara);	//文本框末尾添加空格
}

//
//	合并通道并将通道号显示在下方文本框内
//
void CCombinDlg::WriteChannels(int i, int j,int k, CString& str)
{
	CString str1;
//oyj
	rtsave[2].m_bChannels[k]=rtsave[i].m_bChannels[j];
	int loop=0;
	for(loop=0;loop<MAXOFSPL;loop++)
	{
		rtsave[2].m_fPtc[rt3_ChanNum][loop]=rtsave[i].m_fPtc[j][loop];
        rtsave[2].m_fTem[rt3_ChanNum][loop]=rtsave[i].m_fTem[j][loop];

	}
	strcpy(rtsave[2].m_sChannelsName[k],rtsave[i].m_sChannelsName[j]);
	if(i==0)
	{
		str1.Format("F3.%2d <---- F1.%2d\t",k+1,j+1);
	}
	else if(i==1)
	{
		str1.Format("F3.%2d <---- F2.%2d\t",k+1,j+1);
	}
CString strcopy;
     strcopy=str;
	str.Format("%s%s",strcopy,str1);
}

//
//	文件保存
//
void CCombinDlg::SaveFile(CArchive &ar)
{
	try
	{
		int i,j,k;
		int l=0;
		char c[15];
		CString str("",15);
		float r,t;
					
		rtsave[2].Initialization();

		for(k=0;k<2;k++)
		{
			for(i=0;i<NMBOFSPL;i++)
			{
				if(bChannelSelected[k][i]==TRUE)
				{
					l++;
					for(j=0;j<MAXOFSPL;j++)
					{
						r=rtsave[k].m_fPtc[i][j];
						ar<<r;
					}
				}
			}
		}
		
		for(i=l;i<NMBOFSPL;i++)
			for(j=0;j<MAXOFSPL;j++)
				ar<<rtsave[2].m_fPtc[i][j];

		for(k=0;k<2;k++)
		{
			for(i=0;i<NMBOFSPL;i++)
			{
				if(bChannelSelected[k][i]==TRUE)
				{
					for(j=0;j<MAXOFSPL;j++)
					{
						t=rtsave[k].GetT(i,j);
						ar<<t;
					}
				}
			}
		}
		
		for(i=l;i<NMBOFSPL;i++)
			for(j=0;j<MAXOFSPL;j++)
				ar<<rtsave[2].GetT(i,j);
		
//oyj10-10		
		//ar<<s;
//				ar<<m_rt.m_rtSave.m_STEP;
		ar<<rtsave[0].GetStep();


//   ar.Write(m_rt.m_rtSave.m_sStr,sizeof(m_rt.m_rtSave.m_sStr));	
		str=rtsave[0].m_sStr[0];
		for(i=0;i<15;i++)
		{
			if(i<str.GetLength())
			   c[i]=str.GetAt(i);
            else
				c[i]=' ';
			ar<<c[i];
		}
		str=rtsave[0].m_sStr[1];
		for(i=0;i<15;i++)
		{
			if(i<str.GetLength())
			   c[i]=str.GetAt(i);
            else
				c[i]=' ';
			ar<<c[i];
		}
//	}
	
  // 

   ar.Write(rtsave[2].m_bChannels,sizeof(rtsave[2].m_bChannels));	

   ar.Write(rtsave[2].m_sChannelsName,sizeof(rtsave[2].m_sChannelsName));	
  
   CString m_Time("",12);

	 ar.Write(rtsave[2].endTime,sizeof(rtsave[2].endTime));	

	 ar.Write(rtsave[2].MaxT,sizeof(rtsave[2].MaxT));	
	 ar.Write(rtsave[2].soaking,sizeof(rtsave[2].soaking));	
	 ar.Write(rtsave[2].Step,sizeof(rtsave[2].Step));	
	 ar.Write(rtsave[2].Ramp,sizeof(rtsave[2].Ramp));	

	 
	 //zjun 2002/8/6

/*	 ar<<MultiMeter;	
	 ar<<ZWX;	
	 ar<<DigitController;	
	 ar<<m_HT12D;	
	 ar<<w2w4;	//2Wire/4wire
	 ar<<Pt100Chan_1;
	 ar<<Pt100Chan_2;

	 ar<<m_rt.Cooling;
	 ar<<CPptc;
	 ar<<heatstop;
     ar<< m_rt.m_Number;
	 */
	 int aaa[500];
	 ar.Write(aaa,sizeof(aaa));	

//OpenFlag=TRUE;	

//10-10oyj
/*		ar<<rtsave[0].GetStep();
		str=rtsave[0].m_sStr[0];
		for(i=0;i<15;i++)
		{
			c[i]=str.GetAt(i);
			ar<<c[i];
		}
		str=rtsave[0].m_sStr[1];
		for(i=0;i<15;i++)
		{
			c[i]=str.GetAt(i);
			ar<<c[i];
		}
	}
*/	
  }
	catch(CArchiveException* theException)
	{
		TCHAR str[255];
		theException->GetErrorMessage(str,255);
		MessageBox(str, "警告",MB_OK);
	}
		
}
