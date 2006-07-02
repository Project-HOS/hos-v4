/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ 可変長メモリプール                         */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_mpl_h__
#define __HOS_V4__knl_mpl_h__


#include "knl_hos.h"
#include "knl_hep.h"



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* IDの範囲 */
#define KERNEL_TMIN_MPLID	TMIN_MPLID			/* 可変長メモリプールIDの最小値 */
#define KERNEL_TMAX_MPLID	(KERNEL_TMIN_MPLID + kernel_mplcb_cnt - 1)
												/* 可変長メモリプールIDの最大値 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* 可変長メモリプール生成情報 */
typedef struct t_cmpl
{
	ATR  mplatr;		/* 可変長メモリプール属性 */
	UINT mplsz;			/* 可変長メモリプール領域のサイズ(バイト数) */
	VP   mpl;			/* 可変長メモリプール領域の先頭番地 */
} T_CMPL;

/* 可変長メモリプール状態 */
typedef struct t_rmpl
{
	ID   wtskid;		/* 可変長メモリプールの待ち行列の先頭のタスクのID番号 */
	SIZE fmplsz;		/* 可変長メモリプールの空き領域の合計サイズ(バイト数) */
	UINT fblksz;		/* すぐに獲得可能な最大メモリブロックサイズ(バイト数) */
} T_RMPL;


/* 可変長メモリプールコントロールブロック(ROM部) */
typedef struct t_kernel_mplcb_rom
{
	ATR  mplatr;		/* 可変長メモリプール属性 */
	UINT mplsz;			/* 可変長メモリプール領域のサイズ(バイト数) */
	VP   mpl;			/* 可変長メモリプール領域の先頭番地 */
} T_KERNEL_MPLCB_ROM;


/* 可変長メモリプールコントロールブロック(RAM部) */
typedef struct t_kernel_mplcb_ram
{
	T_MKNL_QUE     que;	/* 可変長メモリプール待ちタスクキュー */
	T_KERNEL_HEPCB hep;	/* メモリヒープ */
	const T_KERNEL_MPLCB_ROM *mplcb_rom;	/* 可変長メモリプールコントロールブロックROM部へのポインタ */
} T_KERNEL_MPLCB_RAM;


/* メモリ待ち情報構造体 */
typedef struct t_kernel_mplinf
{
	UINT blksz;			/* 獲得するメモリブロックのサイズ(バイト数) */
	VP   *p_blk;		/* 獲得したメモリブロックの先頭番地 */
} T_KERNEL_MPLINF;



/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* 可変長メモリプール管理 */
extern       T_KERNEL_MPLCB_RAM *kernel_mplcb_ram_tbl[];	/* 可変長メモリプールコントロールブロックテーブル(RAM部) */
extern const INT kernel_mplcb_cnt;							/* 可変長メモリプールコントロールブロック個数 */


/* ---------------------------------- */
/*            マクロ定義              */
/* ---------------------------------- */

/* 可変長メモリプールコントロールブロック変換マクロ */
#define KERNEL_MPLID_TO_MPLCB_RAM(mplid)	(kernel_mplcb_ram_tbl[(mplid) - KERNEL_TMIN_MPLID])
															/* 可変長メモリプールIDからMPLCB RAMアドレスを取得 */


/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif

/* 可変長メモリプール */
void    kernel_ini_mpl(void);								/* 可変長メモリプールの初期化 */
ER      cre_mpl(ID mplid, const T_CMPL *pk_cmpl);			/* 可変長メモリプールの生成 */
ER_ID   acre_mpl(const T_CMPL *pk_cmpl);					/* 可変長メモリプールの生成(ID番号自動割付け) */
ER      kernel_cre_mpl(ID mplid, const T_CMPL *pk_cmpl);	/* 可変長メモリプールの生成(カーネル内部関数) */
ER      del_mpl(ID mplid);									/* 可変長メモリプールの削除 */
ER      get_mpl(ID mplid, UINT blksz, VP *p_blk);			/* 可変長メモリブロックの獲得 */
ER      pget_mpl(ID mplid, UINT blksz, VP *p_blk);			/* 可変長メモリブロックの獲得(ポーリング) */
ER      tget_mpl(ID mplid, UINT blksz, VP *p_blk, TMO tmout);
															/* 可変長メモリブロックの獲得(タイムアウトあり) */
ER      rel_mpl(ID mplid, VP blk);							/* 可変長メモリブロックの返却 */
ER      ref_mpl(ID mplid, T_RMPL *pk_rmpl);					/* 可変長メモリブロックの状態参照 */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_mpl_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
