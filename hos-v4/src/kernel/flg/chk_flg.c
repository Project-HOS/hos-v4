/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* フラグが起床条件を満たしているかチェック */
BOOL kernel_chk_flg(
		T_KERNEL_FLGCB_RAM *flgcb_ram,	/* コントロールブロック RAM部 */
		T_KERNEL_FLGINF    *pk_flginf)	/* 待ちフラグ情報パケットの先頭番地 */
{
	if ( pk_flginf->wfmode == TWF_ANDW )
	{
		/* AND待ち判定 */
		return ((flgcb_ram->flgptn & pk_flginf->waiptn) == pk_flginf->waiptn);
	}
	else
	{
		/* OR待ち判定 */
		return ((flgcb_ram->flgptn & pk_flginf->waiptn) != 0);
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
