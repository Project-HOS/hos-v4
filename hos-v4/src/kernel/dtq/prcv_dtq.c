/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル データキュー                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* データキューからの受信(ポーリング) */
ER prcv_dtq(
		ID     dtqid,	/* 受信対象のデータキューのID番号 */
		VP_INT *p_data)	/* データキューから受信したデータ */				
{
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;
	ER  ercd;

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

	dtqcb_rom = dtqcb_ram->dtqcbrom;

	if ( dtqcb_ram->datacnt == 0 )
	{
		/* データキューが空なら */
		if ( mknl_ref_qhd(&dtqcb_ram->sndque) != NULL )
		{
			/* 送信待ちタスクがあれば開放 */
			mtcb = mknl_ref_qhd(&dtqcb_ram->sndque);	/* 待ち行列先頭からタスク取り出し */
			mknl_rmv_que(mtcb);							/* 待ち行列から削除 */
			mknl_rmv_tmout(mtcb);						/* タイムアウト解除 */
			*p_data = mtcb->data;						/* データを取り出し */
			mknl_wup_tsk(mtcb, E_OK);					/* タスクの待ち解除 */
			
			mknl_exe_dsp();		/* タスクディスパッチの実行 */
			mknl_exe_tex();		/* 例外処理の実行 */
			
			ercd = E_OK;
		}
		else
		{
			/* データキューが空で送信待ちタスクが無ければタイムアウト */
			ercd = E_TMOUT;
		}
	}
	else
	{
		/* データキューからデータを取り出し */
		*p_data = dtqcb_rom->dtq[dtqcb_ram->head];
		dtqcb_ram->head++;
		if ( dtqcb_ram->head >= dtqcb_rom->dtqcnt )
		{
			dtqcb_ram->head = 0;
		}
		
		/* 送信待ちタスクがあるなら開放 */
		mtcb = mknl_ref_qhd(&dtqcb_ram->sndque);
		if ( mtcb!= NULL )
		{
			UINT tail;
			
			/* データキュー末尾にデータを格納 */
			tail = dtqcb_ram->head + dtqcb_ram->datacnt - 1;
			if ( tail >= dtqcb_rom->dtqcnt )
			{
				tail -= dtqcb_rom->dtqcnt;
			}
			dtqcb_rom->dtq[tail] = mtcb->data;
			
			mknl_rmv_que(mtcb);			/* 待ち行列から削除 */
			mknl_rmv_tmout(mtcb);		/* タイムアウト解除 */
			mknl_wup_tsk(mtcb, E_OK);	/* タスクの待ち解除 */
			
			mknl_exe_dsp();		/* タスクディスパッチの実行 */
			mknl_exe_tex();		/* 例外処理の実行 */
		}
		else
		{
			dtqcb_ram->datacnt--;
		}
		
		ercd = E_OK;
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
