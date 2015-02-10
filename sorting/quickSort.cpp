#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

// Quick sort
// This is the fastest sorting algorithm for large arrays.
// Even though the worst case for quick sort is O(N^2), it's extremely
// hard to fall on the worst case in real applications. Also it can
// be probabilistic avoided shuffling the array before sorting.
// This one consists in taking a random number from the array and putting
// all numbers lesser than this sentinel number on it's left (thus all
// numbers on the right will be equal or greater than it) and doing this
// recursively.
template<typename T>
void quickSortInternal(std::vector<T>& vec, int low, int high)
{
  if (low >= high)
    return;

  int pivot = low;
  T pivotValue = vec[pivot];

  int pos = low;

  for (int i = low + 1; i <= high; ++i)
    if (vec[i] <= pivotValue)
      std::swap(vec[i], vec[++pos]);

  std::swap(vec[pivot], vec[pos]);

  quickSortInternal(vec, low, pos - 1);
  quickSortInternal(vec, pos + 1, high);
}

template<typename T>
void quickSort(std::vector<T>& vec)
{
  quickSortInternal(vec, 0, vec.size() - 1);
}


int main()
{
  // Create n random numbers between 0 and n - 1
  std::vector<int> vec;

  int n;
  while (std::cin >> n)
    vec.push_back(n);

  quickSort(vec);

  for (unsigned int i = 0; i < vec.size(); ++i)
    std::cout << vec[i] << " ";
  std::cout << std::endl;

  return 0;
}

