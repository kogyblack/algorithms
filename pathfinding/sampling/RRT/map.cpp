#include <iostream>
#include "map.h"

// Setters
void Map::loadMap(std::string mapname)
{
  std::cout << "Loading map!" << std::endl;
}

// Getters
Point const& Map::getSize() const
{
  return size_;
}

Point const& Map::getInitialPoint() const
{
  return initialPoint_;
}

Rect const& Map::getGoalRect() const
{
  return goal_;
}

std::vector<Polygon> const& Map::getPolygons() const
{
  return polygons_;
}

// Setters
void Map::setSize(Point size)
{
  size_ = size;
}

void Map::setInitialPoint(Point initialPoint)
{
  initialPoint_ = initialPoint;
}

void Map::setGoalRect(Rect goal)
{
  goal_ = goal;
}
