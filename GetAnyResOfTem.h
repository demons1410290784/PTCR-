/*
**	FILENAME			GetAnyResOfTem.h
**
**	PURPOSE				此类可唤起“获取任意温度阻值”对话框，点击“确认”键
**						时，可根据设置的通道号与温度，读取样品名称和电阻值显
**						示在对应的文本框内
*/

#if !defined(AFX_GETANYRESOFTEM_H__11275FA0_A3A6_11D6_822C_5254AB1E742B__INCLUDED_)
#define AFX_GETANYRESOFTEM_H__11275FA0_A3A6_11D6_822C_5254AB1E742B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetAnyResOfTem.h : 头文件
//

/////////////////////////////////////////////////////////////////////////////
#include "PtcrDoc.h"
// CGetAnyResOfTem对话框

class CGetAnyResOfTem : public CDialog
{
// 构造
public:
	CPtcrDoc *m_pDoc;

    CGetAnyResOfTem(CPtcrDoc* pDoc,CWnd* pParent = NULL);
// 对话框数据
	//{{AFX_DATA(CGetAnyResOfTem)
	enum { IDD = IDD_AnyTemToRes };
	CString	m_ResVal;
	UINT	m_ChanNum;
	float	m_TemVal;
	CString	m_SampleName;
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetAnyResOfTem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// 实现
protected:

	// 生成的消息响应函数
	//{{AFX_MSG(CGetAnyResOfTem)
	afx_msg void OnDeltaposSpinChanNum(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETANYRESOFTEM_H__11275FA0_A3A6_11D6_822C_5254AB1E742B__INCLUDED_)
