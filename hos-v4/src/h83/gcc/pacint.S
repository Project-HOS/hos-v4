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


				.global	_hos_vector001
				.global	_hos_vector002
				.global	_hos_vector003
				.global	_hos_vector004
				.global	_hos_vector005
				.global	_hos_vector006
				.global	_hos_vector007
				.global	_hos_vector008
				.global	_hos_vector009
				.global	_hos_vector010
				.global	_hos_vector011
				.global	_hos_vector012
				.global	_hos_vector013
				.global	_hos_vector014
				.global	_hos_vector015
				.global	_hos_vector016
				.global	_hos_vector017
				.global	_hos_vector018
				.global	_hos_vector019
				.global	_hos_vector020
				.global	_hos_vector021
				.global	_hos_vector022
				.global	_hos_vector023
				.global	_hos_vector024
				.global	_hos_vector025
				.global	_hos_vector026
				.global	_hos_vector027
				.global	_hos_vector028
				.global	_hos_vector029
				.global	_hos_vector030
				.global	_hos_vector031
				.global	_hos_vector032
				.global	_hos_vector033
				.global	_hos_vector034
				.global	_hos_vector035
				.global	_hos_vector036
				.global	_hos_vector037
				.global	_hos_vector038
				.global	_hos_vector039
				.global	_hos_vector040
				.global	_hos_vector041
				.global	_hos_vector042
				.global	_hos_vector043
				.global	_hos_vector044
				.global	_hos_vector045
				.global	_hos_vector046
				.global	_hos_vector047
				.global	_hos_vector048
				.global	_hos_vector049
				.global	_hos_vector050
				.global	_hos_vector051
				.global	_hos_vector052
				.global	_hos_vector053
				.global	_hos_vector054
				.global	_hos_vector055
				.global	_hos_vector056
				.global	_hos_vector057
				.global	_hos_vector058
				.global	_hos_vector059
				.global	_hos_vector060
				.global	_hos_vector061
				.global	_hos_vector062
				.global	_hos_vector063


/************************************************
  割り込みハンドラ
*************************************************/
_hos_vector001:	push.l	er0
				mov.b	#1, r0l
				bra		int_handler1:8

_hos_vector002:	push.l	er0
				mov.b	#2, r0l
				bra		int_handler1:8

_hos_vector003:	push.l	er0
				mov.b	#3, r0l
				bra		int_handler1:8

_hos_vector004:	push.l	er0
				mov.b	#4, r0l
				bra		int_handler1:8

_hos_vector005:	push.l	er0
				mov.b	#5, r0l
				bra		int_handler1:8

_hos_vector006:	push.l	er0
				mov.b	#6, r0l
				bra		int_handler1:8

_hos_vector007:	push.l	er0
				mov.b	#7, r0l
				bra		int_handler1:8

_hos_vector008:	push.l	er0
				mov.b	#8, r0l
				bra		int_handler1:8

_hos_vector009:	push.l	er0
				mov.b	#9, r0l
				bra		int_handler1:8

_hos_vector010:	push.l	er0
				mov.b	#10, r0l
				bra		int_handler1:8

_hos_vector011:	push.l	er0
				mov.b	#11, r0l
				bra		int_handler1:8

_hos_vector012:	push.l	er0
				mov.b	#12, r0l
				bra		int_handler1:8

_hos_vector013:	push.l	er0
				mov.b	#13, r0l
				bra		int_handler1:8

_hos_vector014:	push.l	er0
				mov.b	#14, r0l
				bra		int_handler1:8

_hos_vector015:	push.l	er0
				mov.b	#15, r0l
				bra		int_handler1:8

_hos_vector016:	push.l	er0
				mov.b	#16, r0l
				bra		int_handler1:8

_hos_vector017:	push.l	er0
				mov.b	#17, r0l

int_handler1:
				bra		int_handler:16

_hos_vector018:	push.l	er0
				mov.b	#18, r0l
				bra		int_handler1:8

_hos_vector019:	push.l	er0
				mov.b	#19, r0l
				bra		int_handler1:8

_hos_vector020:	push.l	er0
				mov.b	#20, r0l
				bra		int_handler1:8

_hos_vector021:	push.l	er0
				mov.b	#21, r0l
				bra		int_handler1:8

_hos_vector022:	push.l	er0
				mov.b	#22, r0l
				bra		int_handler1:8

_hos_vector023:	push.l	er0
				mov.b	#23, r0l
				bra		int_handler1:8

_hos_vector024:	push.l	er0
				mov.b	#24, r0l
				bra		int_handler1:8

_hos_vector025:	push.l	er0
				mov.b	#25, r0l
				bra		int_handler1:8

_hos_vector026:	push.l	er0
				mov.b	#26, r0l
				bra		int_handler1:8

_hos_vector027:	push.l	er0
				mov.b	#27, r0l
				bra		int_handler1:8

_hos_vector028:	push.l	er0
				mov.b	#28, r0l
				bra		int_handler1:8

_hos_vector029:	push.l	er0
				mov.b	#29, r0l
				bra		int_handler1:8

_hos_vector030:	push.l	er0
				mov.b	#30, r0l
				bra		int_handler1:8

_hos_vector031:	push.l	er0
				mov.b	#31, r0l
				bra		int_handler1:8

_hos_vector032:	push.l	er0
				mov.b	#32, r0l
				bra		int_handler1:8

_hos_vector033:	push.l	er0
				mov.b	#33, r0l
				bra		int_handler2:8

_hos_vector034:	push.l	er0
				mov.b	#34, r0l
				bra		int_handler2:8

_hos_vector035:	push.l	er0
				mov.b	#35, r0l
				bra		int_handler2:8

_hos_vector036:	push.l	er0
				mov.b	#36, r0l
				bra		int_handler2:8

_hos_vector037:	push.l	er0
				mov.b	#37, r0l
				bra		int_handler2:8

_hos_vector038:	push.l	er0
				mov.b	#38, r0l
				bra		int_handler2:8

_hos_vector039:	push.l	er0
				mov.b	#39, r0l
				bra		int_handler2:8

_hos_vector040:	push.l	er0
				mov.b	#40, r0l
				bra		int_handler2:8

_hos_vector041:	push.l	er0
				mov.b	#41, r0l
				bra		int_handler2:8

_hos_vector042:	push.l	er0
				mov.b	#42, r0l
				bra		int_handler2:8

_hos_vector043:	push.l	er0
				mov.b	#43, r0l
				bra		int_handler2:8

_hos_vector044:	push.l	er0
				mov.b	#44, r0l
				bra		int_handler2:8

_hos_vector045:	push.l	er0
				mov.b	#45, r0l
				bra		int_handler2:8

_hos_vector046:	push.l	er0
				mov.b	#46, r0l
				bra		int_handler2:8

_hos_vector047:	push.l	er0
				mov.b	#47, r0l

int_handler2:
				bra		int_handler:8

_hos_vector048:	push.l	er0
				mov.b	#48, r0l
				bra		int_handler:8

_hos_vector049:	push.l	er0
				mov.b	#49, r0l
				bra		int_handler:8

_hos_vector050:	push.l	er0
				mov.b	#50, r0l
				bra		int_handler:8

_hos_vector051:	push.l	er0
				mov.b	#51, r0l
				bra		int_handler:8

_hos_vector052:	push.l	er0
				mov.b	#52, r0l
				bra		int_handler:8

_hos_vector053:	push.l	er0
				mov.b	#53, r0l
				bra		int_handler:8

_hos_vector054:	push.l	er0
				mov.b	#54, r0l
				bra		int_handler:8

_hos_vector055:	push.l	er0
				mov.b	#55, r0l
				bra		int_handler:8

_hos_vector056:	push.l	er0
				mov.b	#56, r0l
				bra		int_handler:8

_hos_vector057:	push.l	er0
				mov.b	#57, r0l
				bra		int_handler:8

_hos_vector058:	push.l	er0
				mov.b	#58, r0l
				bra		int_handler:8

_hos_vector059:	push.l	er0
				mov.b	#59, r0l
				bra		int_handler:8

_hos_vector060:	push.l	er0
				mov.b	#60, r0l
				bra		int_handler:8

_hos_vector061:	push.l	er0
				mov.b	#61, r0l
				bra		int_handler:8

_hos_vector062:	push.l	er0
				mov.b	#62, r0l
				bra		int_handler:8

_hos_vector063:	push.l	er0
				mov.b	#63, r0l


/************************************************
          割り込み処理

  割り込み発生時は er0 を push した後、er0 に
  割り込み番号をセットして、ここにジャンプする
*************************************************/

int_handler:
				/* 割り込み番号のマスク */
				mov.b	#0,r0h
				mov.w	#0,e0
				extu.w	r0

				/* レジスタ保存 */
				push.l	er1
				push.l	er2

				/* 割り込みマスク設定 */
				stc.b	ccr, r1l
				and.b	#0xc0, r1l
				mov.b	r1l, @_kernel_h83_imsk

				/* 多重割り込みの判別 */
				mov.w	@_kernel_int_cnt, r1
				bne		mul_int

		/* ======== 最初の割り込み ======== */
				/* 割り込みネストカウンタ設定 */
				mov.w	#1, r1
				mov.w	r1, @_kernel_int_cnt

				/* スタックポインタの入れ替え */
				mov.l	er7, @_kernel_int_ssp
				mov.l	@_kernel_int_sp, er7

				/* 割り込み処理の開始 */
				push.l	er0
				jsr		@_kernel_sta_int
				pop.l	er0

				/* 割り込みハンドラの処理 */
				jsr		@_kernel_exe_int

				/* スタックポインタ復帰 */
				mov.l	@_kernel_int_ssp, er7

				/* 割り込みネストカウンタクリア */
				xor.w	r1, r1
				mov.w	r1, @_kernel_int_cnt

				/* 割り込みマスク値の復帰 */
				mov.b	@_kernel_h83_ibmsk, r0l
				mov.b	r0l, @_kernel_h83_imsk		/* 割り込みマスク値をベース値に戻す */

				/* タスクコンテキストに移行 */
				jsr		@_kernel_end_int

				/* 復帰後のマスク値を設定 */
				mov.b	@_kernel_h83_ibmsk, r0l		/* ベースマスク値取り出し */
				mov.b	@(12, er7), r1l
				and.b	#0x3f,r1l					/* スタック上のCCRからIとU以外を取り出し */
				or.b	r0l, r1l					/* ベースマスク値を設定 */
				mov.b	r1l, @(12, er7)				/* スタック上のCCRを更新 */

				/* 復帰 */
				pop.l	er2
				pop.l	er1
				pop.l	er0
				rte


		/* ======== 多重割り込み ======== */
mul_int:
				/* 割り込みネストカウンタ加算 */
				inc.w	#1, r1
				mov.w	r1, @_kernel_int_cnt

				/* 割り込みハンドラ呼び出し */
				jsr		@_kernel_exe_int

				/* 割り込みネストカウンタ減算 */
				mov.w	@_kernel_int_cnt, r0
				dec.w	#1, r0
				mov.w	r0, @_kernel_int_cnt

				/* 復帰 */
				pop.l	er2
				pop.l	er1
				pop.l	er0
				rte



				.end


/* -------------------------------------------------------------------------*/
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* -------------------------------------------------------------------------*/
