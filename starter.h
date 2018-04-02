/*
 * Initial code
 */

# include <string>
#include <unordered_map>
#include <unordered_set>


struct Node
{
   std::string name;
   unsigned int label;
   bool is_PI;
   bool is_PO;
   unordered_set<std::string> input;
   unordered_set<std::string> output;
   unordered_set<std::string> cluster;
};

unordered_map<string, unordered_map<string, value>> matrix;

unordered_map<string, Node> nodes;
vector<string> PIs;
vetcor<string> POs;

