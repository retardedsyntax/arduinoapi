/****************************************************************************
 * analog.cpp
 *
 * This file contains basic analog signal handling functionality.
 *
 * Created: 8.4.2016 14:12:25
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

#include "arduino.h"


#define PWM9_PORT 1
#define PWM10_PORT 2
#define PWM11_PORT 1

int analogRead(uint8_t port)
{
	int  result = 0;
	int i;

	// 1. Choosing port
	ADMUX = (ADMUX & 0xF0) | (port & 0x7);

	// Choosing measurement frequency (default = 125kHz)
	bitSet(ADCSRA, ADPS2);
	bitSet(ADCSRA, ADPS1);
	bitSet(ADCSRA, ADPS0);

	// AD converter on
	bitSet(ADCSRA, ADEN);

	// If there is distortion on the signal to be measured, it is recommended to measure multiple times
	// and divide the result to avoid errors.

	// On default settings conversion is done 8 times.
	for (i = 0; i < 8; i++)
	{
		bitSet(ADCSRA, ADSC); // Start converting

		while(!(ADCSRA& (1 << ADIF))); // Wait until conversion is complete

		result += ADC;         // Read result
	}

	// Divide result by 8
	result = result >> 3;

	// Turn off AD converter to save energy
	bitClear(ADCSRA, ADEN);

	return result;
}
void analogReference(uint8_t mode)
{
	switch (mode)
	{
		case DEFAULT:
			bitSet(ADMUX, REFS0);
			bitClear(ADMUX, REFS1);
		break;
		case EXTERNAL:
			bitClear(ADMUX, REFS0);
			bitClear(ADMUX, REFS1);
		break;
		case INTERNAL:
			bitSet(ADMUX, REFS0);
			bitSet(ADMUX, REFS1);
		break;
	}
}
void analogWrite(uint8_t port, int value)
{
	//PWM Control
	if(port == 9)
	{
		bitSet(DDRB, PWM9_PORT); // PWM-pin OC1A to output
		bitSet(TCCR1A, COM1A1);
		bitSet(TCCR1A, COM1B1);
		bitSet(TCCR1A, WGM10); // Clear timer when OCR1A is reached + phase-corrected calculation in range 0..255
		bitSet(TCCR1B, CS11);
		bitSet(TCCR1B, CS10);      // Counter input freq = 16000000 Hz / 64  = 250000Hz. These pulses are calculated 256 pcs up and 256 pcs down => PWM pulse freq = 250000Hz/256/2 = 488Hz
		OCR1A = (value & 0xFF);
	}
	else if(port == 10)
	{
		bitSet(DDRB, PWM10_PORT); // PWM-pin OC1B to output
		bitSet(TCCR1A, COM1A1);
		bitSet(TCCR1A, COM1B1);
		bitSet(TCCR1A, WGM10); // Clear timer when OCR1B is reached + phase-corrected calculation in range 0..255
		bitSet(TCCR1B, CS11);
		bitSet(TCCR1A, CS10); // Counter input freq = 16000000 Hz / 64  = 250000Hz. These pulses are calculated 256 pcs up and 256 pcs down => PWM pulse freq = 250000Hz/256/2 = 488Hz
		OCR1B = (value & 0xFF);
	}
	else if(port == 11)
	{
		bitSet(DDRB, PWM11_PORT); // PWM-pin OC2A to output
		bitSet(TCCR2A, COM2A1);
		bitSet(TCCR2A, WGM20); // Clear timer when OCR2A is reached + phase-corrected calculation in range 0..255
		bitSet(TCCR2B, CS22); // Counter input freq = 16000000 Hz / 64  = 250000Hz. These pulses are calculated 256 pcs up and 256 pcs down => PWM pulse freq = 250000Hz/256/2 = 488Hz
		OCR2A = (value & 0xFF);
	}
}

