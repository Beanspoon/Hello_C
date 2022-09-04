#ifndef RADIO_H
#define RADIO_H

#include "types.h"

typedef enum
{
    RADIO_SHORTS_READY_START,
    RADIO_SHORTS_END_DISABLE,
    RADIO_SHORTS_DISABLED_TXEN,
    RADIO_SHORTS_DISABLED_RXEN,
    RADIO_SHORTS_ADDRESS_RSSISTART,
    RADIO_SHORTS_END_START,
    RADIO_SHORTS_ADDRESS_BCSTART,
    RADIO_SHORTS_DISABLED_RSSISTOP = 8u,
    RADIO_SHORTS_MAX
} tRadio_shorts;

typedef enum
{
    EVENTS_READY    = 0,    // Radio has ramped up and is ready for tx or rx
    EVENTS_ADDRESS  = 1,    // Address transmitted or received
    EVENTS_PAYLOAD  = 2,    // Payload transmitted or recieved
    EVENTS_END      = 3,    // Tx or rx complete
    EVENTS_DISABLED = 4,    // Radio has been disabled
    EVENTS_DEVMATCH = 5,    // Address match occurred on the last recevied packet
    EVENTS_DEVMISS  = 6,    // No address match occurred on the last recevied packet
    EVENTS_RSSIEND  = 7,    // RSSI sampling is complete

    EVENTS_BCMATCH  = 10,   // Bit counter reached bit count match value

    EVENTS_CRCOK    = 12,   // Packet recieved with CRC OK
    EVENTS_CRCERROR = 13,   // Packet recieved with CRC error
    EVENTS_MAX
} tRadio_events;

typedef void (*tRadio_eventHandler)( void );

typedef struct
{
    tRadio_events       event;
    tRadio_eventHandler handler;
} tRadio_event_handler_tableElement;

/**
 * @brief Initialise the radio peripheral
 * 
 */
void radio_init( void );

void (radio_enableShorts)( const tRadio_shorts shorts[], const uint8_t arrayLen );
/**
 * @brief Enables radio shortcuts between tasks and events
 * 
 * @param[in] shorts Shortcuts to be enabled
 */
#define radio_enableShorts( shortsArray )   radio_enableShorts( shortsArray, sizeof(shorts)/sizeof(shorts[0]) )

#endif // RADIO_H
