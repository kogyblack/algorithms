#include <cassert>

#include <boost/geometry/algorithms/comparable_distance.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

#include "basictypes.h"
#include "plan.h"
#include "map.h"
#include "graph.h"

namespace rrtbase
{

namespace default_functions
{

// Since boost's distance isn't working to Points,
// lets create a pythagoras funtion
inline double pythagoras(Point a, Point b)
{
  double x = a.get<0>() - b.get<0>(),
         y = a.get<1>() - b.get<1>();
  return (x * x) + (y * y);
}

int nearest(const Graph& graph, Point point)
{
  assert(graph.getVertices().size() > 0);

  int nearest;
  double minDistance = boost::numeric::bounds<double>::highest();

  Graph::Vertices vertices = graph.getVertices();
  int numVerts = vertices.size();
  for (int i = 0; i < numVerts; ++i)
  {
    // XXX: This should fucking work!!!
    //double dist = boost::geometry::comparable_distance(vertices[nearest].point, vertices[i].point);
    double dist = pythagoras(point, vertices[i].point);

    if (dist < minDistance)
    {
      nearest = i;
      minDistance = dist;
    }
  }

  return nearest;
}

Point steer(Point from, Point to, double maxDistance)
{
  double dist = pythagoras(from, to);
  if (dist <= maxDistance)
  {
    return to;
  }
  else
  {
    double t = maxDistance / dist;
    double dx = to.get<0>() - from.get<0>(),
           dy = to.get<1>() - from.get<1>();
    return Point(from.get<0>() + dx * t, from.get<1>() + dy * t);
  }
}

bool obstacleFree(const Map& m, Point from, Point to)
{
  Polygon seg;
  seg.outer().push_back(from);
  seg.outer().push_back(to);

  std::vector<Polygon> polys = m.getPolygons();
  for (int i = 0; i < polys.size(); ++i)
  {
    if (boost::geometry::intersects(seg, polys[i]))
      return true;
  }

  return false;
}

std::vector<int> near(const Graph& graph, Point point)
{
}

}

// Base for RRT, RRG and RRTstar
Graph plan(Map m,
          float maxTime,
          Point (*sample)(),
          void (*extend)(Point dest,
                         Graph& graph,
                         int (*nearest)(const Graph&, Point),
                         int (*steer)(Point, Point),
                         bool (*obstacleFree)(Point, Point),
                         std::vector<int> (*near)(const Graph&, Point)))
{
  Graph graph;

  return graph;
}

}
