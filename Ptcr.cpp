/*
**	FILENAME			Ptcr.cpp
**
**	PURPOSE				此类包括主程序初始化以及“帮助”对话框。
**						打开主窗口前该类会作为主程序入口
*/

#include "stdafx.h"
#include "Ptcr.h"

#include "MainFrm.h"
#include "PtcrDoc.h"
#include "PtcrView.h"
#include "Login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPtcrApp

BEGIN_MESSAGE_MAP(CPtcrApp, CWinApp)
	//{{AFX_MSG_MAP(CPtcrApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPtcrApp 构造函数

CPtcrApp::CPtcrApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// 唯一的CPtcrApp对象

CPtcrApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPtcrApp 初始化

BOOL CPtcrApp::InitInstance()
{ 
	CLogin login;  // 8-19
	if(login.DoModal()==IDOK)
	{
		if(login.m_pass==TRUE)
			;
		else 
			return FALSE;
	}
    else
		return FALSE;
	AfxEnableControlContainer();

	// 标准初始化程序：
	// 如果不使用这些功能并希望减小最终
	// 可执行文件的大小，则应从以下中删
	// 除不需要的特定初始化例程。

#ifdef _AFXDLL
	Enable3dControls();			// 在一个共享dll中使用MFC时调用这个函数
#else
	Enable3dControlsStatic();	// 静态链接到 MFC 时调用此函数
#endif

	// 更改存储设置的注册表项。
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // 加载标准INI文件选项(包括MRU)

	// 注册应用程序的文档模板。 
	// 文档模板充当文档、框架窗口和视图之间的连接。

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPtcrDoc),
		RUNTIME_CLASS(CMainFrame),       // 主SDI框架窗口
		RUNTIME_CLASS(CPtcrView));
	AddDocTemplate(pDocTemplate);

	// 解析标准外壳命令、DDE、文件打开的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// 在命令行上指定的调度命令
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的窗口初始化后，显示并更新。
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// 用于“关于”选项的CAboutDlg对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// 构造函数：打开“关于”对话框

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////////
// 对话框数据交换

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog

/////////////////////////////////////////////////////////////////////////////
// 调用“关于”选项

void CPtcrApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPtcrApp message handlers

