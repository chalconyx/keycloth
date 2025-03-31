/* bend.cpp - Implementation of bend sensor functionality

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
#include "bend.h"
#include "utils.h"
#include <Arduino.h>

// unused atm
const float alpha = 0.3;            // Smoothing factor
const float spikeThreshold = 100.0; // Ignore sudden jumps at bending event
const float deadZone = 5.0;         // Ignore tiny fluctuations within ±1 units

/**
 * @brief Rest state resistance upper limit.
 */
float maxR[NUM_BEND];

/**
 * @brief Minimum read resistance at runtime.
 */
float minR[NUM_BEND];

/**
 * @brief BendInfo constructor
 *
 * This struct is to be created at setup. Its values are then updated during
 * runtime by keyHandler().
 */
BendInfo::BendInfo()
{
  for (int i = 0; i < NUM_BEND; i++)
  {
    // Retrieve baseline resistances
    raw[i] = analogRead(bendPins[i]);
    Vout[i] = calcVout(sensorVin, raw[i]);
    R[i] = determineRes(sensorVin, Vout[i], R0);
    // Bend sensor is flat == Highest resistance
    // The device might be initialized with bent bend sensors,
    // so we set the highest possible baseline in that case
    // (baseline is periodically calibrated)
    baseline[i] = R[i] > 500 ? R[i] : INIT_MAXR;
  }
}

/**
 * @brief Setup the bend sensor(s).
 */
void setupBend()
{
  // Set pin mode
  for (int i = 0; i < NUM_BEND; i++)
  {
    pinMode(bendPins[i], INPUT);
    minR[i] = MAXR;
    maxR[i] = INIT_MAXR;
  }
}

// unused atm
float filterBend(float resistance, float prev_out)
{
  float ret = prev_out;
  // Ignore large sudden spikes
  if (fabs(resistance - prev_out) < spikeThreshold)
  {
    // Only update if the change is bigger than deadZone
    if (fabs(resistance - prev_out) > deadZone)
    {
      ret = alpha * resistance + (1.0 - alpha) * prev_out;
    }
  }
  return ret;
}

/**
 * @brief Read from the bend sensor(s).
 *
 * @b: BendInfo struct to store information in.
 * @return BendInfo struct containing relevant information.
 */
BendInfo readBend(BendInfo &b)
{
  // Read analog
  for (int i = 0; i < NUM_BEND; i++)
  {
    b.raw[i] = analogRead(bendPins[i]);
  }
  // Get voltages and resistances
  for (int i = 0; i < NUM_BEND; i++)
  {
    b.Vout[i] = calcVout(sensorVin, b.raw[i]);
    b.R[i] = min(MAXR, determineRes(sensorVin, b.Vout[i], R0));
    // Update max/min read resistance
    if (b.R[i] < minR[i])
    {
      minR[i] = b.R[i];
    }
    if (b.R[i] > maxR[i])
    {
      maxR[i] = b.R[i];
    }
    b.out[i] = filterBend(b.R[i], b.out[i]);
  }
  return b;
}

// unused functions

bool isBent(float sensorValue, float baseline)
{
  return sensorValue < baseline * 0.85;
}

void updateBaseline(BendInfo &b)
{
  for (int i = 0; i < NUM_BEND; i++)
  {
    if (!isBent(b.out[i], b.baseline[i]))
    {
      // Update baseline only when the sensor is in a flat state
      b.baseline[i] = (1 - CALIBRATION_ALPHA) * b.baseline[i] + CALIBRATION_ALPHA * b.out[i];
      b.isBaselineFrozen[i] = false;
    }
    else if (!b.isBaselineFrozen[i])
    {
      // If the sensor is bent, freeze baseline updates
      b.isBaselineFrozen[i] = true;
    }
  }
}