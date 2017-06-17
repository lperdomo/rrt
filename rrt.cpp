#include "rrt.h"

#include <iostream>

Rrt::Rrt()
{
    K = 1000;
    srand(time(0));
}

void Rrt::setGrid(int width, int height)
{
    this->width = width;
    this->height = height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            grid.push_back(Cell(i, j));
        }
    }
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
    //std::cout << "x" << round(drand48()*width) << " y" << round(drand48()*height) << std::endl;
    QPoint XRand, XNear, XNew;

    T.init(XInit);
    for (int k = 0; k < K; k++) {
        this->randomState(XRand);
        this->nearestNeighbour(XRand, XNear);
    }
}

void Rrt::randomState(QPoint XRand)
{
    XRand.setX(round(drand48()*width));
    XRand.setX(round(drand48()*height));
}

void Rrt::nearestNeighbour(QPoint XRand, QPoint XNear)
{
    double d = -1, p;
    for (std::pair<VertexIterator, VertexIterator> it = T.getVertices(); it.first != it.second; ++it.first) {
        std::cout << " eita x" << dynamic_cast<QPoint*>(*it.first).x() << " y" << dynamic_cast<QPoint*>(*it.first).y() << std::endl;
        p = Util::euclideanDistance(dynamic_cast<QPoint*>(*it.first), XRand);
        if (d < 0 || p < d) {
            d = p;
            XNear.setX(dynamic_cast<QPoint*>(*it.first).x());
            XNear.setY(dynamic_cast<QPoint*>(*it.first).y());
        }
    }
}
