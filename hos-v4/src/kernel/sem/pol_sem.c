/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル セマフォ                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* セマフォ資源の獲得(ポーリング) */
ER pol_sem(
		ID semid)	/* 資源獲得対象のセマフォID番号 */
{
	T_KERNEL_SEMCB_RAM *semcb_ram;
	ER ercd;

	/* ID のチェック */
#ifdef HOS_ERCHK_E_ID
	if ( semid < TMIN_SEMID || semid > KERNEL_TMAX_SEMID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();		/* システムのロック */

	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);

	/* オブジェクト存在チェック */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();		/* システムのロック解除 */
		return E_NOEXS;
	}
#endif

	/* セマフォ資源が獲得できれ無ければタイムアウト */
	if ( semcb_ram->semcnt == 0 )
	{
		ercd = E_TMOUT;		/* タイムアウト */
	}
	else
	{
		semcb_ram->semcnt--;	/* セマフォ資源の獲得 */
		ercd = E_OK;
	}

	mknl_unl_sys();		/* システムのロック解除 */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
