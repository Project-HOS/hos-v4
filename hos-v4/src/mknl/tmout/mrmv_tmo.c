/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    μカーネル タイムアウトキュー管理                                     */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* タイムアウト待ち行列からタスクを取り除く */
void mknl_rmv_tmout(
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
