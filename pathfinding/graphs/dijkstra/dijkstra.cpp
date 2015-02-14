#include <iostream>
#include <stack>
#include <vector>
#include <cmath>

struct Node
{
  int x, y;
  float value;
  int previous;
  bool isVerified;
};

// TODO(naum): template with "constant" size to remove dyn arrays(?)
struct Graph
{
  std::vector<Node> vertices;
  std::vector< std::vector<int> > edges;

  int addNode(Node node)
  {
    vertices.push_back(node);
    edges.push_back(std::vector<int>());
    return vertices.size() - 1;
  }

  void addNeighbour(int source, int dest)
  {
    // NOTE(naum): Not verifying repetitions
    edges[source].push_back(dest);
  }

  void print() const
  {
    for (unsigned int i = 0; i < vertices.size(); ++i)
      std::cout << i << ": (" <<
        vertices[i].x << ", " <<
        vertices[i].y << "): " <<
        vertices[i].value << " -> " <<
        vertices[i].previous << std::endl;
  }
};

float nodeDistance(const Node& source, const Node& dest)
{
  int dx = source.x - dest.x,
      dy = source.y - dest.y;

  return std::sqrt(dx * dx + dy * dy);
}

void Dijkstra(Graph& graph, int sourceNode)
{
  // Path stack (using depth first. To use breadth first use queue)
  std::stack<int> pathStack;

  // Initialization
  for (unsigned int i = 0; i < graph.vertices.size(); ++i)
  {
    graph.vertices[i].value = -1.0f;
    graph.vertices[i].isVerified = false;
  }
  graph.vertices[sourceNode].value = 0.0f;
  graph.vertices[sourceNode].previous = -1;

  // Begin the stack
  pathStack.push(sourceNode);

  while (!pathStack.empty())
  {
    int currentIndex = pathStack.top();
    pathStack.pop();

    Node& currentNode = graph.vertices[currentIndex];

    for (unsigned int i = 0; i < graph.edges[currentIndex].size(); ++i)
    {
      int neighbourIndex = graph.edges[currentIndex][i];
      Node& neighbourNode = graph.vertices[neighbourIndex];

      float newValue = currentNode.value +
                       nodeDistance(currentNode,
                                    neighbourNode);

      // Add to stack if not verified
      if (!neighbourNode.isVerified)
        pathStack.push(neighbourIndex);

      // Update node if the new path is better
      if (neighbourNode.value < 0.0f || newValue < neighbourNode.value)
      {
        neighbourNode.value = newValue;
        neighbourNode.previous = currentIndex;
      }

      // Mark the node as verified
      neighbourNode.isVerified = true;
    }
  }
}

int main()
{
  Graph graph;
  Node node;

  // Get vertices
  int n;
  std::cin >> n;
  for(int i = 0; i < n; ++i)
  {
    std::cin >> node.x >> node.y;
    graph.addNode(node);
  }

  // Get edges
  std::cin >> n;
  for (int i = 0; i < n; ++i)
  {
    int source, dest;
    std::cin >> source >> dest;
    graph.addNeighbour(source, dest);
  }

  Dijkstra(graph, 0);

  graph.print();

  return 0;
}
