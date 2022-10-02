#include "clock.h"

#include "types.h"

#define CLOCK_BASE_ADDR     0x40000000

/**
 * @brief Clock tasks enum
 *
 */
typedef enum
{
    CLOCK_TASKS_HFCLKSTART,     // Start the high-frequency clock
    CLOCK_TASKS_HFCLKSTOP,      // Stop the high-frequency clock
    CLOCK_TASKS_LFCLKSTART,     // Start the low-frequency clock
    CLOCK_TASKS_LFCLKSTOP,      // Stop the low-frequency clock
    CLOCK_TASKS_CAL,            // Start calibration of the LFRC oscillator
    CLOCK_TASKS_CTSSTART,       // Start calibration timer
    CLOCK_TASKS_CTSTOP,         // Stop calibration timer
    CLOCK_TASKS_MAX
} tClock_tasks;

/**
 * @brief Clock events enum
 *
 */
typedef enum
{
    CLOCK_EVENTS_HFCLKSTARTED,  // High-frequency clock is started
    CLOCK_EVENTS_LFCLKSTARTED,  // Low-frequency clock is started
    CLOCK_EVENTS_DONE,          // Calibration of LFCLK RC oscillator complete
    CLOCK_EVENTS_CTTO,          // Calibration timer timed out
    CLOCK_EVENTS_MAX
} tClock_events;

/**
 * @brief Clock peripheral register map
 *
 */
typedef struct
{
    RW_reg      TASKS[CLOCK_TASKS_MAX];         // 0x000-018 Tasks registers
    RO_reg      UNUSED_A[0x39];
    RW_reg      EVENTS[CLOCK_EVENTS_MAX];       // 0x100-110 Events registers
    RO_reg      UNUSED_B[0x7C];

} tClock_regMap;