/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* フラグが起床条件を満たしているかチェック */
BOOL kernel_chk_flg(
		T_KERNEL_FLGCB_RAM *flgcb_ram)	/* コントロールブロック RAM部 */
{
	if ( flgcb_ram->wfmode == TWF_ANDW )
	{
		/* AND待ち判定 */
		return ((flgcb_ram->flgptn & flgcb_ram->waiptn) == flgcb_ram->waiptn);
	}
	else
	{
		/* OR待ち判定 */
		return ((flgcb_ram->flgptn & flgcb_ram->waiptn) == flgcb_ram->waiptn);
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
