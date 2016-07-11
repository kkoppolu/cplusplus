#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

namespace {
  void
  printNumber(const int num)
  {
    std::cout << num << std::endl;
  } // printNum


  // bubble the ith element to the correct position in a pass
  void
  bubbleSort(std::vector<int> numbers)
  {
    for (size_t i = 0; i < numbers.size(); ++i) {
      for (size_t j = i+1; j < numbers.size(); ++j) {
	if (numbers[i] > numbers[j]) {
	  int tmp = numbers[i];
	  numbers[i] = numbers[j];
	  numbers[j] = tmp;
	} // if
      } // for
    } // for
    std::cout << "BUBBLE" << std::endl;
    std::for_each(numbers.begin(), numbers.end(), printNumber);
    std::cout << "**********************************************************************"
	      << std::endl;

  } // bubbleSort

  // select the lowest/highest element in every pass and put it in ith position
  void
  selectionSort(std::vector<int> numbers)
  {
    for (size_t i = 0; i < numbers.size(); ++i) {
      int minIdx = i;
      for (size_t j = i+1; j < numbers.size(); ++j) {
	if (numbers[j] < numbers[minIdx]) {
	  minIdx = j;
	} // if
      } // for
      //swap

      if (minIdx != i) {
	int tmp = numbers[minIdx];      
	numbers[minIdx] = numbers[i];
	numbers[i] = tmp;
      } // if
    } // for

    std::cout << "SELECTION" << std::endl;
    std::for_each(numbers.begin(), numbers.end(), printNumber);
    std::cout << "**********************************************************************"
	      << std::endl;

  } // selectionSort


  // insert the given number in the correct position of the array
  // at the begining the first element (1array of size 1 is sorted)
  void
  insertionSort(std::vector<int> numbers)
  {
    for (size_t i = 1; i < numbers.size(); ++i) {
      const int sortedSize = i;
      int j = 0;
      // find the appropriate insertion position
      while (numbers[i] >= numbers[j] && j < sortedSize) {
	++j;
      } // while

      // insert
      int numToInsert = numbers[i];
      if (j != i) {
	for (int k = i; k > j; --k) {
	  numbers[k] = numbers[k-1];
	} // for
      } // if
      numbers[j] = numToInsert;
    } // for
    std::cout << "INSERTION" << std::endl;
    std::for_each(numbers.begin(), numbers.end(), printNumber);
    std::cout << "**********************************************************************"
	      << std::endl;

  } // insertionSort


  // Hoare partition scheme
  int
  doQPartition(std::vector<int>& numbers, int begin, int end)
  {
    int pivot = numbers[(begin + end)/2];
    int i = begin;
    int j = end - 1;
    while (i < j) {
      // find the first number that violates the partition rule
      while (numbers[i] < pivot) {
	++i;
      } 
      // find the last number that violates the partition rule
      while(numbers[j] > pivot) {
	--j;
      } // while

      // we end up with 2 numbers that are equal to the pivot,
      // no point spinning our wheels by swapping them.
      // adjust the pivot slightly
      if (numbers[i] == numbers[j]) {
	++pivot;
      } // if

      // if they do indeed occur on either side of the pivot
      if (i < j) {
	// swap them
	int tmp = numbers[i];
	numbers[i] = numbers[j];
	numbers[j] = tmp;
	// go to the next out of place pair
	++i;
	++j;
      }  else {
	// at this point i == j (i > j is impossible) because
	// the comparisons < and > will return false
	// when comparing the pivot with itself
      } // if
    } // while
    return j;
  } // doQPartition
  
  // end exclusive and begin inclusive
  void
  doQSort(std::vector<int>& numbers, int begin, int end)
  {
    if (begin >= end) {
      return;
    } // if

    int partitionIdx = doQPartition(numbers, begin, end);
    // sort the left partition
    doQSort(numbers, begin, partitionIdx);
    // sort the right partition
    doQSort(numbers, partitionIdx + 1, end);

  } // doQSort


  void doMergeSort(std::vector<int>& numbers, int left, int right)
  {
    // only 1 element
    if (right - left <= 1) {
      return;
    } // if

    int mid = (left + right)/2;
    // sort left array
    doMergeSort(numbers, left, mid);
    // sort the right array
    doMergeSort(numbers, mid, right);

    // merge them both
    std::vector<int> tmp;  
    int leftIdx = left;
    int leftLimit = mid;
    int rightIdx = mid;
    int rightLimit = right;
    do {
      // right array exhausted
      if (rightIdx >= rightLimit) {
	std::copy(&numbers[leftIdx], &numbers[leftLimit],
		  std::back_inserter(tmp));
	leftIdx = leftLimit;
      } else if (leftIdx >= leftLimit) {
	// left array exhausted
	std::copy(&numbers[rightIdx], &numbers[rightLimit],
		  std::back_inserter(tmp));
	rightIdx = rightLimit;
      } else {
	if (numbers[leftIdx] < numbers[rightIdx]) {
	  tmp.push_back(numbers[leftIdx++]);
	} else {
	  tmp.push_back(numbers[rightIdx++]);
	} // if
      }
    } while (leftIdx < leftLimit || rightIdx < rightLimit);

    std::copy(tmp.begin(), tmp.end(), &numbers[left]);

  } // doMergeSort

  void
  mergeSort(std::vector<int> numbers)
  {
    std::cout << "MERGE SORT" << std::endl;
    doMergeSort(numbers, 0, numbers.size());
    std::for_each(numbers.begin(), numbers.end(), printNumber);
    std::cout << "**********************************************************************"
	      << std::endl;
  }
  
  void
  qSort(std::vector<int> numbers)
  {
    doQSort(numbers, 0, numbers.size());
    std::cout << "QUICK SORT" << std::endl;
    std::for_each(numbers.begin(), numbers.end(), printNumber);
    std::cout << "**********************************************************************"
	      << std::endl;
  }

  // move the given element down to its children to maintain the
  // heap property
  void
  percolateHeapElemDown(int k, std::vector<int>& numbers, const int sz)
  {
    while (k >= 0) {
      const int lChild = 2*k + 1;
      const int rChild = lChild + 1;

      if (lChild >= sz) {
	break;
      } // if

      // select the child to swap against
      int childIdx = lChild;
      if (rChild < sz
	  && (numbers[rChild] > numbers[lChild])) {
	childIdx = rChild;
      } // if
      // perform the swap if necessary
      if (numbers[childIdx] > numbers[k]) {
	int tmp = numbers[k];
	numbers[k] = numbers[childIdx];
	numbers[childIdx] = tmp;
      } else {
	break;
      } // if
      k = childIdx;
    } // for 
  } // percolateHeapElemDown


  // delete the root
  void
  heapDelete(std::vector<int>& numbers, int& sz)
  {
    const int rootIdx = 0;
    if (sz==0) {
      throw "0 heap size";
    }
    
    int root = numbers[rootIdx];

    // swap with the last element
    int tmp = numbers[rootIdx];
    numbers[rootIdx] = numbers[sz -1];
    numbers[sz - 1] = tmp;

    // update the size
    sz = sz - 1;

    // percolate it down a heap of one less element
    percolateHeapElemDown(rootIdx, numbers, sz);

  }
  
  void
  heapify(std::vector<int>& numbers, const int sz)
  {
    // Root = (k+1)/2 -1      [(k-1)/2]  // for 1 indexed: k/2
    // Left = 2(k+1) -1       [2k + 1]   // for 1 indexed: 2k
    // Right = 2(k+1) + 1 -1  [2k + 2]   // for 1 indexed: 2k+1
    for (int k = (sz-2)/2; k >= 0; --k) {
      // all the elements in the first half of the array
      // will have children in the second  half of the array
      // so set their children up properly per heap order property
      percolateHeapElemDown(k, numbers, sz);
    } // for    
  } // heapify

  void
  heapSort(std::vector<int> numbers)
  {
    int numHeapElems = numbers.size();
    // heapify
    heapify(numbers, numHeapElems);
    do {
      // pop the max and move it to the last
      // and keep it out of the heap
      heapDelete(numbers, numHeapElems);
    } while (numHeapElems > 0);

    std::cout << "HEAP SORT" << std::endl;
    std::for_each(numbers.begin(), numbers.end(), printNumber);
    std::cout << "**********************************************************************"
	      << std::endl;
  } // heapSort
    
    
} // anonymous


int main(int argc, char* argv[])
{
  std::ifstream fs("numberlist.txt");
  std::vector<int> numbers;
  if (fs.is_open()) {
    std::string line;
    while (std::getline(fs, line)) {
      numbers.push_back(std::atoi(line.c_str()));
    } // while
  } // if

/*  std::random_shuffle(numbers.begin(), numbers.end());
  selectionSort(numbers);

  std::random_shuffle(numbers.begin(), numbers.end());
  insertionSort(numbers);

  std::random_shuffle(numbers.begin(), numbers.end());
  bubbleSort(numbers);

  std::random_shuffle(numbers.begin(), numbers.end());
  qSort(numbers);

  std::random_shuffle(numbers.begin(), numbers.end());
  mergeSort(numbers);
*/
  std::random_shuffle(numbers.begin(), numbers.end());
  heapSort(numbers);

  return 0;
}
