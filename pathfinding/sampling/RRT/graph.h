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
    //Vertice* parent();

    Point const& point() const;
    double const& cost() const;
  private:
    void addAncestor(int);
    void removeAncestor(int);
    void addDescendant(int);
    void removeDescendant(int);
    //void updateCost(std::vector<Vertice>&);

    std::vector<int> const& getAncestors() const;
    std::vector<int> const& getDescendants() const;
    //double calculateCost(int, std::vector<Vertice> const&) const;

    Point point_;
    //Vertice* parent_;
    int parent_;
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
  void setCompleted(bool completed);
  void reset();

  void updateCost(int vertice);

  // Getters
  std::vector<Vertice> const& getVertices() const;
  std::vector<Edge> const& getEdges() const;
  Vertice* getMinimum() const;
  bool hasCompleted() const;

  double const& getCost(int vertice) const;
  double simulateCost(int from, int to) const;

private:
  std::vector<Vertice> vertices_;
  std::vector<Edge> edges_;
  Vertice* minimum_;
  bool completed_;
};

}

#endif
