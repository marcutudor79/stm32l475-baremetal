#ifndef UART_H
#define UART_H

/*************************************************************
 *                          INCLUDES                         *
 *************************************************************/

#include "stm32l4xx.h"

/*************************************************************
 *                      GLOBAL FUNCTIONS                     *
 *************************************************************/

/* Function used to init uart to 115200 */
void uart_init();

/* Function used to send a char through */
void uart_send_char(char c);

/* Function used to send a string through */
void uart_send_string(const char *str);


#endif // UART_H