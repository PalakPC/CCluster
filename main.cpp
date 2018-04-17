/*
 * Main
 */

# include <iostream>
# include "node.h"

unsigned int size_constraint;
unsigned int inter_cluster_delay;
unsigned int node_delay;
std::vector<std::vector<std::string>> final_clusters;

std::vector<std::string> topological_order;
int main()
{
   parsing();
   std::cout << "\nPlease enter the size constraint ";
   std::cin >> size_constraint;
   std::cout << "\nEnter the inter cluster delay ";
   std::cin >> inter_cluster_delay;
   std::cout << "\nEnter the node delay ";
   std::cin >> node_delay;

   std::cout << "\nPrimary Inputs\n";
   for (auto it = PIs.begin(); it != PIs.end(); ++it)
   {
      std::cout << *it << '\n';
   }

   std::cout << "Primary Outputs\n";
   for (auto it = POs.begin(); it != POs.end(); ++it)
   {
      std::cout << *it << '\n';
   }

   for (auto it = nodes.begin(); it != nodes.end(); ++it)
      it->second.print_node();

   std::cout << "Total number of nodes: " << total_nodes << "\n";

   topological_order = topologicalSort();
   initialize();
   /*CreateLabels();
   final_clusters = Clustering();
   std::cout<<"\nNumber of individual nodes is "<<nodes.size();
   std::cout << "\nNumber of individual clusters is " << final_clusters.size();
   Calculate_Max_Parameters();*/
   
   
   return 0;
}

