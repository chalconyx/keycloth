#ifndef PINS_H
#define PINS_H

/* pins.h - Pin declarations

   Copyright (C) 2025 Alexia Pagkopoulou

    This file is part of KeyCloth.

    KeyCloth is free software: you can redistribute it and/or modify it 
    under the terms of the GNU General Public License as published by the 
    Free Software Foundation, either version 3 of the License, or (at your 
    option) any later version.

    KeyCloth is distributed in the hope that it will be useful, but WITHOUT 
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
    more details.

    You should have received a copy of the GNU General Public License along 
    with KeyCloth. If not, see <https://www.gnu.org/licenses/>. 
*/

/**
 * @brief Board pin identifiers for pins dedicated to bend sensors.
 */
extern int* bendPins;

/**
 * @brief Board pin identifier for the pin dedicated to the stretch sensor.
 */
extern int stretchPin;

#endif
