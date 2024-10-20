# 3D Digital Board for 3D Ultrasonic Anemometer

This folder contains the KiCad design files for the **3D Digital Board** used in the 3D Ultrasonic Anemometer. This board expands on the 2D version by adding control for the Top-Bottom (TB) axis, allowing for full 3D wind measurement. It manages the ultrasonic transducers in the NS, EW, and TB directions and processes signals for calculating wind speed and direction in three dimensions.

## Features
- **3D Wind Measurement**: Adds the third axis (Top-Bottom) to enable full 3D wind speed and direction measurement.
- **Expanded Multiplexing**: Uses additional multiplexers to handle signals from six transducers.
- **Transducer Control**: Selects and drives the appropriate transducers for the NS, EW, and TB axes.

## Key Components
- **74HC138 3-to-8 Line Decoder**: Controls the selection of transducer pairs for the three-dimensional setup.
- **74HC4051 Multiplexer**: Routes the received signals from all six transducers to the analog board for processing.
- **Hex Inverters**: Controls the ultrasonic transducers.

## Files in this Folder
- `3D_Digital_Board_Schematic.sch`: The KiCad schematic of the 3D digital board.
- `3D_Digital_Board_PCB.kicad_pcb`: The PCB layout for the 3D digital board.

## Usage
1. **Open the Schematic**: Use KiCad to open and modify the schematic for the 3D digital board.
2. **Edit PCB Layout**: Review the PCB layout to make any necessary adjustments.
3. **Generate Gerber Files**: Export Gerber files from KiCad for PCB fabrication.

## License
This project is open-source under the MIT License.

## Author

- **Dylan Kuming**
  - Date: October, 2024
