; ---------------------------------------------------------------------------
;  HOS-V4                                                                    
;    �ץ����å���ݲ�����ݡ��ͥ�� (ARM��)                                  
;    ������֥���춦�̥��󥯥롼�ɥե�����
;                                                                            
;                                 Copyright (C) 1998-2002 by Ryuji Fuchikami 
; ---------------------------------------------------------------------------



; �ե饰���
Mode_USR		EQU 	0x10		; USR �⡼��
Mode_FIQ		EQU		0x11		; FIQ �⡼��
Mode_IRQ		EQU 	0x12		; IRQ �⡼��
Mode_SVR		EQU		0x13		; Supervisor �⡼��
Mode_ABT		EQU		0x17		; Abort �⡼��
Mode_UND		EQU		0x1b		; Undefined �⡼��
Mode_SYS		EQU 	0x1f		; System �⡼��

T_Bit			EQU		0x20		; T �ӥå�
F_Bit			EQU 	0x40		; F �ӥå�
I_Bit			EQU 	0x80		; I �ӥå�


; CPU�㳰�ϥ�ɥ��ֹ����
EXCNO_UND		EQU		1			; Undefined�㳰
EXCNO_SWI		EQU		2			; SWI�㳰
EXCNO_PRE		EQU		3			; �ץ�ե��å����ܡ���
EXCNO_DAT		EQU		4			; �ǡ������ܡ���



				END


; ---------------------------------------------------------------------------
;  Copyright (C) 1998-2002 by Ryuji Fuchikami                                
; ---------------------------------------------------------------------------