/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (MIPS3互換コア用)                      */
/*    割り込みハンドラ                                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "mipsregs.h"

                .global int_handler     /* 割り込みハンドラ */
        
/**
 * 割り込みハンドラ
 * 内部で割り込み要因を判定して登録したハンドラを呼び出す。
 * 現在はタイマ割り込みしかサポートしていない。
 */
				.text
				.align	2
int_handler:	
				/* レジスタ退避(r1-r1) */
                move    k0, sp          /* 伸張前のスタックポインタを退避 */
                addiu   sp, -288        /* スタックフレームの確保 */
                sw      $2, 4*2(sp)
                sw      $3, 4*3(sp)
                sw      $4, 4*4(sp)
                sw      $5, 4*5(sp)
                sw      $6, 4*6(sp)
                sw      $7, 4*7(sp)
                sw      $8, 4*8(sp)
                sw      $9, 4*9(sp)
                sw      $10, 4*10(sp)
                sw      $11, 4*11(sp)
                sw      $12, 4*12(sp)
                sw      $13, 4*13(sp)
                sw      $14, 4*14(sp)
                sw      $15, 4*15(sp)
                sw      $16, 4*16(sp)
                sw      $17, 4*17(sp)
                sw      $18, 4*18(sp)
                sw      $19, 4*19(sp)
                sw      $20, 4*20(sp)
                sw      $21, 4*21(sp)
                sw      $22, 4*22(sp)
                sw      $23, 4*23(sp)
                sw      $24, 4*24(sp)
                sw      $25, 4*25(sp)
                sw      $26, 4*26(sp)
                sw      $27, 4*27(sp)
                sw      k0,  4*29(sp)           /* sp   を退避（伸張前の値）*/
                sw      $31, 4*31(sp)           /* raを退避*/

        		mfc0	v1, CP0_EPC
        		sw      v1, 4*34(sp)            /* EPCを退避 */

           		/* スタックの退避 */
                la      k0, kernel_int_ssp
                sw      sp, (k0)
                la      k0, kernel_int_sp
                lw      sp, (k0)

				/* 割り込み開始処理呼び出し */
				la      k0, kernel_sta_int
				jal		k0
				nop

                /* 割り込み番号を引数して実行処理呼び出し
                （とりあえずタイマ割り込みだけがかかるとする。割り込みベクタ番号=1）*/
                la      k0, kernel_exe_int
                li      a0, 1
                jal     k0
                nop
        
           		/* スタックの復帰 */
                la      k0, kernel_int_ssp
                lw      sp, (k0)

                /* IE=0, EXL=0にセット（割り込みは禁止のまま）*/
                mfc0    k0, CP0_STATUS
                la      k1, 0xfffffffc
                and     k0, k0, k1                      /* IE=0, EXL=0 */
                mtc0    k0, CP0_STATUS

				/* 割り込み終了処理呼び出し */
                la      k0, kernel_end_int
				jal     k0
				nop

                /* IE=1, EXL=1にセット（割り込みは禁止のまま）*/
                mfc0    k0, CP0_STATUS
                la      k1, 0x00000003
                or      k0, k0, k1                      /* IE=1, EXL=1 */
                mtc0    k0, CP0_STATUS

				/* レジスタ復帰 */
                lw      $2, 4*2(sp)
                lw      $3, 4*3(sp)
                lw      $4, 4*4(sp)
                lw      $5, 4*5(sp)
                lw      $6, 4*6(sp)
                lw      $7, 4*7(sp)
                lw      $8, 4*8(sp)
                lw      $9, 4*9(sp)
                lw      $10, 4*10(sp)
                lw      $11, 4*11(sp)
                lw      $12, 4*12(sp)
                lw      $13, 4*13(sp)
                lw      $14, 4*14(sp)
                lw      $15, 4*15(sp)
                lw      $16, 4*16(sp)
                lw      $17, 4*17(sp)
                lw      $18, 4*18(sp)
                lw      $19, 4*19(sp)
                lw      $20, 4*20(sp)
                lw      $21, 4*21(sp)
                lw      $22, 4*22(sp)
                lw      $23, 4*23(sp)
                lw      $24, 4*24(sp)
                lw      $25, 4*25(sp)
                lw      $26, 4*26(sp)
                lw      $27, 4*27(sp)
                lw      $31, 4*31(sp)           /* raの復帰 */
        
        		lw      v1, 4*34(sp)            /* EPCの復帰 */
         		mtc0	v1, CP0_EPC
                lw      $29, 4*29(sp)           /* スタックポインタの復帰 */

                eret

/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
