#ifndef RRT_GRAPH_H
#define RRT_GRAPH_H

#include "basictypes.h"

namespace rrtbase
{

class Graph
{
public:
  // Structures
  struct Vertice
  {
    Point point;
    float cost;
  };

  // Typedef
  typedef std::pair<int, int>  Edge;
  typedef std::vector<Vertice> Vertices;
  typedef std::vector<Edge>    Edges;

  // Setters
  void addVertice(Vertice vertice);
  void addEdge(int v1, int v2);
  void setCompleted(bool completed);

  // Getters
  std::vector<Vertice> getVertices() const;
  std::vector<Edge> getEdges() const;
  Vertice* getMinimum() const;
  bool hasCompleted() const;

private:
  Vertices vertices_;
  Edges edges_;
  Vertice* minimum_;
  bool completed_;
};

}

#endif
