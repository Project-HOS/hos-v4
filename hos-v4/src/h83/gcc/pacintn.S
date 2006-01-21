/* -------------------------------------------------------------------------*/
/*  Hyper Operating System V4                                               */
/*    割り込みハンドラ  Hitachi H8/300H 用                                  */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)
					.h8300hn
#else
					.h8300h
#endif

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


/************************************************
  割り込みハンドラ
*************************************************/
_hos_vector001:	push.w	r0
				mov.b	#1, r0l
				bra		int_handler1:8

_hos_vector002:	push.w	r0
				mov.b	#2, r0l
				bra		int_handler1:8

_hos_vector003:	push.w	r0
				mov.b	#3, r0l
				bra		int_handler1:8

_hos_vector004:	push.w	r0
				mov.b	#4, r0l

int_handler1:
				bra		int_handler:8

_hos_vector005:	push.w	r0
				mov.b	#5, r0l
				bra		int_handler:8

_hos_vector006:	push.w	r0
				mov.b	#6, r0l
				bra		int_handler:8

_hos_vector007:	push.w	r0
				mov.b	#7, r0l
				bra		int_handler:8

_hos_vector008:	push.w	r0
				mov.b	#8, r0l
				bra		int_handler:8

_hos_vector009:	push.w	r0
				mov.b	#9, r0l
				bra		int_handler:8

_hos_vector010:	push.w	r0
				mov.b	#10, r0l
				bra		int_handler:8

_hos_vector011:	push.w	r0
				mov.b	#11, r0l
				bra		int_handler:8

_hos_vector012:	push.w	r0
				mov.b	#12, r0l
				bra		int_handler:8

_hos_vector013:	push.w	r0
				mov.b	#13, r0l
				bra		int_handler:8

_hos_vector014:	push.w	r0
				mov.b	#14, r0l
				bra		int_handler:8

_hos_vector015:	push.w	r0
				mov.b	#15, r0l
				bra		int_handler:8

_hos_vector016:	push.w	r0
				mov.b	#16, r0l
				bra		int_handler:8

_hos_vector017:	push.w	r0
				mov.b	#17, r0l
				bra		int_handler:8

_hos_vector018:	push.w	r0
				mov.b	#18, r0l
				bra		int_handler:8

_hos_vector019:	push.w	r0
				mov.b	#19, r0l
				bra		int_handler:8

_hos_vector020:	push.w	r0
				mov.b	#20, r0l
				bra		int_handler:8

_hos_vector021:	push.w	r0
				mov.b	#21, r0l
				bra		int_handler:8

_hos_vector022:	push.w	r0
				mov.b	#22, r0l
				bra		int_handler:8

_hos_vector023:	push.w	r0
				mov.b	#23, r0l
				bra		int_handler:8

_hos_vector024:	push.w	r0
				mov.b	#24, r0l
				bra		int_handler

_hos_vector025:	push.w	r0
				mov.b	#25, r0l


/************************************************
          割り込み処理

  割り込み発生時は r0 を push した後、r0l に
  割り込み番号をセットして、ここにジャンプする
*************************************************/

int_handler:
				/* レジスタ保存 */
				push.w	e0
				push.l	er1
				push.l	er2
				push.l	er3

				/* 割り込み番号のマスク */
				extu.w	r0

				/* 割り込みマスク設定 */
				stc.b	ccr, r1l
				and.b	#0xc0, r1l
				mov.b	r1l, @_kernel_h83_imsk:16

				/* 多重割り込みの判別 */
				mov.w	@_kernel_int_cnt:16, r1
				bne		mul_int

		/* ======== 最初の割り込み ======== */
				/* 割り込みネストカウンタ設定 */
				mov.w	#1, r1
				mov.w	r1, @_kernel_int_cnt:16

				/* スタックポインタの入れ替え */
				mov.w	r7, @_kernel_int_ssp:16
				mov.w	@_kernel_int_sp:16, r7

				/* 割り込み処理の開始 */
				push.w	r0
				jsr		@_kernel_sta_int:16
				pop.w	r0

				/* 割り込みハンドラの処理 */
				jsr		@_kernel_exe_int:16

				/* スタックポインタ復帰 */
				mov.w	@_kernel_int_ssp:16, r7

				/* 割り込みネストカウンタクリア */
				xor.w	r1, r1
				mov.w	r1, @_kernel_int_cnt:16

				/* 割り込みマスク値の復帰 */
				mov.b	@_kernel_h83_ibmsk:16, r0l
				mov.b	r0l, @_kernel_h83_imsk:16		/* 割り込みマスク値をベース値に戻す */

				/* タスクコンテキストに移行 */
				jsr		@_kernel_end_int:16

				/* 復帰後のマスク値を設定 */
				mov.b	@_kernel_h83_ibmsk:16, r0l		/* ベースマスク値取り出し */
				mov.b	@(16:16, er7), r1l
				and.b	#0x3f,r1l					/* スタック上のCCRからIとU以外を取り出し */
				or.b	r0l, r1l					/* ベースマスク値を設定 */
				mov.b	r1l, @(16:16, er7)				/* スタック上のCCRを更新 */

				/* 復帰 */
				pop.l	er3
				pop.l	er2
				pop.l	er1
				pop.w	e0
				pop.w	r0
				rte


		/* ======== 多重割り込み ======== */
mul_int:
				/* 割り込みネストカウンタ加算 */
				inc.w	#1, r1
				mov.w	r1, @_kernel_int_cnt:16

				/* 割り込みハンドラ呼び出し */
				jsr		@_kernel_exe_int:16

				/* 割り込みネストカウンタ減算 */
				mov.w	@_kernel_int_cnt:16, r0
				dec.w	#1, r0
				mov.w	r0, @_kernel_int_cnt:16

				/* 復帰 */
				pop.l	er3
				pop.l	er2
				pop.l	er1
				pop.w	e0
				pop.w	r0
				rte

				.end


/* -------------------------------------------------------------------------*/
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* -------------------------------------------------------------------------*/
