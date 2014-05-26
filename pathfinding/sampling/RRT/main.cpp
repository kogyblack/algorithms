#include <iostream>

#include "basictypes.h"
#include "rrt.h"
#include "rrg.h"
#include "rrtstar.h"
#include "plan.h"
#include "graph.h"
#include "map.h"

#include "samplebiased.h"

int main(int argc, char** argv)
{
  Map rrtmap;
  rrtmap.setSize(Point(10, 10));
  rrtmap.setInitialPoint({0.5, 0.5});
  rrtmap.setGoalRect({{9.5, 9.5}, {10, 10}});

  rrtbase::Graph rrtgraph;

  double maxTime = 1000.0 / 60;


  std::cout << "RRT" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrt::extend);           // RRT
  std::cout << "RRT (biased 1%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrt::extend, false, SampleBiased(0.01));           // RRT
  std::cout << "RRT (biased 5%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrt::extend, false, SampleBiased(0.05));           // RRT

  //std::cout << "RRG" << std::endl;
  //rrtbase::plan(rrtmap, maxTime, rrtgraph, rrg::extend);           // RRG

  std::cout << "RRT*" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend);       // RRT*
  std::cout << "RRT* (biased 1%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend, false, SampleBiased(0.01));       // RRT*
  std::cout << "RRT* (biased 5%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend, false, SampleBiased(0.05));       // RRT*


  std::cout << "Anytime RRT*" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend, true); // Anytime RRT*
  std::cout << "Anytime RRT* (biased 1%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend, true, SampleBiased(0.01));           // RRT
  std::cout << "Anytime RRT* (biased 5%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend, true, SampleBiased(0.05));           // RRT

  return 0;
}
