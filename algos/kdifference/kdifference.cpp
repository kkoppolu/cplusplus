#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

namespace {
  int findPairs(const std::vector<int>& numbers, int k)
  {
    std::cout << "K is " << k << std::endl;
    int numPairs = 0;
    std::unordered_set<int> numberSet(numbers.begin(), numbers.end());
    for (std::vector<int>::const_iterator itr = numbers.begin();
	 itr != numbers.end(); ++itr) {
      const int num = *itr;
      std::cout << num << std::endl;
      if (numberSet.find(num + k) != numberSet.end()) {
	std::cout << "Pair is (" << num << ", " << num+k << ")" << std::endl;
	++numPairs;
      } // if
    } // for
    return numPairs;  
  } // findPairs

  
} // namespace

int main()
{
  // seed
  std::srand(std::time(NULL));

  static const size_t MAX_NUMS = 7;
  std::vector<int> numbers;
  numbers.reserve(MAX_NUMS);
  
  for (size_t i = 0; i < MAX_NUMS; ++i) {
      int num = 1 + rand() % 10;
      numbers.push_back(num);
  } // for

  const int k = std::rand() % 5;
  std::sort(numbers.begin(), numbers.end());
  std::vector<int>::iterator it =
    std::unique(numbers.begin(), numbers.end());
  numbers.resize(std::distance(numbers.begin(), it));
  std::random_shuffle (numbers.begin(), numbers.end() );
  std::cout << "Num pairs: " << findPairs(numbers, k)
	    << std::endl;

  return 0;
}
