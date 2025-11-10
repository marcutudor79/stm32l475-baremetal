#include "inc/led.h"
#include "inc/clocks.h"
#include "inc/uart.h"
#include "stdlib.h"

/* Defines */
#define TWO_POWER_32 4294967296

/* Function to delay */
void delay();

/* convert unsigned 32-bit to string in given base (2..36) */
char *utoa32(uint32_t value, char *str, int base)
{
    char *p = str;
    char *first;
    uint32_t tmp;

    if (base < 2 || base > 36) { *str = '\0'; return str; }

    /* handle zero explicitly */
    if (value == 0) {
        *p++ = '0';
        *p = '\0';
        return str;
    }

    first = p;
    while (value != 0) {
        uint32_t digit = value % (uint32_t)base;
        *p++ = (digit < 10) ? ('0' + digit) : ('a' + (digit - 10));
        value /= (uint32_t)base;
    }
    *p = '\0';

    /* reverse */
    for (--p; first < p; ++first, --p) {
        tmp = (uint32_t)*first;
        *first = *p;
        *p = (char)tmp;
    }

    return str;
}

/* classic itoa with sign handling for base 10; for other bases negative handled as unsigned magnitude */
char *itoa(int value, char *str, int base)
{
    if (base == 10 && value < 0) {
        *str++ = '-';
        /* convert magnitude as unsigned to avoid UB for INT_MIN */
        utoa32((uint32_t)(-(int64_t)value), str, base);
    } else {
        utoa32((uint32_t)value, str, base);
    }
    return str - ((base == 10 && value < 0) ? 1 : 0);
}

int main(void)
{
    /* Enables the 80Mhz clock */
    clocks_init();

    /* Init the green LED */
    led_g_init();

    /* Init UART */
    uart_init();

    uint8_t buff = 0;
    uint32_t sum = 0;
    char itoa_buf[11];

    /* Start LED blinking */
    for (int i = 0; i < 1000; i++)
    {
        uart_getchar(&buff);
        sum += buff;
    }

    /* Compute checksum */
    sum = sum % TWO_POWER_32;
    itoa(sum, itoa_buf, 16);

    while(1)
    {
        uart_puts("Sum of bytes sent on UART=0x");
        uart_puts(itoa_buf);
        uart_puts("\n\r");
        delay();
    }

    /* Should not get here */
    while(1);
}

/* Function to delay */
void delay()
{
        for (int i=0U; i<500000U; i++)
            // asm - inline assembly volatile - do not optimize the nops in the executable
            __asm__ volatile("nop");
}
