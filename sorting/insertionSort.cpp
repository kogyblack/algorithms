#include <iostream>
#include <vector>

template<typename T>
void insertionSort(std::vector<T>& vec)
{
  int vecSize = vec.size();
  for (int i = 1; i < vecSize; ++i)
    for (int j = i; j > 0 && (vec[j] < vec[j - 1]); --j)
      std::swap(vec[j], vec[j - 1]);
}

int main()
{
  std::vector<int> vec;

  int num;
  while (std::cin >> num)
    vec.push_back(num);

  insertionSort(vec);

  for (unsigned int i = 0; i < vec.size(); ++i)
    std::cout << vec[i] << " ";
  std::cout << std::endl;

  return 0;
}
