/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    システム時間管理                                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* タイムティックの供給 */
ER isig_tim(void)
{
	RELTIM tic;
	UW     prev_tim;
    INT    i;

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


	/* タイムアウト待ち行列のタスク起床 */
	mknl_tic_tmout(tic);	/* タイムアウトキューにタイムティックを供給 */


	/* 周期タスクの実行 */
	for ( i = 0; i < kernel_cyccb_cnt; i++ )
	{
		const T_KERNEL_CYCCB_ROM *cyccb_rom;
		T_KERNEL_CYCCB_RAM       *cyccb_ram;

		cyccb_ram = kernel_cyccb_ram_tbl[i];

		if ( cyccb_ram->cycstat != TCYC_STP )	/* 停止ではないなら */
		{
			if ( cyccb_ram->lefttim <= tic )
			{
				cyccb_rom = cyccb_ram->cyccb_rom;
				
				/* 次の値を設定 */
				cyccb_ram->lefttim += cyccb_rom->cyctim - tic;

				/* 周期ハンドラ呼び出し */
				cyccb_rom = cyccb_ram->cyccb_rom;
				cyccb_rom->cychdr(cyccb_rom->exinf);				
			}
			else
			{
				cyccb_ram->lefttim -= tic;
			}
			
		}
	}

	mknl_unl_sys();		/* システムのロック解除 */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
