/****************************************************************************
 * serial.cpp
 *
 * This file contains serial traffic functionality.
 *
 * Created: 25.3.2016 11:50:21
 * Author: Joonas Onatsu
 *
 * Copyright (c) 2017 Joonas Onatsu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/


#include "Arduino.h"


void Print::begin(long baud)
{
	switch(baud) {

		case 2400 :
			UBRR0 = (unsigned short)832;		// Speed 2400 Baud
			bitSet(UCSR0A, U2X0);
			break;

		case 4800 :
			UBRR0 = (unsigned short)416;		// Speed 4800 Baud
			bitSet(UCSR0A, U2X0);
			break;

		case 9600 :
			UBRR0 = (unsigned char)207;		// Speed 9600 Baud
			bitSet(UCSR0A, U2X0);
			break;

		case 14400 :
			UBRR0 = (unsigned char)138;		// Speed 14400 Baud
			bitSet(UCSR0A, U2X0);
			break;

		case 19200 :
			UBRR0 = (unsigned char)103;		// Speed 19200 Baud
			bitSet(UCSR0A, U2X0);
			break;

		case 28800 :
			UBRR0 = (unsigned char)68;		// Speed 28800 Baud
			bitSet(UCSR0A, U2X0);
			break;

		case 38400 :
			UBRR0 = (unsigned short)51;		// Speed 38400 Baud
			bitSet(UCSR0A, U2X0);
			break;

		case 57600 :
			UBRR0 = (unsigned char)34;		// Speed 57600 Baud
			bitSet(UCSR0A, U2X0);
			break;

		case 76800 :
			UBRR0 = (unsigned char)25;		// Speed 76800 Baud
			bitSet(UCSR0A, U2X0);
			break;

		case 115200 :
			UBRR0 = (unsigned char)16;		// Speed 115200 Baud
			bitSet(UCSR0A, U2X0);
			break;

		case 230400 :
			UBRR0 = (unsigned char)8;		// Speed 230400 Baud
			bitSet(UCSR0A, U2X0);
			break;

		case 250000 :
			UBRR0 = (unsigned char)7;		// Speed 250000 Baud
			bitSet(UCSR0A, U2X0);
			break;

		default:
			return;		// Unknown speed
	}

	// 8-bit chars
	bitSet(UCSR0C,UCSZ00);
	bitSet(UCSR0C,UCSZ01);
	bitClear(UCSR0B, UCSZ02);
	// One stop bit
	bitClear(UCSR0C, USBS0);
	// No parity
	bitClear(UCSR0C, UPM01);
	bitClear(UCSR0C, UPM00);
	// Allow Rx and Tx
	bitSet(UCSR0B, RXEN0);
	bitSet(UCSR0B, TXEN0);
}

void Print::print(const char* s)
{
	if(s == NULL) {
		return;		// Null pointer
	}
	else {
		while(*s != '\0') {
			print(*s++);
		}
	}
}
void Print::print(char c)
{
	// Wait for empty transmit buffer
	while( !( UCSR0A & ( 1 << UDRE0 ) ) );
	// Put data into buffer, sends data
	UDR0 = c;
}
void Print::print(unsigned char c, int r)
{
	char buf[20];
	itoa(c,buf,r);
	print(buf);
}
void Print::print(int i, int r)
{
	char buf[20];
	itoa(i,buf,r);
	print(buf);
}
void Print::print(unsigned int u, int r)
{
	char buf[20];
	itoa(u,buf,r);
	print(buf);
}
void Print::print(long l, int r)
{
	char buf[20];
	ltoa(l,buf,r);
	print(buf);
}
void Print::print(unsigned long ul, int r)
{
	char buf[20];
	ltoa(ul,buf,r);
	print(buf);
}
void Print::print(double d, int fr)
{
	char buf[13] = { 0 };		// Digits are written here backwards
	unsigned long l;
	unsigned dec = 1;		// Decimal multiplier
	int i;
	bool fNegative = false;

	if ( d < 0 )	// If d is negative
	{
		fNegative = true;
		d = -d; // Handle the number as a positive
	}

	for( i = 0; i < fr; i++) {
		dec = dec * 10;		// Multiplier
	}

	l = round( ( d * dec ) );		// Round to integer number

	// Parse the number backwards
	i = 1;
	while( l )
	{
		// Apply . to the correct place
		if( ( fr > 0 ) && ( fr == ( i - 1 ) ) ) {
			buf[i++] = '.';
		}
		// Parse numbers
		buf[i++] = l % 10 + '0';
		l /= 10; // Remove last number
	}
	// Add possible leading zeroes
	if ( d < 1.0 )
	{
		if ( fr )
		{
		  while( fr >= i )
		  {
		    buf[i++] = '0';	// Leading zeroes of the decimal part
		  }
		  buf[i++]= '.'; // Decimal point
		}
		buf[i++] = '0'; // Zero of the integer part
	}
	// Add possible negative sign
	if( fNegative ) {
		buf[i++] = '-';
	}

	// Print the buffer out backwards
	while(i) {
		print(buf[i--]);
	}
}

void Print::println(const char* s)
{
	if(s == NULL) {
		return ;		// Null pointer
	}
	print(s);
	println();
}
void Print::println(char c)
{
	print(c);
	println();
}
void Print::println(unsigned char c, int r)
{
	print(c,r);
	println();
}
void Print::println(int i, int r)
{
	print(i,r);
	println();
}
void Print::println(unsigned int u, int r)
{
	print(u,r);
	println();
}
void Print::println(long l, int r)
{
	print(l,r);
	println();
}
void Print::println(unsigned long ul, int r)
{
	print(ul,r);
	println();
}
void Print::println(double d, int fr)
{
	print(d,fr);
	println();
}
void Print::println(void)
{
	print("\n\r");
}
int Print::available(void)
{
	if ( ( UCSR0A & ( 1 << RXC0 ) ) ) {
		return 1;
	}
	else {
		return 0;
	}
}
unsigned char Print::read(void)
{
	// Wait until something is received
	while ( !( UCSR0A & ( 1 << RXC0 ) ) );
	return UDR0;
}
int Print::parseInt(void)
{
	char buffer[12] = { 0 };
	int i;
	for( i = 0; i < (int)sizeof(buffer); i++)
	{
		buffer[i] = read();
		print(buffer[i]);		// Echo
		if( ( buffer[i] == '-') && ( i == 0) ) {
			continue;		// Negative sign
		}
		if( ( buffer[i] < '0') || ( buffer[i] > '9') ) {
			break;		// NaN (Not a Number)
		}
	}
	return atoi(buffer);
}
float Print::parseFloat(void)
{
	char buffer[13] = { 0 };
	int i;
	for( i = 0; i < (int)sizeof(buffer); i++)
	{
		buffer[i] = read();
		print(buffer[i]);		// Echo
		if( ( buffer[i] == '-') && ( i == 0) ) {
			continue;		// Negative sign
		}
		if( buffer[i] == '.' ) {
			continue;		// Decimal point
		}
		if( ( buffer[i] < '0' ) || ( buffer[i] > '9' ) ) {
			break;		// NaN (Not a Number)
		}
	}
	return atof(buffer);
}
