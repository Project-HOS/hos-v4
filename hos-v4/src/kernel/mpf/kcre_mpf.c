/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 固定長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
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

/* 固定長メモリプール コントロールブロック(動的生成、カーネルメモリ用) */
typedef struct t_kernel_mpfcb_with_blk
{
	T_KERNEL_MPFCB_RAM mpfcb_ram;	/* 固定長メモリプール コントロールブロック(RAM部) */
	T_KERNEL_MPFCB_ROM mpfcb_rom;	/* 固定長メモリプール コントロールブロック(ROM部) */
	VP	blk[1];			/* メモリブロックダミー */
} T_KERNEL_MPFCB_WBLK;



/* 固定長メモリプールの生成(カーネル内部関数) */
ER kernel_cre_mpf(
		ID           mpfid,		/* 生成対象の固定長メモリプールのID番号 */
		const T_CMPF *pk_cmpf)	/* 固定長メモリプール生成情報を入れたパケットへのポインタ */
{
	T_KERNEL_MPFCB     *mpfcb;
	T_KERNEL_MPFCB_RAM *mpfcb_ram;
	T_KERNEL_MPFCB_ROM *mpfcb_rom;
	VP   mpf;
	UINT i;

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmpf->mpfatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

        /* パラメータチェック */
#ifdef HOS_ERCHK_E_PAR
        if ( pk_cmpf->blkcnt == 0 || pk_cmpf->blksz == 0 )
	{
                return E_PAR;   /* パラメータ不正 */
	}
#endif

	/* 固定長メモリプール用メモリの確保 */
	mpfcb = (T_KERNEL_MPFCB *)kernel_alc_mem(
		pk_cmpf->mpf != NULL ? 	sizeof(T_KERNEL_MPFCB) :
		sizeof(T_KERNEL_MPFCB_WBLK) - sizeof(VP)
		+ TSZ_MPF( pk_cmpf->blkcnt, pk_cmpf->blksz ) 
		);
	if ( mpfcb == NULL )
	{
		return E_NOMEM;		/* メモリ不足 */
	}
	
	/* メモリプール先頭番地セット */
	if ( pk_cmpf->mpf == NULL )
	{
		mpf = ((T_KERNEL_MPFCB_WBLK *)mpfcb)->blk;
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
	mpfcb_rom->blksz     = TSZ_ALIGNED(pk_cmpf->blksz);

	/* ブロックの初期化 */
	for ( i = 0; i < mpfcb_rom->blkcnt - 1; i++ )
	{
		*(VP *)mpf = (VP)((UB *)mpf + mpfcb_rom->blksz);
		mpf        = (VP)((UB *)mpf + mpfcb_rom->blksz);
	}
	*(VP *)mpf = NULL;	/* 最終ブロック */

	/* 管理テーブルへ追加 */
	KERNEL_MPFID_TO_MPFCB_RAM(mpfid) = mpfcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
