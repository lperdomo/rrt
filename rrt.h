#ifndef RRT_H
#define RRT_H

#include <QPoint>
#include <vector>

#include "util.h"
#include "rrtgraph.h"
#include "cell.h"

class Rrt
{
public:
    Rrt();
    void setXInit(QPoint XInit);
    void setXEnd(QPoint XEnd);
    RrtGraph generateRrt();
    void generateCSpace(int width, int height);
    std::vector<Cell> getCobs();
private:
    int K;
    int width;
    int height;
    std::vector<Cell> Cfree;
    std::vector<Cell> Cobs;
    RrtGraph T;
    QPoint XInit;
    QPoint XEnd;
    void randomState(QPoint &XRand);
    Vertex nearestNeighbour(QPoint XRand, QPoint &XNear);
    void newState(QPoint XNear, QPoint u, QPoint deltat, QPoint &XNew);
};

#endif // RRT_H
