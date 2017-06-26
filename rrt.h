#ifndef RRT_H
#define RRT_H

#include <QObject>
#include <QVector2D>
#include <QMutex>
#include <vector>

#include "util.h"
#include "graph.h"
#include "cspace.h"
#include "state.h"

class Rrt : public QObject
{
    Q_OBJECT
public:
    Rrt();
    ~Rrt();
    void setCSpace(CSpace *cspace);
    CSpace *getCSpace();
    void setXInit(QVector2D XInit);
    QVector2D getXInit();
    void setXEnd(QVector2D XEnd);
    QVector2D getXEnd();
    void setK(int K);
    int getK();
    void setStep(int step);
    int getStep();
    void setBias(int bias);
    int getBias();
    void setMode(int mode);
    int getMode();
    bool isFound();
    std::vector<QVector2D> getResult();
private:
    int K;
    int step;
    int bias;
    State XInit;
    State XEnd;
    State XRand;
    State XNear;
    bool found;
    int mode;
    CSpace *cspace;
    Graph *T;
    void randomState();
    Graph::Vertex nearestNeighbour();
    State newState();
    bool validTransition(State p1, State p2);
    void buildResult();
    std::vector<QVector2D> result;
signals:
    void iteration();
    void ended();
public slots:
    void generateRrt();
};

#endif // RRT_H
