#include <iostream>

#include "basictypes.h"
#include "rrt.h"
#include "rrg.h"
#include "rrtstar.h"
#include "plan.h"
#include "graph.h"
#include "map.h"

int main()
{
  Map rrtmap;
  rrtmap.setSize(Point(10, 10));
  rrtmap.setInitialPoint({0.5, 0.5});
  rrtmap.setGoalRect({{9.5, 9.5}, {10, 10}});

  rrtbase::Graph rrtgraph;

  double maxTime = 1000.0 / 10;

  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrt::extend);           // RRT
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrg::extend);           // RRG
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend);       // RRT*
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend, true); // Anytime RRT*

  return 0;
}
