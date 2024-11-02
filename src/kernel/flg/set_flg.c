/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* イベントフラグのセット */
ER set_flg(
		ID     flgid,		/* セット対象のイベントフラグのID番号 */
		FLGPTN setptn)		/* セットするビットパターン */
{
	const T_KERNEL_FLGCB_ROM *flgcb_rom;
	T_KERNEL_FLGCB_RAM       *flgcb_ram;
	T_KERNEL_FLGINF          *pk_flginf;
	T_MKNL_TCB *mtcb;
	T_MKNL_TCB *mtcb_next;
	BOOL       wupflg = FALSE;	/* 起動フラグ */

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

	flgcb_rom = flgcb_ram->flgcb_rom;

	/* フラグのセット */
	flgcb_ram->flgptn = (FLGPTN)(flgcb_ram->flgptn | setptn);

	/* 待ちタスクがあれば起床チェック */
	mtcb = mknl_ref_qhd(&flgcb_ram->que);
	while ( mtcb != NULL )
	{
		mtcb_next = mknl_ref_nxt(&flgcb_ram->que, mtcb);	/* 次の待ちタスクを取得 */
		
		/* フラグチェック */
		pk_flginf = (T_KERNEL_FLGINF *)mtcb->data;
		if ( kernel_chk_flg(flgcb_ram, pk_flginf) )
		{
			/* 起床条件を満たしているなら */
			pk_flginf->waiptn = flgcb_ram->flgptn;	/* 現在のフラグパターンを格納 */
			if ( flgcb_rom->flgatr & TA_CLR )
			{
				flgcb_ram->flgptn = 0;				/* クリア属性があればクリア */
			}

			/* 待ち解除 */
			mknl_rmv_que(mtcb);			/* 待ち行列から外す */
			mknl_rmv_tmout(mtcb);		/* タイムアウト解除 */
			mknl_wup_tsk(mtcb, E_OK);	/* 待ちタスクの起床 */
			wupflg = TRUE;
		}
		mtcb = mtcb_next;	/* 次のタスクに進める */
	}

	/* 起動を行ったタスクがあるならディスパッチを行う */
	if ( wupflg )
	{
		mknl_exe_dsp();		/* タスクディスパッチの実行 */
		mknl_exe_tex();		/* 例外処理の実行 */
	}
	
	mknl_unl_sys();	/* システムのロック解除 */
	
	return E_OK;	/* 正常終了 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
