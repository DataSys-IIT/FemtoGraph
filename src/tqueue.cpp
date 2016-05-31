#include <vector>
#include "tqueue.hpp"
#include <mutex> 


int main(void) {
  
  
}


namespace threadblob {

  template <class T>
  queue<T>::queue() {
    
  }
  
  
  template <class T>
  queue<T>::~queue() {
    list_mutex.unlock();
    delete list_mutex;
  }
  
  template <class T>
  void queue<T>::enqueue(T in) {
    list.push_back(in);
  }
  
  

  /* 
   * Locks entire list and does nothing with it until unpause()
   * is called. This is for solving some problems with concurrency
   */
  template <class T>
  void queue<T>::pause() {
    list_mutex(list);
    
  }
  

  /* unlocks permalock called by pause() */ 
  template <class T>
  void queue<T>::unpause() {
    list_mutex.unlock();
  }
  

  template <class T>
  T queue<T>::dequeue() {
    std::lock_guard<std::mutex> auto_mutex(list);
    T result = list.front;
    list.erase(list.size-1);
    return result;
  }

  
  template <class T>
  int queue<T>::size() {
    std::lock_guard<std::mutex> auto_mutex(list);  
    return list.size();
  }
  
  
  template <class T>
  bool queue<T>::empty() {
    std::lock_guard<std::mutex> auto_mutex(list);
    if(list.size() == 0)
      return true;
    else
      return false;
  }

}
