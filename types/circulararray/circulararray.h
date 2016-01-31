#include <iosfwd>

namespace kkoppolu {
  class CircularArray {
  public:
    CircularArray();
    void add(int num);

    void print(std::ostream& os);
    
  private:
    CircularArray(const CircularArray&);
    CircularArray& operator=(const CircularArray&);
    
    static const size_t NUM_ITEMS = 10;
    int d_items[NUM_ITEMS];
    
    size_t d_numItems;
    size_t d_startIdx;
  }; // CircularArray
} // kkoppolu
