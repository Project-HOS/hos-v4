/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0���� Real-Time OS                  */
/*    �ץ����å���ݲ�����ݡ��ͥ�� (ARM gcc��)                            */
/*   ������֥���춦�̥��󥯥롼�ɥե�����                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */



				/* �ե饰��� */
				.equ	Mode_USR, 0x10		/* USR �⡼�� */
				.equ	Mode_FIQ, 0x11		/* FIQ �⡼�� */
				.equ	Mode_IRQ, 0x12		/* IRQ �⡼�� */
				.equ	Mode_SVR, 0x13		/* Supervisor �⡼�� */
				.equ	Mode_ABT, 0x17		/* Abort �⡼�� */
				.equ	Mode_UND, 0x1b		/* Undefined �⡼�� */
				.equ	Mode_SYS, 0x1f		/* System �⡼�� */

				.equ	T_Bit, 0x20			/* T �ӥå� */
				.equ	F_Bit, 0x40			/* F �ӥå� */
				.equ	I_Bit, 0x80			/* I �ӥå� */


				/* CPU�㳰�ϥ�ɥ��ֹ���� */
				.equ	EXCNO_UND, 1		/* Undefined�㳰 */
				.equ	EXCNO_SWI, 2		/* SWI�㳰 */
				.equ	EXCNO_PRE, 3		/* �ץ�ե��å����ܡ��� */
				.equ	EXCNO_DAT, 4		/* �ǡ������ܡ��� */



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */