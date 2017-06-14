#include "griditem.h"

GridItem::GridItem() :
    QGraphicsItem()
{
    scale = 1;
}

GridItem::~GridItem()
{
}

QRectF GridItem::boundingRect() const
{
    //return QRectF((grid->getWidth()/2)*-1, (grid->getHeight()/2)*-1, (grid->getWidth()/2), (grid->getHeight()/2));
}

void GridItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->scale(scale, scale);
}

void GridItem::zoomIn()
{
    scale += 0.1;
}

void GridItem::zoomOut()
{
    scale -= 0.1;
}
