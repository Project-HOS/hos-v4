/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル 可変長メモリプール                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"
#include "knl_mem.h"


/* 可変長メモリプール コントロールブロック(動的生成用) */
typedef struct t_kernel_mplcb
{
	T_KERNEL_MPLCB_RAM mplcb_ram;	/* 可変長メモリプール コントロールブロック(RAM部) */
	T_KERNEL_MPLCB_ROM mplcb_rom;	/* 可変長メモリプール コントロールブロック(ROM部) */
} T_KERNEL_MPLCB;

/* 可変長メモリプール コントロールブロック(動的生成、カーネルメモリ用) */
typedef struct t_kernel_mplcb_with_blk
{
	T_KERNEL_MPLCB_RAM mplcb_ram;	/* 可変長メモリプール コントロールブロック(RAM部) */
	T_KERNEL_MPLCB_ROM mplcb_rom;	/* 可変長メモリプール コントロールブロック(ROM部) */
	VP	blk[1];			/* メモリブロックダミー */
} T_KERNEL_MPLCB_WBLK;



/* 可変長メモリプールの生成(カーネル内部関数) */
ER kernel_cre_mpl(
		ID           mplid,		/* 生成対象の可変長メモリプールのID番号 */
		const T_CMPL *pk_cmpl)	/* 可変長メモリプール生成情報を入れたパケットへのポインタ */
{
	T_KERNEL_MPLCB     *mplcb;
	T_KERNEL_MPLCB_RAM *mplcb_ram;
	T_KERNEL_MPLCB_ROM *mplcb_rom;
	VP   mpl;

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmpl->mplatr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* パラメータチェック */
#ifdef HOS_ERCHK_E_PAR
	if ( pk_cmpl->mplsz == 0 )
	{
		return E_PAR;   /* パラメータ不正 */
	}
#endif

	/* 可変長メモリプール用メモリの確保 */
	mplcb = (T_KERNEL_MPLCB *)kernel_alc_mem(
		pk_cmpl->mpl != NULL ? 	sizeof(T_KERNEL_MPLCB) :
		sizeof(T_KERNEL_MPLCB_WBLK) - sizeof(VP)
		+ pk_cmpl->mplsz 
		);
	if ( mplcb == NULL )
	{
		return E_NOMEM;		/* メモリ不足 */
	}
	
	/* メモリプール先頭番地セット */
	if ( pk_cmpl->mpl == NULL )
	{
		mpl = ((T_KERNEL_MPLCB_WBLK *)mplcb)->blk;
	}
	else
	{
		mpl = pk_cmpl->mpl;
	}

	/* 可変長メモリプールの設定 */
	mplcb_ram = &mplcb->mplcb_ram;
	mplcb_rom = &mplcb->mplcb_rom;
	mknl_ini_que(&mplcb_ram->que);
	mplcb_ram->mplcb_rom = mplcb_rom;
	mplcb_rom->mplatr    = pk_cmpl->mplatr;
	mplcb_rom->mplsz     = pk_cmpl->mplsz;
	mplcb_rom->mpl       = mpl;

	/* ヒープ生成 */
	kernel_cre_hep(&mplcb_ram->hep, mplcb_rom->mpl, mplcb_rom->mplsz);

	/* 管理テーブルへ追加 */
	KERNEL_MPLID_TO_MPLCB_RAM(mplid) = mplcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
