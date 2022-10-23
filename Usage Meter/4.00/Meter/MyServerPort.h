// MyServerPort.h: interface for the CMyServerPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSERVERPORT_H__5ED11D80_BC46_433F_8167_36620987B7DD__INCLUDED_)
#define AFX_MYSERVERPORT_H__5ED11D80_BC46_433F_8167_36620987B7DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyClientPort.h"

class CMyServerPort : public CMyClientPort
{
public:
			CMyServerPort();
	virtual ~CMyServerPort();

public:
	bool	GivePrivilage();
	void	SayServerActive();	
};

#endif // !defined(AFX_MYSERVERPORT_H__5ED11D80_BC46_433F_8167_36620987B7DD__INCLUDED_)
