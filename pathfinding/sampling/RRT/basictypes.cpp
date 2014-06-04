#include <cmath>
#include <cassert>

#include "basictypes.h"

/*
// Constructor
// Point
Point::Point() : coord_{0.0, 0.0} {}
Point::Point(double x, double y) : coord_{x, y} {}

// Setters
template<std::size_t K>
void Point::set(double const& value)
{
  assert(K < 2);
  coord_[K] = value;
}

// Getters
//
template<std::size_t K>
double const& Point::get() const
{
  assert(K < 2);
  return coord_[K];
}
//

double const& Point::get(int K) const
{
  assert(K < 2);
  return coord_[K];
}

bool Point::operator==(Point point)
{
  //if (this->get<0>() == point.get<0>() &&
  //    this->get<1>() == point.get<1>())
  if (this->get(0) == point.get(0) &&
      this->get(1) == point.get(1))
    return true;
  return false;
}


// Rect
// Constructor
Rect::Rect() =default;
Rect::Rect(Point min_corner, Point max_corner)
    : min_corner_(min_corner), max_corner_(max_corner) {}

// Setters
Point& Rect::min_corner()
{
  return min_corner_;
}

Point& Rect::max_corner()
{
  return max_corner_;
}

// Getters
Point const& Rect::min_corner() const
{
  return min_corner_;
}

Point const& Rect::max_corner() const
{
  return max_corner_;
}


// Not equal to boost's polygon!
// Closed polygon!
// Setters
Polygon::Ring& Polygon::outer()
{
  return outer_;
}

// Getters
Polygon::Ring const& Polygon::outer() const
{
  return outer_;
}


// Segment
// Constructors
Segment::Segment() =default;
Segment::Segment(Point const& from, Point const& to) : from_(from), to_(to) {}

// Setters
Point& Segment::from()
{
  return from_;
}

Point& Segment::to()
{
  return to_;
}

// Getters
Point const& Segment::from() const
{
  return from_;
}

Point const& Segment::to() const
{
  return to_;
}


// Functions
// Same name as boost functions
//
Point subtract_point(Point const& a, Point const& b)
{
  Point sub(a.get<0>() - b.get<0>(), a.get<1>() - b.get<1>());
  return sub;
}
//

bool intersects(Segment const& s, Polygon const& p)
{
  assert(p.outer().size() > 1);

  //
  double aseg = s.to().get<1>() - s.from().get<1>(),
         bseg = s.from().get<0>() - s.to().get<0>(),
         xmseg = (s.to().get<0>() + s.from().get<0>()) / 2.0,
         ymseg = (s.to().get<1>() + s.from().get<1>()) / 2.0;
  //
  double aseg = s.to().get(1) - s.from().get(1),
         bseg = s.from().get(0) - s.to().get(0),
         xmseg = (s.to().get(0) + s.from().get(0)) / 2.0,
         ymseg = (s.to().get(1) + s.from().get(1)) / 2.0;

  Polygon::Ring ring = p.outer();
  for (int i = 1; i <= ring.size(); ++i)
  {
    Point p1 = ring[i % ring.size()],
          p0 = ring[i-1];

    bool cross0 = false,
         cross1 = false;

    // See if both points p0 and p1 are on different sides using the line segment
    //
    if (std::signbit(aseg * (p1.get<0>() - xmseg) + bseg * (p1.get<1>() - ymseg)) !=
        std::signbit(aseg * (p0.get<0>() - xmseg) + bseg * (p0.get<1>() - ymseg)))
    //
    if (std::signbit(aseg * (p1.get(0) - xmseg) + bseg * (p1.get(1) - ymseg)) !=
        std::signbit(aseg * (p0.get(0) - xmseg) + bseg * (p0.get(1) - ymseg)))
      cross0 = true;

    //
    double a = p1.get<1>() - p0.get<1>(),
           b = p0.get<0>() - p1.get<0>(),
           xm = (p1.get<0>() + p0.get<0>()) / 2.0,
           ym = (p1.get<1>() + p0.get<1>()) / 2.0;
    //
    double a = p1.get(1) - p0.get(1),
           b = p0.get(0) - p1.get(0),
           xm = (p1.get(0) + p0.get(0)) / 2.0,
           ym = (p1.get(1) + p0.get(1)) / 2.0;

    // See if both point of the segment are on different sides of the line p1-p0
    //
    if (std::signbit(a * (s.to().get<0>() - xm) + b * (s.to().get<1>() - ym)) !=
        std::signbit(a * (s.from().get<0>() - xm) + b * (s.from().get<1>() - ym)))
    //
    if (std::signbit(a * (s.to().get(0) - xm) + b * (s.to().get(1) - ym)) !=
        std::signbit(a * (s.from().get(0) - xm) + b * (s.from().get(1) - ym)))
      cross1 = true;

    // If both cross, the lines intersects
    if (cross0 == true && cross1 == true)
      return true;
  }

  return false;
}

bool pointInsideRect(Point const& point, Rect const& rect)
{
  //
  bool xInside = point.get<0>() >= rect.min_corner().get<0>() &&
                 point.get<0>() <= rect.max_corner().get<0>();
  bool yInside = point.get<1>() >= rect.min_corner().get<1>() &&
                 point.get<1>() <= rect.max_corner().get<1>();
  //
  bool xInside = point.get(0) >= rect.min_corner().get(0) &&
                 point.get(0) <= rect.max_corner().get(0);
  bool yInside = point.get(1) >= rect.min_corner().get(1) &&
                 point.get(1) <= rect.max_corner().get(1);
  if (xInside && yInside)
    return true;
  
  return false;
}


// Since boost's distance isn't working to Points,
// lets create a pythagoras function
double sqrPythagoras(Point const& a, Point const& b)
{
  //
  double x = a.get<0>() - b.get<0>(),
         y = a.get<1>() - b.get<1>();
  //
  double x = a.get(0) - b.get(0),
         y = a.get(1) - b.get(1);
  return (x * x) + (y * y);
}

*/
