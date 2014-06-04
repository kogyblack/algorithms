#include <iostream>
#include <fstream>
#include "map.h"

Map::Map() : size_{1,1}, initialPoint_{0,0}, goal_{{1,1},{1,1}}
{}

// Setters
void Map::loadMap(std::string filename)
{
  std::cout << "Loading map!" << std::endl;
  std::ifstream file;

  file.open(filename);

  //file >> maxTime_;

  double sizeX, sizeY;
  file >> sizeX >> sizeY;
  size_ = Point(sizeX, sizeY);

  double initX, initY;
  file >> initX >> initY;
  initialPoint_ = Point(initX, initY);

  double goalX, goalY;
  file >> goalX >> goalY;
  Point goalPoint(goalX, goalY);
  goal_ = Rect(goalPoint, goalPoint);

  polygons_.clear();
  int nPolygons;
  file >> nPolygons;

  for (int i = 0; i < nPolygons; ++i)
  {
    Polygon polygon;

    int nVertices;
    file >> nVertices;

    for (int j = 0; j < nVertices; ++j)
    {
      double posX, posY;
      file >> posX >> posY;
      polygon.outer().push_back(Point(posX, posY));
    }

    // Close polygon
    polygon.outer().push_back(polygon.outer()[0]);

    polygons_.push_back(polygon);
  }

  file.close();
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

/*
double Map::getMaxTime() const
{
  return maxTime_;
}
*/

void Map::print() const
{
  // print map
  /*
  std::cout << "Size: " << size_.get(0) << " " << size_.get(1) << std::endl;
  std::cout << "Initial: " << initialPoint_.get(0) << " "
            << initialPoint_.get(1) << std::endl;
  std::cout << "Goal: " << goal_.min_corner().get(0) << " "
            << goal_.min_corner().get(1) << std::endl;
  std::cout << "Number of polygons: " << polygons_.size() << std::endl;
  */
  std::cout << "Size: " << size_.get<0>() << " " << size_.get<1>() << std::endl;
  std::cout << "Initial: " << initialPoint_.get<0>() << " "
            << initialPoint_.get<1>() << std::endl;
  std::cout << "Goal: " << goal_.min_corner().get<0>() << " "
            << goal_.min_corner().get<1>() << std::endl;
  std::cout << "Number of polygons: " << polygons_.size() << std::endl;

  for (int i = 0; i < polygons_.size(); ++i)
  {
    std::cout << "Polygon " << i << ": " << polygons_[i].outer().size()
              << " vertices" << std::endl;
  }
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
