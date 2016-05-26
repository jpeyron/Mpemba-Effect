/************************************************************************/
/*																		*/
/*	TC1.h	--	Interface Declarations for TC1.cpp			        	*/
/*																		*/
/************************************************************************/
/*	Author:		Samuel Lowe											*/
/*	Copyright (c) 2014, Digilent Inc. All rights reserved.				*/
/************************************************************************/
/*  File Description:													*/
/*																		*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	10/17/2011(SamL): created										*/
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

#if !defined(TC1_H)
#define TC1_H

#include "SPI.h"

extern "C" {
  #include <stdint.h>
}

/* ------------------------------------------------------------ */
/*					Object Class Declarations					*/
/* ------------------------------------------------------------ */

class TC1
{
	public:
	
		TC1();
		void begin(int CS);
		
		
		double getTemp();
		double getAMBTemp();
		void readData();		
		uint16_t getFault();
		double celToFar(double celsius);	
		

	private:
		
		
		uint32_t data;
		
		static int chipSelect; 
		int fault;
		int SCV;
		int SCG;
		int OC;		
		
};

#endif