#include "controller.h"

#include <iostream>

Controller::Controller() :
    QObject()
{
    cspace = new CSpace(100, 100, 5);
    rrt = new Rrt();
    thread = new QThread();
    scene = new Scene(100+1, 100+1);
    view = new View(scene);
    window.setFixedSize(500+15, 500+65);
    window.getLineK()->setText(QString::number(rrt->getK()));
    window.getLineObstacles()->setText(QString::number(cspace->getObstacles()));
    this->connect(window.getButtonRun(), SIGNAL(clicked(bool)), this, SLOT(doPathPlanning()));
    this->connect(window.getButtonObs(), SIGNAL(clicked(bool)), this, SLOT(doWorldGeneration()));

}

Controller::~Controller()
{
    delete rrt;
    delete view;
    delete thread;
}

void Controller::run()
{
    this->doWorldGeneration();
    this->showView();
}

void Controller::doWorldGeneration()
{
    window.resetMessage();
    cspace->setObstacles(window.getLineObstacles()->text().toInt());
    cspace->generateCSpace();
    scene->getGridItem()->setGraph(NULL);
    scene->getGridItem()->resetSource();
    scene->getGridItem()->resetTarget();
    scene->getGridItem()->setCSpace(cspace->getCSpace());
    scene->getGridItem()->update();
}

void Controller::doPathPlanning()
{
    window.resetMessage();
    rrt->setK(window.getLineK()->text().toInt());
    rrt->setCSpace(cspace);
    rrt->setXInit(scene->getGridItem()->getSource());
    rrt->setXEnd(scene->getGridItem()->getTarget());
    rrt->generateRrt();
    if (!scene->getGridItem()->getTarget().isNull()) {
        window.searchMessage(rrt->getFound());
    }
    scene->getGridItem()->setGraph(rrt->getTPath());
    scene->getGridItem()->update();
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

