#include <cassert>
#include <cmath>

#include "default_functions.h"
#include "basictypes.h"
#include "map.h"
#include "graph.h"
#include "generator.h"

namespace rrtbase
{

namespace default_functions
{

Point sample(Map const& rrtmap)
{
  double x = rrtmap.getSize().get(0) * generator();
  double y = rrtmap.getSize().get(1) * generator();

  return Point(x, y);
}

int nearest(Graph const& graph, Point const& point)
{
  assert(graph.getVertices().size() > 0);

  std::vector<Graph::Vertice> vertices = graph.getVertices();

  int nearest = 0;
  double minDistance = sqrPythagoras(point, vertices[0].point());

  int numVerts = vertices.size();
  for (int i = 1; i < numVerts; ++i)
  {
    //double dist = boost::geometry::comparable_distance(vertices[nearest].point, vertices[i].point);
    double dist = sqrPythagoras(point, vertices[i].point());

    if (dist < minDistance)
    {
      nearest = i;
      minDistance = dist;
    }
  }

  return nearest;
}

Point steer(Point const& from, Point const& to, double maxDistance)
{
  double distance = sqrPythagoras(from, to);
  if (distance <= maxDistance)
  {
    return to;
  }
  else
  {
    double t = ::sqrt(maxDistance / distance);
    double dx = to.get(0) - from.get(0),
           dy = to.get(1) - from.get(1);
    return Point(from.get(0) + dx * t, from.get(1) + dy * t);
  }
}

bool obstacleFree(Map const& m, Point const& from, Point const& to)
{
  Segment seg(from, to);

  std::vector<Polygon> polygons = m.getPolygons();
  for (int i = 0; i < polygons.size(); ++i)
  {
    //if (boost::geometry::intersects(seg, polys[i]))
    //  return true;

    if (intersects(seg, polygons[i]))
      return false;
  }

  return true;
}

std::vector<int> near(Graph const& graph, int vertice, double maxDistance)
{
  std::vector<int> ret;

  std::vector<Graph::Vertice> vertices = graph.getVertices();
  Point point = vertices[vertice].point();
  vertices.erase(vertices.begin() + vertice);

  for (int i = 0; i < vertices.size(); ++i)
  {
    //double sqrDist = boost::geometry::comparable_distance(point, vertices[i].point);
    double sqrDist = sqrPythagoras(point, vertices[i].point());
    if (sqrDist <= maxDistance * maxDistance)
      ret.push_back(i);
  }

  return ret;
}

}

}
