/* stretch.cpp - Implementation of stretch sensor functionality

   Copyright (C) 2025

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

#include "pins.h"
#include "stretch.h"
#include "utils.h"
#include <Arduino.h>

#define STRETCH 3

/**
 * @brief Setup the stretch sensor.
 */
void setupStretch() {
  // Set pin mode
  pinMode(stretchPin, INPUT);
}

/**
 * @brief Read from the sensor.
 */
void readStretch() {
  // Read analog
  sInfo[RAW_I] = analogRead(stretchPin);
  sInfo[VOUT_I] = calcVout(sensorVin, sInfo[RAW_I]);
  sInfo[R_I] = determineRes(sensorVin, sInfo[VOUT_I], R0);
}
