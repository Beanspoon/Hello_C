#include "core.h"
#include "gpio.h"

#include "types.h"

#include "config.h"

typedef struct
{
    uint32_t    tick_count;
} tMain_context;

static tMain_context* main_getContext( void );

#define LED_PIN 17u

void main( void )
{
    core_systickInit( config.systick_frequency, config.core_clock_frequency );

    tGpio_pinCnfReg pinConfig = {
        .DIR = GPIO_DIR_OUTPUT,
        .DRIVE = GPIO_DRIVE_S0S1
    };

    GPIO.OUTSET = GPIO_PINMASK(LED_PIN);
    GPIO.PINCNF[LED_PIN] = pinConfig;

    while(1)
    {
        GPIO.OUTCLR = GPIO_PINMASK(LED_PIN);
        core_busyWait( 1000u );
        GPIO.OUTSET = GPIO_PINMASK(LED_PIN);
        core_busyWait( 1000u );
    }
}

void Systick_handler( void )
{
    tMain_context *pContext = main_getContext();
    ++(pContext->tick_count);
}

static tMain_context* main_getContext( void )
{
    static tMain_context context = { 0 };
    return &context;
}
