#ifndef CORE_NVIC_H
#define CORE_NVIC_H

#include "types.h"

/**
 * @brief Vector table definition
 * 
 */
typedef struct
{
    void *pStack;   // Stack pointer

    // Exception handlers
    void *pfReset_handler;
    void *pfNMI_handler;
    void *pfHardfault_handler;
    void *pfMemMgmtFault_handler;
    void *pfBusFault_handler;
    void *pfUsageFault_handler;
    void *RESERVED_A[4];
    void *pfSVCall_handler;
    void *RESERVED_B[2];
    void *pfPendSV_handler;
    void *pfSystick_handler;

    // Interrupts
    void *pfIrq_clockPowerBprot;
    void *pfIrq_radio;
    void *pfIrq_uarte;
    void *pfIrq_spiTwi0;
    void *pfIrq_spiTwi1;
    void *pfIrq_nfct;
    void *pfIrq_gpiote;
    void *pfIrq_saadc;
    void *pfIrq_timer0;
    void *pfIrq_timer1;
    void *pfIrq_timer2;
    void *pfIrq_rtc0;
    void *pfIrq_temp;
    void *pfIrq_rng;
    void *pfIrq_ecb;
    void *pfIrq_ccm;
    void *pfIrq_aar;
    void *pfIrq_wdt;
    void *pfIrq_rtc1;
    void *pfIrq_qdec;
    void *pfIrq_comp;
    void *pfIrq_swiEgu0;
    void *pfIrq_swiEgu1;
    void *pfIrq_swiegu2;
    void *pfIrq_swiegu3;
    void *pfIrq_swiegu4;
    void *pfIrq_swiegu5;
    void *pfIrq_timer3;
    void *pfIrq_timer4;
    void *pfIrq_pwm0;
    void *pfIrq_pdm;
    void *pfIrq_nvmc;
    void *pfIrq_ppi;
    void *pfIrq_mwu;
    void *pfIrq_pwm1;
    void *pfIrq_pwm2;
    void *pfIrq_spi2;
    void *pfIrq_rtc2;
    void *pfIrq_i2s;
    void *pfIrq_fpu;
} tVectorTable;

typedef enum
{
    NVIC_INT_CLOCK_POWER_BROT,
    NVIC_INT_RADIO,
    NVIC_INT_UARTE,
    NVIC_INT_SPI_TWI0,
    NVIC_INT_SPI_TWI1,
    NVIC_INT_NFCT,
    NVIC_INT_GPIOTE,
    NVIC_INT_SAADC,
    NVIC_INT_TIMER0,
    NVIC_INT_TIMER1,
    NVIC_INT_TIMER2,
    NVIC_INT_RTC0,
    NVIC_INT_TEMP,
    NVIC_INT_RNG,
    NVIC_INT_ECB,
    NVIC_INT_CCM,
    NVIC_INT_AAR,
    NVIC_INT_WDT,
    NVIC_INT_RTCL,
    NVIC_INT_QDEC,
    NVIC_INT_COMP,
    NVIC_INT_SWIEGU0,
    NVIC_INT_SWIEGU1,
    NVIC_INT_SWIEGU2,
    NVIC_INT_SWIEGU3,
    NVIC_INT_SWIEGU4,
    NVIC_INT_SWIEGU5,
    NVIC_INT_TIMER3,
    NVIC_INT_TIMER4,
    NVIC_INT_PWM0,
    NVIC_INT_PDM,
    NVIC_INT_NVMC,
    NVIC_INT_PPI,
    NVIC_INT_MWU,
    NVIC_INT_PWM1,
    NVIC_INT_PWM2,
    NVIC_INT_SPI2,
    NVIC_INT_RTC2,
    NVIC_INT_I2S,
    NVIC_INT_FPU,
} tNvic_interrupt;

void nvic_enableInterrupt( tNvic_interrupt interrupt );

#endif // CORE_NVIC_H