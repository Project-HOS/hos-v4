/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル データキュー                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
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



/* データキューの生成(カーネル内部関数) */
ER kernel_cre_dtq(
		ID           dtqid,		/* 生成対象のデータキューのID番号 */
		const T_CDTQ *pk_cdtq)	/* データキュー生成情報を入れたパケットへのポインタ */
{
	T_KERNEL_DTQCB     *dtqcb;
	T_KERNEL_DTQCB_RAM *dtqcb_ram;
	T_KERNEL_DTQCB_ROM *dtqcb_rom;
	VP_INT *dtq;

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cdtq->dtqatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* データキュー用メモリの確保 */
	dtqcb = (T_KERNEL_DTQCB *)kernel_alc_mem(sizeof(T_KERNEL_DTQCB));
	if ( dtqcb == NULL )
	{
		return E_NOMEM;		/* メモリ不足 */
	}
	
	/* キューメモリ確保 */
	if ( pk_cdtq->dtq == NULL )
	{
		dtq = (VP_INT *)kernel_alc_mem((SIZE)(sizeof(VP_INT *) * pk_cdtq->dtqcnt));
		if ( dtq == NULL )
		{
			kernel_fre_mem(dtqcb);
			return E_NOMEM;			/* メモリ不足 */
		}
	}
	else
	{
		dtq = (VP_INT *)pk_cdtq->dtq;
	}

	/* データキューの設定 */
	dtqcb_ram = &dtqcb->dtqcb_ram;
	dtqcb_rom = &dtqcb->dtqcb_rom;
	dtqcb_rom->dtqatr = pk_cdtq->dtqatr;
	dtqcb_rom->dtqcnt = pk_cdtq->dtqcnt;
	dtqcb_rom->dtq    = dtq;
	mknl_ini_que(&dtqcb_ram->sndque);
	mknl_ini_que(&dtqcb_ram->rcvque);
	dtqcb_ram->head      = 0;
	dtqcb_ram->datacnt   = 0;
	dtqcb_ram->dtqcb_rom = dtqcb_rom;

	/* 管理テーブルへ追加 */
	kernel_dtqcb_ram_tbl[dtqid - TMIN_DTQID] = dtqcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
