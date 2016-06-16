#include <iostream>
#include "graph.hpp"

int main(int argc, char *argv[])
{
  Graph g;
  readGraph(g, argv[1]);
  std::cout << "Starting pagerank" << "\n";
  g.start(4);
  g.print();
  g.printRank();
}
