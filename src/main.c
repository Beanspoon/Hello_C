#include "core_ctrl.h"
#include "radio_ctrl.h"

#include "config.h"

#include <stdint-gcc.h>

void main( void )
{
    systick_init( config.systick_frequency, config.core_clock_frequency );

    // Set up radio
    radioCtrl_init();

    uint8_t packet[] = { 0x55, 0x55, 'H', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 0x55, 0x55 };
    radioCtrl_setTxPacket( packet, sizeof(packet) );

    while(1)
    {

    }
}
