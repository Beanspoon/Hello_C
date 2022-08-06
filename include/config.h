#ifndef CONFIG_H
#define CONFIG_H

#include "types.h"

typedef struct
{
    uint32_t systick_reload_value   : 24;   // Alternative reload value for systick
} tConfig;

#endif // CONFIG_H
