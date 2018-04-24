# Rajaraman and Wong Clustering

Rajaraman and Wong algorithm for optimum polynomial time clustering.

## Files:

* CMakeLists.txt: Self explanatory. We used cmake to generate our Makefile
* main.cpp: Self explanatory. Handles function calls and print statements
* parse.cpp: Contains parsing function for the blif files
* node.cpp: Contains all relevant functions used in the algorithm
* node.h: Header file with class declaration and function definitions
* sample.blif: Sample blif file we made, creates the DAG shown in Prof. Lim's book
* xyz.blif: blif files provided

## How to run

Follow the following steps for execution:

* Run "cmake ." (without the quotes, obviously, duh) to generate makefile
* Run "make" to generate executable. It is called "ram_wong_clustering" (long name, I know, sorry, bugged me too :D)
* Use the following command to execute
  * "./ram_wong_clustering <file_name required> <size_constraint optional, default 8> <inter_cluster_delay optional, default 3> <node_delay optional, default 1>"

The code will execute (don't rush, it may take about a minute and half for the biggest blif in the folder) and display the timings (in seconds) for different steps of algorithm.  
   
It will also display the maximum delay in the circuit, number of nodes and number of clusters.

### Sanity Check

If you wish to check the code, just uncomment line 7 in CMakeLists.txt and follow the steps to run again.  
  
Now it will show the initial condition of nodes, topological order, codition of nodes after matrix formation, condition of nodes after labelling phase and list of final clusters with the root node along with the usual output.  
   
I do not recommend doing this for any blif file other than sample.blif (unless you like your screen getting crowded with continuous printing :D)  
   
Execution will get slower because of the printing, so be patient and enjoy the output :D  
