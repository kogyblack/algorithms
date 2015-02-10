#include <cstdlib>
#include <vector>
#include <iostream>
//#include <memory>

template<class T>
void selectionSort(std::vector<T>& vec)
{
  int vecSize = vec.size();
  for (int i = 0; i < vecSize - 1; ++i)
    for (int j = i + 1; j < vecSize; ++j)
      if (vec[j] < vec[i])
        std::swap(vec[j], vec[i]);
}

int main()
{
  std::vector<int> vec;

  int num;
  while(std::cin >> num)
    vec.push_back(num);

  selectionSort(vec);

  for (unsigned int i = 0; i < vec.size(); ++i)
    std::cout << vec[i] << " ";
  std::cout << std::endl;

  return 0;
}
