#ifndef RRT_H
#define RRT_H

#include <QObject>
#include <QVector2D>
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
    void setXInit(QVector2D XInit);
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
    Graph *getT();
    std::vector<QVector2D> getPaths();
private:
    int K;
    int step;
    int bias;
    CSpace *cspace;
    Graph *T;
    State XInit;
    State XEnd;
    State XRand;
    State XNear;
    bool found;
    int mode;
    std::vector<QVector2D> paths;
    void randomState();
    Graph::Vertex nearestNeighbour();
    State newState(StateInput u);
    StateInput selectInput();
    bool validTransition(State p1, State p2);

signals:
    void iteration();
    void ended();
public slots:
    void generateRrt();
};

#endif // RRT_H
