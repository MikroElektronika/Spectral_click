/*

Use mikroE Timer Calculator to generate proper timer configuration
and timer ISR.

https://www.mikroe.com/timer-calculator

*/
#include "Click_Spectral_types.h"

#define __Spectral_TIMER__

static void spectral_configTimer()
{


    // Configure Timer
}

void Timer_interrupt()
{
    spectral_tick();
    // Reset Flag
}