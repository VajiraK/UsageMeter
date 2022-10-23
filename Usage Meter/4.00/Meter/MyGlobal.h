// MyGlobal.h: interface for the CMyGlobal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYGLOBAL_H__138AC7DC_FC47_41EE_8734_B3356F863A15__INCLUDED_)
#define AFX_MYGLOBAL_H__138AC7DC_FC47_41EE_8734_B3356F863A15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct MY_EXCEPTION
{
	bool	kill;
	bool	err;
	DWORD	code;
	DWORD	list_len;
	char	list_ex[1000];
};

struct MY_FILE_STRUCT
{
	BYTE	type;
	BYTE	day;
	BYTE	start[3];
	BYTE	end[3];
	BYTE	duration[3];
	DWORD	users_len;
	char*	users;
};

struct MY_BEEP_STRUCT
{
	BYTE	enable;
	WORD	frequency;
	WORD	duration;
	WORD	interval;
	DWORD	count;
};

struct MY_DURATION
{
	BYTE	num_dura[3];
	char*	str_dura;
};

class CMyGlobal  
{
public:
			CMyGlobal();
	virtual ~CMyGlobal();

	DWORD			m_id,m_client_count;
	bool			m_skip_timer;;
	BYTE			m_privilage;
	BYTE			m_now[3];
	BYTE			m_win_str_time[3];
	BYTE			m_int_str_time[3];
	char			*m_win_total, *m_int_total;
	MY_FILE_STRUCT	m_um_log;
	MY_EXCEPTION	m_ex;
	SYSTEMTIME		m_st;
	HWND			m_hmain_window;
};

#endif // !defined(AFX_MYGLOBAL_H__138AC7DC_FC47_41EE_8734_B3356F863A15__INCLUDED_)
