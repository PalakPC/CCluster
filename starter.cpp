/*
 * Initial code
 */

# include <string>

struct Node
{
   std::string name;
   unsigned int label;
   unordered_set input;
   unordered_set output;
   unordered_set <string> cluster;
};

unordered_map<string, unordered_map<string, value>> matrix;


