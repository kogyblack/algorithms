#ifndef RRG_H
#define RRG_H

#include <vector>

namespace rrtbase
{
class Graph;
}

class Point;
class Map;

namespace rrg
{

void extend(Point const& to,
            Map const& rrtmap,
            rrtbase::Graph& graph,
            int (*nearest)(rrtbase::Graph const&, Point const&),
            Point (*steer)(Point const&, Point const&, double),
            bool (*obstacleFree)(Map const&, Point const&, Point const&),
            std::vector<int> (*near)(rrtbase::Graph const&, int, double));

}

#endif
