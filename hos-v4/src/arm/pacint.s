; ---------------------------------------------------------------------------
;  HOS-V4                                                                    
;    �㳰�ϥ�ɥ�                                                            
;                                                                            
;                                 Copyright (C) 1998-2002 by Ryuji Fuchikami 
; ---------------------------------------------------------------------------


; ������
Mode_USR		EQU 	0x10
Mode_IRQ		EQU 	0x12

I_Bit			EQU 	0x80
F_Bit			EQU 	0x40


				AREA	inthdr_code, CODE, READONLY

				EXPORT	_HOS_UndefinedHandler
				EXPORT  _HOS_SwiHandler
				EXPORT	_HOS_PrefetchHandler
				EXPORT	_HOS_AbortHandler


; ----------------------------------------------
;  Undefined �ϥ�ɥ�
; ----------------------------------------------
_HOS_UndefinedHandler
				b		_HOS_UndefinedHandler



; ----------------------------------------------
;  SWI �ϥ�ɥ�
; ----------------------------------------------
				IMPORT	hospac_arm_imsk
_HOS_SwiHandler
			; ---- SWI�ֹ��ɤ߽Ф�
				ldr		r13, [lr, #-4]
				bic		r13, r13, #0xff000000

				teq 	r13, #0x10		; �����ͥ륳����� #10 �Ȥ���
				bne 	swi_ret

			; ---- �ѥ�᡼������Ƚ��
				cmp		a1, #3
				and		a1, a1, #0x03
				addls	pc, pc, a1, lsl #2
				b		swi_ret
				b		swi_dis_int
				b		swi_ena_int

			; ---- IRQ/FIQ��������� (a1 = 2)
				ldr		r13, =_HOS_swi_ret
				ldmia	r13, {a1, r13, lr}
				msr		spsr_csxf, r13
				subs	pc, lr, #0

			; ---- �����߶ػ�(a1 = 0)
swi_dis_int
				mov		r13, #Mode_USR:OR:I_Bit:OR:F_Bit
				msr 	spsr_cf, r13
				subs	pc, lr, #0

			; ---- �����ߵ���(a1 = 1)
swi_ena_int
				ldr		r13, =hospac_arm_imsk
				ldr		r13, [r13]
				msr 	spsr_cf, r13

swi_ret
			; ---- ���褳�����㳰�������� 
				subs	pc, lr, #0


; ----------------------------------------------
;  SWI �ϥ�ɥ�
; ----------------------------------------------
_HOS_PrefetchHandler
				b		_HOS_PrefetchHandler



; ----------------------------------------------
;  Abort �ϥ�ɥ�
; ----------------------------------------------
_HOS_AbortHandler
				b		_HOS_AbortHandler



; ----------------------------------------------
;  �����Х��ѿ�
; ----------------------------------------------
				AREA	inthdr_bss, NOINIT

				EXPORT	_HOS_int_cnt
				EXPORT	_HOS_int_sp
				EXPORT	_HOS_swi_ret
_HOS_int_cnt	%		4		; �����ߥͥ��Ȳ��
_HOS_int_sp		%		4		; �����߻������å�����
_HOS_swi_ret	%		12		; a1, cpsr, lr �����Ϥ���


				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Ryuji Fuchikami                                 
; --------------------------------------------------------------------------- 
