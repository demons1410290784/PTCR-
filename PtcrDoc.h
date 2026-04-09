/*
**	FILENAME			PtcrDoc.h
**
**	PURPOSE				此类可用于文档相关的操作，包含文件
**						的打开与保存、文件的修改以及命令/信
**						号的读取与写入的等
*/

#if !defined(AFX_PTCRDOC_H__1031080E_5067_11D5_B28F_5254AB329367__INCLUDED_)
#define AFX_PTCRDOC_H__1031080E_5067_11D5_B28F_5254AB329367__INCLUDED_

#include "rt.h"
#include "SerialPort.h"	// Added by ClassView
#include "PtcrDoc.h"

#include"dos.h"//by zj
#include "ParaPort.h"//by zj
#include "WinIo.h"//by zj
#include "windows.h"//by zj
#include "stdio.h"//by zj

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//CString m_setusername;
#define NMBOFSPL 30 /*SAMPLE NUMBER*/
#define MULNMBOFSPL 30 //8-24 oyj 画多曲线数量
#define MAXOFSPL 200 /*SAMPLE TEMPERATURE NUMBER*/


class CPtcrDoc : public CDocument
{
protected: // create from serialization only
	CPtcrDoc();
	DECLARE_DYNCREATE(CPtcrDoc)

// 属性
public:
//	CRT m_rt;
	CSerialPort m_sPort;
	CSerialPort m_sPortF45;
	BOOL OpenFlag;//TRUE 文件打开成功;False 文件打开失败;
    float stemp[MAXOFSPL];	
	bool m_Running;
	void LoadIndex(int i=100);
	int GetIndex();
    void OutChan(int ch1);
    void OutChan8255(int ch);
    void OutChanHT12D(int ch1);
	void outa12(int j);
    void codd12(int nb,char da);

    void SetC(int ch,int set);
    void Init8253(void);
//zjun 2002/8/5
    void StopHeat(void);
    int TempRange(float tm);
    int Pid(int diff,int b);
    void Heat(int wn);


private:
	float yc0[MAXOFSPL];
	float xc0[MAXOFSPL];
	int m_iIndex;
// 操作
public:

// 重载
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPtcrDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	//}}AFX_VIRTUAL

// 实现
public:
	int OSver;
	int GetOSVersion();
	float m_Tempvias;
	int Pidtime;
    int SetSr93(char *cmd, float temp, int Coefficient) ;
    int SetSr93Temp(float temp);
	int SrRead(char *cmd,int *Read);
    int SrWrite(char *cmd);
	int HexToi(char *Hex);
    int iToHex(char *Hex,int j);

	BOOL SavePtcRtIni();
	float GetOptimizeRes(int j0,int j1,int j2,float t);
	int heatstop;//停止加热标志
	int HeatCool;
	int Pt100Chan_2;//Pt100_2
	int Pt100Chan_1;//Pt100_1
	int w2w4;//双通道或四通道标志
	CRT m_rt;
	int CPptc;//0 陶瓷PTC, 1 高分子PTC
	int m_HT12D;//0 8255; 1 HT12D
	int DigitController; //0 无温控表, 1 SR253;
	int MultiMeter;//0无万用表; 1 FLUKE45, 2 Tonghui2512, 3 Esort3146A, 4 34401A,5 2000
    int ZWX; //0 ZWX-B,   1 ZWX-C
	
	int HeatLimit;//加热限制
	int	HeatRate;
	int	HeatStep;//最小加热步长
    float KP,KD,KI;

	
//	BOOL m_filesaveas;

	float GetspecialRes(int,int,int,float);
	bool OnPlot_Renew;
	bool m_SaveAs;
	virtual ~CPtcrDoc();
 
	float m_PV,m_SV,m_Resistance;
	int STARTDOT;
	float m_Pt100;
	int m_SvNum;
    void ReadSr253(); 
	bool ChanSet;
    void DelayTime(int sec);
    float ReadResiRepeat(int n); 
    int ReadResi(char * results) ;
    int Splint(char buftmp[10][35], char *results, int Sr253BCC);
	float ReadPt100(int ChanNo); 

	float	m_Pt100_1;
	float	m_Pt100_2;
	float	m_Pt100_3;
	float	m_Pt;

 

	int m_ReadingF45;//=1 读温度, =0 读电阻值

	void AddCrc(char * cmd,int Sr253BCC);
    void CalculateCRC(char *buf,char *crc,int Sr253BCC);
	bool Verify( char * strS,int Sr253BCC );
	bool ReadPvsv(char * cmd, char * results, int wTime, int wCount,int Sr253BCC);
    float Temperature(float Resistance0,float tt00);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息处理函数
protected:
	//{{AFX_MSG(CPtcrDoc)
	afx_msg void OnUpdateToolConbind(CCmdUI* pCmdUI);
	afx_msg void OnToolConvert();
	afx_msg void OnUpdateToolConvert(CCmdUI* pCmdUI);
	afx_msg void OnToolConvertExcel();
	afx_msg void OnUpdateToolConvertExcel(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnMenuSetUser();
	afx_msg void OnAppExit();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PTCRDOC_H__1031080E_5067_11D5_B28F_5254AB329367__INCLUDED_)
