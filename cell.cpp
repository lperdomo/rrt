#include "cell.h"

double Cell::size = 5;

Cell::Cell(int X, int Y)
{
    this->X = X;
    this->Y = Y;
}

int Cell::x()
{
    return X;
}

int Cell::y()
{
    return Y;
}

bool Cell::operator<(Cell &b)
{
    if (this->x() < b.x()) {
        return true;
    } else if (this->x() == b.x()) {
        if (this->y() < b.y()) {
            return true;
        }
    }
    return false;
}
