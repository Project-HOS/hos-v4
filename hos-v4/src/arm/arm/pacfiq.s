; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                     
;    �ץ��å���ݲ�����ݡ��ͥ�� (ARM��)                                   
;    FIQ�㳰�ϥ�ɥ�                                                          
;                                                                             
;                                     Copyright (C) 1998-2002 by Project HOS  
;                                     http://sourceforge.jp/projects/hos/     
; --------------------------------------------------------------------------- 


				INCLUDE	pacarm.inc



				AREA	inthdr_code, CODE, READONLY

				EXPORT  _HOS_FiqHandler

; ----------------------------------------------
;  FIQ �ϥ�ɥ�
; ----------------------------------------------
				IMPORT	hos_arm_sta_fiq				; FIQ�ν��������
				IMPORT	hos_arm_end_fiq				; FIQ�ν�λ����
				IMPORT	kernel_sta_int				; �����߳��Ͻ���
				IMPORT	kernel_end_int				; �����߽�λ����
				IMPORT	kernel_exe_int				; �����߽����μ¹�
				IMPORT	kernel_int_sp				; �������ѥ����å����ɥ쥹
				IMPORT	kernel_int_cnt				; �����ߥͥ��Ȳ��
				IMPORT	kernel_int_ssp				; �����߻������å�����
				
_HOS_FiqHandler
				sub		lr, lr, #4					; �꥿���󥢥ɥ쥹����
			
			; ---- System�⡼�ɤ˰ܹԤ��ƥ쥸��������
				mov		r13, #I_Bit:OR:F_Bit:OR:Mode_SYS
				msr		cpsr_csxf, r13
				stmfd	sp!, {r1-r3, ip, lr}		; ���ѥ쥸��������

			; ---- FIQ�⡼�ɤ���ä�spsr��¸				
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_FIQ
				msr		cpsr_c, r1
				mrs		r1, spsr					; spsr ���Ф�
				mov		r2, lr						; ��������������¸
				
			; ---- USR�⡼�ɤ˰ܹ�
				mov		r3, #I_Bit:OR:F_Bit:OR:Mode_USR
				msr		cpsr_c, r3
				
			; ---- �쥸��������
				stmfd	sp!, {r0-r2}				; a1, spsr_irq, lr_irq ��¸
				
			; ---- ¿�ų����ߥ����å�
				ldr		r0, =kernel_int_cnt
				ldr		r1, [r0]					; �����ߥͥ��ȥ����󥿼���
				cmp		r1, #0
				add		r1, r1, #1					; �����ߥͥ��ȥ����󥿥��󥯥����
				str		r1, [r0]
				bne		MultipleInt					; ¿�ų����ߤʤ�ʬ��
				
			; ---- �����å��������ؤ�
				ldr		r0, =kernel_int_ssp
				str		sp, [r0]					; �����å��ݥ��󥿤�����
				ldr		r0, =kernel_int_sp
				ldr		sp, [r0]					; �������ѥ����å�������

			; ---- �����߽����γ���
				bl		kernel_sta_int
				
			; ---- �����߽���
				bl      hos_arm_sta_fiq				; FIQ���Ͻ���(������ֹ����)
				bl		kernel_exe_int				; �����߽����¹�
				bl		hos_arm_end_fiq				; FIQ��λ����
			
			; ---- �����å�������
				ldr		r0, =kernel_int_ssp
				ldr		sp, [r0]					; �����å��ݥ��󥿤�����
			
			; ---- �����ߥͥ��ȥ�����ȥǥ������
				ldr		r0, =kernel_int_cnt
				mov		r1, #0
				str		r1, [r0]					; �����ߥͥ��ȥ����󥿥��ꥢ
			
			; ---- �ٱ�ǥ����ѥå��¹�
				bl		kernel_end_int				; �ٱ�ǥ����ѥå��¹�
			
			; ---- �����ߤ��������
ReturnInt		
				IMPORT	pac_arm_swi_ret
				ldmfd	sp!, {r0-r2}
				ldr		r3, =pac_arm_swi_ret
				stmia	r3, {r0-r2}					; �����������ǡ�������
				ldmfd	sp!, {r1-r3, ip, lr}		; �쥸��������
				mov		a1, #2
				swi		0x10


			;---- ¿�ų����߽���
MultipleInt
			; ---- �����߽���
				bl      hos_arm_sta_fiq				; FIQ���Ͻ���(������ֹ����)
				bl		kernel_exe_int				; �����߽����¹�
				bl		hos_arm_end_fiq				; FIQ��λ����

			; ---- �����ߥͥ��ȥ�����ȥǥ������
				ldr		r0, =kernel_int_ssp
				ldr		r1, [r0]
				add		r1, r1, #1
				str		r1, [r0]

				b		ReturnInt



				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
