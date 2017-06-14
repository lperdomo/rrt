#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QPainter>

class GridItem : public QGraphicsItem
{
public:
    GridItem();
    ~GridItem();
    QRectF boundingRect() const;
    void zoomIn();
    void zoomOut();
protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
private:
    void drawColoredRect(QPainter *painter, double x, double y, QColor color);
    qreal cellSize;
    double scale;
};

#endif // GRIDITEM_H
