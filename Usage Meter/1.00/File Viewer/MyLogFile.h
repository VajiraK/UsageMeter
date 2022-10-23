// MyLogFile.h: interface for the CMyLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYLOGFILE_H__E995CCDE_202A_4E09_9033_3025A16BCB11__INCLUDED_)
#define AFX_MYLOGFILE_H__E995CCDE_202A_4E09_9033_3025A16BCB11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyLogFile  
{
public:
	//Fun
	int		FindLatsSlash(CString* path);
	void	AssosiateFiles();
	void	IntLogFileObj(CListCtrl *pint_list,CListCtrl *pwin_list,CStatic *pintlable,CStatic *pwinlable,CWnd *pmaindlg);
	void	LoadLogFile(CString path);
private:
	CString GetThisMonth();
	CString GetAppPath();
	//Fun
	void	Format_Seconds(int seconds, CString *time);
	void	TimeAddition(int* total_seconds,char* add_time);
	void	Split(CString* data,CStringArray* arr,char delemiter);
	//Ver
	CWinThread	*m_pmythread;
	CListCtrl	*m_pint_list, *m_pwin_list;
	CStatic		*m_int_lable,*m_win_lable;
	CWnd		*m_pmaindlg;
	CString		sH,sM,sS,m_totals;
};

#endif // !defined(AFX_MYLOGFILE_H__E995CCDE_202A_4E09_9033_3025A16BCB11__INCLUDED_)
