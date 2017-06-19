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
    void setK(int K);
    int getK();
    void generateRrt();
    bool getFound();
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
    bool found;
    void randomState();
    Graph::Vertex nearestNeighbour();
    void newState();
    bool validPath(QPoint p1, QPoint p2);
    void addPath(Graph::Vertex near);
    void isTarget(QPoint current);
};

#endif // RRT_H
