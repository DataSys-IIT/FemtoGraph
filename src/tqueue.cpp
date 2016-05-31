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


template <class T>
void TQueue<T>::pause() {
  list_mutex(list);
  
}

template <class T>
void TQueue<T>::unpause() {
  list_mutex.unlock();
}


template <class T>
T TQueue<T>::dequeue() {
  T result = list.front;
  list.erase(list.size-1);
  return result;
}


template <class T>
int TQueue<T>::size() {
  return list.size();
}


template <class T>
bool TQueue<T>::empty() {
  if(list.size() == 0)
    return true;
  else
    return false;
}
