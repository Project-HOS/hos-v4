/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネル依存情報定義ヘッダ セマフォ                                   */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_sem_h__
#define __HOS_V4__knl_sem_h__



/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* IDの範囲 */
#define TMIN_SEMID		1					/* セマフォIDの最小値 */
#define TMAX_SEMID		(TMIN_SEMID + kernel_semcb_cnt - 1)
											/* セマフォIDの最大値 */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* セマフォコントロールブロック(ROM部) */
typedef struct t_kernel_semcb_rom
{
	ATR  sematr;		/* セマフォ属性 */
	UINT isemcnt;		/* セマフォ資源数の初期値 */
	UINT maxsem;		/* セマフォの最大資源数 */
} T_KERNEL_SEMCB_ROM;


/* セマフォコントロールブロック(RAM部) */
typedef struct t_kernel_semcb_ram
{
	T_MKNL_QUE que;		/* セマフォ待ちタスクキュー */
	UINT       semcnt;	/* セマフォの資源数 */
	const T_KERNEL_SEMCB_ROM *semcbrom;	/* セマフォコントロールブロックROM部へのポインタ */
} T_KERNEL_SEMCB_RAM;



#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------- */
/*        グローバル変数宣言          */
/* ---------------------------------- */

/* セマフォ管理 */
extern       T_KERNEL_SEMCB_RAM *kernel_semcb_ram_tbl[];	/* セマフォコントロールブロックテーブル(RAM部) */
extern const INT kernel_semcb_cnt;							/* セマフォコントロールブロック個数 */

/* セマフォコントロールブロック変換マクロ */
#define KERNEL_SEMID_TO_SEMCB_RAM(semid)	(kernel_semcb_ram_tbl[(semid) - TMIN_SEMID])
															/* セマフォIDからSEMCB RAMアドレスを取得 */



/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

/* セマフォ */
void    kernel_ini_sem(void);						/* セマフォの初期化 */
ER      sig_sem(ID semid);							/* セマフォ資源の返却 */
#define isig_sem sig_sem							/* セマフォ資源の返却(非タスクコンテキスト用マクロ) */
ER      wai_sem(ID semid);							/* セマフォ資源の獲得 */
ER      pol_sem(ID semid);							/* セマフォ資源の獲得(ポーリング) */
ER      twai_sem(ID semid, TMO tmout);				/* セマフォ資源の獲得(タイムアウトあり) */

#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_sem_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
