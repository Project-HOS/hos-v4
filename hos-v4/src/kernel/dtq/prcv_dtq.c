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
	
	if ( mknl_ref_qhd(&dtqcb_ram->sndque) != NULL )
	{
		/* 送信待ちタスクがあれば開放 */
		mtcb = mknl_ref_qhd(&dtqcb_ram->sndque);	/* 待ち行列先頭からタスク取り出し */
		mknl_del_que(mtcb);							/* 待ち行列から削除 */
		mknl_del_tmout(mtcb);						/* タイムアウト解除 */
		*p_data = mtcb->data;						/* データを取り出し */
		mknl_wup_tsk(mtcb, E_OK);					/* タスクの待ち解除 */

		/* タスクディスパッチの実行 */
		mknl_exe_dsp();
		
		ercd = E_OK;
	}
	else
	{
		/* 送信待ちタスクが無ければデータキューから取り出し */
		dtqcb_rom = dtqcb_ram->dtqcbrom;
		if ( dtqcb_ram->datacnt == 0 )
		{
			/* データキューが空ならタイムアウト */
			ercd = E_TMOUT;
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
			dtqcb_ram->datacnt--;
			
			ercd = E_OK;
		}
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
