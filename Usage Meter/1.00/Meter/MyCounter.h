// MyCounter.h: interface for the CMyCounter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCOUNTER_H__2FA33CAA_26B5_4CB5_BFDC_75D3F16E6894__INCLUDED_)
#define AFX_MYCOUNTER_H__2FA33CAA_26B5_4CB5_BFDC_75D3F16E6894__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyTimeMath.h"

class CMyCounter  : public CMyTimeMath
{
public:
	int	*m_pstart_sec;
	void SetAt(CString* time);
	void Incriment(CString* duration);
private:
	int		m_refresh_index;
	int		m_sec;
	int		m_min;
	int		m_hou;
	CString m_s;
	CString m_m;
	CString m_h;
};

#endif // !defined(AFX_MYCOUNTER_H__2FA33CAA_26B5_4CB5_BFDC_75D3F16E6894__INCLUDED_)
