/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル メッセージバッファ                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "knl_mem.h"


/* メッセージバッファの削除 */
ER del_mbf(
		ID mbfid)	/* 削除対象のメッセージバッファのID番号 */
{
	T_KERNEL_MBFCB_RAM *mbfcb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbfid < TMIN_MBFID || mbfid > KERNEL_TMAX_MBFID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	mbfcb_ram = kernel_mbfcb_ram_tbl[mbfid - TMIN_MBFID];

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbfcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif
	
	/* 待ちタスクの解除 */
	mknl_clr_que(&mbfcb_ram->sndque);
	mknl_clr_que(&mbfcb_ram->rcvque);
	
	/* メモリの解放 */
	kernel_fre_mem(mbfcb_ram);
	kernel_mbfcb_ram_tbl[mbfid - TMIN_MBFID] = NULL;
	
	mknl_exe_dsp();		/* タスクディスパッチの実行 */
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
