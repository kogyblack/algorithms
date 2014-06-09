#ifndef PLACEHOLDER_FUNCTIONS_H
#define PLACEHOLDER_FUNCTIONS_H

#include <vector>

#include "basictypes.h"

class Map;
class Graph;

namespace rrtbase
{

namespace placeholder_functions
{

Point sample(Map const& rrtmap);
int nearest(Graph const& graph, Point const& point);
Point steer(Point const& from, Point const& to, double maxDistance);
bool obstacleFree(Map const& m, Point const& from, Point const& to);
std::vector<int> near(Graph const& graph, int, double maxDistance);

}

}

#endif
