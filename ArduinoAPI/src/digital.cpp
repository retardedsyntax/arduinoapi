/*****************************************************************************
 * digital.cpp
 *
 * This file contains basic digital port handling functionality.
 *
 * Created: 21.3.2016 10:24:12
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


void pinMode(uint8_t pin, uint8_t mode)
{
	if (pin <= 7)
	{
		// We are using PORTD
		if (mode == OUTPUT) {
			DDRD = DDRD | (1 << pin);
		}
		else if (mode == INPUT) {
			DDRD = DDRD & ~(1 << pin);
		}
		else if (mode == INPUT_PULLUP) {
			DDRD = DDRD & ~(1 << pin);
			PORTD = PORTD | (1 << pin);
		}
	}
	else if ((pin >= 8) && (pin <= 13))
	{
		pin -= 8; // Scale pin number to correct zone
		// We are using PORTB
		if (mode == OUTPUT) {
			DDRB = DDRB | (1 << pin);
		}
		else if (mode == INPUT) {
			DDRB = DDRB & ~(1 << pin);
		}
		else if (mode == INPUT_PULLUP) {
			DDRB = DDRB & ~(1 << pin);
			PORTB = PORTB | (1 << pin);
		}
	}
}
void digitalWrite(uint8_t pin , uint8_t value)
{
	if (pin <= 7)
	{
		// We are using PORTD
		(value) ? (PORTD = PORTD | (1 << pin)) : (PORTD = PORTD & ~(1 << pin));
	}
	else if ((pin >= 8) && (pin <= 13))
	{
		pin -= 8; // Scale pin number to correct zone
		// We are using PORTB
		(value) ? (PORTB = PORTB | (1 << pin)) : (PORTB = PORTB & ~(1 << pin));
	}
}
int digitalRead(uint8_t pin)
{
	if (pin <= 7)
	{
		// We are using PIND
		return ((PIND & (1 << pin)) >> pin);
	}
	else if ((pin >= 8) && (pin <= 13))
	{
		pin -= 8; // Scale pin number to correct zone
		// We are using PINB
		return ((PINB & (1 << pin)) >> pin);
	}
	return 0;
}