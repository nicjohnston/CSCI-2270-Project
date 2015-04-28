# CSCI-2270-Project
This repository is my final project for CSCI-2270.

This library is designed to calculate the most efficient delivery route.
Initially this will be implemented by creating a csv file with the delivery points (nodes), the distances between them, and possibly more information such as the number of right and left turns needed to traverse a path.  The data will be loaded into a graph, and then the shortest path will be calculated.  To be clear, this is not a map of streets correlated with delivery points, it is a set of delivery points with a path from each delivery point to multiple points.
The following options will be available:

1. Calculate the best delivery method.  This option requires a starting point, either "Default" or a delivery location of the users choosing.
2. Deliver a package.  This option simply delivers a package. No arguments required.
3. Pickup a package.  This option requires a destination for the package.
4. Recalculate the delivery method.  This starts at the current delivery node unless otherwise specified.
5. Print current delivery progress.  This is self explanatory.
6. Print the optimal delivery route.  This prints the current route, probably by delivery node ID. Optimal to be defined later.
7. Erase all remaining deliveries.
8. Load a new set of deliveries. This needs a file name from which to load the deliveries.   This requires another parameter for either overwriting the current deliveries or appending new ones from the file.
9. Add a single delivery.  This does not need data from a file, instead it requests it from the user.
8. Quit.

This could be expanded to calculate the distances (and possibly the turns) by cross referencing the delivery locations with nodes in a graph that contains a map of the streets. This would be a very computationally expensive process if an exhaustive search algorithm was used.  One possible method is to calculate the shortest path between each delivery node on the map (possibly along with left and right turn numbers).  And then calculate the best delivery route from those, in a similar manner to the above system.  For clarity's sake, this uses two distinct data structures, a graph for the delivery nodes, another for the street map (most likely a vector.  This is more complex, as the delivery nodes must me correlated to the map nodes.  However this is also far more realistic.

#Installation:
1. Clone the repository.
2. Open the .cbp file in Code Blocks.
3. Build and run the project.

There are two different methods availiable for loading delivery locations into the program.  The first is to call option 7 from the main menu of the program.  The second is to pass it a command line argument that is the name of the file from which to grab the data.
A file is provided for testing called deliveries.txt.
