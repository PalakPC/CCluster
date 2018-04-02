# include <iostream>
# include "starter.h"

std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>> matrix;

std::unordered_map<std::string, Node> nodes;
std::vector<std::string> actual_inputs;
std::vector<std::string> PIs;
std::vector<std::string> POs;

unsigned int total_nodes;

void Node::print_node()
{
   std::cout << "name: " << name << '\n';
   std::cout << "label: " << label << '\n';
   std::cout << "is_PI: " << is_PI << '\n';
   std::cout << "is_PO: " << is_PO << '\n';

   std::cout << "Inputs\n";
   for (auto i = input.begin(); i != input.end(); ++i)
      std::cout << *i << '\n';

   std::cout << "Outputs\n";
   for (auto i = output.begin(); i != output.end(); ++i)
      std::cout << *i << '\n';
   
   std::cout << "Cluster\n";
   for (auto i = cluster.begin(); i != cluster.end(); ++i)
      std::cout << *i << '\n';

   std::cout << "\n";
}
