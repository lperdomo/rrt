#ifndef GRAPH_H
#define GRAPH_H

#include <QVector2D>
#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>

class Graph
{
public:
    Graph();
    struct VertexElement {
        QVector2D value;

    };

    struct EdgeElement {
        int value;
    };

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexElement, EdgeElement> BGraph;
    typedef boost::graph_traits<BGraph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<BGraph>::vertex_iterator VertexIterator;
    typedef boost::graph_traits<BGraph>::edge_descriptor Edge;
    typedef boost::graph_traits<BGraph>::edge_iterator EdgeIterator;
    void init(QVector2D value);
    std::pair<VertexIterator, VertexIterator> getVertices();
    std::pair<EdgeIterator, EdgeIterator> getEdges();
    QVector2D vertexAt(Vertex v);
    Vertex addVertex(QVector2D value);
    Edge addEdge(Vertex v, Vertex u);
    QVector2D edgeSource(EdgeIterator edge);
    QVector2D edgeTarget(EdgeIterator edge);
    Vertex parent(Vertex child);
    Vertex getLast();
    void debug();
private:
    BGraph graph;
    std::map<Vertex, Vertex> parents;
    Vertex last;
};

#endif // GRAPH_H
