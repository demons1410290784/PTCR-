/*
**	FILENAME			DataOptize.h
**
**	PURPOSE				此类可以将曲线中个别点进行修正，通过
**						修改各个拟合点的编号与数值，计算待拟
**						合点的拟合值并进行保存
*/

#if !defined(AFX_DATAOPTIZE_H__97F0E681_DF85_11D6_8AF8_0010DC39A4A9__INCLUDED_)
#define AFX_DATAOPTIZE_H__97F0E681_DF85_11D6_8AF8_0010DC39A4A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataOptize.h : 头文件
//

/////////////////////////////////////////////////////////////////////////////
// CDataOptize对话框
#include "PtcrDoc.h"
class CDataOptize : public CDialog
{
// 构造
public:
	float m_InsteadResVal;
	CDataOptize(CPtcrDoc* pDoc,CWnd* pParent = NULL);   // 标准构造函数
    CPtcrDoc *m_pDoc;
// 对话框数据
	//{{AFX_DATA(CDataOptize)
	enum { IDD = IDD_OPTIMIZE };
	CEdit	m_COptiData;
	CEdit	m_CfirstData;
	CString	m_firstData;
	CString	m_secondData;
	CString	m_OptiData;
	CString	m_fourthData;
	CString	m_fifthData;
	UINT	m_num1;
	UINT	m_num2;
	UINT	m_num4;
	UINT	m_num5;
	CString	m_DataNum3;
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataOptize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// 生成的消息响应函数
	//{{AFX_MSG(CDataOptize)
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpin4(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnUpdateEdit6();
	afx_msg void OnDeltaposSpin5(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAOPTIZE_H__97F0E681_DF85_11D6_8AF8_0010DC39A4A9__INCLUDED_)
