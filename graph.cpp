#include "graph.h"

#include <iostream>

Graph::Graph()
{
}

void Graph::init(QPoint value)
{
    graph.clear();
    this->addVertex(value);
}

std::pair<Graph::VertexIterator, Graph::VertexIterator> Graph::getVertices()
{
    return boost::vertices(graph);
}

std::pair<Graph::EdgeIterator, Graph::EdgeIterator> Graph::getEdges()
{
    return boost::edges(graph);
}

QPoint Graph::vertexAt(Vertex vertex)
{
    return graph[vertex].value;
}

QPoint Graph::edgeSource(EdgeIterator edge)
{
    return graph[boost::source(*edge, graph)].value;
}

QPoint Graph::edgeTarget(EdgeIterator edge)
{
    return graph[boost::target(*edge, graph)].value;
}

Graph::Vertex Graph::addVertex(QPoint value)
{
    Vertex vertex = boost::add_vertex(graph);
    graph[vertex].value = value;
    return vertex;
}

Graph::Edge Graph::addEdge(Vertex v, Vertex u)
{
    boost::add_edge(v, u, graph);
}

void Graph::debug()
{
    std::cout << "n" << boost::num_vertices(graph) << std::endl;
}
