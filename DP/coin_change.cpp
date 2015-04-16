#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

int coinValue[1000];
int coinQnt;

map<int, int> cache;

int coin(int value)
{
  if (value < 0)
    return 1e9;

  if (cache.find(value) != cache.end())
    return cache[value];

  int mincoin = 1e9;
  for (int i = 0; i < coinQnt; ++i)
    mincoin = min(mincoin, coin(value - coinValue[i]));

  cache[value] = 1 + mincoin;
  return 1 + mincoin;
}

int main()
{
  cache[0] = 0;

  int value = 10;
  coinQnt = 2;
  coinValue[0] = 1;
  coinValue[1] = 5;

  printf("%d\n", coin(value));

  return 0;
}
