% Read the coordinates from the text file
data = importdata('swept_surface_coordinates.txt');
x = data(:, 1);
y = data(:, 2);
z = data(:, 3);

% Reshape the data to form coordinate matrices
numPointsCurve = numel(x) / 5;
x = reshape(x, 5, numPointsCurve)';
y = reshape(y, 5, numPointsCurve)';
z = reshape(z, 5, numPointsCurve)';

% Plot the surface
figure;
surf(x, y, z, 'FaceColor', 'cyan', 'EdgeColor', 'none');
xlabel('X');
ylabel('Y');
zlabel('Z');
title('Swept Surface');
axis equal;
grid on;
