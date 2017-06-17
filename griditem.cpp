#include "griditem.h"

#include <iostream>

GridItem::GridItem(qreal width, qreal height) :
    QGraphicsItem()
{
    this->width = width;
    this->height = height;
    scale = 1;
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

    if (!source.isNull()) {
        painter->setBrush(QBrush(QColor(0, 255, 0)));
        painter->drawRect(Cell::size*round(source.x()/Cell::size)-Cell::size,
                      Cell::size*round(source.y()/Cell::size)-Cell::size,
                      Cell::size*2, Cell::size*2);
    }
    if (!target.isNull()) {
        painter->setBrush(QBrush(QColor(255, 0, 0)));
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
    source.setX(x);
    source.setY(y);
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
    target.setX(x);
    target.setY(y);
}

QPoint GridItem::getTarget()
{
    return target;
}

bool GridItem::isTarget(qreal x, qreal y)
{
    return (Cell::size*round(target.x()/Cell::size)-Cell::size <= Cell::size*round(x/Cell::size)
            && Cell::size*round(target.x()/Cell::size) >= Cell::size*round(x/Cell::size)-Cell::size
            && Cell::size*round(target.y()/Cell::size)-Cell::size <= Cell::size*round(y/Cell::size)
            && Cell::size*round(target.y()/Cell::size) >= Cell::size*round(y/Cell::size)-Cell::size);
}
