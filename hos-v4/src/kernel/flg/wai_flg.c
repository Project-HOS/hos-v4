/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* イベントフラグ待ち */
ER wai_flg(
		ID     flgid,		/* 待ち対象のイベントフラグのID番号 */
		FLGPTN waiptn,		/* 待ちビットパターン */
		MODE   wfmode,		/* 待ちモード */
		FLGPTN *p_flgptn)	/* 待ち解除時のビットパターン格納アドレス */
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
	T_MKNL_TCB      *mtcb;
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
	flgcb_rom = flgcb_ram->flgcb_rom;

	/* オブジェクトの存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( flgcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
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
		/* 条件を満たしていなければ待ちに入る */
		mtcb       = mknl_get_run_tsk();		/* 実行中タスクを取得 */
		mtcb->data = &flginf;					/* 待ち状態を保存 */
		mknl_wai_tsk(mtcb, TTW_FLG);
		mknl_add_que(&flgcb_ram->que, mtcb, flgcb_rom->flgatr);	/* 待ち行列に追加 */
		
		ercd = (ER)mknl_exe_dsp();	/* タスクディスパッチ実行 */
		
		/* 条件を満たして解除されたのなら */
		if ( ercd == E_OK )
		{
			*p_flgptn = flginf.waiptn;			/* 解除時のフラグパターンを格納 */
		}
		
		mknl_exe_tex();		/* 例外処理の実行 */
	}
	
	mknl_unl_sys();	/* システムのロック解除 */
	
	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
