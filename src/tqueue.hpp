#include <vector>
#include <mutex>

namespace threadblob { 

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
  private:
    std::vector<T> list;
    std::unique_lock<std::mutex> list_mutex;
    std::unique_lock<std::mutex> audo_mutex;
  };
  
}
