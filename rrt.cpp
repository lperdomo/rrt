#include "rrt.h"

#include <iostream>

Rrt::Rrt()
{
    K = 1000;
    step = 1;
    T = new Graph();
    TPath = new Graph();
}

void Rrt::setCSpace(CSpace *cspace)
{
    this->cspace = cspace;
}

void Rrt::setXInit(QPoint XInit)
{
    this->XInit.setX(XInit.x()/Cell::size);
    this->XInit.setY(XInit.y()/Cell::size);
}

void Rrt::setXEnd(QPoint XEnd)
{
    this->XEnd.setX(XEnd.x()/Cell::size);
    this->XEnd.setY(XEnd.y()/Cell::size);
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

void Rrt::generateRrt()
{
    Graph::Vertex vertex = NULL;
    found = false;
    T->init(XInit);
    TPath->init(XInit);
    for (int k = 0; (k < K && found == false); k++) {
        XRand.setX(0);
        XRand.setY(0);
        XNear.setX(0);
        XNear.setY(0);
        XNew.setX(0);
        XNew.setY(0);

        this->randomState();

        vertex = this->nearestNeighbour();
        if (Util::euclideanDistance(XRand, XNear) > step) {
            this->newState();
            if (this->validPath(XNew, XNear)) {
                this->addPath(vertex);
                T->addEdge(vertex, T->addVertex(XNew));
            }
        }
    }
    T->debug();
}

bool Rrt::getFound()
{
    return found;
}

Graph *Rrt::getT()
{
    return T;
}

Graph *Rrt::getTPath()
{
    return TPath;
}

void Rrt::randomState()
{
    /*int id = rand()%Cfree.size();
    XRand.setX(Cfree[id].x());
    XRand.setY(Cfree[id].y());*/
    //srand(time(0));
    int prob = rand()%100;

    if (prob <= -1) {
        std::cout << "prob" << prob << std::endl;
        XRand.setX(XEnd.x());
        XRand.setY(XEnd.y());
    } else {
        int id = rand()%cspace->getCfree()->size();
        XRand.setX(cspace->freeAt(id)->x());
        XRand.setY(cspace->freeAt(id)->y());
        //XRand.setX(round(drand48()*cspace->getWidth()));
        //XRand.setY(round(drand48()*cspace->getHeight()));
    }
    //std::cout << " randx=" << XRand.x() << " randy=" << XRand.y() << std::endl;
}

Graph::Vertex Rrt::nearestNeighbour()
{
    double closest = -1, distance;
    Graph::Vertex vertex = 0;
    //for (std::pair<Graph::VertexIterator, Graph::VertexIterator> it = T->getVertices(); it.first != it.second; ++it.first) {
    for (std::pair<Graph::VertexIterator, Graph::VertexIterator> it = TPath->getVertices(); it.first != it.second; ++it.first) {
        distance = Util::euclideanDistance(TPath->vertexAt(*it.first), XRand);
        if (closest < 0 || distance < closest) {
            closest = distance;
            XNear.setX(TPath->vertexAt(*it.first).x());
            XNear.setY(TPath->vertexAt(*it.first).y());
            vertex = *it.first;
        }
    }
    return vertex;
}

bool Rrt::validPath(QPoint p1, QPoint p2)
{
    int dx = p2.x() - p1.x(), dy = p2.y() - p1.y()
       , dx1 = abs(dx), dy1 = abs(dy)
       , px = 2*dy1-dx1, py = 2*dx1-dy1
       , x, y, xe, ye;

    path.clear();
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
        path.push_back(QPoint(x, y));
        for (int i = 0; x < xe; i++) {
            x++;
            if (px < 0) px += 2*dy1;
            else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y++;
                else y--;
                px += 2*(dy1-dx1);
            }
            if (cspace->isObstacle(x, y)) return false;
            path.push_back(QPoint(x, y));
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
        path.push_back(QPoint(x, y));
        for (int i = 0; y < ye; i++) {
            y++;
            if (py <= 0) py += 2*dx1;
            else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x++;
                else x--;
                py += 2*(dx1-dy1);
            }
            if (cspace->isObstacle(x, y)) return false;
            path.push_back(QPoint(x, y));
        }
    }
    return true;
}

void Rrt::addPath(Graph::Vertex near)
{
    Graph::Vertex step;
    for (int i = 0; i < path.size(); i++) {
        this->isTarget(path[i]);
        step = TPath->addVertex(path[i]);
        TPath->addEdge(near, step);
        near = step;
    }
}

void Rrt::newState()
{
    XNew = XNear + step * ((XRand - XNear) * 0.1);
}

void Rrt::isTarget(QPoint current)
{
    if ((current.x() == XEnd.x() && current.y() == XEnd.y())
       || (current.x() == XEnd.x() && current.y() == XEnd.y()-1)
       || (current.x() == XEnd.x()-1 && current.y() == XEnd.y())
       || (current.x() == XEnd.x()-1 && current.y() == XEnd.y()-1)) {
        found = true;
    }
}
