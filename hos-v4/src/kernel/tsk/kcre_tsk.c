/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include <string.h>
#include "knl_tsk.h"
#include "knl_mem.h"



/* タスクの生成(カーネル内部) */
ER kernel_cre_tsk(
		ID           tskid,		/* 生成対象のタスクID番号 */
		const T_CTSK *pk_ctsk)	/* タスク生成情報を入れたパケットへのポインタ */
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_KERNEL_TCB_ROM *tcb_rom;
	SIZE memsize;
	UB   *memptr;
	
	/* 必要なメモリサイズを計算 */
	memsize = sizeof(T_KERNEL_TCB_RAM) + sizeof(T_KERNEL_TCB_ROM);
	if ( pk_ctsk->stk == NULL )
	{
		memsize += pk_ctsk->stksz;	/* スタックサイズを加算 */
	}
	
	/* メモリ確保 */
	memptr = (UB *)kernel_alc_mem(memsize);
#ifdef HOS_ERCHK_E_NOMEM
	if ( memptr == NULL )
	{
		return E_NOMEM;		/* メモリ不足 */
	}
#endif

	/* ポインタ設定 */	
	tcb_ram  = (T_KERNEL_TCB_RAM *)memptr;
	memptr  += sizeof(T_KERNEL_TCB_RAM);
	tcb_rom  = (T_KERNEL_TCB_ROM *)memptr;
	if ( pk_ctsk->stk == NULL )
	{
		memptr  += sizeof(T_KERNEL_TCB_ROM);
		tcb_rom->stk = (VP)memptr;
	}
	else
	{
		tcb_rom->stk = pk_ctsk->stk;
	}

	/* μカーネルタスクの初期化 */
	memset(&tcb_ram->mtcb, 0, sizeof(tcb_ram->mtcb));
	mknl_ini_tsk(&tcb_ram->mtcb);

	/* 値設定 */
	tcb_ram->actcnt  = 0;					/* 起動要求キューイング数 */
	tcb_ram->suscnt  = 0;					/* SUSPEND要求ネスト数 */
	tcb_ram->wupcnt  = 0;					/* 起床要求キューイング数 */
	tcb_ram->tcb_rom = tcb_rom;				/* タスクコントロールブロックROM部へのポインタ */
	tcb_rom->tskatr  = pk_ctsk->tskatr;		/* タスク属性 */
	tcb_rom->exinf   = pk_ctsk->exinf;		/* タスクの拡張情報 */
	tcb_rom->task    = pk_ctsk->task;		/* タスクの起動番地 */
	tcb_rom->itskpri = pk_ctsk->itskpri;	/* タスクの起動時優先度 */
	tcb_rom->stksz   = pk_ctsk->stksz;		/* タスクのスタックのサイズ（バイト数） */

	/* タスクコントロールブロックテーブルに登録 */
	kernel_tcb_ram_tbl[tskid - KERNEL_TMIN_TSKID] = tcb_ram;

	/* 実行状態で生成 */
	if ( pk_ctsk->tskatr & TA_ACT )
	{
		/* 実行コンテキスト登録 */
		mknl_sta_tsk(
				&tcb_ram->mtcb,			/* 登録するタスク */
				tcb_rom->exinf,			/* タスクの拡張情報 */
				(FP)kernel_task_entry,	/* タスクの起動番地 */
				tcb_rom->itskpri,		/* タスクの起動時優先度 */
				tcb_rom->stksz,			/* タスクのスタック領域サイズ */
				tcb_rom->stk			/* タスクのスタック領域の先頭番地 */
			);	
		
		mknl_exe_dsp();		/* タスクディスパッチの実行 */
		mknl_exe_tex();		/* 例外処理の実行 */
	}

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
