// MyString.cpp: implementation of the CMyString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyString.h"


CMyString::CMyString()
{}
CMyString::~CMyString()
{}
//--------------------------------------------------------------------------------------
void CMyString::NumToString(char *buf, DWORD num, BYTE setleadzero)
{//Capacity <9999
int		pos[4];
int		stop;
DWORD	n = num;//Reserve original

	//Set loop*********************************************
	if(n>999)
		{//1000
			stop = 3;
		}else{

			if(n>99)
			{//100
				stop = 2;
			}else{
				if(n>9)
				{//10
					stop = 1;
				}else{//1
					stop = 0;
				}
			}
		}

	//split intiger******************************************
	pos[3] =  n/1000;
	n = n - pos[3]*1000;
	pos[2] =  n/100;
	n = n - pos[2]*100;
	pos[1] =  n/10;
	n = n - pos[1]*10;
	pos[0] =  n;
	
	//convert to char****************************************
	for(int i=0;i<=stop;i++)
	{
		switch (pos[stop-i])
		{
		case 0:
			buf[i]='0';break;
		case 1:
			buf[i]='1';break;
		case 2:
			buf[i]='2';break;
		case 3:
			buf[i]='3';break;
		case 4:
			buf[i]='4';break;
		case 5:
			buf[i]='5';break;
		case 6:
			buf[i]='6';break;
		case 7:
			buf[i]='7';break;
		case 8:
			buf[i]='8';break;
		case 9:
			buf[i]='9';break;
		}
	}
	//Set leading zeros
	if(setleadzero!=0)
		SetLeadZeros(buf, &num, &setleadzero);
}
//--------------------------------------------------------------------------------------------
void CMyString::MakeStrTime(char *buf, BYTE* n)
{//Capacity <99:59:59
BYTE num,single,index;

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
				buf[index]='1';single = num-1*10;break;
			case 2:
				buf[index]='2';single = num-2*10;break;
			case 3:
				buf[index]='3';single = num-3*10;break;
			case 4:
				buf[index]='4';single = num-4*10;break;
			case 5:
				buf[index]='5';single = num-5*10;break;
			case 6:
				buf[index]='6';single = num-6*10;break;
			case 7:
				buf[index]='7';single = num-7*10;break;
			case 8:
				buf[index]='8';single = num-8*10;break;
			case 9:
				buf[index]='9';single = num-9*10;break;
			}
		index++;
		}
	index++;
	}
}
//--------------------------------------------------------------------------------------
void CMyString::SetLeadZeros(char *buf, DWORD* num, BYTE* setleadzero)
{
	if(*setleadzero==1)
	{
		if(*num<10)
		{
			buf[1] = buf[0];
			buf[0] = '0';
		}
	}

	if(*setleadzero==2)
	{
		if(*num<10)
		{
			buf[2] = buf[0];
			buf[0] = buf[1] = '0';
		}else
		{
			if((*num>=10) & (*num<100))
			{
				buf[2] = buf[1];
				buf[1] = buf[0];
				buf[0] = '0';
			}
		}
	}
}
//--------------------------------------------------------------------------------------
/*bool CMyString::CompareBuffer(char *one, char *two, WORD size)
{
	size--;
	for(WORD i=0;i<=size;i++)
	{
		if(one[i]!=two[i])
			return false;
	}

	return true;
}*/