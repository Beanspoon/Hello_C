#include "hal_gpio.h"

tGpio_status gpio_configurePin( const uint8_t pin, const tGpio_pinConfig* const config )
{
    // Check for invalid parameter values
    if( pin > GPIO_MAXPIN )
    {
        return GPIO_STATUS_INVALID;
    }

    if( GPIO_DIR_INPUT == config->direction )
    {
        GPIO.PINCNF[pin]
    }
}
