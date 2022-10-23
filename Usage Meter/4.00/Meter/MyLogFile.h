// MyLogFile.h: interface for the CMyLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLOGFILE_H__F437529F_E8BC_48AE_B73A_3009968ECA51__INCLUDED_)
#define AFX_MYLOGFILE_H__F437529F_E8BC_48AE_B73A_3009968ECA51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyLogPath.h"
#include "MyListView.h"
#include "MyCounter.h"

struct MY_LOG_THREAD_DATA
{
	CMyListView*	pwin_list;
	CMyListView*	pint_list;
	MY_FILE_STRUCT*	pum_log;
	char*			pwin_total;
	char*			pint_total;
	BYTE*			data;
	DWORD			len;
	HANDLE 			hlogfile;
};

class CMyLogFile : public CMyLogPath
{
public:
				CMyLogFile();
	virtual		~CMyLogFile();
	void		Save_Int_Usage();
	void		Save_Win_Usage();
	void		AssosiateFiles();
	bool		LoadLog();
	//void		GetViewerPath(char* path,DWORD* len);

	CMyCounter			*m_pwin_counter, *m_pint_counter;
	MY_LOG_THREAD_DATA	m_logthread_data;

private:
	bool		OpenLogFile();
	void		SaveLog();
};

#endif // !defined(AFX_MYLOGFILE_H__F437529F_E8BC_48AE_B73A_3009968ECA51__INCLUDED_)
