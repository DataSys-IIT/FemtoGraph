#include <vector>

/* Some classes representing nodes, edges, and
 * associated data.
 */ 

class Node {

public:
  virtual createRelationship(Relationship R);
  Data getData();
  void setData(Data d);
private:
  std::vector<Relationship> * relationships;
  Data datavalue;

};


/* represents a relationship between nodes */ 
class Relationship {

public:
  Node to;
  Node from;
  Relationship();
  ~Relationship();
  Data getData();
  void setData(Data d);

private: 
  Data datavalue;
};

/* generic data template for edges and vertecies */ 
template <typename T> class Data {

public:
  virtual Data();
  ~Data();
  T getData();
  void setData(T dat);
  const std::vector<T> * getDataRef();

private:
  std::vector<T> datalist;
  
};
