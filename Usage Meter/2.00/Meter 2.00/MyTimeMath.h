// MyTimeMath.h: interface for the CMyTimeMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTIMEMATH_H__A851DB42_2986_461F_946A_9A1837FBCD19__INCLUDED_)
#define AFX_MYTIMEMATH_H__A851DB42_2986_461F_946A_9A1837FBCD19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include  "MyRegistry.h"

struct DAY_STRUCT
{
	char	day[3];
	WORD	daylen;
};

class CMyTimeMath : public CMyRegistry
{
public:
	void	TimeElapse(DWORD start_sec,char* end_time,char* elapse);
	void	GetDay(DAY_STRUCT* today,bool* daychanged=NULL,char* preday=NULL);
	void	TimeAddition(int* total_seconds,char* add_time);
	//void	Format_Seconds(int seconds,CString* time);
	void	Format_Seconds(int seconds, char *time);
	void	NumToString(char* c,int n);
	void	MakeTime(char *buf, WORD* n);
	//int		ToSeconds(CString* time);
	int		ToSeconds(char *time);
	void	GetTime(char* time);
	//CString GetTime();
			CMyTimeMath();

private:
	bool CompareBuffer(char* one,char* two,WORD size);
	CString sH,sM,sS;
	char m_previ_day[3];
};

#endif // !defined(AFX_MYTIMEMATH_H__A851DB42_2986_461F_946A_9A1837FBCD19__INCLUDED_)
