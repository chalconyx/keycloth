# KeyCloth
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Codebase for KeyCloth, a flexible and deformable MIDI Keyboard.

## Hardware Requirements
- [Arduino Leonardo](https://docs.arduino.cc/hardware/leonardo/)
- [Adafruit MPR121](https://www.adafruit.com/product/1982)
- Conductive fabric
- Conductive rubber sheet (or just cord)
- Conductive thread
- Velostat sheet
- Jumper wires
- Resistors
- Sewing supplies (fabrics, non-conductive thread, snap fasteners, etc.)
- Breadboard (optional)

## Software Requirements

This codebase was developed using [Arduino IDE](https://docs.arduino.cc/software/ide/).

### Library Dependencies

Before compiling and uploading the sketch, make sure you have installed the following libraries:

| Library           | Version  | Source                                                 |
| ----------------- | -------- | ------------------------------------------------------ |
| `MIDIUSB`         | > 1.0.5  | [Github](https://github.com/arduino-libraries/MIDIUSB) |
| `Adafruit BusIO`  | > 1.17.0 | [GitHub](https://github.com/adafruit/Adafruit_BusIO)   |
| `Adafruit MPR121` | > 1.1.3  | [GitHub](https://github.com/adafruit/Adafruit_MPR121)  |

These are included in this repository for convenience and can also be loaded directly through the [Arduino Library Manager](https://www.arduino.cc/en/guide/libraries).

## Setup

### Connecting the components to the Arduino
- [Adafruit MPR121 Wiring Tutorial](https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/wiring)
- *Resistive sensors TODO*
- *Overall schematic with picture TODO* 

### Setting the system parameters
The following system parameters depend on the physical configuration of the sensors:                                                             

| Variable Name | Variable Dtype | System Parameter        | Description                                                           | Current Setup Value |
| ------------- | -------------- | ----------------------- | --------------------------------------------------------------------- | ------------------- |
| `bendPinsCnt` | `int`          | Bend sensor pin count   | The number of pins with bend sensor anodes connected to them.         | `3`                 |
| `bendPins`    | `int*`         | Bend sensor pins        | The analog input pin identifiers where the bend sensors are connected. | `{A0, A1, A2}`      |
| `stretchPin`  | `int`          | Stretch sensor pin      | The analog input pin for the stretch sensor.                          | `A3`                |
| `sensorVin`   | `float`        | Sensor voltage (Vin)    | The voltage supplied to the resistive sensors.                        | `5`                 |
| `R0`          | `float`        | Reference resistor (R0) | The reference resistor value used in the sensor voltage divider.      | `100`               |
| `channel`     | `int`          | Audio output channel    | The audio output channel number.                                      | `0`                 |
| `debug`       | `bool`         | Debug flag              | Enables serial output for debugging purposes.                         | `false`             |

### Connecting the keys and sensors to the board(s)

The 12 key connections for the keyboard cloth are connected directly to the MPR121, with 0 being the top left hexagon key, 1 the key to its left and so on.

The resistive sensors all share the same anode (5V or 3.3V), and have separate GND connection. Refer to the schematic for details. *TODO*


## Troubleshooting
### Uploading source code to Leonardo in MIDI mode
When the Arduino Leonardo board is registered as a MIDI USB controller on the host device, it stops receiving code via USB. Uploading new code (e.g. through the Arduino IDE) requires to reset it beforehand:

1. Hold down the reset button on the Arduino board.
2. Click Upload on the Arduino IDE.
3. Release the reset button.

## License
This project is licensed under the GPLv3 License - see the [LICENSE](LICENSE) for details.
