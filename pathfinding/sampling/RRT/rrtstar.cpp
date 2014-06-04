#include <iostream>

#include <algorithm>
#include <vector>

#include <boost/geometry.hpp>

#include "rrtstar.h"
#include "basictypes.h"
#include "graph.h"
#include "map.h"

namespace rrtstar
{

void extend(Point const& to,
            Map const& rrtmap,
            rrtbase::Graph& graph,
            int (*nearest)(rrtbase::Graph const& graph, Point const& point),
            Point (*steer)(Point const& from, Point const& to, double maxDistance),
            bool (*obstacleFree)(Map const& rrtmap, Point const& from, Point const& to),
            std::vector<int> (*near)(rrtbase::Graph const& graph, int vertice, double maxDistance))
{
  std::vector<rrtbase::Graph::Vertice> vertices = graph.getVertices();

  int verticeNearest = nearest(graph, to);
  Point pointNearest = vertices[verticeNearest].point();
  Point pointNew = steer(pointNearest, to, rrtbase::resolution);

  if (obstacleFree(rrtmap, pointNearest, pointNew))
  {
    int verticeNew = graph.addVertice(pointNew);

    //if (pointInsideRect(pointNew, rrtmap.getGoalRect()))
    //  graph.setCompleted(true, verticeNew);
    if (boost::geometry::within(pointNew, rrtmap.getGoalRect()))
      graph.setCompleted(true, verticeNew);

    std::vector<int> verticesNear = near(graph, verticeNew, rrtbase::resolution * 4);
    for (int verticeNear : verticesNear)
    {
      if (obstacleFree(rrtmap, vertices[verticeNear].point(), pointNew))
      {
        graph.addEdge(verticeNear, verticeNew);
      }
    }

    int parent = graph.updateCost(verticeNew);
    graph.setUniqueParent(verticeNew, parent);

    auto findParent = find(verticesNear.begin(), verticesNear.end(), parent);
    if (findParent != verticesNear.end())
      verticesNear.erase(findParent);

    for (int verticeNear : verticesNear)
    {
      if (obstacleFree(rrtmap, pointNew, vertices[verticeNear].point()))
      {
        if (graph.getCost(verticeNear) > graph.getCost(verticeNew) + graph.simulateCost(verticeNear, verticeNew))
        {
          graph.removeEdge(vertices[verticeNear].parent(), verticeNear);
          graph.addEdge(verticeNew, verticeNear);
        }
      }
    }
  }
}

}
