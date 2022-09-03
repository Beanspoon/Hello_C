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

/**
 * @brief Initialise the radio peripheral
 * 
 */
void radio_init( void );

static void radio_enableShortsFn( const tRadio_shorts shorts[], const uint8_t arrayLen );
/**
 * @brief Enables radio shortcuts between tasks and events
 * 
 * @param[in] shorts Shortcuts to be enabled
 */
#define radio_setShorts( shortsArray )   radio_enableShortsFn( shortsArray, sizeof(shorts)/sizeof(shorts[0]) )

#endif // RADIO_H
