#ifndef RADIO_CTRL_H
#define RADIO_CTRL_H

#include "radio.h"

#include "types.h"

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
 * @brief Sets the contents of the radio packet to be transmitted
 * 
 * @param[in] payload The desired payload for the packet
 * @param[in] length The length of the payload
 */
void radio_setTxPacket( const void * const payload, const uint8_t length );

#endif // RADIO_CTRL_H