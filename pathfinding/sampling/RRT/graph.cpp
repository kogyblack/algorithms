#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>
#include <cassert>

#include <boost/geometry.hpp>

#include "graph.h"
#include "basictypes.h"

namespace rrtbase
{

// Vertice
Graph::Vertice::Vertice() : point_(), cost_(0.0)
{}

Graph::Vertice::Vertice(Point point) : point_(point), cost_(0.0)
{}

Point& Graph::Vertice::point()
{
  return point_;
}

// Parent will work if the graph is a tree
// in this case, the graph has one and only one
// ancestor
int Graph::Vertice::parent() const
{
  if (ancestors_.size() <= 0)
    return -1;
  return ancestors_[0];
}

Point const& Graph::Vertice::point() const
{
  return point_;
}

double const& Graph::Vertice::cost() const
{
  return cost_;
}

void Graph::Vertice::addAncestor(int vertice)
{
  if (find(ancestors_.begin(), ancestors_.end(), vertice) != ancestors_.end())
    return;

  ancestors_.push_back(vertice);
}

void Graph::Vertice::removeAncestor(int vertice)
{
  auto ancestor = find(ancestors_.begin(), ancestors_.end(), vertice);
  if (ancestor != ancestors_.end())
    ancestors_.erase(ancestor);
}

void Graph::Vertice::addDescendant(int vertice)
{
  if (find(descendants_.begin(), descendants_.end(), vertice) != descendants_.end())
    return;

  descendants_.push_back(vertice);
}

void Graph::Vertice::removeDescendant(int vertice)
{
  auto descendant = find(descendants_.begin(), descendants_.end(), vertice);
  if (descendant != descendants_.end())
    descendants_.erase(descendant);
}

std::vector<int> const& Graph::Vertice::getAncestors() const
{
  return ancestors_;
}

std::vector<int> const& Graph::Vertice::getDescendants() const
{
  return descendants_;
}



// Graph
// Setters
int Graph::addVertice(Point point)
{
  Vertice newVertice(point);
  vertices_.push_back(newVertice);

  return vertices_.size() - 1;
}

void Graph::addEdge(int parent, int child)
{
  assert(parent >= 0 && parent < vertices_.size());
  assert(child >= 0 && child < vertices_.size());

  if (find(edges_.begin(), edges_.end(), Edge(parent, child)) != edges_.end())
    return;

  edges_.push_back(Edge(parent, child));
  vertices_[parent].addDescendant(child);
  vertices_[child].addAncestor(parent);
}

void Graph::removeEdge(int parent, int child)
{
  assert(parent >= 0 && parent < vertices_.size());
  assert(child >= 0 && child < vertices_.size());

  auto edge = find(edges_.begin(), edges_.end(), Edge(parent, child));
  if (edge != edges_.end())
    edges_.erase(edge);

  vertices_[parent].removeDescendant(child);
  vertices_[child].removeAncestor(parent);
}

void Graph::setCompleted(bool completed, int vertice)
{
  completed_ = completed;
  onGoalVertice_ = vertice;
}

void Graph::reset()
{
  vertices_.clear();
  edges_.clear();
  completed_ = false;
}

int Graph::updateCost(int vertice)
{
  if (vertices_.empty())
  {
    std::cerr << "Vertices vector empty!" << std::endl;
    return -1;
  }

  std::vector<int> ancestors = vertices_[vertice].ancestors_;
  if (ancestors.empty())
  {
    std::cerr << "Ancestors vector empty!" << std::endl;
    return -1;
  }

  int minAncestor;
  double minCost = std::numeric_limits<double>::max();
  for (int ancestor : ancestors)
  {
    double newCost = vertices_[ancestor].cost_ + simulateCost(vertice, ancestor);
    if (newCost < minCost)
    {
      minAncestor = ancestor;
      minCost = newCost;
    }
  }

  vertices_[vertice].cost_ = minCost;
  return minAncestor;
}

void Graph::setUniqueParent(int vertice, int parent)
{
  // TODO: Improve this function!!!
  std::vector<int> ancestors = vertices_[vertice].ancestors_;

  for (int ancestor : ancestors)
  {
    removeEdge(ancestor, vertice);
  }

  addEdge(parent, vertice);
}

// Getters
std::vector<Graph::Vertice> const& Graph::getVertices() const
{
  return vertices_;
}

std::vector<Graph::Edge> const& Graph::getEdges() const
{
  return edges_;
}

int const& Graph::getFinalVertice() const
{
  return onGoalVertice_;
}

double Graph::getLength() const
{
  if (!completed_)
    return -1.0;

  return vertices_[onGoalVertice_].cost();
}

bool const& Graph::hasCompleted() const
{
  return completed_;
}


void Graph::backtrace() const
{
  if (!completed_)
    return;

  backtrace(onGoalVertice_);
  std::cout << std::endl;
}


double const& Graph::getCost(int vertice) const
{
  return vertices_[vertice].cost_;
}

double Graph::simulateCost(int from, int to) const
{
  //return ::sqrt(sqrPythagoras(vertices_[from].point_, vertices_[to].point_));
  return boost::geometry::distance(vertices_[from].point_,
                                   vertices_[to].point_);
}

void Graph::print() const
{
  for (int i = 0; i < vertices_.size(); ++i)
  {
    std::cout << "Vertice: " << i << " <- " << vertices_[i].parent()
              << std::endl;
    std::cout << "  {" << vertices_[i].point().get<0>() << ", "
              << vertices_[i].point().get<1>() << "}" << std::endl;
    std::cout << "  cost: " << vertices_[i].cost() << std::endl;
    std::cout << std::endl;
  }
}


// Private
void Graph::backtrace(int vertice) const
{
  assert(vertice >= 0);
  assert(vertice < vertices_.size());

  if (vertices_[vertice].parent() != -1)
  {
    backtrace(vertices_[vertice].parent());
    std::cout << " -> ";
  }

  Point point = vertices_[vertice].point();
  //std::cout << "(" << point.get(0) << ", " << point.get(1) << ")";
  std::cout << "(" << point.get<0>() << ", " << point.get<1>() << ")";
}

}
