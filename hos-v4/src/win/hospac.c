/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (Windows用)                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <stdlib.h>
#include "hospac.h"
#include <tchar.h>


/* タスク情報 */
typedef struct t_TaskInfo
{
	VP_INT exinf;			/* タスクの実行時パラメータ */
	FP     task;			/* タスクの起動番地 */
} T_TaskInfo;



DWORD WINAPI TaskEntry(LPVOID param);	/* スレッドの開始関数 */
void  HookPrimaryThread(void);			/* プライマリスレッドのフック */

HANDLE hospac_hSem  = NULL;				/* システムの排他制御用セマフォ */
BOOL   hospac_blInt = FALSE;			/* 割り込み処理中フラグ */

static DWORD  hPrimaryThreadId;			/* プライマリスレッドID */
static HANDLE hThreadDelete = NULL;		/* 削除するスレッドハンドル */



/* システムの初期化 */
void hospac_ini_sys(void)
{
	/* プライマリスレッドIDの保存 */
	hPrimaryThreadId = GetCurrentThreadId();

	/* 割り込み禁止に見立てるセマフォの作成 */
	hospac_hSem = CreateSemaphore(NULL, 0, 1, NULL);
}


/* 割り込み許可 */
void hospac_ena_int(void)
{
	if ( !hospac_blInt )
	{
		ReleaseSemaphore(hospac_hSem, 1, NULL);
	}
}


/* 割り込み禁止 */
void hospac_dis_int(void)
{
	if ( !hospac_blInt )
	{
		WaitForSingleObject(hospac_hSem, INFINITE);
	}
}


/* 実行コンテキストの作成 */
void hospac_cre_ctx(
		T_HOSPAC_CTXINF *pk_ctxinf,		/* コンテキストを作成するアドレス */
		VP_INT          exinf,			/* タスクの実行時パラメータ */
		FP              task,			/* タスクの起動番地 */
		SIZE            stksz,			/* スタック領域のサイズ */
		VP              stk)			/* スタック領域の先頭番地 */
{
	T_TaskInfo *pInfo;

	/* タスク情報を格納 */
	pInfo = (T_TaskInfo *)GlobalAlloc(GMEM_FIXED, sizeof(T_TaskInfo));
	pInfo->task  = task;
	pInfo->exinf = exinf;
	
	/* 生成 */
	pk_ctxinf->blIntSuspend = FALSE;
	pk_ctxinf->hThread = CreateThread(NULL, 0, TaskEntry, (LPVOID)pInfo,
									CREATE_SUSPENDED, &pk_ctxinf->dwThreadId);
}


/* スレッドの開始関数 */
DWORD WINAPI TaskEntry(LPVOID param)
{
	T_TaskInfo Info;

	Info = *(T_TaskInfo *)param;

	GlobalFree((HGLOBAL)param);

	Info.task(Info.exinf);

	return 0;
}


/* 実行コンテキストの削除 */
void hospac_del_ctx(T_HOSPAC_CTXINF *pk_ctxinf)
{
	if ( GetCurrentThreadId() != pk_ctxinf->dwThreadId )
	{
		/* 実行中スレッドでなければ即削除 */
		TerminateThread(pk_ctxinf->hThread, 0);
	}
	else
	{
		/* 実行中スレッドなら削除を予約 */
		hThreadDelete = pk_ctxinf->hThread;
	}
}


/* 実行コンテキストの切替 */
void hospac_swi_ctx(
		T_HOSPAC_CTXINF *pk_pre_ctxinf,		/* 現在のコンテキストの保存先 */
		T_HOSPAC_CTXINF *pk_nxt_ctxinf)		/* 新たに実行するコンテキスト */
{
	DWORD dwCount;

	if ( hospac_blInt )
	{
		return;
	}

	/* スレッドが異なれば切り替える */
	if ( pk_nxt_ctxinf != pk_pre_ctxinf )
	{
		/* 切り替え対象がサスペンド中であることを確認 */
		for ( ; ; )
		{
			/* サスペンドカウンタを得る為にサスペンドさせてみる */
			dwCount = SuspendThread(pk_nxt_ctxinf->hThread);
			ResumeThread(pk_nxt_ctxinf->hThread);
			
			/* カウンタが0でなければサスペンドしている */
			if ( dwCount > 0 )
			{
				break;
			}
			
			/* サスペンド完了まで待つ */
			Sleep(1);
		}
		
		/* 切り替え先のスレッドを起こす */
		ResumeThread(pk_nxt_ctxinf->hThread);
		
		/* セマフォを返却 */
		if ( pk_nxt_ctxinf->blIntSuspend )
		{
			pk_nxt_ctxinf->blIntSuspend = FALSE;
			ReleaseSemaphore(hospac_hSem, 1, NULL);
		}
		
		/* プライマリスレッドIのフック */
		if ( hPrimaryThreadId == GetCurrentThreadId() )
		{
			HookPrimaryThread();
		}

		/* 自分自身をサスペンドさせる */
		SuspendThread(GetCurrentThread());
	}
	
	/* 削除予約のスレッドがあれば削除 */
	if ( hThreadDelete != NULL )
	{
		TerminateThread(hThreadDelete, 0);
		CloseHandle(hThreadDelete);
		hThreadDelete = NULL;
	}
}


/* アイドル時の処理 */
void hospac_idle(void)
{
	/* マイコンなら省消費電力モードに切り替えるなど可能 */
	
	/* 他のプロセスに実行タイミングを与える */
	Sleep(1);
}


/* プライマリスレッドのフック */
void  HookPrimaryThread(void)
{
	/* ダイアログを表示 */
	MessageBox(NULL, _T("OKを押すと終了します"), _T("Hyper Operationg System V4 for Win32"), MB_OK);

	/* 終了 */
	ExitProcess(0);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
