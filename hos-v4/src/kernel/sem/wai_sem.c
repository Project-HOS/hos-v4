/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル セマフォ                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* セマフォ資源の獲得 */
ER wai_sem(
		ID semid)	/* 資源獲得対象のセマフォID番号 */
{
	const T_KERNEL_SEMCB_ROM *semcb_rom;
	T_KERNEL_SEMCB_RAM       *semcb_ram;
	T_MKNL_TCB *mtcb;
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( semid < KERNEL_TMIN_SEMID || semid > KERNEL_TMAX_SEMID )
	{
		return E_ID;	/* ID不正 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* コンテキストチェック */
#ifdef HOS_ERCHK_E_CTX
	if ( mknl_sns_wai() )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_CTX;	/* コンテキスト不正 */
	}
#endif

	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	/* セマフォ資源が獲得できれば成功 */
	if ( semcb_ram->semcnt > 0 )
	{
		semcb_ram->semcnt--;	/* セマフォ資源の獲得 */
		ercd = E_OK;
	}
	else
	{
		semcb_rom = semcb_ram->semcb_rom;

		/* タスクを待ち状態にする */
		mtcb = mknl_get_run_tsk();
		mknl_wai_tsk(mtcb, TTW_SEM);
		mknl_add_que(&semcb_ram->que, mtcb, semcb_rom->sematr);	/* 待ち行列に追加 */
	
		ercd = (ER)mknl_exe_dsp();	/* タスクディスパッチの実行 */
		mknl_exe_tex();				/* 例外処理の実行 */
	}
		
	mknl_unl_sys();		/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
