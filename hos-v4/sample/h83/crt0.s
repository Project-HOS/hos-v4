; --------------------------------------------------------------------------- 
;  Hyper Operating System V4  ��Ω H8 �� ����ץ�ץ����                   
;    �������ȥ��åץ롼����                                                   
;                                                                             
;                                   Copyright (C) 1998-2002 by Project HOS    
;                                   http://sourceforge.jp/projects/hos/       
; --------------------------------------------------------------------------- 



				.h8300h

; -------------------------------------
;  �������ȥ��åץ롼����
; -------------------------------------
				.text
				.align 2
				.global _startup
_startup:
		; ----- �����å������
				mov.l	#_stack,er7

		; ----- .data ��������󥳥ԡ� ��DATA��64kbyte�ʲ��Ȳ����
				mov.l	#___dtors_end,er5
				mov.l	#___data,er6
				mov.w	#data_size,r4
copy_dsec:	eepmov.w
				mov.w	r4,r4
				bne	copy_dsec
				
		; ----- .bss ��������󥯥ꥢ��BSS��64kbyte�ʲ��Ȳ����
				mov.l	#_bss_start,er5
				mov.l	#_bss_start+1,er6
				mov.w	#bss_size,r4
				mov.b	#0,r0l
				mov.b	r0l,@er5
clr_bsec:		eepmov.w
				mov.w	r4,r4
				bne	clr_bsec

		; ----- ������롼����ƤӽФ�
				jsr	@_main
idle_loop:
				bra	idle_loop


				.global	_kernel_int_sp
				.section .rodata
				.align 2
_kernel_int_sp:
				.long	_stack		/* �����߻��� er7 ��¸�� */


				.end



; --------------------------------------------------------------------------- 
;  Copyright (C) 1998-2002 by Project HOS                                     
; --------------------------------------------------------------------------- 
