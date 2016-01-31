#include <2dallocator.h>
#include <iostream>

namespace kkoppolu {
  // ***************************************************************************
  // @brief the below function allocates a 2D memory block such that the regular
  // subscript operations [i][j] are mainatined.
  // The memory is llocated in one go such that the begining blocks correspond
  // to the row pointers and each row pointer corresponds to a block of memory
  // holding "cols" number of data types
  // ***************************************************************************
  void*
  TwoDAllocator::allocate2d(size_t rows, size_t cols)
  {
    // store row ptrs of type T* (int here)
    size_t numBytes = sizeof(int*) * rows;
    // store a row of "cols" columns of the given type (int here)
    numBytes += sizeof(int) * (rows * cols);

    // allocate all the memory in 1 go
    int** memPtr = reinterpret_cast<int**>(malloc(numBytes));
    if (memPtr == NULL) {
      return NULL;
    } // if
    // the above memory chunk is allocated such that it holds
    // all row ptrs in the begining
      
    // get the address where the buffer starts
    int* buf = reinterpret_cast<int*>(memPtr + rows);

    // now every rowptr must point to its corresponding cols set
    for (size_t i = 0; i < rows; ++i) {
      // skip through "cols" addresses for every row
      memPtr[i] = buf + i * cols;
    } // for
    return memPtr;
  } // allocate
  
} // kkoppolu
