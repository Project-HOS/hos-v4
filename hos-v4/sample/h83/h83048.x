OUTPUT_FORMAT("coff-h8300")
OUTPUT_ARCH(h8300h)
ENTRY("_startup")
MEMORY
{
	vectors : o = 0x0000, 	l = 0x200
	rom    	: o = 0x0200, 	l = 0x1fdff
	ram    	: o = 0xffef10, l = 0x1000
	stack	: o = 0xffff0c, l = 0x4
}
SECTIONS 				
{ 					
.vectors : {
	*(.vectors)
	FILL(0xff)
        }  > vectors
.text  : {
	*(.text) 				
	*(.strings)
	*(.rodata) 				
   	 _etext = . ; 
	} > rom
.tors : {
	___ctors = . ;
	*(.ctors)
	___ctors_end = . ;
	___dtors = . ;
	*(.dtors)
	___dtors_end = . ;
	}  > rom
.data : AT ( ADDR(.tors) + SIZEOF(.tors) ){
	___data = . ;
	*(.data)
	*(.tiny)
	 _edata = .;
	} > ram
	data_size = SIZEOF(.data);
.bss : {
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
.stab 0 (NOLOAD) : {
	[ .stab ]
	}
.stabstr 0 (NOLOAD) : {
	[ .stabstr ]
	}
}
