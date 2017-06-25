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
    bool isObstacle(int x, int y);
    bool isTarget(int x, int y);
    void markTarget(int x, int y);
    void dismarkTarget(int x, int y);
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
