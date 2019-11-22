# lem-in
This project is quite simple: to find the optimal way(ways) for a set graph and set number of objects (ants).
Usage:    ./lem-in [options] < map_file
Options:  -v visual mode
          -r coordinates redefinition;
Structure of map_file or the input data:
number_of_ants
the_rooms
the_links

The results display on the standard output in the following format:
Lx-y Lz-w Lr-o ...
x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y, w, o represents the rooms’ names.

Example map_file/input data:
4
3 2 2
##start
start 4 0
##end
end 4 6
4 0 4
1 4 2
2 4 4
5 8 2
6 8 4
start-1
3-4
2-4
1-5
6-5
end-6
1-2
2-end
3-start
It is nesscesary to have commands "##start" and "##end" to mark the start and end room.
The output for this example:
L1-1 L2-3
L1-5 L2-4 L3-1 L4-3
L1-6 L2-2 L3-5 L4-4
L1-end L2-end L3-6 L4-2
L3-end L4-end
