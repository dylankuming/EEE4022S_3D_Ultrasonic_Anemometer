# EEE4022S 3D Ultrasonic Anemometer

This repository contains the complete development files for the **3D Ultrasonic Anemometer** project developed as part of the EEE4022S course. The goal of the project is to design, build, and test a low-cost, accurate, and reliable 3D ultrasonic anemometer using Commercial-Off-The-Shelf (COTS) components. The system measures wind speed and direction in three dimensions (X, Y, and Z) using ultrasonic transducers and provides real-time data visualization.

## Repository Structure

This repository is organized into three main directories:

1. **Arduino_code**: Contains all the Arduino code required to interface with the ultrasonic transducers, perform wind speed and direction calculations, and handle the data acquisition process.
   - [More details can be found in the `Arduino_code/README.md`](https://github.com/dylankuming/EEE4022S_3D_Ultrasonic_Anemometer/blob/main/Arduino_code/README.md)

2. **KiCad_folders**: Includes the KiCad schematics and PCB design files for the digital and analog circuits used in the project. These files outline the hardware design and connections between components.
   - [More details can be found in the `KiCad_folders/README.md`]

3. **matlab_code**: This directory contains MATLAB scripts used for data visualization and further analysis of the anemometer's outputs. The scripts allow for the real-time display of wind speed and direction data.
   - [More details can be found in the `matlab_code/README.md`]

## Getting Started

### Prerequisites

- Arduino IDE for uploading and running the Arduino code.
- KiCad for viewing and editing the PCB design files.
- MATLAB for running the data visualization scripts.

### Installation and Usage

1. **Arduino Code**: Navigate to the `Arduino_code` folder, open the relevant `.ino` file in the Arduino IDE, and upload it to your Arduino board.
2. **KiCad Files**: Open the KiCad project files in the `KiCad_folders` directory to explore or modify the circuit designs.
3. **MATLAB Scripts**: Run the MATLAB scripts from the `matlab_code` folder to visualize the wind data captured by the anemometer.


## License



## Acknowledgements

This project was supervised by **Dr. Stephen Paine** and completed as part of the EEE4022S course at the **University of Cape Town**.
