/*
 * Header
 */

# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include <unordered_map>
# include <unordered_set>

class Node
{
   public: 
      unsigned int label;
      std::unordered_set<std::string> orig_input;
      std::unordered_map<std::string, unsigned int> input;
      std::unordered_map<std::string, unsigned int> output;
      std::unordered_set<std::string> cluster;

      Node();
      void print_node();
};

extern std::unordered_set<std::string> p_input;
extern std::unordered_set<std::string> p_output;
extern std::unordered_map<std::string, Node> nodes;

extern unsigned int size_constraint;
extern unsigned int inter_cluster_delay;
extern unsigned int node_delay;

extern std::vector<std::string> topological_order;
extern std::unordered_map<std::string, std::unordered_set<std::string>> final_clusters;

void parsing();
void topological_sort();
void longest_path(std::string);
void initialize();
void create_labels();
void label_node(std::string);
void clustering();
void calculate_max_parameters();
