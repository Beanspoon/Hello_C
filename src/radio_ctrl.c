#include "radio_ctrl.h"

#include "utils.h"

/**
 * @brief Radio context
 * 
 */
typedef struct
{
    tRadio_packet   txPacket;
} tRadioCtrl_context;

/**
 * @brief Get a pointer to the radio context
 * 
 * @return pointer to the context
 */
static tRadioCtrl_context *getContext( void )
{
    static tRadioCtrl_context radioCtrl_context = { 0 };
    return &radioCtrl_context;
}

void radio_setTxPacket( const void *const payload, const uint8_t length )
{
    tRadioCtrl_context *pContext = getContext();
    pContext->txPacket.length = length;
    memcpy( &(pContext->txPacket.payload), payload, length );
}