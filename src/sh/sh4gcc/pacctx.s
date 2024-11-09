/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                  */
/*    プロセッサ抽象化コンポーネント (日立 SH4用)                           */
/*                                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


		.global	_hospac_dis_int		/* 割り込み禁止 */
		.global	_hospac_ena_int		/* 割り込み許可 */
		.global	_hospac_cre_ctx_asm	/* 実行コンテキストの作成 */
		.global	_hospac_swi_ctx		/* 実行コンテキストの切替 */



/************************************************
  割り込み禁止
  void hospac_dis_int(void)
************************************************/
		.text
		.align	2
_hospac_dis_int:
	mov.l	bl_set_mask,r1
	stc	sr,r0
	or	r1,r0		/* 全割り込みマスク */
	ldc		r0,sr
	rts
	nop

bl_set_mask:
	.long	0x10000000

/************************************************
  割り込み許可
  void hospac_ena_int(void)
************************************************/
		.text
		.align	2
_hospac_ena_int:
	stc	sr,r0
	mov.l	bl_imsk_clr_mask,r1
	and	r1,r0			/* 割り込みマスク値以外を取得 */
	mov.l	imsk_addr,r1
	mov.l	@r1,r1
	or	r1,r0			/* 割り込みマスクの値を設定 */
	ldc	r0,sr
	rts
	nop

		.align	2
bl_imsk_clr_mask:
	.long	0xefffff0f
imsk_addr:
	.long	_hospac_sh_imsk			/* 割り込みマスク */

/************************************************
  実行コンテキストエントリーアドレス
************************************************/
		.text
		.align 2
ctx_entry:	 	
	jmp	@r14			/* 実行アドレスにジャンプ */
	mov	r13,r4			/* 実行時パラメータを第一引数に設定 */


/************************************************
  実行コンテキストの作成
  void hospac_cre_ctx_asm(
 T_HOSPAC_CTXINF *pk_ctxinf,	作成するコンテキスト
 VP 	sp,					スタックポインタ
 void	(*task)(VP_INT),		実行アドレス
 VP_INT exinf)					実行時パラメータ
************************************************/
		.text
		.align 2
_hospac_cre_ctx_asm:
	add 	#-20,r5		/* r14-10分コンテキストのstackを伸ばす */
	mov.l	r7,@-r5			/* 実行パラメータの格納(r9) */
	mov.l	r6,@-r5			/* 実行アドレスの格納(r8) */
	mov.l	ctx_entry_addr,r0	/* 実行エントリポイントを */
					/* コンテキストのスタックに保存 */
	mov.l	r0,@-r5	
	rts
	mov.l	r5,@(0,r4) 	/* コンテキストのスタックポインタ保存 */

		.align	2
ctx_entry_addr:
	.long	ctx_entry



/************************************************
  実行コンテキストの切替
  void hospac_swi_ctx(
T_HOSPAC_CTXINF *pk_pre_ctxinf,	現在のコンテキストの保存先
T_HOSPAC_CTXINF *pk_nxt_ctxinf)	切り替えるコンテキスト
************************************************/
		.text
		.align 2
_hospac_swi_ctx:
	mov.l	 r8,@-r15		/* 8-r14,prを退避 */
	mov.l	 r9,@-r15
	mov.l	 r10,@-r15
	mov.l	 r11,@-r15
	mov.l	 r12,@-r15
	mov.l	 r13,@-r15
	mov.l	 r14,@-r15
	sts.l	 pr,@-r15

	mov.l	 r15,@(0,r4)	/* スタックポインタ保存 */
	mov.l	 @(0,r5),r15	/* スタックポインタ復帰 */

	lds.l	 @r15+,pr		/* r8-r14,prを復帰 */
	mov.l	 @r15+,r14
	mov.l	 @r15+,r13
	mov.l	 @r15+,r12
	mov.l	 @r15+,r11
	mov.l	 @r15+,r10
	mov.l	 @r15+,r9
	rts
	mov.l	 @r15+,r8

	.end


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
