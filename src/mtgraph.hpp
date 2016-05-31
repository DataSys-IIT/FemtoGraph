#include <vector>
#include <unordered_map>
#include <queue>
#include "queue.hpp"

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
    //TODO Add lock for multithreading
	GraphNode(int weight) {
		data = new GraphNodeData(weight);
	}
	std::vector<int> neighbors;
	std::vector<int> inEdges;
    GraphNodeData *data;
};

//WARNING Queue is not thread safe
class Graph {
public:
	std::unordered_map<int, GraphNode*> vertices;
  tqueue<int> *  taskQueue; //TODO find a threadsafe queue implmentation
    Graph() {
        done = false;
	taskQueue = new tqueue<int>();
    }

  ~Graph() {
    delete taskQueue;
  }
    bool done;
    void update (int nodeId);
    void threadMain ();
    void start (int numThreads);
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
