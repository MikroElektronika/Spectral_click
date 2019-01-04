![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Spectral Click

- **CIC Prefix**  : SPECTRAL
- **Author**      : Katarina Perendic
- **Verison**     : 1.0.0
- **Date**        : Jan 2018.

---

### Software Support

We provide a library for the Spectral Click on our [LibStock](https://libstock.mikroe.com/projects/view/2348/spectral-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Library initializes and defines UART driver and functions witch offer a choice to providing direct XYZ color coordinates consistent with the CIE 1931 
2. Standard Observer color coordinates. It also maps the XYZ coordinates to the x, y (Y) of the 2-dimensional color gamut and scales the coordinates 
to the CIE 1976 u’v’ coordinate system. The library provides accurate Correlated Color Temperature (CCT) measurements and provides color point deviation 
from the black body curve for white light color in the delta u’ v’ coordinate system. Check documentation for more details.

Key functions :

- ``` void spectral_getColor_Data(uint8_t *rsp, uint8_t *) ``` - Reads calibrated X, Y, and Z color data.
- ``` void spectral_getXYsmall_Data(uint8_t *rsp, uint8_t *xyData) ``` - Reads calibrated x and y for CIE 1931 color gamut.
- ``` uint8_t spectral_getLUX_Data(uint8_t *rsp) ``` - Reads calibrated LUX value from the sensor.
- ``` uint8_t spectral_getCCT_Data(uint8_t *rsp) ``` - Reads calibrated CCT value from the sensor.
- ``` void spectral_getUV_Data(uint8_t *rsp, uint16_t *uvData) ``` - Reads calibrated u’, v’ and u, v for CIE 1976 color gamut.

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes all necessary GPIO pins, UART used for
the communcation with Spectral and UART used for infromation logging
- Application Initialization - Initializes driver, reset module and sends
command for the default module configuration
- Application Task - Sends the command to start reading data. 
   Then logs to USBUART, six read values every 1 second.
   

```.c
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
```

Alongside with the demo application timer initialization functions are provided.
Note that timer is configured acording to default develoment system and 
MCUs, changing the system or MCU may require update of timer init and timer ISR 
functions.

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2348/spectral-click) page.

Other mikroE Libraries used in the example:

- String
- Conversions
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---

| **Supported** | STM | KIN | CEC | MSP | TI  | PIC | P32 | DSP | AVR | FT90x |
|--------------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:-----:|
| **mikroC**    |  x  |  x  |     |     |  x  |  x  |  x  |  x  |  x  |   x   |
| **mikroB**    |  x  |  x  |     |     |  x  |  x  |  x  |  x  |  x  |   x   |
| **mikroP**    |  x  |  x  |     |     |  x  |  x  |  x  |  x  |  x  |   x   |

---
---
