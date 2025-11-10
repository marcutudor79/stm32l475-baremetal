
/*************************************************************
 *                          INCLUDES                         *
 *************************************************************/
#include "inc/uart.h"

/*************************************************************
 *                      GLOBAL FUNCTIONS                     *
 *************************************************************/

void uart_init(void)
{
    /* Enable GPIOB clock (PB6 = TX, PB7 = RX) */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    /* Configure PB6/PB7 as Alternate Function (AF7 = USART1) */
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE6_Msk) | GPIO_MODER_MODE6_1;
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7_Msk) | GPIO_MODER_MODE7_1;

    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL6_Msk) | (7 << GPIO_AFRL_AFSEL6_Pos);
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL7_Msk) | (7 << GPIO_AFRL_AFSEL7_Pos);

    /* Select PCLK as clock source for USART1 */
    RCC->CCIPR &= ~RCC_CCIPR_USART1SEL; /* 00 = PCLK */

    /* Enable and reset USART1 peripheral */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

    /* Configure oversampling = 16 (clear OVER8) */
    USART1->CR1 &= ~USART_CR1_OVER8;

    /* Set baud rate to 115200 assuming PCLK = 80 MHz */
    USART1->BRR = 80000000U / 115200U;

    /* Configure 8N1 (default: M bits = 0, no parity) and enable TE/RE */
    USART1->CR1 &= ~(USART_CR1_M0 | USART_CR1_M1 | USART_CR1_PCE);
    USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE);

    /* Enable USART1 */
    USART1->CR1 |= USART_CR1_UE;
}

void uart_putchar(uint8_t c)
{
    /* Wait until transmit data register is empty */
    while (!(USART1->ISR & USART_ISR_TXE));

    /* Send the character */
    USART1->TDR = c;
}

void uart_puts(const char *str)
{
    while (*str)
    {
        uart_putchar(*str++);
    }
}

void uart_getchar(uint8_t *c)
{
    /* Wait until receive data register is not empty */
    while (!(USART1->ISR & USART_ISR_RXNE));

    /* Read the character */
    *c = (char)(USART1->RDR & 0xFF);
}

void uart_gets(char *buf, size_t len)
{
    size_t i = 0;
    uint8_t c;

    while (i < (len - 1)) // Leave space for null terminator
    {
        uart_getchar(&c);
        if (c == '\r' || c == '\n') // Newline or carriage return
        {
            break;
        }
        buf[i++] = (char)c;
    }
    buf[i] = '\0'; // Null-terminate the string
}