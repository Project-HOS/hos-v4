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
_HOS_SwiHandler
			; ---- SWI�ֹ��ɤ߽Ф�
				ldr		r13, [lr, #-4]
				bic		r13, r13, #0xff000000

				teq 	r13, #0x10		; �����ͥ륳����� #10 �Ȥ���
				bne 	NoKarnelCall
				
			; ---- a1 �� ���ʤ�����ߵ���
				cmp 	a1, #0
				moveq	r13, #Mode_USR:OR:I_Bit:OR:F_Bit
				movne	r13, #Mode_USR
				msr 	spsr_cf, r13
				subs	pc, lr, #0

NoKarnelCall
				; �����ͥ�ʳ���swi�����Ѥ���ʤ餳���˽�
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



				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Ryuji Fuchikami                                 
; --------------------------------------------------------------------------- 
