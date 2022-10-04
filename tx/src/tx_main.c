#include "tx_core_ctrl.h"
#include "tx_radio_ctrl.h"
#include "tx_clock_ctrl.h"

#include "config.h"

#include <stdint-gcc.h>

void main( void )
{
    systick_init( CONFIG_SYSTICK_FREQUENCY_HZ, CONFIG_CORE_CLOCK_FREQUENCY_HZ );

    clockCtrl_init();

    // Set up radio
    radioCtrl_init();

    uint8_t packet[] = { 0x55, 0x55, 'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', 0x00, 0x55, 0x55 };
    uint8_t counter = 0u;

    while(1)
    {
        packet[13] = counter;
        radioCtrl_transmitPacket( packet, sizeof(packet) );
        systick_busyWait( CONFIG_TRANSMIT_INTERVAL_MS );
        ++counter;
    }
}
