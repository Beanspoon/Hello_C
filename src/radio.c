#include "radio.h"

#include "core_nvic.h"

/**
 * @brief Radio context
 * 
 */
typedef struct
{
    tRadio_packet   txPacket;
} tRadio_context;

/**
 * @brief Get a pointer to the radio context
 * 
 * @return pointer to the context
 */
static tRadio_context* getContext( void )
{
    static tRadio_context context = { 0 };
    return &context;
}

void radio_init( void )
{
    nvic_enableInterrupt( NVIC_INT_RADIO );
}

void radio_enableShortsFn( const tRadio_shorts shorts[], const uint8_t length )
{
    RW_reg enabledShorts = { 0u };
    for( uint8_t shortIdx = 0u; shortIdx < length; ++shortIdx )
    {
        enabledShorts |= (1u << shorts[shortIdx]);
    }
}

void radio_setTxPacket( const uintptr_t const payload, const uint8_t length )
{
    tRadio_context *pContext = getContext();
    pContext->txPacket.length = length;
    memcpy( &(pContext->txPacket.payload), (void *)payload, length );
}