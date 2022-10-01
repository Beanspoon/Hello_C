#include "rx_radio_ctrl.h"

#include "utils.h"

extern uint32_t __estack;

/**
 * @brief Radio context
 *
 */
typedef struct
{
    tRadio_packet   txPacket;
    tRadio_packet * pRxPacket;
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

static void radioCtrl_endHandler( void )
{
    tRadioCtrl_context *pContext = getContext();

    if( radio_start() != RADIO_OK )
    {
        radioCtrl_errorHandler( "Radio RX error\n" );
    }
}

static void radioCtrl_addressHandler( void )
{
    static uint32_t counter = 0;
    ++counter;
}

void radioCtrl_init( void )
{
    radio_init();

    radio_setMode( RADIO_MODE_BLE1MBIT );

    radio_setWhiteningIV( 37u );    // Use channel number for data whitening (37 is default frequency)

    radio_setPrimaryAddress( 0x00, 0x00 );

    tRadio_logAddr addresses[] = { RADIO_LOGADDR_PRIMARY };
    radio_setRxAddresses( addresses, 1u );

    tRadio_packetConfig packetConfig =
    {
        .s0Len = 1u,
        .s1Len = 2u,
        .lengthFieldLen = 6u,
        .maxPayloadLen = 37u,
        .staticLen = 0u,
        .baseAddrLen = RADIO_3_BYTE_BASE_ADDR,
        .endian = RADIO_LITTLE_ENDIAN,
        .dataWhitening = ENABLED
    };
    tRadio_retVal initRetVal = radio_setPacketConfiguration( &packetConfig );

    tRadio_crcConfig crcConfig =
    {
        .crcLength = RADIO_3_BYTE_CRC,
        .addressBehaviour   = RADIO_CRC_SKIP_ADDRESS,
        .initValue          = 0x555555,
        .polyArray          = { 10u, 9u, 6u, 4u, 3u, 1u, 0u }
    };
    initRetVal |= radio_configureCrc( &crcConfig );

    if( initRetVal != RADIO_OK )
    {
        radioCtrl_errorHandler( "Init failure!\n" );
    }

    tRadio_event_handler_tableElement eventTable[] = {
        { RADIO_EVENTS_END, radioCtrl_endHandler },
        { RADIO_EVENTS_ADDRESS, radioCtrl_addressHandler },
    };
    radio_enableEvents( eventTable );

    tRadio_shorts shortsToEnable[] = { RADIO_SHORTS_READY_START };
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

void radioCtrl_waitForPacket()
{
    tRadioCtrl_context *pContext = getContext();
    pContext->pRxPacket = &__estack;

    radio_setPacketAddress( pContext->pRxPacket );

    if( RADIO_OK != radio_enableRxMode() )
    {
        radioCtrl_errorHandler( "Invalid radio state\n" );
    }
}
