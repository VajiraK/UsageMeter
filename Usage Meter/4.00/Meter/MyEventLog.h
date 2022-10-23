// MyEventLog.h: interface for the CMyEventLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYEVENTLOG_H__E75B73A0_4DE7_439E_B3A3_61792754146E__INCLUDED_)
#define AFX_MYEVENTLOG_H__E75B73A0_4DE7_439E_B3A3_61792754146E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyString.h"

class CMyEventLog : public CMyString
{
public:
	void AddLine();
	void IntEventLog();
			CMyEventLog();
	virtual ~CMyEventLog();
	void	WriteLog(char *text);


private:
	DWORD		m_len;
	HANDLE 		hlogfile;
	char		m_time[22];
	char		m_path[MAX_PATH];
};

#endif // !defined(AFX_MYEVENTLOG_H__E75B73A0_4DE7_439E_B3A3_61792754146E__INCLUDED_)
