/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル 割り込み処理                                               */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ローカル関数 */
static void mknl_int_ctx(VP_INT exinf);		/* 割り込みコンテキスト */


/* ローカル変数 */
static INTNO           mknl_int_intno;		/* 割り込み番号 */
static INT             mknl_int_nstcnt = 0;	/* 多重割り込みのネストカウント */
static T_HOSPAC_CTXINF mknl_intctx;			/* 割り込みコンテキスト */
static T_HOSPAC_CTXINF mknl_int_orgctx;		/* 割り込み前のコンテキスト保存用 */



/* 割り込み処理の初期化 */
void mknl_ini_int(void)
{
	/* 割り込みコンテキストの作成 */
	hospac_cre_cnt(&mknl_intctx, 0, mknl_int_ctx, mknl_int_stksz, mknl_int_stk);
}


/* 割り込み処理実行 */
void mknl_exe_int(INTNO intno)
{
	if ( mknl_int_nstcnt++ != 0 )
	{
		/* 多重割り込み */
		kernel_exe_int(intno);
		mknl_int_nstcnt--;
		return;
	}
	
	/* 割り込みコンテキストに移行 */
	mknl_sta_ind();
	
	/* スタック入れ替え */
	mknl_int_intno = intno;
	hospac_swi_cnt(&mknl_int_orgctx, &mknl_intctx);

	/* 割り込みコンテキストの終了 */
	mknl_int_nstcnt--;
	mknl_ext_ind();
}


/* 割り込みの終了処理 */
void mknl_end_int(void)
{
	if ( mknl_int_nstcnt == 0 )
	{
		mknl_dly_dsp();
	}
}


/* 割り込み処理用コンテキスト */
void mknl_int_ctx(VP_INT exinf)
{
	for ( ; ; )
	{
		/* 割り込み処理実行 */
		kernel_exe_int(mknl_int_intno);
		
		/* 割り込み前のコンテキストに戻る */
		hospac_swi_cnt(&mknl_intctx, &mknl_int_orgctx);
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
