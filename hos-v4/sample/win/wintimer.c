/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ����ץ�ץ����                           */
/*   Windows�� ���󥿡��Х륿���ޥ��֥�������                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "wintimer.h"



DWORD WINAPI WinTimer_Thread(LPVOID param);	/* �����޳������ѥ���åɴؿ� */


static HANDLE hEventTimer;
static INTNO  intnoTimer;


/* ����� */
void WinTimer_Initialize(INTNO intno)
{
	DWORD dwThreadId;

	/* �����������ֹ������ */
	intnoTimer = intno;

	/* �������ѥ��٥�Ȥκ��� */
	hEventTimer = CreateEvent(NULL, FALSE, FALSE, NULL);

	/* �ޥ����ǥ��������ޤγ��� */
	timeSetEvent(10, 1, (LPTIMECALLBACK)hEventTimer, 0, TIME_PERIODIC | TIME_CALLBACK_EVENT_PULSE);

	CreateThread(NULL, 0, WinTimer_Thread, 0, 0, &dwThreadId);
}


/* �����޳������ѥ���åɴؿ� */
DWORD WINAPI WinTimer_Thread(LPVOID param)
{
	for ( ; ; )
	{
		WaitForSingleObject(hEventTimer, INFINITE);

		hospac_win_int(intnoTimer);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
