#ifndef RRT_H
#define RRT_H

#include <QPoint>
#include <vector>

#include "util.h"
#include "graph.h"
#include "cspace.h"
#include "cell.h"

class Rrt
{
public:
    Rrt();
    void setCSpace(CSpace *cspace);
    void setXInit(QPoint XInit);
    void setXEnd(QPoint XEnd);    
    void generateRrt();
    Graph *getT();
    Graph *getTPath();
private:
    int K;
    CSpace *cspace;
    Graph *T;
    Graph *TPath;
    QPoint XInit;
    QPoint XEnd;
    QPoint XRand;
    QPoint XNear;
    QPoint XNew;
    std::vector<QPoint> path;
    void randomState();
    Graph::Vertex nearestNeighbour();
    void newState();
    bool validPath(QPoint p1, QPoint p2);
    void addPath(Graph::Vertex near);
};

#endif // RRT_H
