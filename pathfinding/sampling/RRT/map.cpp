#include <iostream>
#include "map.h"

// Setters
void Map::loadMap(std::string mapname)
{
  std::cout << "Loading map!" << std::endl;
}

// Getters
Point Map::getSize() const
{
  return size_;
}

Point Map::getInitialPoint() const
{
  return initial_point_;
}

Rect Map::getGoalRect() const
{
  return goal_;
}

std::vector<Polygon> Map::getPolygons() const
{
  return polygons_;
}
