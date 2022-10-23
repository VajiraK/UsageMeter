// MyCounter.cpp: implementation of the CMyCounter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyCounter.h"

//--------------------------------------------------------------------------------
void CMyCounter::Incriment(CString *duration)
{
	m_sec++;
	#ifdef _DEBUG
	m_refresh_index++;
	#endif

	if(m_sec==60)
	{//Seconds
		m_sec=0;
		m_s="00";
		//Minutes
		m_min++;
		#ifdef _DEBUG
		#else
		m_refresh_index++;
		#endif
			if(m_min==60)
			{
				m_min=0;
				m_m="00";
				m_hou++;
				//Hours
				if(m_hou<10)
				m_h.Format("%c%i",'0',m_hou);
				else
				m_h.Format("%i",m_hou);
			}
			else
			{
				if(m_min<10)
				m_m.Format("%c%i",'0',m_min);
				else
				m_m.Format("%i",m_min);
			}
	}
	else
	{
		if(m_sec<10)
		m_s.Format("%c%i",'0',m_sec);
		else
		m_s.Format("%i",m_sec);
	}

	//Refresh counter by recalculating duration using time diference
	//once after 5 min for release build 5 sec for debug
		if(m_refresh_index==5)
		{
		CString	tmp_du;
		m_refresh_index=0;
		TimeElapse(*m_pstart_sec,&GetTime(),&tmp_du);
		SetAt(&tmp_du);
		}

	duration->Format("%s:%s:%s",m_h,m_m,m_s);
}
//--------------------------------------------------------------------------------
void CMyCounter::SetAt(CString* time)
{
int		itime[3];
int		values[2];
int		index;
char*	com;
char*	ptime;

	m_h	=	time->Left(2);
	m_m	=	time->Mid(3,2);
	m_s	=	time->Right(2);
	m_refresh_index = 0;

	index=0;
	ptime=time->GetBuffer(8);

		for(int y=0;y<8;y=y+3)
		{//Loop though one time (23:45:34)
		com = ptime+y;
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

	m_hou=itime[0];
	m_min=itime[1];
	m_sec=itime[2];
}
