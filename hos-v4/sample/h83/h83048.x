OUTPUT_FORMAT("coff-h8300")
OUTPUT_ARCH(h8300h)
ENTRY("_startup")
MEMORY
{
	vectors : o = 0x20000, 	l = 0x20200
	rom    	: o = 0x20200, 	l = 0x1fdff
	ram    	: o = 0x30000, l = 0x0fffc
	stack	: o = 0x3fffc, l = 0x4
}
SECTIONS 				
{ 					
.vectors : {
	*(.vectors)
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
