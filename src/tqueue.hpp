#include <vector>
#include <mutex>

template<class T> class TQueue {

public:
  void enqueue(T in);
  T dequeue();
  int size();
  bool empty();
private:
  std::vector<T> list;
  std::mutex list_mutex;

};
