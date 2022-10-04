#include "clock_ctrl.h"

#include "clock.h"

void clockCtrl_init( void )
{
    clock_startHFClock();
}

bool clockCtrl_isHFClockRunning( void )
{
    return CLOCK_STATE_RUNNING == clock_getHFClockState();
}

bool clockCtrl_isXtalRunning( void )
{
    return CLOCK_SOURCE_CRYSTAL == clock_getHFClockSource();
}
