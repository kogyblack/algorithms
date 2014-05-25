#include <iostream>

#include "basictypes.h"
#include "rrt.h"
#include "rrg.h"
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

  rrtbase::plan(rrtmap, 16.66, rrtgraph, rrt::extend);
  rrtbase::plan(rrtmap, 1000.0 / 60.0, rrtgraph, rrg::extend);

  return 0;
}
