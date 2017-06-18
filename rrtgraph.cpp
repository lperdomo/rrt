#include "rrtgraph.h"

#include <iostream>

RrtGraph::RrtGraph()
{
}

void RrtGraph::init(QPoint value)
{
    graph.clear();
    Vertex vertex = boost::add_vertex(graph);
    graph[vertex].value = value;
}

std::pair<VertexIterator, VertexIterator> RrtGraph::getVertices()
{
    return boost::vertices(graph);
}

std::pair<EdgeIterator, EdgeIterator> RrtGraph::getEdges()
{
    return boost::edges(graph);
}

QPoint RrtGraph::vertexAt(Vertex vertex)
{
    return graph[vertex].value;
}

QPoint RrtGraph::edgeSource(EdgeIterator edge)
{
    return graph[boost::source(*edge, graph)].value;
}

QPoint RrtGraph::edgeTarget(EdgeIterator edge)
{
    return graph[boost::target(*edge, graph)].value;
}

Vertex RrtGraph::addVertex(QPoint value)
{
    Vertex vertex = boost::add_vertex(graph);
    graph[vertex].value = value;
    return vertex;
}

Edge RrtGraph::addEdge(Vertex v, Vertex u)
{
    boost::add_edge(v, u, graph);
}

void RrtGraph::debug()
{
    std::cout << "n" << boost::num_vertices(graph) << std::endl;
}
