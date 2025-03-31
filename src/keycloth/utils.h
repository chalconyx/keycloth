#ifndef UTILS_H
#define UTILS_H

/* utils.h - Miscellaneous functions

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
 * @brief Analog signal input resolution
 */
extern int analogResolution;

/**
 * @brief Calculate Vout from analog signal and fixed Vin.
 *
 * @Vin: Input voltage.
 * @raw: Raw analog input.
 */
float calcVout(float Vin, int raw);

/**
 * @brief Calculate unknown resistance value in voltage divider resistor.
 *
 * @Vin: Input voltage.
 * @Vout: Output voltage.
 * @raw: Raw analog input.
 */
float determineRes(float Vin, float Vout, float R0);

/**
 * @brief Calculate average over floats.
 * 
 * @values: Values to average over.
 * @size: Total number of values.
 */
float avg(float values[], int size);

#endif
