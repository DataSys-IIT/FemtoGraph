#include <vector>
#include <mutex>



#ifndef __queue_H_INCLUDED__
#define __queue_H_INCLUDED__


template<class T> class tqueue {
    
public:
  tqueue();
  ~tqueue();
  void pause();
  void unpause();
  void enqueue(T in);
  T dequeue();
  int size();
  bool empty();
  T front();
private:
  std::vector<T> list;
  std::mutex global_mutex;
};
template <class T>
tqueue<T>::tqueue() {
  
}


template <class T>
tqueue<T>::~tqueue() {
 
}

template <class T>
void tqueue<T>::enqueue(T in) {
  list.push_back(in);
}



/* 
 * Locks entire list and does nothing with it until unpause()
 * is called. This is for solving some problems with concurrency
 */
template <class T>
void tqueue<T>::pause() {
  global_mutex.lock();
}


/* unlocks permalock called by pause() */ 
template <class T>
void tqueue<T>::unpause() {
  global_mutex.unlock();
}


template <class T>
T tqueue<T>::dequeue() {
  global_mutex.lock();
  T result = list.front();
  list.erase(list.end()); //maybe front
  global_mutex.unlock();
  return result;
}

  
template <class T>
int tqueue<T>::size() {
  return list.size();
}


template <class T>
bool tqueue<T>::empty() {
  global_mutex.lock();
  if(list.size() == 0) {
    global_mutex.unlock();
    return true;
  }
  else {
    global_mutex.unlock();
    return false;
  }
}


template <class T>
T tqueue<T>::front() {
  return list.front();
}
 
#endif
