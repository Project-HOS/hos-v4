/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル メールボックス                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* メールボックスへの送信 */
ER snd_mbx(
		ID    mbxid,		/* 送信対象のメールボックスのID番号 */
		T_MSG *pk_msg)		/* メールボックスへ送信するメッセージパケットの先頭番地 */
{
	const T_KERNEL_MBXCB_ROM *mbxcb_rom;
	T_KERNEL_MBXCB_RAM       *mbxcb_ram;
	T_MKNL_TCB *mtcb;
	T_MSG      *msg;
	PRI        msgpri;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < KERNEL_TMIN_MBXID || mbxid > KERNEL_TMAX_MBXID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();	/* システムのロック */

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

	/* メッセージ優先度取得 */
	if ( mbxcb_rom->mbxatr & TA_MPRI )	/* 優先度順なら */
	{
		msgpri = (PRI)(((T_MSG_PRI*)pk_msg)->msgpri - TMIN_MPRI);

		/* 優先度チェック */
#ifdef HOS_ERCHK_E_PAR
		if ( msgpri < 0	|| msgpri > mbxcb_rom->maxmpri - TMIN_MPRI )
		{
			mknl_unl_sys();		/* システムのロック解除 */
			return E_PAR;
		}
#endif
	}
	else	/* 優先度なし(FIFO順)なら */
	{
		msgpri = 0;
	}

	mtcb = mknl_ref_qhd(&mbxcb_ram->que);		/* 待ち行列先頭タスクを取得 */
	if ( mtcb != NULL )
	{
		/* 待ちタスクがあれば開放 */
		mtcb->data = (VP_INT)pk_msg;			/* メッセージを渡す */
		mknl_rmv_que(mtcb);						/* メールボックスの待ち行列から削除 */
		mknl_rmv_tmout(mtcb);					/* タイムアウト待ち行列から削除 */
		mknl_wup_tsk(mtcb, E_OK);				/* タスクの待ち解除 */
		
		mknl_exe_dsp();		/* タスクディスパッチの実行 */
		mknl_exe_tex();		/* 例外処理の実行 */
	}
	else
	{
		/* 待ちタスクがなければメールボックスに接続 */
		if ( mbxcb_rom->mprihd[msgpri] == NULL )
		{
			/* 最初の１個の登録 */
			mbxcb_rom->mprihd[msgpri] = pk_msg;
			pk_msg->next              = pk_msg;
		}
		else
		{
			/* 末尾に追加 */
			msg                       = mbxcb_rom->mprihd[msgpri];
			pk_msg->next              = msg->next;
			msg->next                 = pk_msg;
			mbxcb_rom->mprihd[msgpri] = pk_msg;
		}
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;	/* 成功 */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
