#include <iostream>
#include <vector>

#include "rrt.h"
#include "basictypes.h"
#include "graph.h"
#include "map.h"

namespace rrt
{

const double resolution = 0.5;

void extend(Point const& to,
            Map const& rrtmap,
            rrtbase::Graph& graph,
            int (*nearest)(rrtbase::Graph const& graph, Point const& point),
            Point (*steer)(Point const& from, Point const& to, double maxDistance),
            bool (*obstacleFree)(Map const& rrtmap, Point const& from, Point const& to),
            std::vector<int> (*near)(rrtbase::Graph const& graph, Point const& point, double maxDistance))
{
  int verticeNearest = nearest(graph, to);
  Point pointNearest = graph.getVertices()[verticeNearest].point();
  Point pointNew = steer(pointNearest, to, resolution);

  if (obstacleFree(rrtmap, pointNearest, pointNew))
  {
    int verticeNew = graph.addVertice(pointNew);
    graph.addEdge(verticeNearest, verticeNew);

    if (pointInsideRect(pointNew, rrtmap.getGoalRect()))
      graph.setCompleted(true);
  }
}

}
