#ifndef RRT_MAP_H
#define RRT_MAP_H

#include <string>

#include "basictypes.h"

class Map
{
public:
  // Constructor
  Map();

  // Setters
  void loadMap(std::string filename);

  // Getters
  Point const& getSize() const;
  Point const& getInitialPoint() const;
  Rect const&  getGoalRect() const;
  std::vector<Polygon> const& getPolygons() const;
  //double getMaxTime() const;
  void print() const;

  // Setters
  void setSize(Point size);
  void setInitialPoint(Point initialPoint);
  void setGoalRect(Rect goal);

private:
  Point size_;
  Point initialPoint_;
  Rect  goal_;
  std::vector<Polygon> polygons_;

  //double maxTime_;
};

#endif
