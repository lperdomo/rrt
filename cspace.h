#ifndef SPACE_H
#define SPACE_H

#include <vector>

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
    std::vector<std::vector<bool> > getCSpace();
    Cell *freeAt(int i);
    Cell *obstacleAt(int i);
    void generateCSpace();
    bool isObstacle(int x, int y);
private:
    int width;
    int height;
    int obstacles;
    std::vector<std::vector<bool> > Cspace;
    std::vector<Cell*> *Cfree;
    std::vector<Cell*> *Cobstacle;
    void generateCobstacle();
};

#endif // SPACE_H
