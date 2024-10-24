# EEE4022S 3D Ultrasonic Anemometer

This repository contains the complete development files for the **3D Ultrasonic Anemometer** project developed as part of the EEE4022S course. The goal of the project is to design, build, and test a low-cost, accurate, and reliable 3D ultrasonic anemometer using Commercial-Off-The-Shelf (COTS) components. The system measures wind data in three dimensions (X, Y, and Z) using ultrasonic transducers and provides real-time data visualisation.

## Repository Structure

This repository is organized into three main directories:

1. **Arduino_code**: Contains all the Arduino code required to interface with the ultrasonic transducers, perform wind speed and direction calculations, and handle the data acquisition process.
   - [More details can be found in the `Arduino_code/README.md`](https://github.com/dylankuming/EEE4022S_3D_Ultrasonic_Anemometer/blob/main/Arduino_code/README.md)

2. **KiCad_folders**: Includes the KiCad schematics and PCB design files for the digital and analog circuits used in the project. These files outline the hardware design and connections between components. The following KiCad folders are included:

   - **Analog Board**: Contains the PCB design for the analog circuit.
     - [More details can be found in the `Analog Board README.md`](https://github.com/dylankuming/EEE4022S_3D_Ultrasonic_Anemometer/blob/main/KiCad_folders/analog_board/README.md)

   - **2D Digital Board**: Contains the PCB design for the 2D digital circuit.
     - [More details can be found in the `2D Digital Board README.md`](https://github.com/dylankuming/EEE4022S_3D_Ultrasonic_Anemometer/tree/main/KiCad_folders/2d_digital_board#readme)

   - **3D Digital Board**: Contains the PCB design for the 3D digital circuit.
     - [More details can be found in the `3D Digital Board README.md`](https://github.com/dylankuming/EEE4022S_3D_Ultrasonic_Anemometer/blob/main/KiCad_folders/3d_digital_board/README.md)


3. **matlab_code**: This directory contains MATLAB scripts used for data visualization and further analysis of the anemometer's outputs. The scripts allow for the real-time display of wind speed and direction data.
   - [More details can be found in the `matlab_code/README.md`](https://github.com/dylankuming/EEE4022S_3D_Ultrasonic_Anemometer/blob/main/matlab_code/README.md)

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

This project is open-source, and all contributions are welcome. You are free to modify and distribute the code under the terms of the MIT license.


## Author

- **Dylan Kuming**
  - Date: October, 2024



## Acknowledgements

This project was supervised by **Dr. Stephen Paine** and completed as part of the EEE4022S course at the **University of Cape Town**.
