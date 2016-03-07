#include <vector>

/* Some classes representing nodes, edges, and
 * associated data.
 */ 

class Node {

public:
  virtual void createRelationship(Relationship R);
  Data getData();
  void setData(Data d);
protected:
  std::vector<Relationship> relationships;
  Data datavalue;

};


/* represents a relationship between nodes */ 
class Relationship {

public:
  Node to;
  Node from;
 virtual  Relationship();
  ~Relationship();
  Data getData();
  void setData(Data d);

protected: 
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

protected:
  std::vector<T> datalist;
  
};
