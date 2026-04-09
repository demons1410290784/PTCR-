/*
**	FILENAME			CSerialPort.cpp
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

#include "stdafx.h"
#include "SerialPort.h"

#include <assert.h>
 
//
// 构造函数
//
CSerialPort::CSerialPort()
{
	m_hComm = NULL;

	// 将重载的结构成员初始化为零
	m_ov.Offset = 0;
	m_ov.OffsetHigh = 0;

	// 创造事件
	m_ov.hEvent = NULL;
	m_hWriteEvent = NULL;
	m_hShutdownEvent = NULL;

	m_szWriteBuffer = NULL;

	m_bThreadAlive = FALSE;

    m_dwCommEvents=0;
	m_dwCommEvents|= EV_RXCHAR;
	m_nWriteBufferSize=255;
  
//    m_baudno=4; //1200

	//lby    m_nPortNr=0;     //com1
//	m_stopno=0; // 1 stopbit
//	m_parityno=2; //EVEN
//	m_datano=1; // 7 databits

	sprintf(baudrate[0],"19200");
	sprintf(baudrate[1],"9600");
	sprintf(baudrate[2],"4800");
	sprintf(baudrate[3],"2400");
	sprintf(baudrate[4],"1200");
	sprintf(baudrate[5],"600");
	sprintf(baudrate[6],"300");
	
	strcpy(stopbits[0],"1");
	strcpy(stopbits[1],"1.5");
	strcpy(stopbits[2],"2");
	
	strcpy(databits[0],"8");
	strcpy(databits[1],"7");
	strcpy(databits[2],"6");
    
	strcpy(parity[0],"N");
	strcpy(parity[1],"O");
	strcpy(parity[2],"E");
	strcpy(parity[3],"M");
	strcpy(parity[4],"S");

    m_SPAvailable=FALSE;
}

//
// 析构函数：删除动态内存
//
CSerialPort::~CSerialPort()
{
	do
	{
		SetEvent(m_hShutdownEvent);
	} while (m_bThreadAlive);

	TRACE("Thread ended\n");
        m_SPAvailable=FALSE;

	delete [] m_szWriteBuffer;
}

//
// 初始化端口. 
//
BOOL CSerialPort::InitPort(CWnd* pPortOwner)		
{
	assert(pPortOwner != NULL);

	// 结束活跃的线程
	if (m_bThreadAlive)
	{
		do
		{
			SetEvent(m_hShutdownEvent);
		} while (m_bThreadAlive);
		TRACE("Thread ended\n");
	}

	// 创造事件
	if (m_ov.hEvent != NULL)
		ResetEvent(m_ov.hEvent);
	m_ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_hWriteEvent != NULL)
		ResetEvent(m_hWriteEvent);
	m_hWriteEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	if (m_hShutdownEvent != NULL)
		ResetEvent(m_hShutdownEvent);
	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	// 初始化事件对象
	m_hEventArray[0] = m_hShutdownEvent;	// 优先级最高
	m_hEventArray[1] = m_ov.hEvent;
	m_hEventArray[2] = m_hWriteEvent;

	// 初始化关键部分
	InitializeCriticalSection(&m_csCommunicationSync);
	
	// 设置写入的缓冲区大小并保存所有者
	m_pOwner = pPortOwner;

	if (m_szWriteBuffer != NULL)
		delete [] m_szWriteBuffer;
	m_szWriteBuffer = new char[m_nWriteBufferSize];
	
	BOOL bResult = FALSE;

	char szPort[10];

	//关键部分!
	EnterCriticalSection(&m_csCommunicationSync);

	// 若端口已开启则将其关闭
	if (m_hComm != NULL)
	{
		CloseHandle(m_hComm);
		m_hComm = NULL;
	}

	// 准备端口指令字符串
	sprintf(szPort, "COM%d", m_nPortNr+1);
	
	// 获取端口的句柄
	m_hComm = CreateFile(szPort,						// 通信端口字符串 （COMX）
					     GENERIC_READ | GENERIC_WRITE,	// 读/写类型
					     0,								// 通信设备必须以独占访问权限打开
					     NULL,							// 无安全属性
					     OPEN_EXISTING,					// 通信设备必须使用OPEN_EXISTING
					     FILE_FLAG_OVERLAPPED,			// 异步 I/O
					     0);							// 通信设备的模板必须为 0

	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		// 如未找到端口
        m_SPAvailable=FALSE;
		return FALSE;
	}

	// 设置超时值
	m_CommTimeouts.ReadIntervalTimeout = 1000;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 1000;
	m_CommTimeouts.ReadTotalTimeoutConstant = 1000;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 1000;
	m_CommTimeouts.WriteTotalTimeoutConstant = 1000;

	// 配置
	char szBaud[50];
	sprintf(szBaud,"baud=%s parity=%s data=%s stop=%s",\
		         baudrate[m_baudno],\
				 parity[m_parityno],\
				 databits[m_datano],\
				 stopbits[m_stopno]);

	if (SetCommTimeouts(m_hComm, &m_CommTimeouts))
	{						   
		if (SetCommMask(m_hComm, m_dwCommEvents))
		{
			if (GetCommState(m_hComm, &m_dcb))
			{
				m_dcb.fRtsControl = RTS_CONTROL_ENABLE;		// 设置高位RTS
				if (BuildCommDCB(szBaud, &m_dcb))
				{
					if (SetCommState(m_hComm, &m_dcb))
						; // 通常操作... 
					else
						ProcessErrorMessage("SetCommState()");
				}
				else
					ProcessErrorMessage("BuildCommDCB()");
			}
			else
				ProcessErrorMessage("GetCommState()");
		}
		else
			ProcessErrorMessage("SetCommMask()");
	}
	else
		ProcessErrorMessage("SetCommTimeouts()");

	// 刷新端口
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	// 发布关键部分
	LeaveCriticalSection(&m_csCommunicationSync);

	TRACE("Initialisation for communicationport %d completed.\nUse Startmonitor to communicate.\n", m_nPortNr);

	m_SPAvailable=TRUE;
	return TRUE;
}

//
//  监视线程函数.
//
UINT CSerialPort::CommThread(LPVOID pParam)
{
	// 将传递给线程的 void 指针转换回 CSerialPort 类的指针
	CSerialPort *port = (CSerialPort*)pParam;
	
	// 将对话框类中的状态变量设置为 TRUE 以指示线程正在运行
	port->m_bThreadAlive = TRUE;	
		
	// 杂项变量
	DWORD BytesTransfered = 0; 
	DWORD Event = 0;
	DWORD CommEvent = 0;
	COMSTAT comstat;
	BOOL  bResult = TRUE;
//lby	DWORD	dwError = 0;

	port->dwError = 0;
		
	// 启动时清除通信缓冲区
	if (port->m_hComm)		// 检查端口开闭
		PurgeComm(port->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	// 开始死循环： 只要线程处于活动状态，此循环就会运行
	for (;;) 
	{ 

		// 调用 WaitCommEvent（）。 此调用将立即返回，因为我们
		// 的端口是创建为异步端口（FILE_FLAG_OVERLAPPED和指定的
		// m_OverlappedStructerlapped结构）。 此调用将导致
		// m_OverlappedStructerlapped元素 m_OverlappedStruct.hEvent
		// （如果m_hEventArray的一部分）处于无符号状态（如果没有可用
		// 字节），则置于有符号状态，如果有可用字节，则将其置于有符
		// 号状态。 如果此事件句柄设置为非签名状态，则当字符到达端口
		// 时，它将设置为已签名。


		// 对每个端口执行此操作

		bResult = WaitCommEvent(port->m_hComm, &Event, &port->m_ov);

		if (!bResult)  
		{ 
			// 如果 WaitCommEvent()返回 FALSE，则处理最后一个错误以确定原因。
//lby			switch (dwError = GetLastError()) 
			switch (port->dwError = GetLastError()) 
			{ 
			case ERROR_IO_PENDING: 	
				{ 
					// 如果端口上没有要读取的字节，则这是正常的返回值。
					// 什么都不做，继续
					break;
				}
			case 87:
				{
					// 在 Windows NT 下，由于某种原因返回此值。 我没有调查为
					// 什么，但它也是一个有效的回复
					// 同样什么都不做，继续。
					break;
				}
			default:
				{
					// 所有其他错误代码表示发生了严重错误。 处理此错误。
					port->ProcessErrorMessage("WaitCommEvent()");
					break;
				}
			}
		}
		else
		{
			// 如果 WaitCommEvent()返回TRUE，请检查以确保缓冲区中确实有要读取的字节。 
			//
			// 如果您一次从缓冲区读取多个字节（此程序不这样做），则会出现第一个字节到
			// 达将导致 WaitForMultipleObjects()函数停止等待的情况。 
			// WaitForMultipleObjects() 函数在返回时将m_OverlappedStruct.hEvent中的事
			// 件句柄重置为非 signelead 状态。  
			//
			// 如果在重置此事件和调用 ReadFile()之间的时间内有更多字节到达，则 
			// m_OverlappedStruct.hEvent 句柄将再次设置为已签名状态。当调用 ReadFile()
			// 时，它将从缓冲区读取所有字节，程序将循环回 WaitCommEvent()。
			// 
			// 此时，您将处于设置了 m_OverlappedStruct.hEvent 的情况，但没有可供读取的
			// 字节。 如果继续并调用 ReadFile()，由于异步端口设置，它将立即返回，但 
			// GetOverlappedResults()在下一个字符到达之前不会返回。
			//
			// 我们不希望GetOverlappedResults()函数处于此状态。如果线程被
			// GetOverlappedResults()阻止，则线程关闭事件(事件 0)和 WriteFile()事件
			// (Event2)将不起作用。
			//
			// 对此的解决方案是通过调用ClearCommError()来检查缓冲区。此调用将重置事件句
			// 柄，如果没有要读取的字节，我们可以再次循环回 WaitCommEvent()，然后继续。
			// 如果确实有字节要读取，则不执行任何操作并继续。
		
//lby			bResult = ClearCommError(port->m_hComm, &dwError, &comstat);
			bResult = ClearCommError(port->m_hComm, &port->dwError, &comstat);

			if (comstat.cbInQue == 0)
			{
				ResetEvent(port->m_ov.hEvent);
				continue;
			}
		}	// end if bResult

		// 主等待功能。 此函数通常会阻塞线程，直到发生需要操作的九个事件之一。
		Event = WaitForMultipleObjects(3, port->m_hEventArray, FALSE, INFINITE);
		switch (Event)
		{
		case 0:
			{
				// 关闭事件。 这是事件0，优先级别最高，首先进行处理。

			 	port->m_bThreadAlive = FALSE;
				
				// 结束这个线程。 这里不需要break，但可以让代码可读性更好。
				AfxEndThread(100);
				break;
			}
		case 1:	// 读事件
			{
				GetCommMask(port->m_hComm, &CommEvent);
				if (CommEvent & EV_CTS)
					::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_CTS_DETECTED, (WPARAM) 0, (LPARAM) port->m_nPortNr);
				if (CommEvent & EV_RXFLAG)
					::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_RXFLAG_DETECTED, (WPARAM) 0, (LPARAM) port->m_nPortNr);
				if (CommEvent & EV_BREAK)
					::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_BREAK_DETECTED, (WPARAM) 0, (LPARAM) port->m_nPortNr);
				if (CommEvent & EV_ERR)
					::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_ERR_DETECTED, (WPARAM) 0, (LPARAM) port->m_nPortNr);
				if (CommEvent & EV_RING)
					::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_RING_DETECTED, (WPARAM) 0, (LPARAM) port->m_nPortNr);
				
				if (CommEvent & EV_RXCHAR)
					// 从端口接收字符事件。
					ReceiveChar(port, comstat);
					
				break;
			}  

		case 2: // 写事件
			{
				// 从端口写入字符事件
				WriteChar(port);
				break;
			}
		} // end switch

	} // 结束死循环

	return 0;
}

//
// 开始监视线程
//
BOOL CSerialPort::StartMonitoring()
{
	if (!(m_Thread = AfxBeginThread(CommThread, this)))
		return FALSE;
	TRACE("Thread started\n");
	return TRUE;	
}

//
// 从挂起恢复监视线程
//
BOOL CSerialPort::RestartMonitoring()
{
	TRACE("Thread resumed\n");
	m_Thread->ResumeThread();
	return TRUE;	
}


//
// 挂起监视线程
//
BOOL CSerialPort::StopMonitoring()
{
	TRACE("Thread suspended\n");
	m_Thread->SuspendThread(); 
	return TRUE;	
}


//
// 错误消息提示函数
//
void CSerialPort::ProcessErrorMessage(char* ErrorText)
{
	char *Temp = new char[200];
	
	LPVOID lpMsgBuf;

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

	sprintf(Temp, "WARNING:  %s Failed with the following error: \n%s\nPort: %d\n", (char*)ErrorText, lpMsgBuf, m_nPortNr); 
	MessageBox(NULL, Temp, "Application Error", MB_ICONSTOP);

	LocalFree(lpMsgBuf);
	delete[] Temp;
}

//
// 写一个字符串.
//
void CSerialPort::WriteChar(CSerialPort* port)
{
	BOOL bWrite = TRUE;
	BOOL bResult = TRUE;

	DWORD BytesSent = 0;
	DWORD  i;//lby

	ResetEvent(port->m_hWriteEvent);

	// 获得关键部分的所有权
	EnterCriticalSection(&port->m_csCommunicationSync);

	if (bWrite)
	{
		// 变量初始化
		port->m_ov.Offset = 0;
		port->m_ov.OffsetHigh = 0;

		// 清理缓存
		PurgeComm(port->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

		bResult = WriteFile(port->m_hComm,							// 线程端口的句柄
							port->m_szWriteBuffer,					// 指向调用函数中消息缓冲区的指针
							strlen((char*)port->m_szWriteBuffer),	// 发送消息的长度
							&BytesSent,								// 存储发送的字节数的位置
							&port->m_ov);							// 结构体重载

		// 处理错误代码
		if (!bResult)  
		{
//lby			DWORD dwError = GetLastError();
			port->dwError = GetLastError();//lby
			switch (port->dwError)
			{
				case ERROR_IO_PENDING:
					{
						// continue to GetOverlappedResults()
						BytesSent = 0;
						bWrite = FALSE;
						break;
					}
				default:
					{
						// all other error codes
						port->ProcessErrorMessage("WriteFile()");
					}
			}
		} 
		else
		{
			LeaveCriticalSection(&port->m_csCommunicationSync);
		}
	} // end if(bWrite)

	if (!bWrite)
	{
		bWrite = TRUE;
	
		bResult = GetOverlappedResult(port->m_hComm,	// Handle to COMM port 
									  &port->m_ov,		// Overlapped structure
									  &BytesSent,		// Stores number of bytes sent
									  TRUE); 			// Wait flag

		LeaveCriticalSection(&port->m_csCommunicationSync);

		// deal with the error code 
		if (!bResult)  
		{
			port->ProcessErrorMessage("GetOverlappedResults() in WriteFile()");
		}	
	} // end if (!bWrite)

	// Verify that the data size send equals what we tried to send
		
	if (BytesSent != strlen((char*)port->m_szWriteBuffer))
	{
		i=strlen((char*)port->m_szWriteBuffer);
	BytesSent=port->m_ov.InternalHigh;
	if(i!=BytesSent)TRACE("WARNING: WriteFile() error.. Bytes Sent: %d; Message Length: %d\n", BytesSent, strlen((char*)port->m_szWriteBuffer));
	}
}

//
// 接受字符
//
void CSerialPort::ReceiveChar(CSerialPort* port, COMSTAT comstat)
{
	BOOL  bRead = TRUE; 
	BOOL  bResult = TRUE;
//lby 10/05/2002	DWORD


	port->dwError = 0;

	DWORD BytesRead = 0;
	unsigned char RXBuff;
	CString Receivedstring;

	Receivedstring.Empty();

	for (;;) 
	{ 
		// 获得通信端口关键部分的所有权。此过程保证此程序的其他部分不使用端口对象。
		
		EnterCriticalSection(&port->m_csCommunicationSync);

		// ClearCommError()将更新 COMSTAT 结构并清除任何其他错误

		//lby		bResult = ClearCommError(port->m_hComm, &dwError, &comstat);
		
		bResult = ClearCommError(port->m_hComm, &port->dwError, &comstat);

		LeaveCriticalSection(&port->m_csCommunicationSync);

		// 开始死循环。在不知道在运行时必须运行多少个循环时可以使用这种类型的循环，
		// 并在处理完所有可用数据后打破它。 
		// 这个解决方案是最有效的方法。
		
		if (comstat.cbInQue == 0)
		{
			// 读取所有字节后退出循环
            ResetEvent(port->m_ov.hEvent);
			break;
		}
						
		EnterCriticalSection(&port->m_csCommunicationSync);
   
		if (bRead)
		{
			bResult = ReadFile(port->m_hComm,		// COMM端口句柄 
							   &RXBuff,				// RX缓冲区指针
							   1,					// 读一个字节
							   &BytesRead,			// 存储读取的字节数
							   &port->m_ov);		// 指向m_ov结构的指针
   Receivedstring+=RXBuff;
			// 处理错误代码
			if (!bResult)  
			{ 
				switch (port->dwError = GetLastError()) 
				{ 
					case ERROR_IO_PENDING: 	
						{ 
							// 异步i/o仍在进程中 
							// 继续GetOverlappedResults();
							bRead = FALSE;
							break;
						}
					default:
						{
							// 产生了其他的错误.处理此错误.
							port->ProcessErrorMessage("ReadFile()");
							break;
						} 
				}
			}
			else
			{
				// ReadFile()返回完毕.无需再调用GetOverlappedResults()
				bRead = TRUE;
			}
		}  // close if (bRead)

		if (!bRead)
		{
			bRead = TRUE;
			bResult = GetOverlappedResult(port->m_hComm,	// COMM端口指针
										  &port->m_ov,		// 重载结构体
										  &BytesRead,		// 存储读取的字节数
										  TRUE); 			// 等待标志

			// 处理错误代码 
			if (!bResult)  
			{
				port->ProcessErrorMessage("GetOverlappedResults() in ReadFile()");
			}	
		}  // close if (!bRead)
				
		LeaveCriticalSection(&port->m_csCommunicationSync);

		// 通知父级已收到字节
		if(!port->m_rxdata.theend)
		{
			port->m_rxdata.results[port->m_rxdata.count++]=RXBuff;

if((port->m_rxdata.m_MultiMeter==1)&&(RXBuff=='\n'&&port->m_rxdata.results[port->m_rxdata.count-2]=='\r'&&port->m_rxdata.results[port->m_rxdata.count-3]=='>'&&port->m_rxdata.results[port->m_rxdata.count-4]=='='))
			{//FLUKE45
			   port->m_rxdata.results[port->m_rxdata.count]=0;
			   port->m_rxdata.theend=TRUE;
			   ::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXLINE, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
			}
			else if((port->m_rxdata.m_MultiMeter==5)&&(RXBuff=='\n'))
			{//2000
			   port->m_rxdata.results[port->m_rxdata.count]=0;
			   port->m_rxdata.theend=TRUE;
			   ::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXLINE, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
			}
		    else if((port->m_rxdata.m_MultiMeter==4)&&(RXBuff=='\n'&&port->m_rxdata.results[port->m_rxdata.count-2]=='\r'))
			{//34401
			   port->m_rxdata.results[port->m_rxdata.count]=0;
			   port->m_rxdata.theend=TRUE;
			   ::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXLINE, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
			}
		    else if((port->m_rxdata.m_MultiMeter==3)&&(RXBuff=='\r'&&port->m_rxdata.results[port->m_rxdata.count-2]=='>'))
			{//3146
			   port->m_rxdata.results[port->m_rxdata.count]=0;
			   port->m_rxdata.theend=TRUE;
			   ::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXLINE, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
			}
			else if((port->m_rxdata.Sr253BCC==1)&&(RXBuff=='\r'))
			{//@00DS:BCC
			   port->m_rxdata.results[port->m_rxdata.count]=0;
			   port->m_rxdata.theend=TRUE;
			   ::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXLINE, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
			}
			else if(port->m_rxdata.Sr253BCC==2){
				if(RXBuff==3)
				{//SRX+CMD+ETX BCC:ADD
			    port->m_rxdata.results[port->m_rxdata.count]=0;
			    port->m_rxdata.theend=TRUE;
			    ::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXLINE, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
				}
		        else if(RXBuff==6)
				{//SRX+CMD+ETX BCC:ADD
			    port->m_rxdata.results[port->m_rxdata.count]=0;
			    port->m_rxdata.theend=TRUE;
			    ::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXLINE, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
				}
		        else if(RXBuff==15)
				{//SRX+CMD+ETX BCC:ADD
			    port->m_rxdata.results[port->m_rxdata.count]=0;
			    port->m_rxdata.theend=TRUE;
			    ::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXLINE, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
				}
			}
			else if(port->m_rxdata.Sr253BCC==4){
				{
		        if((RXBuff==13)&&(port->m_rxdata.results[5]=='0')&&(port->m_rxdata.results[6]=='0'))
				{//SRX+CMD+ETX BCC:ADD
					int a;
					a=port->m_rxdata.count;
			    port->m_rxdata.results[a]=0;
			    port->m_rxdata.theend=TRUE;
			    ::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXLINE, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
				}


				}
			}
			else if(port->m_rxdata.count>=126)
			{
			   port->m_rxdata.results[port->m_rxdata.count++]='\r';
			   port->m_rxdata.results[port->m_rxdata.count]=0;
			   port->m_rxdata.theend=TRUE;
			   ::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXLINE, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
			}
		}
	} // 结束死循环
}

//
// 向端口写一个字符串
//
void CSerialPort::WriteToPort(char* string)
{		
	assert(m_hComm != 0);

	memset(m_szWriteBuffer, 0, sizeof(m_szWriteBuffer));
	strcpy(m_szWriteBuffer, string);

	// 设置写事件
	SetEvent(m_hWriteEvent);
}

//
// 获取设备控制块
//
DCB CSerialPort::GetDCB()
{
	return m_dcb;
}

//
// 获取通信事件掩码
//
DWORD CSerialPort::GetCommEvents()
{
	return m_dwCommEvents;
}

//
// 获取输出缓冲区大小
//
DWORD CSerialPort::GetWriteBufferSize()
{
	return m_nWriteBufferSize;
}

