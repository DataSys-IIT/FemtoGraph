#include <vector>
#include "tqueue.hpp"
#include <mutex> 


int main(void) {

  
}


template <class T>
TQueue<T>::TQueue() {

}


template <class T>
TQueue<T>::~TQueue() {
  list_mutex.unlock();
  delete list_mutex;
}

template <class T>
void TQueue<T>::enqueue(T in) {
  list.push_back(in);
}



/* 
 * Locks entire list and does nothing with it until unpause()
 * is called. This is for solving some problems with concurrency
 */
template <class T>
void TQueue<T>::pause() {
  list_mutex(list);
  
}


/* unlocks permalock called by pause() */ 
template <class T>
void TQueue<T>::unpause() {
  list_mutex.unlock();
}


template <class T>
T TQueue<T>::dequeue() {
  std::lock_guard<std::mutex> auto_mutex(list);
  T result = list.front;
  list.erase(list.size-1);
  return result;
}


template <class T>
int TQueue<T>::size() {
  std::lock_guard<std::mutex> auto_mutex(list);  
  return list.size();
}


template <class T>
bool TQueue<T>::empty() {
  std::lock_guard<std::mutex> auto_mutex(list);
  if(list.size() == 0)
    return true;
  else
    return false;
}
