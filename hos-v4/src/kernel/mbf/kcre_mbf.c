/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル メッセージバッファ                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"
#include "knl_mem.h"


/* メッセージバッファコントロールブロック(動的生成用) */
typedef struct t_kernel_mbfcb
{
	T_KERNEL_MBFCB_RAM mbfcb_ram;	/* メッセージバッファコントロールブロック(RAM部) */
	T_KERNEL_MBFCB_ROM mbfcb_rom;	/* メッセージバッファコントロールブロック(ROM部) */
} T_KERNEL_MBFCB;



/* メッセージバッファの生成(カーネル内部関数) */
ER kernel_cre_mbf(
		ID           mbfid,		/* 生成対象のメッセージバッファのID番号 */
		const T_CMBF *pk_cmbf)	/* メッセージバッファ生成情報を入れたパケットへのポインタ */
{
	T_KERNEL_MBFCB     *mbfcb;
	T_KERNEL_MBFCB_RAM *mbfcb_ram;
	T_KERNEL_MBFCB_ROM *mbfcb_rom;
	VP                 mbf;
	
	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmbf->mbfatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif
	
	/* メッセージバッファ用メモリの確保 */
	if ( pk_cmbf->mbf == NULL )
	{
		mbfcb = (T_KERNEL_MBFCB *)kernel_alc_mem(sizeof(T_KERNEL_MBFCB) + pk_cmbf->mbfsz);
		if ( mbfcb == NULL )
		{
			return E_NOMEM;		/* メモリ不足 */
		}
		mbf = (VP)((VB *)mbfcb + pk_cmbf->mbfsz);
	}
	else
	{
		mbfcb = (T_KERNEL_MBFCB *)kernel_alc_mem(sizeof(T_KERNEL_MBFCB));
		if ( mbfcb == NULL )
		{
			return E_NOMEM;		/* メモリ不足 */
		}
		mbf = pk_cmbf->mbf;
	}

	
	/* メッセージバッファの設定 */
	mbfcb_ram = &mbfcb->mbfcb_ram;
	mbfcb_rom = &mbfcb->mbfcb_rom;
	mknl_ini_que(&mbfcb_ram->sndque);
	mknl_ini_que(&mbfcb_ram->rcvque);
	mbfcb_ram->head      = 0;
	mbfcb_ram->fmbfsz    = pk_cmbf->mbfsz;
	mbfcb_ram->smsgcnt   = 0;
	mbfcb_ram->mbfcb_rom = mbfcb_rom;
	mbfcb_rom->mbfatr    = pk_cmbf->mbfatr;
	mbfcb_rom->maxmsz    = pk_cmbf->maxmsz;
	mbfcb_rom->mbfsz     = pk_cmbf->mbfsz;
	mbfcb_rom->mbf       = mbf;
	
	/* 管理テーブルへ追加 */
	KERNEL_MBFID_TO_MBFCB_RAM(mbfid) = mbfcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
