#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "types.h"

#define GPIO_BASE_ADDR  0x50000000

typedef enum
{
    GPIO_DIR_INPUT,
    GPIO_DIR_OUTPUT
} tGpio_dir;

typedef enum
{
    GPIO_INBUF_CONNECT,
    GPIO_INBUF_DISCONNECT
} tGpio_inBuf;

typedef enum
{
    GPIO_PULL_DISABLED,
    GPIO_PULL_DOWN,
    GPIO_PULL_UP
} tGpio_pull;

typedef enum
{
    GPIO_DRIVE_S0S1,    // Standard '0', standard '1'
    GPIO_DRIVE_H0S1,    // High drive '0', standard '1'
    GPIO_DRIVE_S0H1,    // Standard '0', high drive '1'
    GPIO_DRIVE_H0H1,    // High drive '0', high drive '1'
    GPIO_DRIVE_D0S1,    // Disconnect '0', standard '1' (wired-or)
    GPIO_DRIVE_D0H1,    // Disconnect '0', high drive '1' (wired-or)
    GPIO_DRIVE_S0D1,    // Standard '0', disconnect '1' (wired-and)
    GPIO_DRIVE_H0D1,    // High drive '0', disconnect '1' (wired-and)
} tGpio_drive;

typedef enum
{
    GIPO_SENSE_DISABLED,    // Pin sensing mechanism disabled
    GPIO_SENSE_HIGH,        // Sense for high level
    GPIO_SENSE_LOW          // Sense for low level
} tGpio_sense;

typedef struct
{
    tGpio_dir       DIR             : 1;    // Bit[0]   Pin direction
    tGpio_inBuf     INPUT_BUFFER    : 1;    // Bit[1]   Connect or disconnect input buffer
    tGpio_pull      PULL            : 2;    // Bit[2-3] Pin pull configuration
    const uint8_t                   : 0;
    tGpio_drive     DRIVE           : 3;    // Bit[8-10]    Drive configuration
    const uint8_t                   : 0;
    tGpio_sense     SENSE           : 2;    // Bit[16-17]   Pin sensing mechanism
    RO_reg                          : 0;
} tGpio_pinCnfReg;

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

typedef enum
{
    LOW,
    HIGH
} tGpio_pinState;

typedef struct
{
    tGpio_dir       direction;      // Pin direction
    tGpio_inBuf     inputBuffer;    // Input buffer configuration
    tGpio_pull      pull;           // Pin pull direction
    tGpio_drive     drive;          // Pin drive configuration
    tGpio_sense     sense;          // Sense mechanism configuration
    tGpio_pinState  initState;      // Initial state for the pin
} tGpio_pinConfig;

#define GPIO_PINMASK(pin)   (1u << pin)

/**
 * @brief Configure a pin
 *
 * @param[in] pin The pin to be configured
 * @param[in] config Struct detailing the configuration of the pin
 */
void gpio_configurePin( const uint8_t pin, const tGpio_pinConfig* const config );

/**
 * @brief Set pin to state
 *
 * @param[in] pin The pin to set
 * @param[in] state The state to set
 */
void gpio_writePin( const uint8_t pin, const tGpio_pinState state );

#endif // HAL_GPIO_H
