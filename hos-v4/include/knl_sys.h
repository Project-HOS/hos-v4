/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    カーネル依存情報定義ヘッダ システム状態管理                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */

#ifndef __HOS_V4__knl_sys_h__
#define __HOS_V4__knl_sys_h__


#include "knl_hos.h"
#include "knl_tsk.h"


/* ------------------------------------------ */
/*                  定数定義                  */
/* ------------------------------------------ */

/* バージョン情報 */
#define TKERNEL_MAKER	0x0008				/* メーカーコード(個人) */
#define TKERNEL_PRID	0x0000				/* カーネルの識別番号(未定) */
#define TKERNEL_SPVER	0x5401				/* ITRON仕様のバージョン(μITRON Ver 4.01) */
#define TKERNEL_PRVER	0x0001				/* カーネルのバージョン番号 (HOS-V4 Ver 0.01) */



/* ------------------------------------------ */
/*                 型定義                     */
/* ------------------------------------------ */

/* バージョン情報 */
typedef struct t_rver
{
	UH    maker;		/* カーネルのメーカーコード */
	UH    prid;			/* カーネルの識別番号 */
	UH    spver;		/* ITRON仕様のバージョン情報 */
	UH    prver;		/* カーネルのバージョン番号 */
	UH    prno[4];		/* カーネル製品の管理情報 */
} T_RVER;



#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------ */
/*                関数宣言                    */
/* ------------------------------------------ */

/* システム状態管理機能 */
ER      rot_rdq(PRI tskpri);						/* タスク優先順位の回転 */
#define irot_rdq	rot_rdq							/* タスク優先順位の回転(非タスクコンテキスト用マクロ) */
ER      get_tid(ID *p_tskid);						/* 実行状態タスクIDの参照 */
ID      kernel_get_tid(T_KERNEL_TCB_RAM *tcb_ram);	/* タスクIDの取得(カーネル内部関数) */
ER      loc_cpu(void);								/* CPUロック状態への移行 */
#define iloc_cpu	loc_cpu							/* CPUロック状態への移行(非タスクコンテキスト用マクロ) */
ER      unl_cpu(void);								/* CPUロック状態の解除 */
#define iunl_cpu	unl_cpu							/* CPUロック状態の解除(非タスクコンテキスト用マクロ)  */
ER      dis_dsp(void);								/* ディスパッチの禁止 */
ER      ena_dsp(void);								/* ディスパッチの許可 */
BOOL    sns_ctx(void);								/* コンテキストの参照 */
BOOL    sns_loc(void);								/* CPUロック状態の参照 */
BOOL    sns_dsp(void);								/* ディスパッチ禁止状態の参照 */
BOOL    sns_dpn(void);								/* ディスパッチ保留状態の参照 */

/* システム構成管理機能 */
ER      ref_ver(T_RVER *pk_rver);					/* バージョン番号の参照 */


#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_sys_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
