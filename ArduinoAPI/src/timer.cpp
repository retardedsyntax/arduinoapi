/****************************************************************************
 * timer.cpp
 *
 * This file contains timer related functionality.
 * Delay functions use Timer0 as a clock source.
 *
 * Created: 24.3.2016 10:56:38
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


volatile unsigned long milliSeconds = 0;	// Millisecond counter variable
volatile unsigned long microSeconds = 0;	// Microsecond counter variable
volatile unsigned long tout_ms = 0;			// Delay timeout in milliseconds


void init()
{
	 TCCR0A = 2;									// No output control, clear counter on compare match (CTC-mode)
	 TCCR0B = 3;									// System clock / 64 = 4uS
	 OCR0A = 250;									// 1ms = 250 * 4uS = 1000 uS
	 TIMSK0 =  TIMSK0 | ( 1 << OCIE0A);				// Compare value A in use
	 TIFR0 = TIFR0 | (1 << OCF0A);					// Clear interrupt flag

	 TCNT1 = 0;										// Clear counting register

	 sei();											// Enable hardware interrupts
}
unsigned long millis(void)
{
	unsigned long localCopy;

	cli();			// Disable hardware interrupts

	/*	Local copy of milliseconds value is used to avoid corrupted values. If the milliseconds value were updated by
		the interrupt when we are transferring the value via transfer bus, rest of the value would be corrupted.
		This is why we copy the value to local variable and return that	*/
	localCopy = milliSeconds;

	sei();			// Enable hardware interrupts
	return localCopy;
}
unsigned long micros(void)
{
	unsigned long us;
	us = ( milliSeconds * 1000 ) + ( TCNT0 << 2 );
	return us;
}
void delay(unsigned long ms)
{
	if (ms == 0) {
		return;
	}
	else {
		tout_ms = ms;
		// Wait until tout_ms == 0
		while(tout_ms);			// tout_ms is updated by hardware interrupt
	}
}
void delayMicroseconds(unsigned int us)
{
	if (us < 4) {
		return;		// Cannot do delays under 4 us
	}
	else {
		unsigned int ms;
		unsigned int us_extra;

		// If delay is over 1ms, we'll use milliseconds delay() as a helper function
		if (us > 1000)
		{
			ms = us / 1000;
			delay(ms);
			us = us - (ms * 1000); // ms removed
		}

		// Wait for the rest of the time
		us = us >> 2; // us => 4us units

		if (us < (unsigned)(250 - TCNT0))
		{
			us_extra = us + TCNT0;
			while(TCNT0 < us_extra); // Wait
		}
		else
		{
			us = us - (unsigned)(250 - TCNT0);
			while (TCNT0 < 250);
			while(TCNT0 < us); // Wait
		}
	}
}


// This interrupt is called at 1ms intervals
ISR((TIMER0_COMPA_vect))
{
	milliSeconds++;
	// Handling timeouts
	if (tout_ms > 0)
	{
		tout_ms--; // Decrement timeout once in a millisecond
	}
}
