/*****************************************************************************
* arduino.h
*
* This is the common Arduino header for Arduino Uno platform
*
* Created: 14.3.2016 9:54:58
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


#ifndef ARDUINO_H_
#define ARDUINO_H_

// Required header files
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Datatypes
typedef uint8_t byte;
typedef uint8_t boolean;
#define true 1
#define false 0

// Constants
#define HIGH 1
#define LOW  0
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

// Analog constants
#define DEFAULT 0
#define EXTERNAL 1
#define INTERNAL 2

// Byte handling macros
#define lowByte(x) (uint8_t) (x & 0xFF)
#define highByte(x) (uint8_t) (x >> 8)
#define bitRead(x, n) (uint8_t) ((x >> n) & 1)
#define bitWrite(x, n, b) (b ? bitSet(x, n) : bitClear(x, n))
#define bitSet(x, n) (x = x | (1 << n))
#define bitClear(x, n) (x = x & ~(1 << n))
#define bit(n) (1 << n)

// Other useful macros
// Undefine <stdlib> abs
#ifdef abs
#undef abs
#endif

#define min(a,b) ((a < b) ? a : b)
#define max(a,b) ((a > b) ? a : b)
#define abs(a) ((a < 0) ? -a : a)
#define constrain(x,a,b) ((x < a) ? a : (x > b ? b : x))
#define map(x, in_min, in_max, out_min, out_max) (((x - in_min) * (out_max - out_min)) / (in_max - in_min) + out_min)
#define round(x) ((x) >= 0 ? (long)((x)+0.5) : (long)((x)-0.5))

// Function declarations
void setup();
void loop();

// Digital port functions
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin , uint8_t value);
int digitalRead(uint8_t pin);

// Timer functions
unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long);
void delayMicroseconds(unsigned int us);
void init(void); // Timer initialization

// Analog functions
int analogRead(uint8_t port);
void analogReference(uint8_t mode);
void analogWrite(uint8_t port, int value);

// Serial traffic functions + constants
#define DEC 10
#define HEX 16
#define BIN 2
class Print
{
	public:
	void begin(long baud); // Speed setting

	int available(void);  // Is there any characters to read ?
	unsigned char read(void); // Reading a char
	int parseInt(void); // Integer
	float parseFloat(void); // Floating point
	void print(const char *); // Print string
	void print(char); // Print char
	void print(unsigned char, int = DEC); // Print byte
	void print(int , int  = DEC);
	void print(unsigned int, int = DEC);
	void print(long, int = DEC);
	void print(unsigned long, int = DEC);
	void print(double, int = 3);

	void println(const char[]);
	void println(char);
	void println(unsigned char, int = DEC);
	void println(int, int = DEC);
	void println(unsigned int, int = DEC);
	void println(long, int = DEC);
	void println(unsigned long, int = DEC);
	void println(double, int = 2);
	void println(void);
};

extern Print Serial; // Defined in main.cpp

#endif /* ARDUINO_H_ */