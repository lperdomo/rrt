#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include "graph.h"
#include "util.h"

class GridItem : public QGraphicsItem
{
public:
    GridItem(qreal width, qreal height, int cellSize);
    ~GridItem();
    QRectF boundingRect() const;
    void setSource(qreal x, qreal y);
    QPoint getSource();
    void resetSource();
    bool isSource(qreal x, qreal y);
    void setTarget(qreal x, qreal y);
    QPoint getTarget();
    void resetTarget();
    bool isTarget(qreal x, qreal y);
    void setGraph(Graph *graph);
    void resetGraph();
    void setCSpace(std::vector<std::vector<int> > cspace);
    void setPaths(std::vector<QVector2D> paths);
    bool isFree(qreal x, qreal y);
    void setFoundTarget(bool foundTarget);
    void setDrawPath(bool drawPath);
    void setCellSize(double cellSize);
    double getCellSize();
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
    Graph *graph;
    std::vector<std::vector<int> > cspace;
    std::vector<QVector2D> paths;
    bool drawPath;
    double cellSize;
};

#endif // GRIDITEM_H
