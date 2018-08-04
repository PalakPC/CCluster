# Rajaraman and Wong Clustering

Rajaraman and Wong algorithm for optimum polynomial time clustering.

## Files:

* CMakeLists.txt: Self explanatory. We used cmake to generate our Makefile
* main.cpp:       Self explanatory. Handles function calls and print statements
* parse.cpp:      Contains parsing function for the blif files and functions to generate files for GUI
* node.cpp:       Contains all relevant functions used in the algorithm
* node.h:         Header file with class declaration and function definitions
* sample.blif:    Sample blif file we made, creates the DAG shown in Prof. Lim's book
* xyz.blif:       blif files provided
* xyz.json:       json files used for GUI
* xyz.csv:        csv files used for GUI

## How to run

Follow the following steps for execution:

* Run "cmake ." (without the quotes, obviously, duh) to generate makefile.
* Run "make" to generate executable. It is called "ram_wong_clustering" (long name, I know, sorry, bugged me too :D).
* Use the following command to execute
   * "./ram_wong_clustering [options] <blif file>"
   * Options are: "-s <size_constraint, default 8> -d <inter_cluster_delay, default 3> -n <node_delay, default 1> -j <generate json? yes(1) or no(0)> -p <perform post processing? yes(1) or no(0)>"


The code will execute (don't rush, it may take a few minutes for the biggest blif in the folder) and display the timings (in seconds) for different steps of algorithm.  
   
It will also display the maximum delay in the circuit, number of nodes and number of clusters.   
   
If you chose post-processing, it will display reduced cluster count and number of duplicate nodes removed.
   
If GUI file generation is enabled, various json and csv files will be generated in the same folder as the input file.

### Sanity Check

If you wish to check the code, just uncomment line 7 in CMakeLists.txt and follow the steps to run again.  
  
Now it will show the initial condition of nodes, topological order, codition of nodes after matrix formation, condition of nodes after labelling phase and list of final clusters with the root node along with the usual output. If post-processing is enabled, you can also see the final cluster list.   
   
I do not recommend doing this for any blif file other than sample.blif (unless you like your screen getting crowded with continuous printing :D).  
   
Execution will get slower because of the printing, so be patient and enjoy the output :D.  

## GUI Demonstration

Minimum Requirements :-
* Python: version 3.6 or higher
* Import the following libraries:
   * Matplotlib: version 2.2.2 or higher
   * Networkx: version 2.1 or higher
   * Json and csv packages if you still get an error message, although these packages are generally installed with the standard python packages   

Note: Sample.blif is the blif file created for the sample circuit analysed in Page 3 of "Practical Problems in VLSI Physical Design Automation" by Prof. Sung-Kyu Lim

To generate the json and csv files for sample.blif with size constraint 4 and default delay values, run the following command:
	./ram_wong_clustering -s 4 -j 1 sample.blif

### Linux Machine Instructions

* Change Directory to the required path
* Run the following commands to install the required packages:
   * pip install networkx
   * pip install matplotlib
* Execute the following command to run the script:
   * python ./graphics.py
	
### Windows Machine Instructions

* Use JetBrains PyCharm Community Edition 2017.3.4 as the IDE
* Setup the libraries and Python Interpreter in the following manner:
   * Go to File-> Settings-> Project: project_name
   * Under this, select Project Interpreter	
   * Make sure you have pip (> version 9.0.1) and setuptools (> 28.8.0) set up.
   * Click on the + button in the right. 
   * From this install the following packages:
      * Networkx
      * Matplotlib
* Press run

### GUI Ouputs 
* Dag.png : Shows the input to the clustering problem, i.e the DAG constructed from sample.blif
* Matrix.html: Shows the Initialization matrix for the DAG in a tabular format
* Label.png: Shows the label value associated with each node after Labeling phase
* Cluster.png: Shows a pictorial representation of the clustering solution with each cluster represented with a different color.
* Result.html: Tabular representation of the results of the algorithm
	
Note: Make sure the following files are in the same directory as the python script:
* sample.blif.dag.json
* sample.blif.label.json
* sample.blif.cluster.json
* sample.blif.matrix.csv
* sample.blif.result.csv
