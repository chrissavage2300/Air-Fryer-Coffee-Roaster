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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18446
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA2 procedures
#define RA2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define RA2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define RA2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define RA2_GetValue()              PORTAbits.RA2
#define RA2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define RA2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define RA2_SetPullup()             do { WPUAbits.WPUA2 = 1; } while(0)
#define RA2_ResetPullup()           do { WPUAbits.WPUA2 = 0; } while(0)
#define RA2_SetAnalogMode()         do { ANSELAbits.ANSA2 = 1; } while(0)
#define RA2_SetDigitalMode()        do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()              PORTBbits.RB6
#define RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()             do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()           do { WPUBbits.WPUB6 = 0; } while(0)
#define RB6_SetAnalogMode()         do { ANSELBbits.ANSB6 = 1; } while(0)
#define RB6_SetDigitalMode()        do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set BUZZER aliases
#define BUZZER_TRIS                 TRISCbits.TRISC0
#define BUZZER_LAT                  LATCbits.LATC0
#define BUZZER_PORT                 PORTCbits.RC0
#define BUZZER_WPU                  WPUCbits.WPUC0
#define BUZZER_OD                   ODCONCbits.ODCC0
#define BUZZER_ANS                  ANSELCbits.ANSC0
#define BUZZER_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define BUZZER_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define BUZZER_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define BUZZER_GetValue()           PORTCbits.RC0
#define BUZZER_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define BUZZER_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define BUZZER_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define BUZZER_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define BUZZER_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define BUZZER_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define BUZZER_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define BUZZER_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set HEATER_PWM aliases
#define HEATER_PWM_TRIS                 TRISCbits.TRISC1
#define HEATER_PWM_LAT                  LATCbits.LATC1
#define HEATER_PWM_PORT                 PORTCbits.RC1
#define HEATER_PWM_WPU                  WPUCbits.WPUC1
#define HEATER_PWM_OD                   ODCONCbits.ODCC1
#define HEATER_PWM_ANS                  ANSELCbits.ANSC1
#define HEATER_PWM_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define HEATER_PWM_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define HEATER_PWM_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define HEATER_PWM_GetValue()           PORTCbits.RC1
#define HEATER_PWM_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define HEATER_PWM_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define HEATER_PWM_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define HEATER_PWM_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define HEATER_PWM_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define HEATER_PWM_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define HEATER_PWM_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define HEATER_PWM_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set HEATER_FAN aliases
#define HEATER_FAN_TRIS                 TRISCbits.TRISC2
#define HEATER_FAN_LAT                  LATCbits.LATC2
#define HEATER_FAN_PORT                 PORTCbits.RC2
#define HEATER_FAN_WPU                  WPUCbits.WPUC2
#define HEATER_FAN_OD                   ODCONCbits.ODCC2
#define HEATER_FAN_ANS                  ANSELCbits.ANSC2
#define HEATER_FAN_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define HEATER_FAN_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define HEATER_FAN_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define HEATER_FAN_GetValue()           PORTCbits.RC2
#define HEATER_FAN_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define HEATER_FAN_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define HEATER_FAN_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define HEATER_FAN_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define HEATER_FAN_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define HEATER_FAN_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define HEATER_FAN_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define HEATER_FAN_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set CS aliases
#define CS_TRIS                 TRISCbits.TRISC5
#define CS_LAT                  LATCbits.LATC5
#define CS_PORT                 PORTCbits.RC5
#define CS_WPU                  WPUCbits.WPUC5
#define CS_OD                   ODCONCbits.ODCC5
#define CS_ANS                  ANSELCbits.ANSC5
#define CS_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define CS_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define CS_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define CS_GetValue()           PORTCbits.RC5
#define CS_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define CS_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define CS_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define CS_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define CS_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define CS_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define CS_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set EXHAUST_FAN aliases
#define EXHAUST_FAN_TRIS                 TRISCbits.TRISC7
#define EXHAUST_FAN_LAT                  LATCbits.LATC7
#define EXHAUST_FAN_PORT                 PORTCbits.RC7
#define EXHAUST_FAN_WPU                  WPUCbits.WPUC7
#define EXHAUST_FAN_OD                   ODCONCbits.ODCC7
#define EXHAUST_FAN_ANS                  ANSELCbits.ANSC7
#define EXHAUST_FAN_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define EXHAUST_FAN_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define EXHAUST_FAN_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define EXHAUST_FAN_GetValue()           PORTCbits.RC7
#define EXHAUST_FAN_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define EXHAUST_FAN_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define EXHAUST_FAN_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define EXHAUST_FAN_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define EXHAUST_FAN_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define EXHAUST_FAN_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define EXHAUST_FAN_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define EXHAUST_FAN_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

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