/* ------------------------------------------------------------------------ */
/*  HOS-V4                                                                  */
/*    カーネルコンフィギュレーション ソースファイル                         */
/*                                                                          */
/*                              Copyright (C) 1998-2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "kernel_id.h"

/* INCLUDE() API による生成 */
#include "test.h"



/* ------------------------------------------ */
/*         レディキューの静的生成             */
/* ------------------------------------------ */

T_MKNL_QUE mknl_rdq_tbl[8];			/* レディーキューテーブル */
const INT mknl_rdq_cnt = 8;			/* レディーキュー個数 */



/* ------------------------------------------ */
/*             タスクの静的生成               */
/* ------------------------------------------ */

static UW Tsk1Stack[(4096 + 3) / 4];
static UW Tsk2Stack[(4096 + 3) / 4];
static UW Tsk3Stack[(4096 + 3) / 4];

/* タスクコントロールブロックテーブル(ROM部) */
const T_KERNEL_TCB_ROM kernel_tcb_rom[3] =
	{
		{(ATR)TA_HLNG, (VP_INT)0, (FP)Task1, (PRI)1, (SIZE)sizeof(Tsk1Stack), (VP)Tsk1Stack},
		{(ATR)TA_HLNG, (VP_INT)0, (FP)Task2, (PRI)2, (SIZE)sizeof(Tsk2Stack), (VP)Tsk2Stack},
		{(ATR)TA_HLNG, (VP_INT)0, (FP)Task3, (PRI)3, (SIZE)sizeof(Tsk3Stack), (VP)Tsk3Stack},
	};

/* タスクコントロールブロックテーブル(RAM部) */
T_KERNEL_TCB_RAM kernel_tcb_ram[3];

/* タスクコントロールブロックテーブル(RAM部) */
T_KERNEL_TCB_RAM *kernel_tcb_ram_tbl[3] =
	{
		&kernel_tcb_ram[0],
		&kernel_tcb_ram[1],
		&kernel_tcb_ram[2],
	};

const INT kernel_tcb_cnt = 3;					/* タスクコントロールブロック個数 */



/* ------------------------------------------ */
/*            セマフォの静的生成              */
/* ------------------------------------------ */

const T_KERNEL_SEMCB_ROM kernel_semcb_rom[2] =	/* セマフォコントロールブロック(ROM部) */
	{
		{TA_TFIFO, 1, 1},
		{TA_TFIFO, 1, 1},
	};

T_KERNEL_SEMCB_RAM kernel_semcb_ram[2];			/* セマフォコントロールブロック(RAM部) */

/* セマフォコントロールブロックテーブル(RAM部) */
T_KERNEL_SEMCB_RAM *kernel_semcb_ram_tbl[2] =
	{
		&kernel_semcb_ram[0],
		&kernel_semcb_ram[1],
	};

const INT kernel_semcb_cnt = 2;					/* セマフォコントロールブロック個数 */



/* ------------------------------------------ */
/*        イベントフラグの静的生成            */
/* ------------------------------------------ */
const T_KERNEL_FLGCB_ROM kernel_flgcb_rom[2] =	/* イベントフラグコントロールブロック(ROM部) */
	{
		{TA_WSGL, 0},
		{TA_WSGL, 0},
	};

T_KERNEL_FLGCB_RAM kernel_flgcb_ram[2];			/* イベントフラグコントロールブロック(RAM部) */

T_KERNEL_FLGCB_RAM *kernel_flgcb_ram_tbl[2] =	/* イベントフラグコントロールブロックテーブル(RAM部) */
	{
		&kernel_flgcb_ram[0],
		&kernel_flgcb_ram[1],
	};

const INT kernel_flgcb_cnt = 2;					/* イベントフラグコントロールブロック個数 */



/* ------------------------------------------ */
/*         データキューの静的生成             */
/* ------------------------------------------ */
VP_INT kernel_dtq1data[128];
VP_INT kernel_dtq2data[128];

const T_KERNEL_DTQCB_ROM kernel_dtqcb_rom[2] =	/* イベントフラグコントロールブロック(ROM部) */
	{
		{0, 128, kernel_dtq1data},
		{0, 128, kernel_dtq2data},
	};

T_KERNEL_DTQCB_RAM kernel_dtqcb_ram[2];			/* イベントフラグコントロールブロック(RAM部) */

T_KERNEL_DTQCB_RAM *kernel_dtqcb_ram_tbl[2] =	/* イベントフラグコントロールブロックテーブル(RAM部) */
	{
		&kernel_dtqcb_ram[0],
		&kernel_dtqcb_ram[1],
	};

const INT kernel_dtqcb_cnt = 2;					/* イベントフラグコントロールブロック個数 */



/* ------------------------------------------ */
/*          時間管理機能の静的生成            */
/* ------------------------------------------ */

const UW kernel_tic_deno = TIC_DENO;			/* TIC_DENO を設定 */
const UW kernel_tic_div  = TIC_NUME / TIC_DENO;	/* ベース加算単位を設定 */
const UW kernel_tic_mod  = TIC_NUME % TIC_DENO;	/* 補正加算量を設定 */

T_MKNL_TIMOUT mknl_timout[16];					/* タイムアウト待ち行列 */
const INT     mknl_timout_size = 16;			/* タイムアウト待ち行列のサイズ */



/* ------------------------------------------ */
/*          周期ハンドラの静的生成            */
/* ------------------------------------------ */

T_KERNEL_CYCCB_ROM kernel_cyccb_rom[1] =		/* 周期ハンドラコントロールブロック(ROM部) */
	{
		{0, CycHandler1, 10},
	};

T_KERNEL_CYCCB_RAM kernel_cyccb_ram[1];			/* 周期ハンドラコントロールブロック(RAM部) */

T_KERNEL_CYCCB_RAM *kernel_cyccb_ram_tbl[1] =	/* 周期ハンドラコントロールブロックテーブル */
	{
		&kernel_cyccb_ram[0],
	};

const INT kernel_cyccb_cnt = 1;					/* 周期ハンドラコントロールブロック個数 */



/* ------------------------------------------ */
/*               割り込み制御                 */
/* ------------------------------------------ */

UW mknl_int_stack[(1024 + 3) / 4];				/* 割り込み用スタック */

const VP   mknl_int_stk   = mknl_int_stack;		/* 割り込みスタックアドレス */
const SIZE mknl_int_stksz = 1024;				/* 割り込みスタックサイズ */

T_KERNEL_INTCB  kernel_intcb_tbl[32];			/* 割り込み管理コントロールブロックテーブル */
const INT       kernel_intcb_cnt = 32;			/* 最大割り込み番号数 */



/* ------------------------------------------ */
/*               初期化関数                   */
/* ------------------------------------------ */

/* コンフィギュレーター変数の初期化 */
void kernel_cfg_init(void)
{
	/* RAMデータは殆ど0なので DATA 領域に置くより BSS に置いてここで初期化したほうが効率がよい */

	/* タスクコントロールブロック初期化 */
	kernel_tcb_ram[0].tcbrom = &kernel_tcb_rom[0];
	kernel_tcb_ram[1].tcbrom = &kernel_tcb_rom[1];
	kernel_tcb_ram[2].tcbrom = &kernel_tcb_rom[2];

	/* セマフォコントロールブロック初期化 */
	kernel_semcb_ram[0].semcbrom = &kernel_semcb_rom[0];
	kernel_semcb_ram[1].semcbrom = &kernel_semcb_rom[1];

	/* イベントフラグコントロールブロック初期化 */
	kernel_flgcb_ram[0].flgcbrom = &kernel_flgcb_rom[0];
	kernel_flgcb_ram[1].flgcbrom = &kernel_flgcb_rom[1];
	
	/* データキューコントロールブロック初期化 */
	kernel_dtqcb_ram[0].dtqcbrom = &kernel_dtqcb_rom[0];
	kernel_dtqcb_ram[1].dtqcbrom = &kernel_dtqcb_rom[1];
	
	/* 周期ハンドラコントロールブロック初期化 */
	kernel_cyccb_ram[0].cyccbrom = &kernel_cyccb_rom[0];

	/* 割り込み登録 */
	kernel_intcb_tbl[1].exinf = 0;
	kernel_intcb_tbl[1].isr   = IntHndler1;
}


/* ATT_INI などを処理 */
void kernel_cfg_start(void)
{
	/* 利用するオブジェクトのみを初期化(余計なものをリンクさせない) */
	kernel_ini_tsk();		/* タスクの初期化 */
	kernel_ini_sem();		/* セマフォの初期化 */
	kernel_ini_flg();		/* イベントフラグの初期化 */

	/* ATT_INI の処理 */
	TestStart((VP_INT)0);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Ryuji Fuchikami                              */
/* ------------------------------------------------------------------------ */
