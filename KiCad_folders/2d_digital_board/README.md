# 2D Digital Board for 2D Ultrasonic Anemometer

This folder contains the KiCad design files for the **2D Digital Board** used in the 2D version of the Ultrasonic Anemometer. This board is designed to control and manage the transducers along two axes: North-South (NS) and East-West (EW). It sends and receives ultrasonic pulses and calculates wind speed and direction in two dimensions.

## Features
- **Transducer Control**: Manages the transducers for both the NS and EW axes.
- **Multiplexing**: Uses multiplexers to route the signals to and from the appropriate transducers.

## Key Components
- **74HC139 Decoder**: Controls the transducer selection for NS and EW.
- **74HC368 Hex Inverters**: Drives the ultrasonic transducers.
- **74HC4052 Multiplexers**: Routes the signals to the analog board for processing.

## Files in this Folder
- [2D_Digital_Board_Schematic.sch](https://github.com/dylankuming/EEE4022S_3D_Ultrasonic_Anemometer/blob/main/KiCad_folders/2d_digital_board/Digital.kicad_sch): The KiCad schematic of the 2D digital board.
- [2D_Digital_Board_PCB.kicad_pcb](https://github.com/dylankuming/EEE4022S_3D_Ultrasonic_Anemometer/blob/main/KiCad_folders/2d_digital_board/Digital.kicad_pcb): The PCB layout for the 2D digital board.

## Usage
1. **Open the Schematic**: Load the schematic file into KiCad to view or modify the design.
2. **View or Edit the PCB**: Review the PCB layout and adjust the component placement as needed.
3. **Fabrication**: Generate Gerber files from KiCad for PCB manufacturing.

## License
This project is open-source under the MIT License.

## Author

- **Dylan Kuming**
  - Date: October, 2024
