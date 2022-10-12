#include "tx_radio_ctrl.h"

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


static void radioCtrl_errorHandler( const char errorString[] )
{
    while (1)
    {
        // Radio hit fatal error!
    }
}

static void radioCtrl_readyHandler( void )
{
    tRadioCtrl_context *pContext = getContext();
    radio_setPacketAddress( &pContext->txPacket );
    radio_setTxAddress( RADIO_LOGADDR_PRIMARY );

    if( radio_start() != RADIO_OK )
    {
        radioCtrl_errorHandler( "Radio TX error\n" );
    }
}

void radioCtrl_init( void )
{
    radio_init();

    // radio_setMode( RADIO_MODE_BLE1MBIT );
    radio_configureFrequency( 0u, true );

    radio_setWhiteningIV( 37u );

    radio_setPrimaryAddress( 0xde, 0xadbeef00 );

    radio_setTxAddress( RADIO_LOGADDR_PRIMARY );

    tRadio_packetConfig packetConfig =
    {
        .s0Len          = 1u,
        .s1Len          = 2u,
        .lengthFieldLen = 6u,
        .maxPayloadLen  = 37u,
        .staticLen      = 0u,
        .baseAddrLen    = RADIO_3_BYTE_BASE_ADDR,
        .endian         = RADIO_LITTLE_ENDIAN,
        .dataWhitening  = ENABLED
    };
    tRadio_retVal initRetVal = radio_setPacketConfiguration( &packetConfig );

    tRadio_crcConfig crcConfig =
    {
        .crcLength = RADIO_3_BYTE_CRC,
        .addressBehaviour   = RADIO_CRC_INCLUDE_ADDRESS,
        .initValue          = 0x555555,
        .polyArray          = { 10u, 9u, 6u, 4u, 3u, 1u, 0u }
    };
    initRetVal |= radio_configureCrc( &crcConfig );

    if( initRetVal != RADIO_OK )
    {
        radioCtrl_errorHandler( "Init failure!\n" );
    }

    tRadio_event_handler_tableElement eventTable[] = {
        { RADIO_EVENTS_READY, radioCtrl_readyHandler }
    };
    radio_enableEvents( eventTable );

    tRadio_shorts shortsToEnable[] = { RADIO_SHORTS_END_DISABLE };
    radio_enableShorts( shortsToEnable );
}

void radioCtrl_transmitPacket( const void * const pPayload, const uint8_t payloadLen )
{
    tRadioCtrl_context *pContext = getContext();
    pContext->txPacket.length = payloadLen;
    memcpy( &(pContext->txPacket.payload), pPayload, payloadLen );

    if( RADIO_OK != radio_enableTxMode() )
    {
        radioCtrl_errorHandler( "Invalid radio state\n" );
    }
}
