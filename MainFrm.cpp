/*
**	FILENAME			MainFrame.h
**
**	PURPOSE				此类为主窗口框架操作类，可用于更新
**						日期时间、PVSVPt100等参数
*/

#include "stdafx.h"
#include "Ptcr.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)

    ON_UPDATE_COMMAND_UI(ID_INDICATOR_DATE, OnUpdateDate)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_TIME, OnUpdateTime)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_PV, OnUpdatePV)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_SV, OnUpdateSV)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_PT100, OnUpdatePT100)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator

    ID_INDICATOR_DATE, 
	ID_INDICATOR_TIME,
ID_INDICATOR_PV,
ID_INDICATOR_SV,
ID_INDICATOR_PT100,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

//
//	窗口创建与消息响应
//
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
    CenterWindow();
    CTime dt=CTime::GetCurrentTime();
	m_Date=dt.Format("%Y年%m月%d日");
	m_Time=dt.Format("%H:%M:%S");

	m_PV.Format("设定温度:%+5.1f",0.0);
	m_SV.Format("测定温度:%+5.1f",25.0);
	m_PT100.Format("PT100温度:%+5.1f",25.0);
//   return 0;

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

//
//	创建窗口之前的操作
//
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	CRect rect;
	GetDesktopWindow()->GetClientRect(rect);
	cs.cx=rect.Width();
	cs.cy=rect.Height();
//	cs.style|=WS_MAXIMIZE;
//	cs.style^=(WS_MAXIMIZEBOX|WS_MINIMIZEBOX);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame 监测

//
//	日期更新
//
void CMainFrame::OnUpdateDate(CCmdUI *pCmdUI) 
{
    pCmdUI->Enable(); 
    pCmdUI->SetText( m_Date ); 
 }

//
//	时间更新
//
void CMainFrame::OnUpdateTime(CCmdUI *pCmdUI) 
{
    pCmdUI->Enable(); 
    pCmdUI->SetText( m_Time );
}

//
//	PV（设定温度）更新
//
void CMainFrame::OnUpdatePV(CCmdUI *pCmdUI) 
{
    pCmdUI->Enable(); 
    pCmdUI->SetText( m_PV ); 
 }

//
//	SV（测定温度）更新
//
void CMainFrame::OnUpdateSV(CCmdUI *pCmdUI) 
{
    pCmdUI->Enable(); 
    pCmdUI->SetText( m_SV ); 
 }

//
//	PT100温度更新
//
void CMainFrame::OnUpdatePT100(CCmdUI *pCmdUI) 
{
    pCmdUI->Enable(); 
    pCmdUI->SetText( m_PT100 ); 
 }
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

