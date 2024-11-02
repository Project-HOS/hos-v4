/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル データキュー                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_dtq.h"
#include "knl_mem.h"




/* データキューコントロールブロック(動的生成用) */
typedef struct t_kernel_dtqcb
{
	T_KERNEL_DTQCB_RAM dtqcb_ram;	/* データキューコントロールブロック(RAM部) */
	T_KERNEL_DTQCB_ROM dtqcb_rom;	/* データキューコントロールブロック(ROM部) */
} T_KERNEL_DTQCB;

/* データキューコントロールブロック(動的生成、カーネルメモリ用) */
typedef struct t_kernel_dtqcb_with_blk
{
	T_KERNEL_DTQCB_RAM dtqcb_ram;	/* データキューコントロールブロック(RAM部) */
	T_KERNEL_DTQCB_ROM dtqcb_rom;	/* データキューコントロールブロック(ROM部) */
	VP_INT	blk[1];			/* ダミーデータブロック */
} T_KERNEL_DTQCB_WBLK;



/* データキューの生成(カーネル内部関数) */
ER kernel_cre_dtq(
		ID           dtqid,		/* 生成対象のデータキューのID番号 */
		const T_CDTQ *pk_cdtq)	/* データキュー生成情報を入れたパケットへのポインタ */
{
	T_KERNEL_DTQCB     *dtqcb;
	T_KERNEL_DTQCB_RAM *dtqcb_ram;
	T_KERNEL_DTQCB_ROM *dtqcb_rom;

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cdtq->dtqatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* データキュー用メモリの確保 */
	dtqcb = (T_KERNEL_DTQCB *)kernel_alc_mem(
		pk_cdtq->dtq != NULL ?
			sizeof(T_KERNEL_DTQCB) :
			sizeof(T_KERNEL_DTQCB_WBLK) - sizeof(VP_INT)
			+ ( sizeof(VP_INT *) * pk_cdtq->dtqcnt )
		);
	if ( dtqcb == NULL )
	{
		return E_NOMEM;		/* メモリ不足 */
	}
	
	/* データキューの設定 */
	dtqcb_ram = &dtqcb->dtqcb_ram;
	dtqcb_rom = &dtqcb->dtqcb_rom;
	dtqcb_rom->dtqatr = pk_cdtq->dtqatr;
	dtqcb_rom->dtqcnt = pk_cdtq->dtqcnt;
	dtqcb_rom->dtq =  pk_cdtq->dtq != NULL ?
	    (VP_INT *)pk_cdtq->dtq : ((T_KERNEL_DTQCB_WBLK *)dtqcb)->blk;
	mknl_ini_que(&dtqcb_ram->sndque);
	mknl_ini_que(&dtqcb_ram->rcvque);
	dtqcb_ram->head      = 0;
	dtqcb_ram->datacnt   = 0;
	dtqcb_ram->dtqcb_rom = dtqcb_rom;

	/* 管理テーブルへ追加 */
	KERNEL_DTQID_TO_DTQCB_RAM(dtqid) = dtqcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
