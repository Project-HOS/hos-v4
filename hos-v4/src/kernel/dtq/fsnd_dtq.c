/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル データキュー                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* データキューへの強制送信 */
ER fsnd_dtq(
		ID     dtqid,	/* 送信対象のデータキューのID番号 */
		VP_INT data)	/* データキューへ送信するデータ */
{
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;
	UINT tail;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < TMIN_DTQID || dtqid > TMAX_DTQID )
	{
		return E_ID;
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);

	/* オブジェクトの存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	if ( mknl_ref_qhd(&dtqcb_ram->rcvque) != NULL )
	{
		/* 受信待ちタスクがあれば開放 */
		mtcb = mknl_ref_qhd(&dtqcb_ram->rcvque);	/* 待ち行列先頭からタスク取り出し */
		mknl_rmv_que(mtcb);							/* 待ち行列から削除 */
		mknl_rmv_tmout(mtcb);						/* タイムアウト解除 */
		mtcb->data = data;							/* データを格納 */
		mknl_wup_tsk(mtcb, E_OK);					/* タスクの待ち解除 */
		
		mknl_exe_dsp();		/* タスクディスパッチの実行 */
		mknl_exe_tex();		/* 例外処理の実行 */
	}
	else
	{
		/* 待ちタスクが無ければデータキューに格納 */
		dtqcb_rom = dtqcb_ram->dtqcb_rom;
		if ( dtqcb_ram->datacnt >= dtqcb_rom->dtqcnt )
		{
			/* データキューサイズ確認 */
#ifdef HOS_ERCHK_E_ILUSE
			if ( dtqcb_rom->dtqcnt == 0 )
			{
				mknl_unl_sys();	/* システムのロック解除 */
				return E_ILUSE;	/* サービスコール不正使用 */
			}
#endif

			/* キュー先頭のデータを抹消して送信 */
			dtqcb_rom->dtq[dtqcb_ram->head] = data;
			dtqcb_ram->head++;
			if ( dtqcb_ram->head >= dtqcb_rom->dtqcnt )
			{
				dtqcb_ram->head -= dtqcb_rom->dtqcnt;
			}
		}
		else
		{
			/* データキュー末尾にデータを格納 */
			tail = dtqcb_ram->head + dtqcb_ram->datacnt;
			if ( tail >= dtqcb_rom->dtqcnt )
			{
				tail -= dtqcb_rom->dtqcnt;
			}
			dtqcb_rom->dtq[tail] = data;
			dtqcb_ram->datacnt++;
		}
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
