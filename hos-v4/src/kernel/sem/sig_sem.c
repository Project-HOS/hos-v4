/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル セマフォ                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* セマフォ資源の返却 */
ER sig_sem(
		ID semid)		/* セマフォ資源返却対象のセマフォのID番号 */
{
	const T_KERNEL_SEMCB_ROM *semcb_rom;
	T_KERNEL_SEMCB_RAM *semcb_ram;
	T_MKNL_TCB *mtcb;
	
	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( semid < TMIN_SEMID || semid > TMAX_SEMID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();	/* システムのロック */
	
	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);
	
	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif
	
	semcb_rom = semcb_ram->semcb_rom;
	
	/* キューイングオーバーフローチェック */
#ifdef HOS_ERCHK_E_QOVR
	if ( semcb_ram->semcnt >= semcb_rom->maxsem )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_QOVR;
	}
#endif
	
	mtcb = mknl_ref_qhd(&semcb_ram->que);	/* 待ち行列先頭からタスク取り出し */
	if ( mtcb != NULL )
	{
		/* 待ちタスクがあれば待ち解除 */
		mknl_rmv_que(mtcb);						/* セマフォの待ち行列から削除 */
		mknl_rmv_tmout(mtcb);					/* タイムアウト待ち行列から削除 */
		mknl_wup_tsk(mtcb, E_OK);				/* タスクの待ち解除 */
		
		mknl_exe_dsp();		/* タスクディスパッチの実行 */
		mknl_exe_tex();		/* 例外処理の実行 */
	}
	else
	{
		semcb_ram->semcnt++;	/* セマフォ資源返却 */
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;	/* 成功 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
