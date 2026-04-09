/*
**	FILENAME			SelPrintData.h
**
**	PURPOSE				此类可用于打印数据的选择，选项包含“打印原始测试数据”
**						、“打印温度取整后测试记录”和“不打印原始测试数据”
*/

#if !defined(AFX_SELPRINTDATA_H__E952A25C_3296_418E_96BB_2437DFE425F7__INCLUDED_)
#define AFX_SELPRINTDATA_H__E952A25C_3296_418E_96BB_2437DFE425F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelPrintData.h : 头文件
//

/////////////////////////////////////////////////////////////////////////////
// SelPrintData对话框

class SelPrintData : public CDialog
{
// 构造
public:
	int m_PriStyle;
	SelPrintData(CWnd* pParent = NULL);   // 标准构造函数

// 对话框数据
	//{{AFX_DATA(SelPrintData)
	enum { IDD = IDD_SELPRINTDATA };
	int		m_order;
	//}}AFX_DATA


// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelPrintData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// 实现
protected:

	// 生成的消息响应函数
	//{{AFX_MSG(SelPrintData)
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELPRINTDATA_H__E952A25C_3296_418E_96BB_2437DFE425F7__INCLUDED_)
