#ifndef RRT_PLAN_H
#define RRT_PLAN_H

#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>

//#include "placeholder_functions.h"
#include "default_functions.h"
#include "generator.h"
#include "basictypes.h"
#include "map.h"
#include "graph.h"

namespace rrtbase
{

template <typename Extend,
          typename Sample       = Point (*)(Map const&),
          typename Nearest      = int   (*)(Graph const&, Point const&),
          typename Steer        = Point (*)(Point const&, Point const&, double),
          typename ObstacleFree = bool  (*)(Map const&, Point const&, Point const&),
          typename Near         = std::vector<int> (*)(Graph const&, int, double)>
void plan(Map const& rrtmap,
          double maxTime,
          Graph& graph,
          Extend extend,
          bool anytime = false,
          Sample sample = default_functions::sample,
          Nearest nearest = default_functions::nearest,
          Steer steer = default_functions::steer,
          ObstacleFree obstacleFree = default_functions::obstacleFree,
          Near near = default_functions::near)
{
  //std::cout << "Initiating planning!" << std::endl;

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

#endif
