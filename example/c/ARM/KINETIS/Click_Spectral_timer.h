/*

Use mikroE Timer Calculator to generate proper timer configuration
and timer ISR.

https://www.mikroe.com/timer-calculator

*/
#include "Click_Spectral_types.h"

#define __Spectral_TIMER__

static void spectral_configTimer()
{
    SIM_SCGC6 |= (1 << PIT);
    NVIC_IntEnable(IVT_INT_PIT0);
    PIT_MCR = 0x00;
    PIT_LDVAL0 = 119999;
    PIT_TCTRL0 |= 2;
    PIT_TCTRL0 |= 1;
    EnableInterrupts();
}
//  
void Timer_interrupt() iv IVT_INT_PIT0
{
    spectral_tick();
    PIT_TFLG0.TIF = 1;
}