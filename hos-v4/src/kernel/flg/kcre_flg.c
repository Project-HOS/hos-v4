/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル イベントフラグ                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"
#include "knl_mem.h"



/* イベントフラグコントロールブロック(動的生成用) */
typedef struct t_kernel_flgcb
{
	T_KERNEL_FLGCB_RAM flgcb_ram;	/* イベントフラグコントロールブロック(RAM部) */
	T_KERNEL_FLGCB_ROM flgcb_rom;	/* イベントフラグコントロールブロック(ROM部) */
} T_KERNEL_FLGCB;



/* イベントフラグの生成(カーネル内部関数) */
ER kernel_cre_flg(
		ID           flgid,		/* 生成対象のイベントフラグのID番号 */
		const T_CFLG *pk_cflg)	/* イベントフラグ生成情報を入れたパケットへのポインタ */
{
	T_KERNEL_FLGCB     *flgcb;
	T_KERNEL_FLGCB_RAM *flgcb_ram;
	T_KERNEL_FLGCB_ROM *flgcb_rom;

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cflg->flgatr & ~(TA_TFIFO | TA_TPRI | TA_WSGL | TA_WMUL | TA_CLR) )
	{
		return E_RSATR;
	}
#endif

	/* イベントフラグ用メモリの確保 */
	flgcb = (T_KERNEL_FLGCB *)kernel_alc_mem(sizeof(T_KERNEL_FLGCB));
	if ( flgcb == NULL )
	{
		return E_NOMEM;		/* メモリ不足 */
	}

	/* イベントフラグの設定 */
	flgcb_ram = &flgcb->flgcb_ram;
	flgcb_rom = &flgcb->flgcb_rom;
	flgcb_rom->flgatr  = pk_cflg->flgatr;
	flgcb_rom->iflgptn = pk_cflg->iflgptn;
	mknl_ini_que(&flgcb_ram->que);
	flgcb_ram->flgptn    = flgcb_rom->iflgptn;
	flgcb_ram->flgcb_rom = flgcb_rom;

	/* 管理テーブルへ追加 */
	KERNEL_FLGID_TO_FLGCB_RAM(flgid) = flgcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
