// MyString.h: interface for the CMyString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSTRING_H__A0476639_E4D7_4981_AEFE_FDD926B3215A__INCLUDED_)
#define AFX_MYSTRING_H__A0476639_E4D7_4981_AEFE_FDD926B3215A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyExceptions.h"

class CMyString  : public CMyGlobal
{
public:
			CMyString();
	virtual ~CMyString();
	void	NumToString(char *buf, DWORD num, BYTE setleadzero = 0);
	void	MakeStrTime(char *buf, BYTE* n);
	//bool	CompareBuffer(char* one,char* two,WORD size);

private:
	void	SetLeadZeros(char *buf, DWORD* num, BYTE* setleadzero);
};

#endif // !defined(AFX_MYSTRING_H__A0476639_E4D7_4981_AEFE_FDD926B3215A__INCLUDED_)
