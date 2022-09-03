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
} tRadio_shorts;

/**
 * @brief Radio packet structure
 * 
 */
typedef struct __attribute__((packed))
{
    uint8_t length;
    uint8_t payload[255];
} tRadio_packet;

/**
 * @brief Initialise the radio peripheral
 * 
 */
void radio_init( void );

/**
 * @brief Enables radio shortcuts between tasks and events
 * 
 * @param[in] shorts Shortcuts to be enabled
 */
void radio_enableShortsFn( const tRadio_shorts shorts[], const uint8_t arrayLen );
#define radio_setShorts( shorts )   radio_setShortsFn( shorts, sizeof(shorts)/sizeof(shorts[0]) )

/**
 * @brief Sets the contents of the radio packet to be transmitted
 * 
 * @param[in] payload The desired payload for the packet
 * @param[in] length The length of the payload
 */
void radio_setTxPacket( const void * const payload, const uint8_t length );

#endif // RADIO_H
