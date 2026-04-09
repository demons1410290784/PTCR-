// ParaPort.h: interface for the CParaPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAPORT_H__B2232B81_273C_11D8_8DAA_000AEB11619A__INCLUDED_)
#define AFX_PARAPORT_H__B2232B81_273C_11D8_8DAA_000AEB11619A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParaPort  
{
public:
	bool ExitDeviceLPT1();
	bool WriteLPT1(BYTE *pOut);
	BYTE ReadLPT1();
	bool CreatLPT1();
	CParaPort();
	virtual ~CParaPort();

protected:
	HANDLE hFile;
    CString m_LPTString;
	unsigned char pIn;
//	BYTE *pOut;
	DWORD number; 
	
};

#endif // !defined(AFX_PARAPORT_H__B2232B81_273C_11D8_8DAA_000AEB11619A__INCLUDED_)
