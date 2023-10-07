/**
   EXT_INT Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     ext_int.c
 
   @Summary
     This is the generated driver implementation file for the EXT_INT driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for EXT_INT.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
         Device            :  PIC16F18446
         Driver Version    :  1.11
     The generated drivers are tested against the following:
         Compiler          :  XC8 2.31 and above
         MPLAB             :  MPLAB X 5.45
 */ 

 /**
   Section: Includes
 */
#include <xc.h>
#include "ext_int.h"
#include "mcc.h"
unsigned char PID;
_Bool Overtemp;

//Fan Speed scaling
//160 is heater fan min
//0 is fully on
// therefore: (-1.6*X) + 160
//fanspeed is the requested speed. (0 to 100%))
//Fanspeed_scaled is the output to the timer
signed int Fanspeed=0;
unsigned char Fanspeed_Scaled;

void (*INT_InterruptHandler)(void);

void INT_ISR(void)
{
    EXT_INT_InterruptFlagClear();

    // Callback function gets called everytime this ISR executes
    INT_CallBack();    
}


void INT_CallBack(void)
{
    // Add your custom callback code here
    if(INT_InterruptHandler)
    {
        INT_InterruptHandler();
    }
}

void INT_SetInterruptHandler(void (* InterruptHandler)(void)){
    INT_InterruptHandler = InterruptHandler;
}

void INT_DefaultInterruptHandler(void){
    // add your INT interrupt custom code
    // or set custom function using INT_SetInterruptHandler()
    /**
     * This is where we will control the heater or other stuff depending on ZCD. 
     * Timer 2 will be triggered here eventually, this is for testing.
     * OFF is actually ON for the TRIAC
     */
    
   
    //HEATER_PWM_SetLow();    
    
    
    
    
    //Lower numbers mean more power gets passed.
    //TMR2_Period8BitSet(PID);
    if (Overtemp==0){
        
        TMR2_Period8BitSet(PID); 
        TMR2_Start();
        //REGULAR
        HEATER_PWM_SetLow(); //turn off heater
        
        //INVERSE 
        //HEATER_PWM_SetHigh();
    }
    HEATER_FAN_SetLow();    //turn on fan
    //TMR6_Period8BitSet(Fanspeed_Scaled);//turn on fan
     TMR6_Period8BitSet(0);//keep fan on all the time
    TMR6_Start();
    



}

void EXT_INT_Initialize(void)
{
    
    // Clear the interrupt flag
    // Set the external interrupt edge detect
    EXT_INT_InterruptFlagClear();   
    EXT_INT_risingEdgeSet();    
    // Set Default Interrupt Handler
    INT_SetInterruptHandler(INT_DefaultInterruptHandler);
    EXT_INT_InterruptEnable();      

}

