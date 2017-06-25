#include "scene.h"

#include <iostream>

Scene::Scene(int width, int height, int cellSize) :
    QGraphicsScene(0, 0, width*cellSize, height*cellSize)
{
    gridItem = new GridItem(this->width(), this->height(), cellSize);
    this->addItem(gridItem);
}

Scene::~Scene()
{
    delete gridItem;
}

void Scene::drawForeground(QPainter *painter, const QRectF &rect)
{
    painter->scale(gridItem->scale, gridItem->scale);
    qreal left = int(rect.left()) - (int(rect.left()) % (int(gridItem->getCellSize())));
    qreal top = int(rect.top()) - (int(rect.top()) % (int(gridItem->getCellSize())));
    QVarLengthArray<QLineF, 100> lines;

    painter->setPen(QPen(QColor(240, 240, 240, 100)));
    for (qreal x = left; x < rect.right(); x += gridItem->getCellSize())
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    for (qreal y = top; y < rect.bottom(); y += gridItem->getCellSize())
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
    gridItem->setSomething(event->scenePos().x(), event->scenePos().y());
}

GridItem *Scene::getGridItem()
{
    return gridItem;
}
