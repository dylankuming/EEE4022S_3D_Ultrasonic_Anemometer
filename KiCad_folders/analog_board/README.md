# Analog Board for 3D Ultrasonic Anemometer

This folder contains the KiCad design files for the **Analog Board** used in the 3D Ultrasonic Anemometer. The Analog Board plays a crucial role in processing the ultrasonic signals received from the transducers. It is responsible for signal amplification, envelope detection, and zero-crossing detection, which are required to measure the time-of-flight (ToF) of the ultrasonic pulses.

## Features
- **Signal Amplification**: Boosts the received ultrasonic signals to detectable levels.
- **Envelope Detection**: Extracts the amplitude variations of the signals for timing analysis.
- **Zero-Crossing Detection**: Detects the zero-crossing points of the ultrasonic waves for more precise ToF measurement.
- **Temperature Compensation**: Includes a temperature sensor for compensating the speed of sound based on environmental temperature.

## Components
- Tuned amplifiers for signal conditioning.
- Envelope detectors to capture signal peaks.
- Zero-crossing detectors to mark the precise timing of signal transitions.
- Temperature sensor for environmental adjustments.

## Files in this Folder
- `Analog_Board_Schematic.sch`: The KiCad schematic of the analog board.
- `Analog_Board_PCB.kicad_pcb`: The PCB layout for the analog board.
- `Analog_Board_BOM.csv`: Bill of materials listing all components used on this board.

## Usage
1. **Open the Schematic**: Load the schematic file into KiCad to view the circuit.
2. **View or Edit the PCB**: Open the PCB layout file to review the placement and routing of components.
3. **Generate Fabrication Files**: Export the necessary Gerber files from KiCad for PCB fabrication.

## License
This project is open-source under the MIT License.

