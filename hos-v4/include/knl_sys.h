/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネル依存情報定義ヘッダ システム状態管理                           */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#ifndef __HOS_V4__knl_sys_h__
#define __HOS_V4__knl_sys_h__



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



#ifdef __cplusplus
}
#endif



#endif	/* __HOS_V4__knl_sys_h__ */


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
