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
extern unsigned int size_constraint;
extern unsigned int inter_cluster_delay;
extern unsigned int node_delay;

extern std::vector<std::string> topological_order;
extern std::vector<std::vector<std::string>> final_clusters;

void parsing();
std::vector<std::string>  topologicalSort();
void longest_path(std::string);
void initialize();
void CreateLabels();
void LabelNode(std::string);
std::vector<std::string> Calculate_Cluster_Inputs(std::vector<std::string>);
std::vector<std::vector<std::string>> Clustering();
void Calculate_Max_Parameters();