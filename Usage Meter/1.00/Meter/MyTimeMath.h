// MyTimeMath.h: interface for the CMyTimeMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTIMEMATH_H__A851DB42_2986_461F_946A_9A1837FBCD19__INCLUDED_)
#define AFX_MYTIMEMATH_H__A851DB42_2986_461F_946A_9A1837FBCD19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include  "MyRegistry.h"

class CMyTimeMath : public CMyRegistry
{
public:
			CMyTimeMath();
	int		ToSeconds(CString* time);
	CString GetDay(bool* daychanged=NULL,CString* preday=NULL);
	CString GetTime();
	void	TimeAddition(int* total_seconds,char* add_time);
	void	TimeElapse(int start_sec,CString* end_time,CString* elapse);
	void	Format_Seconds(int seconds,CString* time);

private:
	CString sH,sM,sS;
	CString m_previ_day;
};

#endif // !defined(AFX_MYTIMEMATH_H__A851DB42_2986_461F_946A_9A1837FBCD19__INCLUDED_)
