#include "controller.h"

#include <iostream>

Controller::Controller() :
    QObject()
{
    cspace = new CSpace(150, 100, 10);
    rrt = new Rrt();
    thread = new QThread();
    thread->connect(thread, SIGNAL(started()), rrt, SLOT(generateRrt()));
    this->connect(rrt, SIGNAL(iteration()), this, SLOT(showResult()));
    this->connect(rrt, SIGNAL(ended()), this, SLOT(stopThread()));
    scene = new Scene(150+1, 100+1, 5);
    view = new View(scene);
    window.setFixedSize(750+15, 500+65);
    window.getLineK()->setText(QString::number(rrt->getK()));
    window.getLineStep()->setText(QString::number(rrt->getStep()));
    window.getLineBias()->setText(QString::number(rrt->getBias()));
    window.getLineObstacles()->setText(QString::number(cspace->getObstacles()));
    window.getComboMode()->setCurrentIndex(rrt->getMode());
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
    scene->getGridItem()->setDrawPath(false);
    scene->getGridItem()->resetGraph();
    scene->getGridItem()->resetSource();
    scene->getGridItem()->resetTarget();
    scene->getGridItem()->setCSpace(cspace->getCSpace());
    scene->getGridItem()->update();
}

void Controller::doPathPlanning()
{
    window.resetMessage();
    if (thread->isRunning()) {
        rrt->setK(1);
     } else {
        window.getButtonRun()->setText("Stop");
        window.getButtonObs()->setEnabled(false);
        scene->getGridItem()->setDrawPath(false);

        rrt->setK(window.getLineK()->text().toInt());
        rrt->setStep(window.getLineStep()->text().toInt());
        rrt->setBias(window.getLineBias()->text().toInt());
        rrt->setMode(window.getComboMode()->currentIndex());
        rrt->setXInit(QVector2D(round(scene->getGridItem()->getSource().x()/scene->getGridItem()->getCellSize())
                    , round(scene->getGridItem()->getSource().y()/scene->getGridItem()->getCellSize())));

        if (!rrt->getXEnd().isNull()) cspace->dismarkTarget(rrt->getXEnd().x(), rrt->getXEnd().y());
        rrt->setXEnd(QVector2D(round(scene->getGridItem()->getTarget().x()/scene->getGridItem()->getCellSize())
                    , round(scene->getGridItem()->getTarget().y()/scene->getGridItem()->getCellSize())));
        if (!rrt->getXEnd().isNull()) cspace->markTarget(rrt->getXEnd().x(), rrt->getXEnd().y());
        rrt->setCSpace(cspace);

        rrt->moveToThread(thread);
        thread->start();
    }
}

void Controller::showResult()
{
    if (!scene->getGridItem()->getTarget().isNull()) {
        scene->getGridItem()->setFoundTarget(rrt->isFound());
        window.searchMessage(rrt->isFound());
    }
    scene->getGridItem()->setGraph(rrt->getT());
    scene->getGridItem()->setPaths(rrt->getPaths());
    scene->getGridItem()->update();
}

void Controller::stopThread()
{
    thread->exit();
    window.getButtonRun()->setText("Run");
    window.getButtonObs()->setEnabled(true);
    scene->getGridItem()->setDrawPath(true);
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

