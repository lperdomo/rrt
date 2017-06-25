#ifndef SPACE_H
#define SPACE_H

#include <QVector2D>
#include <vector>
#include <deque>

#include "util.h"

class CSpace
{
public:
    CSpace(int width, int height, int obstacles);
    int getWidth();
    int getHeight();
    void setObstacles(int obstacles);
    int getObstacles();
    std::vector<QVector2D> *getCfree();
    std::vector<QVector2D> *getCobstacle();
    std::vector<std::vector<int> > getCSpace();
    QVector2D freeAt(int i);
    QVector2D obstacleAt(int i);
    void generateCSpace();
    void clearCSpace();
    bool isObstacleAt(int x, int y);
    bool isTargetAt(int x, int y);
    bool isVertexAt(int x, int y);
    bool isResultVertexAt(int x, int y);
    void markTarget(int x, int y);
    void dismarkTarget(int x, int y);
    void setPathAt(int x, int y);
    void setVertexAt(int x, int y);
    void setResultPathAt(int x, int y);
    void setResultVertexAt(int x, int y);
private:
    int width;
    int height;
    int obstacles;
    std::vector<std::vector<int> > Cspace;
    std::vector<QVector2D> *Cfree;
    std::vector<QVector2D> *Cobstacle;
    void generateCobstacle();
};

#endif // SPACE_H
