#include <algorithm>
#include <cassert>

#include "graph.h"
#include "basictypes.h"

namespace rrtbase
{

// Vertice
//Graph::Vertice::Vertice() : point_(), parent_(nullptr), cost_(0.0)
Graph::Vertice::Vertice() : point_(), parent_(-1), cost_(0.0)
{}

Graph::Vertice::Vertice(Point point)
    //: point_(point), parent_(nullptr), cost_(0.0)
    : point_(point), parent_(-1), cost_(0.0)
{}

Point& Graph::Vertice::point()
{
  return point_;
}

/*
Graph::Vertice* Graph::Vertice::parent()
{
  return parent_;
}
*/

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
  if (find(ancestors_.begin(), ancestors_.end(), vertice) == ancestors_.end())
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
  if (find(descendants_.begin(), descendants_.end(), vertice) == descendants_.end())
    return;

  descendants_.push_back(vertice);
}

void Graph::Vertice::removeDescendant(int vertice)
{
  auto descendant = find(descendants_.begin(), descendants_.end(), vertice);
  if (descendant != descendants_.end())
    descendants_.erase(descendant);
}

/*
void Graph::Vertice::updateCost(std::vector<Vertice>& vertices)
{
  if (ancestors_.size() <= 0)
    return;

  if (vertices.size() <= 0)
    return;

  int minAncestor = 0;
  double minCost = calculateCost(0, vertices);
  for (int i = 1; i < ancestors_.size(); ++i)
  {
    double newCost = calculateCost(i, vertices);
    if (newCost < minCost)
    {
      minAncestor = i;
      minCost = newCost;
    }
  }

  parent_ = &vertices[ancestors_[minAncestor]];
  cost_ = minCost;
}
*/

std::vector<int> const& Graph::Vertice::getAncestors() const
{
  return ancestors_;
}

std::vector<int> const& Graph::Vertice::getDescendants() const
{
  return descendants_;
}

/*
double Graph::Vertice::calculateCost(int ancestor, std::vector<Vertice> const& vertices) const
{
  Graph::Vertice vert = vertices[ancestors_[ancestor]];
  return vert.cost() + sqrPythagoras(vert.point(), point_);
}
*/


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

  if (find(edges_.begin(), edges_.end(), Edge(parent, child)) == edges_.end())
    return;

  edges_.push_back(Edge(parent, child));
  vertices_[parent].addDescendant(child);
  vertices_[child].addAncestor(parent);
  //vertices_[child].updateCost(vertices_);
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
  //vertices_[child].updateCost(vertices_);
}

void Graph::setCompleted(bool completed)
{
  completed_ = completed;
}

void Graph::reset()
{
  vertices_.clear();
  edges_.clear();
  completed_ = false;
}

void Graph::updateCost(int vertice)
{
  if (vertices_.size() <= 0)
    return;

  Vertice* vert = &vertices_[vertice];
  std::vector<int> ancestors = vert->ancestors_;
  if (ancestors.size() <= 0)
    return;

  int minAncestor = 0;
  //double minCost = calculateCost(0, vertices);
  double minCost = simulateCost(vertice,
                                ancestors[0]);
  for (int i = 1; i < vert->ancestors_.size(); ++i)
  {
    //double newCost = calculateCost(i, vertices);
    double newCost = simulateCost(vertice,
                                  ancestors[i]);
    if (newCost < minCost)
    {
      minAncestor = i;
      minCost = newCost;
    }
  }

  //vertices_[vertice].parent_ = &vertices_[ancestors[minAncestor]];
  vertices_[vertice].parent_ = ancestors[minAncestor];
  vertices_[vertice].cost_ = minCost;
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

Graph::Vertice* Graph::getMinimum() const
{
  return minimum_;
}

bool Graph::hasCompleted() const
{
  return completed_;
}

double const& Graph::getCost(int vertice) const
{
  return vertices_[vertice].cost_;
}

double Graph::simulateCost(int from, int to) const
{
  return sqrPythagoras(vertices_[from].point_, vertices_[to].point_);
}

}
