#include "placeholder_functions.h"
#include "basictypes.h"
#include "map.h"
#include "graph.h"
#include "generator.h"

namespace rrtbase
{

namespace placeholder_functions
{

Point sample(Map const& rrtmap)
{
  return Point();
}

int nearest(Graph const& graph, Point const& point)
{
  return 0;
}

Point steer(Point const& from, Point const& to, double maxDistance)
{
  return Point();
}

bool obstacleFree(Map const& m, Point const& from, Point const& to)
{
  return true;
}

std::vector<int> near(Graph const& graph, int vertice, double maxDistance)
{
  return std::vector<int>();
}

}

}
