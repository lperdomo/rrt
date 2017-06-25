#include "griditem.h"

#include <iostream>

GridItem::GridItem(qreal width, qreal height, int cellSize) :
    QGraphicsItem()
{
    this->width = width;
    this->height = height;
    this->cellSize = cellSize;
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
                    painter->drawRect(cellSize*x, cellSize*y, cellSize, cellSize);
                }
            }
        }
    }

    if (graph) {
        if (graph->size() > 0) {
            for (std::pair<Graph::EdgeIterator, Graph::EdgeIterator> it = graph->getEdges(); it.first != it.second; ++it.first) {
                painter->setPen(QPen(QColor(0, 200, 240)));
                painter->setBrush(QBrush(QColor(0, 200, 240)));
                for (int i = 0; i < paths.size(); i++) {
                    painter->drawRect(cellSize*paths[i].x(), cellSize*paths[i].y(), cellSize, cellSize);
                }
            }
            for (std::pair<Graph::VertexIterator, Graph::VertexIterator> it = graph->getVertices(); it.first != it.second; ++it.first) {
                painter->setPen(QPen(QColor(0, 100, 240)));
                painter->setBrush(QBrush(QColor(0, 100, 240)));
                painter->drawRect(cellSize*graph->vertexAt(*it.first).x()
                                  , cellSize*graph->vertexAt(*it.first).y()
                                  , cellSize, cellSize);
            }
        }
    }

    if (drawPath && foundTarget) {
        Graph::Vertex current = graph->getLast();
        Graph::Vertex parent = graph->parent(current);;
        while (true) {
            painter->setPen(QPen(QColor(220, 100, 100)));
            painter->setBrush(QBrush(QColor(220, 100, 100)));
            //std::vector<QVector2D> path = Util::bresenham(graph->vertexAt(current), graph->vertexAt(parent));
            std::vector<State> path = Util::dubins(graph->vertexAt(parent), graph->vertexAt(current));
            for (int i = 0; i < path.size(); i++) {
                painter->drawRect(cellSize*path[i].x(), cellSize*path[i].y(), cellSize, cellSize);
            }
            painter->setPen(QPen(QColor(220, 0, 0)));
            painter->setBrush(QBrush(QColor(220, 0, 0)));
            painter->drawRect(cellSize*graph->vertexAt(current).x()
                              , cellSize*graph->vertexAt(current).y()
                              , cellSize, cellSize);
            current = graph->parent(current);
            if (parent == graph->getFirst()) {
                break;
            } else if (current == graph->parent(current)) {
                parent = graph->getFirst();
            } else {
                parent = graph->parent(current);
            }
        }
    }

    if (!source.isNull()) {
        painter->setPen(QPen(QColor(220, 0, 0)));
        painter->setBrush(QBrush(QColor(220, 0, 0)));
        painter->drawRect(cellSize*round(source.x()/cellSize)-cellSize,
                      cellSize*round(source.y()/cellSize)-cellSize,
                      cellSize*2, cellSize*2);
    }
    if (!target.isNull()) {
        painter->setPen(QPen(QColor(220, 0, 0)));
        painter->setBrush(QBrush(QColor(220, 0, 0)));
        painter->drawRect(cellSize*round(target.x()/cellSize)-cellSize*2,
                      cellSize*round(target.y()/cellSize)-cellSize*2,
                      cellSize*3, cellSize*3);
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
    return (cellSize*round(source.x()/cellSize)-cellSize <= cellSize*round(x/cellSize)
            && cellSize*round(source.x()/cellSize) >= cellSize*round(x/cellSize)-cellSize
            && cellSize*round(source.y()/cellSize)-cellSize <= cellSize*round(y/cellSize)
            && cellSize*round(source.y()/cellSize) >= cellSize*round(y/cellSize)-cellSize);
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
    return (cellSize*round(target.x()/cellSize)-cellSize <= cellSize*round(x/cellSize)
            && cellSize*round(target.x()/cellSize) >= cellSize*round(x/cellSize)-cellSize
            && cellSize*round(target.y()/cellSize)-cellSize <= cellSize*round(y/cellSize)
            && cellSize*round(target.y()/cellSize) >= cellSize*round(y/cellSize)-cellSize);
}

bool GridItem::isFree(qreal x, qreal y)
{
    if (x > width-cellSize || y > height-cellSize || x <= cellSize+2 || y <= cellSize+2) return false;
    return cspace[round(x/cellSize)][round(y/cellSize)] <= 0;
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

void GridItem::setPaths(std::vector<QVector2D> paths)
{
    this->paths = paths;
}

void GridItem::setDrawPath(bool drawPath)
{
    this->drawPath = drawPath;
}

void GridItem::setCellSize(double cellSize)
{
    this->cellSize = cellSize;
}

double GridItem::getCellSize()
{
    return cellSize;
}
