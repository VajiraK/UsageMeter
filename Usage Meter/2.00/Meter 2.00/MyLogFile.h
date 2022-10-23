// MyLogFile.h: interface for the CMyLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLOGFILE_H__931E4F8F_5F7B_4067_92CB_1DCB82863187__INCLUDED_)
#define AFX_MYLOGFILE_H__931E4F8F_5F7B_4067_92CB_1DCB82863187__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyLogFolder.h"

struct IU_FILE_STRUCT
{
char	type;
char	day[3];
char	start_end[22];
char	duration[9];
char	roughdu[9];
DWORD	names_len;
};

class CMyLogFile : public CMyLogFolder
{
public:
	bool	Save_Int_Usage(DAY_STRUCT* day,char* start,char* end,char* duration,char* roughdu);
	bool	Save_Win_Usage(DAY_STRUCT* day,char* start,char* end,char* duration,char* roughdu);
	void	IntLogFileObj(HWND hint_list,HWND hwin_list,char* pint_total,char* pwin_total,CWnd* pmaindlg,DWORD* pprivilage);
	void	SetStatusFile(WORD flag);
	CString	CreateTitle();
	void	MonthChange();
	bool	LoadLog();

private:
	void FormatTotal(char *buf, DWORD seconds);
	bool SaveLog(char* names);
	
	CWinThread* m_pmythread;
	CString		m_logfilename;
	HWND		m_hint_list, m_hwin_list;
	char		*m_pint_total,*m_pwin_total;
	CWnd*		m_pmaindlg;	
IU_FILE_STRUCT	m_us;
};

#endif // !defined(AFX_MYLOGFILE_H__931E4F8F_5F7B_4067_92CB_1DCB82863187__INCLUDED_)
