/**
 * Coffee Roasting Control Board Software
 * 
 * 2023/02/10 
 * 
 * Heater Fan in Rev 1 is relay controlled
 * 
*/

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>


//SPI Vars
uint8_t writeData = 1; /* Data that will be transmitted */
uint8_t SPI_receiveData; /* Data that will be received */
uint8_t SPI_receiveData2;
uint8_t SPI_receiveData3;
uint8_t SPI_receiveData4;
unsigned int CurrentTemperature;
unsigned int TempVariable;
unsigned int ScaledTempF;
unsigned int ScaledTempHMI;

//PID loop vars
extern unsigned int DerivativeTime;  //external variable used in tmr1.c
signed int Intergral;
signed int Error;
//signed int PreviousError;
//signed char Derivative;
unsigned int SetTemperature;//
unsigned int PIDoutput;
unsigned int PIDinterm;
_Bool IntakeFanBit;

//PID control
extern unsigned char PID;
signed int ki_term;
signed int kp_term;


//make constants negative to invert output
//PID Constants
const signed int Kp = 12;//
const signed int Ki = 0;//
//const signed int Kd = 1;


//USART Vars
char buf[8];
extern uint8_t eusart1RxBuffer[8];
unsigned char COOL;
unsigned char HEAT;
unsigned char CLEARTIME;
unsigned char TEMP_MINUS;
unsigned char TEMP_PLUS;
unsigned char Fan_MINUS;
unsigned char Fan_PLUS;
unsigned char Rot_MINUS;
unsigned char Rot_PLUS;
unsigned char Rot_ON;
unsigned char Rot_OFF;
unsigned char FIRSTCRACK;

unsigned char NUMBERINPUT;
char IntBuffer[3];
unsigned int val;

unsigned char USART_TemperatureSP_Compare;
unsigned char USART_FanSPSP_Compare;
unsigned char USART_DrumSP_Compare;

//scaling vars
//PWM Scale calc: ((X * 2) + 745)/10 scales RPM input to PWM output
//PWM min = 76 (80%)), ~7RPM
//PWM max = 99 (100%), ~120 RPM
unsigned int RPM;
unsigned int RPM_Scaled;

//Fan Speed scaling
//Fan uses Timer 6
//160 is heater fan min
//0 is fully on
// therefore: (-1.6*X) + 160
//fanspeed is the requested speed. (0 to 100%))
//Fanspeed_scaled is the output to the timer
extern signed int Fanspeed=50;
extern unsigned char Fanspeed_Scaled;
unsigned char Old_Fanspeed;


//misc
extern unsigned int Elapsed_Time=0;//seconds
extern unsigned int Cooling_Time=0;//seconds
unsigned int Set_Time=1200;//seconds
extern _Bool RoastFinished=0;
extern _Bool CoolingMode=0;
extern _Bool CoolingSecondsBit=0;
unsigned char GarbageByte;
unsigned int StartupFinished=0;
extern unsigned char DisplayDelaytime=0;
unsigned int FirstCrackTime;

extern _Bool Overtemp;
extern _Bool ROTARTY_ON;

/*
                         Main application
 */

unsigned char PIDLoop(){//NOT USED CURRENTLY
    
//        //NOTE Higher values mean less of the sine wave gets passed
//        //PID = 0 is a full sine wave, PID = 255 is fully OFF
//        //IF INVERETED THIS IS REVERSE
//        //PIE3bits.RC1IE = 0;
//        Error = SetTemperature - ScaledTempHMI;
//        Intergral = Intergral + Error;
////        if (Error <=1){IntakeFanBit=1;EXHAUST_FAN_SetHigh();}//turn on the fan and bring in some fresh air
////        if (Error > 1){IntakeFanBit=0; EXHAUST_FAN_SetLow();}
//         //check Intergral error to make sure it doesnt get too large
//        if (Intergral >= 255){Intergral=255;}
//        if (Intergral <= -255){Intergral=-255;}            
//        
//        //Derivative = (Error - PreviousError)/DerivativeTime;
//        Derivative = (Error - PreviousError);   
//
//        
//        PIDoutput = (Error/Kp) + (Intergral*Ki) + (Derivative*Kd);            
//        //PIDoutput=~PIDoutput;
//        if (PIDoutput <= 0){PIDoutput=0;}
//        PreviousError = Error; 
//        return PIDoutput;   
//}


//Functions not used:
//void NextionBasic_command(char *Text) //basic command to get started.
//{
//    printf(Text);
//    EUSART1_Write(0xFF);
//    EUSART1_Write(0xFF);
//    EUSART1_Write(0xFF);
//    
//}
////This command sends a string and a number to a number box in the Nextion HMI
////so if you have a number box called "n0", the commands will be used like this:
////NextionSendNumber_command("n0.val=",i2);
////assuming i2 is an unsigned int
//void NextionSendNumber_command(char *Text,unsigned int number) 
//{
//        // disable receive interrupt
//    //PIE3bits.RC1IE = 0;
//    printf(Text);
//    printf("%d",number);
//    EUSART1_Write(0xFF);
//    EUSART1_Write(0xFF);
//    EUSART1_Write(0xFF);    
//        // enable receive interrupt
//    //PIE3bits.RC1IE = 1;
} 

void EUSART_Read_Text(char *Output, unsigned int length)
{
	unsigned int j;
	for(j=0;j<length;j++)
	Output[j] = EUSART1_Read();
}

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();
        SPI1_Initialize();
        PWM6_Initialize();
                TMR2_Initialize();
        TMR2_Stop();

     
    PWM6EN=0;
    memset(buf,0,8);//clear buffer after
    SetTemperature = 450;
    //PIDoutput = 128;//set initial
    
    while (1)
    {
        



        //scale the RPM for the rotary drum.        
        RPM_Scaled = (((RPM*2)+746)/10);
        //This turns on and off the rotary drum
        //PWM6EN=1;//PWM6EN=0;
        PWM6_LoadDutyValue(RPM_Scaled);        
        Fanspeed_Scaled=(((Fanspeed*-10)+1600)/10);
       
        
        //MAX31885 notes: Last TWO bits of receiveData2 have to be dropped
        // in order to convert things. Then the number has to be multiplied by 0.25
        //OR shift to the right two times. 
        SPI1_Open(SPI1_DEFAULT);
        CS_SetLow();

        SPI_receiveData = SPI1_ExchangeByte(writeData);
        SPI_receiveData2 = SPI1_ExchangeByte(writeData);
        SPI_receiveData3 = SPI1_ExchangeByte(writeData);
        SPI_receiveData4 = SPI1_ExchangeByte(writeData);
        CS_SetHigh();
        SPI1_Close();
        TempVariable = SPI_receiveData2 | SPI_receiveData<<8;
        TempVariable = (TempVariable >> 2);
        CurrentTemperature = TempVariable/4;
        ScaledTempF = ((CurrentTemperature*18)+320)/10; //convert to F
        ScaledTempHMI=ScaledTempF;


        //this function stops the output from getting too high as an over temp shut off
        if (ScaledTempHMI > SetTemperature)
            {
            Overtemp=1;
            HEATER_PWM_SetLow();//Setting low turns OFF the SCR
            EXHAUST_FAN_SetHigh();
            TMR2_Stop();
        }
        if (ScaledTempHMI < SetTemperature) {

            EXHAUST_FAN_SetLow();
            Overtemp = 0;
            
            if (DerivativeTime==1){ //check to see if its time to do math
                Error = SetTemperature - ScaledTempHMI;
                
                //Intergral = Intergral + Error;

                //check Intergral error to make sure it doesnt get too large
                //not really using the integral
                //if (Intergral >= 1023){Intergral=1023;}
                //if (Intergral <= -1023){Intergral=-1023;}           
                //Derivative = (Error - PreviousError);   

                //ki_term = (Intergral*Ki);
                kp_term = (Error*Kp);

                PIDoutput = kp_term; //+            

                if (PIDoutput <= 0){PIDoutput=0;}
                if (PIDoutput >=1000){PIDoutput=1000;}
                //PreviousError = Error;


                  //scale the output. In practice the min output for any physical change to happen is 150               
                 //PID=255-((PIDoutput*25)/100);
                 PIDinterm=((PIDoutput*16)/100);
                 PID = 160-PIDinterm;//
                 DerivativeTime=0;
                }//PID loop

        }     
   


        
        if (RoastFinished==0){

        }//roast NOT finished loop
        
        if (DisplayDelaytime==1 && RoastFinished == 0){
                
            // uncomment these lines
            printf("t");
            printf("%0.3u",Elapsed_Time);
           // __delay_ms(10);
            printf("a");
            printf("%0.3u",ScaledTempHMI);            
            //printf("%0.3u",ScaledTempHMI);    
             DisplayDelaytime=0;
         //PID=PIDLoop();
        }
        
        
        
        if (Elapsed_Time==Set_Time){//do times match? If so shut off heater
            //PID=255;
            HEATER_PWM_SetHigh();
            //Fanspeed=100;
            TMR2_Stop();
            //TMR1_StopTimer();                               
            //CoolingMode=1;
            //Cooling_Time=0;
            //RoastFinished=1;
            //Elapsed_Time=0;
            
        }//Roast Finished loop
        if (CoolingMode==1 && CoolingSecondsBit==1){

            //PID=255;
            HEATER_PWM_SetHigh();
            //Fanspeed=100;
            TMR2_Stop();
            RoastFinished=1;
            //Elapsed_Time=0;
            CoolingSecondsBit=0;
            DerivativeTime=0;
            
            //RPM=75;
        }//cooling mode loop    
        
    
    if (eusart1RxCount!=0){//is RX count not equal to 0? (ie is it 1)
     //begin sequence to read from the serial port
     //EUSART_Read_Text(buf,6);
     //make a button that prints out "FAN"
     //then compare and look for it

        
        EUSART_Read_Text(buf,4);
        //EUSART1_Write("0");
        COOL = strncmp (buf,"XCOL",4);
        //cooling mode on
        if (COOL==0){

         CoolingMode=1;

         memset(buf,0,8);//clear buffer after
        }

        CLEARTIME = strncmp (buf, "XZER",4);
        if (CLEARTIME==0){
          Elapsed_Time=0;
          printf("t");
          printf("%0.3u",Elapsed_Time);
          memset(buf,0,8);//clear buffer after
        }
        
        FIRSTCRACK = strncmp (buf, "XFCZ",4);
        if (FIRSTCRACK==0){
            FirstCrackTime=Elapsed_Time;
            //printf("z");
            //printf("%u",FirstCrackTime);
            Elapsed_Time=0;
            printf("t");
            printf("%0.3u",Elapsed_Time);
            
          memset(buf,0,4);//clear buffer after
        }        
//        TEMP_PLUS = strncmp (buf, "TE+",3);
//        if (TEMP_PLUS==0){
//            SetTemperature=SetTemperature+5;
//            //printf("Current Set Point Changed: =%u\n",SetTemperature);
//          memset(buf,0,3);//clear buffer after
//        }
//        //adjust Fan Speed
//        Fan_MINUS = strncmp (buf, "FE-",3);
//        if (Fan_MINUS==0){
//            Fanspeed=Fanspeed-5;
//            //printf("Current speed Changed: =%u\n",Fanspeed);
//          memset(buf,0,3);//clear buffer after
//        }        
//        Fan_PLUS = strncmp (buf, "FE+",3);
//        if (Fan_PLUS==0){
//            Fanspeed=Fanspeed+5;
//            //printf("Current speed Changed: =%u\n",Fanspeed);
//          memset(buf,0,3);//clear buffer after
//        }
//        //adjust rotation speed
//        Rot_MINUS = strncmp (buf, "RO-",3);
//        if (Rot_MINUS==0){
//            RPM=RPM-5;
//            //printf("Current Rotation Changed: =%u\n",RPM);
//          memset(buf,0,3);//clear buffer after
//        }        
//        Rot_PLUS = strncmp (buf, "RO+",3);
//        if (Rot_PLUS==0){
//            RPM=RPM+5;
//            //printf("Current Rotation Changed: =%u\n",RPM);
//            memset(buf,0,3);//clear buffer after
//        }
        Rot_ON = strncmp(buf, "XRON",4);
        if (Rot_ON==0){
            PWM6EN=1;
            ROTARTY_ON=1;
            //printf("Rotation ON\n");
            memset(buf,0,8);//clear buffer after           
        }
        Rot_OFF = strncmp(buf, "XROF",4);
        if (Rot_OFF==0){
            PWM6EN=0;
            ROTARTY_ON=0;
            //printf("Rotation OFF\n");
            memset(buf,0,8);//clear buffer after           
        }

    //command structure from display:
    //Snnn = temperature set point, character "S" followed by the 3 digits
    //Fnnn = Fan speed set point, character "F" followed by the 3 digits
    //Dnnn = Drum Speed set point, character "D" followed by the 3 digits
    //this then converts the number to ASCII and then we print
    //First function looks for temp set point    
        USART_TemperatureSP_Compare = strncmp(buf,"S",1);

        if (USART_TemperatureSP_Compare==0)
        {
            //memset(buf,0,3); //clear only the first 3 bytes
            //move things into a new buffer so we can get rid of the leading zeros
            IntBuffer[0]=buf[1];
            IntBuffer[1]=buf[2];
            IntBuffer[2]=buf[3];
            //then convert the buffer to an int;
            
            //***TEMP REMOVED ///***
            SetTemperature=atoi(IntBuffer);
            //then spit it back out in another text box. 
            //NextionSendNumber_command("n0.val=",val);
            //printf("New Setpoint: =%u\n",SetTemperature);
            //printf("I see you\n");
            memset(buf,0,4); //then clear the buffer after use
            memset(IntBuffer,0,4);
        }//end Set Point Look up
        
        //Look for Fan Speed Set Point
        
        USART_FanSPSP_Compare = strncmp(buf,"F",1);
        
        if (USART_FanSPSP_Compare ==0)
        {
            IntBuffer[0]=buf[1];
            IntBuffer[1]=buf[2];
            IntBuffer[2]=buf[3];
            Fanspeed=atoi(IntBuffer);
            //("New Fan Speed: =%u\n",Fanspeed);
            memset(buf,0,4); //then clear the buffer after use
            memset(IntBuffer,0,4);            
            
        }//end Fan Speed Look up
              
        //look up for Drum Speed
        USART_DrumSP_Compare = strncmp (buf,"D",1);
        
        if (USART_DrumSP_Compare==0)
        {
            IntBuffer[0]=buf[1];
            IntBuffer[1]=buf[2];
            IntBuffer[2]=buf[3];
            RPM=atoi(IntBuffer);
            //printf("New Drum Speed: =%u\n",RPM);
            memset(buf,0,4); //then clear the buffer after use
            memset(IntBuffer,0,4);            
        }//end Drum Speed look up
               
              
                
              
        //memset(eusart1RxBuffer,0,8);
        }//end rx loop
        //memset(eusart1RxBuffer,0,8);

    }//main loop end
}
/**
 End of File
*/