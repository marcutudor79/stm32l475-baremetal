#ifndef LED_H
#define LED_H

/*************************************************************
 *                          INCLUDES                         *
 *************************************************************/
#include <stdint.h>
#include "stm32l475xx.h"

/*************************************************************
 *                      GLOBAL FUNCTIONS                     *
 *************************************************************/
/* Function to init LED2 (green) */
void led_g_init();

/* Function to turn on LED2 (green)*/
void led_g_on();

/* Function to turn off LED2 (green) */
void led_g_off();

/* Function to turn on LED (yellow) and off LED (blue) */
void led_y_on_b_off(void);

/* Function to turn off LED (yellow) and on LED (blue) */
void led_y_off_b_on(void);

#endif /* LED_H */