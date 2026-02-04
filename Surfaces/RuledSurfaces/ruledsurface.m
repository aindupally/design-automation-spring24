% Read x, y, and z coordinates from text files
x = importdata('x_coordinates.txt');
y = importdata('y_coordinates.txt');
z = importdata('z_coordinates.txt');

% Reshape the data to form coordinate matrices
numPoints = numel(x) / 2;
x = reshape(x, 2, numPoints)';
y = reshape(y, 2, numPoints)';
z = reshape(z, 2, numPoints)';

% Plot the surface
figure;
surf(x, y, z, 'FaceColor', 'cyan', 'EdgeColor', 'none');
xlabel('X');
ylabel('Y');
zlabel('Z');
title('Ruled Surface');
axis equal;
grid on;
