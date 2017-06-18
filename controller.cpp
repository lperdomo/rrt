#include "controller.h"

#include <iostream>

Controller::Controller() :
    QObject()
{
    rrt = new Rrt();
    thread = new QThread();
    scene = new Scene(100, 100);
    view = new View(scene);
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
    rrt->setXInit(scene->getGridItem()->getSource());
    rrt->setXEnd(scene->getGridItem()->getTarget());
    rrt->generateCSpace(100, 100);
    scene->drawObstacles(rrt->getCobs());
    scene->drawPath(rrt->generateRrt());
}

void Controller::showView()
{
    if (!view->isVisible()) {
        view->show();
    } else {
        view->viewport()->update();
    }
}

