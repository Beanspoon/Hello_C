#include "rx_core_ctrl.h"
#include "rx_radio_ctrl.h"
#include "clock_ctrl.h"

#include "config.h"

#include <stdint-gcc.h>

void messageReceivedCallback( void )
{
    while(1) { }
}

void main( void )
{
    systick_init( CONFIG_SYSTICK_FREQUENCY_HZ, CONFIG_CORE_CLOCK_FREQUENCY_HZ );

    clockCtrl_init();

    // Set up radio
    radioCtrl_init();

    while( !clockCtrl_isXtalRunning() ) { }

    radioCtrl_waitForPacket();

    while(1)
    {

    }
}
