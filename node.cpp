# include <iostream>
# include "node.h"
#include <queue> 

#define NINF -1

std::unordered_map<std::string, std::unordered_map<std::string, unsigned int>> matrix;

std::unordered_map<std::string, Node> nodes;
std::vector<std::string> PIs;
std::vector<std::string> POs;

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

std::vector<std::string>  topologicalSort()
{
	// Create a vector to store indegrees of all
	// vertices. Initialize all indegrees as 0.
	unsigned int V = total_nodes;
    std::cout<<"V = "<<V<<"\n";
	//std::vector<int> in_degree(V, 0);
	std::unordered_map<std::string, int> in_degree;
	for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
	{
		in_degree.insert(std::make_pair((itr->second).name, 0));
	}
	// Traverse adjacency lists to fill indegrees of
	// vertices.  This step takes O(V+E) time

	for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
	{
		for (auto itr_op = (itr->second).output.begin(); itr_op != (itr->second).output.end(); itr_op++)
			in_degree[*itr_op]++;
	}

	// Create an queue and enqueue all vertices with
	// indegree 0
	std::queue<std::string> q;
	//for (int i = 0; i < V; i++)
	for (auto itr = in_degree.begin(); itr != in_degree.end(); itr++)
		if (itr->second == 0)
			q.push(itr->first);

	// Initialize count of visited vertices
	int cnt = 0;

	// Create a vector to store result (A topological
	// ordering of the vertices)
	std::vector <std::string> top_order;

	// One by one dequeue vertices from queue and enqueue
	// adjacents if indegree of adjacent becomes 0
	while (!q.empty())
	{
		// Extract front of queue (or perform dequeue)
		// and add it to topological order
		std::string u = q.front();
		q.pop();
		top_order.push_back(u);

		// Iterate through all its neighbouring nodes
		// of dequeued node u and decrease their in-degree
		// by 1
		std::vector<std::string>::iterator itr;
		for (itr = nodes[u].output.begin(); itr != nodes[u].output.end(); itr++)
			// If in-degree becomes zero, add it to queue
			if (--in_degree[*itr] == 0)
				q.push(*itr);
		cnt++;
	}

	// Check if there was a cycle
	if (cnt != V)
	{
        std::cout<<"cnt = "<<cnt<<"\n";
		std::cout << "There exists a cycle in the graph\n";
		return top_order;
	}

	// Print topological order
	for (int i = 0; i<top_order.size(); i++)
		std::cout << top_order[i] << " ";
	std::cout << std::endl;

    return top_order;
}

void longest_path(std::string from_node)
{
   std::unordered_map<std::string,int> dist;

    // Initialize distances to all vertices as infinite and
    // distance to source as 0
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
    {
        dist.insert(std::make_pair((itr->second).name, NINF));
    }

    dist[from_node] = 0;

    int top_node = 0;
    int nodes_iterated = 0;
    // Process vertices in topological order
    while (nodes_iterated != topological_order.size())
    {
        // Get the next vertex from topological order
        std::string u = topological_order.at(nodes_iterated);

        // Update distances of all adjacent vertices
        std::vector<std::string>::iterator i;
        if (dist[u] != NINF)
        {
            for (auto i = nodes[u].output.begin(); i != nodes[u].output.end(); ++i)
                if (dist[*i] < dist[u] + 1)
                    dist[*i] = dist[u] + 1;
        }
        nodes_iterated++;
    }
	std::unordered_map<std::string, unsigned int> longest_dist;
    // Print the calculated longest distances
    for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
    {
        if (dist[itr->first] == NINF)
        {
			dist[itr->first] = 0;
			//std::cout <<itr->first <<"="<< dist[itr->first];
        }
        else
        {
           // std::cout << itr->first << "=" << dist[(itr->second).name] << " ";
        }
		longest_dist.insert(std::make_pair(itr->first, dist[itr->first]));
    }
	matrix.insert(std::make_pair(from_node, longest_dist));

	return;

}

void initialize()
{
	std::cout << "Starting initialisation phase";
	for (auto itr = nodes.begin(); itr != nodes.end(); itr++)
	{
		longest_path(itr->first);
	}

	for (auto itr = matrix.begin(); itr != matrix.end(); itr++)
	{
		std::cout << "Node " << itr->first << " : ";

		for (auto itr1 = (itr->second).begin(); itr1 != (itr->second).end(); itr1++)
		{
			std::cout << itr1->first << "=" << itr1->second << " ";
		}

		std::cout << "\n";
	}

	topological_order.erase(topological_order.begin(), topological_order.begin() + PIs.size());

	// Print topological order
	for (int i = 0; i<topological_order.size(); i++)
		std::cout << topological_order[i] << " ";
	std::cout << std::endl;

}