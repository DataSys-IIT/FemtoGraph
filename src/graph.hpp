#include <list>
#include <vector>

//TODO Add deconstructors - NEED TO CLEANUP

class GraphNodeData {
public:
    double weight;
    GraphNodeData(int weight) {
        this->weight = weight;
    }
};

class GraphNode {
public:
	GraphNode(int weight) {
		data = new GraphNodeData(weight);
	}
	std::vector<int> neighbors;
	std::vector<int> inEdges;
    GraphNodeData *data;
};

class Graph {
public:
	std::vector<GraphNode*> vertices;
	void addVertex(int weight);
	void addEdge (int from, int to);
	void print();
	void printRank();
	int size();
	int edgeCount();
	void pagerank (double alpha, double epsilon, int maxIterations);
};

void readGraph (Graph& g, std::string filename);
void readGraphEdges (Graph g, std::string filename);
void printVec (std::vector<GraphNode> ll);