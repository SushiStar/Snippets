% simple file for visualizing the voxelized mesh map
function y = VoxelizedMap(filename)

A = load(filename);

x = A(:,1); y = A(:,2); z = A(:,3);

plot3(x,y,z, '.');
grid on;
