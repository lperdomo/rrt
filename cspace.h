#ifndef SPACE_H
#define SPACE_H

#include <vector>

#include "util.h"
#include "cell.h"

class CSpace
{
public:
    CSpace(int width, int height);
    int getWidth();
    int getHeight();
    void generateCSpace();
    bool isObstacle(int x, int y);
    std::vector<std::vector<bool> > getCSpace();
private:
    int width;
    int height;
    std::vector<std::vector<bool> > Cspace;
    void generateCobstacle();
};

#endif // SPACE_H
