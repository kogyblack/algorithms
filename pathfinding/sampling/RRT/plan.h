#ifndef RRT_PLAN_H
#define RRT_PLAN_H

#include <vector>

class A;
typedef A Edge;
//typedef A Point;
class Point;

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
std::vector<int> near(Graph const& graph, Point const& point, double maxDistance);

}

namespace default_functions
{

Point sample(Map const& rrtmap);
int nearest(Graph const& graph, Point const& point);
Point steer(Point const& from, Point const& to, double maxDistance);
bool obstacleFree(Map const& m, Point const& from, Point const& to);
std::vector<int> near(Graph const& graph, Point const& point, double maxDistance);

}

// Base for RRT, RRG and RRTstar
void plan(Map const& rrtmap,
          double maxTime,
          Graph& graph,
          void (*extend)(Point const& to,
                         Map const& rrtmap,
                         Graph& graph,
                         int (*nearest)(Graph const&, Point const&),
                         Point (*steer)(Point const&, Point const&, double),
                         bool (*obstacleFree)(Map const&, Point const&, Point const&),
                         std::vector<int> (*near)(Graph const&, Point const&, double)),
          bool anytime = false,
          Point (*sample)(Map const& rrtmap) = default_functions::sample,
          int (*nearest)(Graph const&, Point const&) = default_functions::nearest,
          Point (*steer)(Point const&, Point const&, double) = default_functions::steer,
          bool (*obstacleFree)(Map const&, Point const&, Point const&) = default_functions::obstacleFree,
          std::vector<int> (*near)(const Graph&, Point const&, double) = default_functions::near);

}

#endif
