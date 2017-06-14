#include "controller.h"

#include <iostream>

Controller::Controller(double width, double height, double cellSize) :
    QObject()
{
    scene = new Scene((width/2)*cellSize*-1, (height/2)*cellSize*-1, width*cellSize, height*cellSize, cellSize);
    view = new QGraphicsView(scene);
    thread = new QThread();
}

Controller::~Controller()
{
    delete view;
    delete scene;
    delete thread;
}

void Controller::run()
{
    this->showView();
}

void Controller::update()
{
    this->showView();
}

void Controller::showView()
{
    if (!view->isVisible()) {
        view->show();
    } else {
        view->viewport()->update();
    }
}
