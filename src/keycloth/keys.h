#ifndef KEYS_H
#define KEYS_H

/* keys.h - Keypad functionality

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

#include <Wire.h>
#include "bend.h"
#include "stretch.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

/**
 * @def NUM_KEYS
 * @brief Number of keys (12 pads on MPR121)
 */
#define NUM_KEYS 12

/**
 * @brief Keypad keys to notes
 *
 * Physical index map (hex numbering):
 *      0  1  2  3
 *    4  5  6  7
 *      8  9  A  B
 */
extern const float keyMap[NUM_KEYS];

/**
 * @brief Minimum capacity readings
 *
 * This array is filled with values read from EEPROM at runtime.
 * It contains the lowest recorded capacitance readings from the MPR121.
 * These values are influenced by the baseline readings from the sensor,
 * which themselves fluctuate due to physical factors (e.g., humidity).
 *
 * These stored values are used to determine velocity:
 * When a key is touched, its capacitance signal drops (relative to its baseline).
 * This drop is mapped onto a velocity scale, where:
 * - The stored minimum capacitance (lowest recorded touch) corresponds to
 *   the highest velocity (127, loudest sound).
 * - The baseline capacitance (untouched state) corresponds to the lowest 
 *   velocity (1, softest sound).
 * - Intermediate capacitance values are linearly interpolated between 1 and 127.
 *
 * The stored values are reset when @ref wipeEEPROM() is called.
 */
extern uint16_t minCap[NUM_KEYS];

/**
 * @brief Structure for storing keypad data.
 */
struct KeyInfo {
    bool active[NUM_KEYS]; /**< Active (pressed) keys*/
    int filtered[NUM_KEYS]; /**< Key filtered capacitance*/
    int baseline[NUM_KEYS]; /**< Key baseline capacitance */
    bool notePlayed[NUM_KEYS]; /**< For tracking playing status of notes */

    
    /**
    * @brief Constructor
    */
    KeyInfo();
};

/**
 * @brief Wipe capacitance values from EEPROM.
 */
void wipeEEPROM();

/**
 * @brief Setup the keypad.
 */
void setupKeypad();

/**
 * @brief Key interaction handler
 *
 */
void keyHandler(KeyInfo &k); 

#endif
