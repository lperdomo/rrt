#include "view.h"

#include <iostream>

View::View(Scene *scene) :
    QGraphicsView(scene)
{
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        if (!dynamic_cast<Scene*>(this->scene())->getGridItem()->getSource().isNull()
            && !dynamic_cast<Scene*>(this->scene())->getGridItem()->getTarget().isNull()) {
            this->startPathPlanning();
        }
    }
}
