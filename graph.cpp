#include "graph.h"

#include <iostream>

Graph::Graph()
{
}

void Graph::init(QVector2D value)
{
    this->clear();
    this->addVertex(value);
}

void Graph::clear()
{
    graph.clear();
    parents.clear();
}

std::pair<Graph::VertexIterator, Graph::VertexIterator> Graph::getVertices()
{
    return boost::vertices(graph);
}

std::pair<Graph::EdgeIterator, Graph::EdgeIterator> Graph::getEdges()
{
    return boost::edges(graph);
}

QVector2D Graph::vertexAt(Vertex vertex)
{
    return graph[vertex].value;
}

QVector2D Graph::edgeSource(EdgeIterator edge)
{
    return graph[boost::source(*edge, graph)].value;
}

QVector2D Graph::edgeTarget(EdgeIterator edge)
{
    return graph[boost::target(*edge, graph)].value;
}

Graph::Vertex Graph::addVertex(QVector2D value)
{
    last = boost::add_vertex(graph);
    graph[last].value = value;
    return last;
}

Graph::Edge Graph::addEdge(Vertex v, Vertex u)
{
    boost::add_edge(v, u, graph);
    parents[u] = v;
}

Graph::Vertex Graph::parent(Vertex child)
{
    if (parents.at(child)) {
        return parents[child];
    }
    return child;
}

Graph::Vertex Graph::getLast()
{
    return last;
}

int Graph::size()
{
    return boost::num_vertices(graph);
}

void Graph::debug()
{
    std::cout << "n" << boost::num_vertices(graph) << std::endl;
}
