/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (日立 SH4用)                           */
/*    割り込みハンドラ                                                      */
/*                                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


		.global	__exception_handler
/* 一般例外ハンドラ */
		.text
		.align	2
__exception_handler:
	mov.l	expevt_adr,r4
	stc	spc,r5
	stc	ssr,r6
	mov.l	exception_hdr_adr,r0
	jsr	@r0
	mov.l	@r4,r4

		.align	2
expevt_adr:
	.long	0xff000024		/* 一般例外レジスタ     */
exception_hdr_adr:
	.long	_exception_hdr


/* TLBミス例外ハンドラ */
		.text
		.org	__exception_handler+0x300
__tbl_mis_handler:
	bra	__exception_handler
	nop


/* 割り込み例外ハンドラ */
		.text
		.org	__exception_handler+0x500
__interrupt_handler:
	stc.l	ssr,@-r15
	stc.l	spc,@-r15
	mov.l	r4,@-r15

	/* 割り込み番号 = ( 割り込み事象レジスタ >> 5 ) - 16 */
	mov.l	intevt_adr,r4
	mov.l	@r4,r4
	shlr2	r4
	shlr2	r4
	shlr	r4
	add	#-16,r4

	/* レジスタ退避(r0-r1) */
	mov.l	r0,@-r15
	mov.l	r1,@-r15

	/* 当該割り込みのマスクを保存 */
	mov.l	int_pri_tbl_adr,r0
	mov.b	@(r0,r4),r0
	shll2	r0
	shll2	r0
	mov.l	imsk_addr,r1
	mov.l	r0,@r1

	/* レジスタ保存(r2-r7,mach,macl,pr) */
	mov.l	r2,@-r15
	mov.l	r3,@-r15
	mov.l	r5,@-r15
	mov.l	r6,@-r15
	mov.l	r7,@-r15
	sts.l	mach,@-r15
	sts.l	macl,@-r15
	sts.l	pr,@-r15

	/* 多重割り込み判定 */
	mov.l	int_cnt_addr,r1
	mov.l	@r1,r0
	cmp/eq	#0,r0
	bf/s	int_multi
	add	#1,r0

	/* 単独割り込み時 */
	mov.l	r0,@r1				/* 割り込みネスト値を設定 */

	/* スタック入れ替え */
	mov.l	save_sp_addr,r0
	mov.l	r15,@r0			/* 現在のスタックを退避 */
	mov.l	int_sp_addr,r0
	mov.l	@r0,r15			/* 割り込み用スタックを設定 */

	mov.l	r4,@-r15			/* 割り込み番号を退避 */

	/* 割り込み開始処理呼び出し */
	mov.l	sta_int_addr,r1
	jsr	@r1
	nop

	/* 割り込み実行処理呼び出し */
	mov.l	exe_int_addr,r1
	jsr	@r1
	mov.l	@r15+,r4			/* 割り込み番号を引数とする */

	/* スタックの復帰 */
	mov.l	save_sp_addr,r0
	mov.l	@r0,r15

	/* 割り込みカウンタのクリア */
	mov.l	int_cnt_addr,r1
	xor	r0,r0
	mov.l	r0,@r1

	/* ベースマスク値に戻す */
	mov.l	imsk_base_addr,r0
	mov.l	@r0,r1
	mov.l	imsk_addr,r0
	mov.l	r1,@r0

	/* 割り込み終了処理呼び出し */
	mov.l	end_int_addr,r1
	jsr	@r1
	nop

	/* レジスタ復帰 */
	lds.l	@r15+,pr
	lds.l	@r15+,macl
	lds.l	@r15+,mach
	mov.l	@r15+,r7
	mov.l	@r15+,r6
	mov.l	@r15+,r5
	mov.l	@r15+,r3
	mov.l	@r15+,r2
	mov.l	@r15+,r1
	mov.l	@r15+,r0
	mov.l	@r15+,r4
	ldc.l	@r15+,spc
	ldc.l	@r15+,ssr
	rte
	nop

	/* 多重割り込み処理 */
int_multi:
	mov.l	r0,@r1				/* 割り込みネスト値を設定 */

	/* 割り込み実行処理呼び出し */
	mov.l	exe_int_addr,r1
	jsr	@r1				/* 割り込み番号を引数とする */
	nop

	/* 割り込みカウンタの減算 */
	mov.l	int_cnt_addr,r1
	mov.l	@r1,r0
	add	#-1,r0
	mov.l	r0,@r1

	/* レジスタ復帰 */
	lds.l	@r15+,pr
	lds.l	@r15+,macl
	lds.l	@r15+,mach
	mov.l	@r15+,r7
	mov.l	@r15+,r6
	mov.l	@r15+,r5
	mov.l	@r15+,r3
	mov.l	@r15+,r2
	mov.l	@r15+,r1
	mov.l	@r15+,r0
	mov.l	@r15+,r4
	ldc.l	@r15+,spc
	ldc.l	@r15+,ssr
	rte
	nop


	.align	2
imsk_addr:
	.long	_hospac_sh_imsk		/* 割り込みマスク */
imsk_base_addr:
	.long	_hospac_sh_imsk_base	/* 割り込みマスクベース値 */
int_cnt_addr:
	.long	_kernel_int_cnt		/* 割り込みネスト回数 */
save_sp_addr:
	.long	_kernel_int_ssp		/* 割り込み用スタックポインタ退避 */
int_sp_addr:
	.long	_kernel_int_sp		/* 割り込み用スタックポインタ */
sta_int_addr:
	.long	_kernel_sta_int		/* 割り込み開始処理 */
end_int_addr:
	.long	_kernel_end_int		/* 割り込み終了処理 */
exe_int_addr:
	.long	_kernel_exe_int		/* 割り込み実行処理 */
int_pri_tbl_adr:
	.long	_int_pri_tbl		/* UB int_pri_tbl[] */
					/* 割り込み優先順位のテーブル */
intevt_adr:
	.long	0xff000028		/* 割り込み事象レジスタ */

	.end



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
