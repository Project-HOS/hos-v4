/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* イベントフラグ待ち */
ER wai_flg(
		ID     flgid,		/* 待ち対象のイベントフラグのID番号 */
		FLGPTN waiptn,		/* 待ちビットパターン */
		MODE   wfmode,		/* 待ちモード */
		FLGPTN *p_flgptn)	/* 待ち解除時のビットパターン格納アドレス */
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
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

	/* オブジェクトの存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	/* サービスコール不正使用チェック(TA_WMUL 未サポート)  */
#ifdef HOS_ERCHK_E_ILUSE
	if ( flgcb_ram->mtcb != NULL )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_ILUSE;		/* サービスコール不正使用 */
	}
#endif

	/* 待ち条件設定 */
	flgcb_ram->waiptn = waiptn;
	flgcb_ram->wfmode = wfmode;
	
	/* フラグチェック */
	if ( kernel_chk_flg(flgcb_ram) )
	{
		/* 既に条件を満たしているなら */
		flgcb_rom = flgcb_ram->flgcbrom;
		*p_flgptn = flgcb_ram->flgptn;		/* 解除時のフラグパターンを格納 */
		if ( flgcb_rom->flgatr & TA_CLR )
		{
			flgcb_ram->flgptn = 0;		/* クリア属性があればクリア */
		}
		ercd = E_OK;
	}
	else
	{
		/* 条件を満たしていなければ待ちに入る */
		flgcb_ram->mtcb = mknl_get_run_tsk();
		mknl_wai_tsk(flgcb_ram->mtcb, TTW_FLG);

		/* タスクディスパッチ実行 */
		ercd = (ER)mknl_exe_dsp();

		/* 条件を満たして解除されたのなら */
		if ( ercd == E_OK )
		{
			flgcb_rom = flgcb_ram->flgcbrom;
			*p_flgptn = flgcb_ram->flgptn;		/* 解除時のフラグパターンを格納 */
			if ( flgcb_rom->flgatr & TA_CLR )
			{
				flgcb_ram->flgptn = 0;		/* クリア属性があればクリア */
			}		
		}
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
