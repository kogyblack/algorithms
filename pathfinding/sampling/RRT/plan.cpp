#include <iostream>

#include <algorithm>
#include <ctime>
#include <limits>
#include <random>
#include <chrono>

#include <cassert>
#include <cmath>

//#include <boost/geometry/algorithms/comparable_distance.hpp>
//#include <boost/geometry/algorithms/intersects.hpp>

#include "basictypes.h"
#include "plan.h"
#include "map.h"
#include "graph.h"

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

namespace default_functions
{

Point sample(Map const& rrtmap)
{
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::mt19937 generator(seed);

  double x = rrtmap.getSize().get(0) * generator() / generator.max();
  double y = rrtmap.getSize().get(1) * generator() / generator.max();

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

// Base for RRT, RRG and RRTstar
void plan(Map const& rrtmap,
          double maxTime,
          Graph& graph,
          void (*extend)(Point const& dest,
                         Map const& rrtmap,
                         Graph& graph,
                         int (*nearest)(const Graph&, Point const&),
                         Point (*steer)(Point const&, Point const&, double),
                         bool (*obstacleFree)(const Map&, Point const&, Point const&),
                         std::vector<int> (*near)(const Graph&, int, double)),
          bool anytime,
          Point (*sample)(Map const& rrtmap),
          int (*nearest)(const Graph&, Point const&),
          Point (*steer)(Point const&, Point const&, double),
          bool (*obstacleFree)(const Map&, Point const&, Point const&),
          std::vector<int> (*near)(const Graph&, int, double))
{
  std::cout << "Initiating planning!" << std::endl;

  graph.reset();
  graph.addVertice(rrtmap.getInitialPoint());

  using namespace std::chrono;

  high_resolution_clock::time_point initTime = high_resolution_clock::now();
  high_resolution_clock::time_point curTime = initTime;
  milliseconds timeSpan = duration_cast<milliseconds>(curTime - initTime);

  int i = 0;
  while (timeSpan.count() < maxTime && (anytime || !graph.hasCompleted()))
  {
    Point randomPoint = sample(rrtmap);
    extend(randomPoint, rrtmap, graph, nearest, steer, obstacleFree, near);

    curTime = high_resolution_clock::now();
    timeSpan = duration_cast<milliseconds>(curTime - initTime);
    //std::cout << "Current time span: " << timeSpan.count() << " ms." << std::endl;

    i++;
  }

  std::vector<Graph::Vertice> vertices = graph.getVertices();
  /*
  // Print graph
  for (int i = 0; i < vertices.size(); ++i)
  {
    std::cout << "Vertice: " << i << " <- " << vertices[i].parent() << std::endl;
    std::cout << "  {" << vertices[i].point().get(0) << ", " << vertices[i].point().get(1) << "}" << std::endl;
    std::cout << "  cost: " << vertices[i].cost() << std::endl;
    std::cout << std::endl;
  }
  //
  */

  std::cout << "Iterations: " << i << std::endl;
  if (graph.hasCompleted())
  {
    std::cout << "Completed: " << graph.getLength() << std::endl;
    double minDistance = sqrt(sqrPythagoras(vertices[0].point(), vertices[graph.getFinalVertice()].point()));
    std::cout << "Ratio: " << graph.getLength() / minDistance << std::endl;
  }

  std::cout << std::endl;
}

}
