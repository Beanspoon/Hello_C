#include "core_systick.h"
#include "radio.h"

#include "types.h"

#include "config.h"

void main( void )
{
    systick_init( config.systick_frequency, config.core_clock_frequency );

    // Set up radio
    radio_init();

    uint8_t packet[] = { 0x55, 0x55, 'H', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 0x55, 0x55 };
    radio_setTxPacket( packet, sizeof(packet) );

    while(1)
    {

    }
}
