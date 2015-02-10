#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>

// Merge sort
// This one is a divide-and-conquer algorithm.
// It consists in dividing the array in two subarrays, sorting the
// subarrays and merging the subarrays together.
// It works very well for large arrays.
// Time complexity: O(N logN)
// Space complexity: O(N)
template<typename T>
void merge(std::vector<T>& vec, int low, int mid, int high)
{
  // Create auxiliar array that copies from low to high
  std::vector<T> aux (vec.begin() + low, vec.begin() + high + 1);

  // We have to work from 0 to (high - low), so we reduce high and mid
  // from low.
  high -= low;
  mid -= low;

  int i = 0,
      j = mid + 1;

  for (int k = low; k <= high; ++k)
  {
    if (i > mid)              vec[k] = aux[j++];
    else if (j > high)        vec[k] = aux[i++];
    else if (aux[j] < aux[i]) vec[k] = aux[j++];
    else                      vec[k] = aux[i++];
  }
}

template<typename T>
void mergeSortInternal(std::vector<T>& vec, int low, int high)
{
  if (high <= low)
    return;

  int mid = low + (high - low) / 2;
  mergeSortInternal(vec, low, mid);
  mergeSortInternal(vec, mid + 1, high);
  merge(vec, low, mid, high);
}

template<typename T>
void mergeSort(std::vector<T>& vec)
{
  mergeSortInternal(vec, 0, vec.size() - 1);
}

int main()
{
  std::vector<int> vec;

  int n;
  while (std::cin >> n)
    vec.push_back(n);

  mergeSort(vec);

  for (unsigned int i = 0; i < vec.size(); ++i)
    std::cout << vec[i] << " ";
  std::cout << std::endl;

  return 0;
}

