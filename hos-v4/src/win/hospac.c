/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    プロセッサ抽象化コンポーネント (Windows用)                            */
/*                                                                          */
/*                               Copyright (C) 1998-2002 by Ryuji Fuchikami */
/* ------------------------------------------------------------------------ */


#include <stdlib.h>
#include "kernel.h"
#include "hospac.h"




/* スレッド削除用リスト */
typedef struct t_hospac_dellist
{
	HANDLE hThread;					/* 削除するスレッドハンドル */
	struct t_hospac_dellist *next;	/* 次の削除リスト */
} T_HOSPAC_DELLIST;



static HANDLE           hospac_hSem      = NULL;	/* システムの排他制御用セマフォ */
static T_HOSPAC_DELLIST *hospac_pDelList = NULL;	/* スレッド削除用リスト */



/* システムの初期化 */
void hospac_ini_sys(void)
{
	/* 割り込み禁止に見立てるセマフォの作成 */
	hospac_hSem = CreateSemaphore(NULL, 1, 1, NULL);
}


/* 割り込み許可 */
void hospac_ena_int(void)
{
	ReleaseSemaphore(hospac_hSem, 1, NULL);
}


/* 割り込み禁止 */
void hospac_dis_int(void)
{
	WaitForSingleObject(hospac_hSem, INFINITE);
}



/* 実行コンテキストの作成 */
void hospac_cre_cnt(
		T_HOSPAC_CTXINF *pk_ctxinf,		/* コンテキストを作成するアドレス */
		VP_INT exinf,					/* タスクの実行時パラメータ */
		FP    task,						/* タスクの起動番地 */
		SIZE  stksz,					/* スタック領域のサイズ */
		VP    stk)						/* スタック領域の先頭番地 */
{
	DWORD dwThreadId;
	pk_ctxinf->hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)task,
								(LPVOID)exinf, CREATE_SUSPENDED, &dwThreadId);
}


/* 実行コンテキストの削除 */
void hospac_del_cnt(T_HOSPAC_CTXINF *pk_ctxinf)
{
	T_HOSPAC_DELLIST *pDelList;

	/* 削除リストの作成 */
	pDelList = (T_HOSPAC_DELLIST *)malloc(sizeof(T_HOSPAC_DELLIST));
	pDelList->hThread = pk_ctxinf->hThread;

	/* 削除リストに追加 */
	if ( hospac_pDelList == NULL )
	{
		pDelList->next = NULL;
	}
	else
	{
		pDelList->next = hospac_pDelList;
	}
	hospac_pDelList = pDelList;
}


/* 実行コンテキストの切替 */
void hospac_swi_cnt(
		T_HOSPAC_CTXINF *pk_pre_ctxinf,		/* 現在のコンテキストの保存先 */
		T_HOSPAC_CTXINF *pk_nxt_ctxinf)		/* 新たに実行するコンテキスト */
{
	static volatile HANDLE hPrevThread;
	T_HOSPAC_DELLIST *pDelList;
	T_HOSPAC_DELLIST *pDelListTmp;;

	/* 初回のアイドルからの起動ならスレッドハンドルを作成 */
	if ( pk_pre_ctxinf->hThread == NULL )
	{
		HANDLE hProcess;
		hProcess = GetCurrentProcess();
		DuplicateHandle(hProcess, GetCurrentThread(), hProcess,
					&pk_pre_ctxinf->hThread, 0, TRUE, DUPLICATE_SAME_ACCESS);
	}

	/* 現在のスレッドを保存 */
	hPrevThread = pk_pre_ctxinf->hThread;
	
	/* スレッドが異なれば切り替える */
	if ( pk_nxt_ctxinf != pk_pre_ctxinf )
	{
		/* 新たなスレッドに実行を切り替える */
		ResumeThread(pk_nxt_ctxinf->hThread);
		SuspendThread(pk_pre_ctxinf->hThread);

		/* 直前のスレッドが完全にサスペンドするまで待つ */
		while ( SuspendThread(hPrevThread) == 2 )
		{
			ResumeThread(hPrevThread);
			Sleep(0);
		}
		ResumeThread(hPrevThread);
	}

	/* 削除リストにスレッドがあればこのタイミングで削除 */
	pDelList = hospac_pDelList;
	while ( pDelList != NULL )
	{
		TerminateThread(pDelList->hThread, 0);
		CloseHandle(pDelList->hThread);
		pDelListTmp = pDelList;
		pDelList = pDelList->next;
		free(pDelListTmp);
	}
	hospac_pDelList = NULL;
}


/* 例外処理実行設定 */
void hospac_set_tex(
		T_HOSPAC_CTXINF *pk_pre_ctxinf,		/* 例外処理を設定するコンテキスト */
		void (*exp)(TEXPTN),				/* 例外処理ハンドラのアドレス */
		TEXPTN rasptn)						/* 例外処理ハンドラに渡す例外要因 */
{
	/* 頑張ればごまかしは作れそうだがひとまず保留 */
	/* どっちみち Windowsではスタックを同じままの分岐が困難なので */
	/* longjmp などが発行できないとおもふ */

	return;
}


/* アイドル時の処理 */
void hospac_idle(void)
{
	/* マイコンなら省消費電力モードに切り替えるなど可能 */

	/* Windows ではここで他のプロセスにプロセッサタイムを供給とともに */
	/* インターバルタイマのエミュレーション */
	for ( ; ; )
	{
		isig_tim();		/* タイムティック供給 */
		Sleep(10);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
