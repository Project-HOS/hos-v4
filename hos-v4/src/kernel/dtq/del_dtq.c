/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル データキュー                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"
#include "knl_mem.h"



/* データキューの削除 */
ER del_dtq(
		ID dtqid)	/* 削除対象のデータキューのID番号 */
{
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;
	T_KERNEL_DTQCB_RAM *dtqcb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < KERNEL_TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();		/* システムのロック */

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);
	dtqcb_rom = dtqcb_ram->dtqcb_rom;

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif
	
	/* タスクの解除 */
	mknl_clr_que(&dtqcb_ram->sndque);	/* 送信待ちタスクの解除 */
	mknl_clr_que(&dtqcb_ram->rcvque);	/* 受信待ちタスクの解除 */
	
	/* メモリの解放 */
	kernel_fre_mem(dtqcb_rom->dtq);
	kernel_fre_mem(dtqcb_ram);
	KERNEL_DTQID_TO_DTQCB_RAM(dtqid) = NULL;
	
	mknl_exe_dsp();		/* タスクディスパッチの実行 */
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
