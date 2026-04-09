/*
**	FILENAME			MainFrame.h
**
**	PURPOSE				此类为主窗口框架操作类，可用于更新
**						日期时间、PVSVPt100等参数
*/

#if !defined(AFX_MAINFRM_H__1031080C_5067_11D5_B28F_5254AB329367__INCLUDED_)
#define AFX_MAINFRM_H__1031080C_5067_11D5_B28F_5254AB329367__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 属性
public:
	CString m_Date;
	CString m_Time;
	CString m_PV;
	CString m_SV;
	CString m_PT100;
// 操作
public:

// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控制栏嵌入成员
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// 生成的消息处理函数
protected:
	//{{AFX_MSG(CMainFrame)
    afx_msg void OnUpdateDate(CCmdUI *pCmdUI);
    afx_msg void OnUpdateTime(CCmdUI *pCmdUI);
    afx_msg void OnUpdatePV(CCmdUI *pCmdUI);
    afx_msg void OnUpdateSV(CCmdUI *pCmdUI);
    afx_msg void OnUpdatePT100(CCmdUI *pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnAppExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1031080C_5067_11D5_B28F_5254AB329367__INCLUDED_)
