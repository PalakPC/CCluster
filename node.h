/*
 * Initial code
 */

# include <string>
# include <vector>
# include <unordered_map>

class Node
{
   public: 
      std::string name;
      unsigned int label;
      bool is_PI;
      bool is_PO;
      std::vector<std::string> input;
      std::vector<std::string> output;
      std::vector<std::string> cluster;

      void print_node();
      
      Node()
      {
         label = 0;
         is_PI = false;
         is_PO = false;
         input.clear();
         output.clear();
         cluster.clear();
      }
};

extern std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>> matrix;

extern std::unordered_map<std::string, Node> nodes;
extern std::vector<std::string> PIs;
extern std::vector<std::string> POs;

extern unsigned int total_nodes;

void parsing();
