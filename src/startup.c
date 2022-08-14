#include "core.h"

#include <stddef.h>

extern unsigned int __srodata;
extern unsigned int __erodata;
extern unsigned int __sbss;
extern unsigned int __ebss;
extern unsigned int __sdata;
extern unsigned int __edata;
extern unsigned int __sstack;
extern unsigned int __estack;

// Forward-define main
void main( void );

__attribute__((weak))
void Reset_handler( void )
{
    // Initialise zeroed statics
    unsigned int *pBss = &__sbss;
    while( pBss < &__ebss )
    {
        *pBss = 0;
        ++pBss;
    }

    // Copy statics from flash to ram section
    unsigned int *pInitVals = &__erodata;
    unsigned int *pData = &__sdata;
    while( pData < &__edata)
    {
        *pData = *pInitVals;
        ++pData;
        ++pInitVals;
    }

    main();

    while(1) {}
}

__attribute__((weak))
void NMI_handler( void )
{
    while(1) {}
}

__attribute__((weak))
void Hardfault_handler( void )
{
    while(1) {}
}

__attribute__((weak))
void MemMgmtFault_handler( void )
{
    while(1) {}
}

__attribute__((weak))
void BusFault_handler( void )
{
    while (1) {}
}

__attribute__((weak))
void UsageFault_handler( void )
{
    while (1) {}
}

__attribute__((weak))
void Systick_handler( void ) { }

// Vector table
__attribute__ ((section(".vectors")))
const tVectorTable vectorTable =
{
    // Stack pointer
    .pStack                 = (void *)(&__estack),

    // Exception handlers
    .pfReset_handler        = (void *)Reset_handler,
    .pfNMI_handler          = (void *)NMI_handler,
    .pfHardfault_handler    = (void *)Hardfault_handler,
    .pfMemMgmtFault_handler = (void *)MemMgmtFault_handler,
    .pfBusFault_handler     = (void *)BusFault_handler,
    .pfUsageFault_handler   = (void *)UsageFault_handler,
    .pfSVCall_handler       = NULL,
    .pfPendSV_handler       = NULL,
    .pfSystick_handler      = (void *)Systick_handler,
};
