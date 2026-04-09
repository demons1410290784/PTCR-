/*
**	FILENAME			CombinDlg.h
**
**	PURPOSE				此类可将两个文件中的相关数据合并到一个文件。
**						键入通道号或用逗号或-表示所选范围（如1，3，
**						6-10）后，将合并后对应通道显示在对话框下方的
**						文本框内
*/
#if !defined(AFX_COMBINDLG_H__1055DE82_5901_11D5_B28F_5254AB329367__INCLUDED_)
#define AFX_COMBINDLG_H__1055DE82_5901_11D5_B28F_5254AB329367__INCLUDED_

#include "rtsave.h"
#include "PtcrDoc.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CombinDlg.h : 头文件
//

/////////////////////////////////////////////////////////////////////////////
// CCombinDlg 对话框

class CCombinDlg : public CDialog
{
// 构造
public:
	int rt_num;
	int rt3_ChanNum;
	void SaveFile(CArchive &ar);
	void WriteChannels(int i,int j,int k,CString& str);
	int GetSubNum(CString str,int index);
	int GetDotNum(CString str,int index);
	void Open(CArchive& ar, CRTSave& rt,int num);
	CCombinDlg(CPtcrDoc *pDoc,CWnd* pParent = NULL);   // standard constructor
	CRTSave rtsave[3];
	BOOL OpenOk;
	BOOL FileOpen[3];
	BOOL bChannelSelected[3][NMBOFSPL];
	CString FileName[3],FileCha[3];
	CString strpara;
	int ChaNum[3];
//	("",1000)
// 对话框数据
	//{{AFX_DATA(CCombinDlg)
	enum { IDD = IDD_COMBINEDLG };
	CEdit	m_File3Channel;
	CEdit	m_File2Channel;
	CEdit	m_File2Edit;
	CEdit	m_File1Channel;
	CEdit	m_File1Edit;
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCombinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// 实现
protected:

	// 生成的消息映射函数
	//{{AFX_MSG(CCombinDlg)
	afx_msg void OnFile1Cmd();
	afx_msg void OnFile2Cmd();
	virtual void OnOK();
	afx_msg void OnKillfocusFile1Edit();
	afx_msg void OnKillfocusFile2Edit();
	afx_msg void OnKillfocusFile1Edit2();
	afx_msg void OnKillfocusFile2Edit2();
	afx_msg void OnUpdateFile3Edit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBINDLG_H__1055DE82_5901_11D5_B28F_5254AB329367__INCLUDED_)
