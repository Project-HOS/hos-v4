/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル タスク管理機能                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* タスクの起動 */
ER act_tsk(
		ID tskid)	/* タスクID */
{
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM       *tcb_ram;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < TMIN_TSKID || tskid > TMAX_TSKID) )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* タスクコントロールブロック取得 */
	if ( tskid == TSK_SELF )
	{
		/* 自タスク指定時の変換 */
#ifdef HOS_ERCHK_E_ID
		if ( mknl_sns_ctx() )
		{
			/* 非タスクコンテキストで TSK_SELF指定は不正 */
			mknl_unl_sys();		/* システムのロック解除 */
			return E_ID;		/* 不正ID番号 */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
	}
	else
	{
		/* ID番号指定時の変換 */
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();		/* システムのロック解除 */
			return E_NOEXS;		/* オブジェクト未生成 */
		}
#endif
	}

	/* オブジェクト状態判定 */
	if ( mknl_get_tskstat(&tcb_ram->mtcb) != TTS_DMT )
	{
		/* 既に実行状態なら起動要求をキューイング */
#ifdef HOS_ERCHK_E_QOVR
		if ( tcb_ram->actcnt >= TMAX_ACTCNT )
		{
			mknl_unl_sys();	/* システムのロック解除 */
			return E_QOVR;	/* キューイングオーバーフロー */
		}
#endif

		/* 起動要求をキューイング */
		tcb_ram->actcnt++;
	}
	else
	{
		/* 休止状態ならタスクを起動する */
		tcb_rom = tcb_ram->tcbrom;
	
		/* 実行コンテキスト登録 */
		mknl_sta_tsk(
				&tcb_ram->mtcb,			/* 登録するタスク */
				tcb_rom->exinf,			/* タスクの拡張情報 */
				(FP)kernel_task_entry,	/* タスクの起動番地 */
				tcb_rom->itskpri,		/* タスクの起動時優先度 */
				tcb_rom->stksz,			/* タスクのスタック領域サイズ */
				tcb_rom->stk			/* タスクのスタック領域の先頭番地 */
			);	
		tcb_ram->suscnt = 0;	/* 強制待ちネストクリア */
		tcb_ram->wupcnt = 0;	/* 待ち解除要求キューイングクリア */
		
		mknl_exe_dsp();			/* タスクディスパッチの実行 */
		mknl_exe_tex();			/* 例外処理の実行 */
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;	/* 成功 */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
