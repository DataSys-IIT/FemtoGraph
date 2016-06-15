#include <iostream>
#include "graph.hpp"

int main(int argc, char *argv[])
{
  Graph g;
  g.addVertex(3);
  g.addVertex(1);
  g.addVertex(2);
  g.addVertex(5);
  g.addEdge(0,3);
  g.addEdge(2,1);
  g.addEdge(1,3);
  g.start();
}
