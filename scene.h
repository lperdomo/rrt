#ifndef SCENEGRID_H
#define SCENEGRID_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QKeyEvent>

#include "griditem.h"

class Scene : public QGraphicsScene
{
public:
    Scene(qreal x, qreal y, qreal width, qreal height);
    ~Scene();
private:
    GridItem *gridItem;
protected:
    void drawForeground(QPainter *painter, const QRectF &rect);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // SCENEGRID_H
