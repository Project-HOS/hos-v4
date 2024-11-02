SECTIONS
{
	_stack_init = 0x8007FFF0 ;
	.text 0x9FC80000 : {
		_ftext = . ;
		_stext = . ;
		*(.text)
		*(.text.*)
		*(.gnu.linkonce.t*)
		. = ALIGN(8) ;					/*	. = ALIGN(4) ;	*/
		_ctor_list = . ;
		*(.ctors);*(.ctor);LONG (0); 
		_dtor_list = . ;
		*(.dtors);*(.dtor);LONG (0); 
		etext  = . ;
		_etext = . ;
	}
	. = ALIGN(8) ;		/* added */
	.rodata : {
		*(.rdata)
		*(.rodata)
		*(.rodata.*)
		*(.gnu.linkonce.r*)
	}
	. = ALIGN(8) ;		/* added */
	.eh_frame_hdr : {
		 *(.eh_frame_hdr)
	}
	. = ALIGN(8) ;		/* added */
	.eh_frame : {
		*(.eh_frame)
	}
	. = ALIGN(8) ;		/* added */
	.jcr : {
		*(.jcr)
		_erdata = . ;
	}
	_fdata = . ;
	.data 0x80020000 : AT ( _fdata ) {
		_data = . ;
		*(.data)
		*(.data.*)
		*(.gnu.linkonce.d*)
		_mdata = . ;
	}
	_gp = . + 0x8000 ;
	.sdata : AT ( _fdata + SIZEOF(.data) ) {
		*(.lit8)
		*(.lit4)
		*(.sdata) 
		*(.sdata.*) 
	}
	. = ALIGN(8) ;		/* added */
	edata  = . ;
	_edata = . ;
	_fbss  = . ;
	.sbss : {
		*(.sbss)
		*(.sbss.*)
		*(.gnu.linkonce.sb.*)
		*(.scommon)
	}
	. = ALIGN(8) ;		/* added */
	.bss : {
		_bss_start = . ;
		*(.bss)
		*(.bss.*)
		*(.gnu.linkonce.b.*)
		*(COMMON)
	}
	. = ALIGN(8) ;		/* added */
	end  = . ;
	_end = . ;

	/* DWARF debug sections */

	.debug          0 : { *(.debug) }
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_sfnames  0 : { *(.debug_sfnames) }
	.line           0 : { *(.line) }

	.debug_info     0 : { *(.debug_info) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
}
