/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* イベントフラグ待ち(タイムアウトあり) */
ER twai_flg(
		ID     flgid,
		FLGPTN waiptn,
		MODE   wfmode,
		FLGPTN *p_flgptn,
		TMO    tmout)
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
	T_KERNEL_FLGINF flginf;
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( flgid < TMIN_FLGID || flgid > TMAX_FLGID )
	{
		return E_ID;	/* 不正ID番号 */
	}
#endif

	/* パラメータのチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( (wfmode != TWF_ANDW && wfmode != TWF_ORW) || waiptn == 0)
	{
		return E_PAR;	/* パラメータエラー */
	}
	if ( tmout < TMO_FEVR )
	{
		return E_PAR;
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

	flgcb_ram = KERNEL_FLGID_TO_FLGCB_RAM(flgid);
	flgcb_rom = flgcb_ram->flgcbrom;

	/* オブジェクトの存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		return E_NOEXS;
	}
#endif

	/* サービスコール不正使用チェック */
#ifdef HOS_ERCHK_E_ILUSE
	if ( !(flgcb_rom->flgatr & TA_WMUL) && mknl_ref_qhd(&flgcb_ram->que) != NULL )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_ILUSE;		/* サービスコール不正使用 */
	}
#endif

	/* 待ち条件設定 */
	flginf.waiptn = waiptn;
	flginf.wfmode = wfmode;
	
	/* フラグチェック */
	if ( kernel_chk_flg(flgcb_ram, &flginf) )
	{
		/* 既に条件を満たしているなら */
		*p_flgptn = flgcb_ram->flgptn;		/* 解除時のフラグパターンを格納 */
		if ( flgcb_rom->flgatr & TA_CLR )
		{
			flgcb_ram->flgptn = 0;		/* クリア属性があればクリア */
		}
		ercd = E_OK;
	}
	else
	{
		/* 条件を満たしていなければ */
		if ( tmout == TMO_POL )
		{
			/* ポーリングならタイムアウト */
			ercd = E_TMOUT;
		}
		else
		{
			/* 待ちに入る */
			flgcb_ram->mtcb = mknl_get_run_tsk();		/* 実行中タスクを取得 */
			flgcb_ram->mtcb->data = &flginf;			/* 待ち状態を保存 */
			mknl_wai_tsk(flgcb_ram->mtcb, TTW_FLG);
			if ( tmout == TMO_FEVR )
			{
				/* 無限待ちでなければタイムアウト設定 */
				mknl_add_tmout(flgcb_ram->mtcb, (RELTIM)tmout);
			}
			
			ercd = (ER)mknl_exe_dsp();	/* タスクディスパッチ実行 */
			
			/* 条件を満たして解除されたのなら */
			if ( ercd == E_OK )
			{
				*p_flgptn = flginf.waiptn;		/* 解除時のフラグパターンを格納 */
			}
			
			mknl_exe_tex();		/* 例外処理の実行 */
		}
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
