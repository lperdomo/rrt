#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <QGraphicsView>

#include "rrt.h"
#include "view.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller();
    ~Controller();
    void run();
private:
    Rrt *rrt;
    View *view;
    Scene *scene;
    QThread *thread;
    void showView();
signals:

public slots:
//    void setSourcePoint(int x, int y);
    void doPathPlanning();
};

#endif // CONTROLLER_H
