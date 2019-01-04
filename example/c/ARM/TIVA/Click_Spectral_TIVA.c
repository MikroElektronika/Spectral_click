/*
Example for Spectral Click

    Date          : Jan 2018.
    Author        : MikroE Team

Test configuration TIVA :
    
    MCU              : TM4C129XNCZAD
    Dev. Board       : EasyMx PRO v7 for TIVA ARM
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes all necessary GPIO pins, UART used for
the communcation with GSM module and UART used for infromation logging
- Application Initialization - Initializes driver, power on module and sends few
command for the default module configuration
- Application Task - running in parallel core state machine and checks for call flag. 
If call detected parser will hang up call.

Additional Functions :

All additional functions such as timer initialization and default handler. 

Notes :

- Echo must be turned off for succefull parsing. ( ATE0 )
- UART polling works much better with HFC enabled.
- In case of usage of other MCUs Timer initialization must be adjusted according to your MCU.

*/

#define __Spectral__

#include "Click_Spectral_types.h"
#include "Click_Spectral_config.h"
#include "Click_Spectral_timer.h"

static uint8_t callFlag;

void spectral_default_handler( uint8_t *rsp, uint8_t *evArgs )
{
    mikrobus_logWrite( rsp, _LOG_TEXT );

//  SKIP <CR> and <LF>
    if (0 == strncmp("RING", rsp + 2, 4))
    {
        callFlag = 1;
    }
}

void systemInit()
{
    callFlag = 0;
    
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_AN_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_PWM_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );
    mikrobus_uartInit( _MIKROBUS1, &_SPECTRAL_UART_CFG[0] );
    mikrobus_logInit( _LOG_USBUART_A, 9600 );
}

void applicationInit()
{
// TIMER INIT
    spectral_configTimer();

// DRIVER INIT
    spectral_uartDriverInit((T_SPECTRAL_P)&_MIKROBUS1_GPIO, (T_SPECTRAL_P)&_MIKROBUS1_UART);
    spectral_coreInit( spectral_default_handler, 1500 );

// MODULE POWER ON
    spectral_hfcEnable( true );
    spectral_modulePower( true );

// MODULE INIT
    spectral_cmdSingle( "AT" );
    spectral_cmdSingle( "AT" );
    spectral_cmdSingle( "AT" );
    spectral_cmdSingle( "ATE0" );
    spectral_cmdSingle( "AT+IFC=2,2" );
    spectral_cmdSingle( "AT+CMGF=1" );
}

void applicationTask()
{
// CORE STATE MACHINE
    spectral_process();

    if (0 != callFlag)
    {
        spectral_cmdSingle( "ATH" );
        Delay_ms( 3000 );

        callFlag = 0;
    }
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

/* -------------------------------------------------------------------------- */