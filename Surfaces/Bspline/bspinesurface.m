% Read data from the text file
data = load('bspline_surface_data.txt');

% Extract x, y, and z coordinates
x = data(:, 1);
y = data(:, 2);
z = data(:, 3);

% Reshape coordinates into matrices
resolutionU = 10; % Update this with the resolution used in the C++ code
resolutionV = 10; % Update this with the resolution used in the C++ code
x = reshape(x, resolutionV + 1, resolutionU + 1);
y = reshape(y, resolutionV + 1, resolutionU + 1);
z = reshape(z, resolutionV + 1, resolutionU + 1);

% Plot the B-spline surface
figure;
surf(x, y, z);
xlabel('X');
ylabel('Y');
zlabel('Z');
title('B-spline Surface');