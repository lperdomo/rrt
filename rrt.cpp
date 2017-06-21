#include "rrt.h"

#include <iostream>

Rrt::Rrt() :
    QObject()
{
    K = 10000;
    step = 1;
    bias = 0;
    T = new Graph();
}

Rrt::~Rrt()
{
}

void Rrt::setCSpace(CSpace *cspace)
{
    this->cspace = cspace;
}

void Rrt::setXInit(QVector2D XInit)
{
    this->XInit.setX(round(XInit.x()/Cell::size));
    this->XInit.setY(round(XInit.y()/Cell::size));
}

void Rrt::setXEnd(QVector2D XEnd)
{
    this->XEnd.setX(round(XEnd.x()/Cell::size));
    this->XEnd.setY(round(XEnd.y()/Cell::size));
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

bool Rrt::isFound()
{
    return found;
}

Graph *Rrt::getT()
{
    return T;
}

void Rrt::generateRrt()
{
    Graph::Vertex vertex;
    found = false;
    T->init(XInit);
    for (int k = 0; (k < K && found == false); k++) {
        //std::cout << "eeeeeee1" << std::endl;
        this->randomState();
        //std::cout << "eeeeeee2=" << T->size() << std::endl;
        vertex = this->nearestNeighbour();
        //std::cout << "eeeeeee3" << std::endl;
        if (Util::euclideanDistance(XRand, XNear) > step) {
            //std::cout << "eeeeeee4" << std::endl;
            this->newState();
            //std::cout << "eeeeeee5" << std::endl;
            if (this->validTransition(XNew, XNear)) {
                //std::cout << "eeeeeee6" << std::endl;
                T->addEdge(vertex, T->addVertex(XNew));
                //std::cout << "eeeeeee7" << std::endl;
            }
        }
        //std::cout << "eeeeeee8" << std::endl;
        this->iteration();
        //std::cout << "eeeeeee9" << std::endl;
    }
    //std::cout << "eeeeeee100" << std::endl;
    this->ended();
}

void Rrt::randomState()
{
    if (bias > 0 && rand()%100 <= bias) {
        XRand.setX(XEnd.x());
        XRand.setY(XEnd.y());
    } else {
        int id = rand()%cspace->getCfree()->size();
        XRand.setX(cspace->freeAt(id)->x());
        XRand.setY(cspace->freeAt(id)->y());
        //XRand.setX(round(drand48()*cspace->getWidth()));
        //XRand.setY(round(drand48()*cspace->getHeight()));
    }
}

Graph::Vertex Rrt::nearestNeighbour()
{
    double closest = -1, distance;
    Graph::Vertex vertex = 0;
    for (std::pair<Graph::VertexIterator, Graph::VertexIterator> it = T->getVertices(); it.first != it.second; ++it.first) {
        distance = Util::euclideanDistance(T->vertexAt(*it.first), XRand);
        if (closest < 0 || distance < closest) {
            closest = distance;
            XNear.setX(T->vertexAt(*it.first).x());
            XNear.setY(T->vertexAt(*it.first).y());
            vertex = *it.first;
        }
    }
    return vertex;
}

bool Rrt::validTransition(QVector2D p1, QVector2D p2)
{
    int dx = p2.x() - p1.x(), dy = p2.y() - p1.y()
       , dx1 = abs(dx), dy1 = abs(dy)
       , px = 2*dy1-dx1, py = 2*dx1-dy1
       , x, y, xe, ye;
    if (dy1 <= dx1) {
        if (dx >= 0) {
            x = p1.x();
            y = p1.y();
            xe = p2.x();
        } else {
            x = p2.x();
            y = p2.y();
            xe = p1.x();
        }
        if (cspace->isObstacle(x, y)) return false;
        this->isXEnd(QVector2D(x, y));
        for (int i = 0; x < xe; i++) {
            x++;
            if (px < 0) px += 2*dy1;
            else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y++;
                else y--;
                px += 2*(dy1-dx1);
            }
            if (cspace->isObstacle(x, y)) return false;
            this->isXEnd(QVector2D(x, y));
        }
    } else {
        if (dy >= 0) {
            x = p1.x();
            y = p1.y();
            ye = p2.y();
        } else {
            x = p2.x();
            y = p2.y();
            ye = p1.y();
        }
        if (cspace->isObstacle(x, y)) return false;
        this->isXEnd(QVector2D(x, y));
        for (int i = 0; y < ye; i++) {
            y++;
            if (py <= 0) py += 2*dx1;
            else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x++;
                else x--;
                py += 2*(dx1-dy1);
            }
            if (cspace->isObstacle(x, y)) return false;
            this->isXEnd(QVector2D(x, y));
        }
    }
    return true;
}

void Rrt::newState()
{
    if (Util::euclideanDistance(XNear, XRand) < step) {
        XNew = XRand;
    } else {
        double th = atan2(XRand.y()-XNear.y(),XRand.x()-XNear.x());
        XNew.setX(round(XNear.x()+step*cos(th)));
        XNew.setY(round(XNear.y()+step*sin(th)));
    }
}

bool Rrt::isXEnd(QVector2D current)
{
    if (cspace->isTarget(current.x(), current.y())) {
        found = true;
        return true;
    }
    return false;
}
