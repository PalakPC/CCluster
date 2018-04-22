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
      std::cout << *i << ' ';

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

	if (cnt != total_nodes)
	{
      std::cout << "cnt = " << cnt << "\n";
		std::cout << "There exists a cycle in the graph\n";
	}	
}

void longest_path(std::string from_node)
{
   unsigned int count;
   count = 0;
   auto it = nodes[from_node].output.begin(); 
   while (1)
   {
      if (it == nodes[from_node].output.end())
      {
         break;
      }
/*
     if (nodes.find(from_node)->second.output.find(it->first)->second != 1)
      {
         break;
      }
*/
      auto it2 = nodes[it->first].output.begin(); 
      while (it2 != nodes[it->first].output.end())
      {
         if (nodes[from_node].output.find(it2->first) == nodes[from_node].output.end())
         {
            auto got = nodes.find(from_node);
            got->second.output.insert(std::make_pair(it2->first, (it2->second + 1)));
            for (auto i = got->second.output.begin(); i != got->second.output.end(); ++i)
            {
               std::cout << i->first<<" ";
            }
            std::cout << "\n";
            nodes[it2->first].input.push_back(from_node);
         }
         else if (nodes[from_node].output.find(it2->first)->second >= (it2->second + 1))
         {
            break;
         }
         else
         {
            nodes[from_node].output.find(it2->first)->second = (it2->second + 1);
         }
         ++it2;
      }
      ++it;
      ++count;
   }
}
/*
   unsigned int top_node;
   unsigned int nodes_iterated;
   std::string u;
   std::unordered_map<std::string,int> dist;
   std::unordered_map<std::string, unsigned int> longest_dist;

   for (auto itr = nodes.begin(); itr != nodes.end(); ++itr)
   {
      dist.insert(std::make_pair(itr->first, NINF));
   }

   dist[from_node] = 0;
   top_node = 0;
   nodes_iterated = 0;

   while (nodes_iterated != topological_order.size())
   {
      u = topological_order.at(nodes_iterated);

      if (dist[u] != NINF)
      {
         for (auto i = nodes[u].output.begin(); i != nodes[u].output.end(); ++i)
         {
            if (dist[*i] < dist[u] + 1)
            {
               dist[*i] = dist[u] + 1;
            }
         }
      }
      ++nodes_iterated;
   }

   for (auto itr = nodes.begin(); itr != nodes.end(); ++itr)
   {
      if (dist[itr->first] == NINF)
      {
         dist[itr->first] = 0;
      }
      longest_dist.insert(std::make_pair(itr->first, dist[itr->first]));
   }

   matrix.insert(std::make_pair(from_node, longest_dist));
   */
//}

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
   unsigned int level;
	unsigned int l1;
	unsigned int l2;
	std::vector<std::pair<std::string, unsigned int>> G;
   std::vector<std::pair<unsigned int, std::pair<std::string, unsigned int>>> S;
	std::unordered_set<std::string> this_cluster;
   std::set<std::pair<std::string, unsigned int>> temp_queue;
   std::set<std::string> gates;
	l1 = 0;
	l2 = 0;

   G.push_back(std::make_pair(cur_node, 0));
   for (auto i = nodes[cur_node].input.begin(); i != nodes[cur_node].input.end(); ++i)
   {
      gates.insert(*i);
      temp_queue.insert(std::make_pair(*i, 1));
   }

   while (!temp_queue.empty())
   {
      auto temp = *temp_queue.begin();
      temp_queue.erase(temp_queue.begin());
      G.push_back(temp);
      
      for (auto i = nodes[temp.first].input.begin(); i != nodes[temp.first].input.end(); ++i)
      {
         auto ret = gates.insert(*i);

         if (ret.second)
         {
            temp_queue.insert(std::make_pair(*i, temp.second + 1));
         }

         else
         {
            for (auto it = G.begin(); it != G.end(); ++it)
            {
               if ((it->first == *i) && (it->second < (temp.second + 1)))
               {
                  G.erase(it);
                  G.push_back(std::make_pair(*i, temp.second + 1));
               }
            }
         }
      }
   }

	for (auto itr = G.begin(); itr != G.end(); ++itr) 
	{
		if (itr->first != cur_node)
		{
			S.push_back(std::make_pair((nodes[itr->first].label + matrix[itr->first][cur_node]), *itr));
		}		
	}

	std::stable_sort(S.begin(), S.end(), [](const std::pair<unsigned int, std::pair<std::string, unsigned int>> &a, const std::pair<unsigned int, std::pair<std::string, unsigned int>> &b) { if (a.first == b.first) return a.second.second < b.second.second; else return a.first > b.first; });
   
   count = 0;
   std::vector<std::pair<unsigned int, std::pair<std::string, unsigned int>>>::iterator itr;
	for (itr = S.begin(); ((count < (size_constraint - 1)) && (itr != S.end())); ++itr, ++count)
	{
		this_cluster.insert(itr->second.first);
		
      if (p_input.find((*itr).second.first) != p_input.end())
		{
			l1 = ((*itr).first > l1) ? (*itr).first : l1;
		}
	}

	this_cluster.insert(cur_node);

	if (itr != S.end())
   {
		l2 = (*itr).first + inter_cluster_delay;
   }

	else
   {
		l2 = 0;
   }
	
   nodes[cur_node].label = l1 > l2 ? l1 : l2;
	nodes[cur_node].cluster = this_cluster;
}

std::vector<std::string> calculate_cluster_inputs(std::vector<std::string> cl)
{
	std::vector<std::string> I;


	return I;
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
         for (auto node_itr = nodes[*itr].input.begin(); node_itr != nodes[*itr].input.end(); ++node_itr)
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
