/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (MIPS3互換コア用)                      */
/*    割り込みハンドラ                                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2008 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "mipsregs.h"

		.global int_handler				/* 割り込みハンドラ */
		.global inthdl					/* crt0.c 用 */
		.global einthdl					/* crt0.c 用 */
		.global inthdljp				/* crt0.c 用 */
/***********************************************************************
 *  割り込みハンドラ (0x80000800 へ crt0.c にてコピーされる）
 *  内部で割り込み要因を判定して登録したハンドラを呼び出す。
 *  現在はタイマ割り込みしかサポートしていない。
 ***********************************************************************/
		.text
		.align	4
int_handler:
inthdl:
		pushall							/* レジスタ退避				*/

		/* スタックの退避 */
		la		k0, kernel_int_ssp
		sw		sp, (k0)
		la		k0, kernel_int_sp
		lw		sp, (k0)

		/* 割り込み開始処理呼び出し */
		la		k0, kernel_sta_int
		jal		k0
		nop

		/* 割り込み番号を引数して実行処理呼び出し
		（とりあえずタイマ割り込みだけがかかるとする。割り込みベクタ番号=1）*/
		la		k0, kernel_exe_int
		li		a0, 1
		jal		k0
		nop

		/* スタックの復帰 */
		la		k0, kernel_int_ssp
		lw		sp, (k0)

		/* IE=0, EXL=0にセット（割り込みは禁止のまま）*/
		mfc0	k0, CP0_STATUS
		nop
		la		k1, 0xF1FFFFF8					/* ERL=0,IE=0,EXL=0 */
		and		k0, k1, k0
		mtc0	k0, CP0_STATUS
		nop

		/* 割り込み終了処理呼び出し */
		la		k0, kernel_end_int
		jal		k0
		nop

		/* IE=1, EXL=1にセット（割り込みは禁止のまま）*/
		mfc0	k0, CP0_STATUS
		nop
		la		k1, 0xF1FFFFFB
		and		k0, k1, k0				/* ERL=0 */
		la		k1, 0x00000003			/* IE=1, EXL=1 */
		or		k0, k1, k0
		mtc0	k0, CP0_STATUS
		nop

		popall							/* レジスタ復帰				*/
		eret
einthdl:
/***********************************************************************
 *  0x80000180の例外処理発生時にinthdlへ処理を移行するための細工
 *  crt0.c にてジャンプ命令をコピーし実現する。
 ***********************************************************************/
		.text
		.align	4
inthdljp:								/* 0x80000180 へコピー(crt0.cにて) */
		j		0x80000800
		nop
/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2008 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
