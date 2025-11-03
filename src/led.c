/*************************************************************
 *                          INCLUDES                         *
 *************************************************************/
#include "inc/led.h"

/*************************************************************
 *                      GLOBAL FUNCTIONS                     *
 *************************************************************/

void led_g_init(void)
{
    /* Enable GPIOB clock */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    /* Configure PB14 as general purpose output (01) */
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE14_Msk) | GPIO_MODER_MODE14_0;

    /* Enable GPIOC clock */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    /* Configure PC9 as general purpose output (01) */
    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODE9_0;
}

void led_g_on(void)
{
    /* Write-only register: use '=' */
    GPIOB->BSRR |= GPIO_BSRR_BS14;
}

void led_g_off(void)
{
    /* Reset PB14 via upper half of BSRR */
    GPIOB->BSRR |= GPIO_BSRR_BR14;
}

void led_y_on_b_off(void)
{
    GPIOC->BSRR |= GPIO_BSRR_BS9;
}

void led_y_off_b_on(void)
{
    GPIOC->BSRR |= GPIO_BSRR_BR9;
}