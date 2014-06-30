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

  auto initTime = high_resolution_clock::now();
  auto curTime = initTime;
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

  std::cout << "Iterations: " << i << std::endl;
  if (graph.hasCompleted())
    std::cout << "Completed: " << graph.getLength() << std::endl;
  std::cout << std::endl;
}

}
