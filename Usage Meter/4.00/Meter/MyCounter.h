// MyCounter.h: interface for the CMyCounter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYCOUNTER_H__284AB40E_F9DD_4C32_8729_824E625511F7__INCLUDED_)
#define AFX_MYCOUNTER_H__284AB40E_F9DD_4C32_8729_824E625511F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyString.h"

class CMyCounter : public CMyString
{
public:
				CMyCounter();
	virtual		~CMyCounter();
	void		Reset();
	void		Increment();

	MY_DURATION		m_duration;
	MY_BEEP_STRUCT	m_beep;
};

#endif // !defined(AFX_MYCOUNTER_H__284AB40E_F9DD_4C32_8729_824E625511F7__INCLUDED_)
