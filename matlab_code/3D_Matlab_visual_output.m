% MATLAB Script to Visualize Resultant Wind Data with Cardinal Directions

% Set up the serial port (replace 'COM3' with the appropriate port for your Arduino)
s = serialport("COM3", 9600);

% Number of data points to collect
numPoints = 1000;

% Initialize arrays for wind data
windNS = zeros(1, numPoints);
windEW = zeros(1, numPoints);
windTB = zeros(1, numPoints);

% Set up the figure for visualization
figure('Color', 'w', 'Name', 'Enhanced Wind Visualization');

% Enhanced 3D Quiver Plot with Trailing Vectors
subplot(2,2,1);
quiver3Plot = quiver3(0, 0, 0, windEW(1), windNS(1), windTB(1), 'MaxHeadSize', 0.5, 'AutoScale', 'off', 'Color', 'b');
hold on;
[x, y, z] = sphere;
surf(x*0.5, y*0.5, z*0.5, 'EdgeColor', 'none', 'FaceColor', 'r');
axis([-15 15 -15 15 -15 15]);  % Changed axis limits to 15
xlabel('EW (m/s)');
ylabel('NS (m/s)');
zlabel('TB (m/s)');
title({'3D Wind Speed and Direction', ''});
grid on;
trail = plot3(nan, nan, nan, 'r--');

% Line Graph for Smoothed Wind Speed Over Time for All Three Directions
subplot(2,2,2);
plotNS = plot(windNS, 'b--', 'LineWidth', 1.5);
hold on;
plotEW = plot(windEW, 'r-.', 'LineWidth', 1.5);
plotTB = plot(windTB, 'g:', 'LineWidth', 1.5);
legend('NS', 'EW', 'TB', 'Location', 'eastoutside');
xlabel('Time');
ylabel('Wind Speed (m/s)');
title({'Smoothed Wind Speed Over Time', ''});
grid on;

% Resultant Wind Speed and Direction on Polar Plot
subplot(2,2,3);
directionArrow = polarplot(deg2rad(0), 0, 'r', 'Marker', 'o', 'LineWidth', 2);
ax = gca;
ax.ThetaZeroLocation = 'top';
ax.ThetaDir = 'clockwise';
ax.RLim = [0 15];  % Changed radial limit to 15
title('Resultant Wind Speed and Direction');

% Digital Readout
subplot(2,2,4);
axis off;

for i = 1:numPoints
    % Read a line of data from the Arduino
    data = readline(s);
    
    % Parse the data
    tokens = sscanf(data, 'NS:%f,EW:%f,TB:%f');
    windNS(i) = tokens(1);
    windEW(i) = tokens(2);
    windTB(i) = tokens(3);
    
    % Calculate resultant wind speed and direction
    resultantWindSpeed = sqrt(windNS(i)^2 + windEW(i)^2 + windTB(i)^2);
    windDirection = atan2d(windNS(i), windEW(i));
    if windDirection < 0
        windDirection = windDirection + 360;
    end
    
    % Convert direction to cardinal directions
    directions = ["North", "North-East", "East", "South-East", "South", "South-West", "West", "North-West"];
    index = mod(ceil((windDirection + 22.5) / 45) - 1, 8) + 1;
    cardinalDir = directions(index);
    
    % Update 3D quiver plot
    set(quiver3Plot, 'UData', windEW(i), 'VData', windNS(i), 'WData', windTB(i));
    set(trail, 'XData', windEW(1:i), 'YData', windNS(1:i), 'ZData', windTB(1:i));
    
    % Update line graph
    set(plotNS, 'YData', windNS(1:i));
    set(plotEW, 'YData', windEW(1:i));
    set(plotTB, 'YData', windTB(1:i));
    
    % Update polar plot
    set(directionArrow, 'ThetaData', deg2rad(windDirection), 'RData', resultantWindSpeed);
    ax.RLim = [0 max(resultantWindSpeed, 15)]; % Adjust radial limits based on max speed
    
    % Update digital readout
    elevationAngle = atan2d(windTB(i), sqrt(windNS(i)^2 + windEW(i)^2));
    subplot(2,2,4);
    cla;
    text(0.5, 0.8, sprintf('Speed: %.2f m/s', resultantWindSpeed), 'FontSize', 12, 'HorizontalAlignment', 'center');
    text(0.5, 0.6, sprintf('Direction: %.2f° (%s)', windDirection, cardinalDir), 'FontSize', 12, 'HorizontalAlignment', 'center');
    text(0.5, 0.4, sprintf('Elevation: %.2f°', elevationAngle), 'FontSize', 12, 'HorizontalAlignment', 'center');
    axis off;
    
    % Refresh the plot
    drawnow;
end
