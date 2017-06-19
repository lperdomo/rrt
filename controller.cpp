#include "controller.h"

#include <iostream>

Controller::Controller() :
    QObject()
{
    window.setFixedSize(500+15, 500+65);
    cspace = new CSpace(100, 100);
    rrt = new Rrt();
    thread = new QThread();
    scene = new Scene(100+1, 100+1);
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
    cspace->generateCSpace();
    scene->drawSpace(cspace->getCSpace());
    this->showView();
}

void Controller::doPathPlanning()
{
    rrt->setCSpace(cspace);
    rrt->setXInit(scene->getGridItem()->getSource());
    rrt->setXEnd(scene->getGridItem()->getTarget());
    rrt->generateRrt();
    scene->drawPath(rrt->getTPath());
}

void Controller::showView()
{
    window.setCentralWidget(view);
    if (!window.isVisible()) {
        window.show();
    } else {
        view->viewport()->update();
    }
}

