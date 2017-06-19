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
    void generateCSpace();
    bool isObstacle(int x, int y);
    std::vector<std::vector<bool> > getCSpace();
private:
    int width;
    int height;
    int obstacles;
    std::vector<std::vector<bool> > Cspace;
    void generateCobstacle();
};

#endif // SPACE_H
