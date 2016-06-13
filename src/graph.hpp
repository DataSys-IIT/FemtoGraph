#include <list>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cmath>
#include <limits>
#include <sstream>
#include <sys/time.h>
#include <queue>
//TODO Add deconstructors - NEED TO CLEANUP

class message {
public:
  message(int to, double data);
  double data;
  int to;
};


class GraphNodeData {
public:
  double weight;
  GraphNodeData(int weight) {
    this->weight = weight;
  }

};

class GraphNode {
public:
  GraphNode(int weight, std::queue<message*> &  messagequeue,   std::vector<GraphNode*>  & vertices, int id) {
    data = new GraphNodeData(weight);
    this->messagequeue = &messagequeue;
    this->id = id;

    /* generate inEdges from neighbors */ 
    for(int x=0;x<neighbors.size();x++) {
      for(int y=0;y<vertices[x]->outEdges.size();y++) {
	if(vertices[vertices[x]->outEdges[y]]->id == id) {
	  this->inEdges.push_back(vertices[x]->id);
	}
      }
    }
  }
  ~GraphNode();
  void compute(std::vector<message>  messages);
  void sendMessageToNodes(std::vector<int> nodes, double msg);
  std::vector<int> neighbors;
  std::vector<int> inEdges;
  std::vector<int> outEdges;
  GraphNodeData *data;
  int id;
private:
  std::queue<message*> * messagequeue;
};



class Graph {
public:
  Graph();
  ~Graph();
  std::vector<GraphNode*> vertices;
  std::queue<message*>  messagequeue;
  void addVertex(int weight);
  void addEdge (int from, int to);
  void print();
  void printRank();
  int size();
  int edgeCount();
  void pagerank (double alpha, double epsilon, int maxIterations);
  int superstep();
private:
  int superstepcount;
  
};

void readGraph (Graph& g, std::string filename);
void readGraphEdges (Graph g, std::string filename);
void printVec (std::vector<GraphNode> ll);


/* appends a message to the message queue for the next iteration */ 
void GraphNode::sendMessageToNodes(std::vector<int> nodes, double msg) {
  for(int x=0;x<nodes.size();x++) {
    message *  m = new message(nodes[x], msg);
    messagequeue->push(m);
  }
}


message::message(int to, double data) {
  this->to = to;
  this->data = data;
}


GraphNode::~GraphNode () {
  if (data != NULL) {
    delete data;
  }
}

void GraphNode::compute(std::vector<message>  messages) {
  
}

Graph::~Graph () {
  std::vector<GraphNode*>::const_iterator nodePtrIter;
  for (nodePtrIter = vertices.begin(); nodePtrIter != vertices.end(); ++nodePtrIter) {
    delete (*nodePtrIter);
  }
  vertices.clear();
  
}

Graph::Graph() {
  superstepcount = 0;
}


int Graph::superstep() {
  return superstepcount;
}

void Graph::addVertex (int weight) {
  //GraphNode *node = new GraphNode(weight);
  //vertices.push_back(new GraphNode(weight));
  vertices.push_back(new GraphNode(weight,messagequeue, vertices, vertices.size()));
}

void Graph::addEdge (int from, int to) {
  vertices[from]->neighbors.push_back(to);
  vertices[to]->inEdges.push_back(from);
}

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
  std::vector<GraphNode*>::const_iterator it;
  for (it = vertices.begin(); it != vertices.end(); it++) {
    total += (*it)->neighbors.size();
  }
  return total;
}

/**
 * NOT THREAD SAFE
 */
void Graph::pagerank (double alpha, double epsilon, int maxIterations) {
  int n = size();
  double linkResult, delta, total_delta = std::numeric_limits<double>::max(), old;
  int iteration = 0;
  std::vector<int>::const_iterator inEdgeIter;
  std::vector<GraphNode*>::const_iterator nodePtrIter, end;
  end = vertices.end();
  GraphNode *v;
  int nodeTouchCount = 0, edgeTouchCount = 0;
  while (iteration < maxIterations && total_delta >= epsilon) {
    total_delta = 0;
    for (nodePtrIter = vertices.begin(); nodePtrIter != end; ++nodePtrIter) {
      nodeTouchCount++;
      v = *nodePtrIter;
      linkResult = 0;
      for (inEdgeIter = v->inEdges.begin(); inEdgeIter != v->inEdges.end(); ++inEdgeIter) {
	// For now, we use 1 for edge weight
	linkResult += (1.0 / vertices[*inEdgeIter]->neighbors.size()) * vertices[*inEdgeIter]->data->weight;
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
  std::ifstream infile(filename);
  int id, to, from, maxId = 0;
  int minId = std::numeric_limits<int>::max();
  while (infile >> id) {
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
