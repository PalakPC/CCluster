/*
 * Miscellaneous functions
 */

# include <queue> 
# include <set>
# include <map>
# include "node.h"

#define NINF -1

std::unordered_map<std::string, Node> nodes;
std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>> matrix;
std::unordered_set<std::string> p_input;
std::unordered_set<std::string> p_output;
std::vector<std::string> topological_order;
std::unordered_map<std::string, std::unordered_set<std::string>> final_clusters;

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
   std::cout << "label: " << label;

   std::cout << "\nInputs: ";
   for (auto i = input.begin(); i != input.end(); ++i)
      std::cout << i->first << ":" << i->second << ' ';

   std::cout << "\nOutputs: ";
   for (auto i = output.begin(); i != output.end(); ++i)
      std::cout << i->first << ":" << i->second << ' ';
   
   std::cout << "\nCluster: ";
   for (auto i = cluster.begin(); i != cluster.end(); ++i)
      std::cout << *i << ' ';

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
		in_degree.insert(std::make_pair(itr->first, 0));
	}

	for (auto itr = nodes.begin(); itr != nodes.end(); ++itr)
	{
		for (auto itr_op = (itr->second).output.begin(); itr_op != (itr->second).output.end(); ++itr_op)
      {
			++in_degree[itr_op->first];
      }
	}
	
   for (auto itr = in_degree.begin(); itr != in_degree.end(); ++itr)
   {
		if (itr->second == 0)
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
   std::map<std::string, unsigned int> temp;
   auto got = nodes.find(from_node);
   for (auto it = got->second.output.begin(); it != got->second.output.end(); ++it)
   {
      temp.insert(*it);
   }

   for (auto it = temp.begin(); it != temp.end(); ++it)
   {
      for (auto it2 = nodes.find(it->first)->second.output.begin(); it2 != nodes.find(it->first)->second.output.end(); ++it2)
      {
         if(got->second.output.find(it2->first) == got->second.output.end())   
         {
            temp.insert(std::make_pair(it2->first, (it->second + 1)));
            got->second.output.insert(std::make_pair(it2->first, (it->second + 1)));
            nodes.find(it2->first)->second.input.insert(std::make_pair(from_node, (it->second + 1)));
         }
         else if (got->second.output.find(it2->first)->second < (it->second + 1))
         {
            got->second.output.find(it2->first)->second = (it->second + 1);
            nodes.find(it2->first)->second.input.find(from_node)->second = (it->second + 1);
         }
         else
         {
            break;
         }
      }
   }
}

void initialize()
{
   for (auto itr = topological_order.begin(); itr != topological_order.end(); ++itr)
   {
      longest_path(*itr);
   }
   
   topological_order.erase(topological_order.begin(), topological_order.begin() + p_input.size());
}

void create_labels()
{
	for (auto itr = topological_order.begin(); itr != topological_order.end(); itr++)
	{
		label_node(*itr);
	}
}

void label_node(std::string cur_node)
{
   unsigned int count;
	unsigned int l1;
	unsigned int l2;
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

   count = 0;
   std::vector<std::pair<std::pair<std::string, unsigned int>, unsigned int>>::iterator itr;
	for (itr = S.begin(); ((count < (size_constraint - 1)) && (itr != S.end())); ++itr, ++count)
	{
		nodes[cur_node].cluster.insert(itr->first.first);
		
      if (p_input.find((*itr).first.first) != p_input.end())
		{
			l1 = ((*itr).second > l1) ? (*itr).second : l1;
		}
	}

	nodes[cur_node].cluster.insert(cur_node);

	if (itr != S.end())
   {
		l2 = (*itr).second + inter_cluster_delay;
   }

   nodes[cur_node].label = l1 > l2 ? l1 : l2;
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
	std::unordered_set<std::string> max_path;

	for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
	{
		if ((*itr).second.label > max_delay)
		{
			max_delay = (*itr).second.label;
			max_path = (*itr).second.cluster;
		}			
	}

	std::cout << "The maximum delay: " << max_delay << "\n";
	std::cout << "The cluster with max delay: ";
	for (auto itr = max_path.begin(); itr != max_path.end(); itr++)
	{
		std::cout << *itr << " ";
	}
   std::cout << "\n";
}
