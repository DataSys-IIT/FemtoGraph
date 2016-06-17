#include <vector>
#include <mutex>
#include <thread>


#ifndef __queue_H_INCLUDED__
#define __queue_H_INCLUDED__


template<class T> class adjlist {
    
public:
  adjlist();
  ~adjlist();
  void pause();
  void unpause();
  int size();
  void addRows(int num);
  std::vector<T> * listAt(int vertex);
  T begin();
  T end();
  void push(std::vector<T> * val);
  void pushToList(int node, T val);
  
private:
  std::vector<std::vector<T>*>  list;
  std::mutex global_mutex;
};


template <class T>
adjlist<T>::adjlist() {
}

template <class T>
adjlist<T>::~adjlist() {
  typename std::vector<std::vector<T>*>::const_iterator row;
  typename std::vector<T>::const_iterator col;
  for(row = list.begin() ;row != list.end() ; ++row) {
    for(col = (*row)->begin(); col != (*row)->end(); ++col) {
      delete *col;
    }
    delete *row;;
  }
}


template <class T>
void adjlist<T>::push(std::vector<T> * val) {
  global_mutex.lock();
  list.push_back(val);
  global_mutex.unlock();
}

template <class T>
std::vector<T> *  adjlist<T>::listAt(int vertex) {
  global_mutex.lock();
  std::vector<T> * vec = list.at(vertex);
  global_mutex.unlock();
  return  vec;
}

template <class T>
void adjlist<T>::addRows(int num) {
  global_mutex.lock();
  for(int x=0;x<num;x++) {
    std::vector<T> * row = new std::vector<T>();
    list.push_back(row);
  }
  global_mutex.unlock();
}

template <class T>
void adjlist<T>::pushToList(int node, T val)  {
  std::vector<T> * messagetmp = list.at(node);
  global_mutex.lock();
  (*messagetmp).push_back(val);
  global_mutex.unlock();
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
