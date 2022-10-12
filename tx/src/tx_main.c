#include "tx_core_ctrl.h"
#include "tx_radio_ctrl.h"
#include "gpio.h"
#include "clock_ctrl.h"

#include "config.h"
#include "types.h"

#include <stdint-gcc.h>

void main( void )
{
    systick_init( CONFIG_SYSTICK_FREQUENCY_HZ, CONFIG_CORE_CLOCK_FREQUENCY_HZ );

    clockCtrl_init();

    // Set up radio
    radioCtrl_init();

    tGpio_pinCnfReg buttonConfig =
    {
        .DIR = GPIO_DIR_INPUT,
        .INPUT_BUFFER = GPIO_INBUF_CONNECT,
        .PULL = GPIO_PULL_UP,
    };

    gpio_configurePin( BTN0, &buttonConfig );
    gpio_configurePin( BTN1, &buttonConfig );

    uint8_t prevGpioState, newGpioState = 0u;
    while(1)
    {
        newGpioState = (gpio_readPin(BTN0)) | (gpio_readPin(BTN1) << 1u);
        if( newGpioState != prevGpioState )
        {
            radioCtrl_transmitPacket( &newGpioState, sizeof(newGpioState) );
            prevGpioState = newGpioState;
        }
        systick_busyWait( CONFIG_UPDATE_INTERVAL );
    }
}
