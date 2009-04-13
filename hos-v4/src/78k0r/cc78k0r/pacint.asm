;	------------------------------------------------------------------------
;		Hyper Operating System V4  ��ITRON4.0���� Real-Time OS
;			�ץ��å���ݲ�����ݡ��ͥ�� (78K0R������)
;
;									Copyright (C) 1998-2009 by Project HOS
;									http://sourceforge.jp/projects/hos/
;	------------------------------------------------------------------------
;		$PROCESSOR	(f1166a0)			; ra78k0r ��ư���ץ����ǻ���

		$INCLUDE	(78k0rregs.inc)		; ��٥�����ȥޥ������
		$INCLUDE	(78k0r/vectasm.inc)	; ����ߥ٥����ֹ����

		DSEG
		EXTRN		_kernel_int_sp
		EXTRN		_kernel_int_cnt
		EXTRN		_kernel_int_ssp

		DSEG	SADDR
		PUBLIC		intno
intno:	DW			(1)
;	************************************************************************
;		����ߥϥ�ɥ�
;		__interrupt void int_handler( void )
;		saddr intno�˳�����ֹ������Ƥ��δؿ���ƤӽФ�����
;		������ֹ�� include/78k0r/vectasm.inc �� vect.h �ˤ������Ʊ���
;	************************************************************************
		CSEG	BASE
		EXTRN		_kernel_sta_int
		EXTRN		_kernel_exe_int
		EXTRN		_kernel_end_int

		PUBLIC		_int_handler
_int_handler:
	; �쥸��������
		push	ax
	; ¿�ų���ߤ�Ƚ��
		movw	ax, !_kernel_int_cnt
		cmpw	ax, #0000H
		bnz		$_mul_int
		nop
	; �����ߥͥ��ȥ����󥿲û�
		incw	!_kernel_int_cnt
	; �����å�������Ⱥ����
		movw	ax, sp
		movw	!_kernel_int_ssp, ax
		movw	ax, !_kernel_int_sp
		movw	sp, ax
	; �����߳��Ͻ����ƤӽФ�
		call	!!_kernel_sta_int
	; �����ߥϥ�ɥ�ƤӽФ�
		movw	ax, intno
		call	!!_kernel_exe_int
	; �����å�������
		movw	ax, !_kernel_int_ssp
		movw	sp, ax
	; �����ߥͥ��ȥ����󥿥��ꥢ
		decw	!_kernel_int_cnt
	; �����߽�λ�����ƤӽФ�
		call	!!_kernel_end_int
	; �쥸��������
		pop		ax
		reti
	; ======== ¿�ų����� ========
_mul_int:
	; �����ߥͥ��ȥ����󥿲û�
		incw	!_kernel_int_cnt
	; �����ߥϥ�ɥ�ƤӽФ�
		movw	ax, intno
		call	!!_kernel_exe_int
	; �����ߥͥ��ȥ����󥿸���
		decw	!_kernel_int_cnt
	; �쥸��������
		pop		ax
		reti

		END
;	------------------------------------------------------------------------
;		Copyright (C) 1998-2009 by Project HOS
;	------------------------------------------------------------------------
