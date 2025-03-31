#ifndef STRETCH_H
#define STRETCH_H

/* stretch.h - Stretch sensor functionality

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

#define S 3

/**
 * @def RAW_I
 * @brief Stretch sensor read value index for raw value.
 */
#define RAW_I 0
/**
 * @def VOUT_I
 * @brief Stretch sensor read value index for Vout.
 */
#define VOUT_I 1
/**
 * @def R_I
 * @brief Stretch sensor read value index for R.
 */
#define R_I 3

/**
 * @def NUM_STRETCH_DATA
 * @brief Number of stretch sensor relevant data.
 */
#define NUM_STRETCH_DATA 3

/**
 * @brief Stretch sensor read information.
 * 
 * Float array containing relevant information. 
 *          [RAW_I]: raw read value
 *          [VOUT_I]: Vout
 *          [R_I]: R
 */
extern float sInfo[NUM_STRETCH_DATA];

/**
 * @brief Input voltage for sensor pin(s).
 *
 * This is the input voltage applied to the sensor circuit(s).
 * It should be set according to the used voltage pin (e.g., 3.3V).
 */
extern float sensorVin;

/**
 * @brief Reference resistance for determining sensor resistance.
 *
 * This value represents the known resistance (R0) of the voltage divider
 * used to determine the sensor resistance. 
 */
extern float R0;

/**
 * @brief Setup the stretch sensor.
 */
void setupStretch();

/**
 * @brief Read from the sensor.
 */
void readStretch();

#endif
