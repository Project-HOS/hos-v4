/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 時間管理                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* タイマオブジェクトをリストから削除 */
void kernel_rmv_tml(
		T_KERNEL_TIM *timobj)	/* 削除するタイマオブジェクト */
{
	/* 未登録なら何もしない */
	if ( timobj->next == NULL )
	{
		return;
	}
	
	/* 検索中のタイマならポインタをずらす(再入対策) */
	if ( timobj == kernel_tml_ptr )
	{
		if ( timobj->next == kernel_tml_head )
		{
			kernel_tml_ptr = NULL;			/* 末尾なら、次のポインタは無し */
		}
		else
		{
			kernel_tml_ptr = timobj->next;	/* 次のオブジェクトに移動 */
		}
	}
	
	/* リストから削除 */
	if ( timobj == timobj->next )
	{
		/* リストが空になる場合 */
		kernel_tml_head = NULL;
	}
	else
	{
		/* 先頭なら先頭位置をずらす */
		if ( timobj == kernel_tml_head )
		{
			kernel_tml_head = timobj->next;
		}
		
		/* リストから削除 */
		timobj->next->prev = timobj->prev;
		timobj->prev->next = timobj->next;
	}

	/* 未登録に設定 */
	timobj->next = NULL;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
