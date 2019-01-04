/*
Example for Spectral Click

    Date          : Jan 2018.
    Author        : MikroE Team

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes all necessary GPIO pins, UART used for
the communcation with Spectral and UART used for infromation logging
- Application Initialization - Initializes driver, reset module and sends
command for the default module configuration
- Application Task - Sends the command to start reading data.
   Then logs to USBUART, six read values every 1 second.


*/

#include "Click_Spectral_types.h"
#include "Click_Spectral_config.h"
#include "Click_Spectral_timer.h"



uint16_t readData[6] ;
uint8_t dataBuffer[100]= {0};
char text[100];

uint8_t cmdData[7] = {'A','T','D','A','T','A',0};
uint8_t cmdAT[3] = {'A','T',0};
uint8_t cmdGain[9] = {'A','T','G','A','I','N','=','2',0};
uint8_t cmdMode[10] = {'A','T','T','C','S','M','D','=','2',0};


void spectral_default_handler( uint8_t *rsp, uint8_t *evArgs )
{
    char *ptr = rsp;
    mikrobus_logWrite( ptr, _LOG_LINE );
    strcpy(dataBuffer,ptr);
}

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
    mikrobus_uartInit( _MIKROBUS1, &_SPECTRAL_UART_CFG[0] );
    mikrobus_logInit( _MIKROBUS2, 115200 );

    mikrobus_logWrite( " --- System init --- ", _LOG_LINE );

}

void applicationInit()
{
    spectral_configTimer();
    spectral_uartDriverInit((T_SPECTRAL_P)&_MIKROBUS1_GPIO, (T_SPECTRAL_P)&_MIKROBUS1_UART);
    UART2_C2 |= 1 << 5;
    NVIC_IntEnable(IVT_INT_UART2_RX_TX);
    EnableInterrupts();

    spectral_coreInit( &spectral_default_handler, 1500 );
    spectral_reset();
    Delay_ms( 500 );

    // Settings
    spectral_cmdSingle(&cmdAT[0]);
    spectral_cmdSingle(&cmdGain[0]);
    spectral_cmdSingle(&cmdMode[0]);
    Delay_ms( 1000 );
}


void applicationTask()
{
    spectral_process();

    spectral_cmdSingle(&cmdData[0]);
    spectral_getData(&dataBuffer[0],&readData[0]);
    IntToStr(readData[0],text);
    mikrobus_logWrite( "-- X value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    IntToStr(readData[1],text);
    mikrobus_logWrite( "-- Y value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    IntToStr(readData[2],text);
    mikrobus_logWrite( "-- Z value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    IntToStr(readData[3],text);
    mikrobus_logWrite( "-- NIR value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    IntToStr(readData[4],text);
    mikrobus_logWrite( "-- D value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    IntToStr(readData[5],text);
    mikrobus_logWrite( "-- C value:", _LOG_TEXT );
    mikrobus_logWrite( text, _LOG_LINE );

    mikrobus_logWrite( "---------------------", _LOG_LINE );

    Delay_1sec();
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }
}

/*
 * UART Interrupt
 */
// 
void RX_ISR() iv IVT_INT_UART2_RX_TX ics ICS_AUTO
{
    if(  UART2_S1 & ( 1 << 5 )  )
    {
        char tmp = UART2_D;
        spectral_putc( tmp );
    }
}
/* -------------------------------------------------------------------------- */