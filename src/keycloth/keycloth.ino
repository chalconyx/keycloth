/*
 * Arduino Project Name: KeyCloth
 *
 * Copyright (C) 2025
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 * Flexible musical interface.
 */

#include "keys.h"
#include "pins.h"
#include "bend.h"
#include "stretch.h"
#include "midi.h"

/**
 * SET FIXED VALUES
 **/
int* bendPins = new int[NUM_BEND] {A0, A1, A2}; // bend sensor pins

int stretchPin = A3; // stretch sensor pin

float sensorVin = 5; // Vin for DIY-ed sensors
float R0 = 1000; // Reference resistor of voltage divider (bend)

int channel = 0; // Audio output channel

bool debug = true; // Flag to output to Serial

KeyInfo k;
BendInfo b;
float sInfo[NUM_STRETCH_DATA];
/** 
 * END 
 **/

void setup(){
  Serial.begin(9600);
  // wipeEEPROM(); // for debugging, TODO extra physical button to call at runtime
  // Keys
  
  setupKeypad();
  // Bend sensors
  setupBend();
  b = BendInfo();
  // Stretch sensor
  setupStretch();
}

void loop(){
  // Read sensors
  readBend(b);
  readStretch(); // loads to global var
  keyHandler(k);

  handleSignals(k, b, sInfo);

  // /**
  //  * MONITORING / DEBUGGING
  //  **/
  if (debug) {
    String msg = "";

  // Keys
  // for (int i = 0; i < NUM_KEYS; i++) {
  //   msg = String(i) + "\t" + (k.active[i] ? "active" : "off") + "\t" + String(k.values[i]);
  //   Serial.println(msg); 
  // }

  // Bend
  for (int i = 0; i < NUM_BEND; i++) {
    msg = "raw("+ String(i) + ")=" + b.raw[i] + "\tVout("+ String(i) + ")=" + String(b.Vout[i], 2) + "\tR("+ String(i) + ")=" + String(b.R[i], 2);
    Serial.println(msg);  
  }
  // Stretch
  msg = "raw(s)=" + String((int)(sInfo[RAW_I])) + "\tVout(s)=" + String(sInfo[VOUT_I], 2) + "\tR(s)=" + String(sInfo[R_I], 2);
  Serial.println(msg);

  }
  /**
   * END MONITORING / DEBUGGING
   **/
}
