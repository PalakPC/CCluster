/*
 * Main
 */

# include <unistd.h>
# include <ctime>
# include <chrono>

# include "node.h"

std::string file_name;
unsigned int size_constraint = 8;
unsigned int inter_cluster_delay = 3;
unsigned int node_delay = 1;

void showUsage() 
{
   printf("Usage: ./ram_wong_clustering [options] <blif file>\n");
   printf("Options: -s <size_constraint, default 8>\n");
   printf("         -d <inter_cluster_delay, default 3>\n");
   printf("         -n <node_delay, default 1>\n");
}

int main(int argc, char *argv[])
{
   int c;
   while ((c = getopt(argc, argv, "s:d:n:")) != -1) 
   {
      switch (c) 
      {
         case 's':
            size_constraint = atoi(optarg);
            break;
         case 'd':
            inter_cluster_delay = atoi(optarg);
            break;
         case 'n':
            node_delay = atoi(optarg);
            break;
         case '?':
         case 'h':
         default:
            showUsage();
            exit(1);
      }
   }

   if (optind < argc) 
   {
      file_name = argv[optind];
   } 
   else 
   {
      showUsage();
      exit(1);
   }

/*   if ((argc < 2) || (argc > 5))
   {
      std::cout << "File name not specified.\nUse proper execution format:\n" \
         << "./ram_wong_clustering <file_name required> " \
         << "<size_constraint optional, default 8> " \
         << "<inter_cluster_delay optional, default 3> " \
         << "<node_delay optional, default 1>\n";
      exit(1);
   }

   file_name = argv[1];

   if (argc >= 3)
   {
      size_constraint = std::stoi(argv[2]);
   }

   if (argc >= 4)
   {
      inter_cluster_delay = std::stoi(argv[3]);
   }

   if (argc == 5)
   {
      node_delay = std::stoi(argv[4]);
   } 
*/
   std::cout << "Timings\n\n";

   std::chrono::high_resolution_clock::time_point start_time;
   std::chrono::high_resolution_clock::time_point end_time;
   std::chrono::duration<double> span;
   
   start_time = std::chrono::high_resolution_clock::now();
   
   parsing(file_name);
   
   end_time = std::chrono::high_resolution_clock::now();
   span = end_time - start_time;
   std::cout << "DAG Formation:\t\t" << span.count() << " s\n";
   
#  ifdef TEST

   std::cout << "\nPrimary Inputs: ";
   for (auto it = p_input.begin(); it != p_input.end(); ++it)
   {
      std::cout << *it << ' ';
   }

   std::cout << "\nPrimary Outputs: ";
   for (auto it = p_output.begin(); it != p_output.end(); ++it)
   {
      std::cout << *it << ' ';
   }

   for (auto it = nodes.begin(); it != nodes.end(); ++it)
   {
      std::cout << "\n" << it->first << "\n";
      it->second.print_node();
   }

#  endif

   start_time = std::chrono::high_resolution_clock::now();

   topological_sort();
   
   end_time = std::chrono::high_resolution_clock::now();
   span = end_time - start_time;
   std::cout << "Topological Sorting:\t" << span.count() << " s\n";
   
#  ifdef TEST

   std::cout << "Topological Order\n";
   for (unsigned int i = 0; i < topological_order.size(); ++i)
   {
		std::cout << topological_order[i] << " ";
   }
   std::cout << "\n";

#  endif
   
   start_time = std::chrono::high_resolution_clock::now();
   
   initialize();
   
   end_time = std::chrono::high_resolution_clock::now();
   span = end_time - start_time;
   std::cout << "Matrix Formation:\t" << span.count() << " s\n";

#  ifdef TEST

	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr)
	{
		std::cout << "Node " << itr->first << " : ";
		for (auto itr1 = (itr->second).output.begin(); itr1 != (itr->second).output.end(); ++itr1)
		{
			std::cout << itr1->first << "=" << itr1->second << " ";
		}
		std::cout << "\n";
	}
   
#  endif
   
   start_time = std::chrono::high_resolution_clock::now();
   
   create_labels();
   
   end_time = std::chrono::high_resolution_clock::now();
   span = end_time - start_time;
   std::cout << "Labelling:\t\t" << span.count() << " s\n";

#  ifdef TEST

   for (auto it = nodes.begin(); it != nodes.end(); ++it)
   {
      std::cout << it->first << "\n";
      it->second.print_node();
   }

#  endif

   
   start_time = std::chrono::high_resolution_clock::now();
   
   clustering();
   
   end_time = std::chrono::high_resolution_clock::now();
   span = end_time - start_time;
   std::cout << "Clustering:\t\t" << span.count() << " s\n";

#  ifdef TEST

	for (auto itr = final_clusters.begin(); itr != final_clusters.end(); ++itr)
	{
      std::cout << itr->first << ": ";
		for (auto itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
		{
			std::cout << *itr1 << " ";
		}
		std::cout << "\n";
	}

#  endif
   
   std::cout << "\nNumber of nodes:\t"<< nodes.size() << "\n"; 
   std::cout << "Number of clusters:\t" << final_clusters.size() << "\n";
   
   calculate_max_parameters();
   
   return 0;
}
