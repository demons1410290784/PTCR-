/*
**	FILENAME			CSerialPort.h
**
**	PURPOSE				此类可以读取、写入和监视一个串行端口。当端口上发生
**						某些事件时，它会向其所有者发送消息。该类创建一个用
**						于读取和写入的线程，以便主程序不会被阻止。
**
**	CREATION DATE		15-09-1997
**	LAST MODIFICATION	12-11-1997
**
**	AUTHOR				Li Buyin
**
**
*/

#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

#define WM_COMM_BREAK_DETECTED		WM_USER+1	// 在输入时检测到中断。
#define WM_COMM_CTS_DETECTED		WM_USER+2	// CTS（清除发送）信号已更改状态。
#define WM_COMM_DSR_DETECTED		WM_USER+3	// DSR（数据集就绪）信号已更改状态。 
#define WM_COMM_ERR_DETECTED		WM_USER+4	// 发生线路状态错误。线路状态错误包括CE_FRAME、CE_OVERRUN和CE_RXPARITY。 
#define WM_COMM_RING_DETECTED		WM_USER+5	// 检测到振铃指示器。 
#define WM_COMM_RLSD_DETECTED		WM_USER+6	// RLSD（接收线路信号检测）信号更改状态。 
#define WM_COMM_RXCHAR				WM_USER+7	// 接收到一个字符并将其放置在输入缓冲区中。
#define WM_COMM_RXFLAG_DETECTED		WM_USER+8	// 事件字符已接收并放置在输入缓冲区中。  
#define WM_COMM_TXEMPTY_DETECTED	WM_USER+9	// 发送输出缓冲区中的最后一个字符。 
#define WM_COMM_RXLINE              WM_USER+10


class CSerialPort
{														 
public:
	// 构造与析构
	CSerialPort();
	virtual		~CSerialPort();

	// 端口初始化											
	BOOL		InitPort(CWnd* pPortOwner);

	// 开始/停止监视线程
	BOOL		StartMonitoring();
	BOOL		RestartMonitoring();
	BOOL		StopMonitoring();

	DWORD		GetWriteBufferSize();
	DWORD		GetCommEvents();
	DCB			GetDCB();

	void		WriteToPort(char* string);
	CWnd*				m_pOwner;

protected:
	// 受保护的成员函数
	void	ProcessErrorMessage(char* ErrorText);
	static UINT	CommThread(LPVOID pParam);
	static void	ReceiveChar(CSerialPort* port, COMSTAT comstat);
	static void	WriteChar(CSerialPort* port);

	// 线程
	CWinThread*			m_Thread;

	// 同步对象
	CRITICAL_SECTION	m_csCommunicationSync;
	BOOL				m_bThreadAlive;

	// 句柄
	HANDLE				m_hShutdownEvent;
	HANDLE				m_hComm;
	HANDLE				m_hWriteEvent;

	// 事件数组. 
	// 每个事件使用一个元素。每个端口有两个事件句柄。 
	// 一个写入事件和一个位于重叠结构 （m_ov.hEvent ） 中的接收字符事件。 
	// 当端口关闭时，通常会关闭。
	HANDLE				m_hEventArray[3];

	// 结构体
	OVERLAPPED			m_ov;
	COMMTIMEOUTS		m_CommTimeouts;

	// 杂项
    
	char*				m_szWriteBuffer;
    
	//用户定义
public:
	bool m_SPAvailable;
	DWORD		 m_nWriteBufferSize;
	DWORD		 m_dwCommEvents;
	DCB			 m_dcb;
	UINT		 m_nPortNr;
    struct rxline{
	   bool theend;
	   int  count;
	   int  Sr253BCC;
	   char results[128];
	   int m_MultiMeter;
	   int sr;
	}m_rxdata;
    //Sr253BCC=2,Sr253,STX-ETX-CR,SR25CMD;
	// Sr253BCC=4,Sr=93,Sr93;=83,SR83 @+:+BCC+CR,BCC ADD
	int m_baudno;
	int m_stopno;
	int m_datano;
	int m_parityno;
    char stopbits[3][4];
	char baudrate[7][6];
	char databits[3][2];
	char parity[5][2];

	DWORD dwError;


};

#endif __SERIALPORT_H__


