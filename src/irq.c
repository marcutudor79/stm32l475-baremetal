/*************************************************************
 *                          INCLUDES                         *
 *************************************************************/
#include <stdint.h>
#include "inc/irq.h"

/*************************************************************
 *                      SYMBOLS FROM LINKER                   *
 * These must match the symbols used in your linker script
 *************************************************************/
extern uint32_t _stack_start;   /* defined in linker script */
extern void _start(void);

/*************************************************************
 *               CORE / PERIPHERAL HANDLER PROTOTYPES       *
 * Declare all handlers as weak aliases to Default_Handler.
 * Add/rename entries to match your vendor startup list if
 * your device has different IRQ names/order.
 *************************************************************/
void Reset_Handler(void)        __attribute__((noreturn));
void NMI_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));

/* Peripheral IRQ handlers (common STM32L4 names) */
void WWDG_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void PVD_PVM_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler(void)       __attribute__ ((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void)         __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler(void)    __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_IRQHandler(void)    __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel3_IRQHandler(void)    __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel4_IRQHandler(void)    __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel5_IRQHandler(void)    __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel6_IRQHandler(void)    __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel7_IRQHandler(void)    __attribute__ ((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void CAN1_TX_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX0_IRQHandler(void)         __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler(void)         __attribute__ ((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler(void)         __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM15_IRQHandler(void)   __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM16_IRQHandler(void)    __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM17_IRQHandler(void)__attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void USART3_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
/* Add more peripheral handlers here as required by your device... */

/*************************************************************
 *                   DEFAULT HANDLER                         *
 *************************************************************/
void Default_Handler(void)
{
    while (1) { __asm__ volatile ("wfi"); }
}

/*************************************************************
 *                   VECTOR TABLE                             *
 * The first entry is the initial SP value, second is reset
 * handler, then the core exceptions, then peripheral IRQs.
 * Replace / extend peripheral entries to match the device
 * startup file provided by ST for the STM32L475.
 *************************************************************/
void * const vector_table[] __attribute__((section(".isr_vector"))) = {
    /* Initial stack pointer */
    &_stack_start,
    /* Reset handler */
    _start,

    /* Cortex-M4 core handlers */
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0, /* reserved */
    0, /* reserved */
    0, /* reserved */
    0, /* reserved */
    SVC_Handler,
    DebugMon_Handler,
    0, /* reserved */
    PendSV_Handler,
    SysTick_Handler,

    /* External Interrupts (peripheral handlers) */
    WWDG_IRQHandler,               /* Window Watchdog */
    PVD_PVM_IRQHandler,            /* PVD and PVM through EXTI line detection */
    TAMP_STAMP_IRQHandler,         /* Tamper and TimeStamp */
    RTC_WKUP_IRQHandler,           /* RTC Wakeup */
    FLASH_IRQHandler,              /* Flash */
    RCC_IRQHandler,                /* RCC */
    EXTI0_IRQHandler,              /* EXTI Line0 */
    EXTI1_IRQHandler,              /* EXTI Line1 */
    EXTI2_IRQHandler,              /* EXTI Line2 */
    EXTI3_IRQHandler,              /* EXTI Line3 */
    EXTI4_IRQHandler,              /* EXTI Line4 */
    DMA1_Channel1_IRQHandler,      /* DMA1 Channel1 */
    DMA1_Channel2_IRQHandler,      /* DMA1 Channel2 */
    DMA1_Channel3_IRQHandler,      /* DMA1 Channel3 */
    DMA1_Channel4_IRQHandler,      /* DMA1 Channel4 */
    DMA1_Channel5_IRQHandler,      /* DMA1 Channel5 */
    DMA1_Channel6_IRQHandler,      /* DMA1 Channel6 */
    DMA1_Channel7_IRQHandler,      /* DMA1 Channel7 */
    ADC1_2_IRQHandler,             /* ADC1 and ADC2 */
    CAN1_TX_IRQHandler,            /* CAN1 TX */
    CAN1_RX0_IRQHandler,           /* CAN1 RX0 */
    CAN1_RX1_IRQHandler,           /* CAN1 RX1 */
    CAN1_SCE_IRQHandler,           /* CAN1 SCE */
    EXTI9_5_IRQHandler,            /* EXTI Line[9:5] */
    TIM1_BRK_TIM15_IRQHandler,     /* TIM1 Break & TIM15 */
    TIM1_UP_TIM16_IRQHandler,      /* TIM1 Update & TIM16 */
    TIM1_TRG_COM_TIM17_IRQHandler, /* TIM1 Trigger & Commutation & TIM17 */
    TIM1_CC_IRQHandler,            /* TIM1 Capture/Compare */
    TIM2_IRQHandler,               /* TIM2 */
    TIM3_IRQHandler,               /* TIM3 */
    TIM4_IRQHandler,               /* TIM4 */
    I2C1_EV_IRQHandler,            /* I2C1 Event */
    I2C1_ER_IRQHandler,            /* I2C1 Error */
    I2C2_EV_IRQHandler,            /* I2C2 Event */
    I2C2_ER_IRQHandler,            /* I2C2 Error */
    SPI1_IRQHandler,               /* SPI1 */
    SPI2_IRQHandler,               /* SPI2 */
    USART1_IRQHandler,             /* USART1 */
    USART2_IRQHandler,             /* USART2 */
    USART3_IRQHandler,             /* USART3 */
    EXTI15_10_IRQHandler,          /* EXTI Line[15:10] */
    RTC_Alarm_IRQHandler,          /* RTC Alarm */
    /* If your device defines more IRQs, append them here in correct order. */
};

/*************************************************************
 *                   INITIALIZATION HOOK                       *
 * You already provided irq_init() earlier. If not, define:
 *************************************************************/
/* irq_init() should write SCB->VTOR = (uint32_t)vector_table; */
/* and execute dsb/isb. */

/* Set VTOR to point to our vector table so exceptions use the right table */
void irq_init(void)
{
    /* Write VTOR (address 0xE000ED08) with vector_table address.
       If CMSIS is available you can use SCB->VTOR instead. */
    (*(volatile uint32_t *)0xE000ED08U) = (uint32_t)vector_table;

    /* Ensure the write is visible before continuing */
    __asm__ volatile ("dsb");
    __asm__ volatile ("isb");
}