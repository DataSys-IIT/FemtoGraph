#include <iostream>
#include "graph.hpp"

int main(int argc, char *argv[])
{
  Graph g;
  readGraph(g, argv[1]);
  std::cout << "Starting pagerank" << "\n";
  if(atoi(argv[2]) > 0)
    g.start(atoi(argv[2]));
  else
    std::cout << "Invalid thread count\n";
  //g.print();
  //g.printRank();
}
