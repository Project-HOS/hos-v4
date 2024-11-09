/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* イベントフラグのクリア */
ER clr_flg(
		ID     flgid,	/* クリア対象のイベントフラグのID番号 */
		FLGPTN clrptn)	/* クリアするビットパターン(ビット毎の反転値) */
{
	T_KERNEL_FLGCB_RAM *flgcb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < KERNEL_TMIN_FLGID || flgid > KERNEL_TMAX_FLGID )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_NOEXS;
	}
#endif

	/* フラグのクリア */
	flgcb_ram->flgptn = (FLGPTN)(flgcb_ram->flgptn & clrptn);

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
