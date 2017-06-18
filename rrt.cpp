#include "rrt.h"

#include <iostream>

Rrt::Rrt()
{
    K = 1000;
}

void Rrt::generateCSpace(int width, int height)
{
    this->width = width;
    this->height = height;

    srand(time(0));
    int obstacles = rand()%(10+1-2)+2;
    Cobs.clear();
    for (int i = 0; i < obstacles; i++) {
        Cell obstacle(round((rand()%(100+1-1)+1)*width/100), round((rand()%(100+1-1)+1)*height/100));
        int limit = rand()%(20+1-10)+10;
        limit = (obstacle.x()+limit < width ? limit : width);
        for (int j = 0; j < limit; j++) {
            Cobs.push_back(Cell(obstacle.x()+j, obstacle.y()));
        }
    }
    std::cout << "eeee" << std::endl;
    std::sort(Cobs.begin(), Cobs.end());
    for (int i = 0; i < Cobs.size(); i++) {
        std::cout << "cobsx" << Cobs[i].x() << " cobsy" << Cobs[i].y() << std::endl;
    }

    Cfree.clear();
    int cobs = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            std::cout << "cobs" << cobs << " obsx" << Cobs[cobs].x() << " i" << i << " obsy" << Cobs[cobs].y() << " j" << j << std::endl;
            if (Cobs[cobs].x() == i && Cobs[cobs].y() == j) {
                std::cout << "ffffff" << std::endl;
                if (cobs < Cobs.size()) {
                    std::cout << "ggggg" << Cobs.size() << std::endl;
                    cobs++;
                }
            } else {
                Cfree.push_back(Cell(i,j));
            }
        }
    }
    std::cout << "obstacles" << Cobs.size() << " cobs" << cobs << std::endl;
    std::cout << "frees" << Cfree.size() << std::endl;
}

std::vector<Cell> Rrt::getCobs()
{
    return Cobs;
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

RrtGraph Rrt::generateRrt()
{
    QPoint XRand, XNear, XNew;
    Vertex near;
    T.init(XInit);
    for (int k = 0; k < K; k++) {
        this->randomState(XRand);
        near = this->nearestNeighbour(XRand, XNear);
        this->newState(XNear, XRand, XRand - XNear, XNew);
        T.addEdge(near, T.addVertex(XNew));
    }
    T.debug();
    return T;
}

void Rrt::randomState(QPoint &XRand)
{
    int id = rand()%Cfree.size();
    XRand.setX(Cfree[id].x());
    XRand.setY(Cfree[id].y());
    //srand(time(0));
    //XRand.setX(round(drand48()*width));
    //XRand.setY(round(drand48()*height));
    //std::cout << " randx=" << XRand.x() << " randy=" << XRand.y() << std::endl;
}

Vertex Rrt::nearestNeighbour(QPoint XRand, QPoint &XNear)
{
    double d = -1, p;
    Vertex vertex;
    for (std::pair<VertexIterator, VertexIterator> it = T.getVertices(); it.first != it.second; ++it.first) {
        //std::cout << "x" << T.vertexAt(*it.first).x() << std::endl;
        //std::cout << "eeeee" << std::endl;
        p = Util::euclideanDistance(T.vertexAt(*it.first), XRand);
        /*std::cout << "x=" << T.vertexAt(*it.first).x()
                  << " y=" << T.vertexAt(*it.first).y()
                  << " p" << p
                  << " randx=" << XRand.x()
                  << " randy=" << XRand.y()
                  << std::endl;*/
        if (d < 0 || p < d) {
            d = p;
            XNear.setX(T.vertexAt(*it.first).x());
            XNear.setY(T.vertexAt(*it.first).y());
            vertex = *it.first;
        }
    }
    return vertex;
}

void Rrt::newState(QPoint XNear, QPoint u, QPoint deltat, QPoint &XNew)
{
    //std::cout << "deltat x" << deltat.x() << " y" << deltat.y() << std::endl;
    XNew = XNear + deltat * 0.1;
}
