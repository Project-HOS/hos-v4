/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル タスク制御                                              */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* タスクの起動(起動コード指定) */
ER sta_tsk(
		ID tskid,		/* 起動対象のタスクID番号 */
		VP_INT stacd)	/* タスクの起動コード */
{
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID 範囲チェック */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < TMIN_TSKID || tskid > TMAX_TSKID )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* IDからタスクコントロールブロックRAM部取得 */
	tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( tcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	/* オブジェクトの状態チェック */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) != TTS_DMT )	/* 休止状態でなければ */
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_OBJ;	/* オブジェクト状態エラー */
	}
#endif

	/* タスクコントロールブロックROM部取得 */
	tcb_rom = tcb_ram->tcbrom;
	
	/* 実行コンテキスト登録 */
	mknl_sta_tsk(
				&tcb_ram->mtcb,			/* 登録するタスク */
				stacd,					/* タスクの拡張情報 */
				(FP)kernel_task_entry,	/* タスクの起動番地 */
				tcb_rom->itskpri,		/* タスクの起動時優先度 */
				tcb_rom->stksz,			/* タスクのスタック領域サイズ */
				tcb_rom->stk			/* タスクのスタック領域の先頭番地 */
			);	
	tcb_ram->suscnt  = 0;
	tcb_ram->wupcnt  = 0;
	
	/* タスクディスパッチの実行 */
	mknl_exe_dsp();

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
