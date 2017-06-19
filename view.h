#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QKeyEvent>

#include "scene.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(Scene *scene);
};

#endif // VIEW_H
