/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル データキュー                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
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
	if ( dtqid < TMIN_DTQID || dtqid > TMAX_DTQID )
	{
		return E_ID;	/* 不正ID */
	}
#endif

	mknl_loc_sys();		/* システムのロック */

	dtqcb_ram = kernel_dtqcb_ram_tbl[dtqid - TMIN_DTQID];
	dtqcb_rom = dtqcb_ram->dtqcbrom;

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
	kernel_dtqcb_ram_tbl[dtqid - TMIN_DTQID] = NULL;
	
	mknl_exe_dsp();		/* タスクディスパッチの実行 */
	mknl_exe_tex();		/* 例外処理の実行 */
	
	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
