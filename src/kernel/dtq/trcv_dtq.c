/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル データキュー                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"



/* データキューからの受信 */
ER trcv_dtq(
		ID     dtqid,	/* 受信対象のデータキューのID番号 */
		VP_INT *p_data,	/* データキューから受信したデータ */
		TMO    tmout)	/* タイムアウト指定 */
{
	const T_KERNEL_DTQCB_ROM *dtqcb_rom;
	T_KERNEL_DTQCB_RAM       *dtqcb_ram;
	T_MKNL_TCB *mtcb;
	ER  ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( dtqid < KERNEL_TMIN_DTQID || dtqid > KERNEL_TMAX_DTQID )
	{
		return E_ID;
	}
#endif

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR 
	if ( (tmout != TMO_FEVR && tmout < 0) || p_data == NULL )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();	/* システムのロック */

	/* コンテキストチェック */
#ifdef HOS_ERCHK_E_CTX
	if ( tmout != TMO_POL &&  mknl_sns_wai() )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_CTX;	/* コンテキスト不正 */
	}
#endif

	dtqcb_ram = KERNEL_DTQID_TO_DTQCB_RAM(dtqid);

	/* オブジェクトの存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( dtqcb_ram == NULL )
	{
		mknl_unl_sys();	/* システムのロック解除 */
		return E_NOEXS;	/* オブジェクト未生成 */
	}
#endif

	dtqcb_rom = dtqcb_ram->dtqcb_rom;

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
			/* 送信待ちタスクが無ければ待ちに入る */
			if ( tmout == TMO_POL )
			{
				/* ポーリングなら即時タイムアウト */
				ercd = E_TMOUT;
			}
			else
			{
				/* 受信待ちに入る */
				mtcb = mknl_get_run_tsk();		/* 現在のタスクを取得 */
				mknl_wai_tsk(mtcb, TTW_RDTQ);	/* 待ち状態に設定 */
				mknl_add_que(&dtqcb_ram->rcvque, mtcb, dtqcb_rom->dtqatr);	/* 待ち行列に追加 */
				
				/* 無限待ちでなければ */
				if ( tmout != TMO_FEVR )
				{
					mknl_add_tmout(mtcb, (RELTIM)tmout);	/* タイムアウトキューに追加 */
				}
				
				ercd = (ER)mknl_exe_dsp();	/* タスクディスパッチの実行 */
				
				/* 成功したならデータを格納 */		
				if ( ercd == E_OK )
				{
					*p_data = mtcb->data;
				}
				
				mknl_exe_tex();		/* 例外処理の実行 */
			}
		}
	}
	else
	{
		/* データキューからデータを取り出し */
		*p_data = dtqcb_rom->dtq[dtqcb_ram->head];
		dtqcb_ram->head++;
		if ( dtqcb_ram->head >= dtqcb_rom->dtqcnt )
		{
			dtqcb_ram->head -= dtqcb_rom->dtqcnt;
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
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
