#ifndef SCENEGRID_H
#define SCENEGRID_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

#include "rrt.h"
#include "griditem.h"

class Scene : public QGraphicsScene
{
public:
    Scene(int width, int height);
    ~Scene();
    GridItem *getGridItem();
    void drawSpace(std::vector<std::vector<bool> > Cspace);
    void drawPath(Graph *graph);
private:
    GridItem *gridItem;
protected:
    void drawForeground(QPainter *painter, const QRectF &rect);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void change();
};

#endif // SCENEGRID_H
