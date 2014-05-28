#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>

#include "generator.h"
#include "basictypes.h"
#include "map.h"
#include "graph.h"

namespace rrtbase
{

template <typename Extend,
          typename Sample,
          typename Nearest,
          typename Steer,
          typename ObstacleFree,
          typename Near>
void plan(Map const& rrtmap,
          double maxTime,
          Graph& graph,
          Extend extend,
          bool anytime,
          Sample sample,
          Nearest nearest,
          Steer steer,
          ObstacleFree obstacleFree,
          Near near)
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

    i++;
  }

  std::vector<Graph::Vertice> vertices = graph.getVertices();
  /*
  // Print graph
  for (int i = 0; i < vertices.size(); ++i)
  {
    std::cout << "Vertice: " << i << " <- " << vertices[i].parent()
              << std::endl;
    std::cout << "  {" << vertices[i].point().get(0) << ", "
              << vertices[i].point().get(1) << "}" << std::endl;
    std::cout << "  cost: " << vertices[i].cost() << std::endl;
    std::cout << std::endl;
  }
  //
  */

  std::cout << "Iterations: " << i << std::endl;
  if (graph.hasCompleted())
  {
    std::cout << "Completed: " << graph.getLength() << std::endl;
    //int finalVertice = graph.getFinalVertice();
    //double minDistance = sqrt(sqrPythagoras(vertices[0].point(),
    //                                        vertices[finalVertice].point()));
    //std::cout << "Ratio: " << graph.getLength() / minDistance << std::endl;
    graph.backtrace();
  }

  std::cout << std::endl;
}

}
