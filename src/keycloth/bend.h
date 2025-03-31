#ifndef BEND_H
#define BEND_H

/* bend.h - Bend sensor functionality

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

#define NUM_BEND 3
#define MAXR 1000
#define INIT_MAXR 500
#define LEFT 1
#define RIGHT 0
#define MIDDLE 2
#define FILTER_LOW  40   // Default cutoff (dark)
#define FILTER_HIGH 100  // Bent cutoff (bright)
#define CALIBRATION_ALPHA 0.01

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
 * @brief Rest state resistance upper limit.
 */
extern float maxR[NUM_BEND]; // 

/**
 * @brief Minimum read resistance at runtime.
 */
extern float minR[NUM_BEND];

/**
 * @brief Structure for storing bend sensor data.
 */
struct BendInfo {
    int raw[NUM_BEND]; /**< Raw pin read values */
    float Vout[NUM_BEND]; /**< Calculated Vout */
    float R[NUM_BEND]; /**< Calculated R of bend sensor */
    float out[NUM_BEND]; /**< Smoothed and filtered sensor output */
    float baseline[NUM_BEND]; /**< Baseline values for bend detection */
    bool isBaselineFrozen[NUM_BEND]; /**< Monitoring flag for baseline calibration */
    
    /**
    * @brief Constructor
    */
    BendInfo();
};

/**
 * @brief Setup the bend sensor(s).
 */
void setupBend();

/**
 * @brief Read from the bend sensor(s).
 *
 * @b: BendInfo struct to store information in.
 * @return BendInfo struct containing relevant information.
 */
BendInfo readBend(BendInfo &b);

#endif