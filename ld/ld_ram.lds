MEMORY {
    flash : ORIGIN = 0x08000000, LENGTH = 1M
    sram1 : ORIGIN = 0x20000000, LENGTH = 96K
    sram2 : ORIGIN = 0x10000000, LENGTH = 32K
}

SECTIONS {
    .text   : { *(.text) }   > sram1
    .data   : { *(.data) }   > sram1
    .rodata : { *(.rodata) } > sram1
    .bss    : { *(.bss)  }   > sram1
}

_stack_start = ORIGIN(sram2) + LENGTH(sram2);

ENTRY(_start)