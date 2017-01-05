/*****************************************************************************
 * application.cpp
 *
 * Created: 22.3.2016 11:28:38
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


void setup()
{
	// Hardware settings
	Serial.begin(9600);
}
void loop()
{
	// Application code

	// unsigned char x = 32;
	//
	// Serial.print("\r\nHexana:"); Serial.print(x,HEX);
	// Serial.print("\r\ndesimaalisena:"); Serial.print(x,DEC);
	// Serial.print("\r\nBinaarina:"); Serial.print(x,BIN);
	// delay(1000);
	// Serial.println();
	// double y = 123.345678;
	// Serial.println(y,0);
	// Serial.println(y,1);
	// Serial.println(y,2);
	// Serial.println(y,3);
	// Serial.println(y,4);
	// Serial.println();
	// delay(1000);

	double x;
	int y;

	Serial.print("\n\rAnna liukuluku? ");
	x = Serial.parseFloat();

	Serial.print("\n\rAnna kokonaisluku? ");
	y = Serial.parseInt();

	Serial.print("\n\rx = "); Serial.println((double)x);
	Serial.print("\n\ry = "); Serial.println(y);

}

