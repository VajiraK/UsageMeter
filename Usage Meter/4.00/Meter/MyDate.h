// MyDate.h: interface for the CMyDate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDATE_H__9BF71809_CA00_41A2_853B_60D34A881B4F__INCLUDED_)
#define AFX_MYDATE_H__9BF71809_CA00_41A2_853B_60D34A881B4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyRegistry.h"

class CMyDate : public CMyRegistry
{
public:
			CMyDate();
	virtual ~CMyDate();
	void	UpdateDate();
	void	QuarryDate();
	void	SetDate();
	void	SetMonthName();
	void	SetTime();

	BYTE	m_pre_day, m_pre_month;
	char	m_month_name[5];
	bool	m_day_changed,m_month_changed;
};

#endif // !defined(AFX_MYDATE_H__9BF71809_CA00_41A2_853B_60D34A881B4F__INCLUDED_)
