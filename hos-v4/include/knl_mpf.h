/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ 固定長メモリプール                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mpf_h__
#define __HOS_V4__knl_mpf_h__


#include "knl_hos.h"



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* IDの範囲 */
#define TMIN_MPFID		1					/* 固定長メモリプールIDの最小値 */
#define TMAX_MPFID		(TMIN_MPFID + kernel_mpfcb_cnt - 1)
											/* 固定長メモリプールIDの最大値 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* 固定長メモリプール生成情報 */
typedef struct t_cmpf
{
	ATR  mpfatr;		/* 固定長メモリプール属性 */
	UINT blkcnt;		/* 獲得できるメモリブロック数(個数) */
	UINT blksz;			/* メモリブロックのサイズ(バイト数) */
	VP   mpf;			/* 固定長メモリプール領域の先頭番地 */
} T_CMPF;

/* 固定長メモリプール状態 */
typedef struct t_rmpf
{
	ID   wtskid;		/* 固定長メモリプールの待ち行列の先頭のタスクのID番号 */
	UINT fblkcnt;		/* 固定長メモリプールの空きメモリブロック数(個数) */
} T_RMPF;


/* 固定長メモリプールコントロールブロック(ROM部) */
typedef struct t_kernel_mpfcb_rom
{
	ATR  mpfatr;		/* 固定長メモリプール属性 */
	UINT blkcnt;		/* 獲得できるメモリブロック数(個数) */
	UINT blksz;			/* メモリブロックのサイズ(バイト数) */
	VP   mpf;			/* 固定長メモリプール領域の先頭番地 */
} T_KERNEL_MPFCB_ROM;


/* 固定長メモリプールコントロールブロック(RAM部) */
typedef struct t_kernel_mpfcb_ram
{
	T_MKNL_QUE que;		/* 固定長メモリプール待ちタスクキュー */
	VP         free;	/* 空きブロックへのポインタ */
	const T_KERNEL_MPFCB_ROM *mpfcb_rom;	/* 固定長メモリプールコントロールブロックROM部へのポインタ */
} T_KERNEL_MPFCB_RAM;



/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* 固定長メモリプール管理 */
extern       T_KERNEL_MPFCB_RAM *kernel_mpfcb_ram_tbl[];	/* 固定長メモリプールコントロールブロックテーブル(RAM部) */
extern const INT kernel_mpfcb_cnt;							/* 固定長メモリプールコントロールブロック個数 */

/* 固定長メモリプールコントロールブロック変換マクロ */
#define KERNEL_MPFID_TO_MPFCB_RAM(mpfid)	(kernel_mpfcb_ram_tbl[(mpfid) - TMIN_MPFID])
															/* 固定長メモリプールIDからMPFCB RAMアドレスを取得 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* 固定長メモリプール */
void    kernel_ini_mpf(void);								/* 固定長メモリプールの初期化 */
ER      cre_mpf(ID mpfid, const T_CMPF *pk_cmpf);			/* 固定長メモリプールの生成 */
ER_ID   acre_mpf(const T_CMPF *pk_cmpf);					/* 固定長メモリプールの生成(ID番号自動割付け) */
ER      kernel_cre_mpf(ID mpfid, const T_CMPF *pk_cmpf);	/* 固定長メモリプールの生成(カーネル内部関数) */
ER      del_mpf(ID mpfid);									/* 固定長メモリプールの削除 */
ER      get_mpf(ID mpfid, VP *p_blk);						/* 固定長メモリブロックの獲得 */
ER      pget_mpf(ID mpfid, VP *p_blk);						/* 固定長メモリブロックの獲得(ポーリング) */
ER      tget_mpf(ID mpfid, VP *p_blk, TMO tmout);			/* 固定長メモリブロックの獲得(タイムアウトあり) */
ER      rel_mpf(ID mpfid, VP blk);							/* 固定長メモリブロックの返却 */
ER      ref_mpf(ID mpfid, T_RMPF *pk_rmpf);					/* 固定長メモリブロックの状態参照 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mpf_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
