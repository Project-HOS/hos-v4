/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 固定長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"
#include "knl_mem.h"


/* 固定長メモリプール コントロールブロック(動的生成用) */
typedef struct t_kernel_mpfcb
{
	T_KERNEL_MPFCB_RAM mpfcb_ram;	/* 固定長メモリプール コントロールブロック(RAM部) */
	T_KERNEL_MPFCB_ROM mpfcb_rom;	/* 固定長メモリプール コントロールブロック(ROM部) */
} T_KERNEL_MPFCB;



/* 固定長メモリプールの生成(カーネル内部関数) */
ER kernel_cre_mpf(
		ID           mpfid,		/* 生成対象の固定長メモリプールのID番号 */
		const T_CMPF *pk_cmpf)	/* 固定長メモリプール生成情報を入れたパケットへのポインタ */
{
	T_KERNEL_MPFCB     *mpfcb;
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	T_KERNEL_MPFCB_ROM *mpfcb_rom;
	VP   mpf;
	UB   *ptr;
	UINT i;

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmpf->mpfatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* 固定長メモリプール用メモリの確保 */
	mpfcb = (T_KERNEL_MPFCB *)kernel_alc_mem(sizeof(T_KERNEL_MPFCB));
	if ( mpfcb == NULL )
	{
		return E_NOMEM;		/* メモリ不足 */
	}
	
	/* メモリプール用メモリ確保 */
	if ( pk_cmpf->mpf == NULL )
	{
		mpf = kernel_alc_mem((SIZE)(pk_cmpf->blksz * pk_cmpf->blkcnt));
		if ( mpf == NULL )
		{
			kernel_fre_mem(mpfcb);
			return E_NOMEM;		/* メモリ不足 */
		}
	}
	else
	{
		mpf = pk_cmpf->mpf;
	}

	/* 固定長メモリプールの設定 */
	mpfcb_ram = &mpfcb->mpfcb_ram;
	mpfcb_rom = &mpfcb->mpfcb_rom;
	mknl_ini_que(&mpfcb_ram->que);
	mpfcb_ram->free      = mpf;
	mpfcb_ram->mpfcb_rom = mpfcb_rom;
	mpfcb_rom->mpfatr    = pk_cmpf->mpfatr;
	mpfcb_rom->blkcnt    = pk_cmpf->blkcnt;
	mpfcb_rom->blksz     = pk_cmpf->blksz;
	mpfcb_rom->mpf       = pk_cmpf->mpf;

	/* ブロックの初期化 */
	ptr = (UB *)mpfcb_rom->mpf;
	for ( i = 0; i < mpfcb_rom->blkcnt - 1; i++ )
	{
		*(VP *)ptr = (VP)(ptr + mpfcb_rom->blksz);
		ptr += mpfcb_rom->blksz;
	}
	*(VP *)ptr = NULL;	/* 最終ブロック */

	/* 管理テーブルへ追加 */
	KERNEL_MPFID_TO_MPFCB_RAM(mpfid) = mpfcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
