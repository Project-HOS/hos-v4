/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル タイムアウトキュー管理                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



#include "mknl.h"



/* タイムアウトキューは効率よりメモリ優先で単純検索としている   */
/* タイムアウト待ちを行うタスク数が少ないことを前提としているが */
/* 要望があれば I/F を変えずに配列管理をHeapに変えたり、TCBに   */
/* タイムアウト用の連結ポインタを用意して半順序木で管理するよう */
/* 変更する事が可能である                                       */


INT mknl_timout_tskcnt = 0;		/* タイムアウト待ち行列のタスク個数 */



/* タイムアウトにタイムティック供給 */
void mknl_tic_tmout(
		RELTIM tictim)		/* 追加するタイムティック */
{
	int i;

	/* タイムアウト待ち行列のタスク起床 */
	while ( (volatile INT)mknl_timout_tskcnt > 0 )
	{
		/* タイムアウトかどうか判定 */
		if ( mknl_timout[0].diftim > tictim )
		{
			/* タイムアウトでなければ時間を減じてループを抜ける */
			mknl_timout[0].diftim -= tictim;
			break;
		}

		/* タイムアウトなら */
		mknl_wup_tsk(mknl_timout[0].mtcb, E_TMOUT);	/* タイムアウト起床 */

		/* 先頭の待ちタスクを外す */
		mknl_timout[1].diftim += mknl_timout[0].diftim;	/* 次がいなくても害は無い */
		for ( i = 1; i < mknl_timout_tskcnt; i++ )
		{
			mknl_timout[i - 1] = mknl_timout[i];
		}
		mknl_timout_tskcnt--;

		mknl_exe_dsp();		/* 遅延ディスパッチ予約を行う */

		/* ここで一度、多重割り込みの機会を与える */
		mknl_unl_sys();		/* システムのロック解除 */
		mknl_loc_sys();		/* システムのロック */
	}
}


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


/* タイムアウト待ち行列からタスクを削除 */
void mknl_del_tmout(
		T_MKNL_TCB *mtcbs)	/* 待ち行列から削除するタスク */
{
	INT i;

	/* タスクを検索 */
	for ( i = 0; i < mknl_timout_tskcnt; i++ )
	{
		if ( mknl_timout[i].mtcb == mtcbs )
		{
			/* 削除 */
			if ( i < mknl_timout_tskcnt - 1 )
			{
				mknl_timout[i + 1].diftim += mknl_timout[i].diftim;
				for ( i++; i < mknl_timout_tskcnt; i++ )
				{
					mknl_timout[i - 1] = mknl_timout[i];
				}
			}
			mknl_timout_tskcnt--;
			break;
		}
	}
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
