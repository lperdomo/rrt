#ifndef GRAPH_H
#define GRAPH_H

#include <QPoint>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>

struct VertexElement {
  QPoint value;
};

struct EdgeElement {
  int value;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexElement, EdgeElement> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;


class RrtGraph
{
public:
    RrtGraph();
    void init(QPoint value);
    std::pair<VertexIterator, VertexIterator> getVertices();
    std::pair<EdgeIterator, EdgeIterator> getEdges();
    QPoint vertexAt(Vertex v);
    Vertex addVertex(QPoint value);
    Edge addEdge(Vertex v, Vertex u);
    QPoint edgeSource(EdgeIterator edge);
    QPoint edgeTarget(EdgeIterator edge);
    void debug();
private:
    Graph graph;
};

#endif // GRAPH_H
