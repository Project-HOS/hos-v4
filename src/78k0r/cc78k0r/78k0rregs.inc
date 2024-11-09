;	------------------------------------------------------------------------
;		Definition about processor registers
;								Copyright (C) 1998-2009 by Project HOS
;								http://sourceforge.jp/projects/hos/
;	------------------------------------------------------------------------
;	************************************************************************
;		definition about the stack-flame
;	************************************************************************
$IF (__USE_RB__)
pt_adrs	EQU		36		;  4byte
pt_psw	EQU		34		;  1byte(+1byte-dummy)
pt_ax0	EQU		32		;  2byte
pt_bc0	EQU		30		;  2byte
pt_de0	EQU		28		;  2byte
pt_hl0	EQU		26		;  2byte
pt_ax1	EQU		24		;  2byte
pt_bc1	EQU		22		;  2byte
pt_de1	EQU		20		;  2byte
pt_hl1	EQU		18		;  2byte
pt_ax2	EQU		16		;  2byte
pt_bc2	EQU		14		;  2byte
pt_de2	EQU		12		;  2byte
pt_hl2	EQU		10		;  2byte
pt_ax3	EQU		8		;  2byte
pt_bc3	EQU		6		;  2byte
pt_de3	EQU		4		;  2byte
pt_hl3	EQU		2		;  2byte
pt_cs	EQU		1		;  1byte
pt_es	EQU		0		;  1byte
pt_size	EQU		40

pt_ax	EQU		pt_ax0	;  2byte
pt_bc	EQU		pt_bc0	;  2byte
pt_de	EQU		pt_de0	;  2byte
pt_hl	EQU		pt_hl0	;  2byte
$ELSE
pt_adrs	EQU		10		;  4byte
pt_ax	EQU		8		;  2byte
pt_bc	EQU		6		;  2byte
pt_de	EQU		4		;  2byte
pt_hl	EQU		2		;  2byte
pt_cs	EQU		1		;  1byte
pt_es	EQU		0		;  1byte
pt_size	EQU		14
$ENDIF
		DSEG	SADDRP
_AXREG:	DW		(1)
		CSEG	BASE
;	************************************************************************
;		macro for push all of registers
;	************************************************************************
pushall	MACRO
$IF (__USE_RB__)
		push	psw
		SEL		RB0			; select register bank 0
		push	ax
		push	bc
		push	de
		push	hl
		SEL		RB1			; select register bank 1
		push	ax
		push	bc
		push	de
		push	hl
		SEL		RB2			; select register bank 2
		push	ax
		push	bc
		push	de
		push	hl
		SEL		RB3			; select register bank 3
		push	ax
		push	bc
		push	de
		push	hl
$ELSE
		push	ax
		push	bc
		push	de
		push	hl
$ENDIF
		mov		a, cs
		xch		a, x
		mov		a, es
		push	ax			; push cs|es
		ENDM
;	************************************************************************
;		macro for pop all of registers
;	************************************************************************
popall	MACRO
		pop		ax
		mov		es, a		; pop es
		xch		a, x
		mov		cs, a		; pop cs
$IF (__USE_RB__)
		SEL		RB3			; select register bank 3
		pop		hl
		pop		de
		pop		bc
		pop		ax
		SEL		RB2			; select register bank 2
		pop		hl
		pop		de
		pop		bc
		pop		ax
		SEL		RB1			; select register bank 1
		pop		hl
		pop		de
		pop		bc
		pop		ax
		SEL		RB0			; select register bank 0
		pop		hl
		pop		de
		pop		bc
		pop		ax
		pop		psw
$ELSE
		pop		hl
		pop		de
		pop		bc
		pop		ax
$ENDIF
		ENDM
;	------------------------------------------------------------------------
;		Copyright (C) 1998-2009 by Project HOS
;	------------------------------------------------------------------------
