#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QGraphicsView>
#include "scene.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(double width, double height, double cellSize);
    ~Controller();
    void run();
private:
    Scene *scene;
    QGraphicsView *view;
    QThread *thread;
    void showView();
signals:

public slots:
    void update();
};

#endif // CONTROLLER_H
