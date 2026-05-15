#include "graph.hpp"

namespace ulanova
{
  Edge::Edge():
    vertex(),
    weight(0)
  {}

  Edge::Edge(const std::string& vertexName, unsigned edgeWeight):
    vertex(vertexName),
    weight(edgeWeight)
  {}

  bool Edge::operator==(const Edge& rhs) const
  {
    return vertex == rhs.vertex && weight == rhs.weight;
  }

  Graph::Graph():
    name_(),
    vertices_(),
    outbound_(),
    inbound_()
  {}

  Graph::Graph(const std::string& name):
    name_(name),
    vertices_(),
    outbound_(),
    inbound_()
  {}

  const std::string& Graph::getName() const noexcept
  {
    return name_;
  }

  bool Graph::hasVertex(const std::string& vertex) const
  {
    return vertices_.has(vertex);
  }

  void Graph::addVertex(const std::string& vertex)
  {
    if (!vertices_.has(vertex))
    {
      vertices_.add(vertex, true);
      outbound_.add(vertex, Vector<Edge>());
      inbound_.add(vertex, Vector<Edge>());
    }
  }

  bool Graph::hasEdge(const std::string& from, const std::string& to, unsigned weight) const
  {
    const Vector<Edge>* edges = outbound_.find(from);

    if (edges == nullptr)
    {
      return false;
    }

    for (auto it = edges->begin(); it != edges->end(); ++it)
    {
      if (it->vertex == to && it->weight == weight)
      {
        return true;
      }
    }

    return false;
  }

  void Graph::addEdge(const std::string& from, const std::string& to, unsigned weight)
  {
    addVertex(from);
    addVertex(to);

    Vector<Edge>* outEdges = outbound_.find(from);
    Vector<Edge>* inEdges = inbound_.find(to);

    outEdges->push_back(Edge(to, weight));
    inEdges->push_back(Edge(from, weight));
  }

  bool Graph::removeEdge(const std::string& from, const std::string& to, unsigned weight)
  {
    Vector<Edge>* outEdges = outbound_.find(from);
    Vector<Edge>* inEdges = inbound_.find(to);

    if (outEdges == nullptr || inEdges == nullptr)
    {
      return false;
    }

    bool removedOut = false;

    for (size_t i = 0; i < outEdges->getsize(); ++i)
    {
      if ((*outEdges)[i].vertex == to && (*outEdges)[i].weight == weight)
      {
        outEdges->erase(i);
        removedOut = true;
        break;
      }
    }

    if (!removedOut)
    {
      return false;
    }

    for (size_t i = 0; i < inEdges->getsize(); ++i)
    {
      if ((*inEdges)[i].vertex == from && (*inEdges)[i].weight == weight)
      {
        inEdges->erase(i);
        return true;
      }
    }

    return true;
  }

  Vector<std::string> Graph::getVertices() const
  {
    Vector<std::string> result;

    for (auto it = vertices_.cbegin(); it != vertices_.cend(); ++it)
    {
      result.push_back(it.key());
    }

    return result;
  }

  Vector<Edge> Graph::getOutbound(const std::string& vertex) const
  {
    const Vector<Edge>* edges = outbound_.find(vertex);

    if (edges == nullptr)
    {
      return Vector<Edge>();
    }

    return *edges;
  }

  Vector<Edge> Graph::getInbound(const std::string& vertex) const
  {
    const Vector<Edge>* edges = inbound_.find(vertex);

    if (edges == nullptr)
    {
      return Vector<Edge>();
    }

    return *edges;
  }
}
