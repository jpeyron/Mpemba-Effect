/************************************************************************/
/*																		*/
/*	TC1.cpp	--	Driver for Thermocouple Sensor				        	*/
/*																		*/
/************************************************************************/
/*	Author: 	Samuel Lowe											*/
/*	Copyright (c) 2015, Digilent Inc, All rights reserved				*/
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	10/26/2011(SamL): created										*/
/*																		*/
/************************************************************************/
/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/************************************************************************/


/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#include <TC1.h>

extern "C" {
  #include <stdint.h>
}

/* ------------------------------------------------------------ */
/*			Thermocouple Driver Object Instantiation					*/
/* ------------------------------------------------------------ */
/* Instantiate a single static instance of this object class
*/


int TC1::chipSelect  = -1;


/* ------------------------------------------------------------ */
/*  TC1
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Constructor to the class TC1
*/
TC1:: TC1(){
}

/*  begin()
**
**  Parameters:
**    CS is the desired chip select pin for the SPI interface. Need 
**		this value to access into our read and write register functions
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**   	initializes the class parameters and calls for the IC to be initialized
*/
void TC1::begin(int CS){	
	SPI.begin();
	chipSelect = CS;	
}

/*  getTemp()
**
**  Parameters:
**    none
**
**  Return Value:
**    double result -  value of the read temp data from readData
**
**  Errors:
**    none
**
**  Description:
**   	call readData and return that value
*/
double TC1::getTemp(){
	
	int modded = 0;
	int buffer = 0;
	double temp = 0;
	
	readData();
	
	buffer = data & 0xFFFC0000;	
	
	//shift over to LSB 
	buffer = buffer >> 18;
	
	
	modded = buffer % 4;
	temp = (double) (buffer / 4);	
	
	
	temp = temp + (modded * .25);

	return temp;
	
}

/*  getAMBTemp()
**
**  Parameters:
**    	none
**
**  Return Value:
**   double temperature of chip
**
**  Errors:
**    none
**
**  Description:
**   	will extract the chip temperature data from the data stream
*/
double TC1::getAMBTemp(){
	
	int buffer = 0;
	double ambTemp = 0;
	int modded = 0;
	
	readData();
	
	buffer = data & 0x0000FFF0;		
	
	buffer = buffer >> 4;	
	
	modded = buffer % 16;
	ambTemp = (double) (buffer / 16);	
	
	ambTemp = ambTemp + (modded * .0625);
	
	return ambTemp;

}



/*  readData()
**
**  Parameters:
**    	none
**
**  Return Value:
**   none
**
**  Errors:
**    none
**
**  Description:
**   	will read the bitstream from the TC1 and store it into data member "data"
*/
void TC1::readData(){
	
	//Serial.println("Entered update data");
	

	uint32_t buffer = 0;
	//clear current data int
	data = 0;	
	
	double result = 0.0;
	
	//read in 32 bits of data 
	
	digitalWrite(chipSelect, LOW);
	
	for(int i = 0; i<4; i++){
		buffer = SPI.transfer(0);
		data = data << 8;
		data = data | buffer;
	}
	
		
	
	digitalWrite(chipSelect, HIGH);

}


/*  getFault()
**
**  Parameters:
**    	none
**
**  Return Value:
**   uint16_t fault code which tells you what is failing
**
**  Errors:
**    none
**
**  Description:
**   	will read the bitstream from the TC1 and store it into data member "data"
*/
uint16_t TC1::getFault(){
	
	readData();	

	if((data & 65536) == 65536){	
		Serial.println("Entered fault");
		if((data & 1) == 1 && (data & 3) != 3)
			return 1;   //open connection	
		if((data & 3) == 3)
			return 2;	//SCG shorted to gnd				
		if((data & 4) == 4)
			return 3;	//SCV shorted to VCC		
	}
	
	//else zero Pmod is working correctly
	return 0;

}



/*  double celToFar(double celsius)
**
**  Parameters:
**   double celcius		value to convert to farenheit
**
**  Return Value:
**   double farenheit	converted farenheit value
**
**  Errors:
**    none
**
**  Description:
**   	converts a temperature in celcius to farenheit
*/
double TC1::celToFar(double celsius){	
	return (celsius * 1.8) + 32;
}






