/*
**	FILENAME			NameResi.h
**
**	PURPOSE				此类可用于设置通道号启用、样品名称和室温阻值。
**						此外可以选择相应的温度、阻值进行读取，并进行通
**						道校零
*/

#if !defined(AFX_NAMERESI_H__2CBD1AC1_D91C_11D5_A239_0010DC09E70D__INCLUDED_)
#define AFX_NAMERESI_H__2CBD1AC1_D91C_11D5_A239_0010DC09E70D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NameResi.h : 头文件
//
#include "PtcrDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CNameResi对话框

class CNameResi : public CDialog
{
// 构造
public:
	CPtcrDoc *m_pDoc;
	CNameResi(CPtcrDoc *pDoc,CWnd* pParent = NULL);   // 标准构造函数
    void UpData();
    void   ChannelDisplay(int i,char buf[][35]); 
    CString ResiFormat(int i);
// 对话框数据
	//{{AFX_DATA(CNameResi)
	enum { IDD = IDD_Name_Resis_Setting };
	BOOL	m_Ch1;
	BOOL	m_Ch10;
	BOOL	m_Ch11;
	BOOL	m_Ch12;
	BOOL	m_Ch13;
	BOOL	m_Ch14;
	BOOL	m_Ch15;
	BOOL	m_Ch16;
	BOOL	m_Ch17;
	BOOL	m_Ch18;
	BOOL	m_Ch19;
	BOOL	m_Ch2;
	BOOL	m_Ch20;
	BOOL	m_Ch21;
	BOOL	m_Ch22;
	BOOL	m_Ch23;
	BOOL	m_Ch24;
	BOOL	m_Ch25;
	BOOL	m_Ch26;
	BOOL	m_Ch27;
	BOOL	m_Ch28;
	BOOL	m_Ch29;
	BOOL	m_Ch3;
	BOOL	m_Ch30;
	BOOL	m_Ch4;
	BOOL	m_Ch5;
	BOOL	m_Ch6;
	BOOL	m_Ch7;
	BOOL	m_Ch8;
	BOOL	m_Ch9;
	CString	m_Name1;
	CString	m_Name10;
	CString	m_Name11;
	CString	m_Name12;
	CString	m_Name13;
	CString	m_Name14;
	CString	m_Name15;
	CString	m_Name16;
	CString	m_Name17;
	CString	m_Name18;
	CString	m_Name19;
	CString	m_Name2;
	CString	m_Name20;
	CString	m_Name21;
	CString	m_Name22;
	CString	m_Name23;
	CString	m_Name24;
	CString	m_Name25;
	CString	m_Name26;
	CString	m_Name27;
	CString	m_Name28;
	CString	m_Name29;
	CString	m_Name3;
	CString	m_Name30;
	CString	m_Name4;
	CString	m_Name5;
	CString	m_Name6;
	CString	m_Name7;
	CString	m_Name8;
	CString	m_Name9;
	CString	m_Resi10;
	CString	m_Resi1;
	CString	m_Resi11;
	CString	m_Resi12;
	CString	m_Resi13;
	CString	m_Resi14;
	CString	m_Resi15;
	CString	m_Resi16;
	CString	m_Resi17;
	CString	m_Resi18;
	CString	m_Resi19;
	CString	m_Resi2;
	CString	m_Resi20;
	CString	m_Resi21;
	CString	m_Resi22;
	CString	m_Resi23;
	CString	m_Resi24;
	CString	m_Resi25;
	CString	m_Resi26;
	CString	m_Resi27;
	CString	m_Resi28;
	CString	m_Resi29;
	CString	m_Resi3;
	CString	m_Resi30;
	CString	m_Resi4;
	CString	m_Resi5;
	CString	m_Resi6;
	CString	m_Resi7;
	CString	m_Resi8;
	CString	m_Resi9;
	int		m_ChanNo;
	CString	m_Resi;
	CString	m_Sr253PV;
	CString	m_Pt100PV;
	CString	m_Sr253SV;
	BOOL	m_CheckZero;
	CString	m_Pt100_1;
	CString	m_Pt100_2;


	//}}AFX_DATA

// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNameResi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// 实现 
protected:

	// Generated message map functions
	//{{AFX_MSG(CNameResi)
	virtual void OnOK();
	afx_msg void OnReadF45();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnReadResis0();
	afx_msg void OnReadSr253();
	afx_msg void OnReadPt100();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAMERESI_H__2CBD1AC1_D91C_11D5_A239_0010DC09E70D__INCLUDED_)
