; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                     
;    �ץ��å���ݲ�����ݡ��ͥ�� (ARM��)                                   
;    �㳰�ϥ�ɥ�                                                             
;                                                                             
;                                     Copyright (C) 1998-2002 by Project HOS  
;                                     http://sourceforge.jp/projects/hos/     
; --------------------------------------------------------------------------- 


				INCLUDE	pacarm.inc



				AREA	inthdr_code, CODE, READONLY
				CODE32

				EXPORT	_HOS_CpuExceptionHandler

; ----------------------------------------------
;  CPU�㳰�ϥ�ɥ�
; ----------------------------------------------
				IMPORT	kernel_sta_exc				; CPU�㳰�ϥ�ɥ鳫�Ͻ���
				IMPORT	kernel_end_exc				; CPU�㳰�ϥ�ɥ齪λ����
				IMPORT	kernel_exe_exc				; CPU�㳰�ϥ�ɥ�μ¹�
				IMPORT	kernel_int_sp				; �������ѥ����å����ɥ쥹
				IMPORT	_HOS_int_cnt				; �����ߥͥ��Ȳ��
				IMPORT	_HOS_int_sp					; �����߻������å�����
				
_HOS_CpuExceptionHandler
			; ---- System�⡼�ɤ˰ܹԤ��ƥ쥸��������
				mov		r13, #I_Bit:OR:F_Bit:OR:Mode_SYS
				msr		cpsr_csxf, r13
				stmfd	sp!, {r1-r3, ip, lr}		; ���ѥ쥸��������

			; ---- ���Υ⡼�ɤ���ä�spsr��¸
				mov		r1, #I_Bit:OR:F_Bit:OR:Mode_UND
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
				bne		MultipleInt					; ��������ʤ�ʬ��
				
			; ---- �����å��������ؤ�
				ldr		r0, =_HOS_int_sp
				str		sp, [r0]					; �����å��ݥ��󥿤�����
				ldr		r0, =kernel_int_sp
				ldr		sp, [r0]					; �������ѥ����å�������

			; ---- CPU�㳰�ϥ�ɥ�����γ���
				bl		kernel_sta_exc				; CPU�㳰�ϥ�ɥ鳫�Ͻ���
				bl		kernel_exe_exc				; �����߽����¹�
			
			; ---- �����å�������
				ldr		r0, =_HOS_int_sp
				ldr		sp, [r0]					; �����å��ݥ��󥿤�����
			
			; ---- �����ߥͥ��ȥ�����ȥǥ������
				ldr		r0, =_HOS_int_cnt
				mov		r1, #0
				str		r1, [r0]					; �����ߥͥ��ȥ����󥿥��ꥢ
			
			; ---- �ٱ�ǥ����ѥå��¹�
				bl		kernel_end_exc				; �ٱ�ǥ����ѥå��¹�
			
			; ---- CPU�㳰�ϥ�ɥ餫�������
ReturnExc		
				IMPORT	_HOS_swi_ret
				ldmfd	sp!, {r0-r2}
				ldr		r3, =_HOS_swi_ret
				stmia	r3, {r0-r2}					; �����������ǡ�������
				ldmfd	sp!, {r1-r3, ip, lr}		; �쥸��������
				mov		a1, #2
				swi		0x10


			;---- ��������ν���
MultipleInt
			; ---- �����߽���
				bl		kernel_sta_exc				; CPU�㳰�ϥ�ɥ鳫�Ͻ���

			; ---- �����ߥͥ��ȥ�����ȥǥ������
				ldr		r0, =_HOS_int_sp
				ldr		r1, [r0]
				add		r1, r1, #1
				str		r1, [r0]

				b		ReturnExc



				END


; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
