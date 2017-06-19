#include "scene.h"

#include <iostream>

Scene::Scene(int width, int height) :
    QGraphicsScene(0, 0, width*Cell::size, height*Cell::size)
{
    gridItem = new GridItem(this->width(), this->height());
    this->addItem(gridItem);
}

Scene::~Scene()
{
    delete gridItem;
}

void Scene::drawForeground(QPainter *painter, const QRectF &rect)
{
    painter->scale(gridItem->scale, gridItem->scale);
    qreal left = int(rect.left()) - (int(rect.left()) % (int(Cell::size)));
    qreal top = int(rect.top()) - (int(rect.top()) % (int(Cell::size)));
    QVarLengthArray<QLineF, 100> lines;

    painter->setPen(QPen(QColor(240, 240, 240, 150)));
    for (qreal x = left; x < rect.right(); x += Cell::size)
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    for (qreal y = top; y < rect.bottom(); y += Cell::size)
        lines.append(QLineF(rect.left(), y, rect.right(), y));

    painter->drawLines(lines.data(), lines.size());
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Minus) {
        gridItem->zoomOut();
        this->update();
    } else if (event->key() == Qt::Key_Plus) {
        gridItem->zoomIn();
        this->update();
    }
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (gridItem->isTarget(event->scenePos().x(), event->scenePos().y())) {
        gridItem->resetTarget();
        this->update();
    } else if (gridItem->isSource(event->scenePos().x(), event->scenePos().y())) {
        gridItem->resetSource();
        this->update();
    } else if (gridItem->getSource().isNull()) {
        gridItem->setSource(event->scenePos().x(), event->scenePos().y());
        this->update();
    } else if (gridItem->getTarget().isNull()) {
        gridItem->setTarget(event->scenePos().x(), event->scenePos().y());
        this->update();
    }
}

GridItem *Scene::getGridItem()
{
    return gridItem;
}
