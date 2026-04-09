/*
**	FILENAME			Ptcr.h
**
**	PURPOSE				PTCR测试系统的主头文件。
**						打开主窗口前该类会作为主程序入口
*/

#if !defined(AFX_PTCR_H__10310808_5067_11D5_B28F_5254AB329367__INCLUDED_)
#define AFX_PTCR_H__10310808_5067_11D5_B28F_5254AB329367__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPtcrApp:
// 该类的实现方法详见Ptcr.cpp
//

class CPtcrApp : public CWinApp
{
public:
	CPtcrApp();

// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPtcrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// 实现
	//{{AFX_MSG(CPtcrApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTCR_H__10310808_5067_11D5_B28F_5254AB329367__INCLUDED_)
