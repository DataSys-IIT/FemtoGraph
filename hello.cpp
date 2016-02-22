#include <iostream>
#include <list>

void printList(std::list<int> ll);

int main()
{
	std::cout << "I am graph processing system!\n";
	std::list<int> linkedList;
	linkedList.push_back(3);
	linkedList.push_back(4);
	printList(linkedList);
}

class GraphNode {
public:
	GraphNode(std::list<GraphNode> neighbors, int weight) {
		this->neighbors = neighbors;
		this->weight = weight; 
	}
	std::list<GraphNode> neighbors;
	int weight;
};



class Graph {
public:
	std::list<GraphNode> vertices;
	void addVertex(GraphNode node);
};

void Graph::addVertex (GraphNode node) {
	vertices.push_back(node);
}

void printList (std::list<int> ll) {
	std::list<int>::const_iterator it;
	for (it = ll.begin(); it != ll.end(); it++) {
		std::cout << (*it) << ' ';
	}
}