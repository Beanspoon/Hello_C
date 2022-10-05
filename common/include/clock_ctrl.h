#ifndef CLOCK_CTRL_H
#define CLOCK_CTRL_H

#include <stdbool.h>

/**
 * @brief Initialise the clock peripheral
 *
 */
void clockCtrl_init( void );

/**
 * @brief Determines whether the high-frequency clock is running
 *
 * @return true if clock is running
 * @return false is clock is not running
 */
bool clockCtrl_isHFClockRunning( void );

/**
 * @brief Determines whether the crystal oscillator is the source for the high-frequency clock
 *
 * @return true if oscillator is running
 * @return false if oscillator is not running
 */
bool clockCtrl_isXtalRunning( void );

#endif
