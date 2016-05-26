#include <TC1.h>


/**************************************************/
/* Mpemba Demo                                    */
/**************************************************/
/*    Author:  Jon Peyron                         */
/*    Copyright 2016, Digilent Inc.               */
/*                                                */
/*   Made for use with chipKIT Pro MX4            */
/*   Pmod TPH2 2 PmodTC1 on connector JB          */
/**************************************************/
/*  Module Description:                           */
/*                                                */
/*    This module implements a demo application   */
/*    of the PmodTC1 and the Pmod TPH2            */
/*                                                */
/*  Functionality:                                */
/*                                                */  
/*    This module reads data from the 2 Pmod TC1  */
/*    and reports the data through Serial         */
/*    communication                               */  
/**************************************************/
/*  Revision History:                             */
/*                                                */
/*                                                */
/*                                                */
/**************************************************/

// the sensor communicates using SPI, so include the library:
#include <SPI.h>


  int x =0;
//uses two TC1 so needs two ChipSelect Pins
int chipSelectPin1 = 21;
int chipSelectPin2 = 20;
int i =0;

double celsius = 0;
double celsius1 = 0;
double faren = 0;
TC1 myTMP;


void setup() {

          
          if(x==0)
          chipSelectPin1 = 21;
          
          else
          chipSelectPin1 = 20;
          
          
          Serial.begin(115200);
         
           
           SPI.begin();
          
          myTMP.begin(chipSelectPin1);
          
          
          
          // initalize the  data ready and chip select pins:
          
          pinMode(chipSelectPin1, OUTPUT); 
           
          digitalWrite(chipSelectPin1, HIGH); 
          
           
          delay(100);
          i += 100;
}

void loop() {

         //inserts a delay of 30 seconds between each read so 1 minute between reads of each TC1
         for(i;i<30000;i++)
        {
         delay(1);
         
        }
  
        celsius = myTMP.getTemp(); 
        
         
        i =1;
         
        if(x==0){
                  
         //used to know which TC1 data we are writing serially
         Serial.write(x);
         
         Serial.write(celsius);
          
         x++;
         
        }else{
        
         Serial.write(x);
         Serial.write(celsius);
       
        x=0;
         }
        
        
         delay(100);
         i += 100;
         setup();
 

}

