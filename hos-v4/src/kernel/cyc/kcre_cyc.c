/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 周期ハンドラ                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"
#include "knl_mem.h"



/* 周期ハンドラの生成(カーネル内部) */
ER kernel_cre_cyc(
		ID           cycid,		/* 生成対象の周期ハンドラID番号 */
		const T_CCYC *pk_ccyc)	/* 周期ハンドラ生成情報を入れたパケットへのポインタ */
{
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	T_KERNEL_CYCCB_ROM *cyccb_rom;
	SIZE memsize;
	UB   *memptr;
	
	/* 必要なメモリサイズを計算 */
	memsize = sizeof(T_KERNEL_CYCCB_RAM) + sizeof(T_KERNEL_CYCCB_ROM);
	
	/* メモリ確保 */
	memptr = (UB *)kernel_alc_mem(memsize);
#ifdef HOS_ERCHK_E_NOMEM
	if ( memptr == NULL )
	{
		return E_NOMEM;		/* メモリ不足 */
	}
#endif

	/* ポインタ設定 */	
	cyccb_ram  = (T_KERNEL_CYCCB_RAM *)memptr;
	memptr  += sizeof(T_KERNEL_CYCCB_RAM);
	cyccb_rom  = (T_KERNEL_CYCCB_ROM *)memptr;

	/* 値設定 */
	cyccb_ram->timobj.timhdr = kernel_cyc_hdr; /* 周期ハンドラ登録 */
	cyccb_ram->timobj.next   = NULL;            /* タイマリスト未接続 */
	cyccb_ram->cyccb_rom     = cyccb_rom;	/* 周期ハンドラコントロールブロックROM部へのポインタ */
	cyccb_rom->cycatr  = pk_ccyc->cycatr;	/* 周期ハンドラ属性 */
	cyccb_rom->exinf   = pk_ccyc->exinf;	/* 周期ハンドラの拡張情報 */
	cyccb_rom->cychdr  = pk_ccyc->cychdr;	/* 周期ハンドラの起動番地 */
	cyccb_rom->cyctim  = pk_ccyc->cyctim;	/* 周期ハンドラの起動周期 */
/*	cyccb_rom->cycphs  = pk_ccyc->cycphs;*/	/* 周期ハンドラの起動位相 */

	/* 周期ハンドラコントロールブロックテーブルに登録 */
	KERNEL_CYCID_TO_CYCCB_RAM(cycid) = cyccb_ram;

	/* 実行属性ならば開始 */
	if ( pk_ccyc->cycatr & TA_STA )
	{
		/* タイマリストに追加 */
		cyccb_ram->lefttim = pk_ccyc->cyctim;
		kernel_add_tml((T_KERNEL_TIM *)cyccb_ram);
	}

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
