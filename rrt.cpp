#include "rrt.h"

#include <iostream>

Rrt::Rrt() :
    QObject()
{
    K = 6000;
    step = 1;
    bias = 0;
    T = new Graph();
    mode = 0;

}

Rrt::~Rrt()
{
}

void Rrt::setCSpace(CSpace *cspace)
{
    this->cspace = cspace;
}

CSpace *Rrt::getCSpace()
{
    return cspace;
}

void Rrt::setXInit(QVector2D XInit)
{
    this->XInit = XInit;
}

QVector2D Rrt::getXInit()
{
    return this->XInit;
}

void Rrt::setXEnd(QVector2D XEnd)
{
    this->XEnd = XEnd;
}

QVector2D Rrt::getXEnd()
{
    return this->XEnd;
}

void Rrt::setK(int K)
{
    this->K = K;
}

int Rrt::getK()
{
    return this->K;
}

void Rrt::setStep(int step)
{
    this->step = step;
}

int Rrt::getStep()
{
    return this->step;
}

void Rrt::setBias(int bias)
{
    this->bias = bias;
}

int Rrt::getBias()
{
    return this->bias;
}

void Rrt::setMode(int mode)
{
    this->mode = mode;
}

int Rrt::getMode()
{
    return mode;
}

bool Rrt::isFound()
{
    return found;
}

void Rrt::generateRrt()
{
    Graph::Vertex vertex;
    State XNew;
    found = false;
    cspace->clearCSpace();
    T->init(XInit);
    for (int k = 0; (k < K && found == false); k++) {
        this->randomState();
        vertex = this->nearestNeighbour();
        if (Util::euclideanDistance(XRand, XNear) > 1) {
            XNew = this->newState();
            if (this->validTransition(XNear, XNew)) {
                if (cspace->isTargetAt(XNew.x(), XNew.y())) found = true;
                cspace->setVertexAt(XNew.x(), XNew.y());
                T->addEdge(vertex, T->addVertex(XNew));
            }
        }
        this->iteration();
    }
    if (found) this->buildResult();
    this->ended();
}

void Rrt::randomState()
{
    if (bias > 0 && rand()%100 <= bias) {
        XRand.setX(XEnd.x());
        XRand.setY(XEnd.y());
        XRand.setTh(XEnd.th());
    } else {
        int id = rand()%cspace->getCfree()->size();
        XRand.setX(cspace->freeAt(id).x());
        XRand.setY(cspace->freeAt(id).y());
        XRand.setTh(rand()%360 + (-180));
        //XRand.setX(round(drand48()*cspace->getWidth()));
        //XRand.setY(round(drand48()*cspace->getHeight()));
    }
}

Graph::Vertex Rrt::nearestNeighbour()
{
//    if (mode == 0 || mode == 1) {
        double closest = -1, distance;
        Graph::Vertex vertex = 0;
        for (std::pair<Graph::VertexIterator, Graph::VertexIterator> it = T->getVertices(); it.first != it.second; ++it.first) {
            //std::cout << "teste" << std::endl;
            distance = Util::euclideanDistance(QVector2D(T->vertexAt(*it.first).x(), T->vertexAt(*it.first).y()), XRand);
            if (closest < 0 || distance < closest) {
                closest = distance;
                XNear.setX(T->vertexAt(*it.first).x());
                XNear.setY(T->vertexAt(*it.first).y());
                vertex = *it.first;
            }
        }
        return vertex;
//    }
}

bool Rrt::validTransition(State p1, State p2)
{
    if (cspace->isObstacleAt(p1.x(), p1.y())) return false;

    std::vector<QVector2D> transition;
    if (mode == 0) transition = Util::bresenham(p1, p2);
    else if (mode == 1) transition = Util::dubins(p1, p2, step);
    for (int i = 0; i < transition.size(); i++) {
        if (cspace->isObstacleAt(transition[i].x(), transition[i].y())) return false;
    }

    for (int i = 0; i < transition.size(); i++) {
        if (!cspace->isVertexAt(transition[i].x(), transition[i].y())
            && !cspace->isTargetAt(transition[i].x(), transition[i].y())) {
            cspace->setPathAt(transition[i].x(), transition[i].y());
        }
    }
    return true;
}

State Rrt::newState()
{
//    if (mode == 0 || mode == 1) {
        double th = atan2(XRand.y()-XNear.y(),XRand.x()-XNear.x());
        if (Util::euclideanDistance(XNear, XRand) < step) {
            return State(XRand.x(), XRand.y(), th);
        } else {
            return State(round(XNear.x()+step*cos(th)), round(XNear.y()+step*sin(th)), th);
        }
//    }
}

void Rrt::buildResult()
{
    Graph::Vertex current = T->getLast();
    Graph::Vertex parent = T->parent(current);;
    std::vector<QVector2D> transition;
    while (true) {
        transition.clear();
        if (mode == 0) transition = Util::bresenham(T->vertexAt(current), T->vertexAt(parent));
        else if (mode == 1) transition = Util::dubins(T->vertexAt(parent), T->vertexAt(current), step);

        for (int i = 0; i < transition.size(); i++) {
            if (!cspace->isObstacleAt(transition[i].x(), transition[i].y())) {
                if (!cspace->isResultVertexAt(transition[i].x(), transition[i].y())) {
                    cspace->setResultPathAt(transition[i].x(), transition[i].y());
                }
            }
        }
        cspace->setResultVertexAt(T->vertexAt(current).x(), T->vertexAt(current).y());
        current = T->parent(current);
        if (parent == T->getFirst()) {
            break;
        } else if (current == T->parent(current)) {
            parent = T->getFirst();
        } else {
            parent = T->parent(current);
        }
    }
}
