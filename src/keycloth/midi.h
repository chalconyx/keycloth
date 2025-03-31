#ifndef MIDI_H
#define MIDI_H

/* midi.h - MIDI driver

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

#include "keys.h"
#include "bend.h"

/**
 * @def NOTE_ON
 * @brief Note on event code
 */
#define NOTE_ON 0x09
/**
 * @def NOTE_OFF
 * @brief Note off event code
 */
#define NOTE_OFF 0x08

/**
 * @brief MIDI channel to be used
 */
extern int channel;

/**
 * @brief Send MIDI note on signal
 *
 * @pitch: Note MIDI pitch
 * @velocity: Note velocity
 */
void noteOn(int pitch, int velocity);

/**
 * @brief Send MIDI note off signal
 *
 * @pitch: Note MIDI pitch
 */
void noteOff(int pitch);

/**
 * @brief Consolidate input signals and send out MIDI data.
 *
 * @k: Key input data.
 * @b: Bend sensor input data.
 * @stretch: Stretch sensor input data.
 */
void handleSignals(KeyInfo &k, BendInfo &b, float stretch[]);

#endif