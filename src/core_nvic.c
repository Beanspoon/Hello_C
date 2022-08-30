#include "core_nvic.h"

void nvic_enableInterrupt( tNvic_interrupt interrupt )
{
    uint8_t registerNumber = interrupt / 32u;
    uint8_t bitNumber = interrupt % 32u;

    NVIC.ISER[registerNumber] = (1u << bitNumber);
}