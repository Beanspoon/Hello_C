#include "utils.h"

#define ARCH_SIZE   sizeof(unsigned int)

void memcpy( void * pDest, const void * pSource, uint32_t length )
{
    // Fast copy using full register size
    while( length >= ARCH_SIZE )
    {
        *(unsigned int *)pDest = *(unsigned int *)pSource;
        pSource += ARCH_SIZE;
        pDest += ARCH_SIZE;
        length -= ARCH_SIZE;
    }

    // Slow copy for remaining bytes
    while( length > 0u )
    {
        *(uint8_t *)pDest = *(uint8_t *)pSource;
        ++pSource;
        ++pDest;
        --length;
    }
}