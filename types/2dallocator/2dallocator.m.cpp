#include <2dallocator.h>
#include <iostream>

int main(int argc, char* argv[])
{
  using namespace kkoppolu;

  static const int numRows = 5;
  static int numCols = 5;

  int** arr = reinterpret_cast<int**>(TwoDAllocator::allocate2d(
				    numRows, numCols));

  if (arr != NULL) {
    for (int i = 0; i < numRows; ++i) {
      for (int j = 0; j < numCols; ++j) {
	arr[i][j] = i+j;
      }
    } // for

    for (int i = 0; i < numRows; ++i) {
      for (int j = 0; j < numCols; ++j) {
	std::cout << &arr[i][j] << ":" << arr[i][j];
	std::cout << "    ";
      }
      std::cout << std::endl;
    } // for
  }
				  
  return 0;
}
