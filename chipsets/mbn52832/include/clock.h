#ifndef CLOCK_H
#define CLOCK_H

/**
 * @brief Clock state enum
 *
 */
typedef enum
{
    CLOCK_STATE_NOT_RUNNING,
    CLOCK_STATE_RUNNING
} tClock_state;

/**
 * @brief Clock source enum
 *
 */
typedef enum
{
    CLOCK_SOURCE_INTERNAL,  // Internal RC oscillator
    CLOCK_SOURCE_CRYSTAL,   // Crystal oscillator
    CLOCK_SOURCE_SYNTH,     // 32.768 kHz synthesised from high-frquency clock (only applicable to low-frequency clock)
} tClock_source;

/**
 * @brief Sends the task to start the high-frequency crystal oscillator
 * The CLOCK_EVENTS_HFCLKSTART event will be generated when the high-frequency oscillator has started
 */
void clock_startHFClock( void );

/**
 * @brief Returns the state of the high-frequency clock
 *
 * @return tClock_state indicating whether or not the high-frequency crystal oscillator is running
 */
tClock_state clock_getHFClockState();

/**
 * @brief Returns the current source for the high-frequency clock
 *
 * @return tClock_source indicating the clock source. Can only be CLOCK_SOURCE_INTERNAL or CLOCK_SOURCE_CRYSTAL
 */
tClock_source clock_getHFClockSource();

#endif // CLOCK_H
