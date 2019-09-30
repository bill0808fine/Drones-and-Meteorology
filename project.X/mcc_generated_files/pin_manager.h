/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F25K22
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set PM_LED aliases
#define PM_LED_TRIS                 TRISAbits.TRISA5
#define PM_LED_LAT                  LATAbits.LATA5
#define PM_LED_PORT                 PORTAbits.RA5
#define PM_LED_ANS                  ANSELAbits.ANSA5
#define PM_LED_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define PM_LED_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define PM_LED_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define PM_LED_GetValue()           PORTAbits.RA5
#define PM_LED_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define PM_LED_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define PM_LED_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define PM_LED_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set channel_AN9 aliases
#define channel_AN9_TRIS                 TRISBbits.TRISB3
#define channel_AN9_LAT                  LATBbits.LATB3
#define channel_AN9_PORT                 PORTBbits.RB3
#define channel_AN9_WPU                  WPUBbits.WPUB3
#define channel_AN9_ANS                  ANSELBbits.ANSB3
#define channel_AN9_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define channel_AN9_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define channel_AN9_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define channel_AN9_GetValue()           PORTBbits.RB3
#define channel_AN9_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define channel_AN9_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define channel_AN9_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define channel_AN9_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define channel_AN9_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define channel_AN9_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set air_pressure aliases
#define air_pressure_TRIS                 TRISBbits.TRISB4
#define air_pressure_LAT                  LATBbits.LATB4
#define air_pressure_PORT                 PORTBbits.RB4
#define air_pressure_WPU                  WPUBbits.WPUB4
#define air_pressure_ANS                  ANSELBbits.ANSB4
#define air_pressure_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define air_pressure_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define air_pressure_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define air_pressure_GetValue()           PORTBbits.RB4
#define air_pressure_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define air_pressure_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define air_pressure_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define air_pressure_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define air_pressure_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define air_pressure_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set GPS aliases
#define GPS_TRIS                 TRISBbits.TRISB5
#define GPS_LAT                  LATBbits.LATB5
#define GPS_PORT                 PORTBbits.RB5
#define GPS_WPU                  WPUBbits.WPUB5
#define GPS_ANS                  ANSELBbits.ANSB5
#define GPS_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define GPS_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define GPS_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define GPS_GetValue()           PORTBbits.RB5
#define GPS_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define GPS_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define GPS_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define GPS_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define GPS_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define GPS_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()               do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()                do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()                do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()              PORTBbits.RB6
#define RB6_SetDigitalInput()       do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()      do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()             do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()           do { WPUBbits.WPUB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()               do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()                do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()                do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()       do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()      do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)

// get/set clk aliases
#define clk_TRIS                 TRISCbits.TRISC3
#define clk_LAT                  LATCbits.LATC3
#define clk_PORT                 PORTCbits.RC3
#define clk_ANS                  ANSELCbits.ANSC3
#define clk_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define clk_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define clk_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define clk_GetValue()           PORTCbits.RC3
#define clk_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define clk_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define clk_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define clk_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()               do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()                do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()                do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()       do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()      do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()               do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()                do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()                do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()       do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()      do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/