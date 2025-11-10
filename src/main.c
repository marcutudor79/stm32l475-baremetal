#include "inc/led.h"
#include "inc/clocks.h"
#include "inc/uart.h"

/* Function to delay */
void delay();

int main(void)
{
    /* Enables the 80Mhz clock */
    clocks_init();

    /* Init the green LED */
    led_g_init();

    /* Init UART */
    uart_init();

    /* Start LED blinking */
    while(1)
    {
        uart_send_string("Toggle LEDs ON...\r\n");
        led_g_on();
        led_y_on_b_off();
        delay();

        uart_send_string("Toggle LEDs OFF...\r\n");
        led_g_off();
        led_y_off_b_on();
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
