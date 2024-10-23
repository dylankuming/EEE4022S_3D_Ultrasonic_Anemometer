# 3D Ultrasonic Anemometer (EEE4022S)

This project implements a **3D ultrasonic anemometer** for measuring wind data across three axes: North-South (NS), East-West (EW), and Top-Bottom (TB). The system uses ultrasonic transducers and calculates wind speed by measuring the time-of-flight (ToF) of sound pulses between the transducers.

The original 2D version of the code was written by **Lukas Fässler** and has been modified for 3D wind measurements by **Dylan Kuming**.


## Overview

The **3D Ultrasonic Anemometer** measures wind speed in all three dimensions using ultrasonic transducers. The time difference in sound pulses between pairs of transducers provides the wind speed, while the direction and elevation angle are computed based on phase and vertical components.

### Key Features:
- **3D Wind Measurement**: Accurate wind measurement in NS, EW, and TB axes.
- **Temperature Sensor**: Used for temperature compensation as it affects the speed of sound.
- **LCD Display**: Provides a real-time display of measurements.
- **Arduino Controlled**: The system is managed using an Arduino microcontroller.

### Components:
- **Ultrasonic Transducers**: Measure wind speed through sound waves.
- **Temperature Sensor**: Reads ambient temperature to account for speed of sound variation.
- **LCD Display**: Shows real-time measurements such as wind speed, phase, and elevation. (ref Matlab code for visual output option)
- **Arduino**: Controls the ultrasonic pulses and processes the wind data.

### Project Structure:
- `3D_Ultrasonic_Anemometer.ino`: Contains the Arduino code that handles the measurement process.

## How It Works

1. **Sound Pulse Emission**: The Arduino controls the ultrasonic transducers to emit sound pulses along the three axes.
2. **Time-of-Flight (ToF) Calculation**: The time taken for the pulse to travel between transducers is measured.
3. **Wind Speed and Direction**: Wind speed is calculated from the difference in ToF along opposite directions (e.g., NS vs SN). The direction is determined using trigonometry.
4. **Vertical Wind Component**: The system also calculates the vertical wind speed using the top-bottom axis.

### Measurements:
- **NS Wind Speed**: Wind speed in the North-South axis.
- **EW Wind Speed**: Wind speed in the East-West axis.
- **TB Wind Speed**: Wind speed in the Top-Bottom axis.
- **Magnitude**: Overall wind speed magnitude across the three axes.
- **Phase**: Wind direction in degrees.
- **Elevation**: Vertical angle of the wind.

## Hardware Setup

The following components and connections are used in the project:

- **AXIS1 (Pin 13)**: Controls the first axis (Horizontal vs Vertical).
- **AXIS2 (Pin 12)**: Controls the second axis (NS/EW vs TB).
- **DIRECTION (Pin 11)**: Sets the direction of the sound pulse.
- **SIGNAL (Pin 10)**: Pulse Width Modulation (PWM) signal for driving transducers.
- **MUTE (Pin 9)**: Mutes the amplifier during transmission and unmutes during reception.
- **Envelope Detector (Pin 7)**: Captures the envelope of the signal.
- **Zero-Crossing Detector (Pin 8)**: Captures the zero-crossing signal.
- **Temperature Sensor (Pin A0)**: Reads ambient temperature for compensating the speed of sound.
- **LCD Connections (Pins A1-A3, D3-D6)**: Used to control the 16x2 LCD.

### Additional Required Hardware:
- Ultrasonic transducers.
- Analog Board (ref KiCad folder).
- 3D Digital Board (ref KiCad folder).
- Arduino-compatible microcontroller.
- LCD 16x2 display.

## Output Data

The system outputs the following data over the serial interface:
- **NS Wind Speed**: Wind speed in the North-South direction (in m/s).
- **EW Wind Speed**: Wind speed in the East-West direction (in m/s).
- **TB Wind Speed**: Wind speed in the Top-Bottom direction (in m/s).
- **Magnitude**: The overall wind speed magnitude calculated using the three axes.
- **Phase**: Wind direction based on NS and EW components.
- **Elevation**: Wind elevation based on the TB axis.

The LCD displays the same data in real-time, providing an easy interface for monitoring wind conditions.

## License

This project is open-source, and all contributions are welcome. You are free to modify and distribute the code under the terms of the MIT license.

## Author

- **Dylan Kuming**
  - Date: October, 2024

