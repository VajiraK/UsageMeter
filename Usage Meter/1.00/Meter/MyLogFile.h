// MyLogFile.h: interface for the CMyLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLOGFILE_H__931E4F8F_5F7B_4067_92CB_1DCB82863187__INCLUDED_)
#define AFX_MYLOGFILE_H__931E4F8F_5F7B_4067_92CB_1DCB82863187__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyUser.h"

class CMyLogFile : public CMyUser 
{
public:
	//func
	CString CreateTitle();
	void	SetLogPath();
	void	LoadLog();
	void	Save_Int_Usage(CString day,CString start,CString end,CString duration);
	void	Save_Win_Usage(CString day,CString start,CString end,CString duration);
	void	IntLogFileObj(CListCtrl* pint_list,CListCtrl* pwin_list,CString* pint_total,CString* pwin_total,CWnd* pmaindlg);
private:
	CWinThread* m_pmythread;
	//ver
	CString		m_logpath;
	CListCtrl*	m_pint_list;
	CListCtrl*	m_pwin_list;
	CString*	m_pint_total;
	CString*	m_pwin_total;
	CWnd*		m_pmaindlg;	
};

#endif // !defined(AFX_MYLOGFILE_H__931E4F8F_5F7B_4067_92CB_1DCB82863187__INCLUDED_)
