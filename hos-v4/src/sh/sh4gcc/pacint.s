/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ��å���ݲ�����ݡ��ͥ�� (��Ω SH4��)                           */
/*    �����ߥϥ�ɥ�                                                      */
/*                                                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


		.global	__exception_handler
/* �����㳰�ϥ�ɥ� */
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
	.long	0xff000024		/* �����㳰�쥸����     */
exception_hdr_adr:
	.long	_exception_hdr


/* TLB�ߥ��㳰�ϥ�ɥ� */
		.text
		.org	__exception_handler+0x300
__tbl_mis_handler:
	bra	__exception_handler
	nop


/* �������㳰�ϥ�ɥ� */
		.text
		.org	__exception_handler+0x500
__interrupt_handler:
	stc.l	ssr,@-r15
	stc.l	spc,@-r15
	mov.l	r4,@-r15

	/* �������ֹ� = ( �����߻��ݥ쥸���� >> 5 ) - 16 */
	mov.l	intevt_adr,r4
	mov.l	@r4,r4
	shlr2	r4
	shlr2	r4
	shlr	r4
	add	#-16,r4

	/* �쥸��������(r0-r1) */
	mov.l	r0,@-r15
	mov.l	r1,@-r15

	/* ���������ߤΥޥ�������¸ */
	mov.l	int_pri_tbl_adr,r0
	mov.b	@(r0,r4),r0
	shll2	r0
	shll2	r0
	mov.l	imsk_addr,r1
	mov.l	r0,@r1

	/* �쥸������¸(r2-r7,mach,macl,pr) */
	mov.l	r2,@-r15
	mov.l	r3,@-r15
	mov.l	r5,@-r15
	mov.l	r6,@-r15
	mov.l	r7,@-r15
	sts.l	mach,@-r15
	sts.l	macl,@-r15
	sts.l	pr,@-r15

	/* ¿�ų�����Ƚ�� */
	mov.l	int_cnt_addr,r1
	mov.l	@r1,r0
	cmp/eq	#0,r0
	bf/s	int_multi
	add	#1,r0

	/* ñ�ȳ����߻� */
	mov.l	r0,@r1				/* �����ߥͥ����ͤ����� */

	/* �����å������ؤ� */
	mov.l	save_sp_addr,r0
	mov.l	r15,@r0			/* ���ߤΥ����å������� */
	mov.l	int_sp_addr,r0
	mov.l	@r0,r15			/* �������ѥ����å������� */

	mov.l	r4,@-r15			/* �������ֹ������ */

	/* �����߳��Ͻ����ƤӽФ� */
	mov.l	sta_int_addr,r1
	jsr	@r1
	nop

	/* �����߼¹Խ����ƤӽФ� */
	mov.l	exe_int_addr,r1
	jsr	@r1
	mov.l	@r15+,r4			/* �������ֹ������Ȥ��� */

	/* �����å������� */
	mov.l	save_sp_addr,r0
	mov.l	@r0,r15

	/* �����ߥ����󥿤Υ��ꥢ */
	mov.l	int_cnt_addr,r1
	xor	r0,r0
	mov.l	r0,@r1

	/* �١����ޥ����ͤ��᤹ */
	mov.l	imsk_base_addr,r0
	mov.l	@r0,r1
	mov.l	imsk_addr,r0
	mov.l	r1,@r0

	/* �����߽�λ�����ƤӽФ� */
	mov.l	end_int_addr,r1
	jsr	@r1
	nop

	/* �쥸�������� */
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

	/* ¿�ų����߽��� */
int_multi:
	mov.l	r0,@r1				/* �����ߥͥ����ͤ����� */

	/* �����߼¹Խ����ƤӽФ� */
	mov.l	exe_int_addr,r1
	jsr	@r1				/* �������ֹ������Ȥ��� */
	nop

	/* �����ߥ����󥿤θ��� */
	mov.l	int_cnt_addr,r1
	mov.l	@r1,r0
	add	#-1,r0
	mov.l	r0,@r1

	/* �쥸�������� */
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
	.long	_hospac_sh_imsk		/* �����ߥޥ��� */
imsk_base_addr:
	.long	_hospac_sh_imsk_base	/* �����ߥޥ����١����� */
int_cnt_addr:
	.long	_kernel_int_cnt		/* �����ߥͥ��Ȳ�� */
save_sp_addr:
	.long	_kernel_int_ssp		/* �������ѥ����å��ݥ������� */
int_sp_addr:
	.long	_kernel_int_sp		/* �������ѥ����å��ݥ��� */
sta_int_addr:
	.long	_kernel_sta_int		/* �����߳��Ͻ��� */
end_int_addr:
	.long	_kernel_end_int		/* �����߽�λ���� */
exe_int_addr:
	.long	_kernel_exe_int		/* �����߼¹Խ��� */
int_pri_tbl_adr:
	.long	_int_pri_tbl		/* UB int_pri_tbl[] */
					/* ������ͥ���̤Υơ��֥� */
intevt_adr:
	.long	0xff000028		/* �����߻��ݥ쥸���� */

	.end



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
