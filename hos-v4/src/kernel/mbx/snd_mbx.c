/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル メールボックス                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"



/* メールボックスへの送信 */
ER snd_mbx(
		ID    mbxid,		/* 送信対象のメールボックスのID番号 */
		T_MSG *pk_msg)		/* メールボックスへ送信するメッセージパケットの先頭番地 */
{
	T_KERNEL_MBXCB_RAM *mbxcb_ram;
	T_MKNL_TCB *mtcb;
	T_MSG      *msg;
	T_MSG      *msg_next;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( mbxid < TMIN_MBXID || mbxid > TMAX_MBXID )
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

	mtcb = mknl_ref_qhd(&mbxcb_ram->que);		/* 待ち行列先頭タスクを取得 */
	if ( mtcb != NULL )
	{
		/* 待ちタスクがあれば開放 */
		mtcb->data = (VP_INT)pk_msg;			/* メッセージを渡す */
		mtcb = mknl_ref_qhd(&mbxcb_ram->que);	/* 待ち行列先頭からタスク取り出し */
		mknl_rmv_que(mtcb);						/* メールボックスの待ち行列から削除 */
		mknl_rmv_tmout(mtcb);					/* タイムアウト待ち行列から削除 */
		mknl_wup_tsk(mtcb, E_OK);				/* タスクの待ち解除 */
		
		mknl_exe_dsp();		/* タスクディスパッチの実行 */
		mknl_exe_tex();		/* 例外処理の実行 */
	}
	else
	{
		/* 待ちタスクがなければメールボックスに接続 */
		if ( mbxcb_ram->msg == NULL )
		{
			/* メッセージが空なら先頭に接続 */
			mbxcb_ram->msg = pk_msg;
			pk_msg->next   = NULL;
		}
		else
		{
			msg = mbxcb_ram->msg;
			if ( mbxcb_ram->mbxcb_rom->mbxatr & TA_MPRI )
			{
				/* 優先度位置を検索 */
				for ( ; ; )
				{
					msg_next = msg->next;
					if ( msg_next == NULL
						|| ((T_MSG_PRI*)msg_next)->msgpri > ((T_MSG_PRI*)pk_msg)->msgpri )
					{
						/* 優先度位置に挿入 */
						msg->next    = pk_msg;
						pk_msg->next = msg_next;
						break;
					}
					msg = msg_next;
				}
			}
			else
			{
				/* 末尾を検索 */
				while ( msg->next != NULL )
				{
					msg = msg->next;
				}
				/* 末尾に追加 */
				msg->next    = pk_msg;
				pk_msg->next = NULL;
			}
		}
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return E_OK;	/* 成功 */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
