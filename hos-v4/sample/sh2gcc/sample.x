OUTPUT_FORMAT("coff-sh")
OUTPUT_ARCH(sh)
MEMORY
{
  vector : o = 0x00000000, l = 0x00000300
  rom    : o = 0x00000300, l = 0x0001fd00
  ram    : o = 0xfffff000, l = 0x00001000
  stack  : o = 0xffffff90, l = 0x00000010
}
SECTIONS
{
  .vector :
  {
    _vec_top = . ;
    *(.vector)
  } > vector
  
  .text :
  {
    _stext = . ;
    *(.vector)
    *(.text)
    *(.strings)
    _etext = . ;
  } > rom
  .tors :
  {
    ___ctors = . ;
    *(.ctors)
    ___ctors_end = . ;
    ___dtors = . ;
    *(.dtors)
    ___dtors_end = . ;
  } > rom
  .data :
  {
    _sdata = . ;
    *(.data)
    _edata = . ;
  } > ram
  .bss :
  {
    _bss_start = . ;
    *(.bss)
    *(COMMON)
    _bss_end = . ;
  } > ram
  .stack :
  {
    _stack_top = . ;
    *(.stack);
    _stack_end = . ;
  } > stack
  .stab 0 (NOLOAD) :
  {
    *(.stab)
  }
  .stabstr 0 (NOLOAD) :
  {
    *(.stabstr)
  }
}
