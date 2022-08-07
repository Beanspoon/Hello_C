#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#define RW_reg  volatile uint32_t
#define RO_reg  volatile const uint32_t

typedef enum
{
    DISABLED,
    ENABLED
} tBitState;

#endif // TYPES_H