#include <vector>
#include <mutex>



#ifndef __queue_H_INCLUDED__
#define __queue_H_INCLUDED__
namespace threadblob{


template<class T> class queue {
    
  public:
    queue();
    ~queue();
    void pause();
    void unpause();
    void enqueue(T in);
    T dequeue();
    int size();
    bool empty();
    T front();
  private:
    std::vector<T> list;
    std::unique_lock<std::mutex> list_mutex;
    std::unique_lock<std::mutex> audo_mutex;
  };
 
}
#endif
