#include "api/node.hpp"
/* basically extending classes in the API */




class pageRank {

public:
  
private:
  

};

class Vertex: public Node {

public:
  void createRelationship(Relationship R);
  PageRankVertexData getData();
  void setData(PageRankVertexData d);
private:
  std::vector<Edge> relationships;
  PageRankVertexData dataValue;  
};


class Edge: public Relationship {

public:
  Vertex to;
  Vertex from;
  Relationship();
  PageRankEdgeData getData();
  void setData(PageRankEdgeData d);
private:
  PageRankEdgeData datavalue;
};


class PageRankEdgeData : public Data {
public:
  Data();
  
private:
  int weight;
};

class PageRankVertexData : public Data {
public:
  Data();
private:
  int pagerank;
};
