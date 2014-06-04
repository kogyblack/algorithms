#include <iostream>

#include "basictypes.h"
#include "map.h"
#include "graph.h"
#include "plan.h"
#include "rrt.h"
#include "rrg.h"
#include "rrtstar.h"
#include "samplebiased.h"
//#include "placeholder_functions.h"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Not enough parameters! Missing map parameter." << std::endl
              << "e.g.: ./rrt.out map.txt" << std::endl;
    return -1;
  }

  Map rrtmap;
  rrtmap.loadMap(argv[1]);

  rrtbase::Graph rrtgraph;

  double maxTime = 1000.0 / 30;

  /*
  std::cout << "RRT" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrt::extend);
  std::cout << "RRT (biased 1%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrt::extend, false,
                SampleBiased(0.01));
  std::cout << "RRT (biased 5%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrt::extend, false,
                SampleBiased(0.05));

  // RRG
  //std::cout << "RRG" << std::endl;
  //rrtbase::plan(rrtmap, maxTime, rrtgraph, rrg::extend);

  // RRT*
  std::cout << "RRT*" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend);
  std::cout << "RRT* (biased 1%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend, false,
                SampleBiased(0.01));
  std::cout << "RRT* (biased 5%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend, false,
                SampleBiased(0.05));
  */

  // Anytime RRT*
  std::cout << "Anytime RRT*" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend, true);
  std::cout << "Anytime RRT* (biased 1%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend, true,
                SampleBiased(0.01));
  std::cout << "Anytime RRT* (biased 5%)" << std::endl;
  rrtbase::plan(rrtmap, maxTime, rrtgraph, rrtstar::extend, true,
                SampleBiased(0.05));

  return 0;
}
