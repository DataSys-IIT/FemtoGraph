#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <list>
#include <cmath>
#include <limits>
#include <map>
#include <sys/time.h>

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
  std::unordered_map<int, GraphNode*> vertices;
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



void Graph::addVertex (int weight) {
  //GraphNode *node = new GraphNode(weight);
  vertices[this->size()] = new GraphNode(weight);
}

void Graph::addEdge (int from, int to) {
  vertices[from]->neighbors.push_back(to);
  vertices[to]->inEdges.push_back(from);
}

//TODO iterate over keys to support non sequential keys
void Graph::print () {
  std::vector<int>::const_iterator it;
  for (int i = 0; i < vertices.size(); i++) {
    std::cout << i << "-> ";
    for (it = vertices[i]->neighbors.begin(); it != vertices[i]->neighbors.end(); it++) {
      std::cout << (*it) << ' ';
    }
    std::cout << std::endl;
  }
}

//TODO iterate over keys to support non sequential keys
void Graph::printRank () {
  std::list<int>::const_iterator it;
  for (int i = 0; i < vertices.size(); i++) {
    std::cout << i << "-> " << vertices[i]->data->weight << std::endl;
	}
}

int Graph::size () {
  return vertices.size();
}

int Graph::edgeCount () {
  int total = 0;
  for (int i = 0; i < vertices.size(); i++) {
    total += vertices[i]->neighbors.size();
  }
  //	std::unordered_map<int, GraphNode*>::const_iterator it;
  //	for (it = vertices.begin(); it != vertices.end(); it++) {
  //		total += (*it)->neighbors.size();
  //	}
  return total;
}

/**
 * NOT THREAD SAFE
 */
void Graph::pagerank (double alpha, double epsilon, int maxIterations) {
  int n = size();
  double linkResult, delta, total_delta = std::numeric_limits<double>::max(), old;
  int iteration = 0;
  std::list<int>::const_iterator inEdgeIter;
  std::vector<GraphNode*>::const_iterator nodePtrIter;
  int inEdgeId;
  GraphNode *v;
  int nodeTouchCount = 0, edgeTouchCount = 0;
  while (iteration < maxIterations && total_delta >= epsilon) {
    total_delta = 0;
    for (int i = 0; i < this->size(); i++) {
      nodeTouchCount++;
      v = vertices[i];
      linkResult = 0;
      for (int i = 0; i < v->inEdges.size(); i++) {
	// For now, we use 1 for edge weight
	inEdgeId = v->inEdges[i];
	linkResult += (1.0 / vertices[inEdgeId]->neighbors.size()) * vertices[inEdgeId]->data->weight;
	edgeTouchCount++;
      }
      old = v->data->weight;
      v->data->weight = n*((alpha / n) + (1 - alpha) * linkResult/n);
      delta = fabs(v->data->weight - old);
      total_delta += delta;
    }
    std::cout << "Delta: " << total_delta << std::endl;
    iteration++;
  }
  std::cout << "Iterations completed: " << iteration << std::endl;
  std::cout << "Vertices touched: " << nodeTouchCount << std::endl;
  std::cout << "Edges touched: " << edgeTouchCount << std::endl;
}

void printList (std::list<int> ll) {
  std::list<int>::const_iterator it;
  for (it = ll.begin(); it != ll.end(); it++) {
    std::cout << (*it) << ' ';
  }
}

void printVec (std::vector<GraphNode> ll) {
  std::vector<GraphNode>::const_iterator it;
  for (it = ll.begin(); it != ll.end(); it++) {
    std::cout << it->data->weight << ' ';
  }
}

void readGraphEdges (Graph g, std::string filename) {
  std::ifstream infile(filename);
  int from, to;
  while (infile >> from >> to) {
    g.addEdge(from-1, to-1);
  }
}

// expects to/from edge pairs
// id starts at 1
void readGraph (Graph& g, std::string filename) {
  std::cout << "Reading in graph\n";
  std::ifstream infile(filename);
  int id, to, from, maxId = 0;
  int minId = std::numeric_limits<int>::max();
  while (infile >> id) {
    std::cout << "id: " << id << "\n";
    maxId = std::max(id-1, maxId);
    minId = std::min(id-1, minId);
  }
  for (int i = minId; i <= maxId; i++) {
    // all same starting weight
    g.addVertex(1);
  }
  // return to beginning of file
  infile.clear();
  infile.seekg(0, std::ios::beg);
  while (infile >> from >> std::skipws >> to) {
    g.addEdge(from-1, to-1);
  }
}
