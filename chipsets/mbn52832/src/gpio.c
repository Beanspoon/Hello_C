#include "gpio.h"

#define GPIO_BASE_ADDR  0x50000000

/**
 * @brief Definition of GPIO register map
 *
 */
typedef struct
{
    RO_reg          RESERVED_A[0x141];
    RW_reg          OUT;           // 0x504 Write GPIO port
    RW_reg          OUTSET;        // 0x508 Set individual bits in GPIO port
    RW_reg          OUTCLR;        // 0x50C Clear individual bits in GPIO port
    RO_reg          IN;            // 0x510 Read GPIO port
    RW_reg          DIR;           // 0x514 Direction of GPIO pins
    RW_reg          DIRSET;        // 0x518 Direction set register (sets pin to output)
    RW_reg          DIRCLR;        // 0x51C Direction clear register (sets pin to input)
    RW_reg          LATCH;         // 0x520 Latch register indicating which GPIO pins have met criteria set in PIN_CNF[n].SENSE. Write '1' to clear
    RW_reg          DETECTMODE;    // 0x524 Select between default DETECT signal behaviour (0) and LDETECT mode (1)
    RO_reg          RESERVED_B[0x77];
    tGpio_pinCnfReg PINCNF[32];    // 0x700-77C Configuration of GPIO pins
} tGpio_regMap;

#define GPIO    (*((volatile tGpio_regMap *) GPIO_BASE_ADDR))

#define GPIO_PINMASK(pin)   (1u << pin)

tGpio_status gpio_configurePin( const tGpio_pin pin, const tGpio_pinCnfReg *pPinConfig )
{
    tGpio_status retStatus = GPIO_STATUS_INVALID;

    if( pin > GPIO_PIN_MAX )
    {
        GPIO.PINCNF[pin] = *pPinConfig;
        retStatus = GPIO_STATUS_OK;
    }
    return retStatus;
}

tGpio_pinState gpio_readPin( const tGpio_pin pin )
{
    RW_reg pinValue = GPIO.IN & GPIO_PINMASK(pin);
    return (tGpio_pinState)pinValue;
}

void gpio_writePin( const tGpio_pin pin, const tGpio_pinState state )
{
    RW_reg *reg = ( state == HIGH ) ? &GPIO.OUTSET : &GPIO.OUTCLR;
    *reg = GPIO_PINMASK( pin );
}