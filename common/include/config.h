#ifndef CONFIG_H
#define CONFIG_H

#include "gpio.h"

#include <stdint-gcc.h>

// SYSTICK
#define CONFIG_SYSTICK_FREQUENCY_HZ     1000u       // 1 kHz = 1 ms period
#define CONFIG_CORE_CLOCK_FREQUENCY_HZ  64000000u   // 64 MHz

//GPIO
#define BTN0    GPIO_PIN13
#define BTN1    GPIO_PIN14
#define LED0    GPIO_PIN17
#define LED1    GPIO_PIN18

#define CONFIG_UPDATE_INTERVAL  20u

#endif // CONFIG_H
