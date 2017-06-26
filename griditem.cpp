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
                if (cspace[x][y] == 3) {
                    painter->setPen(QPen(QColor(0, 0, 0)));
                    painter->setBrush(QBrush(QColor(0, 0, 0)));
                    painter->drawRect(cellSize*x, cellSize*y, cellSize, cellSize);
                } else if (cspace[x][y] == -1) {
                    painter->setPen(QPen(QColor(0, 200, 240)));
                    painter->setBrush(QBrush(QColor(0, 200, 240)));
                    painter->drawRect(cellSize*x, cellSize*y, cellSize, cellSize);
                } else if (cspace[x][y] == -2) {
                    painter->setPen(QPen(QColor(0, 100, 240)));
                    painter->setBrush(QBrush(QColor(0, 100, 240)));
                    painter->drawRect(cellSize*x, cellSize*y, cellSize, cellSize);
                } else if (cspace[x][y] == -3) {
                    painter->setPen(QPen(QColor(220, 100, 100)));
                    painter->setBrush(QBrush(QColor(220, 100, 100)));
                    painter->drawRect(cellSize*x, cellSize*y, cellSize, cellSize);
                } else if (cspace[x][y] == -4) {
                    painter->setPen(QPen(QColor(220, 0, 0)));
                    painter->setBrush(QBrush(QColor(220, 0, 0)));
                    painter->drawRect(cellSize*x, cellSize*y, cellSize, cellSize);
                }
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

void GridItem::setCellSize(double cellSize)
{
    this->cellSize = cellSize;
}

double GridItem::getCellSize()
{
    return cellSize;
}

void GridItem::setSource(qreal x, qreal y)
{
    source.setX(x);
    source.setY(y);
}

void GridItem::resetSource()
{
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
    target.setX(x);
    target.setY(y);
}

QPoint GridItem::getTarget()
{
    return target;
}

void GridItem::resetTarget()
{
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
    int xa = round(x/cellSize), ya = round(y/cellSize);
    for (int i = xa-2; i <= xa+1; i++) {
        for (int j = ya-2; j <= ya+1; j++) {
            if (cspace[i][j] >= 2) return false;
        }
    }
    return true;
}

void GridItem::setFoundTarget(bool foundTarget)
{
    this->foundTarget = foundTarget;
}

void GridItem::setCSpace(std::vector<std::vector<int> > cspace)
{
   this->cspace = cspace;
}

void GridItem::zoomIn()
{
    scale += 0.1;
}

void GridItem::zoomOut()
{
    scale -= 0.1;
}
