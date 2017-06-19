#ifndef GRAPH_H
#define GRAPH_H

#include <QPoint>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>

class Graph
{
public:
    Graph();
    struct VertexElement {
      QPoint value;
    };

    struct EdgeElement {
      int value;
    };

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexElement, EdgeElement> BGraph;
    typedef boost::graph_traits<BGraph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<BGraph>::vertex_iterator VertexIterator;
    typedef boost::graph_traits<BGraph>::edge_descriptor Edge;
    typedef boost::graph_traits<BGraph>::edge_iterator EdgeIterator;
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
    BGraph graph;
};

#endif // GRAPH_H
