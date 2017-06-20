#include "util.h"

Util::Util()
{
}

double Util::euclideanDistance(QVector2D from, QVector2D to)
{
    QVector2D delta = from - to;
    return sqrt(pow(delta.x(), 2) + pow(delta.y(), 2));
}
