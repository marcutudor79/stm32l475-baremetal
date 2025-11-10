#ifndef UART_H
#define UART_H

/*************************************************************
 *                          INCLUDES                         *
 *************************************************************/

#include "stm32l4xx.h"
#include <stddef.h>

/*************************************************************
 *                      GLOBAL FUNCTIONS                     *
 *************************************************************/

/* Function used to init uart to 115200 */
void uart_init();

/* Function used to send a char through */
void uart_putchar(uint8_t c);

/* Function to receive a char */
void uart_getchar(uint8_t *c);

/* Function used to send a string through */
void uart_puts(const char *str);

/* Function to receive a string */
void uart_gets(char *buf, size_t len);


#endif // UART_H