#include <vector>
#include "api/node.hpp"
#include <map>



/*basically the main interface. Needs a query language... */ 
class QueryBot {

public:
  Result execute(std::string query, std::map<std::string,std::string> params); 
  void registerTransactionHandledr(TransactionHandler t); //sets the handler
private:
  TransactionHandler handler;


};

class Transaction {

public:
  Lock aquireReadLock();
private: 

};


class PropertyContainer {
public:
  std::map<std::string, * void> getAllProps();
  std::map<std::string, * void> getProps(std::string keys[], int size); //not sure if cpp arrays do this
  void * getProp(std::string key);
  void getKeys(std::string & keys[], int & size);
  bool hasProp(std::string key);
  void * removeProp(std::string key);
  void setProp(std::string key, void & value); //again not sure of cpp here. 
private:

};

class TransactionHandler {

public:
  virtual void afterCommit(); //success
  virtual void beforeCommit();
  virtual void afterRollback(); //failure
private:


};


class Result {

public:
  Result();
  ~Result();

  std::vector<Node> getNodes();
  std::vector<Relationship> getRelationships();
private:
  std::vector<Node> nodes;
  std::vector<Relationship> rels;

};



class Lock {

public:
  Lock();
  ~Lock();
  void release();


};
