#include "rx_core_ctrl.h"
#include "rx_radio_ctrl.h"
#include "clock_ctrl.h"
#include "gpio.h"

#include "config.h"

#include <stdint-gcc.h>

void packetCallback( const uint8_t * const pPacket, const uint8_t packetLength )
{
    if( packetLength == 1u )
    {
        tGpio_pinState led0State = *pPacket & 1u;
        tGpio_pinState led1State = (*pPacket & 2u) >> 1u;

        gpio_writePin( LED0, led0State );
        gpio_writePin( LED1, led1State );
    }
}

void main( void )
{
    systick_init( CONFIG_SYSTICK_FREQUENCY_HZ, CONFIG_CORE_CLOCK_FREQUENCY_HZ );

    clockCtrl_init();

    // Set up radio
    radioCtrl_init();

    tGpio_pinCnfReg pinConfig =
    {
        .DIR = GPIO_DIR_OUTPUT,
        .INPUT_BUFFER = GPIO_INBUF_DISCONNECT,
        .PULL = GPIO_PULL_DISABLED,
        .DRIVE = GPIO_DRIVE_S0S1,
        .SENSE = GPIO_SENSE_DISABLED
    };
    gpio_configurePin( LED0, &pinConfig );
    gpio_writePin( LED0, HIGH );
    gpio_configurePin( LED1, &pinConfig );
    gpio_writePin( LED1, HIGH );

    while( !clockCtrl_isXtalRunning() ) { }

    radioCtrl_waitForPacket( packetCallback );

    while(1)
    {

    }
}
