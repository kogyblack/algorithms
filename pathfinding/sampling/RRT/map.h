#ifndef RRT_MAP_H
#define RRT_MAP_H

#include "boostaliases.h"

class Map
{
public:
  // Setters
  void loadMap(std::string filename);

  // Getters
  Point getSize() const;
  Point getInitialPoint() const;
  Rect  getGoalRect() const;
  std::vector<Polygon> getPolygons() const;

private:
  Point size_;
  Point initial_point_;
  Rect  goal_;
  std::vector<Polygon> polygons_;
};

#endif
