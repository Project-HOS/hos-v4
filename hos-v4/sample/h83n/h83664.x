OUTPUT_FORMAT("coff-h8300")
OUTPUT_ARCH(h8300hn)
/* OUTPUT_ARCH(h8300h) gcc 3.2 or earlier */
ENTRY("_startup")
MEMORY
{
	vectors : o = 0x0000, l = 0x0034
	rom     : o = 0x0034, l = 0x7fcc
	ram     : o = 0xf780, l = 0x0800
	/* stack   : o = 0xff7c, l = 0x0004 */
	stack   : o = 0xff80, l = 0x0004
}
SECTIONS
{
.vectors : {
	*(.vectors)
        }  > vectors
.text 0x0034 : {
	*(.strings)
	*(.rodata)
   	 _etext = .;
	} > rom
.tors : {
	___ctors = .;
	*(.ctors)
	___ctors_end = .;
	___dtors = . ;
	*(.dtors)
	___dtors_end = .;
	}  > rom
.data : AT ( ADDR(.tors) + SIZEOF(.tors)){
	___data = .;
	*(.data)
	 _edata = .;
	} > ram
	data_size = SIZEOF(.data);
.bss :  {
	 _bss_start = . ;
	*(.bss)
	*(COMMON)
	 _end = . ;
	}  > ram
	bss_size = SIZEOF(.bss);  
.stack : {
	 _stack = . ; 
	*(.stack)
	}  > stack
p.stab 0 (NOLOAD) : {
	[ .stab ]
	}
.stabstr 0 (NOLOAD) : {
	[ .stabstr ]
	}
}
