; ---------------------------------------------------------------------------
;  HOS-V4                                                                    
;    �㳰�ϥ�ɥ�                                                            
;                                                                            
;                                 Copyright (C) 1998-2002 by Ryuji Fuchikami 
; ---------------------------------------------------------------------------


; ������
Mode_USR		EQU 	0x10
Mode_IRQ		EQU 	0x12
Mode_SYS		EQU 	0x1f

I_Bit			EQU 	0x80
F_Bit			EQU 	0x40



				AREA	inthdr_code, CODE, READONLY

				EXPORT	_HOS_IrqHandler

; ----------------------------------------------
;  IRQ �ϥ�ɥ�
; ----------------------------------------------
				IMPORT	hos_arm_sta_irq
				IMPORT	hos_arm_end_irq
				IMPORT	mknl_exe_int
				IMPORT	mknl_end_int
_HOS_IrqHandler
				sub		lr, lr, #4				; �꥿���󥢥ɥ쥹����
			
			; ---- System�⡼�ɤ˰ܹԤ��ƥ쥸��������
				mov		r13, #I_Bit:OR:F_Bit:OR:Mode_SYS
				msr		cpsr_c, r13
				stmfd	sp!, {r0-r3, ip, lr, pc}	; ���ѥ쥸��������
				mov		r0, sp

			; ---- IRQ�⡼�ɤ����äƤ�spsr��¸				
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_IRQ
				msr		cpsr_c, r1
				str		lr, [r0, #24]			; ��������������¸
				mrs		r0, spsr				; spsr ���Ф�
				
			; ---- USR�⡼�ɤ˰ܹ�
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_USR
				msr		cpsr_c, r1
				stmfd	sp!, {r0}				; �����߸��ե饰��¸
				
			; ---- �����߽���
				bl      hos_arm_sta_irq			; IRQ���Ͻ���(������ֹ����)
				bl		mknl_exe_int			; �����߽����¹�
				bl		hos_arm_end_irq			; IRQ��λ����
				bl		mknl_end_int			; �����ߤν�λ����
				
			; ---- �����ߵ���
				mov	a1, #1		; �����ߵ��Ĥ����
				swi	0x10		; �����ѥХ�������������
				
				ldmfd	sp!, {r0}
				msr		cpsr_sxf, r0
				ldmfd	sp!, {r0-r3, ip, lr, pc}	; �쥸�����������꥿����

				

				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Ryuji Fuchikami                                 
; --------------------------------------------------------------------------- 
