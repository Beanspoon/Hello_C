#ifndef CORE_M4_H
#define CORE_M4_H

#include "types.h"

/************************************************
 * SYSTICK
 * *********************************************/

#define CORE_SYSTICK_BASE_ADDR  0xE000E010

/**
 * @brief Systick control and status register
 * 
 */
typedef struct
{
    RW_reg  CSR_SYST_EN     : 1;    // Bit[0] Status of the counter; 0: disabled, 1: enabled
    RW_reg  CSR_TICKINT     : 1;    // Bit[1] Interrupt status on counter=0; 0: disabled, 1: enabled
    RW_reg  CSR_CLKSOURCE   : 1;    // Bit[2] Systick clock source; 0: external, 1: processor
    const uint16_t          : 0;
    RW_reg  CSR_COUNTFLAG   : 1;    // Bit[16] Indicates if counter has reached 0 since last read of this register; 0: false, 1: true
    RW_reg                  : 0;
} tSystick_csrReg;

/**
 * @brief Systick register map
 * 
 */
typedef struct
{
    tSystick_csrReg SYST_CSR;   // 0x00 Control and status register
    RW_reg          SYST_RVR;   // 0x04 Reload value register
    RW_reg          SYST_CVR;   // 0x08 Current value register
    RO_reg          SYST_CALIB; // 0x0C Calibration value register
} tCore_systickRegmap;

/************************************************
 * NVIC
 * *********************************************/

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
} tVectorTable;


#endif // CORE_M4_H