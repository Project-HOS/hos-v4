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
				IMPORT	hos_arm_sta_irq				; IRQ�ν��������
				IMPORT	hos_arm_end_irq				; IRQ�ν�λ����
				IMPORT	kernel_sta_int				; �����߳��Ͻ���
				IMPORT	kernel_end_int				; �����߽�λ����
				IMPORT	kernel_exe_int				; �����߽����μ¹�
				IMPORT	kernel_int_sp				; �������ѥ����å����ɥ쥹
				IMPORT	_HOS_int_cnt				; �����ߥͥ��Ȳ��
				IMPORT	_HOS_int_sp					; �����߻������å�����
				
_HOS_IrqHandler
				sub		lr, lr, #4					; �꥿���󥢥ɥ쥹����
			
			; ---- System�⡼�ɤ˰ܹԤ��ƥ쥸��������
				mov		r13, #I_Bit:OR:F_Bit:OR:Mode_SYS
				msr		cpsr_csxf, r13
				stmfd	sp!, {r1-r3, ip, lr}		; ���ѥ쥸��������

			; ---- IRQ�⡼�ɤ���ä�spsr��¸				
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_IRQ
				msr		cpsr_c, r1
				mrs		r1, spsr					; spsr ���Ф�
				mov		r2, lr						; ��������������¸
				
			; ---- USR�⡼�ɤ˰ܹ�
				mov		r3, #I_Bit:OR:F_Bit:OR:Mode_USR
				msr		cpsr_c, r3
				
			; ---- �쥸��������
				stmfd	sp!, {r0-r2}				; a1, spsr_irq, lr_irq ��¸
				
			; ---- ¿�ų����ߥ����å�
				ldr		r0, =_HOS_int_cnt
				ldr		r1, [r0]					; �����ߥͥ��ȥ����󥿼���
				cmp		r1, #0
				add		r1, r1, #1					; �����ߥͥ��ȥ����󥿥��󥯥����
				str		r1, [r0]
				bne		MultipleInt					; ¿�ų����ߤʤ�ʬ��
				
			; ---- �����å��������ؤ�
				ldr		r0, =_HOS_int_sp
				str		sp, [r0]					; �����å��ݥ��󥿤�����
				ldr		r0, =kernel_int_sp
				ldr		sp, [r0]					; �������ѥ����å�������

			; ---- �����߽����γ���
				bl		kernel_sta_int
				
			; ---- �����߽���
				bl      hos_arm_sta_irq				; IRQ���Ͻ���(������ֹ����)
				bl		kernel_exe_int				; �����߽����¹�
				bl		hos_arm_end_irq				; IRQ��λ����
			
			; ---- �����å�������
				ldr		r0, =_HOS_int_sp
				ldr		sp, [r0]					; �����å��ݥ��󥿤�����
			
			; ---- �����ߥͥ��ȥ�����ȥǥ������
				ldr		r0, =_HOS_int_cnt
				mov		r1, #0
				str		r1, [r0]					; �����ߥͥ��ȥ����󥿥��ꥢ
			
			; ---- �ٱ�ǥ����ѥå��¹�
				bl		kernel_end_int				; �ٱ�ǥ����ѥå��¹�
			
			; ---- �����ߤ��������
ReturnInt		
				IMPORT	_HOS_swi_ret
				ldmfd	sp!, {r0-r2}
				ldr		r3, =_HOS_swi_ret
				stmia	r3, {r0-r2}					; �����������ǡ�������
				ldmfd	sp!, {r1-r3, ip, lr}		; �쥸��������
				mov		a1, #2
				swi		0x10


			;---- ¿�ų����߽���
MultipleInt
			; ---- �����߽���
				bl      hos_arm_sta_irq				; IRQ���Ͻ���(������ֹ����)
				bl		kernel_exe_int				; �����߽����¹�
				bl		hos_arm_end_irq				; IRQ��λ����

			; ---- �����ߥͥ��ȥ�����ȥǥ������
				ldr		r0, =_HOS_int_sp
				ldr		r1, [r0]
				add		r1, r1, #1
				str		r1, [r0]

				b		ReturnInt



				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Ryuji Fuchikami                                 
; --------------------------------------------------------------------------- 
