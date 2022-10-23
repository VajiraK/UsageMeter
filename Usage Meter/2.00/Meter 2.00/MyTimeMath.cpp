// MyTimeMath.cpp: implementation of the CMyTimeMath class.

#include "stdafx.h"
#include "Usage Meter.h"
#include "MyTimeMath.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMyTimeMath::CMyTimeMath()
{
DAY_STRUCT temp;
	GetDay(&temp);
	memcpy(m_previ_day,temp.day,2);
}
//--------------------------------------------------------------------------------------------
void CMyTimeMath::TimeAddition(int* total_seconds,char* add_time)
{//time recive like "12:45:34"
//More efficient function to convert time component to Int(eg - 23:45:56)
int itime[3];
int values[2];
int index;
char* com;

	index=0;

		for(WORD y=0;y<8;y=y+3)
		{//Loop though one time (23:45:34)
		com = add_time+y;
		//initialize
		itime[index]=0;
			for(WORD i=0;i<2;i++)
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
	itime[M] = itime[M] * 60;
	itime[M] = itime[M] + itime[S];
	itime[H] = itime[H] * 3600;
	itime[H] = itime[H] + itime[M];

	//add seconds
	*total_seconds = *total_seconds + itime[H];
}
//--------------------------------------------------------------------------------------------
void CMyTimeMath::TimeElapse(DWORD start_sec,char* end_time,char* elapse)
{
DWORD end_sec;
DWORD elapse_sec;
WORD i[3];

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
#pragma warning(disable:4244)
	i[H]		= elapse_sec/3600;	//Hourse
	elapse_sec	= elapse_sec%3600;	//Reminder
	i[M]		= elapse_sec/60;	//Minutes
	i[S	]		= elapse_sec%60;	//Reminder(That's seconds)
#pragma warning(default:4244)
	
//Format output
	MakeTime(elapse,i);
}
//--------------------------------------------------------------------------------------------
void CMyTimeMath::GetDay(DAY_STRUCT* today,bool* daychanged,char* preday)
{//Get Day
SYSTEMTIME	st; 

	ZeroMemory(today->day,2);
	GetLocalTime(&st);
	NumToString(today->day, st.wDay);

	if(daychanged!=NULL)
	{//valid pointer
		if(CompareBuffer(today->day,m_previ_day,2)==false)
		{//day changed
			//return previous day
			memcpy(preday,m_previ_day,2);
			memcpy(m_previ_day,today->day,2);
			*daychanged=true;
		}else{
			*daychanged=false;
		}
	}
	//Return the lenth of day 
	if(st.wDay<9)
	{
		//today->day	[1] = '\0';
		today->daylen = 1;
	}else{
		//today->day[2] = '\0';
		today->daylen = 2;
	}
}
//--------------------------------------------------------------------------------------------
void CMyTimeMath::GetTime(char *time)
{
SYSTEMTIME	st; 
WORD		t[3];

	time[2] = time[5] = ':';
	time[8] = '\0';

	GetLocalTime(&st);

	t[0] = st.wHour;
	t[1] = st.wMinute;
	t[2] = st.wSecond;

	MakeTime(time,t);
}
//--------------------------------------------------------------------------------------------
/*void CMyTimeMath::Format_Seconds(int seconds, CString *time)
{//Capacity <99:59:59
	*time = "00:00:00";
	Format_Seconds(seconds,SP(time));
}*/
//--------------------------------------------------------------------------------------------
void CMyTimeMath::Format_Seconds(int seconds, char *time)
{//Capacity <99:59:59
WORD i[3];
//Convert seconds to time
	i[H]		= seconds/3600;	//Hourse
	seconds		= seconds%3600; //Reminder
	i[M]		= seconds/60;	//Minutes
	i[S]		= seconds%60;	//Reminder(That's seconds)
//Convert seconds to time

//Format output
	MakeTime(time,i);
}
//--------------------------------------------------------------------------------------------
/*int CMyTimeMath::ToSeconds(CString *time)
{
	return ToSeconds(SP(time));
}*/
//--------------------------------------------------------------------------------------------
int CMyTimeMath::ToSeconds(char *time)
{
int itime[3];
int values[2];
int index;
char* com;

	index=0;

		for(WORD y=0;y<8;y=y+3)
		{//Loop though one time (23:45:34)
		com = time+y;
		//initialize
		itime[index]=0;
			for(WORD i=0;i<2;i++)
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
	itime[M] = itime[M] * 60;
	itime[M] = itime[M] + itime[S];
	itime[H] = itime[H] * 3600;
	itime[H] = itime[H] + itime[M];
return itime[H];
}

//--------------------------------------------------------------------------------------------
void CMyTimeMath::MakeTime(char *buf, WORD* n)
{//Capacity <99:59:59
WORD num,single,index;

	index = 0;

	for(WORD t=0;t<=2;t++)
	{//Loop through three time components
	//Get each components
	num = n[t];
		for(WORD i=0;i<=1;i++)
		{//Convert each component to char
			if(i==0)
				single = num/10;

			switch (single)
			{
			case 0:
				buf[index]='0';single = num;break;
			case 1:
				buf[index]='1';single=num-1*10;break;
			case 2:
				buf[index]='2';single=num-2*10;break;
			case 3:
				buf[index]='3';single=num-3*10;break;
			case 4:
				buf[index]='4';single=num-4*10;break;
			case 5:
				buf[index]='5';single=num-5*10;break;
			case 6:
				buf[index]='6';single=num-6*10;break;
			case 7:
				buf[index]='7';single=num-7*10;break;
			case 8:
				buf[index]='8';single=num-8*10;break;
			case 9:
				buf[index]='9';single=num-9*10;break;
			}
		index++;
		}
	index++;
	}
}
//--------------------------------------------------------------------------------------------------------
void CMyTimeMath::NumToString(char *buf, int n)
{//Capacity <999
int	num,min,sav;
	sav = n;

for(int i=0;i<=2;i++)
{
	switch (i)
	{
	case 0:
		min=100;
		num = n/min;
		break;
	case 1:
		min=10;
		n = num;
		num = n/min;
		break;
	}

	switch (num)
	{
	case 0:
		buf[i]='0';num = n;break;
	case 1:
		buf[i]='1';num=n-1*min;break;
	case 2:
		buf[i]='2';num=n-2*min;break;
	case 3:
		buf[i]='3';num=n-3*min;break;
	case 4:
		buf[i]='4';num=n-4*min;break;
	case 5:
		buf[i]='5';num=n-5*min;break;
	case 6:
		buf[i]='6';num=n-6*min;break;
	case 7:
		buf[i]='7';num=n-7*min;break;
	case 8:
		buf[i]='8';num=n-8*min;break;
	case 9:
		buf[i]='9';num=n-9*min;break;
	}
}

	if(sav<100)
	{
		if(sav<10)
		{//Like 34
			buf[0] = buf[2];
			buf[1] = '\0';
		}else{//Like 6
			buf[0] = buf[1];
			buf[1] = buf[2];
			buf[2] = '\0';
		}
	}else//Like 624
		buf[3] = '\0';
}
//--------------------------------------------------------------------------------------------------------
bool CMyTimeMath::CompareBuffer(char *one, char *two, WORD size)
{
	size--;
	for(WORD i=0;i<=size;i++)
	{
		if(one[i]!=two[i])
			return false;
	}

	return true;
}
