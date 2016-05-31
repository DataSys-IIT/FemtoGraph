#include <vector>
#include <mutex>

template<class T> class TQueue {

public:
  TQueue();
  ~TQueue();
  void pause();
  void unpause();
  void enqueue(T in);
  T dequeue();
  int size();
  bool empty();
private:
  std::vector<T> list;
  std::unique_lock<std::mutex> list_mutex;
  std::unique_lock<std::mutex> audo_mutex;
};
