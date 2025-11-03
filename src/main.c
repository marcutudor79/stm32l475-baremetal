#include "led.h"

int n = 0U;

// recursive fibo_recursivennaci - not good in embedded apps due to being susceptible to stack overflow
int fibo_recursive(int n)
{
    if (n <= 1U)
        return n;

    return (fibo_recursive(n-1) + fibo_recursive(n-2));
}

int fibo_linear(int n)
{
    int a = 0U;
    int b = 1U;

    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;

    for (int i = 2; i <= n; ++i)
    {
        int c = a + b;
        a = b;
        b = c;
    }

    return b;
}

/* Function to delay */
void delay()
{
        for (int i=0U; i<50000U; i++)
            // asm - inline assembly volatile - do not optimize the nops in the executable
            __asm__ volatile("nop");
}

int main(void)
{
    /* Checkout fibonacci calculus */
    if (fibo_recursive(3) != fibo_linear(3))
    {
        while(1);
    }

    /* Init the green LED */
    led_g_init();

    /* Start LED blinking */
    while(1)
    {
        led_g_on();
        led_y_on_b_off();
        delay();

        led_g_off();
        led_y_off_b_on();
        delay();
    }

    /* Should not get here */
    while(1);
}
