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
				mov.l	#1, er0
				bra		int_handler:16

_hos_vector002:	push.l	er0
				mov.l	#2, er0
				bra		int_handler:16

_hos_vector003:	push.l	er0
				mov.l	#3, er0
				bra		int_handler:16

_hos_vector004:	push.l	er0
				mov.l	#4, er0
				bra		int_handler:16

_hos_vector005:	push.l	er0
				mov.l	#5, er0
				bra		int_handler:16

_hos_vector006:	push.l	er0
				mov.l	#6, er0
				bra		int_handler:16

_hos_vector007:	push.l	er0
				mov.l	#7, er0
				bra		int_handler:16

_hos_vector008:	push.l	er0
				mov.l	#8, er0
				bra		int_handler:16

_hos_vector009:	push.l	er0
				mov.l	#9, er0
				bra		int_handler:16

_hos_vector010:	push.l	er0
				mov.l	#10, er0
				bra		int_handler:16

_hos_vector011:	push.l	er0
				mov.l	#11, er0
				bra		int_handler:16

_hos_vector012:	push.l	er0
				mov.l	#12, er0
				bra		int_handler:16

_hos_vector013:	push.l	er0
				mov.l	#13, er0
				bra		int_handler:16

_hos_vector014:	push.l	er0
				mov.l	#14, er0
				bra		int_handler:16

_hos_vector015:	push.l	er0
				mov.l	#15, er0
				bra		int_handler:16

_hos_vector016:	push.l	er0
				mov.l	#16, er0
				bra		int_handler:16

_hos_vector017:	push.l	er0
				mov.l	#17, er0
				bra		int_handler:16

_hos_vector018:	push.l	er0
				mov.l	#18, er0
				bra		int_handler:16

_hos_vector019:	push.l	er0
				mov.l	#19, er0
				bra		int_handler:16

_hos_vector020:	push.l	er0
				mov.l	#20, er0
				bra		int_handler:16

_hos_vector021:	push.l	er0
				mov.l	#21, er0
				bra		int_handler:16

_hos_vector022:	push.l	er0
				mov.l	#22, er0
				bra		int_handler:16

_hos_vector023:	push.l	er0
				mov.l	#23, er0
				bra		int_handler:16

_hos_vector024:	push.l	er0
				mov.l	#24, er0
				bra		int_handler:16

_hos_vector025:	push.l	er0
				mov.l	#25, er0
				bra		int_handler:16

_hos_vector026:	push.l	er0
				mov.l	#26, er0
				bra		int_handler:16

_hos_vector027:	push.l	er0
				mov.l	#27, er0
				bra		int_handler:16

_hos_vector028:	push.l	er0
				mov.l	#28, er0
				bra		int_handler:16

_hos_vector029:	push.l	er0
				mov.l	#29, er0
				bra		int_handler:16

_hos_vector030:	push.l	er0
				mov.l	#30, er0
				bra		int_handler:16

_hos_vector031:	push.l	er0
				mov.l	#31, er0
				bra		int_handler:16

_hos_vector032:	push.l	er0
				mov.l	#32, er0
				bra		int_handler:16

_hos_vector033:	push.l	er0
				mov.l	#33, er0
				bra		int_handler:16

_hos_vector034:	push.l	er0
				mov.l	#34, er0
				bra		int_handler:16

_hos_vector035:	push.l	er0
				mov.l	#35, er0
				bra		int_handler:16

_hos_vector036:	push.l	er0
				mov.l	#36, er0
				bra		int_handler:16

_hos_vector037:	push.l	er0
				mov.l	#37, er0
				bra		int_handler:16

_hos_vector038:	push.l	er0
				mov.l	#38, er0
				bra		int_handler:16

_hos_vector039:	push.l	er0
				mov.l	#39, er0
				bra		int_handler:16

_hos_vector040:	push.l	er0
				mov.l	#40, er0
				bra		int_handler:16

_hos_vector041:	push.l	er0
				mov.l	#41, er0
				bra		int_handler:16

_hos_vector042:	push.l	er0
				mov.l	#42, er0
				bra		int_handler:16

_hos_vector043:	push.l	er0
				mov.l	#43, er0
				bra		int_handler:16

_hos_vector044:	push.l	er0
				mov.l	#44, er0
				bra		int_handler:16

_hos_vector045:	push.l	er0
				mov.l	#45, er0
				bra		int_handler:16

_hos_vector046:	push.l	er0
				mov.l	#46, er0
				bra		int_handler:16

_hos_vector047:	push.l	er0
				mov.l	#47, er0
				bra		int_handler:16

_hos_vector048:	push.l	er0
				mov.l	#48, er0
				bra		int_handler:16

_hos_vector049:	push.l	er0
				mov.l	#49, er0
				bra		int_handler:16

_hos_vector050:	push.l	er0
				mov.l	#50, er0
				bra		int_handler:16

_hos_vector051:	push.l	er0
				mov.l	#51, er0
				bra		int_handler:16

_hos_vector052:	push.l	er0
				mov.l	#52, er0
				bra		int_handler:16

_hos_vector053:	push.l	er0
				mov.l	#53, er0
				bra		int_handler

_hos_vector054:	push.l	er0
				mov.l	#54, er0
				bra		int_handler

_hos_vector055:	push.l	er0
				mov.l	#55, er0
				bra		int_handler

_hos_vector056:	push.l	er0
				mov.l	#56, er0
				bra		int_handler

_hos_vector057:	push.l	er0
				mov.l	#57, er0
				bra		int_handler

_hos_vector058:	push.l	er0
				mov.l	#58, er0
				bra		int_handler

_hos_vector059:	push.l	er0
				mov.l	#59, er0
				bra		int_handler

_hos_vector060:	push.l	er0
				mov.l	#60, er0
				bra		int_handler

_hos_vector061:	push.l	er0
				mov.l	#61, er0
				bra		int_handler

_hos_vector062:	push.l	er0
				mov.l	#62, er0
				bra		int_handler

_hos_vector063:	push.l	er0
				mov.l	#63, er0
				bra		 int_handler



/************************************************
          割り込み処理

  割り込み発生時は er0 を push した後、er0 に
  割り込み番号をセットして、ここにジャンプする
*************************************************/

int_handler:
				/* レジスタ保存 */
				push.l	er1
				push.l	er2
				
				/* 割り込みマスク設定 */
				stc.b	ccr, r1l
				and.b	#0xc0, r1l
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
				mov.l	@_kernel_int_sp, er7

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
				mov.w	r1, @__HOS_int_cnt
				
				/* 割り込みハンドラ呼び出し */
				mov.l	er2, er0			/* 割り込み番号を引数とする */
				jsr		@_kernel_exe_int
				
				/* 割り込みネストカウンタ減算 */
				mov.w	@__HOS_int_cnt, r0
				dec.w	#1, r0
				mov.w	r0, @__HOS_int_cnt
				
				/* 復帰 */
				pop.l	er2
				pop.l	er1
				pop.l	er0
				rte



/************************************************
       割り込み処理データ
*************************************************/
		.comm __HOS_int_sp,4		/* 割り込み時の er7 保存用 */
		.comm __HOS_int_cnt,2		/* 割り込みネストカウンタ */


				.end


/* -------------------------------------------------------------------------*/
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* -------------------------------------------------------------------------*/
