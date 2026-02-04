% Read NURBS surface data from file
data = load('NURBS_Surface1.txt');

% Extract u, v, and z coordinates from data
u = data(:, 1);
v = data(:, 2);
z = data(:, 3);

% Determine the resolution (assuming it's square)
resolution = sqrt(length(u)) - 1;

% Reshape u, v, and z into matrices
u = reshape(u, resolution+1, resolution+1);
v = reshape(v, resolution+1, resolution+1);
z = reshape(z, resolution+1, resolution+1);

% Plot NURBS surface
figure;
surf(u, v, z);
xlabel('u');
ylabel('v');
zlabel('z');
title('NURBS Surface');
