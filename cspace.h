#ifndef SPACE_H
#define SPACE_H

#include <vector>
#include <deque>

#include "util.h"
#include "cell.h"

class CSpace
{
public:
    CSpace(int width, int height, int obstacles);
    int getWidth();
    int getHeight();
    void setObstacles(int obstacles);
    int getObstacles();
    std::vector<Cell*> *getCfree();
    std::vector<Cell*> *getCobstacle();
    std::vector<std::vector<int> > getCSpace();
    Cell *freeAt(int i);
    Cell *obstacleAt(int i);
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
    std::vector<Cell*> *Cfree;
    std::vector<Cell*> *Cobstacle;
    void generateCobstacle();
};

#endif // SPACE_H
