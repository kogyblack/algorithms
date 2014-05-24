#ifndef RRT_PLAN_H
#define RRT_PLAN_H

#include <vector>

class A;
typedef A Edge;
typedef A Point;

class Map;
class Graph;

namespace rrtbase
{

namespace default_functions
{

int nearest(const Graph& graph, Point point);
Point steer(Point from, Point to, double maxDistance);
bool obstacleFree(const Map& m, Point from, Point to);
std::vector<int> near(const Graph& graph, Point point);

}

// Base for RRT, RRG and RRTstar
Graph plan(const Map& m,
          float maxTime,
          Point (*sample)(),
          void (*extend)(Point dest,
                         Graph& graph,
                         int (*nearest)(const Graph&, Point),
                         Point (*steer)(Point, Point, double),
                         bool (*obstacleFree)(const Map&, Point, Point),
                         std::vector<int> (*near)(const Graph&, Point)));

}

#endif
