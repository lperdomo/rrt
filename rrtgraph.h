#ifndef GRAPH_H
#define GRAPH_H

#include <QPoint>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_iterator.hpp>

struct VertexElement {
  QPoint component;
};

struct EdgeElement {
  int weight;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexElement, EdgeElement> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

class RrtGraph
{
public:
    RrtGraph();
    void init(QPoint component);
    std::pair<VertexIterator, VertexIterator> getVertices();
private:
    Graph graph;
    double edges;
    double rows;
    double columns;
};

#endif // GRAPH_H
