# include <iostream>
# include "node.h"
#include <queue> 

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

void topologicalSort()
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
		return;
	}

	// Print topological order
	for (int i = 0; i<top_order.size(); i++)
		std::cout << top_order[i] << " ";
	std::cout << std::endl;
}
