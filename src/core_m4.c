#include "core_m4.h"

#define TENMS_FREQUENCY 100u    // 10 ms periodicity == 100 Hz

void core_systickInit( const uint16_t tickFrequency, const uint32_t clockFrequency )
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

    CORE_SYSTICK.SYST_CSR.CSR_TICKINT = ENABLED;
}