#include "rrtgraph.h"

RrtGraph::RrtGraph()
{
}

void RrtGraph::init(QPoint component)
{
    Vertex vertex = boost::add_vertex(graph);
    graph[vertex].component = component;
}

std::pair<VertexIterator, VertexIterator> RrtGraph::getVertices()
{
    return vertices(graph);
}
