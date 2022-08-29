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

#define NVIC_BASE_ADDR  0xE000E004

typedef struct
{
    RO_reg  ICTR;               // 0x004 Interrupt controller type register
    RO_reg  RESERVED_A[0x3E];
    RW_reg  ISER[8];            // 0x100-11C Interrupt set-enable registers
    RO_reg  RESERVED_B[0x18];
    RW_reg  ICER[8];            // 0x180-19C Interrupt clear-enable registers
    RW_reg  ISPR[8];            // 0x200-21C Interrupt set-pending registers
    RO_reg  RESERVED_C[0x18];
    RW_reg  ICPR[8];            // 0x280-29C Interrupt clear-pending registers
    RO_reg  IABR[8];            // 0x300-31C Interrupt active bit register
    RO_reg  RESERVED_D[0x38];
    RW_reg  IPR[60];            // 0x400-4EC Interrupt priority registers
} tCore_nvicRegmap;

#define NVIC        (*((tCore_nvicRegmap *)NVIC_BASE_ADDR))

#endif // CORE_NVIC_H