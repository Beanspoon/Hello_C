#include "radio_ctrl.h"

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

void radio_setTxPacket( const void * const payload, const uint8_t length )
{
    tRadio_context *pContext = getContext();
    pContext->txPacket.length = length;
    memcpy( &(pContext->txPacket.payload), payload, length );
}