#ifndef CORE_SYSTICK_H
#define CORE_SYSTICK_H

#include "types.h"

/**
 * @brief Initialises the systick
 *
 * @param[in] tickFrequency Frequency of systick ticks
 * @param[in] clockFrequency Frequency of the clock (used if no calibration value exists)
 */
void systick_init( const uint16_t tickFrequency, const uint32_t clockFrequency );

/**
 * @brief Holds execuction for <delay_ms> miliseconds
 *
 * @param[in] delay_Ms Time to delay
 */
void systick_busyWait( uint32_t delay_ms );

#endif // CORE_SYSTICK_H
