
				.section	.text
				
				.extern		_boot
				.extern		_main
				.extern		_exit
				.global		_start
				
_start:			
				mov.l	L_BOOT, r8
				jsr		@r8
				nop
				mov.l	L_MAIN, r8
				jsr		@r8
				nop
				mov.l	L_EXIT, r8
				jsr		@r8
				nop

				.align	4
L_BOOT:			.long	_boot
L_MAIN:			.long	_main
L_EXIT:			.long	_exit

				.section	.stack
				.global		_stack
				.align		4
_stack:			.long		1


				.end

