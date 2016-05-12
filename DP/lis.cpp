/*
  Longest Increasing Subsequence
  Dynamic Programming solution
  */

#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;

int lis(int vec[], int n)
{
  vector<int> l (n, 1);

  int maxi = 1;
  for (int i = 1; i < n; ++i)
    for (int j = 0; j < i; ++j)
      if (vec[i] > vec[j])
        l[i] = max(l[i], 1+l[j]), maxi = max(maxi, l[i]);

  return maxi;
}

int main()
{
  int vec[7] = {1, 3, 2, 4, 5, 0, 9};

  printf("%d\n", lis(vec, 7));

  return 0;
}
