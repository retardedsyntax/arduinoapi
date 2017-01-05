/****************************************************************************
 * main.cpp
 *
 * This is the C/C++ main() function
 *
 * Created: 21.3.2016 11:45:10
 * Author: Joonas Onatsu
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


Print Serial;  // For serial traffic use

int main(void)
{
	init();
	setup();

	while(1) loop();
}
