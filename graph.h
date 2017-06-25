#ifndef GRAPH_H
#define GRAPH_H

#include <map>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>

#include "state.h"

class Graph
{
public:
    Graph();
    struct VertexElement {
        State value;

    };

    struct EdgeElement {
        int value;
    };

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexElement, EdgeElement> BGraph;
    typedef boost::graph_traits<BGraph>::vertex_descriptor Vertex;
    typedef boost::graph_traits<BGraph>::vertex_iterator VertexIterator;
    typedef boost::graph_traits<BGraph>::edge_descriptor Edge;
    typedef boost::graph_traits<BGraph>::edge_iterator EdgeIterator;
    void init(State value);
    void clear();
    std::pair<VertexIterator, VertexIterator> getVertices();
    std::pair<EdgeIterator, EdgeIterator> getEdges();
    State vertexAt(Vertex v);
    Vertex addVertex(State value);
    Edge addEdge(Vertex v, Vertex u);
    State edgeSource(EdgeIterator edge);
    State edgeTarget(EdgeIterator edge);
    Vertex parent(Vertex child);
    Vertex getFirst();
    Vertex getLast();
    int size();
    void debug();
private:
    BGraph graph;
    std::map<Vertex, Vertex> parents;
    Vertex first;
    Vertex last;
};

#endif // GRAPH_H
