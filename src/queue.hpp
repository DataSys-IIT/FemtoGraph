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
  std::unique_lock<std::mutex> list_mutex;
  std::unique_lock<std::mutex> auto_mutex;
};
template <class T>
tqueue<T>::tqueue() {
  
}


template <class T>
tqueue<T>::~tqueue() {
  list_mutex.unlock();
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
  list_mutex(list);  
}


/* unlocks permalock called by pause() */ 
template <class T>
void tqueue<T>::unpause() {
  list_mutex.unlock();
}


template <class T>
T tqueue<T>::dequeue() {
  std::lock_guard<std::mutex> auto_mutex(global_mutex);
  T result = list.front();
  list.erase(list.end()); //maybe front
  return result;
}

  
template <class T>
int tqueue<T>::size() {
  std::lock_guard<std::mutex> auto_mutex(global_mutex);  
  return list.size();
}


template <class T>
bool tqueue<T>::empty() {
  std::lock_guard<std::mutex> auto_mutex(global_mutex);
  if(list.size() == 0)
    return true;
  else
    return false;
}


template <class T>
T tqueue<T>::front() {
  return list.front();
}
 
#endif
