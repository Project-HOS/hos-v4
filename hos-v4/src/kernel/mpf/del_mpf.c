/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 固定長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"
#include "knl_mem.h"



/* 固定長メモリプールの削除 */
ER del_mpf(
		ID mpfid)	/* 削除対象の固定長メモリプールのID番号 */
{
	const T_KERNEL_MPFCB_ROM *mpfcb_rom;
	T_KERNEL_MPFCB_RAM *mpfcb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mpfid < TMIN_MPFID || mpfid > TMAX_MPFID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	mpfcb_ram = kernel_mpfcb_ram_tbl[mpfid - TMIN_MPFID];
	mpfcb_rom = mpfcb_ram->mpfcb_rom;

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mpfcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif
	
	/* 待ちタスクの解除 */
	mknl_clr_que(&mpfcb_ram->que);
	
	/* メモリの解放 */
	kernel_fre_mem(mpfcb_rom->mpf);	
	kernel_fre_mem(mpfcb_ram);
	kernel_mpfcb_ram_tbl[mpfid - TMIN_MPFID] = NULL;
	
	mknl_exe_dsp();		/* タスクディスパッチの実行 */
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
