/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル タイムアウトキュー管理                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タイムアウト待ち行列にタスクを追加 */
ER mknl_add_tmout(
		T_MKNL_TCB *mtcbs,	/* 待ち行列に加えるタスク */
		RELTIM     tmout)	/* タイムアウトまでの時間 */
{
	INT i, j;

	/* 待ち行列メモリチェック */
#ifdef HOS_ERCHK_E_NOMEM
	if ( mknl_timout_tskcnt >= mknl_timout_size )
	{
		return E_NOMEM;
	}
#endif

	/* 挿入位置を検索(時間順に配置) */
	for ( i = 0; i < mknl_timout_tskcnt; i++ )
	{
		if ( mknl_timout[i].diftim < tmout )
		{
			break;	/* 挿入場所に来たら抜ける */
		}
		tmout -= mknl_timout[i].diftim;	/* 時間の差分で管理する */
	}
	if ( i < mknl_timout_tskcnt )
	{
		/* 途中なら挿入の為に後ろを移動 */
		for ( j = mknl_timout_tskcnt; j > i; j-- )
		{
			mknl_timout[j] = mknl_timout[j - 1];
		}
		mknl_timout[j].diftim -= tmout;
	}
	mknl_timout[i].mtcb   = mtcbs;
	mknl_timout[i].diftim = tmout;

	mknl_timout_tskcnt++;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
