#ifndef RRT_BASICTYPES_H
#define RRT_BASICTYPES_H

#include <vector>
//#include <cmath>
//#include <cassert>

/*
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/box.hpp>

// Boost
typedef boost::geometry::model::d2::point_xy<double>       Point;
typedef boost::geometry::model::box<Point>                 Rect;
typedef boost::geometry::model::polygon<Point, true, true> Polygon;
typedef boost::geometry::model::segment<Point>             Segment;
*/

namespace rrtbase
{

const double resolution = 0.1;

}

// Since Boost is causing issues, the classes will be created
class Point
{
public:
  // Constructor
  Point();
  Point(double x, double y);

  // Setters
  template<std::size_t K>
  void set(double const& value);

  // Getters
  //template<std::size_t K>
  //double const& get() const;

  double const& get(int dim) const;

  bool operator==(Point);

private:
  double coord_[2];
};



class Rect
{
public:
  // Constructor
  Rect();
  Rect(Point const& min_corner, Point const& max_corner);

  // Setters
  Point& min_corner();
  Point& max_corner();

  // Getters
  Point const& min_corner() const;
  Point const& max_corner() const;

private:
  Point min_corner_,
        max_corner_;
};


// Not equal to boost's polygon!
// Closed polygon!
class Polygon
{
public:
  // Typedef
  typedef std::vector<Point> Ring;

  // Setters
  Ring& outer();

  // Getters
  Ring const& outer() const;

private:
  Ring outer_;
};



class Segment
{
public:
  // Constructors
  Segment();
  Segment(Point const& from, Point const& to);

  // Setters
  Point& from();
  Point& to();

  // Getters
  Point const& from() const;
  Point const& to() const;

private:
  Point from_, to_;
};

// Functions
// Same name as boost functions
//Point subtract_point(Point const& a, Point const& b);
bool intersects(Segment const& s, Polygon const& p);
bool pointInsideRect(Point const&, Rect const&);

// Since boost's distance isn't working to Points,
// lets create a pythagoras function
double sqrPythagoras(Point const& a, Point const& b);

#endif
