#ifndef CONFIG_H
#define CONFIG_H

#include "types.h"

typedef struct
{
    uint16_t    systick_frequency;
    uint32_t    core_clock_frequency;
} tConfig;

#endif // CONFIG_H
