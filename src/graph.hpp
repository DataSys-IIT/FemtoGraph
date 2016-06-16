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
#include <iostream>
#include <thread>
#include "adjlist.hpp"
//enables some expensive validation and error checking
#define ECC 0

//TODO Add deconstructors - NEED TO CLEANUP


/* represents a messaqge for the pregel message queue */
class message {
public:
  message(int to, double data);
  double data;
  int to;
};



/* data payload (weight) for graph vertex */
class GraphNodeData {
public:
  double weight;
  GraphNodeData(int weight) {
    this->weight = weight;
  }

};


//declare GraphNode because Graph depends on it
class GraphNode;

/* represents the entire simulation
 * Responsible for managing vertexes and calling compute() 
 * on all of them
 */ 
class Graph {
public:
  Graph();
  ~Graph();
  std::vector<GraphNode*> vertices;
  adjlist<message*>  messagequeue;
  void addVertex(int weight);
  void addEdge (int from, int to);
  void print();
  void printRank();
  int size();
  int edgeCount();
  int superstep();
  void start(int threads);
  bool isDone();
  void threadMain(int id);
private:
  int superstepcount;
  int numThreads;
  
};


/* represents a vertex in the graph */ 
class GraphNode {
public:
  GraphNode(int weight, adjlist<message*> &  messagequeue,  Graph * graph, int id) {
    data = new GraphNodeData(weight);
    this->messagequeue = &messagequeue;
    this->id = id;
    this->graph = graph;
    isHalted = false;
    
    /* generate inEdges from neighbors */ 
    for(int x=0;x<neighbors.size();x++) {
      for(int y=0;y<graph->vertices[x]->outEdges.size();y++) {
	if(graph->vertices[graph->vertices[x]->outEdges[y]]->id == id) {
	  this->inEdges.push_back(graph->vertices[x]->id);
	}
      }
    }
  }
  ~GraphNode();
  void compute(const std::vector<message*> *  messages);
  void sendMessageToNodes(std::vector<int> nodes, double msg);
  std::vector<int> neighbors;
  std::vector<int> inEdges;
  std::vector<int> outEdges;
  GraphNodeData *data;
  int id;
  void voteToHalt();
  void unHalt();
  bool isHalted;
  Graph * graph;
private:
  adjlist<message*> * messagequeue;
};



//some extra function
void readGraph (Graph& g, std::string filename);
void readGraphEdges (Graph g, std::string filename);
void printVec (std::vector<GraphNode> ll);


/* appends a message to the message queue for the next iteration */ 
void GraphNode::sendMessageToNodes(std::vector<int> nodes, double msg) {
  for(int x=0;x<nodes.size();x++) {
    message *  m = new message(nodes[x], msg);
    int nodeid = graph->vertices[nodes[x]]->id;
    messagequeue->pushToList(nodeid, m);
  }
}



//send a message to one vertex
message::message(int to, double data) {
  this->to = to;
  this->data = data;
}



//destructor for graphnode
GraphNode::~GraphNode () {
  if (data != NULL) {
    delete data;
  }
}


/* 
 * Pregel 'update' function. Called virtually in parallel from 
 * the context of each vertex. 
 */  
void GraphNode::compute(const std::vector<message*> *  messages) {
    #if ECC
  if(messagequeue->size() != graph->vertices.size()) {std::cout<<"BLARG"<<"\n"; exit(2);}
  #endif
  if(graph->superstep() >= 1) {
    double sum = 0;
    for(int x=0;x<messages->size();x++) {
      sum += (*messages)[x]->data;
    }
    this->data->weight = 0.15 / graph->size() + 0.85 * sum;
  }
  if(graph->superstep() < 30) {
    const long n = this->outEdges.size();
    sendMessageToNodes(this->neighbors, this->data->weight / n);
  }
  else {
    voteToHalt();
  }
}


//halts the vertex until it receives a message or all
//vertexes halt
void GraphNode::voteToHalt() {
  isHalted = true;
}

//resume the vertex compute
void GraphNode::unHalt() {
  isHalted = false; 
}


//dewstructor for graph
Graph::~Graph () {
  std::vector<GraphNode*>::const_iterator nodePtrIter;
  for (nodePtrIter = vertices.begin(); nodePtrIter != vertices.end(); ++nodePtrIter) {
    delete (*nodePtrIter);
  }

  vertices.clear();
  
}


//constructor for graph
Graph::Graph() {
  superstepcount = 0;
  messagequeue.addRows(vertices.size());
}


//is every vertex halted?
bool Graph::isDone() {
  #if ECC
  if(messagequeue.size() != vertices.size()) {std::cout<<"BLARG"<<"\n"; exit(2);}
  #endif
  bool result = true;
  for(int i=0;i<vertices.size();i++) {
    if(vertices[i]->isHalted == false)
      result = false;
  }
  
  return result;
}

void Graph::start(int threads) {
    #if ECC
  if(messagequeue.size() != vertices.size()) {std::cout<<"BLARG"<<"\n"; exit(2);}
  #endif
  numThreads = threads;
  while(!isDone()) {
    std::vector<std::thread*> threads;
    std::cout << "SUPERSTEP " << superstepcount << "\n";
    for (int i = 0; i < numThreads; i++) {
      threads.push_back(new std::thread(&Graph::threadMain, this, i ));
    }
    for (int i = 0; i < numThreads; i++) {
      threads[i]->join();
    }

    for(int i=0;i<numThreads;i++) {
      delete threads[i];
    }
    superstepcount++;
  }
  
}


void Graph::threadMain(int id) {
  std::cout << "started thread id: "<<id << "\n";
  for(int x=id;x<messagequeue.size();x = x + numThreads) {
    vertices[x]->compute(messagequeue.listAt(x));
  }
}



//returns current pregel superstep count
int Graph::superstep() {
  return superstepcount;
}


//adds a vertex to the graph
void Graph::addVertex (int weight) {
    #if ECC
  if(messagequeue.size() != vertices.size()) {std::cout<<"BLARG"<<"\n"; exit(2);}
  #endif
  //GraphNode *node = new GraphNode(weight);
  //vertices.push_back(new GraphNode(weight));
  vertices.push_back(new GraphNode(weight,messagequeue, this, vertices.size()));
  std::vector<message*> * nodequeue = new std::vector<message*>();
  messagequeue.push(nodequeue);

}


//adds an edge to the graph
void Graph::addEdge (int from, int to) {
    #if ECC
  if(messagequeue.size() != vertices.size()) {std::cout<<"BLARG"<<"\n"; exit(2);}
  #endif
  vertices[from]->neighbors.push_back(to);
  vertices[to]->inEdges.push_back(from);
}


//prints out current graph
void Graph::print () {
    #if ECC
  if(messagequeue.size() != vertices.size()) {std::cout<<"BLARG"<<"\n"; exit(2);}
  #endif
  std::vector<int>::const_iterator it;
  for (int i = 0; i < vertices.size(); i++) {
    std::cout << i << "-> ";
    for (it = vertices[i]->neighbors.begin(); it != vertices[i]->neighbors.end(); it++) {
      std::cout << (*it) << ' ';
    }
    std::cout << std::endl;
  }
}


//prtints the weight of the vertices
void Graph::printRank () {
  std::list<int>::const_iterator it;
  for (int i = 0; i < vertices.size(); i++) {
    std::cout << i << "-> " << vertices[i]->data->weight << std::endl;
  }
}

//size of graph
int Graph::size () {
  return vertices.size();
}


//returns number of edges
int Graph::edgeCount () {
  int total = 0;
  std::vector<GraphNode*>::const_iterator it;
  for (it = vertices.begin(); it != vertices.end(); it++) {
    total += (*it)->neighbors.size();
  }
  return total;
}


//prints a list of ints (for debug)
void printList (std::list<int> ll) {
  std::list<int>::const_iterator it;
  for (it = ll.begin(); it != ll.end(); it++) {
		std::cout << (*it) << ' ';
  }
}


//prints a list of graphnodes
void printVec (std::vector<GraphNode> ll) {
  std::vector<GraphNode>::const_iterator it;
  for (it = ll.begin(); it != ll.end(); it++) {
    std::cout << it->data->weight << ' ';
  }
}


//reads a graph in from file
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
    //std::cout << "Adding edge " << from << "=>" << to << "\n"; 
    g.addEdge(from, to);
  }
}
