#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

namespace {

  // implement max contiguious sum using kadane's algo
  static int
  maxSum(const std::vector<int>& numbers)
  {
    int ls = 0;
    int gs = 0;

    for(std::vector<int>::const_iterator it = numbers.begin();
	it != numbers.end(); ++it) {
      ls = ls + *it;
      if (ls < 0) {
	ls = 0;
      } // if
      gs = std::max(ls, gs);
    } // for    

    return gs;
  } // maxSum
}  // namespace

int main(int argc, char* argv[])
{
  srand(time(NULL));
  
  static size_t MAX_NUM= 10;
  if (argc > 1) {
    MAX_NUM = std::atoi(argv[1]);
  } // if

  std::vector<int> numbers;
  for (size_t i = 0; i < MAX_NUM; ++i) {
    int num = MAX_NUM/2 - (rand() % MAX_NUM);
    numbers.push_back(num);
  } // for

  int ms = maxSum(numbers);

  std::cout << "Max sum of [";
  for(std::vector<int>::const_iterator it = numbers.begin();
      it != numbers.end(); ++it) {
    std::cout << *it << ",";
  } // for
  std::cout << "] is " << ms << std::endl;
  
} // main
