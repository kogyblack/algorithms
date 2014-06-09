#ifndef RRT_GRAPH_H
#define RRT_GRAPH_H

#include "basictypes.h"

namespace rrtbase
{

class Graph;

class Graph
{
public:
  class Vertice;
  class Vertice
  {
    friend class Graph;
  public:
    Vertice();
    Vertice(Point);

    Point& point();

    int parent() const;
    Point const& point() const;
    double const& cost() const;
  private:
    void addAncestor(int);
    void removeAncestor(int);

    void addDescendant(int);
    void removeDescendant(int);

    std::vector<int> const& getAncestors() const;
    std::vector<int> const& getDescendants() const;

    Point point_;
    std::vector<int> descendants_;
    std::vector<int> ancestors_;
    double cost_;
  };

  // Typedef
  typedef std::pair<int, int>  Edge;

  // Setters
  int addVertice(Point point);
  //void removeVertice(int vertice);
  void addEdge(int parent, int child);
  void removeEdge(int parent, int child);
  void setCompleted(bool completed, int vertice);
  void reset();

  int updateCost(int vertice);

  void setUniqueParent(int vertice, int parent);

  // Getters
  std::vector<Vertice> const& getVertices() const;
  std::vector<Edge> const& getEdges() const;
  int const& getFinalVertice() const;
  double getLength() const;
  bool const& hasCompleted() const;

  void backtrace() const;

  double const& getCost(int vertice) const;
  double simulateCost(int from, int to) const;

  void print() const;

private:
  void backtrace(int vertice) const;

  std::vector<Vertice> vertices_;
  std::vector<Edge> edges_;
  int onGoalVertice_;
  bool completed_;
};

}

#endif
