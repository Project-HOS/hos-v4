/* ------------------------------------------------------------------------ */
/*  HOS-V4 ����ץ�ץ������                                               */
/*    �������ȥ��åץ⥸�塼�� (��Ω SH2 gcc ��)                            */
/*                                                                          */
/*                                   Copyright (C) 2002 by Ryuji Fuchikami  */
/* ------------------------------------------------------------------------ */



				.extern		_main
				.extern		_DATA_ROM
				.extern		_DATA_START
				.extern		_DATA_END
				.extern		_BSS_START
				.extern		_BSS_END

				.global		_pwr_reset
				.global		_man_reset
				.global		___main



				.section	.text


/************************************************
  �ꥻ�åȥϥ�ɥ�
************************************************/
_pwr_reset:
_man_reset:
				/* DATA�ΰ�Υ��ԡ� */
				mov.l	l_data_rom, r0
				mov.l	l_data_start, r1
				mov.l	l_data_end, r2
				cmp/hs	r2, r1
				bt		data_end
data_loop:		
				mov.l	@r0+, r3
				mov.l	r3, @r1
				add		#4, r1
				cmp/hs	r2, r1
				bf		data_loop
data_end:		
				
				/* BSS�ΰ�ν���� */
				mov.l	l_bss_start, r0
				mov.l	l_bss_end, r1
				cmp/hs	r1, r0
				bt		bss_end
				mov		#0, r2
bss_loop:		
				mov.l	r2, @r0
				add		#4, r0
				cmp/hs	r1, r0
				bf		bss_loop
bss_end:		
				
				/* main�ؿ��θƤӽФ� */
				mov.l	l_main, r8
				jsr		@r8
				nop
end_loop:
				bra		end_loop

				/* __main */
___main:
				rts		/* ���⤷�ʤ� */
				nop

				.align	4
l_data_rom:		
				.long	_DATA_ROM
l_data_start:	
				.long	_DATA_START
l_data_end:		
				.long	_DATA_END
l_bss_start:
				.long	_BSS_START
l_bss_end:
				.long	_BSS_END
l_main:			
				.long	_main



				.section	.stack
				.global		_stack

/************************************************
  �����å��ΰ�
************************************************/
				.align		4
_stack:			.long		1



				.end



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 2002 by Ryuji Fuchikami                                   */
/* ------------------------------------------------------------------------ */