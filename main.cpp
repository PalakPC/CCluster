/*
 * Main
 */

# include <iostream>
# include "starter.h"

int main()
{
   parsing();

   std::cout << "Actual Inputs\n";
   for (auto i = actual_inputs.begin(); i != actual_inputs.end(); ++i)
      std::cout << *i << '\n';
   
   std::cout << "Primary Inputs\n";
   for (auto i = PIs.begin(); i != PIs.end(); ++i)
      std::cout << *i << '\n';

   std::cout << "Primary Outputs\n";
   for (auto i = POs.begin(); i != POs.end(); ++i)
      std::cout << *i << '\n';

   for (auto it = nodes.begin(); it != nodes.end(); ++it)
      it->second.print_node();

   std::cout << "Total number of nodes: " << total_nodes << "\n";
   return 0;
}

