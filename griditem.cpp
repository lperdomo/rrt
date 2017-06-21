#include "griditem.h"

#include <iostream>

GridItem::GridItem(qreal width, qreal height) :
    QGraphicsItem()
{
    this->width = width;
    this->height = height;
    scale = 1;
    foundTarget = false;
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
                if (cspace[x][y] == 2) {
                    painter->setPen(QPen(QColor(0, 0, 0)));
                    painter->setBrush(QBrush(QColor(0, 0, 0)));
                    painter->drawRect(Cell::size*x, Cell::size*y, Cell::size, Cell::size);
                }
            }
        }
    }

    if (graph) {
        if (graph->size() > 0) {
            for (std::pair<Graph::EdgeIterator, Graph::EdgeIterator> it = graph->getEdges(); it.first != it.second; ++it.first) {
                painter->setPen(QPen(QColor(0, 200, 240)));
                painter->setBrush(QBrush(QColor(0, 200, 240)));
                int dx = graph->edgeTarget(it.first).x() - graph->edgeSource(it.first).x(), dy = graph->edgeTarget(it.first).y() - graph->edgeSource(it.first).y()
                   , dx1 = abs(dx), dy1 = abs(dy)
                   , px = 2*dy1-dx1, py = 2*dx1-dy1
                   , x, y, xe, ye;
                if (dy1 <= dx1) {
                    if (dx >= 0) {
                        x = graph->edgeSource(it.first).x();
                        y = graph->edgeSource(it.first).y();
                        xe = graph->edgeTarget(it.first).x();
                    } else {
                        x = graph->edgeTarget(it.first).x();
                        y = graph->edgeTarget(it.first).y();
                        xe = graph->edgeSource(it.first).x();
                    }
                    for (int i = 0; x < xe; i++) {
                        x++;
                        if (px < 0) px += 2*dy1;
                        else {
                            if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y++;
                            else y--;
                            px += 2*(dy1-dx1);
                        }
                        painter->drawRect(Cell::size*x
                                          , Cell::size*y, Cell::size, Cell::size);
                    }
                } else {
                    if (dy >= 0) {
                        x = graph->edgeSource(it.first).x();
                        y = graph->edgeSource(it.first).y();
                        ye = graph->edgeTarget(it.first).y();
                    } else {
                        x = graph->edgeTarget(it.first).x();
                        y = graph->edgeTarget(it.first).y();
                        ye = graph->edgeSource(it.first).y();
                    }
                    for (int i = 0; y < ye; i++) {
                        y++;
                        if (py <= 0) py += 2*dx1;
                        else {
                            if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x++;
                            else x--;
                            py += 2*(dx1-dy1);
                        }
                        painter->drawRect(Cell::size*x
                                          , Cell::size*y, Cell::size, Cell::size);
                    }
                }
            }
            for (std::pair<Graph::VertexIterator, Graph::VertexIterator> it = graph->getVertices(); it.first != it.second; ++it.first) {
                if (drawPath && foundTarget) {
                    painter->setPen(QPen(QColor(0, 100, 240, 200)));
                    painter->setBrush(QBrush(QColor(0, 100, 240, 200)));
                } else {
                    painter->setPen(QPen(QColor(0, 100, 240)));
                    painter->setBrush(QBrush(QColor(0, 100, 240)));
                }
                painter->drawRect(Cell::size*graph->vertexAt(*it.first).x()
                                  , Cell::size*graph->vertexAt(*it.first).y(), Cell::size, Cell::size);
            }
        }
    }

    if (drawPath && foundTarget) {
        Graph::Vertex current = graph->getLast();
        while (current != graph->parent(current)) {
            painter->setPen(QPen(QColor(240, 100, 240)));
            painter->setBrush(QBrush(QColor(240, 100, 240)));
            painter->drawRect(Cell::size*graph->vertexAt(current).x()
                              , Cell::size*graph->vertexAt(current).y(), Cell::size, Cell::size);
            current = graph->parent(current);
        }
        painter->setPen(QPen(QColor(240, 100, 240)));
        painter->setBrush(QBrush(QColor(240, 100, 240)));
        painter->drawRect(Cell::size*graph->vertexAt(current).x()
                          , Cell::size*graph->vertexAt(current).y(), Cell::size, Cell::size);
    }

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
        painter->drawRect(Cell::size*round(target.x()/Cell::size)-Cell::size*2,
                      Cell::size*round(target.y()/Cell::size)-Cell::size*2,
                      Cell::size*3, Cell::size*3);
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
    this->resetGraph();
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
    this->resetGraph();
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
    return cspace[round(x/Cell::size)][round(y/Cell::size)] <= 0;
}

void GridItem::setGraph(Graph *graph)
{
    this->graph = graph;
}

void GridItem::resetGraph()
{
    foundTarget = false;
    drawPath = false;
    if (graph) {
        this->graph->clear();
    }
}

void GridItem::setFoundTarget(bool foundTarget)
{
    this->foundTarget = foundTarget;
}

void GridItem::setCSpace(std::vector<std::vector<int> > cspace)
{
   this->cspace = cspace;
}

void GridItem::setDrawPath(bool drawPath)
{
    this->drawPath = drawPath;
}
