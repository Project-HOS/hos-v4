/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (Windows用)                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <stdlib.h>
#include "kernel.h"
#include "hospac.h"



/* タスク情報 */
typedef struct t_TaskInfo
{
	VP_INT exinf;			/* タスクの実行時パラメータ */
	FP     task;			/* タスクの起動番地 */
} T_TaskInfo;


/* スレッド削除用リスト */
typedef struct t_hospac_dellist
{
	HANDLE hThread;					/* 削除するスレッドハンドル */
	struct t_hospac_dellist *next;	/* 次の削除リスト */
} T_HOSPAC_DELLIST;



DWORD WINAPI TaskEntry(LPVOID param);	/* スレッドの開始関数 */



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
void hospac_cre_ctx(
		T_HOSPAC_CTXINF *pk_ctxinf,		/* コンテキストを作成するアドレス */
		VP_INT          exinf,			/* タスクの実行時パラメータ */
		FP              task,			/* タスクの起動番地 */
		SIZE            stksz,			/* スタック領域のサイズ */
		VP              stk)			/* スタック領域の先頭番地 */
{
	T_TaskInfo *pInfo;
	DWORD      dwThreadId;

	/* タスク情報を格納 */
	pInfo = (T_TaskInfo *)GlobalAlloc(GMEM_FIXED, sizeof(T_TaskInfo));
	pInfo->task  = task;
	pInfo->exinf = exinf;

	/* スレッドをサスペンド状態で生成 */
	pk_ctxinf->hThread = CreateThread(NULL, 0, TaskEntry,
								(LPVOID)&pInfo, CREATE_SUSPENDED, &dwThreadId);
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
void hospac_swi_ctx(
		T_HOSPAC_CTXINF *pk_pre_ctxinf,		/* 現在のコンテキストの保存先 */
		T_HOSPAC_CTXINF *pk_nxt_ctxinf)		/* 新たに実行するコンテキスト */
{
	T_HOSPAC_DELLIST *pDelList;
	T_HOSPAC_DELLIST *pDelListTmp;
	DWORD dwCount;
	
	/* スレッドが異なれば切り替える */
	if ( pk_nxt_ctxinf != pk_pre_ctxinf )
	{
		/* 切り替え対象がサスペンド中であることを確認 */
		for ( ; ; )
		{
			/* サスペンドカウンタを得る為にサスペンドさせてみる */
			while ( (dwCount = SuspendThread(pk_nxt_ctxinf->hThread)) == 0xffffffff )
			{
				Sleep(0);
			}
			ResumeThread(pk_nxt_ctxinf->hThread);
			
			/* カウンタが1でなければサスペンドしている */
			if ( dwCount > 1 )
			{
				break;
			}

			/* サスペンド完了まで待つ */
			Sleep(1);
		}

		/* 切り替え先のスレッドを起こす */
		ResumeThread(pk_nxt_ctxinf->hThread);

		/* 自分自身をサスペンドさせる */
		SuspendThread( GetCurrendT
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
		dis_dsp();
		isig_tim();		/* タイムティック供給 */
		ena_dsp();
		Sleep(10);
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
