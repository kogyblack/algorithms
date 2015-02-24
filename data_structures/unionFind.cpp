#include <cstdio>
#include <vector>
using namespace std;

vector<int> pset;

void initSet(int s)
{
  pset.resize(s);
  for (int i = 0; i < s; ++i)
    pset[i] = i;
}

int findSet(int i)
{
  return (pset[i] == i) ? i : (pset[i] = findSet(pset[i]));
}

void unionSet(int i, int j)
{
  pset[findSet(i)] = findSet(j);
}

bool isSameSet(int i, int j)
{
  return findSet(i) == findSet(j);
}

int main()
{
  int n;
  scanf("%d", &n);
  initSet(n);

  return 0;
}
