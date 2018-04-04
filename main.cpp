/*
 * Main
 */

# include <iostream>
# include "node.h"

int main()
{
   parsing();

   std::cout << "Primary Inputs\n";
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
   return 0;
}

