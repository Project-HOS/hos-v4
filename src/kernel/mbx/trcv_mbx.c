/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル メールボックス                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* メールボックスからの受信 */
ER trcv_mbx(			
		ID    mbxid,		/* 受信対象のメールボックスのID番号 */
		T_MSG **pk_msg,		/* メールボックスから受信したメッセージパケットの先頭番地 */
		TMO   tmout)		/* タイムアウト指定 */
{
	const T_KERNEL_MBXCB_ROM *mbxcb_rom;
	T_KERNEL_MBXCB_RAM       *mbxcb_ram;
	T_MKNL_TCB *mtcb;
	T_MSG *msg;
	PRI   msgpri;
	ER    ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < KERNEL_TMIN_MBXID || mbxid > KERNEL_TMAX_MBXID )
	{
		return E_ID;
	}
#endif
	
	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_PAR 
	if ( tmout != TMO_FEVR && tmout < 0 )
	{
		return E_PAR;	/* パラメーター不正 */
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

	mbxcb_ram = KERNEL_MBXID_TO_MBXCB_RAM(mbxid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( mbxcb_ram == NULL )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_NOEXS;
	}
#endif

	mbxcb_rom = mbxcb_ram->mbxcb_rom;
	
	/* メッセージを優先度順に検索 */
	for ( msgpri = 0; msgpri <= mbxcb_rom->maxmpri - TMIN_MPRI; msgpri++ )
	{
		if ( mbxcb_rom->mprihd[msgpri] != NULL )
		{
			break;
		}
	}

	if ( msgpri <= mbxcb_rom->maxmpri - TMIN_MPRI )
	{
		/* メールボックスにデータがあれば取り出す */
		msg = mbxcb_rom->mprihd[msgpri];
		if ( msg == msg->next )		/* 最後の１つなら */
		{
			*pk_msg                   = msg;
			mbxcb_rom->mprihd[msgpri] = NULL;
		}
		else
		{
			*pk_msg   = msg->next;
			msg->next = msg->next->next;
		}
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
			mknl_add_que(&mbxcb_ram->que, mtcb, mbxcb_ram->mbxcb_rom->mbxatr);	/* 待ち行列に追加 */

			/* 無限待ちでなければ */
			if ( tmout != TMO_FEVR )
			{
				mknl_add_tmout(mtcb, (RELTIM)tmout);	/* タイムアウトキューに追加 */
			}
			
			ercd = (ER)mknl_exe_dsp();	/* タスクディスパッチの実行 */
			
			/* 成功したら受信データを格納 */
			if ( ercd == E_OK )
			{
				*pk_msg = (T_MSG *)mtcb->data;
			}
			
			mknl_exe_tex();		/* 例外処理の実行 */
		}
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
