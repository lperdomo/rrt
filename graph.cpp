#include "graph.h"

#include <iostream>

Graph::Graph()
{
}

void Graph::init(State value)
{
    this->clear();
    first = this->addVertex(value);
    parents[first] = first;
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

State Graph::vertexAt(Vertex vertex)
{
    return graph[vertex].value;
}

State Graph::edgeSource(EdgeIterator edge)
{
    return graph[boost::source(*edge, graph)].value;
}

State Graph::edgeTarget(EdgeIterator edge)
{
    return graph[boost::target(*edge, graph)].value;
}

Graph::Vertex Graph::addVertex(State value)
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

Graph::Vertex Graph::getFirst()
{
    return first;
}

int Graph::size()
{
    return boost::num_vertices(graph);
}

void Graph::debug()
{
    std::cout << "n" << boost::num_vertices(graph) << std::endl;
}
