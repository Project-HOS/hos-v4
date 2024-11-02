/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル セマフォ                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"
#include "knl_mem.h"


/* セマフォの削除 */
ER del_sem(
		ID semid)	/* 削除対象のセマフォのID番号 */
{
	T_KERNEL_SEMCB_RAM *semcb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( semid < KERNEL_TMIN_SEMID || semid > KERNEL_TMAX_SEMID )
	{
		return E_ID;	/* 不正ID */
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
	
	/* 待ちタスクの解除 */
	mknl_clr_que(&semcb_ram->que);
	
	/* メモリの解放 */
	kernel_fre_mem(semcb_ram);
	KERNEL_SEMID_TO_SEMCB_RAM(semid) = NULL;
	
	mknl_exe_dsp();		/* タスクディスパッチの実行 */
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
