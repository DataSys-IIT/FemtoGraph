#include <iostream>
#include <list>

int main()
{
	std::cout << "I am graph processing system!\n";
	std::list<int> linkedList;
	linkedList.push_back(3);
	linkedList.push_back(4);
}

class Graph {
public:
	std::list<GraphNode> vertices;
	void addVertex(GraphNode node);
};

Graph::addVertex (GraphNode node) {
	vertices.push_back(node);
}

class GraphNode {
public:
	std::list<GraphNode> neighbors;
	int weight;
}