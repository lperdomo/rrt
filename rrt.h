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
    void setGrid(int width, int height);
    void setXInit(QPoint XInit);
    void setXEnd(QPoint XEnd);
    void generateRrt();
private:
    int K;
    int width;
    int height;
    std::vector<Cell> grid;
    RrtGraph T;
    QPoint XInit;
    QPoint XEnd;
    void randomState(QPoint XRand);
    void nearestNeighbour(QPoint XRand, QPoint XNear);
};

#endif // RRT_H
