#include "core.h"

#include "types.h"

#include "config.h"

void main( void )
{
    core_systickInit( config.systick_frequency, config.core_clock_frequency );

    while(1)
    {

    }
}
