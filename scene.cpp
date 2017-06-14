#include "scene.h"

Scene::Scene(qreal x, qreal y, qreal width, qreal height, qreal cellSize) :
    QGraphicsScene(x, y, width, height)
{
    gridItem = new GridItem(cellSize);
    this->addItem(gridItem);
}

Scene::~Scene()
{
    delete gridItem;
}

void Scene::drawForeground(QPainter *painter, const QRectF &rect)
{
    qreal x, y;
    qreal left = int(rect.left()) - (int(rect.left()) % (int(cellSize)));
    qreal top = int(rect.top()) - (int(rect.top()) % (int(cellSize)));
    QVarLengthArray<QLineF, 100> lines;

    painter->setPen(QPen(Qt::gray));
    for (x = left; x < rect.right(); x += cellSize)
        lines.append(QLineF(x, rect.top(), x, rect.bottom()));
    for (y = top; y < rect.bottom(); y += cellSize)
        lines.append(QLineF(rect.left(), y, rect.right(), y));

    painter->drawLines(lines.data(), lines.size());

    painter->setPen(QPen(Qt::black));
    painter->drawLine(QLineF(0, rect.top(), 0, rect.bottom()));
    painter->drawLine(QLineF(rect.left(), 0, rect.right(), 0));

    painter->setPen(QPen(Qt::black));
    painter->drawLine(QLineF(0, rect.top(), 0, rect.bottom()));
    painter->drawLine(QLineF(rect.left(), 0, rect.right(), 0));
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Minus) {
        gridItem->zoomOut();
    } else if (event->key() == Qt::Key_Plus) {
        gridItem->zoomIn();
    }
}

void Scene::keyReleaseEvent(QKeyEvent *event)
{
}
