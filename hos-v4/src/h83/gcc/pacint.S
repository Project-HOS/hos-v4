/* -------------------------------------------------------------------------*/
/*  Hyper Operating System V4                                               */
/*    割り込みハンドラ  Hitachi H8/300H 用                                  */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


				.h8300h


				.text
				.align 2


				.global	_hos_vecter001
				.global	_hos_vecter002
				.global	_hos_vecter003
				.global	_hos_vecter004
				.global	_hos_vecter005
				.global	_hos_vecter006
				.global	_hos_vecter007
				.global	_hos_vecter008
				.global	_hos_vecter009
				.global	_hos_vecter010
				.global	_hos_vecter011
				.global	_hos_vecter012
				.global	_hos_vecter013
				.global	_hos_vecter014
				.global	_hos_vecter015
				.global	_hos_vecter016
				.global	_hos_vecter017
				.global	_hos_vecter018
				.global	_hos_vecter019
				.global	_hos_vecter020
				.global	_hos_vecter021
				.global	_hos_vecter022
				.global	_hos_vecter023
				.global	_hos_vecter024
				.global	_hos_vecter025
				.global	_hos_vecter026
				.global	_hos_vecter027
				.global	_hos_vecter028
				.global	_hos_vecter029
				.global	_hos_vecter030
				.global	_hos_vecter031
				.global	_hos_vecter032
				.global	_hos_vecter033
				.global	_hos_vecter034
				.global	_hos_vecter035
				.global	_hos_vecter036
				.global	_hos_vecter037
				.global	_hos_vecter038
				.global	_hos_vecter039
				.global	_hos_vecter040
				.global	_hos_vecter041
				.global	_hos_vecter042
				.global	_hos_vecter043
				.global	_hos_vecter044
				.global	_hos_vecter045
				.global	_hos_vecter046
				.global	_hos_vecter047
				.global	_hos_vecter048
				.global	_hos_vecter049
				.global	_hos_vecter050
				.global	_hos_vecter051
				.global	_hos_vecter052
				.global	_hos_vecter053
				.global	_hos_vecter054
				.global	_hos_vecter055
				.global	_hos_vecter056
				.global	_hos_vecter057
				.global	_hos_vecter058
				.global	_hos_vecter059
				.global	_hos_vecter060
				.global	_hos_vecter061
				.global	_hos_vecter062
				.global	_hos_vecter063



/************************************************
  割り込みハンドラ
*************************************************/
_hos_vecter001:	push.l	er0
				mov.l	#1, er0
				bra		int_handler

_hos_vecter002:	push.l	er0
				mov.l	#2, er0
				bra		int_handler

_hos_vecter003:	push.l	er0
				mov.l	#3, er0
				bra		int_handler

_hos_vecter004:	push.l	er0
				mov.l	#4, er0
				bra		int_handler

_hos_vecter005:	push.l	er0
				mov.l	#5, er0
				bra		int_handler

_hos_vecter006:	push.l	er0
				mov.l	#6, er0
				bra		int_handler

_hos_vecter007:	push.l	er0
				mov.l	#7, er0
				bra		int_handler

_hos_vecter008:	push.l	er0
				mov.l	#8, er0
				bra		int_handler

_hos_vecter009:	push.l	er0
				mov.l	#9, er0
				bra		int_handler

_hos_vecter010:	push.l	er0
				mov.l	#10, er0
				bra		int_handler

_hos_vecter011:	push.l	er0
				mov.l	#11, er0
				bra		int_handler

_hos_vecter012:	push.l	er0
				mov.l	#12, er0
				bra		int_handler

_hos_vecter013:	push.l	er0
				mov.l	#13, er0
				bra		int_handler

_hos_vecter014:	push.l	er0
				mov.l	#14, er0
				bra		int_handler

_hos_vecter015:	push.l	er0
				mov.l	#15, er0
				bra		int_handler

_hos_vecter016:	push.l	er0
				mov.l	#16, er0
				bra		int_handler

_hos_vecter017:	push.l	er0
				mov.l	#17, er0
				bra		int_handler

_hos_vecter018:	push.l	er0
				mov.l	#18, er0
				bra		int_handler

_hos_vecter019:	push.l	er0
				mov.l	#19, er0
				bra		int_handler

_hos_vecter020:	push.l	er0
				mov.l	#20, er0
				bra		int_handler

_hos_vecter021:	push.l	er0
				mov.l	#21, er0
				bra		int_handler

_hos_vecter022:	push.l	er0
				mov.l	#22, er0
				bra		int_handler

_hos_vecter023:	push.l	er0
				mov.l	#23, er0
				bra		int_handler

_hos_vecter024:	push.l	er0
				mov.l	#24, er0
				bra		int_handler

_hos_vecter025:	push.l	er0
				mov.l	#25, er0
				bra		int_handler

_hos_vecter026:	push.l	er0
				mov.l	#26, er0
				bra		int_handler

_hos_vecter027:	push.l	er0
				mov.l	#27, er0
				bra		int_handler

_hos_vecter028:	push.l	er0
				mov.l	#28, er0
				bra		int_handler

_hos_vecter029:	push.l	er0
				mov.l	#29, er0
				bra		int_handler

_hos_vecter030:	push.l	er0
				mov.l	#30, er0
				bra		int_handler

_hos_vecter031:	push.l	er0
				mov.l	#31, er0
				bra		int_handler

_hos_vecter032:	push.l	er0
				mov.l	#32, er0
				bra		int_handler

_hos_vecter033:	push.l	er0
				mov.l	#33, er0
				bra		int_handler

_hos_vecter034:	push.l	er0
				mov.l	#34, er0
				bra		int_handler

_hos_vecter035:	push.l	er0
				mov.l	#35, er0
				bra		int_handler

_hos_vecter036:	push.l	er0
				mov.l	#36, er0
				bra		int_handler

_hos_vecter037:	push.l	er0
				mov.l	#37, er0
				bra		int_handler

_hos_vecter038:	push.l	er0
				mov.l	#38, er0
				bra		int_handler

_hos_vecter039:	push.l	er0
				mov.l	#39, er0
				bra		int_handler

_hos_vecter040:	push.l	er0
				mov.l	#40, er0
				bra		int_handler

_hos_vecter041:	push.l	er0
				mov.l	#41, er0
				bra		int_handler

_hos_vecter042:	push.l	er0
				mov.l	#42, er0
				bra		int_handler

_hos_vecter043:	push.l	er0
				mov.l	#43, er0
				bra		int_handler

_hos_vecter044:	push.l	er0
				mov.l	#44, er0
				bra		int_handler

_hos_vecter045:	push.l	er0
				mov.l	#45, er0
				bra		int_handler

_hos_vecter046:	push.l	er0
				mov.l	#46, er0
				bra		int_handler

_hos_vecter047:	push.l	er0
				mov.l	#47, er0
				bra		int_handler

_hos_vecter048:	push.l	er0
				mov.l	#48, er0
				bra		int_handler

_hos_vecter049:	push.l	er0
				mov.l	#49, er0
				bra		int_handler

_hos_vecter050:	push.l	er0
				mov.l	#50, er0
				bra		int_handler

_hos_vecter051:	push.l	er0
				mov.l	#51, er0
				bra		int_handler

_hos_vecter052:	push.l	er0
				mov.l	#52, er0
				bra		int_handler

_hos_vecter053:	push.l	er0
				mov.l	#53, er0
				bra		int_handler

_hos_vecter054:	push.l	er0
				mov.l	#54, er0
				bra		int_handler

_hos_vecter055:	push.l	er0
				mov.l	#55, er0
				bra		int_handler

_hos_vecter056:	push.l	er0
				mov.l	#56, er0
				bra		int_handler

_hos_vecter057:	push.l	er0
				mov.l	#57, er0
				bra		int_handler

_hos_vecter058:	push.l	er0
				mov.l	#58, er0
				bra		int_handler

_hos_vecter059:	push.l	er0
				mov.l	#59, er0
				bra		int_handler

_hos_vecter060:	push.l	er0
				mov.l	#60, er0
				bra		int_handler

_hos_vecter061:	push.l	er0
				mov.l	#61, er0
				bra		int_handler

_hos_vecter062:	push.l	er0
				mov.l	#62, er0
				bra		int_handler

_hos_vecter063:	push.l	er0
				mov.l	#63, er0
				bra		int_handler



/************************************************
          割り込み処理

  割り込み発生時は er0 を push した後、er0 に
  割り込み番号をセットして、ここにジャンプする
*************************************************/
				.extern	_kernel_sta_int		/* 割り込み処理開始 */
				.extern	_kernel_end_int		/* 割り込み処理終了 */
				.extern	_kernel_exe_int		/* 割り込み処理実行 */
				.extern	_kernel_int_sp		/* 割り込み用スタックアドレス */
				.extern	_kernel_h83_imsk	/* 現在の割り込みマスク値 */
				.extern	_kernel_h83_ibmsk	/* ベース割り込みマスク値 */

int_handler:	
				/* レジスタ保存 */
				push.l	er1
				
				/* 割り込みマスク設定 */
				stc.b	ccr, r1l
				and.b	#h'c0, r1l
				mov.b	r1l, @_kernel_h83_imsk
				
				/* 多重割り込みの判別 */
				mov.w	@__HOS_int_cnt, r1
				bne		mul_int
				
		/* ======== 最初の割り込み ======== */
				/* 割り込みネストカウンタ設定 */
				mov.w	#1, r1
				mov.w	r1, @__HOS_int_cnt
				
				/* スタックポインタの入れ替え */
				mov.l	er7, @__HOS_int_sp
				mov.l	@_kernel_int_sp, er1
				mov.l	@er1, er7
				
				/* 割り込み処理の開始 */
				push.l	er0
				jsr		@_kernel_sta_int
				pop.l	er0
				
				/* 割り込みハンドラの処理 */
				jsr		@_kernel_exe_int
				
				/* スタックポインタ復帰 */
				mov.l	@__HOS_int_sp, er7
				
				/* 割り込みネストカウンタクリア */
				xor.w	r1, r1
				mov.w	r1, @__HOS_int_cnt
				
				/* 割り込みマスク値の復帰 */
				mov.b	@_kernel_h83_ibmsk, r0l
				mov.b	r0l, @_kernel_h83_imsk		/* 割り込みマスク値をベース値に戻す */
				
				/* タスクコンテキストに移行 */
				jsr		@_kernel_end_int
				
				/* 復帰後のマスク値を設定 */
				mov.b	@_kernel_h83_ibmsk, r0l		/* ベースマスク値取り出し */
				mov.b	@(8, er7), r1l
				and.b	#h'3f, r1l					/* スタック上のCCRからIとUI以外を取り出し */
				or.b	r0l, r1l					/* ベースマスク値を設定 */
				mov.b	r1l, @(8, er7)				/* スタック上のCCRを更新 */
				
				/* 復帰 */
				pop.l	er1
				pop.l	er0
				rte


		/* ======== 多重割り込み ======== */
mul_int:		
				/* 割り込みネストカウンタ加算 */
				inc.w	#1, r1
				mov.w	r1, @__HOS_int_cnt
				
				/* 割り込みハンドラ呼び出し */
				mov.l	er2, er0			/* 割り込み番号を引数とする */
				jsr		@_kernel_exe_int
				
				/* 割り込みネストカウンタ減算 */
				mov.w	@__HOS_int_cnt, r0
				dec.w	#1, r0
				mov.w	r0, @__HOS_int_cnt
				
				/* 復帰 */
				pop.l	er1
				pop.l	er0
				rte



/************************************************
       割り込み処理データ
*************************************************/
					.data
					.align 2

__HOS_int_sp:	.long	0		/* 割り込み時のスタックポインタ(er7)保存用 */
__HOS_int_cnt:	.word	0		/* 割り込みネストカウンタ */



				.end


/* -------------------------------------------------------------------------*/
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* -------------------------------------------------------------------------*/
