% Read data from text file
data = load('bezier_surface.txt');

% Extract x, y, and z coordinates
x = data(:,1);
y = data(:,2);
z = data(:,3);

% Define the dimensions of the control points grid
%numInterpolatedPointsU = input('Enter the number of points to interpolate along U direction: ');
%numInterpolatedPointsV = input('Enter the number of points to interpolate along V direction: ');
numInterpolatedPointsU = 10;
numInterpolatedPointsV = 10;
numRows = numInterpolatedPointsU + 1;
numCols = numInterpolatedPointsV + 1;

% Reshape the data to match the grid dimensions
x = reshape(x, [numRows, numCols]);
y = reshape(y, [numRows, numCols]);
z = reshape(z, [numRows, numCols]);

% Plot the Bezier surface
plot3(x,y,z);
title('Bezier Surface');
xlabel('X');
ylabel('Y');
zlabel('Z');
