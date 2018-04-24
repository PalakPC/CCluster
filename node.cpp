/*
 * Miscellaneous functions
 */

# include <queue> 
# include <set>
# include "node.h"

#define NINF -1

std::unordered_map<std::string, Node> nodes;
std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>> matrix;
std::unordered_set<std::string> p_input;
std::unordered_set<std::string> p_output;
std::vector<std::string> topological_order;
std::unordered_map<std::string, std::unordered_set<std::string>> final_clusters;
std::vector<std::unordered_set<std::string>> fclusters;

std::unordered_map<std::string,unsigned int>::iterator visited;
std::unordered_map<std::string,unsigned int>::iterator ittemp;
Node::Node()
{
   label = 0;
   input.clear();
   output.clear();
   cluster.clear();
}

void Node::print_node()
{
   std::cout << "label: " << label << "\n";

   std::cout << "Inputs: ";
   for (auto i = input.begin(); i != input.end(); ++i)
   {
      std::cout << i->first << ":" << i->second << ' ';
   }
   
   std::cout << "\nOriginal Inputs: ";
   for (auto i = orig_input.begin(); i != orig_input.end(); ++i)
   {
      std::cout << *i << ' ';
   }
   
   std::cout << "\nOriginal Outputs: ";
   for (auto i = orig_output.begin(); i != orig_output.end(); ++i)
   {
      std::cout << *i << ' ';
   }
   
   std::cout << "\nOutputs: ";
   for (auto i = output.begin(); i != output.end(); ++i)
   {
      std::cout << i->first << ":" << i->second << ' ';
   }

   std::cout << "\nCluster: ";
   for (auto i = cluster.begin(); i != cluster.end(); ++i)
   {
      std::cout << *i << ' ';
   }
   std::cout << "\n";
}

void topological_sort()
{
   int cnt;
   std::string u;
	std::queue<std::string> q;
   std::unordered_map<std::string, int> in_degree;
	
   for (auto itr = nodes.begin(); itr != nodes.end(); ++itr)
	{
		in_degree.insert(std::make_pair(itr->first, itr->second.input.size()));
      
      if (!itr->second.input.size())
      {
         q.push(itr->first);
      }
	}

	cnt = 0;
	while (!q.empty())
	{
		u = q.front();
		q.pop();
		topological_order.push_back(u);

		for (auto itr = nodes[u].output.begin(); itr != nodes[u].output.end(); ++itr)
      {
			if ((--in_degree[itr->first]) == 0)
         {
				q.push(itr->first);
         }
      }
		++cnt;
	}

	if (cnt != nodes.size())
	{
      std::cout << "cnt = " << cnt << "\n";
		std::cout << "There exists a cycle in the graph\n";
	}	
}

void longest_path(std::string from_node)
{
   unsigned int check = 0;
   std::unordered_map<std::string, unsigned int> temp_map;
   std::vector<std::string> temp;

   auto got = nodes.find(from_node);
   for (auto it = got->second.output.begin(); it != got->second.output.end(); ++it)
   {
      if (it->second != 1)
      {
         return;
      }
      temp.push_back(it->first);
      temp_map.insert(*it);
   }

   for (unsigned int i = 0; i < temp.size(); ++i)
   {
      unsigned int x = temp_map.find(temp[i])->second + node_delay;
      auto got2 = nodes.find(temp[i]);
      for (auto it = got2->second.output.begin(); it != got2->second.output.end(); ++it)
      {
         if (got->second.output.find(it->first) == got->second.output.end())
         {
            temp.push_back(it->first);
            temp_map.insert(std::make_pair(it->first, x));
            got->second.output.insert(std::make_pair(it->first, x));
            nodes.find(it->first)->second.input.insert(std::make_pair(from_node, x));
         }
         else if (got->second.output.find(it->first)->second < x)
         {
            auto f = temp_map.find(it->first);
            f->second = x;
            got->second.output.find(it->first)->second = x;
            nodes.find(it->first)->second.input.find(from_node)->second = x;
         }
      }
   }
}

void initialize()
{
   for (auto itr = topological_order.begin(); itr != topological_order.end(); ++itr)
   {
      if (p_output.find(*itr) == p_output.end())
      {
         longest_path(*itr);
      }
   }
   
   topological_order.erase(topological_order.begin(), topological_order.begin() + p_input.size());
}

bool compareTwo (std::pair<std::pair<std::string, unsigned int>, unsigned int> a, std::pair<std::pair<std::string, unsigned int>, unsigned int> b)
{
   if (a.second == b.second)
   {
      return a.first.second < b.first.second;
   }

   else
   {
      return a.second > b.second;
   }
}

void label_node(std::string cur_node)
{
	unsigned int l1;
	unsigned int l2;
   std::unordered_set<std::string> cluster;
   std::vector<std::pair<std::pair<std::string, unsigned int>, unsigned int>> S;
	
   l1 = 0;
	l2 = 0;

   for (auto it = nodes[cur_node].input.begin(); it != nodes[cur_node].input.end(); ++it)
   {
      unsigned int label;
      auto got = nodes.find(it->first);
      label = got->second.label + got->second.output[cur_node];
      S.push_back(std::make_pair(*it, label));
   }

   std::stable_sort(S.begin(), S.end(), [](const std::pair<std::pair<std::string, unsigned int>, unsigned int> &a, const std::pair<std::pair<std::string, unsigned int>, unsigned int> &b) { if (a.second == b.second) return a.first.second < b.first.second; else return a.second > b.second; });

   auto it = S.begin();
   for (unsigned int count = 0; (count < (size_constraint - 1)) && it != S.end(); ++count, ++it)
   {
      cluster.insert(it->first.first);
      if (p_input.find(it->first.first) != p_input.end())
      {
         if (l1 < it->second)
         {
            l1 = it->second;
         }
      }
   }
   cluster.insert(cur_node);

   if (it != S.end())
   {
      l2 = it->second + inter_cluster_delay;
   }

   if (l1 > l2)
   {
      nodes[cur_node].label = l1;
   }
   else
   {
      nodes[cur_node].label = l2;
   }
   nodes[cur_node].cluster = cluster;
}

void create_labels()
{
	for (auto itr = topological_order.begin(); itr != topological_order.end(); itr++)
	{
		label_node(*itr);
	}
}

void clustering()
{
	std::deque<std::string> L;
	std::string cur_node;
	std::set<std::string> I;
	std::unordered_set<std::string> cl;

	for (auto itr = p_output.begin(); itr != p_output.end(); ++itr)
	{
		L.push_back(*itr);
	}

	while (!L.empty())
	{
		cur_node = L.front();
		L.pop_front();
		cl = nodes[cur_node].cluster;
      auto got = final_clusters.find(cur_node);
		if (got == final_clusters.end())
      {
			final_clusters.insert(std::make_pair(cur_node, cl));
      }

      I.clear();
      for (auto itr = cl.begin(); itr != cl.end(); ++itr)
      {
         for (auto node_itr = nodes[*itr].orig_input.begin(); node_itr != nodes[*itr].orig_input.end(); ++node_itr)
         {
            if (std::find(cl.begin(), cl.end(), *node_itr) == std::end(cl))
            {
               I.insert(*node_itr);
            }
         }
      }

      for (auto itr = I.begin(); itr != I.end(); ++itr)
      {
         if (std::find(L.begin(), L.end(), *itr) == std::end(L))
         {	
            L.push_back(*itr);
         }
      }
   }
}

void calculate_max_parameters()
{
	unsigned int max_delay = 0;

	for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
	{
		if ((*itr).second.label > max_delay)
		{
			max_delay = (*itr).second.label;
		}			
	}

	std::cout << "Maximum delay:\t\t" << max_delay + 1 << "\n";
}

void post_processing()
{
   unsigned int duplication = 0;
   std::vector<std::unordered_set<std::string>> clusters;
   std::vector<std::unordered_set<std::string>> buckets;

   buckets.clear();

   for (auto it = final_clusters.begin(); it != final_clusters.end(); ++it)
   {
      if (it->second.size() < size_constraint)
      {
         clusters.push_back(it->second);
      }
      else
      {
         fclusters.push_back(it->second);
      }
   }
   
   std::stable_sort(clusters.begin(), clusters.end(), [](const std::unordered_set<std::string> &a, const std::unordered_set<std::string> &b) { return a.size() > b.size(); });

   for (unsigned int i = 0; i < clusters.size(); ++i)
   {
      bool flag = 0;
      for (unsigned int it2 = 0; it2 < buckets.size(); ++it2)
      {
         if (clusters[i].size() + buckets[it2].size() <= size_constraint)
         {
            flag = 1;
            for (auto it3 = clusters[i].begin(); it3 != clusters[i].end(); ++it3)
            {
               if (buckets[it2].insert(*it3).second == false)
               {
                  duplication++;
               }
            }
            break;
         }
      }
      if (!flag)
      {
         buckets.push_back(clusters[i]);
      }
   }

   for (auto it = buckets.begin(); it != buckets.end(); ++it)
   {
      fclusters.push_back(*it);
   }

#  ifdef TEST
   
   std::cout << "Final optimized cluster list:\n";

   for (unsigned int it = 0; it < fclusters.size(); ++it)
   {
      for (auto it2 = fclusters[it].begin(); it2 != fclusters[it].end(); ++it2)
      {
         std::cout << *it2 << " ";
      }
      std::cout << "\n";
   }

#  endif

   std::cout << "Cluster count:\t\t\t" << fclusters.size() << "\n";
   std::cout << "Duplicate nodes removed:\t" << duplication << "\n";
}
