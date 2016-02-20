#include "node.hpp"
#include <vector>


class Path {


public:
  Node startNode();
  Node endNode();
  std::vector<Relationship> * getRelationships();
  std::vector<Relationship> * getRelationshipsReverse(); 
  Relationship *  lastRelationship(); //last relation in vector
  int getLength();
private:
  Node start;
  Node end;
  int length;
  std::vector<Node> nodeList;
  

};
