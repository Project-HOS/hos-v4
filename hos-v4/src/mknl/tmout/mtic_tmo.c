/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル タイムアウトキュー管理                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* グローバル変数定義 */
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


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
