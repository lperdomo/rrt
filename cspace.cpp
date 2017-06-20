#include "cspace.h"

#include <iostream>

CSpace::CSpace(int width, int height, int obstacles)
{
    this->width = width;
    this->height = height;
    this->obstacles = obstacles;
    Cfree = new std::vector<Cell*>();
    Cobstacle = new std::vector<Cell*>();
}

int CSpace::getWidth()
{
    return this->width;
}

int CSpace::getHeight()
{
    return this->height;
}

void CSpace::setObstacles(int obstacles)
{
    this->obstacles = obstacles;
}

int CSpace::getObstacles()
{
    return obstacles;
}


std::vector<Cell*> *CSpace::getCfree()
{
    return Cfree;
}

Cell *CSpace::freeAt(int i)
{
    if (Cfree->size() >= i) return Cfree->at(i);
    return NULL;
}

std::vector<Cell*> *CSpace::getCobstacle()
{
    return Cobstacle;
}

Cell *CSpace::obstacleAt(int i)
{
    if (Cobstacle->size() >= i) return Cobstacle->at(i);
    return NULL;
}

bool CSpace::isObstacle(int x, int y)
{
    return (Cspace[x][y] == 2);
}

bool CSpace::isTarget(int x, int y)
{
    return (Cspace[x][y] == -1);
}

std::vector<std::vector<int> > CSpace::getCSpace()
{
    return Cspace;
}

void CSpace::generateCSpace()
{
    Cspace.clear();
    for (int i = 0; i <= width; i++) {
        std::vector<int> tmp;
        for (int j = 0; j <= height; j++) {
            tmp.push_back(0);
        }
        Cspace.push_back(tmp);
    }

    this->generateCobstacle();
}

void CSpace::generateCobstacle()
{
    for (int x = 0; x <= width; x++) {
        Cspace[x][0] = 2;
        Cspace[x][height] = 2;
    }

    for (int y = 0; y <= height; y++) {
        Cspace[0][y] = 2;
        Cspace[width][y] = 2;
    }

    srand(time(0));
    for (int o = 0; o < obstacles; o++) {
        Cell obstacle(round((rand()%(80+5-1)+5)*width/100), round((rand()%(80+5-1)+5)*height/100));
        int limitx = rand()%(20+1-10)+10, limity = rand()%(20+1-10)+10;
        limitx = (obstacle.x()+limitx < width ? obstacle.x()+limitx : width);
        limity = (obstacle.y()+limity < height ? obstacle.y()+limity : height);
        for (int i = obstacle.x(); i < limitx; i++) {
            for (int j = obstacle.y(); j < limity; j++) {
                Cspace[i][j] = 2;
            }
        }
    }

    Cfree->clear();
    Cobstacle->clear();
    for (int x = 0; x <= width; x++) {
        for (int y = 0; y <= height; y++) {
            if (Cspace[x][y] <= 0) Cfree->push_back(new Cell(x, y));
            else Cobstacle->push_back(new Cell(x, y));
        }
    }

    //std::random_shuffle(Cfree->begin(), Cfree->end());


}

void CSpace::dismarkTarget(int x, int y)
{
    for (int i = x-3; i < x+2; i++) {
        for (int j = y-3; j < y+2; j++) {
            Cspace[i][j] = 0;
        }
    }
}

void CSpace::markTarget(int x, int y)
{
    for (int i = x-3; i < x+2; i++) {
        for (int j = y-3; j < y+2; j++) {
            Cspace[i][j] = -1;
        }
    }
}
