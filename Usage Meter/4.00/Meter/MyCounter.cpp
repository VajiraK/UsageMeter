// MyCounter.cpp: implementation of the CMyCounter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Resource.h"
#include "MyCounter.h"

//////////////////////////////////////////////////////////////////////
CMyCounter::~CMyCounter(){}
//--------------------------------------------------------------------------------
CMyCounter::CMyCounter()
{
	m_beep.enable=0;
}
//--------------------------------------------------------------------------------
void CMyCounter::Reset()
{//Set counter to "00:00:00"
	m_duration.num_dura[H] = m_duration.num_dura[M] = m_duration.num_dura[S] = 0;
}
//--------------------------------------------------------------------------------------
void CMyCounter::Increment()
{
	m_duration.num_dura[S]++;

	if(m_duration.num_dura[S]==60)
	{//Seconds
		m_duration.num_dura[S]=0;
		//Minutes
		m_duration.num_dura[M]++;
			if(m_duration.num_dura[M]==60)
			{//Hours
				m_duration.num_dura[M]=0;
				m_duration.num_dura[H]++; 
			}
	}

	MakeStrTime(m_duration.str_dura,m_duration.num_dura);

	//Do Beep
	if(m_beep.enable==1)
	{
		m_beep.count++;
		if(m_beep.interval==m_beep.count)
		{
			Beep(m_beep.frequency,m_beep.duration);
			m_beep.count = 0;
		}
	}
}
//--------------------------------------------------------------------------------------
