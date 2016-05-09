#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <cmath>
#include <limits>
#include <sys/time.h>
#include "graph.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <edge list filename>" << std::endl;
		return 1;
	}
	std::cout << "I am graph processing system!\n";
	Graph g2;
	readGraph(g2, argv[1]);
	g2.print();
	g2.printRank();
	struct timeval start, end;
	double elapsed;
	gettimeofday(&start, NULL);
    g2.pagerank(0.5, .000000001, 12);
//    g2.pagerank(0.5, .01, 12);
	gettimeofday(&end, NULL);
    elapsed = ((end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec) / (double)1000000;
	g2.printRank();
	std::cout << "Number of nodes: " << g2.size() << std::endl;
	std::cout << "Number of edges: " << g2.edgeCount() << std::endl;
	std::cout << elapsed << std::endl;
}



void Graph::addVertex (int weight) {
	//GraphNode *node = new GraphNode(weight);
	vertices.push_back(new GraphNode(weight));
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
	while (infile >> from >> to) {
		g.addEdge(from-1, to-1);
	}
}
