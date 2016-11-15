#include <vector>
#include <mutex>
#include <thread>
#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/policies.hpp>

#ifndef __queue_H_INCLUDED__
#define __queue_H_INCLUDED__


class message {
public:
  message(int to, double data);
  double data;
  int to;
};


template<class T> class adjlist {
    
public:
  adjlist();
  ~adjlist();
  void pause();
  void unpause();
  int size();
  void addRows(int num);
  boost::lockfree::queue<T, boost::lockfree::fixed_sized<true>> * listAt(int vertex);
  T begin();
  T end();
  void push(boost::lockfree::queue<T, boost::lockfree::fixed_sized<true>> * val);
  void pushToList(int node, T val);
  
private:
  std::vector<boost::lockfree::queue<T, boost::lockfree::fixed_sized<true>>*>  list;
  std::mutex global_mutex;
};


template <class T>
adjlist<T>::adjlist() {
}

template <class T>
adjlist<T>::~adjlist() {
  
}


template <class T>
void adjlist<T>::push(boost::lockfree::queue<T, boost::lockfree::fixed_sized<true>> * val) {
  global_mutex.lock();
  list.push_back(val);
  global_mutex.unlock();
}

template <class T>
boost::lockfree::queue<T, boost::lockfree::fixed_sized<true>> *  adjlist<T>::listAt(int vertex) {
  boost::lockfree::queue<T, boost::lockfree::fixed_sized<true>> * vec = list.at(vertex);
  return  vec;
}

template <class T>
void adjlist<T>::addRows(int num) {
  global_mutex.lock();
  for(int x=0;x<num;x++) {
    boost::lockfree::queue<T, boost::lockfree::fixed_sized<true>> * row = new boost::lockfree::queue<T, boost::lockfree::fixed_sized<true>>(100);
    list.push_back(row);
  }
  global_mutex.unlock();
}

template <class T>
void adjlist<T>::pushToList(int node, T val)  {
  boost::lockfree::queue<T, boost::lockfree::fixed_sized<true>> * messagetmp = list.at(node);
  (*messagetmp).push(val);
}


/* 
 * Locks entire list and does nothing with it until unpause()
 * is called. This is for solving some problems with concurrency
 */
template <class T>
void adjlist<T>::pause() {
  global_mutex.lock();
}


/* unlocks permalock called by pause() */ 
template <class T>
void adjlist<T>::unpause() {
  global_mutex.unlock();
}

  
template <class T>
int adjlist<T>::size() {
  return list.size();
}
 
#endif
