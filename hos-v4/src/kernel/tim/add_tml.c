/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 時間管理                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* タイマオブジェクトをリストに追加 */
void kernel_add_tml(
		T_KERNEL_TIM *timobj)	/* 登録するタイマオブジェクト */
{
	/* 既に登録されていたら何もしない */
	if ( timobj->next != NULL )
	{
		return;
	}
	
	/* リストに登録 */
	if ( kernel_tml_head == NULL )
	{
		/* リストが空の場合の追加 */
		timobj->next = timobj;
		timobj->prev = timobj;
		kernel_tml_head = timobj;
	}
	else
	{
		/* リストの末尾に追加 */
		timobj->next = kernel_tml_head;
		timobj->prev = kernel_tml_head->prev;
		timobj->next->prev = timobj;
		timobj->prev->next = timobj;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
