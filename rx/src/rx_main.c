#include "rx_core_ctrl.h"
#include "rx_radio_ctrl.h"

#include "rx_config.h"

#include <stdint-gcc.h>

void messageReceivedCallback( void )
{
    while(1) { }
}

void main( void )
{
    systick_init( config.systick_frequency, config.core_clock_frequency );

    // Set up radio
    radioCtrl_init();

    radioCtrl_waitForPacket();

    while(1)
    {

    }
}
