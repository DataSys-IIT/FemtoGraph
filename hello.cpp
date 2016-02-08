#include <iostream>
#include <list>

int main()
{
	std::cout << "I am graph processing system!\n";
	std::list<int> linkedList;
	linkedList.push_back(3);
	linkedList.push_back(4);
}

class GraphNode {
public:
  GraphNode(std::list<GraphNode> neighbors, int weight);
	std::list<GraphNode> neighbors;
	int weight;
};


GraphNode::GraphNode(std::list<GraphNode> neighbors, int weight) {
  this->neighbors = neighbors;
  this->weight = weight; 

}

class Graph {
public:
	std::list<GraphNode> vertices;
	void addVertex(GraphNode node);
};

void Graph::addVertex (GraphNode node) {
	vertices.push_back(node);
}

