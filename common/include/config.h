#ifndef CONFIG_H
#define CONFIG_H

#include <stdint-gcc.h>

// SYSTICK
#define CONFIG_SYSTICK_FREQUENCY_HZ     1000u       // 1 kHz = 1 ms period
#define CONFIG_CORE_CLOCK_FREQUENCY_HZ  64000000u   // 64 MHz

// RADIO
#define CONFIG_TRANSMIT_INTERVAL_MS    1000u

#endif // CONFIG_H
