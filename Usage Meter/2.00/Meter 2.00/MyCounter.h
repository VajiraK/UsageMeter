// MyCounter.h: interface for the CMyCounter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCOUNTER_H__2FA33CAA_26B5_4CB5_BFDC_75D3F16E6894__INCLUDED_)
#define AFX_MYCOUNTER_H__2FA33CAA_26B5_4CB5_BFDC_75D3F16E6894__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyBeep.h"

class CMyCounter  : public CMyBeep
{
public:
	void	SetAt(char* time,int m_duration,bool resetbeep);
	void	Reset();

	void	Incriment(char* duration);
	//CString	GetRoughDuration();
	void	GetDuration(char* duration);

	int		m_duration_sec;
	int		*m_pstart_sec;

private:
	//int		m_refresh_index;
	WORD	m_i[3];
};

#endif // !defined(AFX_MYCOUNTER_H__2FA33CAA_26B5_4CB5_BFDC_75D3F16E6894__INCLUDED_)
