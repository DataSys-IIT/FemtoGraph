#include <iostream>
#include "hmgraph.hpp"

int main(int argc, char *argv[])
{
	double epsilon, damping;
	int maxIterations;
	bool verbose = false;
	if (argc < 5) {
		std::cout << "Usage: " << argv[0] << " <edge list filename> <epsilon> <damping factor> <max iterations> [verbose]" << std::endl;
		return 1;
	}
	std::cout << "I am graph processing system!\n";
	Graph g2;
	readGraph(g2, argv[1]);
	epsilon = atof(argv[2]);
	damping = atof(argv[3]);
	maxIterations = atoi(argv[4]);
	if (argc > 5) {
		std::cout << "verbose mode enabled" << std::endl;
		verbose = true;
	}
	else {
		std::cout << "verbose mode disabled" << std::endl;
	}
	std::cout << "epsilon: " << epsilon << std::endl;
	std::cout << "damping: " << damping << std::endl;
	std::cout << "max iterations: " << maxIterations << std::endl;
	if (verbose) {
		g2.print();
		g2.printRank();
	}
	struct timeval start, end;
	double elapsed;
	gettimeofday(&start, NULL);
	g2.pagerank(damping, epsilon, maxIterations);
//    g2.pagerank(0.5, .01, 12);
	gettimeofday(&end, NULL);
	elapsed = ((end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec) / (double)1000000;
	if (verbose) {
		g2.printRank();
	}
	std::cout << "Number of nodes: " << g2.size() << std::endl;
	std::cout << "Number of edges: " << g2.edgeCount() << std::endl;
	std::cout << elapsed << std::endl;
}

