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

static void radioCtrl_readyHandler( void )
{

}

static void radioCtrl_errorHandler( const char errorString[] )
{
    while (1)
    {
        // Radio hit fatal error!
    }
}

void radioCtrl_init( void )
{
    tRadio_packetConfig packetConfig =
    {
        .lengthFieldLen = 8u,
        .maxPayloadLen = 255u,
        .baseAddrLen = RADIO_4_BYTE_BASE_ADDR,
    };
    tRadio_retVal initRetVal = radio_setPacketConfiguration( packetConfig );

    if( initRetVal != RADIO_OK )
    {
        radioCtrl_errorHandler( "Init failure!\n" );
    }

    tRadio_event_handler_tableElement eventTable[] = {
        { RADIO_EVENTS_READY, radioCtrl_readyHandler }
    };
    radio_enableEvents( eventTable );

    radio_setPrimaryAddress( 0x12, 0xdeadbeef );
}

void radioCtrl_setTxPacket( const void *const payload, const uint8_t length )
{
    tRadioCtrl_context *pContext = getContext();
    pContext->txPacket.length = length;
    memcpy( &(pContext->txPacket.payload), payload, length );
}