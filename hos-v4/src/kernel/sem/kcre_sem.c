/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    ITRONカーネル セマフォ                                                */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"
#include "knl_mem.h"


/* セマフォコントロールブロック(動的生成用) */
typedef struct t_kernel_semcb
{
	T_KERNEL_SEMCB_RAM semcb_ram;	/* セマフォコントロールブロック(RAM部) */
	T_KERNEL_SEMCB_ROM semcb_rom;	/* セマフォコントロールブロック(ROM部) */
} T_KERNEL_SEMCB;



/* セマフォの生成(カーネル内部関数) */
ER kernel_cre_sem(
		ID           semid,		/* 生成対象のセマフォのID番号 */
		const T_CSEM *pk_csem)	/* セマフォ生成情報を入れたパケットへのポインタ */
{
	T_KERNEL_SEMCB     *semcb;
	T_KERNEL_SEMCB_RAM *semcb_ram;
	T_KERNEL_SEMCB_ROM *semcb_rom;

	/* パラメーターチェック */
#ifdef HOS_ERCHK_E_RSATR
	if ( pk_csem->sematr & ~(TA_TFIFO | TA_TPRI) )
	{
		return E_RSATR;
	}
#endif

	/* セマフォ用メモリの確保 */
	semcb = (T_KERNEL_SEMCB *)kernel_alc_mem(sizeof(T_KERNEL_SEMCB));
#ifdef HOS_ERCHK_E_NOMEM
	if ( semcb == NULL )
	{
		return E_NOMEM;		/* メモリ不足 */
	}
#endif

	/* セマフォの設定 */
	semcb_ram = &semcb->semcb_ram;
	semcb_rom = &semcb->semcb_rom;
	mknl_ini_que(&semcb_ram->que);
	semcb_ram->semcnt    = pk_csem->isemcnt;
	semcb_ram->semcb_rom = semcb_rom;
	semcb_rom->sematr    = pk_csem->sematr;
	semcb_rom->isemcnt   = pk_csem->isemcnt;
	semcb_rom->maxsem    = pk_csem->maxsem;

	/* 管理テーブルへ追加 */
	kernel_semcb_ram_tbl[semid - TMIN_SEMID] = semcb_ram;

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
