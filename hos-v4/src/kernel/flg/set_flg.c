/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* イベントフラグのセット */
ER set_flg(
		ID     flgid,		/* セット対象のイベントフラグのID番号 */
		FLGPTN setptn)		/* セットするビットパターン */
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
	T_KERNEL_FLGCB_RAM *flgcb_ram;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < TMIN_FLGID || flgid > TMAX_FLGID )
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

	/* フラグのセット */
	flgcb_ram->flgptn |= setptn;

	/* 待ちタスクがあれば起床チェック */
	if ( flgcb_ram->mtcb != NULL )
	{
		flgcb_rom = flgcb_ram->flgcbrom;
		if ( kernel_chk_flg(flgcb_ram) )
		{
			/* 起床条件を満たしているなら */
			mknl_del_que(flgcb_ram->mtcb);			/* 待ち行列から外す */
			mknl_del_tmout(flgcb_ram->mtcb);		/* タイムアウト解除 */
			mknl_wup_tsk(flgcb_ram->mtcb, E_OK);	/* 待ちタスクの起床 */

			/* タスクディスパッチの実行 */
			mknl_exe_dsp();
		}
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;	/* 正常終了 */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
