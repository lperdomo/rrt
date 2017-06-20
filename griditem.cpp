#include "griditem.h"

#include <iostream>

GridItem::GridItem(qreal width, qreal height) :
    QGraphicsItem()
{
    this->width = width;
    this->height = height;
    scale = 1;
    graph = NULL;
}

GridItem::~GridItem()
{
}

QRectF GridItem::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void GridItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->scale(scale, scale);

    if (cspace.size() > 0) {
        for (int x = 0; x < cspace.size(); x++) {
            for (int y = 0; y < cspace[x].size(); y++) {
                if (cspace[x][y] == false) {
                    painter->setPen(QPen(QColor(0, 0, 0)));
                    painter->setBrush(QBrush(QColor(0, 0, 0)));
                    painter->drawRect(Cell::size*x, Cell::size*y, Cell::size, Cell::size);
                }
            }
        }
    }

    if (graph) {
        for (std::pair<Graph::VertexIterator, Graph::VertexIterator> it = graph->getVertices(); it.first != it.second; ++it.first) {
            if (drawPath) {
                painter->setPen(QPen(QColor(0, 100, 240)));
                painter->setBrush(QBrush(QColor(0, 100, 240)));
            } else {
                painter->setPen(QPen(QColor(0, 100, 240)));
                painter->setBrush(QBrush(QColor(0, 100, 240)));
            }
            painter->drawRect(Cell::size*graph->vertexAt(*it.first).x()
                              , Cell::size*graph->vertexAt(*it.first).y(), Cell::size, Cell::size);
        }
    }

    if (drawPath) {
        Graph::Vertex current = graph->getLast();
        while (current != graph->parent(current)) {
            painter->setPen(QPen(QColor(255, 0, 0)));
            painter->setBrush(QBrush(QColor(255, 0, 0)));
            painter->drawRect(Cell::size*graph->vertexAt(current).x()
                              , Cell::size*graph->vertexAt(current).y(), Cell::size, Cell::size);
            current = graph->parent(current);
        }
    }

    /*for (std::pair<EdgeIterator, EdgeIterator> it = graph.getEdges(); it.first != it.second; ++it.first) {
        painter->setPen(QPen(QBrush(QColor(200, 200, 200)), 2));
        painter->drawLine(Cell::size*graph.edgeSource(it.first).x()
                          , Cell::size*graph.edgeSource(it.first).y()
                          , Cell::size*graph.edgeTarget(it.first).x()
                          , Cell::size*graph.edgeTarget(it.first).y());
    }*/
    if (!source.isNull()) {
        painter->setPen(QPen(QColor(0, 220, 0)));
        painter->setBrush(QBrush(QColor(0, 220, 0)));
        painter->drawRect(Cell::size*round(source.x()/Cell::size)-Cell::size,
                      Cell::size*round(source.y()/Cell::size)-Cell::size,
                      Cell::size*2, Cell::size*2);        
    }
    if (!target.isNull()) {
        painter->setPen(QPen(QColor(220, 0, 0)));
        painter->setBrush(QBrush(QColor(220, 0, 0)));

        painter->drawRect(Cell::size*round(target.x()/Cell::size)-Cell::size,
                      Cell::size*round(target.y()/Cell::size)-Cell::size,
                      Cell::size*2, Cell::size*2);
    }
}

void GridItem::zoomIn()
{
    scale += 0.1;
}

void GridItem::zoomOut()
{
    scale -= 0.1;
}

void GridItem::setSource(qreal x, qreal y)
{
    if (this->isFree(x, y)) {
        source.setX(x);
        source.setY(y);
    }
}

void GridItem::resetSource()
{
    graph = NULL;
    source.setX(0);
    source.setY(0);
}

QPoint GridItem::getSource()
{
    return source;
}

bool GridItem::isSource(qreal x, qreal y)
{
    return (Cell::size*round(source.x()/Cell::size)-Cell::size <= Cell::size*round(x/Cell::size)
            && Cell::size*round(source.x()/Cell::size) >= Cell::size*round(x/Cell::size)-Cell::size
            && Cell::size*round(source.y()/Cell::size)-Cell::size <= Cell::size*round(y/Cell::size)
            && Cell::size*round(source.y()/Cell::size) >= Cell::size*round(y/Cell::size)-Cell::size);
}

void GridItem::setTarget(qreal x, qreal y)
{
    if (this->isFree(x, y)) {
        target.setX(x);
        target.setY(y);
    }
}

QPoint GridItem::getTarget()
{
    return target;
}

void GridItem::resetTarget()
{
    graph = NULL;
    target.setX(0);
    target.setY(0);
}

bool GridItem::isTarget(qreal x, qreal y)
{
    return (Cell::size*round(target.x()/Cell::size)-Cell::size <= Cell::size*round(x/Cell::size)
            && Cell::size*round(target.x()/Cell::size) >= Cell::size*round(x/Cell::size)-Cell::size
            && Cell::size*round(target.y()/Cell::size)-Cell::size <= Cell::size*round(y/Cell::size)
            && Cell::size*round(target.y()/Cell::size) >= Cell::size*round(y/Cell::size)-Cell::size);
}

bool GridItem::isFree(qreal x, qreal y)
{
    if (x > width-Cell::size || y > height-Cell::size || x <= Cell::size+2 || y <= Cell::size+2) return false;
    return cspace[round(x/Cell::size)][round(y/Cell::size)];
}

void GridItem::setGraph(Graph *graph)
{
    this->graph = graph;
}

void GridItem::setCSpace(std::vector<std::vector<bool> > cspace)
{
   this->cspace = cspace;
}

void GridItem::setDrawPath(bool drawPath)
{
    this->drawPath = drawPath;
}
