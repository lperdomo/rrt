#include "rrt.h"

#include <iostream>

Rrt::Rrt() :
    QObject()
{
    K = 6000;
    step = 1;
    bias = 0;
    T = new Graph();
    type = 1;
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
    this->XInit = XInit;
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

Graph *Rrt::getT()
{
    return T;
}

std::vector<QVector2D> Rrt::getPaths()
{
    return paths;
}

void Rrt::generateRrt()
{
    Graph::Vertex vertex;
    State XNew;
    paths.clear();
    found = false;
    T->init(XInit);
    for (int k = 0; (k < K && found == false); k++) {
        //std::cout << "eeeeeee1" << std::endl;
        this->randomState();
        //std::cout << "eeeeeee2=" << T->size() << std::endl;
        vertex = this->nearestNeighbour();
        //std::cout << "eeeeeee3" << std::endl;
        if (Util::euclideanDistance(XRand, XNear) > 1) {
            //std::cout << "eeeeeee4" << std::endl;
            XNew = this->newState(this->selectInput());
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
    if (mode == 1) {
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
    } else {
        double closest = -1, distance;
        Graph::Vertex vertex = 0;
        for (std::pair<Graph::VertexIterator, Graph::VertexIterator> it = T->getVertices(); it.first != it.second; ++it.first) {
            distance = Util::distanceStates(T->vertexAt(*it.first), XRand);
            if (closest < 0 || distance < closest) {
                closest = distance;
                XNear.setX(T->vertexAt(*it.first).x());
                XNear.setY(T->vertexAt(*it.first).y());
                vertex = *it.first;
            }
        }
        return vertex;
    }
}

bool Rrt::validTransition(State p1, State p2)
{
    if (mode == 1) {
        //std::vector<QVector2D> path = Util::bresenham(p1, p2);
        std::vector<State> path = Util::dubins(p1, p2, step);
        for (int i = 0; i < path.size(); i++) {
            if (cspace->isObstacle(path[i].x(), path[i].y())) return false;
            if (cspace->isTarget(path[i].x(), path[i].y())) found = true;
        }
        for (int i = 0; i < path.size(); i++) {
            paths.push_back(QVector2D(path[i].x(), path[i].y()));
        }

    }
    return true;
}

State Rrt::newState(StateInput u)
{
    if (mode == 1) {
        double th = atan2(XRand.y()-XNear.y(),XRand.x()-XNear.x());
        if (Util::euclideanDistance(XNear, XRand) < step) {
            return State(XRand.x(), XRand.y(), th);
        } else {
            return State(round(XNear.x()+step*cos(th)), round(XNear.y()+step*sin(th)), th);
        }
    } else {
        State n;
        n.setX(XNear.x()+u.v()*step*cos(XNear.th())*cos(u.th()));
        n.setY(XNear.y()+u.v()*step*sin(XNear.th())*cos(u.th()));
        n.setTh(XNear.th()+(u.v()*step/1)*sin(u.th()));
        return n;
    }
}










StateInput Rrt::selectInput()
{
    State p;
    StateInput u, optu;
    double fi[3];
    int v[2]={1, -1};
    fi[0] = atan(1*(XNear.th()-XRand.th())/((XNear.x()-XRand.x())*cos(XNear.th())+(XNear.y()-XRand.y())*sin(XNear.th())));
    fi[1] = atan(1*(XNear.th()-XRand.th()+2*M_PI)/(((XNear.x()-XRand.x())*cos(XNear.th()))+(XNear.y()-XRand.y())*sin(XNear.th())));
    fi[2] = atan(1*(XNear.th()-XRand.th()-2*M_PI)/(((XNear.x()-XRand.x())*cos(XNear.th()))+(XNear.y()-XRand.y())*sin(XNear.th())));

    double dr, d = -1;
    double MAX = M_PI/4;
    for (int i=0; i<2; i++) {
        for (int j=0; j<3; j++) {
            u.setV(v[i]);
            u.setTh(fi[j]);
            if (u.th() < -MAX) u.setTh(-MAX);
            else if (u.th() > MAX) u.setTh(MAX);

            p = this->newState(u);

            dr = Util::distanceStates(p, XRand);
            if (d < 0 || dr < d) {
                d = dr;
                optu = u;
            }
        }
    }

    StateInput u1 = optu, u2 = optu;
    State p1, p2;
    u1.setTh(u1.th()+M_PI/20);
    u2.setTh(u2.th()-M_PI/20);
    p1 = this->newState(u1);
    p2 = this->newState(u2);

    double d1, d2;
    d1 = Util::distanceStates(p1, XRand);
    d2 = Util::distanceStates(p2, XRand);
    u1.setTh(u1.th()+M_PI/20);
    u2.setTh(u2.th()-M_PI/20);
    p1 = this->newState(u1);
    p2 = this->newState(u2);

    if (d1 <= d2) return u1;
    return u2;
}
