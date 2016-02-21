#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

namespace {
  // ***************************************************************************
  // @brief Print the usage of the task
  // ***************************************************************************
  void
  printUsage()
  {
    std::cout << "<Task> <# of numbers> <interval size>"
	      << std::endl;
  } // printUsage

  // ***************************************************************************
  // @brief Generate numbers between 1 and 10
  // @param numbers - (out) generated numbers
  // @param numItems - Number of numbers to generate
  // ***************************************************************************
  void
  generateNumbers(std::vector<double>&  numbers,
		  const size_t          numItems)
  {
    static const size_t NumRange = 10;
    for (size_t i = 0; i < numItems; ++i) {
      double num = static_cast<double>(rand() % NumRange + 1);
      numbers.push_back(num);
    } // for
  } // generateNumbers

  // ***************************************************************************
  // @brief Compute the moving average of the given numbers for the specific
  // interval size
  // @param avgs - (out) Computed averages
  // @param nums - the numbers
  // @intervalSz - Moving average interval size. If the interval is larger than
  // the number of numbers provided, simple average of the numbers will be computed
  // ***************************************************************************
  void
  movingAverages(std::vector<double>& avgs,
		 const std::vector<double>& nums,
		 const size_t intervalSz)
  {
    // we will first compute the first interval average.
    // This depends on the interval size and the number of numbers
    const size_t firstSumSz = std::min(intervalSz, nums.size());

    // keep track of the prev sum
    double prevSum = 0;
    for (size_t i = 0; i < firstSumSz; ++i) {
      prevSum = prevSum + nums[i];
    } // for   
    avgs.push_back(prevSum/(firstSumSz));

    // go through the numbers and compute the averages for the rest of the intervals
    for (size_t i = firstSumSz; i < nums.size(); ++i) {
      // pop out the first number from the prev sum window
      prevSum -= nums[i-firstSumSz];
      // add the current number to the sum window
      prevSum += nums[i];
      // compute the average
      avgs.push_back(prevSum/intervalSz);
    } // for
  } // movingAverages
  
} // namespace

int main(int argc, char* argv[])
{
  static const size_t NumArgs = 3;
  if (argc < NumArgs) {
    printUsage();
    return 1;
  } // if

  srand(time(NULL));
  
  const size_t numItems = std::atoi(argv[1]);
  const size_t intervalSize = std::atoi(argv[2]);

  std::vector<double> numbers;
  generateNumbers(numbers, numItems);
  
  std::cout << "Numbers: " << std::endl;
  std::for_each(numbers.begin(), numbers.end(), [] (double val)
		{std::cout << val << ",";} );
  std::cout << std::endl;
  
  std::vector<double> averages;
  movingAverages(averages, numbers, intervalSize);
  
  std::cout << "Averages: " << std::endl;
  std::for_each(averages.begin(), averages.end(), [] (double val)
		{std::cout << val << ",";} );
  std::cout << std::endl;
  
  return 0;
} // main
