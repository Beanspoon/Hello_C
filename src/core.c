#include "core.h"

#define TENMS_FREQUENCY 100u    // 10 ms periodicity == 100 Hz

typedef struct
{
    uint32_t    tick_count;
} tCore_context;

static tCore_context* getContext( void )
{
    static tCore_context context = { 0 };
    return &context;
}

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

    CORE_SYSTICK.SYST_CSR.CSR_TICKINT = ENABLED;    // Enable systick interrupt
    CORE_SYSTICK.SYST_CVR = 0u; // Clear the current value register (reset)
    (volatile void)CORE_SYSTICK.SYST_CSR.CSR_COUNTFLAG;  // Read the countflag to reset

    CORE_SYSTICK.SYST_CSR.CSR_SYST_EN = ENABLED;    // Enable systick
}

void core_busyWait( uint32_t delay_ms )
{
    while( delay_ms > 0u )
    {
        if( CORE_SYSTICK.SYST_CSR.CSR_COUNTFLAG )
        {
            --delay_ms;
        }
    }
}

void Systick_handler( void )
{
    tCore_context *pContext = getContext();
    ++(pContext->tick_count);
}