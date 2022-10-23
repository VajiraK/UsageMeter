// MyTime.h: interface for the CMyTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTIME_H__5478A494_F77C_4105_B2F0_9D087BC79967__INCLUDED_)
#define AFX_MYTIME_H__5478A494_F77C_4105_B2F0_9D087BC79967__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyString.h"

class CMyTime  : public CMyString
{
public:

				CMyTime();
	virtual		~CMyTime();
	void		SetTime();
};

#endif // !defined(AFX_MYTIME_H__5478A494_F77C_4105_B2F0_9D087BC79967__INCLUDED_)
