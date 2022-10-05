#include "core_systick.h"

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
    RO_reg  CSR_COUNTFLAG   : 1;    // Bit[16] Indicates if counter has reached 0 since last read of this register; 0: false, 1: true
    RW_reg                  : 0;
} tSystick_csrReg;

/**
 * @brief Systick calibration value register
 *
 */
typedef struct
{
    RO_reg  CALIB_TENMS     : 24;   // Bit[0-23] Optionally holds a reload value to be used for 10 ms (100 Hz) timing, subject to skew errors
    RO_reg                  : 5;
    RO_reg  CALIB_SKEW      : 1;    // Bit[30] Indicates whether the CALIB_TENMS value is exact; 0: exact, 1: inexact
    RO_reg  CALIB_NOREF     : 1;    // Bit[31] Indicates whether the external reference clock is defined; 0: implemented, 1: not implemented
} tSystick_calibReg;

/**
 * @brief Systick register map
 *
 */
typedef struct
{
    tSystick_csrReg     SYST_CSR;   // 0x00 Control and status register
    RW_reg              SYST_RVR;   // 0x04 Reload value register
    RW_reg              SYST_CVR;   // 0x08 Current value register
    tSystick_calibReg   SYST_CALIB; // 0x0C Calibration value register
} tSystick_regMap;

#define CORE_SYSTICK    (*((volatile tSystick_regMap *) CORE_SYSTICK_BASE_ADDR))

#define TENMS_FREQUENCY 100u    // 10 ms periodicity == 100 Hz

void systick_init( const uint16_t tickFrequency, const uint32_t clockFrequency )
{
    // If there is a reference clock (NOREF==0), use it (CSR_CLKSOURCE==0)
    // Otherwise, CSR_CLKSOURCE is forced to 1 anyway
    CORE_SYSTICK.SYST_CSR.CSR_CLKSOURCE = CORE_SYSTICK.SYST_CALIB.CALIB_NOREF;

    // Set up reload value register
    if( CORE_SYSTICK.SYST_CALIB.CALIB_TENMS != 0u )
    {
        uint16_t frequencyCoeff = TENMS_FREQUENCY / tickFrequency;
        CORE_SYSTICK.SYST_RVR = CORE_SYSTICK.SYST_CALIB.CALIB_TENMS * frequencyCoeff;
    }
    else
    {
        CORE_SYSTICK.SYST_RVR = clockFrequency / tickFrequency;
    }

    CORE_SYSTICK.SYST_CSR.CSR_TICKINT = ENABLED;    // Enable systick interrupt
    CORE_SYSTICK.SYST_CVR = 0u; // Clear the current value register (reset)
    (volatile void)CORE_SYSTICK.SYST_CSR.CSR_COUNTFLAG;  // Read the countflag to reset

    CORE_SYSTICK.SYST_CSR.CSR_SYST_EN = ENABLED;    // Enable systick
}

void systick_busyWait( uint32_t delay_ms )
{
    while( delay_ms > 0u )
    {
        if( CORE_SYSTICK.SYST_CSR.CSR_COUNTFLAG )
        {
            --delay_ms;
        }
    }
}