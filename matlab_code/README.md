# MATLAB Wind Visualisation for 3D Ultrasonic Anemometer

This MATLAB script connects to an Arduino via serial communication and streams wind speed data from the **3D Ultrasonic Anemometer** in three axes: North-South (NS), East-West (EW), and Top-Bottom (TB). The script processes this data and visualizes it in real time using multiple plot types, including 3D quiver plots, line graphs, and polar plots.

## Features

- **3D Quiver Plot with Trailing Vectors**: Shows the wind direction and magnitude in real time in a 3D space, along with trailing lines for visual tracking.
- **Smoothed Line Graph**: Displays the wind speed over time for all three axes (NS, EW, TB).
- **Polar Plot**: Illustrates the resultant wind direction and speed on a polar graph.
- **Digital Readout**: Provides real-time information on the resultant wind speed, direction (in both degrees and cardinal direction), and elevation angle.
  
## How to Use

### 1. Connect the Arduino

- Make sure the Arduino, loaded with [`3D_Ultrasonic_Anemometer.ino`](https://github.com/dylankuming/EEE4022S_3D_Ultrasonic_Anemometer/blob/main/Arduino_code/3D_Ultrasonic_Anemometer.ino), is connected to your computer and is streaming wind data via a serial connection.
- Replace `"COM3"` in the script with the correct port for your Arduino (you can find the correct port in the Arduino IDE).

```matlab
s = serialport("COM3", 9600); % Change "COM3" to your Arduino's COM port
```

### 2. Run the Script

- Open the [3D_Matlab_visual_output.m](https://github.com/dylankuming/EEE4022S_3D_Ultrasonic_Anemometer/blob/main/matlab_code/3D_Matlab_visual_output.m) script in MATLAB.
- Run the script by pressing the **Run** button or by typing `run` in the MATLAB command window.

### 3. Visualisation

- The script collects 1000 data points from the Arduino and updates the following visualisations in real time:
  - **3D Quiver Plot**: A 3D vector plot that shows wind direction and magnitude in space, with a trailing line for visual history.
  - **Line Graph**: A real-time plot of wind speed over time for each axis (NS, EW, TB).
  - **Polar Plot**: Displays the resultant wind direction and speed on a polar coordinate plot.
  - **Digital Readout**: Displays current wind speed, direction (in degrees and cardinal direction), and elevation angle.

### 4. Data Collection and Visualisation

- The script collects data for 1000 iterations, where each data point contains the wind speed along the NS, EW, and TB axes. 
- It calculates:
  - **Resultant Wind Speed**: The overall wind speed from the three components.
  - **Wind Direction**: The direction of the wind in degrees.
  - **Cardinal Direction**: The wind direction in cardinal terms (e.g., North, East, South, etc.).
  - **Elevation Angle**: The vertical component of the wind based on the TB axis.
  
### Sample Data Format (from Arduino):
```plaintext
NS:<value>,EW:<value>,TB:<value>
```

### Example Output
- Wind speed: `8.65 m/s`
- Wind direction: `45.0° (North-East)`
- Elevation angle: `12.5°`

## Visualisation Details

- **3D Quiver Plot**: Visualizes wind vectors in a 3D space, showing the real-time wind direction and magnitude. The plot is updated dynamically as new data is received from the Arduino.
- **Smoothed Line Graph**: Shows the wind speed variation over time for each axis (NS, EW, TB). The plot is continuously updated as data is received.
- **Polar Plot**: Displays the resultant wind direction and speed on a polar graph, helping users visualize where the wind is coming from.
- **Digital Readout**: Provides real-time numerical values for resultant wind speed, direction, and elevation.

## License

This MATLAB script is open-source and available for modification and distribution. Feel free to use and improve upon the code.

## Author

- **Dylan Kuming**
  - Date: October, 2024
