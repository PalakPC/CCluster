/*
 * Main
 */

# include <ctime>
# include <chrono>

# include "node.h"

unsigned int size_constraint;
unsigned int inter_cluster_delay;
unsigned int node_delay;

int main()
{
   std::chrono::high_resolution_clock::time_point start_time;
   std::chrono::high_resolution_clock::time_point end_time;
   std::chrono::duration<double> span;

   std::cout << "\nEnter the size constraint ";
   std::cin >> size_constraint;
   std::cout << "\nEnter the inter cluster delay ";
   std::cin >> inter_cluster_delay;
   std::cout << "\nEnter the node delay ";
   std::cin >> node_delay;

   start_time = std::chrono::high_resolution_clock::now();
   parsing();

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

   topological_sort();

#  ifdef TEST

   std::cout << "Topological Order\n";
   for (unsigned int i = 0; i < topological_order.size(); ++i)
   {
		std::cout << topological_order[i] << " ";
   }
   std::cout << "\n";

#  endif

   initialize();

#  ifdef TEST

	for (auto itr = matrix.begin(); itr != matrix.end(); ++itr)
	{
		std::cout << "Node " << itr->first << " : ";
		for (auto itr1 = (itr->second).begin(); itr1 != (itr->second).end(); ++itr1)
		{
			std::cout << itr1->first << "=" << itr1->second << " ";
		}
		std::cout << "\n";
	}
   
#  endif
   
   end_time = std::chrono::high_resolution_clock::now();
   span = end_time - start_time;
   std::cout << "Matrix Formation: " << span.count() << "\n";
   
   start_time = std::chrono::high_resolution_clock::now();
   create_labels();
   end_time = std::chrono::high_resolution_clock::now();
   span = end_time - start_time;
   std::cout << "Labelling: " << span.count() << "\n";

#  ifdef TEST

   for (auto it = nodes.begin(); it != nodes.end(); ++it)
   {
      it->second.print_node();
   }

#  endif
   
   start_time = std::chrono::high_resolution_clock::now();
   clustering();
   end_time = std::chrono::high_resolution_clock::now();
   span = end_time - start_time;
   std::cout << "Clustering: " << span.count() << "\n";

#  ifdef TEST

	for (auto itr = final_clusters.begin(); itr != final_clusters.end(); ++itr)
	{
      std::cout << itr->first << "\n";
		for (auto itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
		{
			std::cout << *itr1 << " ";
		}
		std::cout << "\n";
	}

#  endif
   
   std::cout << "Number of nodes: "<< nodes.size() << "\n"; 
   std::cout << "Number of nodes: "<< total_nodes << "\n"; 
   std::cout << "Number of clusters: " << final_clusters.size() << "\n";
   
   //calculate_max_parameters();
   
   return 0;
}
