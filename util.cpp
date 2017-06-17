#include "util.h"

Util::Util()
{
}

double Util::euclideanDistance(QPoint from, QPoint to)
{
    QPoint delta = from - to;
    return sqrt(pow(delta.x(), 2) + pow(delta.y(), 2));
}
