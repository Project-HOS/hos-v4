/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  サンプルプログラム                           */
/*   Windows用 インターバルタイマオブジェクト                               */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "wintimer.h"



DWORD WINAPI WinTimer_Thread(LPVOID param);	/* タイマ割り込み用スレッド関数 */


static HANDLE hEventTimer;
static INTNO  intnoTimer;


/* 初期化 */
void WinTimer_Initialize(INTNO intno)
{
	DWORD dwThreadId;

	/* 擬似割り込み番号を設定 */
	intnoTimer = intno;

	/* タイマ用イベントの作成 */
	hEventTimer = CreateEvent(NULL, FALSE, FALSE, NULL);

	/* マルチメディアタイマの開始 */
	timeSetEvent(10, 1, (LPTIMECALLBACK)hEventTimer, 0, TIME_PERIODIC | TIME_CALLBACK_EVENT_PULSE);

	CreateThread(NULL, 0, WinTimer_Thread, 0, 0, &dwThreadId);
}


/* タイマ割り込み用スレッド関数 */
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
