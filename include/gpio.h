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

#endif // GPIO_H
