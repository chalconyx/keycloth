#include "midi.h"
#include "MIDIUSB.h"
#include "stretch.h"
#include "pitchToNote.h"

/* midi.cpp - Implementation of MIDI driver

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

#define MIDDLE_THRESHOLD 70

static int lastBend[NUM_BEND] = {-1, -1 ,-1};  
bool isCrumpled = false;
bool isStretched = false;

/**
 * @brief Send MIDI note on signal
 *
 * @pitch: Note MIDI pitch
 * @velocity: Note velocity
 */
void noteOn(int pitch, int velocity) {
  MidiUSB.sendMIDI({NOTE_ON, 0x90 | channel, pitch, velocity});
  MidiUSB.flush();
}

/**
 * @brief Send MIDI note off signal
 *
 * @pitch: Note MIDI pitch
 */
void noteOff(int pitch) {
  MidiUSB.sendMIDI({NOTE_OFF, 0x80 | channel, pitch, 0});
  MidiUSB.flush();
}

/**
 * @brief Consolidate input signals and send out MIDI data.
 *
 * @sensorValue: Numeric output after reading sensor input.
 * @sensorIndex: Sensor identifier
 */
void controlChange(float sensorValue, int sensorIndex) {
    uint8_t midiCC = -1;

    switch (sensorIndex) {
      case LEFT: {
        midiCC = 1;
      }
      case RIGHT: {
        midiCC = 1;
        // Reverse mapping: Highest resistance (flat) = 0, Lowest resistance (bent) = 127
        uint8_t midiValue = map((int)floor(sensorValue), (int)floor(minR[sensorIndex]), (int)maxR[sensorIndex], 127, 0);
        midiValue = constrain(midiValue, 0, 127);  // Ensure valid MIDI range

        // Only send MIDI if the value has changed significantly
        if (abs(midiValue - lastBend[sensorIndex]) > 2) {  
          midiEventPacket_t event = {0x0B, 0xB0 | channel, midiCC, midiValue};
          MidiUSB.sendMIDI(event);
          MidiUSB.flush();  // Ensure MIDI data is sent immediately
          lastBend[sensorIndex] = midiValue;  // Update last sent value
        }
        break;
      }
      case MIDDLE:
        if (sensorValue < 100.0 && !isStretched) {
          int velocity = map((int)floor(sensorValue), MIDDLE_THRESHOLD, minR[sensorIndex], 1, 127);
          if (!isCrumpled) {
            noteOn(C2, velocity);  // Trigger drum hit
            delay(50);  // Prevent retriggering too fast
          } else {
            noteOff(C2);
            isCrumpled = false;
          }
        }
        break;
      case S: {
        isStretched = sensorValue < 250.0;
        if (isStretched) {
          if (sensorValue < 100.0 && !isCrumpled) {
          int velocity = map((int)floor(sensorValue), MIDDLE_THRESHOLD, minR[sensorIndex], 1, 127);
          if (!isCrumpled) {
            noteOn(C2, velocity);  // Trigger drum hit
            delay(50);  // Prevent retriggering too fast
          } else {
            noteOff(C2);
            isStretched = false;
          }
        }
        }
        break;
      }
    }
}

/**
 * @brief Consolidate input signals and send out MIDI data.
 *
 * @k: Key input data.
 * @b: Bend sensor input data.
 * @stretch: Stretch sensor input data.
 */
void handleSignals(KeyInfo &k, BendInfo &b, float sInfo[]) {
  // BEND MOD
  for (int i = 0; i < NUM_BEND; i++) { 
    controlChange(b.R[i], i);
  }
  // STRETCH MOD
  controlChange(sInfo[R_I], S);

  // PLAY NOTE 
  for (int i = 0; i < NUM_KEYS; i++) {
    if (k.active[i]) {  
      // PRESSURE MOD
      // Map capacitance drop to velocity
      int velocity = map(k.filtered[i], k.baseline[i], minCap[i], 1, 127);
      if (!k.notePlayed[i]) {  // If the note hasn't been played yet
          noteOn(keyMap[i], velocity);  // Play the note
          k.notePlayed[i] = true;    // Mark the note as played
          delay(100);
      }
    } else {
      if (k.notePlayed[i]) {  // If the note was previously played and key is now released
          noteOff(keyMap[i]);  // Stop the note
          k.notePlayed[i] = false;  // Reset the note as not played
      }
    }
  }
}




