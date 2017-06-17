#include "cell.h"

double Cell::size = 5;

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Cell::getX()
{
    return x;
}

int Cell::getY()
{
    return y;
}
