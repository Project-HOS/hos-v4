/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル メールボックス                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* メールボックスからの受信 */
ER trcv_mbx(			
		ID    mbxid,		/* 受信対象のメールボックスのID番号 */
		T_MSG **pk_msg,		/* メールボックスから受信したメッセージパケットの先頭番地 */
		TMO   tmout)		/* タイムアウト指定 */
{
	T_KERNEL_MBXCB_RAM *mbxcb_ram;
	T_MKNL_TCB *mtcb;
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < TMIN_MBXID || mbxid > TMAX_MBXID )
	{
		return E_ID;
	}
#endif
	
	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR 
	if ( tmout != TMO_FEVR && tmout < 0 )
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

	mbxcb_ram = KERNEL_MBXID_TO_MBXCB_RAM(mbxid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbxcb_ram == NULL )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_NOEXS;
	}
#endif

	if ( mbxcb_ram->msg != NULL )
	{
		/* メールボックスにデータがあれば取り出す */
		*pk_msg = mbxcb_ram->msg;
		mbxcb_ram->msg = mbxcb_ram->msg->next;
		ercd = E_OK;	/* 成功 */
	}
	else
	{
		/* メールボックスが空なら */
		if ( tmout == TMO_POL )
		{
			/* ポーリングなら即時タイムアウト */
			ercd = E_TMOUT;
		}
		else
		{
			/* 待ちに入る */
			mtcb = mknl_get_run_tsk();
			mknl_wai_tsk(mtcb, TTW_MBX);
			if ( mbxcb_ram->mbxrom->mbxatr & TA_TPRI )
			{
				mknl_adp_que(&mbxcb_ram->que, mtcb);	/* タスク優先度順に追加 */
			}
			else
			{
				mknl_add_que(&mbxcb_ram->que, mtcb);	/* FIFO順に追加 */
			}

			/* 無限待ちでなければ */
			if ( tmout != TMO_FEVR )
			{
				mknl_add_tmout(mtcb, (RELTIM)tmout);	/* タイムアウトキューに追加 */
			}

			/* タスクディスパッチの実行 */
			ercd = (ER)mknl_exe_dsp();
		
			/* 成功したら受信データを格納 */
			if ( ercd == E_OK )
			{
				*pk_msg = (T_MSG *)mtcb->data;
			}
		}
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
