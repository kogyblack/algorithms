#ifndef RRT_BOOSTALIASES_H
#define RRT_BOOSTALIASES_H

#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/box.hpp>

// Typedefs for boost
typedef boost::geometry::model::d2::point_xy<double>       Point;
typedef boost::geometry::model::box<Point>                 Rect;
typedef boost::geometry::model::polygon<Point, true, true> Polygon;
typedef boost::geometry::model::segment<Point>            Segment;

#endif
