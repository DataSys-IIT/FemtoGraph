#include <vector>
#include "tqueue.hpp"

int main(void) {


}

template <class T>
void TQueue<T>::enqueue(T in) {
  list.push_back(in);
}


template <class T>
T TQueue<T>::dequeue() {
  T result = list.front;
  list.erase(list.size-1);
  return result;
}
