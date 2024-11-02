/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    ITRONカーネル メールボックス                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2003 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbx.h"
#include "knl_mem.h"



/* メールボックスコントロールブロック(動的生成用) */
typedef struct t_kernel_mbxcb
{
	T_KERNEL_MBXCB_RAM mbxcb_ram;	/* メールボックスコントロールブロック(RAM部) */
	T_KERNEL_MBXCB_ROM mbxcb_rom;	/* メールボックスコントロールブロック(ROM部) */
} T_KERNEL_MBXCB;

/* 優先度別キューヘッダをカーネルで確保する場合 */
typedef struct t_kernel_mbxcb_ph
{
	T_KERNEL_MBXCB	mbxcb;
	T_MSG		*mprihd[1];
} T_KERNEL_MBXCB_PH;


/* メールボックスの生成(カーネル内部関数) */
ER kernel_cre_mbx(
		ID           mbxid,		/* 生成対象のメールボックスのID番号 */
		const T_CMBX *pk_cmbx)	/* メールボックス生成情報を入れたパケットへのポインタ */
{
	T_KERNEL_MBXCB     *mbxcb;
	T_KERNEL_MBXCB_RAM *mbxcb_ram;
	T_KERNEL_MBXCB_ROM *mbxcb_rom;
	T_MSG **mprihd;
	PRI   maxmpri;
	PRI   msgpri;

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_cmbx->mbxatr & ~(TA_TFIFO | TA_TPRI | TA_MFIFO | TA_MPRI) )
	{
		return E_RSATR;
	}
#endif

	/* メッセージ優先度付きか判定 */
	if ( pk_cmbx->mbxatr & TA_MPRI )
	{
		maxmpri = pk_cmbx->maxmpri;
		mprihd  = (T_MSG **)pk_cmbx->mprihd;
	}
	else
	{
		maxmpri = TMIN_MPRI;
		mprihd  = NULL;
	}

	/* メールボックス用メモリの確保 */
	mbxcb = (T_KERNEL_MBXCB *)kernel_alc_mem(
			mprihd == NULL ?
			sizeof(T_KERNEL_MBXCB_PH)+TSZ_MPRIHD(maxmpri-1) :
			sizeof(T_KERNEL_MBXCB));
	if ( mbxcb == NULL )
	{
		return E_NOMEM;		/* メモリ不足 */
	}

	/* メッセージキューヘッダをカーネルで確保する場合のポインタセット */
	if ( mprihd == NULL )
	{
		mprihd = ((T_KERNEL_MBXCB_PH *)mbxcb)->mprihd;
	}

	/* メールボックスの設定 */
	mbxcb_ram = &mbxcb->mbxcb_ram;
	mbxcb_rom = &mbxcb->mbxcb_rom;
	mknl_ini_que(&mbxcb_ram->que);
	mbxcb_ram->mbxcb_rom = mbxcb_rom;
	mbxcb_rom->mbxatr    = pk_cmbx->mbxatr;
	mbxcb_rom->maxmpri   = maxmpri;
	mbxcb_rom->mprihd    = mprihd;

	/* 優先度別のメッセージキューの初期化 */
	for ( msgpri = 0; msgpri <= maxmpri - TMIN_MPRI; msgpri++ )
	{
		mprihd[msgpri] = NULL;
	}

	/* 管理テーブルへ追加 */
	KERNEL_MBXID_TO_MBXCB_RAM(mbxid) = mbxcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2003 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
