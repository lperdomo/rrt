#include "cspace.h"

#include <iostream>

CSpace::CSpace(int width, int height, int obstacles)
{
    this->width = width;
    this->height = height;
    this->obstacles = obstacles;
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
        Cell obstacle(round((rand()%(100+1-1)+1)*width/100), round((rand()%(100+1-1)+1)*height/100));
        int limitx = rand()%(20+1-10)+10, limity = rand()%(20+1-10)+10;
        limitx = (obstacle.x()+limitx < width ? obstacle.x()+limitx : width);
        limity = (obstacle.x()+limity < height ? obstacle.x()+limity : height);

        int type = rand()%(2+1-1)+1;

        if (type == 1) {
            for (int i = obstacle.x(); i < limitx; i++) {
                Cspace[i][obstacle.y()] = false;
            }
        } else if (type == 2) {
            for (int i = obstacle.x(); i < limitx; i++) {
                for (int j = obstacle.y(); j < limity; j++) {
                    Cspace[i][j] = false;
                }
            }
        }
    }
}
