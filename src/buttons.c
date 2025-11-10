/*************************************************************
 *                          INCLUDES                         *
 *************************************************************/

#include <stdint.h>
#include "inc/led.h"
#include "inc/irq.h"   /* si vous avez les prototypes / CMSIS types */

/*************************************************************
 *                      GLOBAL FUNCTIONS                     *
 *************************************************************/

/* Initialize button B2 (PC13) to trigger an interrupt on desendant voltage */
void buttons_init(void)
{
    /* Activate the clock for port C */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    /* Configure PC13 as input */
    GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;

    /* Activate the clock for SYSCFG to enable EXT1 */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    /* Select PC13 as the source for EXTI13 */
    SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] & ~(0xF << 4)) | (0x2 << 4); /* 0x2 = port C */

    /* Configure EXTI13: trigger on descendant front, deactivate rising front */
    EXTI->RTSR1 &= ~EXTI_RTSR1_RT13;
    EXTI->FTSR1 |= EXTI_FTSR1_FT13;

    /* Clear the pending bit */
    EXTI->PR1 = EXTI_PR1_PIF13;

    /* Autorize the interrupt on line 13 */
    EXTI->IMR1 |= EXTI_IMR1_IM13;

    /* fallback direct si CMSIS non disponible : écrire sur ISER */
    NVIC->ISER[EXTI15_10_IRQn >> 5] = (1U << (EXTI15_10_IRQn & 31));
}

