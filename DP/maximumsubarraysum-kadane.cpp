#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int A[100000];

// Kadane
int maxsubarray(int b, int e)
{
  int maxend, maxsofar;
  maxend = maxsofar = A[b];
  for (int i = b + 1; i <= e; ++i)
  {
    maxend = max(A[i], maxend + A[i]);
    maxsofar = max(maxsofar, maxend);
  }
  return maxsofar;
}

int main()
{
  int n, m;
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i)
    scanf("%d", &A[i]);

  scanf("%d", &m);
  for (int i = 0; i < m; ++i)
  {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d\n", maxsubarray(x, y));
  }

  return 0;
}
