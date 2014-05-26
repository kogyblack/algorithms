#ifndef DEFAULT_FUNCTIONS_H
#define DEFAULT_FUNCTIONS_H

#include <vector>

class Point;
class Map;
class Graph;

namespace rrtbase
{

namespace default_functions
{

Point sample(Map const& rrtmap);
int nearest(Graph const& graph, Point const& point);
Point steer(Point const& from, Point const& to, double maxDistance);
bool obstacleFree(Map const& m, Point const& from, Point const& to);
std::vector<int> near(Graph const& graph, int, double maxDistance);

}

}

#endif
