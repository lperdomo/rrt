#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "cell.h"

class GridItem : public QGraphicsItem
{
public:
    GridItem(qreal width, qreal height);
    ~GridItem();
    QRectF boundingRect() const;
    void setSource(qreal x, qreal y);
    QPoint getSource();
    bool isSource(qreal x, qreal y);
    void setTarget(qreal x, qreal y);
    QPoint getTarget();
    bool isTarget(qreal x, qreal y);
    void zoomIn();
    void zoomOut();
    double scale;
protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
private:
    void drawColoredRect(QPainter *painter, double x, double y, QColor color);
    qreal width;
    qreal height;
    QPoint source;
    QPoint target;
};

#endif // GRIDITEM_H
