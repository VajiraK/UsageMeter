// MyTimeMath.cpp: implementation of the CMyTimeMath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Usage Meter.h"
#include "MyTimeMath.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
CMyTimeMath::CMyTimeMath()
{
	m_previ_day = GetDay();
}
//--------------------------------------------------------------------------------------------
#define TH		0
#define TM		1
#define TS		2
void CMyTimeMath::TimeAddition(int* total_seconds,char* add_time)
{//time recive like "12:45:34"
//More efficient function to convert time component to Int(eg - 23:45:56)
int itime[3];
int values[2];
int index;
char* com;

	index=0;

		for(int y=0;y<8;y=y+3)
		{//Loop though one time (23:45:34)
		com = add_time+y;
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

	//End time convert to seconds
	itime[TM] = itime[TM] * 60;
	itime[TM] = itime[TM] + itime[TS];
	itime[TH] = itime[TH] * 3600;
	itime[TH] = itime[TH] + itime[TM];

	//add seconds
	*total_seconds = *total_seconds + itime[TH];
}
//--------------------------------------------------------------------------------------------
void CMyTimeMath::TimeElapse(int start_sec,CString* end_time,CString* elapse)
{//convert time component to Seconds 03:45:56)
static int end_sec;
static int elapse_sec;
static int S,M,H;

	elapse_sec = 0;
	end_sec = ToSeconds(end_time);

	//calculate Time Elaps
	if(end_sec>start_sec){
	//not pass Mid Night
	elapse_sec = end_sec - start_sec;
	}else{
	//pass Mid Night
	elapse_sec = 86400 - start_sec;//Until mid night
    elapse_sec = elapse_sec + end_sec;//Rest (After mid night)
	}

//Convert seconds to time (Time Elaps)
	H			= elapse_sec/3600;	//Hourse
	elapse_sec	= elapse_sec%3600;	//Reminder
	M			= elapse_sec/60;		//Minutes
	S			= elapse_sec%60;		//Reminder(That's seconds)

//Format output
	if(S<=9){sS.Format("0%i",S);} else
	{sS.Format("%i",S);}
	if(M<=9){sM.Format("0%i",M);} else
	{sM.Format("%i",M);}
	if(H<=9){sH.Format("0%i",H);} else
	{sH.Format("%i",H);}

	elapse->Format("%s:%s:%s",sH,sM,sS);
}
//--------------------------------------------------------------------------------------------
CString CMyTimeMath::GetDay(bool* daychanged,CString* preday)
{//Get Day
CTime	t;	
CString d;

	t = t.GetCurrentTime();
	d = t.Format( "%d");

	if(daychanged!=NULL)
	{//valid pointer
		if(m_previ_day!=d)
		{//day changed
			//return previous day
			*preday=m_previ_day;
			m_previ_day=d;
			*daychanged=true;
		}else{
			*daychanged=false;
		}
	}

	return d;
}
//--------------------------------------------------------------------------------------------
CString CMyTimeMath::GetTime()
{//Get Time
CTime t;
	t = t.GetCurrentTime();	
	return t.Format( "%H:%M:%S");
}
//--------------------------------------------------------------------------------------------
void CMyTimeMath::Format_Seconds(int seconds, CString *time)
{
int S,M,H;
//Convert seconds to time
	H		= seconds/3600;	//Hourse
	seconds	= seconds%3600; //Reminder
	M		= seconds/60;	//Minutes
	S		= seconds%60;	//Reminder(That's seconds)
//Convert seconds to time

//Format output
	if(S<=9){sS.Format("0%i",S);} else
	{sS.Format("%i",S);}

	if(M<=9){sM.Format("0%i",M);} else
	{sM.Format("%i",M);}

	if(H<=9){sH.Format("0%i",H);} else
	{sH.Format("%i",H);}

	time->Format("%s:%s:%s",sH,sM,sS);
}
//--------------------------------------------------------------------------------------------
#define TS	2
#define TM	1
#define TH	0
int CMyTimeMath::ToSeconds(CString *time)
{
int itime[3];
int values[2];
int index;
char* com;
char* ctime;

	index=0;
	ctime=time->GetBuffer(8); 

		for(int y=0;y<8;y=y+3)
		{//Loop though one time (23:45:34)
		com = ctime+y;
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

	//End time convert to seconds
	itime[TM] = itime[TM] * 60;
	itime[TM] = itime[TM] + itime[TS];
	itime[TH] = itime[TH] * 3600;
	itime[TH] = itime[TH] + itime[TM];
return itime[TH];
}


