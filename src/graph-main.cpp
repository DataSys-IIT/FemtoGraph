#include <iostream>
#include "graph.hpp"

int main(int argc, char *argv[])
{
  Graph g;
  readGraph(g, argv[1]);
  std::cout << "Starting pagerank" << "\n";
  if(atoi(argv[2]) > 0) {
    try {
    g.start(atoi(argv[2]));
    }
    catch(std::out_of_range & ex) {
      std::cout << ex.what() << std::endl;
    }
  }
  else
    std::cout << "Invalid thread count\n";
  //g.print();
  //g.printRank();
}
