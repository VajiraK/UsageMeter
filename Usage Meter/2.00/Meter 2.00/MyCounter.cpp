// MyCounter.cpp: implementation of the CMyCounter class.
//
//////////////////////////////////////////////////////////////////////
#include "Resource.h"
#include "stdafx.h"
#include "MyCounter.h"

//--------------------------------------------------------------------------------
void CMyCounter::Incriment(char *duration)
{
	m_i[S]++;
	m_duration_sec++;

	if(m_i[S]==60)
	{//Seconds
		m_i[S]=0;
		//Minutes
		m_i[M]++;
		//m_refresh_index++;
			if(m_i[M]==60)
			{//Hours
				m_i[M]=0;
				m_i[H]++;
			}
	}

	//Refresh counter by recalculating duration using time diference
	//once after 5 min 6
	/*if(m_refresh_index==5)
	{
		m_refresh_index=0;
		char now[9];char dur[9];;
		GetTime(now);
		TimeElapse(*m_pstart_sec,now,dur);
		SetAt(dur,m_rough_sec,false);
	}*/
	//Call Beep member of Beep class
	Beep();
	
	MakeTime(duration,m_i);
}
//--------------------------------------------------------------------------------
void CMyCounter::Reset()
{//Set counter to "00:00:00"
	ResetBeepCount();
	//m_refresh_index = 0; 
	m_duration_sec = 0;
	m_i[H] = m_i[M] = m_i[S] = 0;
}
//--------------------------------------------------------------------------------
void CMyCounter::SetAt(char* time,int m_duration,bool resetbeep)
{//Set counter to specified time
int		itime[3];
int		values[2];
int		index;
char*	com;

	if(resetbeep==true)
		ResetBeepCount();
	m_duration_sec = m_duration;

	//m_refresh_index = 0;
	index=0;

		for(int y=0;y<8;y=y+3)
		{//Loop though one time (23:45:34)
		com = time+y;
		//initialize
		itime[index]=0;
			for(int i=0;i<2;i++)
			{//Convert one time componemt (23)
				switch (com[i])
				{
				case '0':
					values[i]=0;break;
				case '1':
					values[i]=1;break;
				case '2':
					values[i]=2;break;
				case '3':
					values[i]=3;break;
				case '4':
					values[i]=4;break;
				case '5':
					values[i]=5;break;
				case '6':
					values[i]=6;break;
				case '7':
					values[i]=7;break;
				case '8':
					values[i]=8;break;
				case '9':
					values[i]=9;break;
				}
				//Tenth place
				if(i==0)
					values[0]=values[0]*10;

				itime[index]=itime[index]+values[i];
			}
		index++;
		}

	m_i[H]=itime[0];
	m_i[M]=itime[1];
	m_i[S]=itime[2];
}
//--------------------------------------------------------------------------------
/*CString	CMyCounter::GetRoughDuration()
{
CString temp;
char	du[9];
	memcpy(du,"00:00:00\0",9);
	GetRoughDuration(du);
	temp = du;
	return temp;
}*/
//--------------------------------------------------------------------------------
void CMyCounter::GetDuration(char* duration)
{
	Format_Seconds(m_duration_sec,duration);
}