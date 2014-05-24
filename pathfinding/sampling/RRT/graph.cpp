#include <cassert>

#include "graph.h"

namespace rrtbase
{

// Setters
void Graph::addVertice(Vertice vertice)
{
  vertices_.push_back(vertice);
}

void Graph::addEdge(int v1, int v2)
{
  edges_.push_back(Edge(v1, v2));
}

void Graph::setCompleted(bool completed)
{
  completed_ = completed;
}

// Getters
std::vector<Graph::Vertice> Graph::getVertices() const
{
  return vertices_;
}

std::vector<Graph::Edge> Graph::getEdges() const
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

}
