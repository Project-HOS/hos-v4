/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"
#include "knl_mem.h"



/* イベントフラグの削除 */
ER del_flg(
		ID flgid)	/* 削除対象のイベントフラグのID番号 */
{
	T_KERNEL_FLGCB_RAM *flgcb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < KERNEL_TMIN_FLGID || flgid > KERNEL_TMAX_FLGID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();		/* システムのロック */

	flgcb_ram = kernel_flgcb_ram_tbl[flgid - KERNEL_TMIN_FLGID];

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif
	
	/* 待ちタスクの解除 */
	mknl_clr_que(&flgcb_ram->que);
	
	/* メモリの解放 */
	kernel_fre_mem(flgcb_ram);
	kernel_flgcb_ram_tbl[flgid - KERNEL_TMIN_FLGID] = NULL;
	
	mknl_exe_dsp();		/* タスクディスパッチの実行 */
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
