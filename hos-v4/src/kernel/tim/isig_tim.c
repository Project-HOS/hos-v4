/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル システム時間管理                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* タイマリスト管理 */
T_KERNEL_TIM *kernel_tml_head;		/* タイマリスト先頭位置 */
T_KERNEL_TIM *kernel_tml_ptr;		/* タイマリストポインタ */



/* タイムティックの供給 */
ER isig_tim(void)
{
	T_KERNEL_TIM* tim_ptr;
	UW            prev_tim;
	RELTIM        tic;

	/* 加算するタイムティックを算出 */
	/* 例えば 10/3 ms 周期なら 3, 3, 4, 3, 3, 4, ... とカウントしていく */
	kernel_tic_cnt--;
	if ( kernel_tic_cnt < kernel_tic_mod )
	{
		tic = kernel_tic_div + 1;	/* 割り切れない分を補正 */
	}
	else
	{
		tic = kernel_tic_div;
	}
	if ( kernel_tic_cnt == 0 )
	{
		kernel_tic_cnt = kernel_tic_deno;
	}

	mknl_loc_sys();		/* システムのロック */

	/* システムタイムに加算 */
	prev_tim = kernel_systim.ltime;
	kernel_systim.ltime += tic;
	if ( kernel_systim.ltime < prev_tim )	/* 桁上がりがあるなら */
	{
		kernel_systim.utime++;
	}
	
	/* タイマオブジェクトのハンドラ呼び出し */
	if ( kernel_tml_head != NULL )
	{
		/* 検索ポインタ設定 */
		kernel_tml_ptr = kernel_tml_head;
		
		do /* リスト末尾まで繰り返し */
		{
			/* 次のポインタを事前に設定 */
			tim_ptr        = kernel_tml_ptr;
			kernel_tml_ptr = tim_ptr->next;
			
			/* タイマハンドラ呼び出し */
			tim_ptr->timhdr(tim_ptr, tic);
			
			/* ハンドラ内で削除された場合 */
			if ( kernel_tml_ptr == NULL )
			{
				break;
			}
		} while ( kernel_tml_ptr != kernel_tml_head );
		
		/* 検索ポインタのクリア */
		kernel_tml_ptr = NULL;
	}
	
	/* タイムアウト待ち行列のタスク起床 */
	mknl_tic_tmout(tic);	/* タイムアウトキューにタイムティックを供給 */
	
	mknl_unl_sys();			/* システムのロック解除 */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
