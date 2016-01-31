#include <circulararray.h>
#include <iostream>
#include <string.h>

namespace kkoppolu {

  CircularArray::CircularArray()
    :d_startIdx(0)
  {
    memset(d_items, 0, sizeof(d_items));
  }

  void
  CircularArray::add(int num)
  {
    if (d_numItems < NUM_ITEMS) {
      d_items[d_numItems++] = num;
    } else {
      d_items[d_startIdx++] = num;
      if (d_startIdx >= NUM_ITEMS) {
	d_startIdx = 0;
      } // if
    }
  } // add

  void
  CircularArray::print(std::ostream& os)
  {
    for (int i = 0; i < NUM_ITEMS; ++i) {
      os << d_items[i] << ",";
    } // for
    os << std::endl;
  } // print

  
} // kkoppolu
