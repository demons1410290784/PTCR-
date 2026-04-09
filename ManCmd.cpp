/////////////////////////////////////////////////////////////////////////////
// CManCmd dialog


CManCmd::CManCmd(CWnd* pParent /*=NULL*/)
	: CDialog(CManCmd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManCmd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CManCmd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManCmd)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CManCmd, CDialog)
	//{{AFX_MSG_MAP(CManCmd)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManCmd message handlers
