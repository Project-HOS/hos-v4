/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル 割り込み制御                                            */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "kernel.h"



/* 割り込みコンテキストの開始 */
void kernel_sta_int(void)
{
	/* 非タスク部(割り込みコンテキストに移行) */
	mknl_sta_ind();
}


/* 割り込みコンテキストの終了 */
void kernel_end_int(void)
{
	/* タスク部に移行 */
	mknl_ext_ind();

	/* 遅延ディスパッチ実行 */
	mknl_dly_dsp();
}


/* 割り込み処理実行 */
void kernel_exe_int(
		INTNO intno)		/* 割り込み番号 */
{
	T_KERNEL_INTCB intcb;

	intcb = kernel_intcb_tbl[intno];	/* ローカルにコピー */

	mknl_unl_sys();		/* 多重割り込み許可 */

	if ( intcb.isr != NULL )
	{
		intcb.isr(intcb.exinf);			/* 割り込みサービスルーチン実行 */
	}

	mknl_loc_sys();		/* 多重割り込み禁止 */
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
