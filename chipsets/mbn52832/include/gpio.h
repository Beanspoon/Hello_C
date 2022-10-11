#ifndef GPIO_H
#define GPIO_H

#include "types.h"

/**
 * @brief Pin state enum
 *
 */
typedef enum
{
    LOW,
    HIGH
} tGpio_pinState;

/**
 * @brief GPIO operation status enum
 *
 */
typedef enum
{
    GPIO_STATUS_OK,
    GPIO_STATUS_INVALID
} tGpio_status;

/**
 * @brief GPIO pin enum
 *
 */
typedef enum
{
    GPIO_PIN0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7,
    GPIO_PIN8,
    GPIO_PIN9,
    GPIO_PIN10,
    GPIO_PIN11,
    GPIO_PIN12,
    GPIO_PIN13,
    GPIO_PIN14,
    GPIO_PIN15,
    GPIO_PIN16,
    GPIO_PIN17,
    GPIO_PIN18,
    GPIO_PIN19,
    GPIO_PIN20,
    GPIO_PIN21,
    GPIO_PIN22,
    GPIO_PIN23,
    GPIO_PIN24,
    GPIO_PIN25,
    GPIO_PIN26,
    GPIO_PIN27,
    GPIO_PIN28,
    GPIO_PIN29,
    GPIO_PIN30,
    GPIO_PIN31,
    GPIO_PIN_MAX
} tGpio_pin;

/**
 * @brief Pin direction enum
 *
 */
typedef enum
{
    GPIO_DIR_INPUT,
    GPIO_DIR_OUTPUT
} tGpio_dir;

/**
 * @brief Input buffer setting enum
 *
 */
typedef enum
{
    GPIO_INBUF_CONNECT,
    GPIO_INBUF_DISCONNECT
} tGpio_inBuf;

/**
 * @brief Pin pull direction enum (input)
 *
 */
typedef enum
{
    GPIO_PULL_DISABLED,
    GPIO_PULL_DOWN,
    GPIO_PULL_UP = 3
} tGpio_pull;

/**
 * @brief Pin drive configuration enum (output)
 *
 */
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

/**
 * @brief Pin sense configuration enum (input)
 *
 */
typedef enum
{
    GPIO_SENSE_DISABLED,    // Pin sensing mechanism disabled
    GPIO_SENSE_HIGH = 2,    // Sense for high level
    GPIO_SENSE_LOW          // Sense for low level
} tGpio_sense;

/**
 * @brief Definition of pin configuration registers
 *
 */
typedef struct
{
    tGpio_dir       DIR             : 1;    // Bit[0]   Pin direction
    tGpio_inBuf     INPUT_BUFFER    : 1;    // Bit[1]   Connect or disconnect input buffer
    tGpio_pull      PULL            : 2;    // Bit[2-3] Pin pull configuration
    uint8_t                         : 0;
    tGpio_drive     DRIVE           : 3;    // Bit[8-10]    Drive configuration
    uint8_t                         : 0;
    tGpio_sense     SENSE           : 2;    // Bit[16-17]   Pin sensing mechanism
    RW_reg                          : 0;
} tGpio_pinCnfReg;

/**
 * @brief Configure specified pin
 *
 * @param[in] pin the pin to be configured
 * @param[in] pPinConfig structure containing configuration settings
 */
tGpio_status gpio_configurePin( const tGpio_pin pin, const tGpio_pinCnfReg *pPinConfig );

/**
 * @brief Read the state of a pin
 *
 * @param[in] pin the pin to read
 * @return tGpio_pinState giving the state of the pin (LOW/HIGH)
 */
tGpio_pinState gpio_readPin( const tGpio_pin pin );

/**
 * @brief Sets the state of a pin
 *
 * @param[in] pin the pin being set
 * @param[in] state the state the pin is bein set to
 */
void gpio_writePin( const tGpio_pin pin, const tGpio_pinState state );

#endif // GPIO_H
