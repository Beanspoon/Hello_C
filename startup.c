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

__attribute__ ((section(".vectors")))
const unsigned int *vectorTable[] = 
{
    (unsigned int *)(&__estack),    // Stack pointer
    (unsigned int *)Reset_handler,
    (unsigned int *)NMI_handler,
    (unsigned int *)Hardfault_handler,
    (unsigned int *)MemMgmtFault_handler,
    (unsigned int *)BusFault_handler,
    (unsigned int *)UsageFault_handler,
};

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

void NMI_handler( void )
{
    while(1) {}
}

void Hardfault_handler( void )
{
    while(1) {}
}

void MemMgmtFault_handler( void )
{
    while(1) {}
}

void BusFault_handler( void )
{
    while (1) {}
}

void UsageFault_handler( void )
{
    while (1) {}
}
