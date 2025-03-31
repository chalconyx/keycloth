#include "keys.h"
#include <Wire.h>
#include <Adafruit_MPR121.h>
#include "pitchToNote.h"
#include <EEPROM.h>

/* keys.cpp - Implementation of keypad functionality

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

/**
 * @def TOUCH_THRESHOLD
 * @brief Sensitivity threshold for touch recognition (MPR121)
 */
#define TOUCH_THRESHOLD 12

/**
 * @def RELEASE_THRESHOLD
 * @brief Sensitivity threshold for release recognition (MPR121)
 */
#define RELEASE_THRESHOLD 6

uint16_t minCap[NUM_KEYS];

/**
 * @brief Keypad keys to notes
 *
 * Physical index map (hex numbering):
 *      0  1  2  3
 *    4  5  6  7
 *      8  9  A  B
 */
const float keyMap[] = {
  D3, G3b, B3, D4,
  F3, A3, D4b, F4, 
  C3, E3, A3b, C4
};

/**
 * @brief Hardcoded minimum capacitance values in case of uninitialized/wiped EEPROM.
 */
uint16_t defaultMinCap[NUM_KEYS] = {80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80};

/**
 * @brief Initialize the Adafruit MPR121 sensor.
 */
Adafruit_MPR121 cap = Adafruit_MPR121();

/**
 * @brief KeyInfo constructor.
 */
KeyInfo::KeyInfo() {}

/**
 * @brief Load minimum capacitance values from EEPROM.
 */
void loadMinCap() {
    for (int i = 0; i < NUM_KEYS; i++) {
        EEPROM.get(i * sizeof(uint16_t), minCap[i]);  // EEPROM access

        // If EEPROM contains uninitialized data use default values
        if (minCap[i] == 0xFFFF) {
          // Serial.print("No stored minimum value for key ");
          // Serial.print(i);
          minCap[i] = defaultMinCap[i];
          // Save default in EEPROM
          EEPROM.put(i * sizeof(uint16_t), minCap[i]);
        }
    }
    
}

/**
 * @brief Update minimum capacitance value in EEPROM.
 */
void updateMinCap(int keyIndex, uint16_t capVal) {
  minCap[keyIndex] = capVal;
  EEPROM.put(keyIndex * sizeof(uint16_t), capVal);
  Serial.print("Updated minimum capacitance record for key ");
  Serial.print(keyIndex);
  Serial.print(": ");
  Serial.println(capVal);
}

/**
 * @brief Wipe capacitance values from EEPROM.
 */
void wipeEEPROM() {
  uint16_t resetValue = 0xFFFF;
  for (int i = 0; i < NUM_KEYS; i++) {
      EEPROM.put(i * sizeof(uint16_t), resetValue); 
  }
}

/**
 * @brief Setup the keypad.
 */
void setupKeypad() {
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  // Calibrate sensitivity 
  cap.setThresholds(TOUCH_THRESHOLD, RELEASE_THRESHOLD);
  loadMinCap();
}

/**
 * @brief Key interaction handler
 */
void keyHandler(KeyInfo &k) {
  // Get the currently touched pads
  uint16_t currtouched = cap.touched();

  // debugging info (copied from Adafruit MPR121 example)
  // Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); 
  // Serial.println(cap.touched(), HEX);
  // Serial.print("Filt: ");
  // for (uint8_t i=0; i<NUM_KEYS; i++) {
  //   Serial.print(cap.filteredData(i)); Serial.print("\t");
  // }
  // Serial.println();
  // Serial.print("Base: ");
  // for (uint8_t i=0; i<NUM_KEYS; i++) {
  //   Serial.print(cap.baselineData(i)); Serial.print("\t");
  // }
  // Serial.println();

  // KEY ACTIVATION
  for (uint8_t i=0; i < NUM_KEYS; i++) {
    // Touch recognition according to thresholds
    k.active[i] = currtouched & _BV(i);
    k.baseline[i] = cap.baselineData(i);
    if (k.active[i]) { // if touched
      // Extract and store filtered capacitance
      k.filtered[i] = cap.filteredData(i); ;
      // If applicable, update minimum capacitance value for key in EEPROM.
      if (k.filtered[i] < minCap[i]) updateMinCap(i, k.filtered[i]);
    }
    else k.filtered[i] = 0;
  }
}



