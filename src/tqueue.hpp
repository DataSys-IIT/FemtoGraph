#include <vector>
template<class T> class TQueue {

public:
  void enqueue(T in);
  T dequeue();
private:
  std::vector<T> list;

};
