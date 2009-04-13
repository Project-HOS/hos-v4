;	------------------------------------------------------------------------
;		Hyper Operating System V4  ��ITRON4.0���� Real-Time OS
;			�ץ��å���ݲ�����ݡ��ͥ�� (78K0R������)
;
;									Copyright (C) 1998-2009 by Project HOS
;									http://sourceforge.jp/projects/hos/
;	------------------------------------------------------------------------
;		$PROCESSOR	(f1166a0)			; ra78k0r ��ư���ץ����ǻ���
		$INCLUDE	(78k0rregs.inc)		; ��٥�����ȥޥ������
;	************************************************************************
;		�¹ԥ���ƥ����Ȥκ���
;		void hospac_cre_ctx_asm(
;			T_HOSPAC_CTXINF	*pk_ctxinf,	; �������륳��ƥ�����	ax		(2)
;			VP_INT			exinf,		; �¹Ի��ѥ�᡼��		[sp+4]	(4)
;			FP				task,		; task��ư����			[sp+8]	(4)
;			VP				stkp)		; �����å��ݥ���		[sp+12]	(2)
;	************************************************************************
		CSEG	BASE
		PUBLIC	_hospac_cre_ctx_asm
_hospac_cre_ctx_asm:
		push	hl
		push	de
		push	ax

		movw	de, ax					; pk_ctxinf
		movw	ax, [sp+12+6]			; stkp
		subw	ax, #pt_size
		movw	hl, ax
	; �����å��ݥ��󥿤���¸�������
	;	movw	[hl+pt_sp], ax
	; ES, CS �쥸�����ξ�����¸
		mov		a, cs
		xch		a, x
		mov		a, es
		movw	[hl+pt_es], ax			; CS, ES �쥸����������
	; �¹Ի��Υѥ�᡼����¸
$IF (__USE_RB__)
		mov		a, psw
		and		a, #10000000B
		clrb	x
		movw	[hl+pt_psw], ax
		movw	ax, [sp+4+6]
		movw	[hl+pt_ax0], ax			; �¹Ի��Υѥ�᡼����¸ (RBS=0����)
		movw	ax, [sp+6+6]
		movw	[hl+pt_bc0], ax			; �¹Ի��Υѥ�᡼����¸ (RBS=0����)
$ELSE
		movw	ax, [sp+4+6]
		movw	[hl+pt_ax], ax			; �¹Ի��Υѥ�᡼����¸
		movw	ax, [sp+6+6]
		movw	[hl+pt_bc], ax			; �¹Ի��Υѥ�᡼����¸
$ENDIF
	; task��ư������¸
		movw	ax, [sp+8+6]
		movw	[hl+pt_adrs], ax
		mov		a, [sp+10+6]
		mov		[hl+(pt_adrs+2)], a
	; ����ƥ�������¸
		movw	ax, hl
		movw	[de], ax

		pop		ax
		pop		de
		pop		hl
		ret								; �ƤӽФ��������
		nop
;	************************************************************************
;		�¹ԥ���ƥ����Ȥ�����
;		void hospac_swi_ctx(
;			T_HOSPAC_CTXINF *pk_pre_ctxinf, ����ƥ����Ȥ���¸��	ax
;			T_HOSPAC_CTXINF *pk_nxt_ctxinf) �ڤ��ؤ��륳��ƥ�����	[sp+4]
;	************************************************************************
		DSEG	SADDRP
prectx:	DW		(1)						; ���ߤΥ���ƥ����Ȥ���¸��
nxtctx:	DW		(1)						; �ڤ��ؤ��륳��ƥ�����
		CSEG	BASE
		PUBLIC	_hospac_swi_ctx
_hospac_swi_ctx:
		movw	prectx, ax
		movw	ax, [sp+4]
		movw	nxtctx, ax
		movw	ax, prectx				; ���פ��ʡ�
		pushall							; ���쥸��������
		movw	hl, prectx
		movw	ax, sp
		movw	[hl], ax				; sp�쥸����������ΰ������
		movw	hl, nxtctx
		movw	ax, [hl]
		movw	sp, ax					; �����ΰ褫�� sp�쥸����������
		popall							; ���쥸��������
		ret								; ����ƥ����Ȥإ�����
		nop

		END
;	------------------------------------------------------------------------
;		Copyright (C) 1998-2009 by Project HOS
;	------------------------------------------------------------------------
