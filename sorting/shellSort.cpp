#include <iostream>
#include <vector>

template<typename T>
void shellSort(std::vector<T>& vec)
{
  int vecSize = vec.size();
  int h = 1;
  while (3 * h < vecSize)
    h = 3 * h + 1;

  while (h > 0)
  {
    for (int i = h; i < vecSize; ++i)
      for (int j = i; j >= h && (vec[j] < vec[j - h]); j -= h)
        std::swap(vec[j], vec[j - h]);

    h /= 3;
  }
}

int main()
{
  std::vector<int> vec;

  int num;
  while (std::cin >> num)
    vec.push_back(num);

  shellSort(vec);

  for (unsigned int i = 0; i < vec.size(); ++i)
    std::cout << vec[i] << " ";
  std::cout << std::endl;

  return 0;
}
