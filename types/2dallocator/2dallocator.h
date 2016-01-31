#include <cstdlib>

namespace kkoppolu {
  class TwoDAllocator
  {
  public:
    static void* allocate2d(size_t rows, size_t cols);
  };
  
} // kkoppolu
