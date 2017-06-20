#ifndef RRT_H
#define RRT_H

#include <QObject>
#include <QVector2D>
#include <vector>

#include "util.h"
#include "graph.h"
#include "cspace.h"
#include "cell.h"

class Rrt : public QObject
{
    Q_OBJECT
public:
    Rrt();
    ~Rrt();
    void setCSpace(CSpace *cspace);
    void setXInit(QVector2D XInit);
    void setXEnd(QVector2D XEnd);
    QVector2D getXEnd();
    void setK(int K);
    int getK();
    void setStep(int step);
    int getStep();
    void setBias(int bias);
    int getBias();
    bool isFound();
    Graph *getT();
private:
    int K;
    int step;
    int bias;
    CSpace *cspace;
    Graph *T;
    QVector2D XInit;
    QVector2D XEnd;
    QVector2D XRand;
    QVector2D XNear;
    QVector2D XNew;
    bool found;
    void randomState();
    Graph::Vertex nearestNeighbour();
    void newState();
    bool validTransition(QVector2D p1, QVector2D p2);
    bool isXEnd(QVector2D current);
signals:
    void iteration();
    void ended();
public slots:
    void generateRrt();
};

#endif // RRT_H
