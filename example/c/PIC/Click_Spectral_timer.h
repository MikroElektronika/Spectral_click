/*

Use mikroE Timer Calculator to generate proper timer configuration
and timer ISR.

https://www.mikroe.com/timer-calculator

*/
#include "Click_Spectral_types.h"

#define __Spectral_TIMER__

static void spectral_configTimer()
{
    T1CON         = 0x01;
    TMR1IF_bit         = 0;
    TMR1H         = 0xF0;
    TMR1L         = 0x60;
    TMR1IE_bit         = 1;
    INTCON         = 0xC0;
    
    RC1IE_bit    = 1;
    RC1IF_bit    = 0;
    PEIE_bit     = 1;
    GIE_bit      = 1;
}

void Interrupt()
{
   if (TMR1IF_bit != 0)
    {
            spectral_tick();
            TMR1IF_bit = 0;
            TMR1H          = 0xF0;
            TMR1L          = 0x60;
    }
    
    if( RC1IF_bit == 1 )
    {
       char tmp = UART1_Read();
       spectral_putc( tmp );
    }
   
}