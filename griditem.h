#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

#include "graph.h"
#include "util.h"

class GridItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    GridItem(qreal width, qreal height, int cellSize);
    ~GridItem();
    QRectF boundingRect() const;
    void setCellSize(double cellSize);
    double getCellSize();
    void setSource(qreal x, qreal y);
    QPoint getSource();
    void resetSource();
    bool isSource(qreal x, qreal y);
    void setTarget(qreal x, qreal y);
    QPoint getTarget();
    void resetTarget();
    bool isTarget(qreal x, qreal y);
    void setCSpace(std::vector<std::vector<int> > cspace);    
    bool isFree(qreal x, qreal y);
    void setFoundTarget(bool foundTarget);
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
    bool foundTarget;
    bool drawPath;
    double cellSize;
    std::vector<std::vector<int> > cspace;
signals:
    void setSomething(int, int);
};

#endif // GRIDITEM_H
