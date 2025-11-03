#include <stdint.h>

#define RCC_BASE                 (0x40021000UL)
#define RCC_AHB2ENR              (*(volatile uint32_t *)(RCC_BASE + 0x4CUL))
#define RCC_AHB2ENR_GPIOBEN      (1UL << 1)   // GPIOB clock enable (bit 1)
#define RCC_AHB2ENR_GPIOCEN      (1UL << 2)   // GPIOC clock enable

#define GPIOB_BASE               (0x48000400UL)
#define GPIOB_MODER              (*(volatile uint32_t *)(GPIOB_BASE + 0x00UL))
#define GPIOB_BSRR               (*(volatile uint32_t *)(GPIOB_BASE + 0x18UL))

#define GPIOC_BASE               (0x48000800UL)
#define GPIOC_MODER              (*(volatile uint32_t *)(GPIOC_BASE + 0x00UL))
#define GPIOC_BSRR               (*(volatile uint32_t *)(GPIOC_BASE + 0x18UL))

#define PC9                       9U /* YELLOW AND BLUE LEDs */
#define PB14                     14U /* GREEN LED */
#define MODER_POS(pin)           ((pin) * 2U)
#define MODER_MASK(pin)          (3UL << MODER_POS(pin))
#define MODER_OUTPUT(pin)        (1UL << MODER_POS(pin))

#define BSRR_SET(pin)            (1UL << (pin))
#define BSRR_RESET(pin)          (1UL << ((pin) + 16U))

void led_g_init(void)
{
    /* Enable GPIOB clock */
    RCC_AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    /* Configure PB14 as general purpose output (01) */
    GPIOB_MODER = (GPIOB_MODER & ~MODER_MASK(PB14)) | MODER_OUTPUT(PB14);

    /* Enable GPIOC clock */
    RCC_AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    /* Configure PC9 as general purpose output (01) */
    GPIOC_MODER = (GPIOC_MODER & ~MODER_MASK(PC9)) | MODER_OUTPUT(PC9);
}
void led_g_on(void)
{
    /* Write-only register: use '=' */
    GPIOB_BSRR = BSRR_SET(PB14);
}

void led_g_off(void)
{
    /* Reset PB14 via upper half of BSRR */
    GPIOB_BSRR = BSRR_RESET(PB14);
}

void led_y_on_b_off(void)
{
    GPIOC_BSRR = BSRR_SET(PC9);
}

void led_y_off_b_on(void)
{
    GPIOC_BSRR = BSRR_RESET(PC9);
}