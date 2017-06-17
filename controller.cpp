#include "controller.h"

#include <iostream>

Controller::Controller() :
    QObject()
{
    rrt = new Rrt();
    rrt->setGrid(100, 100);
    thread = new QThread();
    view = new View(new Scene(100, 100));
    this->connect(view, SIGNAL(startPathPlanning()), this, SLOT(doPathPlanning()));
}

Controller::~Controller()
{
    delete rrt;
    delete view;
    delete thread;
}

void Controller::run()
{
    this->showView();
}

void Controller::doPathPlanning()
{
    rrt->setXInit(dynamic_cast<Scene*>(view->scene())->getGridItem()->getSource());
    rrt->setXEnd(dynamic_cast<Scene*>(view->scene())->getGridItem()->getTarget());
    rrt->generateRrt();
}

void Controller::showView()
{
    if (!view->isVisible()) {
        view->show();
    } else {
        view->viewport()->update();
    }
}

