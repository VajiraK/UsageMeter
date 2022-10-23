// MyBeep.h: interface for the CMyBeep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYBEEP_H__06577F30_32C0_41B2_874D_2E8374E5C471__INCLUDED_)
#define AFX_MYBEEP_H__06577F30_32C0_41B2_874D_2E8374E5C471__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyTimeMath.h"

struct BEEP_STRUCT
{
	bool Enable;
	int	Duration;
	int Frequency;
	int Interval;
	int Count;
};

class CMyBeep : public CMyTimeMath
{
public:
	void ResetBeepCount();
	CMyBeep();
	virtual ~CMyBeep();

void Beep();
void SetBeep(BEEP_STRUCT* bs,bool reset_count);
void RetriveSettings(BEEP_STRUCT* bs, bool flag);
bool CheckInputs(BEEP_STRUCT* bs, bool show_err,HWND parent);
private:
	BEEP_STRUCT m_beep_info;
};

#endif // !defined(AFX_MYBEEP_H__06577F30_32C0_41B2_874D_2E8374E5C471__INCLUDED_)
