#include <TC1.h>


/**************************************************/
/* PmodTC1 Demo                                   */
/**************************************************/
/*    Author: Samuel Lowe                         */
/*    Copyright 2014, Digilent Inc.               */
/*                                                */
/*   Made for use with chipKIT Pro MX3            */
/*   PmodTC1 on connector JC                     */
/**************************************************/
/*  Module Description:                           */
/*                                                */
/*    This module implements a demo application   */
/*    of the PmodTC1.                            */
/*                                                */
/*  Functionality:                                */
/*                                                */  
/*    This module reads data from the Pmod TC1    */
/*    and reports the data to the Serial monitor  */
/*                                                */  
/**************************************************/
/*  Revision History:                             */
/*                                                */
/*      1/15/2015(SamL): Created                 */
/*                                                */
/**************************************************/

// the sensor communicates using SPI, so include the library:
#include <SPI.h>

int chipSelectPin = SS;

double celsius = 0;
double faren = 0;
TC1 myTMP;

void setup() {
  
  
  Serial.begin(9600);
 
  SPI.begin();  
  myTMP.begin(chipSelectPin);
  

  // initalize the  data ready and chip select pins:
  
  pinMode(chipSelectPin, OUTPUT); 

  // initialize sensor  
  digitalWrite(chipSelectPin, HIGH);  
  delay(100);
}

void loop() {
  //Select High Resolution Mode
  celsius = myTMP.getTemp();  
  faren = myTMP.celToFar(celsius);
  
  Serial.print("Temp: ");
  Serial.print(celsius);
  Serial.print("  deg C  ");
 
  Serial.print("Temp: ");
  Serial.print(faren);
  Serial.println("  deg F");
  
 delay(10);
  
}

