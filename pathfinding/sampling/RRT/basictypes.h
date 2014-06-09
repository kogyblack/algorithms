#ifndef RRT_BASICTYPES_H
#define RRT_BASICTYPES_H

//#include <vector>
//#include <cmath>
//#include <cassert>

#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/box.hpp>

// Boost
typedef boost::geometry::model::d2::point_xy<double>       Point;
typedef boost::geometry::model::box<Point>                 Rect;
typedef boost::geometry::model::polygon<Point, true, true> Polygon;
typedef boost::geometry::model::segment<Point>             Segment;

namespace rrtbase
{

extern const double resolution;

}

#endif
