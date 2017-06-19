#include "rrt.h"

#include <iostream>

Rrt::Rrt()
{
    K = 1000;
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

void Rrt::generateRrt()
{
    Graph::Vertex vertex = NULL;
    T->init(XInit);
    TPath->init(XInit);
    for (int k = 0; k < K; k++) {
        XRand.setX(0);
        XRand.setY(0);
        XNear.setX(0);
        XNear.setY(0);
        XNew.setX(0);
        XNew.setY(0);

        this->randomState();

        vertex = this->nearestNeighbour();
        if (Util::euclideanDistance(XRand, XNear) > 0) {
            this->newState();
            if (this->validPath(XNew, XNear)) {
                this->addPath(vertex);
                T->addEdge(vertex, T->addVertex(XNew));
            }
        }
    }
    T->debug();
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
    XRand.setX(round(drand48()*cspace->getWidth()));
    XRand.setY(round(drand48()*cspace->getHeight()));
    //std::cout << " randx=" << XRand.x() << " randy=" << XRand.y() << std::endl;
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
    Graph::Vertex newe;
    for (int i = 0; i < path.size(); i++) {
        newe = TPath->addVertex(path[i]);
        TPath->addEdge(near, newe);
        near = newe;
    }
}

void Rrt::newState()
{
    XNew = XNear + 1 * ((XRand - XNear) * 0.1);
}
