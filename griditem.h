#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "rrtgraph.h"
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
    void setRrtGraph(RrtGraph graph);
    void setObstacles(std::vector<Cell> obstacles);
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
    RrtGraph graph;
    std::vector<Cell> obstacles;
};

#endif // GRIDITEM_H
