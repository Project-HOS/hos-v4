/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル メールボックス                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* メールボックスからの受信(ポーリング) */
ER prcv_mbx(
		ID    mbxid,		/* 受信対象のメールボックスのID番号 */
		T_MSG **pk_msg)		/* メールボックスから受信したメッセージパケットの先頭番地 */
{
	T_KERNEL_MBXCB_RAM *mbxcb_ram;
	ER ercd;

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

	if ( mbxcb_ram->msg != NULL )
	{
		/* メールボックスにデータがあれば取り出す */
		*pk_msg = mbxcb_ram->msg;
		mbxcb_ram->msg = mbxcb_ram->msg->next;
		ercd = E_OK;	/* 成功 */
	}
	else
	{
		/* メールボックスが空ならタイムアウト */
		ercd = E_TMOUT;
	}

	mknl_unl_sys();	/* システムのロック解除 */

	return ercd;
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
