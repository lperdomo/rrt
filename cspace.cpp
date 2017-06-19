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
    return (Cspace[x][y] == false);
}

std::vector<std::vector<bool> > CSpace::getCSpace()
{
    return Cspace;
}

void CSpace::generateCSpace()
{
    Cspace.clear();
    for (int i = 0; i <= width; i++) {
        std::vector<bool> tmp;
        for (int j = 0; j <= height; j++) {
            tmp.push_back(true);
        }
        Cspace.push_back(tmp);
    }

    this->generateCobstacle();
}

void CSpace::generateCobstacle()
{
    for (int x = 0; x <= width; x++) {
        Cspace[x][0] = false;
        Cspace[x][height] = false;
    }

    for (int y = 0; y <= height; y++) {
        Cspace[0][y] = false;
        Cspace[width][y] = false;
    }

    srand(time(0));
    for (int o = 0; o < obstacles; o++) {
        Cell obstacle(round((rand()%(80+5-1)+5)*width/100), round((rand()%(80+5-1)+5)*height/100));
        int limitx = rand()%(20+1-10)+10, limity = rand()%(20+1-10)+10;
        limitx = (obstacle.x()+limitx < width ? obstacle.x()+limitx : width);
        limity = (obstacle.y()+limity < height ? obstacle.y()+limity : height);
        for (int i = obstacle.x(); i < limitx; i++) {
            for (int j = obstacle.y(); j < limity; j++) {
                Cspace[i][j] = false;
            }
        }
    }

    Cfree->clear();
    Cobstacle->clear();
    for (int x = 0; x <= width; x++) {
        for (int y = 0; y <= height; y++) {
            if (Cspace[x][y] == true) Cfree->push_back(new Cell(x, y));
            else Cobstacle->push_back(new Cell(x, y));
        }
    }
}
