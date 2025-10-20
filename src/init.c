#include "stdint.h"

/* Take bss start and end from linker script */
extern uint8_t _bss_start;
extern uint8_t _bss_end;

int init_bss()
{
    uint8_t *dst = 0U;

    /* Init bss memory */
    for (dst = &_bss_start; dst < &_bss_end; dst++)
        *dst = 0U;
}