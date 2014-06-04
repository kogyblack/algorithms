#ifndef RRT_PLAN_H
#define RRT_PLAN_H

#include <vector>

//#include "placeholder_functions.h"
#include "default_functions.h"

#include "basictypes.h"

class Map;
class Graph;
//class Point;

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
          bool anytime              = false,
          Sample sample             = default_functions::sample,
          Nearest nearest           = default_functions::nearest,
          Steer steer               = default_functions::steer,
          ObstacleFree obstacleFree = default_functions::obstacleFree,
          Near near                 = default_functions::near);

}

#include "plan.cpp"

#endif
