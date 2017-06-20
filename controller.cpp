#include "controller.h"

#include <iostream>

Controller::Controller() :
    QObject()
{
    cspace = new CSpace(150, 100, 5);
    rrt = new Rrt();
    thread = new QThread();
    thread->connect(thread, SIGNAL(started()), rrt, SLOT(generateRrt()));
    this->connect(rrt, SIGNAL(iteration()), this, SLOT(showResult()));
    this->connect(rrt, SIGNAL(ended()), this, SLOT(stopThread()));
    scene = new Scene(150+1, 100+1);
    view = new View(scene);
    window.setFixedSize(750+15, 500+65);
    window.getLineK()->setText(QString::number(rrt->getK()));
    window.getLineStep()->setText(QString::number(rrt->getStep()));
    window.getLineBias()->setText(QString::number(rrt->getBias()));
    window.getLineObstacles()->setText(QString::number(cspace->getObstacles()));
    this->connect(window.getButtonRun(), SIGNAL(clicked(bool)), this, SLOT(doPathPlanning()));
    this->connect(window.getButtonObs(), SIGNAL(clicked(bool)), this, SLOT(doWorldGeneration()));
}

Controller::~Controller()
{
    thread->exit();
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
    scene->getGridItem()->setDrawPath(false);
    scene->getGridItem()->resetSource();
    scene->getGridItem()->resetTarget();
    scene->getGridItem()->setCSpace(cspace->getCSpace());
    scene->getGridItem()->update();
}

void Controller::doPathPlanning()
{
    window.resetMessage();
    scene->getGridItem()->setDrawPath(false);
    rrt->setK(window.getLineK()->text().toInt());
    rrt->setStep(window.getLineStep()->text().toInt());
    rrt->setBias(window.getLineBias()->text().toInt());
    rrt->setCSpace(cspace);
    rrt->setXInit(QVector2D(scene->getGridItem()->getSource()));
    rrt->setXEnd(QVector2D(scene->getGridItem()->getTarget()));
    rrt->moveToThread(thread);
    thread->start();
}

void Controller::showResult()
{
    if (!scene->getGridItem()->getTarget().isNull()) {
        window.searchMessage(rrt->isFound());
    }
    scene->getGridItem()->setGraph(rrt->getT());
    scene->getGridItem()->update();
}

void Controller::stopThread()
{
    scene->getGridItem()->setDrawPath(true);
    scene->getGridItem()->update();
    thread->exit();
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

