OUTPUT_ARCH( "riscv" )
ENTRY(_start)

_HEAP_SIZE  = 0x4000;



SECTIONS
{

  . = 0x80000000;
  .text.init : { *(.text.init) }

  . = ALIGN(0x1000);
  .tohost : { *(.tohost) }

  . = ALIGN(0x1000);
  .text : { *(.text) }

  .data : { *(.data) }

  .tdata :
  {
    _tdata_begin = .;
    *(.tdata)
    _tdata_end = .;
  }

  .sdata : {
    __global_pointer$ = . + 0x800;
    *(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata*)
    *(.sdata .sdata.* .gnu.linkonce.s.*)
  }

  .sbss : {
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
  }
  .bss : { *(.bss) }

  .tbss :
  {
    *(.tbss)
    _tbss_end = .;
  }


  _end = .;
    PROVIDE (end = .);



      .heap : ALIGN(4)
  {
    PROVIDE(__heap_start = .);
    . = _HEAP_SIZE;
    /* finish section on WORD boundary */
    . = ALIGN(4);
    PROVIDE(__heap_end = .);
  } 
}
