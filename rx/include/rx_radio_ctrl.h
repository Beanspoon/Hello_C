#ifndef RADIO_CTRL_H
#define RADIO_CTRL_H

#include "radio.h"

#include "config.h"

#include <stdint-gcc.h>

/**
 * @brief Radio packet structure
 *
 */
typedef struct __attribute__((packed))
{
    uint8_t length;
    uint8_t payload[MAX_PACKET_PAYLOAD_SIZE];
} tRadioCtrl_packet;

/**
 * @brief Function pointer for packet handler function
 *
 */
typedef void (*tRadioCtrl_packetHandler)( const uint8_t * const pPacket, const uint8_t packetLength);

/**
 * @brief Initialise the radio
 *
 */
void radioCtrl_init( void );

/**
 * @brief Send a packet
 *
 * @param pPayload payload of the packet to be sent
 * @param payloadLen length of the payload
 */
void radioCtrl_transmitPacket( const void * const pPayload, const uint8_t payloadLen );

void radioCtrl_waitForPacket( const tRadioCtrl_packetHandler callback );

#endif // RADIO_CTRL_H